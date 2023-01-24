#ifndef DATA_HPP
#define DATA_HPP

#include <string>

namespace ft_containers
{
	class Data
	{
	  public:
		class PrintOn
		{
		  private:
			bool tmp_;

		  public:
			PrintOn();
			~PrintOn();
		};
		class ExceptionOn
		{
		  private:
			bool tmp_;

		  public:
			ExceptionOn();
			~ExceptionOn();
		};

	  private:
		static bool      print_on_;
		static bool      exception_on_;
		static const int exception_rate_;

	  public:
		int *p;

	  public:
		Data();
		Data(int i);
		Data(const Data &d);
		~Data();
		Data       &operator=(const Data &d);
		bool        operator==(const Data &d) const;
		bool        operator!=(const Data &d) const;
		static void SetPrintMode(bool b);
		static bool GetPrintMode();
		static void SetExceptionMode(bool b);
		static bool GetExceptionMode();

	  private:
		static void print(const std::string &s, int n);
		void        ThrowRandom();
	};

	typedef Data::PrintOn PrintOn;
	typedef Data::ExceptionOn ExceptionOn;
} // namespace ft_containers

#endif
