#pragma once

#include <string>
#include <Windows.h>
#include <stdexcept>

#include "BaseSerializer.h"
#include "Serializer.h"

class serializer;

class packetSerializer : public BaseSerializer
{
public:
	packetSerializer() : referenceCounter(0) {	// c++ allocator �� �̿��� 64����Ʈ (ĳ�ö���) ��迡 ������ ¥����
	}																					//    aligned alloc ���� ����
	packetSerializer(const size_t _size)
		:BaseSerializer(_size), referenceCounter(0) {
	}
	packetSerializer(HANDLE heap)
		:BaseSerializer(heap), referenceCounter(0) {
	}
	packetSerializer(HANDLE heap, const size_t _size)
		:BaseSerializer(heap, _size), referenceCounter(0) {
	}
	packetSerializer(const packetSerializer& s)
		:BaseSerializer(s), referenceCounter(0) {
	}

	size_t push(const char* _data, size_t _size);
	size_t pop(char* _data, size_t _size);
	size_t peek(char* _buffer, size_t _size);


	int moveFront(const int _size);
	int moveRear(const int _size);

	int incReferenceCounter(int size = 1);
	int decReferenceCounter(int size = 1);

protected:
	volatile LONG referenceCounter;

public:


	// basic data type //

	//serializer& operator << (bool v);  // 1��Ʈ ó���� ���� byte ��� �Ѽ��� �� �����ε� �Է��̵Ǹ� ������ �̴°� �� ��������?

	packetSerializer& operator << (const char v);
	packetSerializer& operator << (const unsigned char v);
	packetSerializer& operator << (const wchar_t v);

	packetSerializer& operator << (const short v);
	packetSerializer& operator << (const unsigned short v);
	packetSerializer& operator << (const int v);
	packetSerializer& operator << (const unsigned int v);
	packetSerializer& operator << (const long v);
	packetSerializer& operator << (const unsigned long v);
	packetSerializer& operator << (const long long v);
	packetSerializer& operator << (const unsigned long long v);

	packetSerializer& operator << (const float v);
	packetSerializer& operator << (const double v);



	packetSerializer& operator >> (char& v);
	packetSerializer& operator >> (unsigned char& v);
	packetSerializer& operator >> (wchar_t& v);

	packetSerializer& operator >> (short& v);
	packetSerializer& operator >> (unsigned short& v);
	packetSerializer& operator >> (int& v);
	packetSerializer& operator >> (unsigned int& v);
	packetSerializer& operator >> (long& v);
	packetSerializer& operator >> (unsigned long& v);
	packetSerializer& operator >> (long long& v);
	packetSerializer& operator >> (unsigned long long& v);

	packetSerializer& operator >> (float& v);
	packetSerializer& operator >> (double& v);
	//



// custom data type //

//
	virtual packetSerializer& operator = (packetSerializer& v);
	virtual packetSerializer& operator = (serializer& v);

	friend class serializer;
};
