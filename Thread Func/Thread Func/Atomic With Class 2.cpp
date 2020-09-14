#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

class Vec 
{
public:
    atomic<bool> flag{false};
    atomic<int> number{ 0 };
    void Increa()
    {

        number++;
        flag = false;
    }
    bool check()
    {
        return flag;
    }
    void Set()
    {
        flag = true;
    }
};

atomic< Vec*> x;
void worker(atomic< Vec*>& counter)
{
	for (int i = 0; i < 1000; i++)
	{
        counter.load();
	}

}
int main()
{
    Vec a;
 
    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker, ref(x)));//클래스 내에 변수를 atomic으로 사용했을 경우는 가능하다.
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    cout << a.number<< endl;
    return 0;
}