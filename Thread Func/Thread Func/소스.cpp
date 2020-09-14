#include<iostream>
using namespace std;

enum class CLASS_STATE : unsigned __int64
{ //OB 는 이진수 표현
  //숫자 앞에 0 붙이면 8진수 
  //숫자 앞에 0X 붙이면 16진수
	NO_STATE = 0x0000000000000000,
	INIT_STATE = 0x0100000000000000,
	LOGIN_STATE = 0x0200000000000000,
	CHAT_STATE = 0x0300000000000000,
	LOBBY_STATE = 0x0400000000000000,
	PLAYER_STATE = 0x0500000000000000,
};

int main()
{
	unsigned __int64 test = (unsigned __int64)CLASS_STATE::INIT_STATE;
	cout << test << endl;
	return 0;
}