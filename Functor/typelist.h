// Автор: Михаил Анухин
// Описание: классы, позволяющие работать со списками типов

#ifndef typelist_h
#define typelist_h

template <class H, class T>
class CTypeList {
public:
    typedef H head;
    typedef T tail;
};

//------------------------------------------------------------------------------

class CNullTypeList {};

//------------------------------------------------------------------------------

template <class TList, unsigned int index, typename DefaultType = CNullTypeList>
struct TypeAtNonStrict {
    typedef DefaultType Result;
};

template <class Head, class Tail, typename DefaultType>
struct TypeAtNonStrict<CTypeList<Head, Tail>, 0, DefaultType> {
    typedef Head Result;
};

template <class Head, class Tail, unsigned int i, typename DefaultType>
struct TypeAtNonStrict<CTypeList<Head, Tail>, i, DefaultType> {
    typedef typename TypeAtNonStrict<Tail, i - 1, DefaultType>::Result Result;
};



#endif /* typelist_h */
