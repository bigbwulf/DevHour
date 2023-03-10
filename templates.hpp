#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>

namespace TEMPLATES
{
    template<typename T>
    T func(const T& x);
    void client();

    template<>
    std::string func(const std::string& x);
}
#include "templatesimpl.cpp"

#endif
