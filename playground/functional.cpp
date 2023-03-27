#include <functional>

class cmp
{
  public:
  	// 全部ないとコンパイルエラー
	typedef int  first_argument_type;
	typedef int  second_argument_type;
	typedef bool result_type;

  public:
	bool operator()(const int &a, const int &b) const
	{
		return a < b;
	}
};

int main()
{
	std::binder1st<cmp> b = std::bind1st(cmp(), 0);
	(void)b;
}
