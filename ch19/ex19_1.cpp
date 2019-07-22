#include <iostream>
#include <cstdlib>
 
void *operator new(std::size_t n){
	std::cout << "new(size_t)\n";
	if (void *mem = malloc(n))
		return mem;
	else
		throw std::bad_alloc();
}
void operator delete(void *mem) noexcept{
	std::cout << "delete(void*)\n";
	free(mem);
}

int main()
{
	int *a = new int(42);
	std::cout << a << " " << *a << std::endl;
	delete a;

	return 0;
}
