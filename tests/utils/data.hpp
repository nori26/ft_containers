#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <set>
#include <stdexcept>
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
			int  tmp_rate_;

		  public:
			ExceptionOn(int rate = 3);
			~ExceptionOn();
		};

	  private:
		static std::set<Data *> destructed;
		static bool             print_on_;
		static bool             exception_on_;
		static int              exception_rate_;

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
		Data        operator,(const Data &a);
		static void SetPrintMode(bool b);
		static bool GetPrintMode();
		static void SetExceptionMode(bool b);
		static bool GetExceptionMode();
		static void ClearDestructedPool();
		template <class Iterator>
		static bool IsDestructed(Iterator first, Iterator last)
		{
			for (; first != last; first++) {
				if (destructed.count(&*first) == 0) {
					return false;
				}
			}
			return true;
		}

	  private:
		static void print(const std::string &s, int n);
		void        ThrowRandom(const std::string &msg, int id);
	};

	std::ostream &operator<<(std::ostream &os, const Data &d);
	bool          operator<(const Data &d1, const Data &d2);

	template <class InputIt1, class InputIt2>
	bool equal(InputIt1, InputIt1, InputIt2)
	{
		throw std::runtime_error("");
		return false;
	}
	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1, InputIt1, InputIt2, BinaryPredicate)
	{
		throw std::runtime_error("");
		return false;
	}

	template <class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1, InputIt1, InputIt2, InputIt2)
	{
		throw std::runtime_error("");
		return false;
	}

	template <class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1, InputIt1, InputIt2, InputIt2, Compare)
	{
		throw std::runtime_error("");
		return false;
	}
	typedef Data::PrintOn     PrintOn;
	typedef Data::ExceptionOn ExceptionOn;
} // namespace ft_containers

#endif
