#pragma once
#include "MemoryHeaders.hpp"

namespace ClassOperator
{
    class Foo
    {
    public:
        Foo();
        Foo(int _id);
        virtual ~Foo();

        static void* operator new(size_t size);
        static void* operator new(size_t size, void *ptr);
        static void* operator new(size_t size, size_t extra);

        static void operator delete(void *ptr);
        static void operator delete(void *ptr, size_t size);

        static void* operator new[](size_t size);
        static void operator delete[](void * ptr, size_t size);

        int id;
    };

    int TestMain();
}