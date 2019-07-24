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

>     B *pb = dynamic_cast< B* >(pa);

> (b) B *pb = new B;

>     C *pc = dynamic_cast< C* >(pb);

> (c) A *pa = new D;

>     B *pb = dynamic_cast< B* >(pa);

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

when we have a derived operation that we want to perform through a pointer or reference to a base-class object and it is not possible to
make that operation a virtual function.

## Exercise 19.6

> Write an expression to dynamically cast a pointer to a Query_base to a pointer to an AndQuery (§ 15.9.1, p. 636). Test the cast
by using objects of AndQuery and of another query type. Print a statement indicating whether the cast works and be sure that the output matches yourexpectations.

[TextQuery](ex19.6.7.8/ex19_6.7.8_TextQuery.h) | [Query](ex19.6.7.8/ex19_6.7.8_Query.h) | [Test](ex19.6.7.8/ex19_6.7.8_Test.cpp)

## Exercise 19.7

> Write the same cast, but cast a Query_base object to a reference to AndQuery. Repeat the test to ensure that your cast works correctly.

[TextQuery](ex19.6.7.8/ex19_6.7.8_TextQuery.h) | [Query](ex19.6.7.8/ex19_6.7.8_Query.h) | [Test](ex19.6.7.8/ex19_6.7.8_Test.cpp)

## Exercise 19.8

> Write a typeid expression to see whether two Query_base pointers point to the same type. Now check whether that type is an AndQuery.

[TextQuery](ex19.6.7.8/ex19_6.7.8_TextQuery.h) | [Query](ex19.6.7.8/ex19_6.7.8_Query.h) | [Test](ex19.6.7.8/ex19_6.7.8_Test.cpp)

## Exercise 19.9

> Write a program similar to the last one in this section to print the names your compiler uses for common type names. If your compiler
gives output similar to ours, write a function that will translate those strings to more human-friendly form.

[type_info](ex19_9_TypeName.cpp)

## Exercise 19.10

> Given the following class hierarchy in which each class defines a public default constructor and virtual destructor, which type name
do the following statements print?
```cpp
class A { /* . . . */ };
class B : public A { /* . . . */ };
class C : public B { /* . . . */ };
```
> (a) A *pa = new C;

>     cout << typeid(pa).name() << endl;  // P1A

A's pointer.

> (b) C cobj;

>     A& ra = cobj;

>     cout << typeid(&ra).name() << endl;  // P1A

A's pointer.

> (c) B *px = new B;

>     A& ra = *px;

>     cout << typeid(ra).name() << endl;  // 1B

B's reference. If all classes didn't define the virtual destructor, It will output A's reference.

## Exercise 19.11

> What is the difference between an ordinary data pointer and a pointer to a data member?

As with any pointer, we declare a pointer to member using a * to indicate that the name we’re declaring is a pointer. Unlike ordinary pointers, a pointer to member also incorporates the class that contains the member. Hence, we must precede the * with classname:: to indicate that the pointer we are defining can point to a member of classname.

When we initialize or assign a pointer to member, that pointer does not yet point to any data. It identifies a specific member but not the object that contains that member. We supply the object when we dereference the pointer to member.

## Exercise 19.12

> Define a pointer to member that can point to the cursor member of class Screen. Fetch the value of Screen::cursor through that pointer.

[const Screen::pos Screen::*pc = &Screen::cursor;](ex19_12.cpp)

## Exercise 19.13

>  Define the type that can represent a pointer to the bookNo member of the Sales_data class.
```cpp
  - member:
	static const std::string Sales_data::* data()
	{
		return &Sales_data::bookNo;
	}
  - call:
  const string Sales_data::*pb=Sales_data::data();
```
Check code [here](ex19_13.cpp)
