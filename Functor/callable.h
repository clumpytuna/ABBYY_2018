// Автор: Михаил Анухин
// Описание: Класс определяет интерфейс callable объекта

#ifndef functorHandler_h
#define functorHandler_h

template <class ParentFunctor,  typename Functor>
class CCallable: public ICallable< typename ParentFunctor::ResType,
                                   typename ParentFunctor::ParameterList > {
public:
    typedef typename ParentFunctor::ResType ResultType;
    CCallable( const Functor& functor_ ) : functor( functor_ ) {}
    
    
    ResultType operator()() const {
        return functor();
    }
    
    ResultType operator()( typename ParentFunctor::Parameter1 parameter1 ) const {
        return functor( parameter1 );
    }
    
    ResultType operator()( typename ParentFunctor::Parameter1 parameter1,
                           typename ParentFunctor::Parameter2 parameter2 ) const {
        return functor( parameter1, parameter2 );
    }
private:
    Functor functor;
};

#endif /* functorHandler_h */
