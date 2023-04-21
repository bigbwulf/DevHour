# C++ Standard Library
## intro
The C++ Standard Library is one of the two major parts of the C++ Standard (the other being the core language)
It provides a range of aggregate types, algorithms, input/output, etc.
Standard library facilities are scoped in the namespace `std`.
The C++ standard specifies the syntax and semantics of its various components, but also places requirements on performance. 
All major implementations of C++ provide a Standard Library Implementation which conforms to the standards. 

## Standard Library vs. STL
Before C++ was standardized, programmer Alexander Stepanov created a library to provide classes and features based on generic programming principals. It was known as the Standard Template Library (STL) and was widely used. The STL is generally divided into four parts:
* Containers
* Algorithms
* Iterators
* Functions (functors or function objects)
During standardization, the committee adopted parts of the STL into the standard library with Stepanov's participation. However, it is not a proper fork or superset, and the two libraries are separate entities.  Referring to the Standard Library as "the STL" is a misnomer. 

## big-o complexity
[bookmark this](https://www.bigocheatsheet.com/)
* O(1): constant time - Excellent/best
* O(log(n)): logorithmic time - Good
* O(n): linear time - OK
* O(n log(n)): linearithmic time - Bad
* O(n^2), O(2^n), O(n!): some fancy math names - just quit C++ and go write python
## containers
There are three general types of containers: 
* **Sequence containers** are *ordered collections* where the element's position depends on the time and place of insertion and is independent of the value.  They are generally implemented as arrays or linked lists. The sequence classes are: `array`, `vector`, `deque`, `list`, and `forward_list`.
* **Associative containers** are *sorted collections* where an element's value determines its position. They are generally implemented as binary trees. The associative containers are `set`, `multiset`, `map`, and `multimap`. 
* **Unordered (associative) containers** are unordered collections where the postion of an element doesn't matter. Only the existence of the element matters. They are generally implemented as hash tables. The unordered classes are `unordered_set`, `unordered_multiset`, `unordered_map`, `unordered_multimap`. 
* Additionally, there are several container adaptors which contain specific interfaces using other containers as an implementation. They are `queue`, `priority_queue`, and `stack`. 
### vector
Vectors are dynamic arrays with random access  (i.e., v[element] is O(1)) that can resize when inserting an element. Inserting to the end of a vector is O(1) (amortized). Inserting to the beginning or middle of a vector is O(n) because all the elements need to be moved.  
### deque
A double-ended queue is a dynamic array (O(1) access) that can grow in both directions. Inserting to the beginning is O(1). Inserting to the middle is still O(n).
### arrays
Fixed sized arrays, the size must be declared at compile time, `array<int, 5>`. It is essentially a lightweight wrapper to a C-style array. 
### lists
A doubly linked list. Elements are not contiguous is memory. The performance is the opposite of a vector. Slow lookup and access (O(n)) but insertion into the middle is fast O(1) once the position is found.  
### forward_list
A singly linked list, made to save memory and slightly better insertion and deletion. However, there is no `push_back` or `size` because they would cause a performance penalty. You also can't search for an element then delete it or insert something in front of it. 
### set
Elements are sorted according to their own value. Duplicates not allowed. Insert and search are O(log(n)). 
### multiset
Same as set, but allows duplicate elements.
### map
Contains key/value pairs. Each element is sorted by key, and no duplicate keys are allowed. Performance is O(log(n))
### multimap
Same as a map but duplicates are allowed. 
### unordered_set
Collection of unordered elements with no duplicates. Search/insertion is O(1)
### unordered_multiset
Same as set but duplicates are allowed
### unordered_map
Key/value pairs that are not sorted. Search/insertion is O(1)
### unordered_multimap
Same as unordered_map but duplicates are allowed. 
### stack
Manages elements by LIFO
### queue
Manages elements by FIFO
### priority queue
Manages elements based on an associated priority value. 
### which container do I use?
Probably `vector`. it provides:
* fastest random access
* lowest space overhead
Usually, you need to add or remove elements dynamically, which gives it an advantage over `array`. Vector can still perform better than other containers on certain operations if the containers are only a few KB in size. 
If you need a dictionary style container with frequent inserts on large data sets (more than a few KB), use `unordered_map` or `map` instead. 
## sources
[C++ STL Complexities (alyssaq.github.io)](https://alyssaq.github.io/stl-complexities/)
[c++ - How can I efficiently select a Standard Library container in C++11? - Stack Overflow](https://stackoverflow.com/questions/10699265/how-can-i-efficiently-select-a-standard-library-container-in-c11)
[Standard Template Library - Wikipedia](https://en.wikipedia.org/wiki/Standard_Template_Library#History)
https://stackoverflow.com/questions/5205491/whats-the-difference-between-stl-and-c-standard-library



