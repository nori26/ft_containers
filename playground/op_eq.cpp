#include <iostream>

class A
{
  public:
	A() {std::cout << this << std::endl;}
	A(int) {std::cout << this << std::endl;}
	A &operator=(const A &a)
	{
		return *this;
	}
};

int main()
{
	A a;
	a = 1;
}
