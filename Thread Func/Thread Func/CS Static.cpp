#include<iostream>
#include<vector>
using namespace std;

class CSEX
{
	int count = 0;
public:
	CSEX()
	{
		cout << "»ý¼º" << endl;
	}
	~CSEX()
	{
		cout << "¼Ò¸ê" << endl;
	}
	void Enter()
	{
		cout << "Enter" << endl;
	}
	void Leave()
	{
		cout << "Leave" << endl;
	}
};


class Test_CS
{
private:
	static CSEX test_cs;
public:
	class CLock
	{
	public:
		CLock()
		{
			test_cs.Enter();
		}

		~CLock()
		{
			test_cs.Leave();
		}
	};
};
CSEX Test_CS::test_cs;

class Base : public Test_CS
{
public:

	void Lock_Print()
	{
		CLock clock;
		Print();
	}
	void No_Lock_Print()
	{
		Print();
	}
	virtual void Print() = 0;
};

class test2 : public Test_CS
{
public:
	void TestCount()
	{
		CLock clock;
		cout << "123" << endl;
	}
};

class First :public Base
{
public:

	virtual void Print()override
	{
		cout << "First" << endl;
	}
};

int main()
{

	First fir;
	fir.Lock_Print();

	test2 te;
	te.TestCount();

	return 0;
}
