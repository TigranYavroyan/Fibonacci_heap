#include <fibo_heap.hpp>
#include <queue>

int main () {
	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
	std::vector<int> vec2 = {0, 2, 3, 10, 1, 16, 17};
	// std::list<int> ls(vec.begin(), vec.end());
	ft_priority_queue<int> ob(vec.begin(), vec.end());
	ft_priority_queue<int> ob2(vec2.begin(), vec2.end());
	// ob.pop();
	// ob.pop();
	// ob2.pop();
	ob.merge(ob2);
	std::cout << "ob: " << std::endl;
	while (!ob.empty()) {
		std::cout << ob.top() << ' ' << std::flush;
		ob.pop();
	}

	std::cout << "\nob2: " << std::endl;
	while (!ob2.empty()) {
		std::cout << ob2.top() << ' ' << std::flush;
		ob2.pop();
	}
}