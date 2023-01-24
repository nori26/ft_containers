#include <cstdlib>
#include <ctime>
#include <iostream>

#include "color.hpp"
#include "data.hpp"
namespace
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
} // namespace

namespace ft_containers
{
	bool      Data::print_on_       = true;
	bool      Data::exception_on_   = false;
	const int Data::exception_rate_ = 3;

	Data::Data() : p()
	{
		print(COL_CYAN "construct 0" COL_END, 0);
		ThrowRandom();
		p    = new int[1];
		p[0] = 0;
	}

	Data::Data(int i) : p()
	{
		print("construct n", i);
		ThrowRandom();
		p    = new int[1];
		p[0] = i;
	}

	Data::Data(const Data &d)
	{
		print("copy", d.p[0]);
		ThrowRandom();
		p    = new int[1];
		p[0] = d.p[0];
	}

	Data::~Data()
	{
		print(COL_RED "destruct" COL_END, p[0]);
		delete[] p;
	}

	Data &Data::operator=(const Data &d)
	{
		print("operator=", d.p[0]);
		ThrowRandom();
		if (&d == this) {
			return *this;
		}
		delete[] p;
		p    = new int[1];
		p[0] = d.p[0];
		return *this;
	}

	bool Data::operator==(const Data &d) const
	{
		print("operator==", p[0]);
		return this->p[0] == d.p[0];
	}

	bool Data::operator!=(const Data &d) const
	{
		print("operator!=", p[0]);
		return !(*this == d);
	}

	void Data::print(const std::string &s, int n)
	{
		if (print_on_) {
			std::cout << s << " " << n << std::endl;
		}
	}

	void Data::ThrowRandom()
	{
		if (exception_on_ && lottery(exception_rate_)) {
			throw std::runtime_error("random throw");
		}
	}

	void Data::SetPrintMode(bool b)
	{
		print_on_ = b;
	}

	void Data::SetExceptionMode(bool b)
	{
		exception_on_ = b;
	}

	bool Data::GetPrintMode()
	{
		return print_on_;
	}

	bool Data::GetExceptionMode()
	{
		return exception_on_;
	}

	Data::PrintOff::PrintOff()
	{
		tmp_ = GetPrintMode();
		Data::SetPrintMode(false);
	}

	Data::PrintOff::~PrintOff()
	{
		Data::SetPrintMode(tmp_);
	}

	Data::ExceptionOn::ExceptionOn()
	{
		tmp_ = GetExceptionMode();
		Data::SetExceptionMode(true);
	}

	Data::ExceptionOn::~ExceptionOn()
	{
		Data::SetExceptionMode(tmp_);
	}
} // namespace ft_containers
