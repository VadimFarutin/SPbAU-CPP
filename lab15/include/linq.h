#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iterator>
#include <functional>

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;

template<typename T>
class enumerator {
public:
	auto drop(int count) {
		return drop_enumerator<T>(*this, count);
	}

	auto take(int count) {
		return take_enumerator<T>(*this, count);
	}

	template<typename U = T, typename F>
	auto select(F func) {
		return select_enumerator<U, T, F>(*this, func);
	}

	template<typename F>
	auto until(F predicate) {
		return until_enumerator<T, F>(*this, predicate);
	}

	auto until_eq(const T &elem) {
		std::function<bool(T)> predicate = [elem](T current) { return current == elem; };
		return until_enumerator<T, std::function<bool(T)>>(*this, predicate);
	}

	template<typename F>
	auto where(F predicate) {
		return where_enumerator<T, F>(*this, predicate);
	}

	auto where_neq(const T &elem) {
		std::function<bool(T)> predicate = [elem](T current) { return current != elem; };
		return where_enumerator<T, std::function<bool(T)>>(*this, predicate);
	}

	std::vector<T> to_vector() {
		std::vector<T> out;
		while (*this == true) {
			T next = *(*this);
			out.push_back(next);
			++(*this);
		}

		return out;
	}

	template<typename Iter>
	void copy_to(Iter &it) {
		while (*this == true) {
			*it = (*(*this));
			++it;
			++(*this);
		}
	}

	virtual const T &operator*() const = 0;
	virtual void operator++() = 0;
	virtual operator bool() const = 0;
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
	range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

private:
	const T &operator*() const override {
		return *begin_;
	}

	void operator++() override {
		++begin_;
	}

	operator bool() const override {
		return begin_ != end_;
	}

	Iter begin_, end_;
};

template<typename T>
auto from(T begin, T end) {
	return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
	drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
		for (int i = 0; i < count; i++) {
			if (parent_ == false) {
				break;
			}

			++parent_;
		}
	}

private:
	const T &operator*() const override {
		return *parent_;
	}

	void operator++() override {
		++parent_;
	}

	operator bool() const override {
		return parent_ == true;
	}

	enumerator<T> &parent_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
	take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

private:
	const T &operator*() const override {
		return *parent_;
	}

	void operator++() override {
		--count_;
		++parent_;
	}

	operator bool() const override {
		return count_ > 0 && parent_ == true;
	}

	enumerator<T> &parent_;
	int count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
	select_enumerator(enumerator<U> &parent, F &func) : parent_(parent), func_(func) {
		if (parent_ == true) {
			current_ = func_(*parent_);
		}
	}

private:
	const T &operator*() const override {
		return current_;
	}

	void operator++() override {
		++parent_;
		if (parent_ == true) {
			current_ = func_(*parent_);
		}
	}

	operator bool() const override {
		return parent_ == true;
	}

	enumerator<U> &parent_;
	F func_;
	T current_;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
	until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(predicate) {
		if (parent_ == true) {
			current_ = *parent_;
			is_current_good_ = !predicate_(current_);
		}
		else {
			is_current_good_ = false;
		}
	}

private:
	const T &operator*() const override {
		return current_;
	}

	void operator++() override {
		++parent_;

		if (parent_ == true) {
			current_ = *parent_;
			is_current_good_ = !predicate_(current_);
		}
		else {
			is_current_good_ = false;
		}
	}

	operator bool() const override {
		return is_current_good_;
	}

	enumerator<T> &parent_;
	F predicate_;
	T current_;
	bool is_current_good_;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
	where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(predicate) {
		is_current_good_ = false;

		while (parent_ == true) {
			current_ = *parent_;
			is_current_good_ = predicate_(current_);
			if (is_current_good_) {
				break;
			}

			++parent_;
		}
	}

private:
	const T &operator*() const override {
		return current_;
	}

	void operator++() override {
		++parent_;
		is_current_good_ = false;

		while (parent_ == true) {
			current_ = *parent_;
			is_current_good_ = predicate_(current_);
			if (is_current_good_) {
				break;
			}

			++parent_;
		}
	}

	operator bool() const override {
		return is_current_good_;
	}

	enumerator<T> &parent_;
	F predicate_;
	T current_;
	bool is_current_good_;
};

#endif
