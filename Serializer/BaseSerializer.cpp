#include "BaseSerializer.h"




size_t BaseSerializer::push(const char* _data, size_t _size)
{
	memmove(tailPtr, _data, _size);
	moveRear(_size);

	return _size;
}

size_t BaseSerializer::pop(char* _data, size_t _size)
{
	memmove(_data, headPtr, _size);
	moveFront(_size);

	return _size;
}

size_t BaseSerializer::peek(char* _buffer, size_t _size)
{
	memmove(_buffer, headPtr, _size);

	return _size;
}



void BaseSerializer::clean()
{
	if (headPtr == bufferPtr)
		return;

	memmove(bufferPtr, headPtr, tailPtr - headPtr);
	tailPtr = bufferPtr + (tailPtr - headPtr);
	headPtr = bufferPtr;
}

void BaseSerializer::clear()
{
	headPtr = bufferPtr;
	tailPtr = bufferPtr;
}

char* BaseSerializer::resize(const size_t _size)
{
	char* tempPtr;
	
	if (useHeap)
		tempPtr = (char*)HeapAlloc(heap, 0, _size);
	else
		tempPtr = (char*)_aligned_malloc(_size, 64);

	clean();
	memmove(tempPtr, bufferPtr, tailPtr - bufferPtr);
	headPtr += tempPtr - bufferPtr;
	tailPtr += tempPtr - bufferPtr;
	bufferSize = _size;

	if (useHeap)
		HeapFree(heap, 0, bufferPtr);
	else
		_aligned_free((char*)bufferPtr);
		
	bufferPtr = tempPtr;

	return bufferPtr;
}

size_t BaseSerializer::moveFront(const size_t _size)
{
	headPtr += _size;
	return _size;
}
size_t BaseSerializer::moveRear(const size_t _size)
{
	tailPtr += _size;
	return _size;
}

char* BaseSerializer::getBufferPtr()
{
	return bufferPtr;
}
size_t BaseSerializer::getBufferSize()
{
	return bufferSize;
}

char* BaseSerializer::getHeadPtr()
{
	return headPtr;
}

char* BaseSerializer::getTailPtr()
{
	return tailPtr;
}



BaseSerializer& BaseSerializer::operator << (const char v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator << (const unsigned char v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator << (const wchar_t v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

//

BaseSerializer& BaseSerializer::operator << (const short v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator << (const unsigned short v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator << (const int v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator << (const unsigned int v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator << (const long v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator << (const unsigned long v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator << (const long long v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator << (const unsigned long long v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

//

BaseSerializer& BaseSerializer::operator << (const float v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator << (const double v) {

	memmove(tailPtr, &v, sizeof(v));
	moveRear(sizeof(v));

	return *this;
}
//


	//

BaseSerializer& BaseSerializer::operator >> (char& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator >> (unsigned char& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator >> (wchar_t& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

//

BaseSerializer& BaseSerializer::operator >> (short& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator >> (unsigned short& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator >> (int& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator >> (unsigned int& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator >> (long& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator >> (unsigned long& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator >> (long long& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
BaseSerializer& BaseSerializer::operator >> (unsigned long long& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

//

BaseSerializer& BaseSerializer::operator >> (float& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}

BaseSerializer& BaseSerializer::operator >> (double& v) {

	memmove(&v, headPtr, sizeof(v));
	moveFront(sizeof(v));

	return *this;
}
//

/*/ custom data type //

/*/



BaseSerializer& BaseSerializer::operator = (BaseSerializer& v) {

	memmove(bufferPtr, v.bufferPtr, bufferSize);
	headPtr = bufferPtr + (v.headPtr - v.bufferPtr);
	tailPtr = bufferPtr + (v.tailPtr - v.bufferPtr);

	return *this;
}

