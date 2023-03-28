#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <cassert>
#include <iostream>
#include <memory>
#include <queue>

#include "utility.hpp"

namespace ft
{
	template <typename Value>
	struct rb_tree_node
	{
		enum color_type {
			RED,
			BLACK,
		};
		typedef Value value_type;

		value_type    value;
		color_type    color;
		rb_tree_node *parent;
		rb_tree_node *left;
		rb_tree_node *right;

		rb_tree_node() : value(), color(BLACK), parent(), left(), right() {}

		rb_tree_node(const value_type &v) : value(v), color(RED), parent(), left(), right() {}

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

	template <
		typename Key,
		typename Value,
		typename KeyOfValue,
		typename Compare,
		typename Allocator>
	class rb_tree
	{
		// protected for visualize
	  protected:
		typedef rb_tree_node<Value>                node_type;
		typedef Compare                            value_compare;
		typedef ft::pair<node_type *, node_type *> pos_and_parent;
		typedef KeyOfValue                         key_of_value;

	  public:
		typedef Key                                                   key_type;
		typedef Value                                                 value_type;
		typedef Allocator                                             allocator_type;
		typedef typename node_type::color_type                        color_type;
		typedef typename Allocator::template rebind<node_type>::other node_allocator;
		// template 曖昧青解消子でrebindがテンプレートクラスであることを明示する
		// template がない場合、< は小なり演算子として解釈される

	  protected:
		node_type   end_;
		node_type *&root_;

	  private:
		node_allocator allocator_;
		value_compare  cmp_;
		key_of_value   get_key_;

	  public:
		rb_tree() : end_(), root_(end_.left), allocator_(), cmp_(), get_key_()
		{
			end_.right = reinterpret_cast<node_type *>(-1);
		}

		rb_tree(const value_compare &cmp, const allocator_type &alloc)
			: end_(), root_(end_.left), allocator_(alloc), cmp_(cmp), get_key_()
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

		value_compare &value_cmp()
		{
			return cmp_;
		}

		void insert(const value_type &value)
		{
			pos_and_parent nodes  = find_pos(get_key_(value));
			node_type     *pos    = nodes.first;
			node_type     *parent = nodes.second;

			if (pos) {
				return;
			}
			pos = new_node(value);
			link_parent(pos, parent);
			balance_for_insert(pos);
		}

	  private:
		node_type *new_node(const value_type &value)
		{
			node_type *p = allocator_.allocate(1);
			allocator_.construct(p, node_type(value));
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
		void erase(const key_type &key)
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

		pos_and_parent find_pos(const key_type &key)
		{
			node_type *parent = &end_;
			node_type *pos    = root_;

			while (pos) {
				if (value_cmp()(key, pos->value)) {
					parent = pos;
					pos    = pos->left;
				} else if (!value_cmp()(key, pos->value)) {
					parent = pos;
					pos    = pos->right;
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
			} else if (grand_parent->right == parent) {
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
			if (a == b->parent) {
				swap_adjacent_node(a, b);
			} else if (b == a->parent) {
				swap_adjacent_node(b, a);
			} else {
				node_type *a_parent = a->parent;
				node_type *a_left   = a->left;
				node_type *a_right  = a->right;

				if (b->parent->left == b) {
					b->parent->link_left(a);
				} else {
					b->parent->link_right(a);
				}
				if (a_parent->left == a) {
					a_parent->link_left(b);
				} else {
					a_parent->link_right(b);
				}
				a->link_left(b->left);
				a->link_right(b->right);
				b->link_left(a_left);
				b->link_right(a_right);
				std::swap(a->color, b->color);
			}
		}

		void swap_adjacent_node(node_type *parent, node_type *child)
		{
			node_type *left  = child->left;
			node_type *right = child->right;

			promote_child(parent, child);
			if (parent->left == child) {
				child->link_left(parent);
				child->link_right(parent->right);
			} else if (parent->right == child) {
				child->link_right(parent);
				child->link_left(parent->left);
			}
			parent->link_left(left);
			parent->link_right(right);
			std::swap(parent->color, child->color);
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

		void link_parent(node_type *n, node_type *new_parent)
		{
			if (new_parent == &end_ || value_cmp()(n->value, new_parent->value)) {
				new_parent->link_left(n);
			} else {
				new_parent->link_right(n);
			}
		}

		node_type *rotate_left(node_type *top)
		{
			if (top == NULL || top->right == NULL) {
				return top;
			}
			node_type *new_top  = top->right;
			node_type *new_left = top;
			node_type *isolated = new_top->left;

			promote_child(top, new_top);
			new_top->link_left(new_left);
			new_left->link_right(isolated);
			return new_top;
		}

		node_type *rotate_right(node_type *top)
		{
			if (top == NULL || top->left == NULL) {
				return top;
			}
			node_type *new_top   = top->left;
			node_type *new_right = top;
			node_type *isolated  = new_top->right;

			promote_child(top, new_top);
			new_top->link_right(new_right);
			new_right->link_left(isolated);
			return new_top;
		}
	};
} // namespace ft

#endif
