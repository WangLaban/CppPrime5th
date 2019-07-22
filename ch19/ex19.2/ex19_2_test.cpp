#include <iostream>
#include <cstdlib>

void *operator new(std::size_t n)
{
	std::cout << "new(size_t)\n";
	if (void *mem = malloc(n))
		return mem;
	else
		throw std::bad_alloc();
}
void operator delete(void *mem) noexcept
{
	std::cout << "delete(void*)\n";
	free(mem);
}
int main()
{
	using namespace std;
	StrVec str{ "c++","primer","effictive" };
	for (auto it = str.begin(), e = str.end(); it != e; ++it)
		cout << *it << endl;
	system("pause");
	return 0;
}
