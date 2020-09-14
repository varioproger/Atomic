#include <cstdio>
#include <thread>

using namespace std;


class Counter {
public:
    Counter(int id, int length) {
        mId = id;
        mLength = length;
    }

    void operator()() const {
        for (int i = 1; i <= mLength; i++) {
            printf("counter[%d] : %d\n", mId, i);
        }
    }

private:
    int mId;
    int mLength;
};
void t1(Counter test)
{
    test();
}
void t2(Counter test)
{
    test();
}
int main() {
    // #1
    thread t1{ Counter(1, 5) };

    // #2
    Counter c2(2, 7);
    thread t2(c2);

    // #3
    thread t3(Counter(3, 8));//operator 같이 실행
    /*
     3번째 방식은 특수한 경우(예를 들어 인자로 들어가는 클래스의 생성자에 파라메터가 없는 경우)에 컴파일 에러가 뜰 수 있기 때문에 
     가급적 첫 번째 방식을 사용하는 편이 더 낫습니다.
    */
    t1.join();
    t2.join();
    t3.join();

    return 0;
}