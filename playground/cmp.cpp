#include <iostream>

template <typename T, typename U = int>
class Cmp
{
  public:
	static U cmp(const T &a, const T &b)
	{
		return a == b;
	}
};

bool f()
{
	return 100;
}

class A
{
  public:
	int f()
	{
		return 0;
	}
	operator bool() const
	{
		std::cout << "bool" << std::endl;
		return true;
	}
};

int main()
{
	A a;
	// char c = 'a';
	if (!a) {
		std::cout << "true" << std::endl;
		return 0;
	}
}
