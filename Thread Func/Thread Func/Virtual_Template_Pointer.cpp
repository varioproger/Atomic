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
	static void Enter()
	{
		cout << "Enter" << endl;
	}
	static void Leave()
	{
		cout << "Leave" << endl;
	}
};

class Test_CS : public CSEX
{
public:
	class CLock
	{
	public:
		CLock()
		{
			Enter();
		}

		~CLock()
		{
			Leave();
		}
	};
};

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


class First :public Base
{
public:

	virtual void Print()override
	{
		cout << "First" << endl;
	}
};
class Second :public Base
{
public:
	virtual void Print()override
	{
		cout << "Second" << endl;
	}
};
class Third :public Base
{
public:
	virtual void Print()override
	{
		cout << "Third" << endl;
	}
};
class Fourth :public Base
{
public:
	virtual void Print()override
	{
		cout << "Fourth" << endl;
	}
};

class Base_Manager
{
public:
	void AddBind(Base* bind) noexcept
	{
		binds.push_back(bind);
	}
	void Lock_Print()
	{

		for (auto& b : binds)
		{

			b->Lock_Print();
		}
	}


	void Lock_Get_Instatnce(Base* bind)
	{
		for (auto& b : binds)
		{
			if (b == bind)
			{
				bind->Lock_Print();
			}
		}
	}
	void No_Lock_Print()
	{
		for (auto& b : binds)
		{
			b->No_Lock_Print();
		}
	}
	void No_Lock_Get_Instatnce(Base* bind)
	{
		for (auto& b : binds)
		{
			if (b == bind)
			{
				bind->No_Lock_Print();
			}
		}
	}
private:
	std::vector<Base*> binds;
};

template<typename T>
class Function_Pointer
{
public:

	void Test_Call(T _test, void (T ::* _fcnPtr)(void))
	{
		(_test.*_fcnPtr)();
	}
};

int main()
{
	void (First :: * fcnPtr)(void);

	Base_Manager test;
	First fir;
	//Second sec;
	//Third thr;
	//Fourth fort;

	Function_Pointer<First> first_test;
	first_test.Test_Call(fir, &First::Print);
	return 0;
}

/*
	//Function_Pointer<First> first_test;
	//first_test.fcnPtr = &First::Print;
	//first_test.test = fir;
	//first_test.Test_Call(fir, &First::Print);
*/