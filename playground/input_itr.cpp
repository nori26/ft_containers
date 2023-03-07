#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

typedef std::istream_iterator<char> InputIter;

class I : public InputIter
{
  public:
	operator char()
	{
		return 2;
	}
};

int main()
{
	{
		std::vector<char> v = std::vector<char>(I(), I());
		std::cout << v.size() << std::endl;
	}

	{
		std::istringstream str("1234");
		std::vector<char>  v = std::vector<char>(InputIter(str), InputIter());
		std::cout << v[0] << std::endl;
		std::cout << v[1] << std::endl;
		std::cout << v[2] << std::endl;
		std::cout << v[3] << std::endl;
	}
}
