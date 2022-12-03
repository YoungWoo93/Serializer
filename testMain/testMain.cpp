
#ifdef _DEBUG
#pragma comment(lib, "RingBufferD")
#pragma comment(lib, "SerializerD")
#else
#pragma comment(lib, "RingBuffer")
#pragma comment(lib, "Serializer")
#endif

#include "../Serializer/Serializer.h"
#include "RingBuffer/RingBuffer/RingBuffer.h"


#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;



void loopTestOperator()
{
	serializer s(32);
	queue<int> q;

	char cc = '1';
	short ss = 12850;
	int ii = 875836468;
	long long int ll = 4051049678932293688;

	for (int i = 0; i < 1000; i++)
	{
		cout << " [ " << i << "] ";
		switch (rand() % 4)
		{
		case 0:
			s << cc;
			cout << "<<<< " << 1 << endl;
			q.push(0);
			break;

		case 1:
			s << cc << ss;
			cout << "<<<< " << 1 << " << " << 22 << endl;
			q.push(0);
			q.push(1);
			break;

		case 2:
			s << cc << ss << ii;
			cout << "<<<< " << 1 << " << " << 22 << " << " << 4444 << endl;
			q.push(0);
			q.push(1);
			q.push(2);
			break;

		case 3:
			s << cc << ss << ii << ll;
			cout << "<<<< " << 1 << " << " << 22 << " << " << 4444 << " << " << 88888888 << endl;
			q.push(0);
			q.push(1);
			q.push(2);
			q.push(3);
			break;
		}

		s.printbuffer();

		int cycle = q.size() * ((float)(rand() % 11) / 10);

		while (cycle--)
		{
			cout << " [ " << i << "] ";
			switch (q.front())
			{
			case 0:
				char c1;
				s >> c1;

				if (c1 == cc)
					cout << ">>>> " << 1 << endl;
				else
					cout << "ERROR" << endl;

				break;

			case 1:
				short S;
				s >> S;

				if (S == ss)
					cout << ">>>> " << 22 << endl;
				else
					cout << "ERROR" << endl;

				break;

			case 2:
				int I;
				s >> I;

				if (I == ii)
					cout << ">>>> " << 4444 << endl;
				else
					cout << "ERROR" << endl;

				break;

			case 3:
				int64_t LL;
				s >> LL;

				if (LL == ll)
					cout << ">>>> " << 88888888 << endl;
				else
					cout << "ERROR" << endl;

				break;
			}

			q.pop();
		}

		s.printbuffer();
	}
}

void loopTestFunction()
{
	serializer s(32);
	queue<int> q;

	char cc = '1';
	short ss = 12850;
	int ii = 875836468;
	long long int ll = 4051049678932293688;

	for (int i = 0; i < 1000; i++)
	{
		cout << " [ " << i << "] ";
		switch (rand() % 4)
		{
		case 0:
			s.push(&cc, sizeof(cc));
			cout << "<<<< " << 1 << endl;
			q.push(0);
			break;

		case 1:
			s.push((char*)&ss, sizeof(ss));
			cout << "<<<< " << 22 << endl;
			q.push(1);
			break;

		case 2:
			s.push((char*)&ii, sizeof(ii));
			cout << "<<<< " << 4444 << endl;
			q.push(2);
			break;

		case 3:
			s.push((char*)&ll, sizeof(ll));
			cout << "<<<< " << 88888888 << endl;
			q.push(3);
			break;
		}

		s.printbuffer();

		int cycle = q.size() * ((float)(rand() % 11) / 10);

		while (cycle--)
		{
			cout << " [ " << i << "] ";
			switch (q.front())
			{
			case 0:
				char c1;
				s.pop(&c1, sizeof(c1));

				if (c1 == cc)
					cout << ">>>> " << 1 << endl;
				else
					cout << "ERROR" << endl;

				break;

			case 1:
				short S;
				s.pop((char*)&S, sizeof(S));

				if (S == ss)
					cout << ">>>> " << 22 << endl;
				else
					cout << "ERROR" << endl;

				break;

			case 2:
				int I;
				s.pop((char*)&I, sizeof(I));

				if (I == ii)
					cout << ">>>> " << 4444 << endl;
				else
					cout << "ERROR" << endl;

				break;

			case 3:
				int64_t LL;
				s.pop((char*)&LL, sizeof(LL));

				if (LL == ll)
					cout << ">>>> " << 88888888 << endl;
				else
					cout << "ERROR" << endl;

				break;
			}

			q.pop();
		}

		s.printbuffer();
	}
}

void RingBufferToSerializerTest()
{
	ringBuffer rb(16);
	list<int> lst;
	serializer s;
	int count = 0;

	while (true)
	{
		for (int i = 0; i < 4; i++) {
			int n = 1 << (rand() % 3);
			if (rb.freeSize() < n)
				break;

			lst.push_back(n);

			switch (lst.back())
			{
			case 1: {

				char c[1];

				c[0] = '1';

				rb.push(c, 1);
				break;
			}
			case 2: {

				char c[2];

				c[0] = '2';
				c[1] = '2';

				rb.push(c, 2);
				break;
			}
			case 4: {

				char c[4];

				c[0] = '4';
				c[1] = '4';
				c[2] = '4';
				c[3] = '4';

				rb.push(c, 4);
				break;
			}

			default:
				break;
			}
			rb.printbuffer();
		}

		/*/
		for (auto it : lst) 
		{
			switch (it)
			{
			case 1: {

				char c[1];

				c[0] = '1';

				rb.push(c, 1);
				break;
			}
			case 2: {

				char c[2];

				c[0] = '2';
				c[1] = '2';

				rb.push(c, 2);
				break;
			}
			case 4: {

				char c[4];

				c[0] = '4';
				c[1] = '4';
				c[2] = '4';
				c[3] = '4';

				rb.push(c, 4);
				break;
			}

			default:
				break;
			}
			rb.printbuffer();
		}
		/*/

		if (count == 8)
			cout << "break";
		cout << "\t\t" << rb.size() << "\t" << rb.DirectDequeueSize() << endl;
		s.push(rb.head(), rb.DirectDequeueSize());
		rb.MoveFront(rb.DirectDequeueSize());
		cout << ">>>> RB" << endl;
		rb.printbuffer();
		cout << endl;

		cout << ">>>> SR" << endl;
		s.printbuffer();
		cout << endl;
		while (!lst.empty() && lst.front() <= s.size()) {
			

			volatile int size = lst.front();
			count++;
			switch (size)
			{
			case 1: {

				char c;
				s >> c;

				cout << c << endl;
				if (c != '1') {

					cout << "?? " << count << endl;
				}
				break;
			}
			case 2:
			{
				short cs;
				char c[3];
				s >> cs;
				memcpy_s(c, 2, &cs, 2);
				c[2] = '\0';
				cout << c << endl;

				if (c[0] != '2' || c[1] != '2') {

					cout << "?? " << count << endl;
				}
				break;
			}
			case 4: {
				int cs;
				char c[5];
				s >> cs;
				memcpy_s(c, 4, &cs, 4);
				c[4] = '\0';
				cout << c << endl;
				if (c[0] != '4' || c[1] != '4' || c[2] != '4' || c[3] != '4') {
					cout << "?? " << count << endl;
				}
				break;
			}
			}
			
			lst.pop_front();
		}
	}
}

void serializer_packetSerializer_test()
{
	packetSerializer p(32);
	serializer s16(16);
	serializer s32(32);
	serializer s64(64);

	p << (int)1234;
	p.printbuffer();

	s16 = p;
	s16.printbuffer();
	s32 = p;
	s32.printbuffer();
	s64 = p;
	s64.printbuffer();

	s16 << (int)4567;
	s16.printbuffer();
	s32 << (int)4567;
	s32.printbuffer();
	s64 << (int)4567;
	s64.printbuffer();
	
	p = s16;
	p.printbuffer();
	p = s32;
	p.printbuffer();
	p = s64;
	p.printbuffer();

	s64 << (int)1 << (int)1 << (int)1 << (int)1 << (int)1 << (int)1 << (int)1;
	s64.printbuffer();

	p = s64;
	p.printbuffer();

}

void main()
{
	serializer_packetSerializer_test();

	//RingBufferToSerializerTest();

	//loopTestOperator();
	//loopTestFunction();
}
