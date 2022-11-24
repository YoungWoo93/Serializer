#pragma once
#include <string>
#include <Windows.h>

class BaseSerializer {
public:
	BaseSerializer()
		:bufferPtr((char*)_aligned_malloc(64, 64)), bufferSize(64), headPtr(bufferPtr), tailPtr(bufferPtr) {	// c++ allocator �� �̿��� 64����Ʈ (ĳ�ö���) ��迡 ������ ¥����
	}																					//    aligned alloc ���� ����
	BaseSerializer(const size_t _size)
		:bufferPtr((char*)_aligned_malloc(_size, 64)), bufferSize(_size), headPtr(bufferPtr), tailPtr(bufferPtr) {
	}
	BaseSerializer(const BaseSerializer& s)
		:bufferPtr((char*)_aligned_malloc(s.bufferSize, 64))
		, bufferSize(s.bufferSize)
		, headPtr(bufferPtr + (s.headPtr - s.bufferPtr))
		, tailPtr(bufferPtr + (s.tailPtr - s.bufferPtr)) {
		memmove(headPtr, s.headPtr, s.tailPtr - s.headPtr);
	}

	virtual ~BaseSerializer() {
		//clear();
		_aligned_free(bufferPtr);
		//delete[] bufferPtr;
	}



	const size_t size() {
		return tailPtr - headPtr;
	}

	const size_t useableSize() {
		return bufferSize - (tailPtr - bufferPtr);
	}

	const size_t maxSize() {
		return bufferSize;
	}

	const size_t usedSize() {
		return headPtr - bufferPtr;
	}



	size_t push(const char* _data, size_t _size);
	size_t pop(char* _data, size_t _size);
	size_t peek(char* _buffer, size_t _size);

	void clean();
	void clear();
	char* resize(const size_t _size);

	size_t moveFront(const size_t _size);
	size_t moveRear(const size_t _size);

	char* getBufferPtr();
	size_t getBufferSize();

	char* getHeadPtr();
	char* getTailPtr();



protected:


public:

	/*/ basic data type /*/

	//BaseSerializer& operator << (bool v);  // 1��Ʈ ó���� ���� byte ��� �Ѽ��� �� �����ε� �Է��̵Ǹ� ������ �̴°� �� ��������?

	BaseSerializer& operator << (const char v);
	BaseSerializer& operator << (const unsigned char v);
	BaseSerializer& operator << (const wchar_t v);

	BaseSerializer& operator << (const short v);
	BaseSerializer& operator << (const unsigned short v);
	BaseSerializer& operator << (const int v);
	BaseSerializer& operator << (const unsigned int v);
	BaseSerializer& operator << (const long v);
	BaseSerializer& operator << (const unsigned long v);
	BaseSerializer& operator << (const long long v);
	BaseSerializer& operator << (const unsigned long long v);

	BaseSerializer& operator << (const float v);
	BaseSerializer& operator << (const double v);



	BaseSerializer& operator >> (char& v);
	BaseSerializer& operator >> (unsigned char& v);
	BaseSerializer& operator >> (wchar_t& v);

	BaseSerializer& operator >> (short& v);
	BaseSerializer& operator >> (unsigned short& v);
	BaseSerializer& operator >> (int& v);
	BaseSerializer& operator >> (unsigned int& v);
	BaseSerializer& operator >> (long& v);
	BaseSerializer& operator >> (unsigned long& v);
	BaseSerializer& operator >> (long long& v);
	BaseSerializer& operator >> (unsigned long long& v);

	BaseSerializer& operator >> (float& v);
	BaseSerializer& operator >> (double& v);
	//



/*/ custom data type //

/*/



	virtual BaseSerializer& operator = (BaseSerializer& v);


	/// <summary>
	/// �׽�Ʈ�� �Լ�
	/// 
	virtual void printbuffer()
	{
		for (size_t i = 0; i < bufferSize; i++)
			printf("==");
		printf("\n");

		for (size_t i = 0; i < bufferSize; i++)
		{
			if (bufferPtr + i == headPtr)
				printf(" ->");
			else if (bufferPtr + i == tailPtr)
				printf("-|");
			else
				printf("  ");
		}
		printf("\n");

		for (size_t i = 0; i < bufferSize; i++)
			printf(" %c", *(bufferPtr + i));
		printf("\n");

		for (size_t i = 0; i < bufferSize; i++)
			printf("==");
		printf("\n");
	}
	/// </summary>

protected:
	char* bufferPtr;
	size_t bufferSize;

	char* headPtr;
	char* tailPtr;
};