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
