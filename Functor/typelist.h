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
class TypeAtNonStrict {

public:
    typedef DefaultType Result;
};

template <class Head, class Tail, typename DefaultType>
class TypeAtNonStrict<CTypeList<Head, Tail>, 0, DefaultType> {

public:
    typedef Head Result;
};

template <class Head, class Tail, unsigned int i, typename DefaultType>
class TypeAtNonStrict<CTypeList<Head, Tail>, i, DefaultType> {

public:
    typedef typename TypeAtNonStrict<Tail, i - 1, DefaultType>::Result Result;
};



#endif /* typelist_h */
