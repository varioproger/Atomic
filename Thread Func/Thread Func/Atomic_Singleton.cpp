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
		nvalue++;
	}
	void SetValue(int _value) { nvalue = _value; }
	int GetValue() { return nvalue; }
};

void Increase(CObject& test)
{
	test.GetSingleton()->Test_Increase();
}
int main()
{
	CObject test;

	CObject::GetSingleton()->SetValue(10);

	// spawn 10 threads to fill the linked list:
	//std::vector<std::thread> threads;
	//for (int i = 0; i < 20; ++i) threads.push_back(std::thread(Increase, ref()));
	//for (auto& th : threads) th.join();

	cout << test.GetValue() << endl;
	CObject::Release();
	return 0;
}