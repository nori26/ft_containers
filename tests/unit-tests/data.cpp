#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

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
	bool      Data::print_on_       = false;
	bool      Data::exception_on_   = false;
	const int Data::exception_rate_ = 3;

	Data::Data() : p()
	{
		print(COL_CYAN "construct 0" COL_END, 0);
		ThrowRandom("construct 0", 0);
		p    = new int[1];
		p[0] = 0;
	}

	Data::Data(int i) : p()
	{
		print("construct n", i);
		ThrowRandom("construct n", i);
		p    = new int[1];
		p[0] = i;
	}

	Data::Data(const Data &d)
	{
		print("copy", d.p[0]);
		ThrowRandom("copy", d.p[0]);
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
		ThrowRandom("operator=", d.p[0]);
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

	void Data::ThrowRandom(const std::string &msg, int id)
	{
		if (exception_on_ && lottery(exception_rate_)) {
			std::stringstream ss;
			ss << msg << " " << id;
			throw std::runtime_error("random throw: " + ss.str());
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

	Data::PrintOn::PrintOn()
	{
		tmp_ = GetPrintMode();
		Data::SetPrintMode(true);
	}

	Data::PrintOn::~PrintOn()
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

	std::ostream &operator<<(std::ostream &os, const Data &d)
	{
		os << d.p[0];
		return os;
	}
} // namespace ft_containers
