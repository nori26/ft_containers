#include "vector_fixture.hpp"
#include "data.hpp"

void vector::TearDown()
{
	ft_containers::Data::ClearDestructedPool();
}
