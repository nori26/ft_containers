#include <iostream>

class A
{
  public:
	int i;
	A() : i(1){};
	A &operator=(const A &a)
	{
		std::cout << "=" << std::endl;
		if (&a == this) {
			std::cout << "self" << std::endl;
		}
		i += a.i;
		return *this;
	}

	A operator+(int) const
	{
		std::cout << "+" << std::endl;
		return *this;
	}
};

int main()
{
	int x = 0;
	int y = 1;
	int z = 2;
	// (1 + 2) = 3; error
	// (x + y) = 3;
	// (x + y) = z;
	// x + y = z;
	// x = y + 1= z;
	x = y = z;
	(void)x;
	A a;
	a + 1 = a; // 右辺値だけどoperator=が関数呼び出しなのでコンパイルが通るっぽい
	std::cout << a.i << std::endl;
	a = a + 1 = a;
	std::cout << a.i << std::endl;
}
