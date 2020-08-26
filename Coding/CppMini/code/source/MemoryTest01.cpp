#include <iostream>
#include "MemoryTest01.hpp"
#include "LogHelper.hpp"

namespace ClassOperator
{

    template<typename T>
    T *Ctor(void *ptr)
    {
        auto res = new(ptr)T;
        return static_cast<T *>(res);        
    }
    template<typename T>
    void *Destor(T *ptr)
    {
        ptr->T::~T();
        return static_cast<void *>(ptr);
    }

    int TestMain()
    {
        using namespace LogHelper;
        LogClear();
        LogLine("----------------------Begin Test Class Operator new and delete-------------------------");
        LogSpaceLine(2);
        auto *p = new Foo;
        delete p;

        LogSpaceLine();
        LogLine("Global new Call!");
        p = ::new Foo;
        ::delete p;
        LogLine("Global delete Call!");

        LogSpaceLine(2);

        auto pArray = new Foo[3];
        delete[] pArray;

        LogSpaceLine(2);
        LogLine("Global new[] Call!");
        pArray = ::new Foo[3];
        ::delete[] pArray;
        LogLine("Global delete[] Call!");

        LogSpaceLine(2);

        LogLine("Template Ctor Test");
        
        auto pfoo = Ctor<Foo>(malloc(sizeof(Foo)));
        free(Destor<Foo>(pfoo));

        LogSpaceLine(2);
        LogLine("Bad Ctor");
        p = new(1)Foo(1);
        delete p;
        
        return 0;        
    }

    Foo::Foo() : id(0){LogHelper::LogLine("Default Ctor Call!");}
    Foo::Foo(int _id) :id(_id){ throw new std::exception; }
    Foo::~Foo(){LogHelper::LogLine("Foo Destructer Call!");}

    void* Foo::operator new(size_t size)
    {
        Foo *p = (Foo*)malloc(size);
        LogHelper::LogLine("Foo operator new Call!");
        return static_cast<void *>(p);
    }

    void* Foo::operator new(size_t size, void *ptr)
    {
        std::cout << "placement new Call!" << std::endl;
        return ptr;        
    }

    void* Foo::operator new(size_t size, size_t extra)
    {
        return malloc(size + extra * sizeof(Foo));
    }

    void Foo::operator delete(void *ptr)
    {  
        LogHelper::LogLine("operator delete Call!");
        free(ptr);        
        return;
    }

    void  Foo::operator delete(void *ptr, size_t size)
    {
        LogHelper::LogLine("operator delete(size_t) Call!");
        free(ptr);
        return;        
    }

    void* Foo::operator new[](size_t size)
    {
        Foo *p = (Foo*)malloc(size);
        std::cout << "operator new[] Call!" << std::endl;
        return p;        
    }
    void Foo::operator delete[](void *ptr, size_t size)
    {

        std::cout << "operator delete[] Call!" << std::endl;
        free(ptr);
    }
}