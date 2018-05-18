// Автор: Михаил Анухин
// Описание: Демонстрация работы класса CFunctor

#include "Functor.h"
#include "TypeList.h"
#include <iostream>

// Классы для демонстрации работы класса CFunctor.

// Класс предназначен для демонстрации привязки функтора к CFunctor
class Functor {
public:
  void operator()() const {
    std::cout << "Functor::operator() call" << std::endl;
  }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Класс предназначен для демонстрации привязки методов класса с раличными спецификаторами к CFunctor
class Object {
public:
    void DoNothing() const
    {
        std::cout << "Const method call" << std::endl;
    }
    void DoSomething()
    {
        ++counter;
        std::cout << "Unconst method call" << std::endl;
    }
    
private:
    int counter = 0;
};

// Функции предназначены для демонстрации привязки функций с различным количеством аргументов к CFunctor
void noArgumentFunction() {
    std::cout << "Function call without arguments" << std::endl;
}
int oneArgumentFunction(int a) {
    std::cout << "Function call with arguments: " << a << std::endl;
    return a;
}
void twoArgumentFunction( int a, double b ) {
  std::cout << "Function call with arguments: int:" << a << ", double:" << b << std::endl;
}


int main()
{
    // Демонстрация привязки функций к CFunctor
    // 1) Можно создать объект, а затем воспользоваться оператором = для привязки функции
    CFunctor<void, NullType> firstFunction;
    firstFunction = &noArgumentFunction;
    firstFunction();
    
    // 2) Можно воспользоваться конструктором и привязать функцию сразу при создании объекта
    CFunctor<int, TYPELIST_1( int )> secondFunction( &oneArgumentFunction );
    int result = secondFunction( 0 );
  
    // 3) Можно создать объект, а затем воспользоваться методом BindFunction для привязки функции
    CFunctor<void, TYPELIST_2( int, double )> thirdFunction;
    thirdFunction.BindFunction( &twoArgumentFunction );
    thirdFunction( 0, 1.0 );
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Демонстрация привязки функторов к CFunctor
    // Аналогично можно работать и с функторами
    Functor functor;
    
    // 1) Можно создать объект, а затем воспользоваться оператором = для привязки функтора
    CFunctor<void, NullType> firstFunctor;
    firstFunctor = functor;
    firstFunctor();
    
    // 2) Можно воспользоваться конструктором и привязать функтора сразу при создании объекта
    CFunctor<void, NullType> secondFunctor( functor );
    secondFunctor();
    
    // 3) Можно создать объект, а затем воспользоваться методом BindFunction для привязки функтора
    CFunctor<void, NullType> thirdFunctor;
    thirdFunctor.BindFunction(functor);
    thirdFunctor();
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Демонстрация привязки метода к CFunctor
    Object object;
    
    // 1) Можно создать объект, а затем воспользоваться методом BindMethod для привзяки метода
    CFunctor<void, NullType> action;
    action.BindMethod(&object, &Object::DoNothing);
    action();
    
    // Можно перепривязать другой метод
    action.BindMethod(&object, &Object::DoSomething);
    action();
}
