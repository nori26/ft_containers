#include <cstdlib>
#include <ctime>

#include "lottery.hpp"

namespace ft_containers
{
	class Srand
	{
	  public:
		Srand()
		{
			std::srand(time(NULL));
		}
	};

	bool lottery(int odds)
	{
		static Srand init;

		return std::rand() % odds == 0;
	}
} // namespace ft_containers
