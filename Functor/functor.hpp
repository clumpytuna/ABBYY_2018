// Автор: Михаил Анухин
// Описание: класс реализующий функционал функтора

#ifndef functor_hpp
#define functor_hpp

#include <stdio.h>
#include "Icallable.h"
#include "typelist.h"
#include "callable.h"

class CEmptyType {};


template <class ResultType, class TypeList>
class  CFunctor {
  
public:
    typedef TypeList ParameterList;
    typedef ResultType ResType;
  
    typedef typename TypeAtNonStrict<TypeList, 0, CEmptyType>::Result Parameter1;
    typedef typename TypeAtNonStrict<TypeList, 1, CEmptyType>::Result Parameter2;
  
    template <typename F>
    CFunctor( const F& f ) :
        callableObject( new CCallable<CFunctor, F>(f) ) { }
  
    ~CFunctor() {
      delete callableObject;
    }
  
    template <typename Function>
    void Fit(const Function& f)
    {
      delete callableObject;
      callableObject = new CCallable<CFunctor, Function>(f);
    }
    
    ResultType operator()() const
    {
        return ( *callableObject )();
    }
    
    ResultType operator()( Parameter1 parameter1 ) const
    {
        return ( *callableObject )( parameter1 );
    }
    
    ResultType operator()( Parameter1 parameter1, Parameter2 parameter2 ) const
    {
        return ( *callableObject )( parameter1, parameter2 );
    }
  
private:
  ICallable <ResultType, TypeList>*  callableObject;
};

#endif /* functor_hpp */
