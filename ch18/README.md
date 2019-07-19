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
```cpp
(a) throw& exceptionType();
(b) any type of exception is ok
(c) throw int();
```

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

- refer to: http://stackoverflow.com/questions/154469/unnamed-anonymous-namespaces-vs-static-functions
- and: http://stackoverflow.com/questions/5312213/uses-of-unnamed-namespace-in-c

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
How would you declare this operator in global scope?

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
