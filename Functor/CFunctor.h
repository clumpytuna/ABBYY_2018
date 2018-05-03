// Автор: Михаил Анухин
// Описание: Класс CFunctor<typename T, TYPELIST_N(...) >

#ifndef functor_hpp
#define functor_hpp

#include <stdio.h>
#include "CTypelist.h"

// Шаблонный класс реализующий функционал функтора.
// Можно поместить в класс функтор, функцию или метод класса и использовать их стандартным образом,
// вызывая оператор (). Для обертки параметров используются TypeList.
// Пример использования:
// void function(int i, double d);
// CFunctor<void, TYPELIST_2(int, double)> f(&function);
// f(4, 4.5);
template <class ResultType, class TypeList>
class  CFunctor {
public:
    // Получаем каждый из типов, который может быть передан в TypeList в явном виде.
    typedef typename GetTypeAt<TypeList, 0, NullType>::Result FirstParameterType;
    typedef typename GetTypeAt<TypeList, 1, NullType>::Result SecondParameterType;
    
    template <typename Callable>
    CFunctor( const Callable& f ) : callableObject( new CCallable<CFunctor, Callable > (f) ) {}
    ~CFunctor() { delete callableObject; }
    
    // Оператор присваивания помещает функцию, функтор или метод в класс
    template <typename Callable>
    void operator =(const Callable& f);
    
    // Вызывает функцию, функтор или метод.
    ResultType operator()() const;
    
    ResultType operator()( FirstParameterType parameter ) const;
    
    ResultType operator()( FirstParameterType firstParameter, SecondParameterType secondParameter ) const;
  
private:
    // Интерфейс для вызываемого объекта, определяем для каждого из возможных количеств параметра.
    // Список может быть расширен для поддержки необходимого количества параметров
    template <typename ResType, typename ClassTypeList>
    class ICallable;
    
    // Указатель на вызываемый объект
    ICallable <ResultType, TypeList>*  callableObject;
    
    // Интерфейс для вызываемого объекта без параметров
    template <typename ResType>
    class ICallable<ResType, NullType> {   
    public:
        virtual ResType operator()() const = 0;
        virtual ~ICallable() {}
    };
    
    // Интерфейс для вызываемого объекта с 1 параметром
    template <typename ResType, typename ParameterType>
    class ICallable<ResType, TYPELIST_1( ParameterType )> {
    public:
        virtual ResType operator()( ParameterType ) const = 0;
        virtual ~ICallable() {}
    };
    
    // Интерфейс для вызываемого объекта с 2 параметроми
    template <typename ResType, typename ParameterTypeFirst, typename ParameterTypeSecond>
    class ICallable<ResType, TYPELIST_2( ParameterTypeFirst, ParameterTypeSecond )> {
    public:
        virtual ResType operator()( ParameterTypeFirst, ParameterTypeSecond ) const = 0;
        virtual ~ICallable() {}
    };
    
    // Класс вызываемого объекта. Определяем в нем оператор () для всевозможных количеств аргумента
    // до фиксированного N.
    template <class ParentFunctor,  typename Callable>
    class CCallable: public ICallable< ResultType, TypeList > {
    public:
        CCallable( const Callable& F ) : callableObject( F ) {}
        
        // Вызывает функцию, функтор или метод
        ResultType operator()() const {
            return callableObject();
        }
        ResultType operator()( typename ParentFunctor::FirstParameterType firstParameter ) const {
            return callableObject( firstParameter );
        }
        ResultType operator()( typename ParentFunctor::FirstParameterType firstParameter,
                               typename ParentFunctor::SecondParameterType secondParameter ) const {
            return callableObject( firstParameter, secondParameter );
        }
                                           
    private:
        //Фунция, функтор или метод, который мы будем вызывать
        Callable callableObject;
    };
};

template<class ResultType, class TypeList>
template <typename Callable>
void CFunctor<ResultType, TypeList>::operator =( const Callable& f )
{
  delete callableObject;
  callableObject = new CCallable<CFunctor, Callable>(f);
}

template<class ResultType, class TypeList>
ResultType CFunctor<ResultType, TypeList>::operator()() const
{
    return ( *callableObject )();
}

template<class ResultType, class TypeList>
ResultType CFunctor<ResultType, TypeList>::operator()(  FirstParameterType firstParameter  ) const
{
    return ( *callableObject )( firstParameter );
}

template<class ResultType, class TypeList>
ResultType CFunctor<ResultType, TypeList>::operator()( FirstParameterType firstParameter, SecondParameterType secondParameter ) const
{
    return ( *callableObject )( firstParameter, secondParameter );
}

#endif /* functor_hpp */
