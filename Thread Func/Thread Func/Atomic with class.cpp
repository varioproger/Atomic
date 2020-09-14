#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
//실패
class Test
{
public:
    int num=0;
    std::atomic<int> countet{ 0 };

    void Printf()
    {
        cout << "Test" << num << endl;
    }
    void UPDATE()
    {
        for (int i = 0; i < 1000; i++)
        {
            num++;
        }
    }
};

class atomic_test
{
public:

    shared_ptr<Test> at1;
    atomic_test()
    {
        shared_ptr<Test> t2 = make_shared<Test>();
        atomic_store(&at1, t2);
    }

    void test()
    {
        shared_ptr<Test> t2 = atomic_load(&at1);
        t2.get()->UPDATE();
    }


    ~atomic_test() = default;
};

void worker(atomic_test& counter)
{
    counter.test();
}


int main()
{
    Test counter;
    std::atomic<Test*> test{ new Test() };
    //thread t1{ &Counter::loop, &c1 };

    atomic_test at1;

    std::vector<std::thread> workers;

    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker, ref(at1)));//클래스 내에 변수를 atomic으로 사용했을 경우는 가능하다.
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }
    std::cout << "Counter 최종 값 : " << at1 .at1.get()->num<< std::endl;
}