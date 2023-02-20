#include "../tests/utils/data.hpp"
#include "../srcs/vector.hpp"

int main()
{
	ft_containers::Data d = 2;
	ft::vector<ft_containers::Data> v;
	v.insert(v.begin(), d);
	v.pop_back();
	std::cout << v.size() << std::endl;
}
