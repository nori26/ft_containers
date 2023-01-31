#include <vector>

int main()
{
	std::vector<size_t> v;
	size_t              a[2] = {0, 1};
	v.reserve(1);
	v.insert(v.end() + 1, a, a + 2);
}
