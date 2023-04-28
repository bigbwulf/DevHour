# const and const-ness
## const correctness
It's an expressive way of declaring an object immutable (read-only). It tells other programmers, and, more importantly, the compiler, that the object should not be written to. They are mainly used for:
* Symbolic constants
* pointers that read-through but never written-through
* function parameters

Why is const-ness a good thing?

* It protects you from accidentally changing objects that should not be changed
* It protects you from accidental assignments:
```cpp
void foo(const int DEFCON)
{
	if(DEFCON = 1) //compiler error!
	{
		fire();
	}
}
```
* the compiler can optimize the read-only value because it will know the state of the variable at all time
* it communicates that parameters will not be changed in function signatures:
```cpp
void f1(const std::string& s); // pass by reference to const
void f2(const std::string* s_ptr); // pass by pointer to const
void f3(std::string s); // pass by value

void g1(std::string& s); // pass by reference to non-const
void g2(std::string* s_ptr); //pass by pointer to non-const
```

## how to read all those const's
From right to left:
```cpp
const X* p; // p is a pointer to an X which is const
p->getter() // ok
p->setter() // error

X* const p; // p is a const pointer to a non-const X
const X* const p; // p is a const pointer to a const X
const X& x; // x is a reference to a const X

// "west const"
X const& x; // same as const X& x
X const* p; //same as const X* p; 

X& const x; // redundent, because references are always const
```

## const member function
A getter or inspect function that does not modify its object. 
```cpp
class X 
{
public:
	void getter() const; // *this will not be changed
	void setter(); // *this might be changed
}

void foo(const X x)
{
	x.setter() // error
}
```
## when to decide const-ness?
As soon as possible. Deciding to make something const later on can have a snowball effect which requires a lot of maintenance. 

# constexpr
constexpr explicitly declares both objects and functions as fit for what the standard calls *constant expressions*, ie it *can* be evaluated at compile time.  

## constexpr functions
Member functions, non-member functions can be declared constexpr but they must be non-virtual and very simple: only a singly return statement is allowed in C++11. It can be used with non-constexpr arguments but this will not result in compile-time evaluation. 

constexpr functions are meant to replace macros and hardcoded literals. 

```cpp
constexpr int max() { return INT_MAX } 
constexpr float getPi() { return 3.14 }

constexpr bool foo() 
{
	bool result = false; 
	return result;
} // error, the function is too complex :(

constexpr int square(int x) { return x * x }
const int res = square(5);  // compile time evalution because the argument is constexpr
int y = foo();
int n = square(y); // Valid, but runtime evaluation
```
constexpr explicitely marks your function as a constant expression
```cpp
int f(int n)
{
	return n > 0 ? n + f(n - 1) : n;
} // compiler can tell this is a constant expression if n is constant expression

int arr[f(10)]; 

```cpp
int f(int n)
{
	static std::map<int, int> cache; 
	if(cache.find(n) == cache.end())
	{
		cache[n] = n > 0 ? n + f(n - 1) : n; 
	}
	return cache[n]; 
} // no longer constexpr!!
```
## constexpr objects
Constant expression objects must be initialized with a constant expression or rvalue. 

```cpp
struct S
{
	constexpr int two();
private:
	static constexpr int small;
}
constexpr int S::small = 256; 
enum DataPacket
{
	Small = S::two(); // error , S::two() hasn't been defined
	Big = 1024; 
}
constexpr int S::two() { return small * 2; }
constexpr S s; 
int arr[s.two()]; 
```

## constexpr constructors
Constant expression constructors can have member initialization list by its body must be empty. This allows the compiler to initialize the object at compile-time with constexpr arguments. 
```cpp
class complex
{
public:
	constexpr complex(double r, double i) : m_real(r), m_imag(i) {}
	constexpr double real() { return m_real; }
	constexpr double imag() { return m_imag; }
private:
	double m_real; 
	double m_imag;
};

constexpr complex cx(0.0, 1.0); // compile time
double x = 1.0; 
constexpr complex cx1(x, 0); // error: x is not constexpr
const complex cx2(x, 1); // runtime initialization
constexpr double xx = cx.real(); // compile time
complex cx3(2, 4.6); // run time
```
## constexpr tips
From *Effective Modern C++* by Scott Meyers:
* ```constexpr``` objects are const and initialized with values known during compilation
* ```constexpr``` functions produce compile-time results when called with arguments whose values are constant expressions
* ```constexpr``` objects and functions may be used with with non-```constexpr``` objects and functions
* ```constexpr``` is part of an object's or function's interface
# references
https://stackoverflow.com/a/34554462

[Const Correctness, C++ FAQ (isocpp.org)](https://isocpp.org/wiki/faq/const-correctness)

https://stackoverflow.com/a/28821610


	
	
