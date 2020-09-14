#pragma warning(disable : 4996)
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

template<class T>
class slist {
    struct Node { T t;  std::shared_ptr<Node> next; };
    std::shared_ptr<Node> head;
public:
    class reference {
        std::shared_ptr<Node> p;
    public:
        reference(std::shared_ptr<Node> p_) :p{p_} {}
        T& operator*() { return p->t; }
        T* operator->() { return &p->t; }
    };
    auto find(T t) const 
    {
        auto p = atomic_load(&head);     
        while (p && p->t != t) {
            p = p-> next;      
        }
        //cout << "Show : " << p->t << endl;
        return reference(move(p));
    }
    auto show_list() const
    {
        auto p = atomic_load(&head);
        cout << "Show : " << p->t << endl;
        while (p->next !=nullptr) 
        {        
            p = p->next;      
            cout << "Show : " << p->t << endl;
        }   
    }
    void push_front(T t) {
        std::shared_ptr<Node> p = std::make_shared<Node>();
        p->t = t;
        p->next = atomic_load(&head);
        while (!atomic_compare_exchange_weak(&head, &p->next, p))
        {
        }
    }
    void pop_front() {
        auto p = atomic_load(&head);

        while (p && !atomic_compare_exchange_weak(&head,&p, p->next))
        { }
        /*/
        참조 횟수는 특정 객체에 새로운 shared_ptr이 추가될 때마다 1씩 증가하며, 수명이 다할 때마다 1씩 감소합니다.
        따라서 마지막 shared_ptr의 수명이 다하여, 참조 횟수가 0이 되면 delete 키워드를 사용하여 메모리를 자동으로 해제합니다.
        delete [] 따윈 사용해 주지 않는다.
        */
    }
    auto pop_list(T t) 
    {
        auto old = atomic_load(&head);
        auto pre = old;
        while (old && old->t != t)
        {       
            old = old->next;
            if (pre->next != old)
            {
                pre = pre->next;
            }
        }
        while (old && !atomic_compare_exchange_weak(&pre->next, &old, old->next))
        {
        }
        /*
        참조 횟수는 특정 객체에 새로운 shared_ptr이 추가될 때마다 1씩 증가하며, 수명이 다할 때마다 1씩 감소합니다.
        따라서 마지막 shared_ptr의 수명이 다하여, 참조 횟수가 0이 되면 delete 키워드를 사용하여 메모리를 자동으로 해제합니다.
        delete [] 따윈 사용해 주지 않는다.
        */   
    }
};
void append(slist<int>& val,int i)
{  
    val.push_front(i);

}
void Delete(slist<int>& val, int i)
{
    // Not Thread Safe if many threads insertingand deleting at the same time
    //if other thread doing only one work together it's fine
    for (int j = 0; j < 100; j++)
    {
        slist<int>::reference test = val.find(j);
        cout << "Show : " << (*test) << endl;
    }


    //Not Thread Safe if many threads inserting and deleting at the same time
    //if other thread doing only one work together it's fine
    //val.pop_front();


    //Not Thread Safe 
   //val.pop_list(i);

}
int main()
{
    slist<int> test;
    std::vector<std::thread> threads;
    std::vector<std::thread> threads2;
    for (int i = 0; i < 100; i++) threads.push_back(std::thread(append, ref(test),i));

    for (auto& th : threads) th.join();
    for (int i = 0; i < 30; i++) threads2.push_back(std::thread(Delete, ref(test), i));
    for (auto& th : threads2) th.join();

    cout << "Pop 이후" << endl;
    //test.show_list();
 /*   cout << "Show 이후" << endl;
	for (int i = 95; i < 100; i++)
	{
		test.find(i);
	}*/





    return 0;
}