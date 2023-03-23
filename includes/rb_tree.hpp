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

		rb_tree_node() : key(), value(), color(BLACK), parent(), left(), right() {}

		rb_tree_node(const key_type &k, const value_type &v)
			: key(k), value(v), color(RED), parent(), left(), right()
		{}

		void link_parent(rb_tree_node *new_parent)
		{
			parent = new_parent;
			if (parent) {
				if (key < parent->key) {
					parent->left = this;
				} else {
					parent->right = this;
				}
			}
		}

		void link_left(rb_tree_node *new_left)
		{
			left = new_left;
			if (new_left) {
				new_left->parent = this;
			}
		}

		void link_right(rb_tree_node *new_right)
		{
			right = new_right;
			if (new_right) {
				new_right->parent = this;
			}
		}
	};

	template <typename T, typename U>
	class rb_tree
	{
		// protected for visualize
	  protected:
		typedef rb_tree_node<T, U> node_type;

	  public:
		typedef T                                   key_type;
		typedef U                                   value_type;
		typedef std::pair<node_type *, node_type *> pos_and_parent;

	  protected:
		node_type   end_;
		node_type *&root_;

	  private:
		std::allocator<node_type> allocator_; // TODO tempalte
		bool                      is_balanced_;

	  public:
		rb_tree() : end_(), root_(end_.left), is_balanced_(true) {}

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
			pos_and_parent nodes  = find_pos(key);
			node_type     *pos    = nodes.first;
			node_type     *parent = nodes.second;

			if (pos) {
				pos->value = value;
				return;
			}
			pos = new_node(key, value);
			link_parent(pos, parent);
			is_balanced_ = false;
			for (node_type *top = pos; !is_balanced_ && top != &end_; top = top->parent) {
				top = balance_for_insert(top);
			}
			root_->color = node_type::BLACK;
		}

			is_balanced_ = true;
			root_        = insert_recursive(NULL, root_, key, value);
			root_->color = node_type::BLACK;
		}


		pos_and_parent find_pos(const T &key)
		{
			node_type *parent = &end_;
			node_type *pos    = root_;

			while (pos) {
				if (key > pos->key) {
					parent = pos;
					pos    = pos->right;
				} else if (key < pos->key) {
					parent = pos;
					pos    = pos->left;
				} else {
					break;
				}
			}
			return std::make_pair(pos, parent);
		}

	  private:
		node_type *new_node(const T &key, const U &value)
		{
			node_type *p = allocator_.allocate(1);
			allocator_.construct(p, node_type(key, value));
			return p;
		}

		node_type *balance_for_insert(node_type *top)
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

		void link_parent(node_type *n, node_type *parent)
		{
			if (parent == &end_) {
				parent->link_left(n);
			} else {
				n->link_parent(parent);
			}
		}

		node_type *rotate_left(node_type *top)
		{
			if (top == NULL || top->right == NULL) {
				return top;
			}
			node_type *parent   = top->parent;
			node_type *new_top  = top->right;
			node_type *new_left = top;
			node_type *isolated = new_top->left;

			link_parent(new_top, parent);
			new_top->link_left(new_left);
			new_left->link_right(isolated);
			return new_top;
		}

		node_type *rotate_right(node_type *top)
		{
			if (top == NULL || top->left == NULL) {
				return top;
			}
			node_type *parent    = top->parent;
			node_type *new_top   = top->left;
			node_type *new_right = top;
			node_type *isolated  = new_top->right;

			link_parent(new_top, parent);
			new_top->link_right(new_right);
			new_right->link_left(isolated);
			return new_top;
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