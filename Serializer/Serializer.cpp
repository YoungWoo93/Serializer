#include "Serializer.h"

size_t serializer::push(const char* _data, size_t _size)
{
	if (useableSize() < _size) {
		clean();

		while (useableSize() < _size)
			resize(bufferSize * 2);
	}

	memmove(tailPtr, _data, _size);
	moveRear(_size);

	return _size;
}

size_t serializer::pop(char* _data, size_t _size)
{
	if (size() < _size)
		_size = size();

	memmove(_data, headPtr, _size);
	moveFront(_size);

	return _size;
}

size_t serializer::peek(char* _buffer, size_t _size)
{
	if (size() < _size)
		_size = size();

	memmove(_buffer, headPtr, _size);

	return _size;
}


int serializer::moveFront(const int _size)
{
	int offset;
	if (_size >= 0)
		offset = min(_size, size());
	else
		offset = max(_size, bufferPtr - headPtr);
	
	headPtr += offset;
	return offset;
}
int serializer::moveRear(const int _size)
{
	int offset;
	if (_size >= 0)
		offset = min(_size, useableSize());
	else
		offset = max(_size, headPtr - tailPtr);

	tailPtr += offset;
	return offset;
}



serializer& serializer::operator << (const bool v) {
	if (useableSize() < sizeof(char)) {
		clean();

		while (useableSize() < sizeof(char))
			resize(bufferSize * 2);
	}

	char temp = (v ? 1 : 0);

	memmove(tailPtr, &temp, sizeof(char));
	moveRear(sizeof(char));

	return *this;
}

serializer& serializer::operator << (const char v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
serializer& serializer::operator << (const unsigned char v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

serializer& serializer::operator << (const wchar_t v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

//

serializer& serializer::operator << (const short v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
serializer& serializer::operator << (const unsigned short v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

serializer& serializer::operator << (const int v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
serializer& serializer::operator << (const unsigned int v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

serializer& serializer::operator << (const long v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
serializer& serializer::operator << (const unsigned long v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

serializer& serializer::operator << (const long long v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
serializer& serializer::operator << (const unsigned long long v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

//

serializer& serializer::operator << (const float v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

serializer& serializer::operator << (const double v) {
	if (useableSize() < sizeof(v)) {
		clean();

		while (useableSize() < sizeof(v))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
serializer& serializer::operator << (const std::string& v)
{
	int length = v.size();

	if (useableSize() < length + sizeof(int)) {
		clean();

		while (useableSize() < length + sizeof(int))
			resize(bufferSize * 2);
	}

	memmove(tailPtr, &length, sizeof(int));
	moveRear(sizeof(int));

	memmove(tailPtr, v.c_str(), v.size());
	moveRear(length);

	return *this;
}
//

serializer& serializer::operator >> (std::string& v)
{
	int length;
	if (size() < sizeof(int)) {
		clean();

		return *this;
	}

	memmove(&length, headPtr, sizeof(int));
	moveFront(sizeof(int));

	v.assign(headPtr, length);
	moveFront(length);

	return *this;
}
	//
serializer& serializer::operator >> (bool& v) {
	if (size() < sizeof(char)) {
		clean();

		return *this;
	}
	
	char temp;
	memmove(&temp, headPtr, sizeof(char));
	moveFront(sizeof(char));

	v = (temp == 0 ? false : true);

	return *this;
}

serializer& serializer::operator >> (char& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
serializer& serializer::operator >> (unsigned char& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

serializer& serializer::operator >> (wchar_t& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

//

serializer& serializer::operator >> (short& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
serializer& serializer::operator >> (unsigned short& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

serializer& serializer::operator >> (int& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
serializer& serializer::operator >> (unsigned int& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

serializer& serializer::operator >> (long& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
serializer& serializer::operator >> (unsigned long& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

serializer& serializer::operator >> (long long& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
serializer& serializer::operator >> (unsigned long long& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

//

serializer& serializer::operator >> (float& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

serializer& serializer::operator >> (double& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
//

/*/ custom data type //

/*/



serializer& serializer::operator = (serializer& v) {
	clear();
	resize(v.bufferSize);

	memmove(bufferPtr, v.bufferPtr, bufferSize);
	headPtr = bufferPtr + (v.headPtr - v.bufferPtr);
	tailPtr = bufferPtr + (v.tailPtr - v.bufferPtr);

	return *this;
}

serializer& serializer::operator = (packetSerializer& v)
{
	clear();
	resize(v.bufferSize);

	memmove(bufferPtr, v.bufferPtr, bufferSize);
	headPtr = bufferPtr + (v.headPtr - v.bufferPtr);
	tailPtr = bufferPtr + (v.tailPtr - v.bufferPtr);

	return *this;
}



