# C++ Build Process
## Preprocessor
* Preprocessor handles *preprocessor directives* including ```#include``` and ```#define``` 
* The preprocessor does not understand C++ syntax
* ```#include``` directives are replaced with the contents of their files
* ```#define``` macros are replaced with their values
* Conditional compilation texts (```#if```, ```#ifdef```  and ```#ifndef```) are inserted or ignored 
* To see the output stream of the preprocessor step, use the ```-E``` switch in ```gcc```:
```bash
$> g++ -E program.cpp
```
* A simple "Hello, World!" program can produce tens of thousands of lines after it has been preprocessed

## Compilation
* Compilation takes place after each output of the preprocessor
* Compiler parses the C++ code and coverts it to assembly language for the platform
* We can stop the compiler afte rthis step with the ```-S``` switch, which will produce an assembly file:
```bash
$> g++ -S program.cpp
```
* The assembly code is assembled into a machine code object file
* Symbols in object files are named, and symbols do not have to be defined
* We can stop the compiler after this step with the ```-c``` switch, which will produce an object file:
```bash
$> g++ -c program.cpp
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

```gmake
app: main.cpp
	g++ -g -Wall main.cpp -o app
```

```bash
$> make
```

* By default, this will run the first target listed in the Makefile

```bash
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
```make
CXX = 
```

