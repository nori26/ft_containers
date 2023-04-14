#include <iostream>

class A
{
  public:
	operator int()
	{
		return 2;
	}
};

class Child : public A
{};

template <typename T>
struct B
{
	B()
	{
		std::cout << "primary" << std::endl;
	}
};

template <>
struct B<long>
{
	B()
	{
		std::cout << "partial" << std::endl;
	}
};

template <typename T>
struct C
{
	C()
	{
		std::cout << "primary" << std::endl;
	}
};

template <>
struct C<Child>
{
	C()
	{
		std::cout << "partial" << std::endl;
	}
};

template <typename T>
void f(T) {std::cout << "aa" << std::endl;}

template <>
void f(long) {std::cout << "bb" << std::endl;}

int main()
{
	B<A> b;
	B<int> b2;
	B<signed long> b3;
	C<A> c;
	f(1);
}
