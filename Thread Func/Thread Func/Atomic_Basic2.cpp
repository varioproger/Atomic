#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
void if_weak(atomic<int>& num)
{
	int test1 = 3;// 이 값과 비교
	int test2 = 4;

	//num에 store된 값이랑 test1이랑 값이 같을경우 test2로 수정
	if (num.compare_exchange_weak(test1, test2))
	{
		cout << "test1 과 같음 Test2로 변경 " << test2 << "   " << num.load() << endl;
	}
	else
	{
		cout << "test1 과 다름 값 변경 안됨 " << test1 << "   " << num.load() << endl;
	}

}
void while_weak(atomic<int>&num)
{
	/*
	* Compares the contents of the value contained in obj with that of expected:
	- if true, it replaces the contained value with val.
	- if false, it replaces the value pointed by expected with the contained value .
	returns true if *expected compares equal to the contained value
	this weak version is allowed to fail spuriously by returning false even when *expected indeed compares equal to the value contained in obj. 
	This may be acceptable behavior for certain looping algorithms, and may lead to significantly better performance on some platforms.
	*/
	int test1 = 5;
	int test2 = 3;

	while (!num.compare_exchange_weak(test1, test2))//num에 store된 값이랑 test1이랑 test2랑 값이 다 같을 경우 같을 경우 
	{											   //둘중에 하나가 달라질때 까지 대기 하고 둘중하나라도 달라지면 while문 한번 추가적으로 더 돌고 빠져나온다.
												   //그리고 while문 조건을 !로 하면 while문 자체가 안돈다.
												   //test2의 값이 변경이 된 값으로 store가 된다.
		//cin >> test1;
		//옳바른 매개변수값이 들어왔을경우, !가 붙어야 while문 안으로 들어온다.
		//cin이 없을경우 한번 돌고 반복문 탈출한다.
	}

	//expected와 num 에 저장된 숫자가 일치를 하던 안하던 num 안에 저장된 값은 desire값으로 변경된다.
	//expected와 num 에 저장된 숫자가 일치 안될경우 expected 값을 num에 저장된 값으로 변경한다.
	//desire 값이 num 에 저장된 숫자가 일치 할경우 expected도 num에 저장된 값으로 변경된다.
	cout << test1 << endl;
	cout << test2 << endl;
	cout << num.load() << endl;
}

void if_strong(atomic<int>& num) 
{
	/*
	Unlike compare_exchange_weak, this strong version is required to always return true when expected indeed compares equal to the contained object,
	not allowing spurious failures. However, on certain machines, and for certain algorithms that check this in a loop,
	compare_exchange_weak may lead to significantly better performance.

	Compares the contents of the value contained in obj with the value pointed by expected:
	- if true, it replaces the contained value with val.
	- if false, it replaces the value pointed by expected with the contained value .
	*/

	int test1 = 3;// 이 값과 비교
	int test2 = 4;

	//num에 store된 값이랑 test1이랑 값이 같을경우 test2로 수정
	if (num.compare_exchange_strong(test1, test2))
	{
		cout << "test1 과 같음 Test2로 변경 " << test1 << "   " << num.load() << endl;
	}
	else
	{
		cout << "test1 과 다름 값 변경 안됨 " << test1 << "   " << num.load() << endl;
	}
}
void while_strong(atomic<int>& num)
{
	int test1 = 3;
	int test2 = 1;

	while (!num.compare_exchange_strong(test1, test2))//num에 store된 값이랑 test1이랑 test2랑 값이 다 같을 경우 같을 경우 
	{											   //둘중에 하나가 달라질때 까지 대기 하고 둘중하나라도 달라지면 while문 한번 추가적으로 더 돌고 빠져나온다.
												   //그리고 while문 조건을 !로 하면 while문 자체가 안돈다.
												   //test2의 값이 변경이 된 값으로 store가 된다.
		printf("while");
		cin >> test1;
		//옳바른 매개변수값이 들어왔을경우, !가 붙어야 while문 안으로 들어온다.
	}
	cout << num.load() << endl;
}
int main()
{
	atomic<int>num{5};


	//if_strong(num);
	//while_strong(num);
	//if_weak(num);
	while_weak(num);
}