#include <iostream>

using namespace std;

class fruit
{
public:
	void apple()
	{
		cout << "apple" << endl;
	}
	void berry()
	{
		cout << "berry" << endl;
	}
};

int main()
{
	fruit x, * y;
	void (fruit:: * f)(void);

	y = new fruit;
	f = &fruit::apple;
	(x.*f)();

	f = &fruit::berry;
	(y->*f)();

	delete y;
}
