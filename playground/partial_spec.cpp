#include <iostream>

#ifdef ERROR

template <bool, typename T>
struct hoge
{};

template <bool, typename T>
struct hoge<true, T>
{};

#else

template <bool, bool, typename T>
struct hoge
{};

template <bool b, typename T>
struct hoge<true, b, T>
{};

#endif
