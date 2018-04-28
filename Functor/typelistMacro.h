// Автор: Михаил Анухин

#ifndef typelistMacro_h
#define typelistMacro_h

#define TYPELIST_1(T1) CTypeList<T1, CNullTypeList>

#define TYPELIST_2(T1, T2) CTypeList<T1, TYPELIST_1(T2) >

#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >

#endif /* typelistMacro_h */
