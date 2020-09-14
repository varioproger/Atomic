#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include<mutex>
using namespace std;

template<typename T>
class CSingleton
{
private:
	static atomic< T*> _Singleton;
public:
	CSingleton() {}
	virtual ~CSingleton() {}
	static T* GetSingleton()
	{
		if (NULL == _Singleton)
		{
			_Singleton = new T;
		}
		return _Singleton;
	}

	static void Release()
	{
		delete _Singleton;
		_Singleton = NULL;
	}
};
template<typename T> atomic<T*> CSingleton<T>::_Singleton{ nullptr };

class CObject : public CSingleton<CObject>
{
	int nvalue;
public:
	CObject() : nvalue(10) {}
	void Test_Increase()
	{
		for (int i = 0; i < 1000; i++)
		{
			nvalue++;
		}
	}
	void SetValue(int _value) { nvalue = _value; }
	int GetValue() { return nvalue; }
};

class CObject2 : public CSingleton<CObject>
{
	int nvalue;
public:
	CObject2() : nvalue(10) {}
	void Test_Increase()
	{
		nvalue++;
	}
	void SetValue(int _value) { nvalue = _value; }
	int GetValue() { return nvalue; }
};

void Increase(CSingleton<CObject>& test)
{
	test.GetSingleton()->Test_Increase();
}
int main()
{
	CSingleton<CObject> test;
	std::vector<std::thread> threads;
	for (int i = 0; i < 4; ++i) threads.push_back(std::thread(Increase, ref(test)));
	for (auto& th : threads) th.join();

	cout << test.GetSingleton()->GetValue() << endl;

	return 0;
}