# C++ Build Process
## Preprocessor
* Preprocessor handles *preprocessor directives* including ```#include``` and ```#define``` 
* The preprocessor does not understand C++ syntax
* ```#include``` directives are replaced with the contents of their files
* ```#define``` macros are replaced with their values
* Conditional compilation texts (```#if```, ```#ifdef```  and ```#ifndef```) are inserted or ignored 
* C++ file extensions that GCC recognizes as source code that must be preprocessed:
  * .cc
  * .cp
  * .cxx
  * .cpp
  * .CPP
  * .c++
  * .C
* To see the output stream of the preprocessor step, use the ```-E``` switch in ```gcc```:
```bash
$> g++ -E program.cpp
```
* A simple "Hello, World!" program can produce tens of thousands of lines after it has been preprocessed

## Compilation
* Compilation takes place after each output of the preprocessor
* Compiler parses the C++ code and coverts it to assembly language for the platform
* We can stop the compiler after this step with the ```-S``` switch, which will produce an assembly file:
```bash
$> g++ -S program.cpp
```
* The assembly code is assembled into a machine code object file
* Symbols in object files are named, and symbols do not have to be defined
* We can stop the compiler after this step with the ```-c``` switch, which will produce an object file:
```bash
$> g++ -c program.cpp
$> ls
program.cpp program.o
```

* This is useful because only source files that have been changed need to be recompiled
* Object files can be put into static libraries for reusing them
* This is generally where you see compiler errors, mainly syntax

## Linking
* Linker produces the final output as a shared (dynamic, .so) library or an executable
* The linker scans .o files looking for symbols that are named but not defined
* It replaces their references with the correct addresses from other object files or libraries
* The most common errors here are missing definitions or duplicate definitions

![GCC Chart](http://www.delorie.com/djgpp/doc/ug/basics/comp1.gif)
# Other useful GCC flags
* ```-g```: generate debugging symbols for gdb or valgrind
* ```-Wall```: turn on all warnings
* ```-pendatic```: issues all warnings defined by strict ISO guidelines
* ```-std=<version>```: specifies C++ version standard
* ```-Wfatal-errors```: treats any error as fatal and stops on the first error
* ```-02```: optimizes code and checks for error in parallel
* ```--help```: you don't need help after this

# Makefile

## Syntax
```gmake
target: prereq_0 prereq_1 ... prereq_N
	command_0
	command_1
	...
	command_N
```
* tabs not spaces

``` gmake
app: main.cpp
	g++ -g -Wall main.cpp -o app
```

``` bash
$> ls
main.cpp Makefile
$> make
```

* By default, this will run the first target listed in the Makefile

``` make
all: app

app: main.cpp addition.o subtraction.o
	g++ -g -Wall main.cpp addition.o substration.o -o app

addition.o: addition.h addition.cpp
	g++ -g -Wall -c addition.cpp -o addition.o
	
subtraction.o: subtraction.h subtraction.cpp
	g++ -g -Wall -c subtraction.h subtraction.cpp
```

* If the target is newer than the prerequisite, the command will not be run

## Variables
``` make
CXX = g++
CXXFLAGS = -Wall -g
OBJDIR = .obj

$(OBJDIR)/addition.o: addition.h addition.cpp
	$(CXX) (CXXFLAGS) -c addition.cpp -o $(OBJDIR)/addition.o	
```

* Automatic variables are set by Make after a rule is matched:
  * ```$@```: Filename representing the target
  * ```$<```: Filename of first prerequisite
  * ```$^```: Filename of all prerequisites, separated by spaces
  
``` make
$(OBJDIR)/addition.o: addition.cpp addition.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

```
## Pattern Rules

``` make
app: main.cpp addition.o subtraction.o
	$(CXX) $(CXXFLAGS) $< -o $@
	
%.o: %.cpp %.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@
```
* [Make has several implicit rules based on patterns](https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html)

## .PHONY
``` make
all: directories app

directions: .obj

.obj:
	mkdir -p $@
```

``` make
clean:
	rm -rf .obj
	rm -rf app
```

* A file named ```clean``` or ```directories``` would cause make to skip

``` make
.PHONY: clean directories
```

### References
https://faculty.cs.niu.edu/~mcmahon/CS241/Notes/build.html

https://stackoverflow.com/a/6264256/11510678

https://bytes.usc.edu/cs104/labs/lab3/

https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html

