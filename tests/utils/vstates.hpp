#ifndef VSTATES_HPP
#define VSTATES_HPP

#include <map>

template <typename T>
class VStates
{
  public:
	struct State
	{
		size_t      size;
		size_t      cap;
		const void *data;
	};
	std::map<void *, State> old_states;

	void SaveState(const T &v)
	{
		void *key            = (void *)(&v);
		old_states[key].size = v.size();
		old_states[key].cap  = v.capacity();
		old_states[key].data = static_cast<const void *>(v.data());
	}

	bool HasSameState(const T &v)
	{
		void *key = (void *)(&v);

		return ExpectEq(old_states[key].size, v.size()) &&
			   ExpectEq(old_states[key].cap, v.capacity()) &&
			   ExpectEq(old_states[key].data, static_cast<const void *>(v.data()));
	}

  private:
	template <typename U>
	bool ExpectEq(const U &a, const U &b)
	{
		if (a != b) {
			std::cout << "Expect:" << a << std::endl;
			std::cout << "Actual:" << b << std::endl;
			return false;
		}
		return true;
	}
};

#endif
