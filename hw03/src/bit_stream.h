#ifndef _BIT_STREAM_H_
#define _BIT_STREAM_H_

#include <exception>
#include <iostream>
#include <cstddef>

class inputBitStream {
public:
	inputBitStream(std::istream &stream);
	char read();

private:
	std::istream *_ifs;
	char _buffer;
	std::size_t _bitCount;
};

class outputBitStream {
public:
	outputBitStream(std::ostream &stream);
	~outputBitStream();
	void write(char bit);
	
private:
	std::ostream *_ofs;
	char _buffer;
	std::size_t _bitCount;
};

class BitStreamExeption : public std::exception {
public:
	BitStreamExeption(const std::string& _m);
	~BitStreamExeption() throw() {}
	const char* what() const throw();

private:
	std::string _message;
};

#endif