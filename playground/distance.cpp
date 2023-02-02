#include <iterator>
#include <iostream>
#include <climits>
int main()
{
	std::cout << std::distance((char*)0, (char*)-3) << std::endl;
}
