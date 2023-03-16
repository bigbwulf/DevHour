#ifndef SMTPTRS_H
#define SMTPTRS_H
#include <memory>
#include <iostream> 
namespace SMTPTRS
{
    void client()
    {
	auto p1 = std::make_unique<int>(42);
	//std::unique_ptr<int> p2 = p1;
	auto sp1 = std::make_shared<int>(500);
	std::cout << sp1.use_count() << std::endl; 
	std::shared_ptr<int> sp2 = sp1;
	std::cout << sp1.use_count() << std::endl; 
	
	
    }
}
#endif
