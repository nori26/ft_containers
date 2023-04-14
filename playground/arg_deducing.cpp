#include <iostream>
#include <typeinfo>

template <typename T>
void f(const T &)
{
	std::cout << typeid(T).name() << std::endl;
}

template <typename T>
void g(T)
{
	std::cout << typeid(T).name() << std::endl;
}

int main()
{
	char a[] = {};
	f("abc");
	g("abc");
	f(a);
	g(a);
}
