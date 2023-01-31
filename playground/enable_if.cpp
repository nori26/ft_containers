#include <type_traits>
#include <iostream>

template <typename T, typename std::enable_if<std::is_integral<T>::value>::type>
void f()
{
    std::cout <<  "ok" << std::endl;
}

int main()
{
    // f<int>();
}
