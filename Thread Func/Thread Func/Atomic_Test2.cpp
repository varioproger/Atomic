#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

enum class Test
{
	NONE,
	INT,
	STOP
};
atomic< Test> test{ Test::NONE };

void plusInt(Test _test,int& num)
{
	Test en_test = test.load();
	while(!test.compare_exchange_weak(en_test, _test))
	{
		num++;
		cout << num << endl;
		if (test.load() == Test::STOP)
		{
			break;
		}
	}
	num++;
	cout << num << endl;
}
void Input(Test& _test)
{
	int choice = 0;
	cin >> choice;
	switch (Test(choice))
	{
	case Test::NONE:
		test.store(Test::NONE);
		break;
	case Test::INT:
		test.store(Test::INT);
		break;
	case Test::STOP:
		test.store(Test::STOP);
		break;
	}
}

int main()
{
	int num = 0;
	Test t1 = Test::INT;
	// spawn 10 threads to fill the linked list:
	std::vector<std::thread> threads;
	threads.push_back(std::thread(Input, ref(t1)));
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(std::thread(plusInt, t1, ref(num)));
	}

	for (auto& th : threads) th.join();

	return 0;
}