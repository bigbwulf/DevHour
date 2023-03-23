
template<typename T>
T TEMPLATES::func(const T& x)
{
    return x * x; 
}

template<>
std::string TEMPLATES::func(const std::string& x)
{
    return x + x; 
}

void TEMPLATES::client()
{
    std::cout << func<int>(5) << std::endl;
    std::cout << func<double>(5) << std::endl;
    std::cout << func<char>('c') << std::endl;
    std::cout << func<std::string>("Hello, World") << std::endl; 
}
