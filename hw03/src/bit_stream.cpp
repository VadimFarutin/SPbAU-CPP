#include "bit_stream.h"

inputBitStream::inputBitStream(std::istream &stream) {
	_ifs = &stream;
	_buffer = 0;
	_bitCount = 0;
}

char inputBitStream::read() {
	if (_bitCount == 0) {
		_ifs->read(&_buffer, 1);

		if (_ifs->bad()) {
			throw BitStreamExeption("Error reading file.");
		}

		_bitCount = 8;
	}

	char bit = (_buffer >> 7) & 1;
	_buffer = _buffer << 1;
	_bitCount--;

	return bit;
}

outputBitStream::outputBitStream(std::ostream &stream) {
	_ofs = &stream;
	_buffer = 0;
	_bitCount = 0;
}

outputBitStream::~outputBitStream() {
	try {
		if (_bitCount != 0) {
			_buffer = _buffer << (8 - _bitCount);

			_ofs->write(&_buffer, 1);

			if (_ofs->bad()) {
				throw BitStreamExeption("Error writing to file.");
			}
		}
	}
	catch (const std::exception &e) {
		std::cout << e.what() << '\n';
	}
}

void outputBitStream::write(char bit) {
	_buffer = (_buffer << 1) | bit;
	_bitCount++;

	if (_bitCount == 8) {
		_ofs->write(&_buffer, 1);

		if (_ofs->bad()) {
			throw BitStreamExeption("Error writing to file.");
		}

		_bitCount = 0;
	}
}


BitStreamExeption::BitStreamExeption(const std::string &m)
	: _message(m) {}
const char* BitStreamExeption::what() const throw() {
	return _message.c_str();
}