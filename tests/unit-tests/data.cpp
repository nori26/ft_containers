#include <iostream>

#include "color.hpp"
#include "data.hpp"

namespace ft_containers
{
	bool Data::print_on_ = true;

	Data::Data() : p()
	{
		print(COL_CYAN "construct 0" COL_END, 0);
		p    = new int[1];
		p[0] = 0;
	}

	Data::Data(int i) : p()
	{
		print("construct n", i);
		p    = new int[1];
		p[0] = i;
	}

	Data::Data(const Data &d)
	{
		print("copy", d.p[0]);
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

	void Data::SetPrintMode(bool b)
	{
		print_on_ = b;
	}

	bool Data::GetPrintMode()
	{
		return print_on_;
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
} // namespace ft_containers
