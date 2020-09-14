#include<iostream>
#include<vector>
using namespace std;

enum class Class_State
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH
};

class CSEX
{
public:
	int count = 0;
	CSEX()
	{
		//cout << "생성" << endl;
		cout << (&count) << endl;
	}
	~CSEX()
	{
		//cout << "소멸" << endl;
		cout << (&count) << endl;
	}
	static void Enter()
	{
		//cout << "Enter" << endl;
	}
	static void Leave()
	{
		//cout << "Leave" << endl;
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
	void Lock_Print(int type)//이부분 가변길이로 변경해야함.
	{
		CLock clock;
		cout << (&count) << endl;
		Print(type);
	}
	void No_Lock_Print(int type)//이부분 가변길이로 변경해야함.
	{
		Print(type);
	}
	virtual void Print(int type) = 0;
	virtual void Create() = 0;
	virtual void Destroy() = 0;
	virtual void Begin() = 0;
};


class First :public Base
{
public:
	virtual void Create()override
	{
		cout << "First_Created" << endl;
	}
	virtual void Destroy()override
	{
		cout << "First_Destroyed" << endl;
	}
	virtual void Begin()override
	{
		cout << "First_Began" << endl;
	}
	virtual void Print(int type)override
	{
		switch (type)
		{
		case 1:
			cout << "First" << endl;
			break;
		case 2:
			cout << "First, First" << endl;
			break;
		case 3:
			cout << "First, First, First" << endl;
			break;
		}
	
	}
};
class Second :public Base
{
public:
	virtual void Create()override
	{
		cout << "Second_Created" << endl;
	}
	virtual void Destroy()override
	{
		cout << "Second_Destroyed" << endl;
	}
	virtual void Begin()override
	{
		cout << "Second_Began" << endl;
	}
	virtual void Print(int type)override
	{
		switch (type)
		{
		case 1:
			cout << "Second" << endl;
			break;
		case 2:
			cout << "Second, Second" << endl;
			break;
		case 3:
			cout << "Second, Second, Second" << endl;
			break;
		}
	
	}
};
class Third :public Base
{
public:
	virtual void Create()override
	{
		cout << "Third_Created" << endl;
	}
	virtual void Destroy()override
	{
		cout << "Third_Destroyed" << endl;
	}
	virtual void Begin()override
	{
		cout << "Third_Began" << endl;
	}
	virtual void Print(int type)override
	{
		switch (type)
		{
		case 1:
			cout << "Third" << endl;
			break;
		case 2:
			cout << "Third, Third" << endl;
			break;
		case 3:
			cout << "Third, Third, Third" << endl;
			break;
		}	
	}
};
class Fourth :public Base
{
public:
	virtual void Create()override
	{
		cout << "Fourth_Created" << endl;
	}
	virtual void Destroy()override
	{
		cout << "Fourth_Destroyed" << endl;
	}
	virtual void Begin()override
	{
		cout << "Fourth_Began" << endl;
	}
	virtual void Print(int type)override
	{
		switch (type)
		{
		case 1:
			cout << "Fourth" << endl;
			break;
		case 2:
			cout << "Fourth, Fourth" << endl;
			break;
		case 3:
			cout << "Fourth, Fourth, Fourth" << endl;
			break;
		}

	}
};

class Base_Manager//접근.
{
public:
	Base_Manager()
	{
		AddBind(new First());
		AddBind(new Second());
		AddBind(new Third());
		AddBind(new Fourth());
	}
	void AddBind(Base* bind) noexcept
	{
		binds.push_back(bind);
	}
	void Create()
	{
		for (auto& b : binds)
		{

			b->Create();
		}
	}
	void Destroyed()
	{
		for (auto& b : binds)
		{

			b->Destroy();
		}
	}
	void Bein()
	{
		for (auto& b : binds)
		{

			b->Begin();
		}
	}
	void Lock_Print(int type)
	{

		for (auto& b : binds)
		{

			b->Lock_Print(type);
		}
	}
	void Lock_Get_Instatnce(Class_State test, int type)
	{
		switch (test)
		{
		case Class_State::FIRST:
			binds[(int)Class_State::FIRST]->Lock_Print(type);
			break;
		case Class_State::SECOND:
			binds[(int)Class_State::SECOND]->Lock_Print(type);
			break;
		case Class_State::THIRD:
			binds[(int)Class_State::THIRD]->Lock_Print(type);
			break;
		case Class_State::FOURTH:
			binds[(int)Class_State::FOURTH]->Lock_Print(type);
			break;
		default:
			break;
		}
	}
	void No_Lock_Print(int type)
	{
		for (auto& b : binds)
		{
			b->No_Lock_Print(type);
		}
	}
	void No_Lock_Get_Instatnce(Base* bind, int type)
	{
		for (auto& b : binds)
		{
			if (b == bind)
			{
				bind->No_Lock_Print(type);
			}
		}
	}
private:
	std::vector<Base*> binds;
};

int main()
{

	Base_Manager test;

	test.Create();
	test.Bein();

	test.Lock_Get_Instatnce(Class_State::SECOND, 3);
	test.Lock_Get_Instatnce(Class_State::SECOND, 3);
	test.Lock_Get_Instatnce(Class_State::SECOND, 3);
	test.Lock_Get_Instatnce(Class_State::FIRST, 3);
	test.Lock_Get_Instatnce(Class_State::THIRD, 3);
	test.Lock_Get_Instatnce(Class_State::FIRST, 3);
	test.Destroyed();
	return 0;
}
