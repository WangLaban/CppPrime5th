# Chapter 19. Specialized Tools and Techniques

## Exercise 19.1

> Write your own operator new(size_t) function using malloc and use free to write the operator delete(void*) function.

check the [code](ex19_1.cpp).

## Exercise 19.2

> By default, the allocator class uses operator new to obtain storage and operator delete to free it. Recompile and rerun your
StrVec programs (§ 13.5, p. 526) using your versions of the functions from the previous exercise.

[Header](ex19.2/ex19_2_StrVec.h) | [Implement](ex19.2/ex19_2_StrVec.cpp) | [Test](ex19.2/ex19_2_test.cpp)
