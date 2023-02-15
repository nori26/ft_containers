#include <iostream>

class A
{
  public:
	A() {}
	A operator,(const A &a)
	{
		(void)a;
		std::cout << "commna" << std::endl;
		return a;
	}
	operator int() const
	{
		std::cout << "int" << std::endl;
		return 0;
	}
	operator void() const
	{
		std::cout << "void" << std::endl;
	}
	A operator++() const
	{
		return *this;
	}
	A operator()(A &a)
	{
		std::cout << "func" << std::endl;
		(void)a;
		return *this;
	}
};

void f(A a, A b)
{
	(void)a;
	(void)b;
}

int main()
{
	A a, b;
	f(a, b);
	std::cout << (int)a << std::endl;
	static_cast<int>(b);
	std::cout << "static" << std::endl;
	(int)b;
	(void)b;
	std::cout << (int)b << " cast" << std::endl;
	std::cout << int(b) << " construct" << std::endl;
	// for (int i = 0; i < 3; ++a, (const volatile void)++b)
	for (int i = 0; i < 3; ++a, (void)++b) {
		std::cout << i << std::endl;
		i++;
	}
}
