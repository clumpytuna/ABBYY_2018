// Автор: Михаил Анухин
// Описание: Класс CFunctor<typename T, TYPELIST_N(...) >

#ifndef functor_hpp
#define functor_hpp

#include "CTypelist.h"

// Шаблонный класс реализующий возможности функтора.
// Можно поместить в класс функтор, функцию или метод класса и использовать их стандартным образом,
// вызывая оператор (). Для обертки параметров используются TypeList. Количество аргументов в данной
// реализации ограничено двумя, но может быть расширена.
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
    
    // Конструктор из функции или функтора
    template <typename Callable>
    CFunctor( const Callable& f ) : callableObject( new CFunctionHandler<CFunctor, Callable > ( f ) ) {}
    
    // Конструктор из указателя на объект и его метода
    template <class ObjectPtr, typename MethodPtr>
    CFunctor( const ObjectPtr& object, MethodPtr method ) :
        callableObject( new CMethodHandler<CFunctor, ObjectPtr, MethodPtr > ( object, method ) ) {}
    
    ~CFunctor() { delete callableObject; }
    
    // Оператор присваивания помещает функцию или функтор в класс.
    // Важно! Не стоит его использовать для присваивания метода
    template <typename Callable>
    void operator =( const Callable& f );
    
    // Вызывает функцию, функтор или метод
    ResultType operator()() const;
    
    ResultType operator()( FirstParameterType firstParameter ) const;
    
    ResultType operator()( FirstParameterType firstParameter, SecondParameterType secondParameter ) const;
    
    // Привязывет метод класса к функтору
    template <class ObjectPtr, typename MethodPtr>
    void BindMethod( const ObjectPtr& object,  MethodPtr method );
  
private:
    // Интерфейс для вызываемого объекта, определяем для каждого из возможных количеств параметра.
    // Список может быть расширен для поддержки необходимого количества параметров
    template <typename ResType, typename ClassTypeList>
    class ICallable;
    
    // Указатель на вызываемый объект
    ICallable <ResultType, TypeList>* callableObject;
    
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
    
    // Класс вызываемого объекта. Хранит функцию или функтор.
    // Определен оператор () для всевозможных количеств аргумента до фиксированного N.
    // Данная реализация поддерживает до 2 аргументов.
    // Через оператор() происходит вызов функции или функтора.
    template <class ParentFunctor,  typename Callable>
    class CFunctionHandler: public ICallable<ResultType, TypeList> {
    public:
        CFunctionHandler( const Callable& f ) : callableObject( f ) {}
        
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
        //Фунция или функтор, которые мы будем вызывать
        Callable callableObject;
    };
    
    // Класс вызываемого объекта. Хранит указатель на метод и укзатель на объект, метод которого мы вызываем.
    // Определен оператор () для всевозможных количеств аргумента до фиксированного N.
    // Данная реализация поддерживает до 2 аргументов.
    // Через оператор() происходит вызов метода.
    template <class ParentFunctor, typename ObjectPointer, typename MethodPointer>
    class CMethodHandler : public ICallable<ResultType, TypeList> {
    public:
        CMethodHandler( const ObjectPointer& object_, MethodPointer method_ ) :
            object( object_ ),
            method( method_ ) { }

        // Вызывов метода для разного числа параметров
        ResultType operator()() const
        {
            return ( ( *object ).*method )();
        }
        ResultType operator()( typename ParentFunctor::FirstParameterType firstParameter ) const
        {
            return ( ( *object ).*method )( firstParameter );
            
        }
        ResultType operator()( typename ParentFunctor::FirstParameterType firstParameter,
                               typename ParentFunctor::SecondParameterType secondParameter ) const
        {
            return ( ( *object ).*method )( firstParameter, secondParameter );
        }
    
    private:
        // Указатель на класс, метод которого будет вызыван
        ObjectPointer object;
        // Указатель на метод класса
        MethodPointer method;
    };
};

template<class ResultType, class TypeList>
template <typename Callable>
void CFunctor<ResultType, TypeList>::operator =( const Callable& f )
{
  delete callableObject;
  callableObject = new CFunctionHandler<CFunctor, Callable>( f );
}

template<class ResultType, class TypeList>
ResultType CFunctor<ResultType, TypeList>::operator()() const
{
    return ( *callableObject )();
}

template<class ResultType, class TypeList>
ResultType CFunctor<ResultType, TypeList>::operator()( FirstParameterType firstParameter ) const
{
    return ( *callableObject )( firstParameter );
}

template<class ResultType, class TypeList>
ResultType CFunctor<ResultType, TypeList>::operator()( FirstParameterType firstParameter, SecondParameterType secondParameter ) const
{
    return ( *callableObject )( firstParameter, secondParameter );
}

template<class ResultType, class TypeList>
template <class ObjectPointer, typename MethodPointer>
void CFunctor<ResultType, TypeList>::BindMethod( const ObjectPointer& object,  MethodPointer method )
{
    delete callableObject;
    callableObject = new CMethodHandler<CFunctor, ObjectPointer, MethodPointer > ( object, method );
}

#endif /* functor_hpp */
