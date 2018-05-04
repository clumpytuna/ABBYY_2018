#include "CFunctor.h"
#include "CTypelist.h"

#include <iostream>

class Functor {
public:
    void operator()(int i, double d) const {
        std::cout << "Functor::operator() call" << std::endl;
    }
};

void firstFunction(int i, double d) {
    std::cout << "Function call with arguments: int:" << i << ", double:" << d << std::endl;
}

void secondFunction() {
    std::cout << "Function call without arguments" << std::endl;
}

class Object {
public:
    void DoNothing() const {
        std::cout << "Do nothing!" << std::endl;
    }
    void DoSomething() {
        ++counter;
        std::cout << "Increase the counter: " << counter << std::endl;
    }
private:
    int counter = 0;
};

int main()
{
    CFunctor<void, TYPELIST_2(int, double)> function(&firstFunction);
    function(4, 4.5);
    
    // Можно оборачивать не только функции,
    // но и другие классы с переопределенным оператором ().
    Functor functor;
    function = functor;
    function(5, 4.0);
    
    // Также можно привязывать методы классов
    Object object;
    CFunctor<void, NullType> action(&object, &Object::DoNothing);
    action();
    // А затем привязывать другой метод
    action.BindMethod(&object, &Object::DoSomething);
    action();
    
}

