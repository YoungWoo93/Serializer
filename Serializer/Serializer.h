#pragma once

#include <string>
#include <Windows.h>
#include <stdexcept>

#include "BaseSerializer.h"

class packetSerializer;

class serializer : public BaseSerializer
{
public:
	serializer() {	// c++ allocator 를 이용해 64바이트 (캐시라인) 경계에 서도록 짜보자
	}																					//    aligned alloc 구현 이후
	serializer(const size_t _size)
		:BaseSerializer(_size) {
	}
	serializer(HANDLE heap)
		:BaseSerializer(heap) {
	}
	serializer(HANDLE heap, const size_t _size)
		:BaseSerializer(heap, _size) {
	}
	serializer(const serializer& s)
		:BaseSerializer(s) {
	}

	size_t push(const char* _data, size_t _size);
	size_t pop(char* _data, size_t _size);
	size_t peek(char* _buffer, size_t _size);


	size_t moveFront(const size_t _size);
	size_t moveRear(const size_t _size);

protected:


public:

	/*/ basic data type /*/

	//serializer& operator << (bool v);  // 1비트 처리로 인한 byte 경계 훼손이 더 문제인듯 입력이되면 에러를 뽑는게 더 나으려나?

	serializer& operator << (const char v);
	serializer& operator << (const unsigned char v);
	serializer& operator << (const wchar_t v);

	serializer& operator << (const short v);
	serializer& operator << (const unsigned short v);
	serializer& operator << (const int v);
	serializer& operator << (const unsigned int v);
	serializer& operator << (const long v);
	serializer& operator << (const unsigned long v);
	serializer& operator << (const long long v);
	serializer& operator << (const unsigned long long v);

	serializer& operator << (const float v);
	serializer& operator << (const double v);



	serializer& operator >> (char& v);
	serializer& operator >> (unsigned char& v);
	serializer& operator >> (wchar_t& v);

	serializer& operator >> (short& v);
	serializer& operator >> (unsigned short& v);
	serializer& operator >> (int& v);
	serializer& operator >> (unsigned int& v);
	serializer& operator >> (long& v);
	serializer& operator >> (unsigned long& v);
	serializer& operator >> (long long& v);
	serializer& operator >> (unsigned long long& v);

	serializer& operator >> (float& v);
	serializer& operator >> (double& v);
	//



/*/ custom data type //

/*/

	virtual serializer& operator = (serializer& v);
	virtual serializer& operator = (packetSerializer& v);

	friend class packetSerializer;
};












class packetSerializer : public BaseSerializer
{
public:
	packetSerializer() {	// c++ allocator 를 이용해 64바이트 (캐시라인) 경계에 서도록 짜보자
	}																					//    aligned alloc 구현 이후
	packetSerializer(const size_t _size)
		:BaseSerializer(_size) {
	}
	packetSerializer(HANDLE heap)
		:BaseSerializer(heap) {
	}
	packetSerializer(HANDLE heap, const size_t _size)
		:BaseSerializer(heap, _size) {
	}
	packetSerializer(const packetSerializer& s)
		:BaseSerializer(s) {
	}

	size_t push(const char* _data, size_t _size);
	size_t pop(char* _data, size_t _size);
	size_t peek(char* _buffer, size_t _size);


	int moveFront(const int _size);
	int moveRear(const int _size);

protected:


public:


	// basic data type //

	//serializer& operator << (bool v);  // 1비트 처리로 인한 byte 경계 훼손이 더 문제인듯 입력이되면 에러를 뽑는게 더 나으려나?

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

