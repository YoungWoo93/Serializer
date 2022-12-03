#pragma once

#include <string>
#include <Windows.h>

#include "BaseSerializer.h"

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
};

