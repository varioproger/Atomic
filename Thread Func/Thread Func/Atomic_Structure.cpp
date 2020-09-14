#include<iostream>
#include<atomic>
#include<vector>
#include<thread>
using namespace std;

struct MyStruct
{
	int num = 0;
};
void worker(atomic<MyStruct>& test,int i)
{
	MyStruct num_st = test.load();
	while (!test.compare_exchange_weak(num_st.num, i))
	{

	}
	for (int i = 0; i < 4; i++)
	{
		test.
	}
}
int main()
{
	atomic<MyStruct> test;
	// spawn 10 threads to fill the linked list:
	std::vector<std::thread> threads;
	for (int i = 0; i < 20; ++i)
	{
		threads.push_back(std::thread(worker, test,i));
	}

	for (auto& th : threads) th.join();
	return 0;
}
