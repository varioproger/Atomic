#include<iostream>
#include<atomic>
#include <thread>
#include <vector>
using namespace std;

template <typename T>
class MyData
{
private:
    atomic<T> m_data;
public:
    void SetData();
    T GetData();
};
template <typename T>
void MyData<T>::SetData()
{
    m_data +=1;
}
template <typename T>
T MyData<T>::GetData()
{
    return m_data;
}
void worker(MyData<int>& counter)
{
    for (int i = 0; i < 10000; i++) {
        counter.SetData();
    }
}
void main()
{
    MyData<int> int_temp;
    int_temp.SetData();
    // int_temp 객체가 가지고 있는 5가 출력된다.
    cout << int_temp.GetData() << endl;

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker, ref(int_temp)));
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }
    cout << int_temp.GetData() << endl;
}