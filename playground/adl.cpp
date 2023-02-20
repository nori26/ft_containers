#include <iostream>

namespace ns
{
	class B
	{
	};

	void f(B)
	{
		std::cout << "B" << std::endl;
	}
} // namespace ns

// void f(ns::B)
// {
// 	std::cout << "g B" << std::endl;
// }

template <typename T>
class A
{
  public:
	void ff()
	{
		T b;
		f(b);
	}

	// fという名前の関数がいると、ns::f(B)はADLによって発見されない
	// (プロトタイプが一致している必要はない)

	void f(T, T)
	{
		std::cout << "A" << std::endl;
	}
	// void f(T)
	// {
	// 	std::cout << "A" << std::endl;
	// }
};

int main()
{
	A<ns::B> a;
	a.ff();

	// ns::B b;
	// f(b);
}
