// Автор: Михаил Анухин
// Описание: Класс определяет интерфейс callable объекта

#ifndef functorImpl_h
#define functorImpl_h

#include "typelist.h"
#include "typelistMacro.h"

template <typename ResultType, class TypeList>
class ICallable;

template <typename ResultType>
class ICallable<ResultType, CNullTypeList> {

public:
    virtual ResultType operator()() const = 0;
    virtual ~ICallable() {}
};

template <typename ResultType, typename Parameter1>
class ICallable<ResultType, TYPELIST_1( Parameter1 )> {

public:
    virtual ResultType operator()( Parameter1 ) const = 0;
    virtual ~ICallable() {}
};

template <typename ResultType, typename Parameter1, typename Parameter2>
class ICallable<ResultType, TYPELIST_2( Parameter1, Parameter2 )> {

public:
    virtual ResultType operator()( Parameter1, Parameter2 ) const = 0;
    virtual ~ICallable() {}
};

#endif /* functorImpl_h */
