#include "gtest.h"

#include "allocator.hpp"
#include "data.hpp"

#ifdef FT_TEST
  #include "vector.hpp"
#else
  #include <vector>
namespace ft = std;
#endif

namespace ftc = ft_containers;
typedef ft::vector<ftc::Data, ftc::Allocator<ftc::Data> > Vector;
typedef ftc::Allocator<ftc::Data>::ExceptionOn            AllocExceptionOn;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

int main()
{
	// Vector::iterator it;
	// (void)(it + it);
	// (void)(1 - it);

	// Vector::iterator it = Vector::iterator(); //set but not used

	// ft::vector<char>       v;
	// ft::vector<const char> v2;
	// v == v2;

	// char *p = NULL;
	// ft::vector<char>::iterator it = p;
	//(void)p;

	// int *p = NULL;
	// ft::vector<int>::reverse_iterator rit(p);
}
