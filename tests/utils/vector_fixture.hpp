#ifndef FIXTURE_HPP
#define FIXTURE_HPP

#include "gtest.h"

class vector : public ::testing::Test
{
  protected:
	virtual void TearDown();
};

#endif
