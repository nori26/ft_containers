#include <iostream>
#include <memory>

// c++98 g++ではコピーが2回発生する

class Key;

typedef std::pair<Key, int> value_type;

class Key
{
	int i;

  public:
	Key() : i() {}
	Key(const Key &a)
	{
		std::cout << "copy" << std::endl;
		i = a.i;
	}
};

class Node
{
	value_type v_;

  public:
	Node() {}
	Node(const value_type &v) : v_(v) {}
};

int main()
{
	value_type           v;
	std::allocator<Node> a;
	Node                *p = a.allocate(1);
	a.construct(p, value_type());
}
