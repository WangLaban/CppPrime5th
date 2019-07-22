# Chapter 19. Specialized Tools and Techniques

## Exercise 19.1

> Write your own operator new(size_t) function using malloc and use free to write the operator delete(void*) function.

check the [code](ex19_1.cpp).

## Exercise 19.2

> By default, the allocator class uses operator new to obtain storage and operator delete to free it. Recompile and rerun your
StrVec programs (§ 13.5, p. 526) using your versions of the functions from the previous exercise.

[Header](ex19.2/ex19_2_StrVec.h) | [Implement](ex19.2/ex19_2_StrVec.cpp) | [Test](ex19.2/ex19_2_test.cpp)


## Exercise 19.3

> Given the following class hierarchy in which each class defines a public default constructor and virtual destructor:
```cpp
class A { /* . . . */ };
class B : public A { /* . . . */ };
class C : public B { /* . . . */ };
class D : public B, public A { /* . . . */ };
```
> which, if any, of the following dynamic_casts fail?

> (a) A *pa = new C;

> B *pb = dynamic_cast< B* >(pa);

> (b) B *pb = new B;

> C *pc = dynamic_cast< C* >(pb);

> (c) A *pa = new D;

> B *pb = dynamic_cast< B* >(pa);

(b) cast fail.

## Exercise 19.4
> Using the classes defined in the first exercise, rewrite the following code to convert the expression *pa to the type C&:
```cpp
if (C *pc = dynamic_cast< C* >(pa))
// use C's members
} else {
// use A's members
}
```
check the [code](ex19_4.cpp).

## Exercise 19.5
> When should you use a dynamic_cast instead of a virtual function?
