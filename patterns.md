> "There Ain't No Such Thing As A Free Lunch...
>  anything free costs twice as much in the long
>  run or turns out worthless."
> - Robert Heinlein, *The Moon is a Harsh Mistress*

# Object Oriented Programming (OOP)
OOP is a high level imperative programming paradigm based on wrapping pieces of related data and behavior into structures called objects. Data is also referred to as state variables, fields, or attributes. Behavior is often called methods, subroutines, code, or procedures.

## The Four "Pillars"
OOP is not an ISO standard, it is a subjective philosophy to structure a computer program. Generally, OOP is based on four concepts. Two of these concepts, *Inheritance* and *Polymorphism* are unique features generally included in languages that support the OOP paradigm (but not always: try to inherit a type in Go). The other two, *Abstraction* and *Encapsulation* are more problem-solving tools that help you scale systems. They are also in no way unique to OOP. You probably already intuitively understood those concepts before ever being exposed to programming. 

### Abstraction
Most popular, naive explanations of OOP explain that objects in software are based on real-world objects and that abstractions provide a data/behavior model for the real world concept. This is rarely true in practice (is a TCPSocket a real world object?) It reality abstraction is a way to reduce dependencies between entities and increase Modularity (see Dependency Inversion Principle)

### Encapsulation
Encapsulate means to hide implementation details about an object's state from clients (code that is using the object). In C++, this means we use the `private` or `protected` keyword to prevent other objects from accessing those members (kinda: the `friend` keyword breaks this with a tight coupling, while the pointer to implementation pattern (pimpl) actually decreases the normal coupling between clients and private/protected members). Encapsulation reduces the knowledge of an object's behavior to a public interface available to clients.

#### Modularity
A closely related concept to encapsulation, and sometimes included as a "Pillar" of OOP. Modulation lets you define a public interface and hide private implementation details. What's the difference? Encapsulation and the notion of a class are rather small scale, and you can have many instances of a class in a system. Modules are meant to model a proper subsystem, and there is only one instance of a model in a subsystem. 

### Inheritance
Probably the most famous and most --understood-- misunderstood concepts of OOP. The naive interpretation is that inheritance is about code reuse: for a derived class to reuse base class code to implement itself in terms of the base class's code. This is actually a valid way of looking at inheritance but *is not* what we mean when we write `class Derived : public Base`. An is-implemented-in-terms-of relationship can be a proper way of modeling classes. But this is *private inheritance*, i.e. `class Derived : private Base` or it's closely related cousin, composition. *Public inheritance* represents an is-a (or works-like-a) relationship (see Liskov Substitution Principal).

Put another way, public inheritance is not about calling existing code, an ability that has existed long before the concepts of OOP. Instead, public inheritance is about existing code *safely and seamlessly* calling new code.

### Polymorphism
Finally, we come to the smartest sounding word on this list: Polymorphism. Despite its fancy Greek roots, Polymorphism just means "many forms", ie a concept represented by a model or class can take many different forms. Polymorphism is how we implement the contract that is guarantee by public inheritance. Naive examples will generally use an `Animal` base class with a `std::string speak()` that may be overloaded as `return "bark"` for the `Dog` class and `return meow` for the `Cat` class. But what if want to implement a `void fly()` method in the `Animal` class and create a `Bird` class. What kind of behavior would `fly()` have for `Dog` or `Cat`? Should it be unimplemented? Absolutely not, since a polymorphic call to `fly()` would do nothing and a contract that advertises `doNothing()` makes no sense. Should it fail (i.e., `throw` an exception)? Well, does `fly()` guarantee success in the `Animal` - client contract? These questions are not always easy to answer and illustrate why good design is imperative. 

#### Composition
These issues with *inheritance* and *polymorphism* make them hard to understand and difficult to implement correctly. It's generally a good rule in software engineering to minimize coupling, and inheritance is one of the strongest relationships in OOP, it should not be overused. That's why many well regarded OOP apologists, including the authors of the highly influential book *Design Patterns*, recommend *composition over inheritance*. In this context, composition simply means making a user-defined-type a member of another user-defined-type. As discussed, composition can model the *implemented-in-terms-of* relationship we often seek when we think of inheritance. Always consider this pattern first before implementing a public inheritance/polymorphic relationship.

## Design Patterns
These are typical solutions to commonly occurring problems in software design. Patterns are concepts, not code, they are meant to be implemented in your system to help solve a similar problem. They should not be confused with algorithms: an algorithm defines a procedure to solve multiple instances of the same problem class. A design pattern is an even higher level abstraction than that. The problem class is more broad and the implementation requirements are even broader.

Patterns vary in complexity, scale, and level of detail. Low-level patterns are called *idioms* and are generally specific to the programming language. An example would be the pass function arguments by the `const` reference idiom in C/C++. Higher level patterns are generally known as *architectural patterns*. These can be implemented in almost any system. An example would be the **Model View Controller** pattern often sound in software design.

We can also categorize the patterns by their intent:

- *Creational patterns* provide creation mechanisms
- *Structural patterns* explain how to assembly objects into larger structures
- *Behavioral patterns* define effective communication and responsibilities between classes

### Creational Patterns
#### Factory Method
In essence this pattern provides an interface for creating polymorphic without having to specify the exact type. Let's look at a basic yet naive implementation:

```c++
#include <memory>
#include <iostream>

class AbstractProduct
{
public:
  virtual int getValue() = 0;

  virtual void setValue(int value) = 0;   
};

class ConcreteProduct1 : public AbstractProduct
{
public:
  int getValue() override { return m_value; }

  void setValue(int value) override { m_value = value; }

private:
  int m_value;
};

class ConcreteProduct2 : public AbstractProduct
{
public:
  int getValue() override { return m_value + 50; }

  void setValue(int value) override { m_value = value * 100; }

private:
  int m_value;   
};

class Factory
{
public:
  std::unique_ptr<AbstractProduct> createInstance(int type);  
};

std::unique_ptr<AbstractProduct> Factory::createInstance(int type)
{
  if(type == 1)
      return std::make_unique<ConcreteProduct1>();

  if(type == 2)
      return std::make_unique<ConcreteProduct2>();

  return std::unique_ptr<AbstractProduct>(); 
}

void client(AbstractProduct* product)
{
    product->setValue(5); 
    std::cout << product->getValue() << std::endl; 
}

int main()
{
    Factory factory;
    auto product1 = factory.createInstance(1);
    auto product2 = factory.createInstance(2); 
    client(product1.get());
    client(product2.get()); 
    return 0; 
}
```
This is a elegant if small implementation that might benefit from a few improvements (enum instead of ints, switch statements) but how salable is this? What if the number of types grows very large throughout the code's life? Such a switch statement would become unwieldy, difficult to maintain.

Let's take an example from RAVE: Our plugin interface class allows extensions to provide various test nodes that can be used as part of Test Cases. The method returns a reference to an `AbstractNode`:

```cpp
class RAVEPluginInterface
{
public:
  virtual AbstractNode* createPluginNode(const QString& name, QObject* parent = nullptr) = 0; 
};

```
Note the abstraction of the interface here. Users writing an extension are free to implement the creation of their `AbstractNode`s in any way they wish. 

The `AbstractNode` class has a few polymorphic functions, including the ability to save a json:

```cpp
class AbstractNode
{
public:
  AbstractNode() = default;
  virtual ~AbstractNode() = default;

  QJsonObject saveAsJson() { return this->doSaveAsJson() };

private:
  virtual QJsonObject doSaveAsJson() = 0; 
};
```
In the plugin's implementation, we can create out factory class:

```cpp
// nodefactory.h
#include <RAVEPluginInterface/abstractnode.hpp>
class NodeFactory
{
public:
  using TCreateFunction = std::function<unique_ptr<AbstractNode>(QObject*)>;

  NodeFactory() = delete;

  static bool register(const QString& name, TCreateFunction func);

  static AbstractNode* create(const QString& name, QObject* parent);

private:
  static QHash<QString, TCreateFunction> m_createFuncs;   
};

// nodefactory.cpp
#include "nodefactory.h"

QHash<QString, TCreateMethod> NodeFactory::m_createFuncs;

bool
register(const QString& name, TCreateFunction func)
{
  // C++17 init-if  
  if(auto it = m_createFuncs.find(name); it == m_createFuncs.end()) { 
    m_createFuncs[name] = funcCreate;
    return true;
  }
  return false; 
}

AbstractNode* create(const QString& name, QObject* parent)
{
  if(auto it = m_createFuncs.find(name); it != m_createFuncs.end()) {
    return it->second(parent); 
  }
  return nullptr; 
}
```
We then create the concrete classes:

```cpp
// radnode.h
class RADNode : AbstractNode
{
public:
  static AbstractNode* create(Qbject* parent) {
    return new RADNode(parent); 
  }

  static QString getName() { return "RADNode"; }

private:
  static bool is_registerd;
  doSaveAsJson() override;   
};

//radnode.cpp

bool is_registered =
  NodeFactory::register(RADNode::getName(), RADNode::create);
```
We can do this for all `AbstractNode`s we want to register in the factory, and they will be registered at static allocation time.

The only major drawback is that each class in the factory requires extra code, but our factory remains relatively clean and simple.

Our implementation of `RAVEPluginInterface` can now call the factory method:

```cpp
#include "nodefactory.h"
class RADPluginImpl : public RAVEPluginInterface
{
  AbstractNode* createPluginNode(const QString& name, QObject* parent = nullptr) override;  
};

inline AbstractNode* RADPluginImpl::createPluginNode(const QString& name, QObject* parent)
{
  return NodeFactory::create(name, parent); 
}
```
Putting it all together, our client code in RAVE proper, which receives the name of the required Node via another transaction, can call via the plugin interface:

```cpp
   QString nodeName = entity.getRequiredName();
   auto pluginNode = plugin.createPluginNode(nodeName, this); 
```














