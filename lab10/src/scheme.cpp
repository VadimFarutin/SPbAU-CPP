#include "scheme.h"

Scheme::Scheme(int capacity) {
	figures_ = new Figure*[capacity];
	capacity_ = capacity;
	size_ = 0;
}

Scheme::~Scheme() {
	for (int i = 0; i < size_; i++)
		delete figures_[i];

	delete []figures_;
}

int Scheme::get_figure_index(int id) {
	int index = 0;
	while (index < size_ && figures_[index]->get_id() != id)
		index++;

	if (index == size_)
		return -1;
	return index;
}

void Scheme::push_back_figure(Figure* fg) {
	if (size_ + 1 <= capacity_)
		figures_[size_++] = fg;
}

void Scheme::remove_figure(int id) {
	int to_delete = get_figure_index(id);
	if (to_delete == -1)
		return;

	delete figures_[to_delete];
	size_--;
	for (int i = to_delete; i < size_; i++)
		figures_[i] = figures_[i + 1];
}

void Scheme::print_all_figures() {
	for (int i = 0; i < size_; i++)
		figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
	int to_zoom = get_figure_index(id);
	if (to_zoom == -1)
		return;

	figures_[to_zoom]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
	for (int i = 0; i < size_; i++)
		if (figures_[i]->is_inside(x, y))
			return figures_[i];

	return 0;
}

void Scheme::move(int id, int new_x, int new_y) {
	int to_move = get_figure_index(id);
	if (to_move == -1)
		return;

	figures_[to_move]->move(new_x, new_y);
}
