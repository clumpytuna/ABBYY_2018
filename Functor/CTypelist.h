// Автор: Михаил Анухин
// Описание: Файл содержит класс список типов и некоторые функции для работы с ним.

#ifndef typelist_h
#define typelist_h


// Обертки для списка параметров
// Использовать следующим образом (пример для функции с двумя параметрами):
// CFunctor<void, TYPELIST_2(int, double)> f(&function)

#define TYPELIST_1(T1) CTypeList<T1, NullType>
#define TYPELIST_2(T1, T2) CTypeList<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >

// Лист типов, в нем можно хранить типы в явном виде
template <class H, class T>
class CTypeList {
public:
    typedef H head;
    typedef T tail;
};

////////////////////////////////////////////////////////////////////////////////
// Пустой элемент списка
class NullType {};

////////////////////////////////////////////////////////////////////////////////
// Данная конструкция позволяет нам получать доступ к списку типов поэлементно.
// Первым параметром в шаблон передается TypeList, вторым передается индекс элемента,
// третьим всегда передается тип, возращаемый по умолчанию
// Пример использования:
// typedef typename GetTypeAt<TypeList, 1, NullType>::Result FirstParameterType;
// теперь FirstParameterType - это второй элемент TypeList
template <class TList, unsigned int index, typename DefaultType = NullType>
class GetTypeAt{
public:
    typedef DefaultType Result;
};

// Помещает в Result первый параметр списка
template <class Head, class Tail, typename DefaultType>
class GetTypeAt<CTypeList<Head, Tail>, 0, DefaultType> {
public:
    typedef Head Result;
};

// Помещает в Result i-ый параметр списка. Если длина списка меньше,
// чем индекс, к которому мы обращаемся, то в Result будет помещен.
// Работает за O(n), однако все операции происходят во время компиляции
template <class Head, class Tail, unsigned int i, typename DefaultType>
class GetTypeAt<CTypeList<Head, Tail>, i, DefaultType> {
public:
    typedef typename GetTypeAt<Tail, i - 1, DefaultType>::Result Result;
};

#endif /* typelist_h */
