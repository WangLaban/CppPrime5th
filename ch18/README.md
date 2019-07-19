# Chapter 18. Tools for Large Programs

## Exercise 18.1

> What is the type of the exception object in the following throws?
>
> **(a)**`range_error r("error");`
> `throw r`;
> **(b)**`exception *p = &r;`
> `throw *P;`
>
> What would happen if the `throw` in **(b)** were written as `throw p`?

The type of the exception object in (a) is range_error which is used to report range errors in internal computations.
The type of the exception object in (b) is exception.
If the "throw" in (b) were written as "throw p", there will be a runtime error.

## Exercise 18.2

> Explain what happens if an exception occurs at the indicated point:
```cpp
void exercise(int *b, int *e)
{
    vector<int> v(b,e);
    int *p = new int[v.size()];
    ifstream in("ints");
    // exception occurs here
}
```
The space "p" points will not be free. There will be a memory leak.

## Exercise 18.3

> There are two ways to make the previous code work correctly if an exception is thrown. Describe them and implement them.

[Throw an exception](ex18.1.2.3/main.cpp)

## Exercise 18.4

> Looking ahead to the inheritance hierarchy in Figure 18.1 (p.783), explain what’s wrong with the following try block. Correct it.
```cpp
try {
// use of the C++ standard library
} catch(exception) {
// ...
} catch(const runtime_error &re) {
// ...
} catch(overflow_error eobj) { /* ... */ }
```
The first catch parameter is the base class, then all derived classes can match, because it's not a reference or pointer, then the exception object will be sliced down.
The second catch parameter is the base class of overflow_error, and also is's a reference, so always use runtime_error when an runtime_error or overflow_error exception occurs.

## Exercise 18.5
> Modify the following main function to catch any of the exception types shown in Figure 18.1 (p. 783):
```cpp
int main() {
// use of the C++ standard library
}
```
The handlers should print the error message associated with the exception before calling abort (defined in the header cstdlib) to terminate main.

[catch exception](ex18_5.cpp)

## Exercise 18.6
> Given the following exception types and catch clauses, write a throw expression that creates an exception object that can be caught
by each catch clause:
```cpp
(a) class exceptionType { };
    catch(exceptionType *pet) { }
(b) catch(...) { }
(c) typedef int EXCPTYPE;
    catch(EXCPTYPE) { }
```
- (a) throw& exceptionType();
- (b) any type of exception is ok
- (c) throw int();

## Exercise 18.7
> Define your Blob and BlobPtr classes from Chapter 16 to use function try blocks for their constructors.

[Header](ex18_7_blob.h) | [Test](ex18_7_blob_test.cpp)

## Exercise 18.8
> Review the classes you’ve written and add appropriate exception specifications to their constructors and destructors. If you think one of your destructors might throw, change the code so that it cannot throw.

...

## Exercise 18.9
> Define the bookstore exception classes described in this section and rewrite your Sales_data compound assigment operator to throw an exception.

[Exception class](ex18.9.10/exception_class.h) | [Sales_data class](ex18.9.10/Sales_data.h) | [Test](ex18.9.10/main.cpp)

## Exercise 18.10
> Write a program that uses the Sales_data addition operator on objects that have differing ISBNs. Write two versions of the program: one that handles the exception and one that does not. Compare the behavior of the programs so that you become familiar with what happens when an uncaught exception occurs.

[Exception class](ex18.9.10/exception_class.h) | [Sales_data class](ex18.9.10/Sales_data.h) | [Test](ex18.9.10/main.cpp)

If an uncaught exception occurs, the program calls the library terminate function to stop execution of the program.

## Exercise 18.11
> Why is it important that the what function doesn’t throw?

std::exception::what() is noexcept. Consequently, if it throws, std::terminate is called. Yes, this is important.

## Exercise 18.12
> Organize the programs you have written to answer the questions in each chapter into their own namespaces. That is, namespace
chapter15 would contain code for the Query programs and chapter10 would contain the TextQuery code. Using this structure, compile the Query code examples.

[Implement](ex18.12.13.14/main.cpp)

## Exercise 18.13
> When might you use an unnamed namespace?

[refer to](http://stackoverflow.com/questions/154469/unnamed-anonymous-namespaces-vs-static-functions) and [refer to](http://stackoverflow.com/questions/5312213/uses-of-unnamed-namespace-in-c)

## Exercise 18.14
> Suppose we have the following declaration of the operator* that is a member of the nested namespace mathLib::MatrixLib:
```cpp
namespace mathLib {
    namespace MatrixLib {
        class matrix { /* ... */ };
        matrix operator*
            (const matrix &, const matrix &);
        // ...
    }
}
```
> How would you declare this operator in global scope?

mathLib::MatrixLib::matrix mathLib::MatrixLib::operator* (const matrix&, const matrix&);


## Exercise 18.15
> Explain the differences between using declarations and directives.

This difference in scope between a using declaration and a using directive stems directly from how these two facilities work. In the case of a using declaration, we are simply making name directly accessible in the local scope. In contrast, a using directive makes the entire contents of a namespace available In general, a namespace might include definitions that cannot appear in a local scope. As a consequence, a using directive is treated as if it appeared in the nearest enclosing namespace scope.

## Exercise 18.16
> Explain the following code assuming using declarations for all the members of namespace Exercise are located at the location labeled position 1. What if they appear at position 2 instead? Now answer the same question but replace the using declarations with a using directive for namespace Exercise.
```cpp
namespace Exercise {
    int ivar = 0;
    double dvar = 0;
    const int limit = 1000;
}
int ivar = 0;
// position 1
void manip() {
    // position 2
    double dvar = 3.1416;
    int iobj = limit + 1;
    ++ivar;
    ++::ivar;
}
```
[Implement](ex18.15.16.17/main.cpp)

## Exercise 18.17
> Write code to test your answers to the previous question.

[Implement](ex18.15.16.17/main.cpp)

## Exercise 18.18
> Given the following typical definition of swap § 13.3 (p.517), determine which version of swap is used if mem1 is a string. What if
mem1 is an int? Explain how name lookup works in both cases.
```cpp
void swap(T v1, T v2)
{
    using std::swap;
    swap(v1.mem1, v2.mem1);
    // swap remaining members of type T
}
```
Swap is a template function defined by the standard library. By stating we are using std::swap all the following uses of swap in the scope of the function will look for the matching template for its argument types in the standard library.
- If mem1 is a string the program will use the standard library function that has string arguments.
- If mem1 is int, it will use the standard library template version with int arguments.


## Exercise 18.19
> What if the call to swap was std::swap(v1.mem1, v2.mem1)?

The function would use the matching std version of swap for that specific call.

## Exercise 18.20
> In the following code, determine which function, if any, matches the call to compute. List the candidate and viable functions. What
type conversions, if any, are applied to the argument to match the parameter in each viable function?
```cpp
namespace primerLib {
    void compute();
    void compute(const void *);
}
using primerLib::compute;
void compute(int);
void compute(double, double = 3.4);
void compute(char*, char* = 0);
void f()
{
    compute(0);
}
```
> What would happen if the using declaration were located in main before the call to compute? Answer the same questions as before.

>**(a)**
-  void compute(int) first, no type conversion
-  void compute() doesn't work
-  void compute(const void *) works
-  void compute(double, double = 3.4) works converted to double
-  void compute(char*, char* = 0) works
>**(b)**
-  The compiler will match to void compute( const void *) in the primerLib namespace. void compute() will still not work because of too many arguments.
>**(c)**
-  void compute(int) first, no type conversion
-  void compute() doesn't work. 'compute' was not declared in this scope
-  void compute(const void *) doesn't works. 'compute' was not declared in this scope
-  void compute(double, double = 3.4) works converted to double
-  void compute(char*, char* = 0) works
```cpp
namespace primerLib {
    void compute();  //Error, does not work. Too many argument in the call to match.
    void compute(const void *) { std::cout << "compupte(const void *)" << std::endl; } //Works! Converts argument to a constant void pointer.
}

void compute(int) { std::cout << "compute(int)" << std::endl; }  //Works! Most closely matches the argument parameters so it is selected first.
void compute(double, double =3.4);  //Works! Converts argument to double.
void compute(char* x, char* =0) { std::cout << "compute(char* x, char* =0)" << std::endl; }  //Works! converts to a character pointer.

void f()
{
    //using primerLib::compute;  // b
    compute(0);
}

int main()
{
    using primerLib::compute;  // c
    f();
    return 0;
}
```

## Exercise 18.21

> Explain the following declarations. Identify any that are in error and explain why they are incorrect:

>**(a)**
```cpp
class CAD{};
class Vehicle{};
class CADVehicle : public CAD, Vehicle{};
```
CADVehicle publicly inherits from CAD and privately inherits from Vehicle.  CADVehicle gets all the  public and private methods that Vehicle has but cant be cast to a Vehicle argument. It is an "inaccessible" base.
for example:
```cpp
CADVehicle example;

void foo(Vehicle){ /*do something*/ };

foo(CADVehicle);  //will not work, will work if Vehicle were public
```
>**(b)**
```cpp
class DBList: public List,public List {/*do something*/};
```
Error because you are trying to derive from the same base class twice. If two different libraries or header files define the same named class, you need to specify with a scope resolution operator, i.e. headerfile_name::List.
>**(c)**
```cpp
class iostream : public istream, public ostream{ /*do something*/ };
```
Ok. 

## Exercise 18.22

> Given the following class hierarchy, in which each class defines a default constructor:
```cpp
class A { ... };
class B : public A { ... };
class C : public B { ... };
class X { ... };
class Y { ... };
class Z : public X, public Y { ... };
class MI : public C, public Z { ... };
```
> What is the order of constructor execution for the following definition.

```cpp
#include <iostream>

class A {};
class B : public A{};
class C : public B{};

class X {};
class Y {};
class Z : public X, public Y {};

class MI : public C, public Z {};
class D : public X, public C{};

MI mi;

int main()
{
*pd = new D;
X *px = pd;
B *pb = pd;
A *pa =pd;
C *pc = pd;
return 0;
}
```
The order in which base classes are constructed depends on the order in which they appear in the class derivation list. construction order is as follows: A, B, C, X, Y, Z, MI.  

## Exercise 18.23

> Using the hierarchy in exercise 18.22 along with class D defined below, and assuming each class defines a default constructor, which, if any, of the following conversion are not permitted?
```cpp
class D : public X, public C { ... };
D *pd = new D;
```
> (a) X *px = pd;
> (b) A *pa = pd;
> (c) B *pb = pd;
> (d) C *pc = pd;

All of the conversions are permitted.


## Exercise 18.24

> On page 807 we presented a series of calls made through a Bear pointer that pointed to a Panda object. Explain each call assuming we used a ZooAnimal pointer pointing to a Panda Object instead.
```cpp
ZooAnimal *pb = new Panda ("ying_yang");

pb->print();  // Ok, ZooAnimal::print()
pb->cuddle();  // Error, not part of the ZooAnimal interface
pb->highlight();  // Error, not part of the ZooAnimal interface
delete pb;  // Ok, ZooAnimal::~ZooAnimal()
```

## Exercise 18.25

> Assume we have two base classes, Base1 and Base 2, each of which define a virtual member named print and a virtual destructor.  From these base classes we derive the following classes, each of which redefines the print function:
```cpp
class D1 : public Base1 { /* ... */ };
class D2 : public Base2 { /* ... */ };
class MI : public D1, public D2 { /* ... */ };
```
> Using the following pointers, determine which function is used in each call:
> - Base1 *pb1 = new MI;\n
> - Base2 *pb2 = new MI;\n
> - D1 *pd1 = new MI;
> - D2 *pd2 = new MI;
> - (a) pb1->print();
> - (b) pd1->print();
> - (c) pd2->print();
> - (d) delete pb2;
> - (e) delete pd1;
> - (f) delete pd2;

>**Answer**:
- (a)MI
- (b)MI
- (c)MI
- (d)MI, D2, Base2, D1, Base1
- (e)MI, D2, Base2, D1, Base1
- (f)MI, D2, Base2, D1, Base1
- (d), (e), (f) will call all the destructor, for "Destructors are always invoked in the reverse order from which the constructors are run."
-----
[cpp](ex18_25.cpp)

-----
## Exercises Section 18.3.3
```cpp
struct Base1 {
    void print(int) const; // public by default
protected:
    int ival;
    double dval;
    char cval;
private:
    int *id;
};
struct Base2 {
    void print(double) const; // public by default
protected:
    double fval;
    private:
    double dval;
};
struct Derived : public Base1 {
    void print(std::string) const; // public by default
protected:
    std::string sval;
    double dval;
};
struct MI : public Derived, public Base2 {
    void print(std::vector<double>); // public by default
protected:
    int *ival;
    std::vector<double> dvec;
};
```
-----

## Exercise 18.26

> Given the hierarchy in the box on page 810, why is the following call to print an error? Revise MI to allow this call to print to compile and execute correctly.
```cpp
#include <iostream>
#include <vector>
struct Base1{
    void print(int) const{
        std::cout<<"Base1 Print Used"<<std::endl;
        };
protected:
        int ival;
        double dval;
        char cval;
private:
        int *id;
};
struct Base2 {
    void print(double) const;
protected:
    double fval;
private:
    double dval;
};

struct Derived : public Base1 {
void print(std::string) const;
protected:
    std::string sval;
    double dval;
};

struct MI : public Derived, public Base2{

void print(std::vector<double>){};
void print(int x) const{
    Base1::print(x);
}
protected:
    int *ival;
    std::vector<double> dvec;
};

using namespace std;

int main()
{
    MI mi;
    mi.print(42);
    return 0;
}
```
There is no matching version of print in MI that matches an integer argument.  If we just remove the print function in MI there is an ambiguity between the Derived and Base2 versions of print; therefore, we should overload the MI version of print() to take an int argument.

## Exercise 18.27

> Given the class hierarchy in the box on page 810 and assuming we add a function named foo to MI as follows:
```cpp
int ival;
double dval;
void MI::foo(double cval)
{
    int dval;
    // exercise questions occur here
}
```
> (a) List all the names visible from within MI::foo.
>
> (b) Are any names visible from more than one base class?
>
> (c) Assign to the local instance of dval the sum of the dval member of Base1 and the dval member of Derived.
>
> (d) Assign the value of the last element in MI::dvec to Base2::fval.
>
> (e) Assign cval from Base1 to the first character in sval from Derived.
```cpp
#include <iostream>
#include <vector>
struct Base1{
    void print(int) const{
        std::cout<<"Base1 Print Used"<<std::endl;
        };
protected:
    int ival;
    double dval;
    char cval;
private:
    int *id;
};

struct Base2 {
    void print(double) const;
protected:
    double fval;
private:
    double dval;
};

struct Derived : public Base1 {
    void print(std::string) const;
protected:
    std::string sval = std::string(1, Base1::cval);  //(e)
    double dval;
};

struct MI : public Derived, public Base2{

void print(std::vector<double>){};
void print(int x) const{
    Base1::print(x);
}

int ival;
double dval;

void foo(double cval)
    {
        int dval;
        dval = Base1::dval+Derived::dval;  //(c)
        Base2::fval = dvec.back() - 1;  //(d)
        Derived::sval[0] = Base1::cval;  //(e)
        std::cout<<dval;
    }
protected:
    std::vector<double> dvec = {9,8,7};
};

int main()
{
    MI mi;
    return 0;
}
```
- (a) Everything that is a property of the classes that MI derives from is visible except those that are private.
- (b) Yes any names in the base classes that repeat and are not private can be accessed in foo by adding a scope operator.
- (c) see above
- (d) see above
- (e) see above

## Exercise 18.28

> Given the following class hierarchy, which inherited members can be accessed without qualification, from within the vmi class? which require qualification? Explain your reasoning.

```cpp
struct Base {
    void bar(int); // public by default
protected:
    int ival;
};
struct Derived1 : virtual public Base {
    void bar(char); // public by default
    void foo(char);
protected:
    char cval;
};
struct Derived2 : virtual public Base {
    void foo(int); // public by default
protected:
    int ival;
    char cval;
};
class VMI : public Derived1, public Derived2 { };
```
```cpp
struct Base{
    void bar(int){ std::cout<<"B::bar(int)"<<std::endl; }  // Accessed without qualification, not defined with int arg anywhere
protected:
    int ival = 1;  // Need qualification, VMI will use Derived2::ival by default
};

struct Derived1 : virtual public Base{
    void bar(char){ std::cout<<"D1::bar(char)"<<std::endl; }  // Accessed with no qualification, VMI derives from Derived1 which derives from Base.
    void foo(char){ std::cout<<"D1::foo(char)"<<std::endl; }  // Need qualification, can convert arg between two foos.
protected:
    char cval = 'a';  // need to qualify ambiguous with other cval.
};

struct Derived2 : virtual public Base{
void foo(int){ std::cout<<"D2::foo(int)"<<std::endl; };  // Need qualification, can convert arg between two foos.
protected:
    int ival = 2;  // Accessed with no qualification.
    char cval = 'b';  // need to qualify ambiguous with other cval.
};
class VMI : public Derived1, public Derived2 { };

int main()
{
	D d;
	d.bar(42);  // D1::bar(char)
	d.B::bar(42);  // B::bar(int)
	std::cout<<d.ival<<std::endl;  // 2
	std::cout<<d.B::ival<<std::endl;  // 1
	//d.foo(42);  // [Error] request for member 'foo' is ambiguous
	d.D1::foo(42);  // D1::foo(char)
	d.D2::foo(42);   // D2::foo(int)
	//std::cout<<d.cval<<std::endl;  // [Error] request for member 'cval' is ambiguous
	std::cout<<d.D1::cval<<std::endl;  // a
	std::cout<<d.D2::cval<<std::endl;  // b
}
```
