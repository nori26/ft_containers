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
		// protected for visualize
	  protected:
		typedef rb_tree_node<T, U> node_type;

	  public:
		typedef T key_type;
		typedef U value_type;

	  protected:
		node_type *root_;

	  private:
		std::allocator<node_type> allocator_; // TODO tempalte
		bool                      is_balanced_;

	  public:
		rb_tree() : root_(), is_balanced_(true) {}

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
			is_balanced_ = true;
			root_        = insert_recursive(NULL, root_, key, value);
			root_->color = node_type::BLACK;
		}

	  private:
		node_type *
		insert_recursive(node_type *parent, node_type *&node, const T &key, const U &value)
		{
			if (node == NULL) {
				is_balanced_ = false;
				return new_node(parent, key, value);
			} else if (key > node->key) {
				node->right = insert_recursive(node, node->right, key, value);
				return balance_insert(node);
			} else if (key < node->key) {
				node->left = insert_recursive(node, node->left, key, value);
				return balance_insert(node);
			} else {
				node->value = value;
				return node;
			}
		}

		node_type *new_node(node_type *parent, const T &key, const U &value)
		{
			node_type *p = allocator_.allocate(1);
			allocator_.construct(p, node_type(parent, key, value));
			return p;
		}

		node_type *balance_insert(node_type *top)
		{
			if (is_balanced_ == true || top == NULL || is_red(top)) {
				return top;
			}
			/*
				   2B          2R
				   / \         / \
				 1R   3R  => 1B   3B
				 /           /
				0R          2R
			*/
			if (is_red(top->left) && is_red(top->right) &&
				(has_red_child(top->left) || has_red_child(top->right))) {
				top->color        = node_type::RED;
				top->left->color  = node_type::BLACK;
				top->right->color = node_type::BLACK;
				return top;
			}
			/*
				  2B            2B
				  / \           / \
				0R   3B  =>   1R   3B
				 \           /
				  1R       0R
			*/
			if (is_red(top->left) && is_red(top->left->right)) {
				top->left = rotate_left(top->left);
			} else if (is_red(top->right) && is_red(top->right->left)) {
				top->right = rotate_left(top->right);
			}
			/*
				   2B         1R           1B
				   / \        / \          / \
				 1R   3B => 0R   2B   => 0R   2R
				 /                \            \
				0R                 3B           3B
			*/
			if (is_red(top->left) && is_red(top->left->left)) {
				top               = rotate_right(top);
				top->right->color = node_type::RED;
			} else if (is_red(top->right) && is_red(top->right->right)) {
				top              = rotate_left(top);
				top->left->color = node_type::RED;
			}
			top->color   = node_type::BLACK;
			is_balanced_ = true;
			return top;
		}

		bool has_red_child(node_type *n)
		{
			return is_red(n->left) || is_red(n->right);
		}

		bool is_black(node_type *n)
		{
			return n == NULL || n->color == node_type::BLACK;
		}

		bool is_red(node_type *n)
		{
			return !is_black(n);
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

		node_type *rotate_left(node_type *n)
		{
			if (n == NULL || n->right == NULL) {
				return n;
			}
			node_type *parent = n->parent;
			node_type *right  = n->right;
			n->parent         = right;
			n->right          = right->left;
			if (n->right) {
				n->right->parent = n;
			}
			right->parent = parent;
			right->left   = n;
			return right;
		}

		node_type *rotate_right(node_type *n)
		{
			if (n == NULL || n->left == NULL) {
				return n;
			}
			node_type *parent = n->parent;
			node_type *left   = n->left;
			n->parent         = left;
			n->left           = left->right;
			if (n->left) {
				n->left->parent = n;
			}
			left->parent = parent;
			left->right  = n;
			return left;
		}

		node_type *double_rotate_left(node_type *n)
		{
			n->right = rotate_right(n->right);
			return rotate_left(n);
		}

		node_type *double_rotate_right(node_type *n)
		{
			n->left = rotate_left(n->left);
			return rotate_right(n);
		}

		void unlink(node_type *n)
		{
			n->parent = NULL;
			n->left   = NULL;
			n->right  = NULL;
		}
	};
} // namespace ft

#endif
