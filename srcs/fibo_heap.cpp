#include <fibo_heap.hpp>

template <typename T, typename Compare>
ft_priority_queue<T, Compare>::Node::Node() :
	children{},
	key{value_type()},
	degree{0}
{}

template <typename T, typename Compare>
ft_priority_queue<T, Compare>::Node::Node(const_reference _key) :
	children{},
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
	root_list.emplace_back(key);
	++n;
	_set_prior(root_list.back());
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::push (r_reference key) {
	root_list.emplace_back(key);
	++n;
	_set_prior(&root_list.back());
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::pop() {
	if (root_list.empty())
		return;
	--n;
	if (!prior->children.empty())
	{
		iterator curr = prior->children.begin();
		while (curr != prior->children.end()) {
			root_list.emplace_back(std::move(*curr++));
		}
	}
	root_list.remove_if([&](Node& other){
		return this->prior == &other;
	});
	prior = nullptr;
	_heapify();
	_set_min();
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_heapify () {
	if (root_list.empty())
		return;
	std::vector<iterator> degrees(std::log2(n) + 1, iterator(nullptr));
	iterator it = root_list.begin();
	while (it != root_list.end())
		_connect(degrees, it++);

	_print_root_list();
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_connect(std::vector<iterator>& degrees, iterator it)
{
	iterator tmp = degrees[it->degree];
	if (tmp == iterator(nullptr))
		degrees[it->degree] = it;
	else {
		degrees[it->degree] = iterator(nullptr);
		iterator res = _push_back(tmp, it);
		_connect(degrees, res);
	}
}

template <typename T, typename Compare>
typename ft_priority_queue<T, Compare>::iterator ft_priority_queue<T, Compare>::_push_back (iterator tmp, iterator it)
{
	if (cmp(tmp->key, it->key)) {
		it->children.push_back(*tmp);
		++it->degree;
		root_list.erase(tmp);
		return it;
	}
	else {
		tmp->children.push_back(*it);
		++tmp->degree;
		root_list.erase(it);
		return tmp;
	}
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_set_min () {
	for_each(root_list.begin(), root_list.end(), [&](Node& other){
		this->_set_prior(&other);
	});
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_set_prior(Node* curr)
{
	if (prior == nullptr)
		prior = curr;
	else
		prior = (cmp(prior->key, curr->key)) ? curr : prior;
}

template <typename T, typename Compare>
void ft_priority_queue<T, Compare>::_print_root_list () const {
	for_each(root_list.begin(), root_list.end(), [](const Node& node) {
		std::cout << node.key << ' ';
	});
	std::cout << std::endl;
}