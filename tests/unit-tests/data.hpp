#ifndef DATA_HPP
#define DATA_HPP

namespace ft_containers
{
	class Data
	{
	  public:
		class PrintOff
		{
		  private:
			bool tmp_;

		  public:
			PrintOff();
			~PrintOff();
		};

	  private:
		static bool print_on_;

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

	  private:
		static void print(const std::string &s);
	};

	typedef Data::PrintOff PrintOff;
} // namespace ft_containers

#endif
