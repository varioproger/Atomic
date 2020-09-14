#include<iostream>
#include<vector>
using namespace std;

class Base
{
public:
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
	void test_Print()
	{
		for (auto& b : binds)
		{
			b->Print();
		}
	}
	void Lock_Get_Instatnce(Base* bind)
	{
		for (auto& b : binds)
		{
			if (b == bind)
			{
				bind->Print();
			}
		}
	}
private:
	std::vector<Base*> binds;
};
int main()
{
	Base_Manager test;
	First fir;
	Second sec;
	Third thr;
	Fourth fort;
	test.AddBind(&fir);
	test.AddBind(&sec);
	test.AddBind(&thr);
	test.AddBind(&fort);
	test.test_Print();
	test.Lock_Get_Instatnce(&thr);
	test.Lock_Get_Instatnce(&fort);
	test.Lock_Get_Instatnce(&fir);
	return 0;
}