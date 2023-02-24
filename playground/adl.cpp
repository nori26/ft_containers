#include <iostream>

namespace ns
{
	class B
	{
	};

} // namespace ns

namespace ns2
{
	class C
	{
	};
} // namespace ns2

namespace ns
{

	void f(B, ns2::C)
	{
		std::cout << "B" << std::endl;
	}
}

namespace ns2
{
	void f(ns::B, C)
	{
		std::cout << "g B" << std::endl;
	}
} // namespace ns2

template <typename T>
class A
{
  public:
	void ff(ns2::C c)
	{
		T b;
		f(b, c);
	}

	// fという名前の関数がいると、ns::f(B)はADLによって発見されない
	// (プロトタイプが一致している必要はない)

	// void f(T, T)
	// {
	// 	std::cout << "A" << std::endl;
	// }
	// void f(T)
	// {
	// 	std::cout << "A" << std::endl;
	// }
};

int main()
{
	ns2::C   c;
	A<ns::B> a;
	a.ff(c);

	// ns::B b;
	// f(b);
}
