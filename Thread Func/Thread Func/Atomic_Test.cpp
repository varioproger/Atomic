#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
class Test
{
public:
    int num;
    std::atomic<int> countet{0 };

    void Printf()
    {
        cout << "Test" << endl;
    }
    void UPDATE()
    {
        for (int i = 0; i < 1000; i++)
        {
            num++;
        }
    }
};
void worker(Test& counter)
{
    for (int i = 0; i < 1000; i++)
    {
        counter.num++;
    }

}


int main() 

{
    Test counter;
    std::atomic<Test*> test{ new Test() };
    //thread t1{ &Counter::loop, &c1 };


    std::vector<std::thread> workers;

    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker, ref(counter)));//클래스 내에 변수를 atomic으로 사용했을 경우는 가능하다.
    }


    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(&Test::UPDATE, &test));//atomic의 경우, 클래스내 함수를 쓰레드로 사용하지 못한다.
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }
    std::cout << "Counter 최종 값 : " << counter.num << std::endl;
}