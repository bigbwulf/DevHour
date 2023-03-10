#ifndef LAMBDA_H
#define LAMBDA_H

#include <vector>
#include <iostream>
#include <algorithm>

namespace LAMBDA
{
    struct Functor
    {
	template<typename T>
	void operator() (const T& e)
	{
	    std::cout << e << " "; 
	}
    };
    
    template<typename T>
    void printVec(const std::vector<T>& vec)
    {
	std::for_each(vec.begin(), vec.end(), [](const T& e)
	{
	    std::cout << e << " ";  
	});
	std::cout << std::endl; 
    }

    void client()
    {
	auto vec = std::vector<int>{1, 20, 3, 40, 5};
	// use functor
	auto f = Functor();
	
	std::for_each(vec.begin(), vec.end(), f);
	std::cout << std::endl;

	// in a function
	printVec(vec);

	//template lambda (only C++20)
	auto l = []<typename T> (const T& e)
	    {
		std::cout << e << " "; 
	    };

	std::for_each(vec.begin(), vec.end(), l);
	std::cout << std::endl;

	// reverse sort
	std::sort(vec.begin(), vec.end(), [](double a, double b)
	{
	    return a > b;  
	});
		
	printVec(vec);

	// copy evens
	std::vector<int> evenVec;
	std::copy_if(vec.begin(), vec.end(), std::back_inserter(evenVec), [](const int& e)
	{
	    return e % 2 == 0; 
	});
	printVec(evenVec);
    }
}

#endif
