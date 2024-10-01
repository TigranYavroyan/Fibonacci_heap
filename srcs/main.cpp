#include <fibo_heap.hpp>



int main () {
	std::vector<int> vec = {1, 2, 3, 4, 5};
	ft_priority_queue<int> ob;
	ob.push(1);
	ob.push(2);
	ob.push(3);
	ob.push(4);
	ob.push(5);
	ft_priority_queue<int> ob2 = ob;
	while (!ob.empty()) {
		std::cout << ob2.top() << ' ';
		ob2.pop();
	}
}