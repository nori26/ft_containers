#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <cassert>
#include <iostream>
#include <memory>
#include <queue>

#include "utility.hpp"

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
		typedef T                                  key_type;
		typedef U                                  value_type;
		typedef ft::pair<node_type *, node_type *> pos_and_parent;
		typedef typename node_type::color_type     color_type;

	  protected:
		node_type   end_;
		node_type *&root_;

	  private:
		std::allocator<node_type> allocator_; // TODO tempalte

	  public:
		rb_tree() : end_(), root_(end_.left)
		{
			end_.right = reinterpret_cast<node_type *>(-1);
		}

		// TODO 例外安全
		~rb_tree()
		{
			std::queue<node_type *> q;

			if (root_ == NULL) {
				return ;
			}
			q.push(root_);
			while (!q.empty()) {
				node_type *nd = q.front();
				if (nd->left != NULL) {
					q.push(nd->left);
				}
				if (nd->right != NULL) {
					q.push(nd->right);
				}
				delete_node(nd);
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
			balance_for_insert(pos);
		}

	  private:
		node_type *new_node(const T &key, const U &value)
		{
			node_type *p = allocator_.allocate(1);
			allocator_.construct(p, node_type(key, value));
			return p;
		}

		void balance_for_insert(node_type *top)
		{
			for (; top != &end_; top = top->parent) {
				if (is_red(top)) {
					continue;
				}
				node_type *left  = top->left;
				node_type *right = top->right;
				if (is_red(left) && is_red(right) &&
					(has_red_child(left) || has_red_child(right))) {
					top->color   = node_type::RED;
					left->color  = node_type::BLACK;
					right->color = node_type::BLACK;
					continue;
				}
				if (is_red(left)) {
					balance_left_for_insert(top);
				} else {
					balance_right_for_insert(top);
				}
				break;
			}
			root_->color = node_type::BLACK;
		}

		void balance_left_for_insert(node_type *top)
		{
			if (is_red(top->left->right)) {
				rotate_left(top->left);
			}
			if (is_red(top->left->left)) {
				top               = rotate_right(top);
				top->right->color = node_type::RED;
				top->color        = node_type::BLACK;
			}
		}

		void balance_right_for_insert(node_type *top)
		{
			if (is_red(top->right->left)) {
				rotate_left(top->right);
			}
			if (is_red(top->right->right)) {
				top              = rotate_left(top);
				top->left->color = node_type::RED;
				top->color       = node_type::BLACK;
			}
		}

	  public:
		void erase(const T &key)
		{
			node_type *pos = find_pos(key).first;
			node_type *parent;
			node_type *child;

			if (pos == NULL) {
				return;
			}
			if (pos->left) {
				swap_node(pos, get_max(pos->left));
				child  = pos->left;
				parent = pos->parent;
			} else {
				child  = pos->right;
				parent = pos->parent;
			}
			promote_child(pos, child);
			balance_for_erase(parent, child, pos);
			delete_node(pos);
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
			return ft::make_pair(pos, parent);
		}

	  private:
		// childがNULLの場合もあるのでparentを受け取る
		// grand_parentがend_の可能性もあるのでポインタで比較
		void promote_child(node_type *parent, node_type *child)
		{
			assert(parent && parent->parent);
			node_type *grand_parent = parent->parent;

			if (grand_parent->left == parent) {
				grand_parent->link_left(child);
			} else {
				grand_parent->link_right(child);
			}
		}

		void balance_for_erase(node_type *parent, node_type *target, node_type *detached)
		{
			if (is_red(detached)) {
				return;
			}
			for (bool is_balanced = false; parent != &end_ && !is_balanced;
				 target = parent, parent = parent->parent) {
				if (target == parent->left) {
					is_balanced = balance_left_for_erase(parent);
				} else {
					is_balanced = balance_right_for_erase(parent);
				}
			}
			if (root_) {
				root_->color = node_type::BLACK;
			}
		}

		// 左部分木の黒高さが低い状態なので(topがend_でない場合)、
		// 暗黙的に右部分木には一つ以上の黒があると期待できる
		bool balance_left_for_erase(node_type *top)
		{
			assert(top != &end_ && top->right);
			node_type *right = top->right;

			if (is_red(top->left)) {
				top->left->color = node_type::BLACK;
				return true;
			}
			if (is_red(top) && !has_red_child(right)) {
				top->color   = node_type::BLACK;
				right->color = node_type::RED;
				return true;
			}
			if (is_red(right)) {
				top              = rotate_left(top);
				top->color       = node_type::BLACK;
				top->left->color = node_type::RED;
				top              = top->left;
				right            = top->right;
			}
			if (is_red(right->left) && is_black(right->right)) {
				right               = rotate_right(right);
				right->color        = node_type::BLACK;
				right->right->color = node_type::RED;
			}
			if (is_red(right->right)) {
				color_type old    = top->color;
				top               = rotate_left(top);
				top->color        = old;
				top->left->color  = node_type::BLACK;
				top->right->color = node_type::BLACK;
				return true;
			} else {
				right->color = node_type::RED;
				return false;
			}
		}

		bool balance_right_for_erase(node_type *top)
		{
			assert(top->left);
			node_type *left = top->left;

			if (is_red(top->right)) {
				top->right->color = node_type::BLACK;
				return true;
			}
			if (is_red(top) && !has_red_child(left)) {
				top->color  = node_type::BLACK;
				left->color = node_type::RED;
				return true;
			}
			if (is_red(left)) {
				top               = rotate_right(top);
				top->color        = node_type::BLACK;
				top->right->color = node_type::RED;
				top               = top->right;
				left              = top->left;
			}
			if (is_red(left->right) && is_black(left->left)) {
				left               = rotate_left(left);
				left->color        = node_type::BLACK;
				left->right->color = node_type::RED;
			}
			if (is_red(left->left)) {
				color_type old    = top->color;
				top               = rotate_right(top);
				top->color        = old;
				top->left->color  = node_type::BLACK;
				top->right->color = node_type::BLACK;
				return true;
			} else {
				left->color = node_type::RED;
				return false;
			}
		}

		node_type *get_max(node_type *node)
		{
			if (node == NULL) {
				return NULL;
			}
			while (node->right) {
				node = node->right;
			}
			return node;
		}

		void swap_node(node_type *a, node_type *b)
		{
			node_type *parent = a->parent;
			node_type *left   = a->left;
			node_type *right  = a->right;
			color_type color  = a->color;

			link_parent(a, b->parent);
			a->link_left(b->left);
			a->link_right(b->right);
			a->color = b->color;

			link_parent(b, parent);
			b->link_left(left);
			b->link_right(right);
			b->color = color;
		}

		void delete_node(node_type *node)
		{
			if (node == NULL) {
				return;
			}
			allocator_.destroy(node);
			allocator_.deallocate(node, 1);
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
	};
} // namespace ft

#endif
