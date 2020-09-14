#include <cstdio>
#include<iostream>
#include <thread>

using namespace std;

int main() {
	thread t1([](int id, int length)
		{
			std::thread::id this_id = std::this_thread::get_id();
			for (int i = 1; i <= length; i++)
			{
				std::cout << "thread " << this_id << endl;
				printf("counter[%d] : %d\n", id, i);

			}
		}, 1, 7);

	t1.join();

	return 0;
}