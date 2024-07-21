#ifndef UTIL_TYPELIST_HH
#define UTIL_TYPELIST_HH

// shamelessly stolen from Alexandrescu, CUJ Experts Forum, Feb 2002

#define UTIL_TYPELIST(a) ::util::cons< void (*)a >::type

namespace util {


  template <class H, class T>
  struct typelist
  {
    typedef H head;
    typedef T tail;
  };

  struct null_typelist { };

  template<typename T> struct length;

  template <> struct length<null_typelist>
  {
    enum { value = 0 };
  };

  template<typename H, typename T> struct length< typelist<H, T> >
  {
    enum { value = 1 + length<T>::value };
  };


  template <class Fun> struct cons;

  template <class T> struct cons<void (*)(T)>
  {
    typedef typelist<T, null_typelist> type;
  };

  // perl -e 'for (2..50) { @t=map("T$_",1..$_); @tl=map("typelist<$_",@t);@c=map("class $_", @t); print "  template<",join(", ", @c),">\n  struct cons<void (*)(",join(", ", @t),")>\n  {\n    typedef ",join(", ",@tl),", null_typelist",("> ")x@t,"type;\n  };\n" }'

  template<class T1, class T2>
  struct cons<void (*)(T1, T2)>
  {
    typedef typelist<T1, typelist<T2, null_typelist> > type;
  };
  template<class T1, class T2, class T3>
  struct cons<void (*)(T1, T2, T3)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, null_typelist> > > type;
  };
  template<class T1, class T2, class T3, class T4>
  struct cons<void (*)(T1, T2, T3, T4)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, null_typelist> > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5>
  struct cons<void (*)(T1, T2, T3, T4, T5)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, null_typelist> > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, null_typelist> > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, null_typelist> > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, null_typelist> > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, null_typelist> > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, null_typelist> > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, null_typelist> > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, null_typelist> > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, null_typelist> > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, null_typelist> > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, null_typelist> > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, null_typelist> > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, null_typelist> > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, null_typelist> > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, null_typelist> > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, null_typelist> > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, null_typelist> > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, null_typelist> > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, null_typelist> > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41, class T42>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, typelist<T42, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41, class T42, class T43>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, typelist<T42, typelist<T43, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41, class T42, class T43, class T44>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, typelist<T42, typelist<T43, typelist<T44, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41, class T42, class T43, class T44, class T45>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, typelist<T42, typelist<T43, typelist<T44, typelist<T45, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41, class T42, class T43, class T44, class T45, class T46>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, typelist<T42, typelist<T43, typelist<T44, typelist<T45, typelist<T46, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41, class T42, class T43, class T44, class T45, class T46, class T47>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, typelist<T42, typelist<T43, typelist<T44, typelist<T45, typelist<T46, typelist<T47, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41, class T42, class T43, class T44, class T45, class T46, class T47, class T48>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, typelist<T42, typelist<T43, typelist<T44, typelist<T45, typelist<T46, typelist<T47, typelist<T48, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41, class T42, class T43, class T44, class T45, class T46, class T47, class T48, class T49>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, typelist<T42, typelist<T43, typelist<T44, typelist<T45, typelist<T46, typelist<T47, typelist<T48, typelist<T49, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };
  template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16, class T17, class T18, class T19, class T20, class T21, class T22, class T23, class T24, class T25, class T26, class T27, class T28, class T29, class T30, class T31, class T32, class T33, class T34, class T35, class T36, class T37, class T38, class T39, class T40, class T41, class T42, class T43, class T44, class T45, class T46, class T47, class T48, class T49, class T50>
  struct cons<void (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, T50)>
  {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8, typelist<T9, typelist<T10, typelist<T11, typelist<T12, typelist<T13, typelist<T14, typelist<T15, typelist<T16, typelist<T17, typelist<T18, typelist<T19, typelist<T20, typelist<T21, typelist<T22, typelist<T23, typelist<T24, typelist<T25, typelist<T26, typelist<T27, typelist<T28, typelist<T29, typelist<T30, typelist<T31, typelist<T32, typelist<T33, typelist<T34, typelist<T35, typelist<T36, typelist<T37, typelist<T38, typelist<T39, typelist<T40, typelist<T41, typelist<T42, typelist<T43, typelist<T44, typelist<T45, typelist<T46, typelist<T47, typelist<T48, typelist<T49, typelist<T50, null_typelist> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > type;
  };

}

#endif // UTIL_TYPELIST_HH
