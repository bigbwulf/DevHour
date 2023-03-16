### The stack
```c++
int f(int a)
{
	if (a > 0)
	{
		std::string s = "hello"; 
		std::cout << s << std::endl;
	} // s destroyed
	return a; 
} // a destroyed
```

### The heap
```c++
int *num = new int(42); 
delete num; 
delete num; // udb

// who owns the return object? 
House* buildAHouse(); 

House* house = buildAHouse(); 
delete house; // ????
```

### RAII
```c++
template <typename T>
class SmartPointer
{
public:
	explicit SmartPointer(T* p) : m_p(p) {}
	~SmartPointer() { delete m_p; }
	T* get() { return m_p; }
private:
	T* m_p; 

}


SmartPointer<House> buildAHouse();

{
	SmartPointer<House> house = buildAHouse(); 
} // house is destroyed

{
    SmartPointer<House> sp1(new House()); 
	if(sp1)
	{
		//convert to bool
	}
	
	*sp1.getRooms(); 
	sp1->getRooms(); 
	
	// get the underlying raw pointer
	House *obj = sp1.get(); 
	
	// copy?
	SmartPointer<House> sp2 = sp1; 		
} // sp1 and sp2 destroyed
```

### std::unique_ptr
```c++
std::unique_ptr<House> buildAHouse(); 
auto p1 = std::make_unique<int>(42);
std::unique_ptr<int> p2 = p1; // compiler error
std::unique_ptr<int> p2 = std::move(p1); 

void myFunc(unique_ptr<A> arg)
{
	std::cout << arg->getVal() << std::endl;
}

int main()
{
	auto uPtr = make_unique<A>(1234);
	myFunc(std::move(uPtr)); 
	assert(uPtr == nullptr)
}
```

### Raw pointers
```cpp
void renderHouse(House const& house); 
void renderHouse(House* house); 
std::unique_ptr<House> house = buildAHouse(); 
renderHouse(*house); 
renderHouse(house.get()); 
```

### std::shared_ptr
```cpp
auto sp1 = std::make_shared<int>(500);
std::cout << sp1.use_count() << std::endl;  // 1
std::shared_ptr<int> sp2 = sp1;
std::cout << sp1.use_count() << std::endl; // 2
```

### std::weak_ptr
```cpp
auto sp = std::make_shared<int>(500); 

std::weak_ptr<int> wp = sp; 

if(std::shared_ptr<int> sp = wp.lock())
{
	// sp.get() is still valid
}
else
{
	// sp.get() obj has been destroyed
}

struct House
{
	std::shared_ptr<House> neighbor;
};

int main()
{
	auto house1 = std::make_shared<House>(); 
	auto house2 = std::make_shared<House>(); 
	house1->neighbor = house2; 
	house2->neighbor = house1; 
}

struct House
{
	std::weak_ptr<House> neighbor; 
}
```
### QT
Do smart pointers belong in QT? 
* QSharedPointer ~ std::shared_ptr
* QWeakPointer ~ std::weak_ptr
* QScopedPointer ~ std::unique_ptr
* QPointer ~ ???

### Sources
https://www.fluentcpp.com/2017/08/22/smart-developers-use-smart-pointers-smart-pointers-basics/
https://www.fluentcpp.com/2017/08/25/knowing-your-smart-pointers/
https://stackoverflow.com/questions/22304118/what-is-the-difference-between-qpointer-qsharedpointer-and-qweakpointer-classes
https://stackoverflow.com/questions/30905487/how-can-i-pass-stdunique-ptr-into-a-function
