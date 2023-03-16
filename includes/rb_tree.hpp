#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include <memory>
#include <queue>

namespace ft
{
	template <typename T, typename U>
	struct rb_tree_node
	{
		enum color_type {
			RED,
			BLACK,
		};
		typedef T key_type;
		typedef U value_type;

		key_type      key;
		value_type    value;
		color_type    color;
		rb_tree_node *parent;
		rb_tree_node *left;
		rb_tree_node *right;

		rb_tree_node(rb_tree_node *p, const key_type &k, const value_type &v)
			: key(k), value(v), color(RED), parent(p), left(), right()
		{}
	};

	template <typename T, typename U>
	class rb_tree
	{
	  private:
		typedef rb_tree_node<T, U> node_type;

	  public:
		typedef T key_type;
		typedef U value_type;

	  private:
		node_type                *root_;
		std::allocator<node_type> allocator_;

	  public:
		// TODO 例外安全
		~rb_tree()
		{
			std::queue<node_type *> q;

			q.push(root_);
			while (!q.empty()) {
				node_type *nd = q.front();
				if (nd->left != NULL) {
					q.push(nd->left);
				}
				if (nd->right != NULL) {
					q.push(nd->right);
				}
				allocator_.deallocate(nd, 1);
				q.pop();
			}
		}

		void insert(const T &key, const U &value)
		{
			insert_recursive(NULL, root_, key, value);
			root_->color = node_type::BLACK;
		}

	  private:
		void insert_recursive(node_type *parent, node_type *&node, const T &key, const U &value)
		{
			if (node == NULL) {
				node = new_node(parent, key, value);
			} else if (key > node->key) {
				insert_recursive(node, node->right, key, value);
			} else if (key < node->key) {
				insert_recursive(node, node->left, key, value);
			} else {
				node->value = value;
			}
		}

		node_type *new_node(node_type *parent, const T &key, const U &value)
		{
			node_type *p = allocator_.allocate(1);
			*p           = node_type(parent, key, value);
			return p;
		}

	  public:
		void print()
		{
			if (!root_) {
				return;
			}
			size_t                  height      = 0;
			size_t                  prev_height = 0;
			std::queue<node_type *> q;

			q.push(root_);
			while (!q.empty()) {
				node_type *n = q.front();
				height       = get_height(n);
				if (height != prev_height) {
					std::cout << std::endl;
				}
				prev_height = height;
				switch (n->color) {
				case node_type::RED:
					std::cout << "\033[1;31m";
					break;
				case node_type::BLACK:
					break;
				default:
					std::cerr << "invalid color" << std::endl;
					abort();
				}
				std::cout << n->key << " "
						  << "\033[0m";
				if (n->left != NULL) {
					q.push(n->left);
				}
				if (n->right != NULL) {
					q.push(n->right);
				}
				q.pop();
			}
			std::cout << std::endl;
		}

	  private:
		size_t get_height(node_type *n)
		{
			size_t i = 0;
			for (; n->parent; n = n->parent) {
				i++;
			}
			return i;
		}
	};
} // namespace ft

#endif
