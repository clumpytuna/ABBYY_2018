#include "CFunctor.hpp"
#include "CTypelist.h"

#include <iostream>

class Functor {
public:
    void operator()(int i, double d) const {
        std::cout << "Functor::operator() call" << std::endl;
    }
};

void function(int i, double d) {
    std::cout << "Function call" << std::endl;
}

int main()
{
    CFunctor<void, TYPELIST_2(int, double)> f(&function);
    f(4, 4.5);
    // Можно оборачивать не только функции,
    // но и другие классы с переопределенным оператором ().
    Functor functor;
    f = functor;
    f(5, 4.0);
}
