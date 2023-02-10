#include "PacketSerializer.h"



size_t packetSerializer::push(const char* _data, size_t _size)
{
	if (useableSize() < _size) {
		throw std::invalid_argument("packetSerializer size overflow");

		return -1;
	}

	memmove(tailPtr, _data, _size);
	moveRear(_size);

	return _size;
}

size_t packetSerializer::pop(char* _data, size_t _size)
{
	if (size() < _size)
		_size = size();

	memmove(_data, headPtr, _size);
	moveFront(_size);

	return _size;
}

size_t packetSerializer::peek(char* _buffer, size_t _size)
{
	if (size() < _size)
		_size = size();

	memmove(_buffer, headPtr, _size);

	return _size;
}


int packetSerializer::moveFront(const int _size)
{
	int offset = 0;

	if (_size > 0)
		offset = min(_size, size());
	else
		offset = max(_size, bufferPtr - headPtr);
	headPtr += offset;

	return offset;
}
int packetSerializer::moveRear(const int _size)
{
	int offset = 0;

	if (_size > 0)
		offset = min(_size, useableSize());
	else
		offset = max(_size, headPtr - tailPtr);
	tailPtr += offset;

	return offset;
}

int packetSerializer::incReferenceCounter(int size)
{
	return InterlockedAdd(&referenceCounter, size);
}

int packetSerializer::decReferenceCounter(int size)
{
	return InterlockedAdd(&referenceCounter, -size);
}



packetSerializer& packetSerializer::operator << (const char v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator << (const unsigned char v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator << (const wchar_t v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

//

packetSerializer& packetSerializer::operator << (const short v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator << (const unsigned short v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator << (const int v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator << (const unsigned int v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator << (const long v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator << (const unsigned long v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator << (const long long v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator << (const unsigned long long v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

//

packetSerializer& packetSerializer::operator << (const float v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator << (const double v) {
	if (useableSize() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
//


	//

packetSerializer& packetSerializer::operator >> (char& v) {
	if (size() < sizeof(v)) {
		clean();

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator >> (unsigned char& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator >> (wchar_t& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

//

packetSerializer& packetSerializer::operator >> (short& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator >> (unsigned short& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator >> (int& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator >> (unsigned int& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator >> (long& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator >> (unsigned long& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator >> (long long& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
packetSerializer& packetSerializer::operator >> (unsigned long long& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

//

packetSerializer& packetSerializer::operator >> (float& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

packetSerializer& packetSerializer::operator >> (double& v) {
	if (size() < sizeof(v)) {
		throw std::invalid_argument("packetSerializer pop fail");

		return *this;
	}

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
//

/*/ custom data type //

/*/



packetSerializer& packetSerializer::operator = (packetSerializer& v) {
	if (this->bufferSize < v.size())
	{
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	clear();
	resize(v.bufferSize);

	memmove(bufferPtr, v.bufferPtr, bufferSize);
	headPtr = bufferPtr + (v.headPtr - v.bufferPtr);
	tailPtr = bufferPtr + (v.tailPtr - v.bufferPtr);

	return *this;
}

packetSerializer& packetSerializer::operator = (serializer& v)
{
	if (this->bufferSize < v.size())
	{
		throw std::invalid_argument("packetSerializer size overflow");

		return *this;
	}

	clear();
	resize(v.bufferSize);

	memmove(bufferPtr, v.bufferPtr, bufferSize);
	headPtr = bufferPtr + (v.headPtr - v.bufferPtr);
	tailPtr = bufferPtr + (v.tailPtr - v.bufferPtr);

	return *this;
}


