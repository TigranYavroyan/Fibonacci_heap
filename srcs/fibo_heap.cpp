#include <fibo_heap.hpp>

template <typename T, typename Compare>
ft_priority_queue<T, Compare>::Node::Node() :
	parent{nullptr},
	prev{nullptr},
	next{nullptr},
	child{nullptr},
	key{value_type()},
	degree{0}
{}

template <typename T, typename Compare>
ft_priority_queue<T, Compare>::Node::Node(const_reference _key) :
	parent{nullptr},
	prev{nullptr},
	next{nullptr},
	child{nullptr},
	key{_key},
	degree{0}
{}

template <typename T, typename Compare>
ft_priority_queue<T, Compare>::~ft_priority_queue() noexcept {}

template <typename T, typename Compare>
ft_priority_queue<T, Compare>::ft_priority_queue(const Compare& compare) :
	root_list{},
	prior{nullptr},
	n{0},
	cmp{compare}
{}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::push (const_reference key) {
	root_list.push_back(std::make_shared<Node>(key));
	++n;
	_set_prior(root_list.back());
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::push (r_reference key) {
	root_list.push_back(std::make_shared<Node>(key));
	++n;
	_set_prior(root_list.back());
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::pop() {
	if (root_list.empty())
		return;
	--n;
	if (prior->child != nullptr)
	{
		std::shared_ptr<Node> curr = prior->child;
		while (curr != nullptr) {
			root_list.push_back(std::shared_ptr<Node>(curr));
			curr = curr->next;
		}
	}
	root_list.remove_if([&](const std::shared_ptr<Node>& other){
		return this->prior == other;
	});
	prior = nullptr;
	_heapify();
	_set_min();
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_heapify () {
	if (root_list.empty())
		return;
	std::vector<std::shared_ptr<Node>> degrees(std::log2(n) + 1, nullptr);
	auto it = root_list.begin();
	while (it != root_list.end())
	{
		_connect(degrees, *(it++));
	}

}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_connect(std::vector<std::shared_ptr<Node>>& degrees, std::shared_ptr<Node>& it)
{
	std::shared_ptr<Node> tmp(degrees[it->degree]);
	if (tmp == nullptr)
		degrees[it->degree] = it;
	else {
		degrees[it->degree] = nullptr;
		std::shared_ptr<Node> res = _push_back(tmp, it);
		_connect(degrees, res);
	}
}

template <typename T, typename Compare>
std::shared_ptr<typename ft_priority_queue<T, Compare>::Node> ft_priority_queue<T, Compare>::_push_back (std::shared_ptr<Node>& tmp, std::shared_ptr<Node>& it)
{
	if (cmp(tmp->key, it->key)) {
		_add_child(it, tmp);
		root_list.remove_if([&](const std::shared_ptr<Node>& other){
			return tmp == other;
		});
		return it;
	}
	else {
		_add_child(tmp, it);
		root_list.remove_if([&](const std::shared_ptr<Node>& other){
			return it == other;
		});
		return tmp;
	}
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_add_child(std::shared_ptr<Node>& parent, std::shared_ptr<Node>& child)
{
	std::shared_ptr<Node>& curr = parent->child;
	std::shared_ptr<Node> prev = nullptr;
	while (curr) {
		prev = curr;
		curr = curr->next;
	}
	curr = child;
	child->parent = parent;
	child->prev = prev;
	++parent->degree;
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_set_min () {
	for_each(root_list.begin(), root_list.end(), [&](std::shared_ptr<Node>& other){
		this->_set_prior(other);
	});
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_set_prior(std::shared_ptr<Node>& curr)
{
	if (prior == nullptr)
		prior = curr;
	else
		prior = (cmp(prior->key, curr->key)) ? curr : prior;
}