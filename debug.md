# debugging and profiling
"If you want more effective programmers, you will discover that they should not waste their time debugging, they should not introduce the bugs to start with." - Edsger Dijkstra

Code does exactly what you tell it to, not what we expect it to do. Bridging the gap between our (or our customers) expectations and a program's errors and performance can be difficult. 
In general, poor performance and error detection should be done as earlier as possible to make resolution easier. 

## debugging
### printf
“The most effective debugging tool is still careful thought, coupled with judiciously placed print statements” - Brian Kernighan

printfs (i.e. use some mechanism to print to stdout/stderr) are a simple way of getting enough information. Some tips: C/C++ offers some standard predefined macros that expand to strings, such as `__FILE__` and `__LINE__`. For instance, 
```cpp
std::cerr << "Error found at" << __FILE__ << ":" << __LINE__ << std::endl;
```
This will print out the file and line to help you locate the error (and help you clean it up afterwards). 
`__func__`, `__FUNCTION__`, and `__PRETTY_FUNCTION__` are available through C99 and GCC, although they are not technically macros. 

### logging
Logging supports more features than random printfs. You can log to files, sockets, or remote servers as opposed to just stdout/stderr. It also supports severity levels (INFO, DEBUG, WARN, ERROR) that can be filtered. And colors! 
Third-party dependencies may use their own logs, and many Unix-like systems will likely write to a system log. Messages logged by `systemd` can be found using the `journalctl` utility. You can write to the system log using `logger` on the terminal. 
### debuggers
Most language implementations come with a debugger. These programs allow you to:
* Halt execution at a certain line (breakpoints)
* Step through the program one line at a time
* Step into the definition of a called function
* Inspect the state of the program
* Conditionally halt the program
GNU Debugger (gdb) is our system's standard debugger. The process starts with generating a Debugging Symbol Table, which maps the compiled instructions to their names in source code. This makes the build process slower and the resulting builds larger. To build the symbol table with gcc, add the `-g` flag, ie:
```bash
g++ -g main.cpp -o main
```
We then start the program with 
```bash
gdb main
```
Some key commands in gdb:
* **b n** - breakpoint at line n
* **b fn** - breakpoint at function "fn"
* **info break** - list breakpoints
* **watch** - set a watch point, i.e. `watch  x == 3`
* **print** - print current value of variable, ie `print x`
* **set** - set variable, ie `set x = 3`
* **l** prints 10 lines of code for the current line
* **r** - run until breakpoint, error, or end of program
* **c** - continue running the program until next breakpoint or error
* **s** - step to next line (or into function)
* **n** - next line (not into function)
* **bt** - print stack 
* **u** - go up a level in the stack
* **d** - go down a level in the stack
* **q** - quit
### static analysis 
Some errors, warnings, and faults can be detected without running code. Static analysis tools are made to analyze source code before it is compiled, linked, and ran. Our system's C++ static analysis tool is `cppcheck`, which will provide warnings and errors on static code and can be integrated into `qtcreator`. 
For instance, this code:
```cpp
void func(int a)
{
	MyClass *p = nullptr; 
	if(a == 1)
	{
		p = new MyClass(); 
	}
	p->x = 5; 
}
```
`cppcheck` will detect the memory leak here, as well as a possible nullptr deference.

## profiling
Performance issues are not necessarily caused by direct errors but by poor optimization. Remember, [premature optimization is the root of all evil](http://wiki.c2.com/?PrematureOptimization). Focus on writing clear, maintainable code rather than going out of your way to be clever about optimization. If we notice performance issues during runtime, we can look for the resource hungry bottlenecks using profiling. 
### timing
The profiling equivilant of printf, this is just adding time stamps in your code. This can be somewhat misleading, as the difference in time between two points of instructions is *real time*, ie the time it took the CPU to finish execution in a multiprocessing system. We're probably more interested in *user* and *sys* times, the actual time the process spent on the CPU. We can measure these times using the `time` program on Unix. 
### profiling tools
`valgrind` is our C++ tool to detect memory management bugs. It can detect memory leaks and errors at run time. It also includes several toolsets to profile CPU usage: `cachegrind`, which simulates the L1/L2 caches and calculates cache statistics; and `callgrind`, which counts function calls and CPU instructions and builds a function call graph. `valgrind` tools are integrated into QTCreator. 
### other tools
* `htop` - a prettier CLI display of the information you would find in `top`
* `df` - disk metrics per partitions
* `du` - disk usage per file
* `ss` - lets you monitor network packets
* `ip` - routing, network devices, and interfaces. Note that `ifconfig` has been deprecated
* `tcpdump` and `wireshark` - network packet analyzers
* `pdb` - python debugger that comes with the standard implementation
* `cProfile` - python profiler
 
### references
[GDB - Quick Guide (tutorialspoint.com)](https://www.tutorialspoint.com/gnu_debugger/gdb_quick_guide.htm)

[Debugging and Profiling · Missing Semester (mit.edu)](https://missing.csail.mit.edu/2020/debugging-profiling/)

[CS107 Valgrind Callgrind (stanford.edu)](https://web.stanford.edu/class/archive/cs/cs107/cs107.1226/resources/callgrind.html)
