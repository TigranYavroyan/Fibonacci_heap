#include <fibo_heap.hpp>

int main () {
	ft_priority_queue<int, std::greater<int>> ob;
	ob.push(4);
	ob.push(5);
	ob.push(6);
	ob.push(7);
	ob.pop();
}