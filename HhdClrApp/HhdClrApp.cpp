// HhdClrApp.cpp : main project file.

#include "stdafx.h"



void print_hello()
{
    Console::WriteLine(L"Hello World");
}



ref class ManagedTest
{
public:
    ManagedTest() { Console::WriteLine(L"ManagedTest new 생성자"); }
    ~ManagedTest() { Console::WriteLine(L"~ManagedTest delete 소멸자"); }
    !ManagedTest() { Console::WriteLine(L"!ManagedTest finalize 종료처리"); }
};

void new_delete_finilize()
{
    Console::WriteLine(L"1");
    ManagedTest^ t1 = gcnew ManagedTest();
    delete t1;

    Console::WriteLine(L"2");
    ManagedTest^ t2 = gcnew ManagedTest();
}



ref class ManagedTest2
{
public:
    ManagedTest2() { Console::WriteLine(L"ManagedTest2 new 생성자"); }
    ~ManagedTest2() { Console::WriteLine(L"~ManagedTest2 delete 소멸자"); }

    void Func() { Console::WriteLine(L"~ManagedTest2 func"); }
    int m_nNumber;
};

void stack_variable()
{
    ManagedTest2 obj;
    obj.m_nNumber = 1;
    obj.Func();
}

void gcheap_variable()
{
    ManagedTest2^ pObj = gcnew ManagedTest2();
    pObj->m_nNumber = 2;
    pObj->Func();
}



void print_fileinfo(FileInfo^ finfo)
{
    Console::WriteLine(L"finfo : {0}", finfo->FullName);
}

void print_cur_dir_files()
{
    auto files = Directory::EnumerateFiles(L".");

    for each(auto file in files)
    {
        auto pInfo = gcnew FileInfo(file);
        print_fileinfo(pInfo);
        delete pInfo;
    }
}



void set_ptr_value(interior_ptr<int> pValue)
{
    *pValue = 100;
}

void set_ptr_value_test()
{
    int nValue = 0;
    Console::WriteLine(L"nValue : {0}", nValue);
    set_ptr_value(&nValue);
    Console::WriteLine(L"nValue : {0}", nValue);
}



void string_conv()
{
    const char* szMsg = "abc가나다";
    auto strMsg = marshal_as<String^>(szMsg);
    Console::WriteLine(L"strMsg : {0}", strMsg);

    const wchar_t* wMsg = L"abc가나다";
    auto strMsg2 = marshal_as<String^>(wMsg);
    Console::WriteLine(L"strMsg2 : {0}", strMsg2);

    std::string stdStr = "abc가나다";
    auto strMsg3 = marshal_as<String^>(stdStr);
    Console::WriteLine(L"strMsg3 : {0}", strMsg3);

    std::wstring stdStr2 = L"abc가나다";
    auto strMsg4 = marshal_as<String^>(stdStr2);
    Console::WriteLine(L"strMsg4 : {0}", strMsg4);

    String^ strMsg5 = L"abc가나다";
    std::wstring wMsg2 = marshal_as<std::wstring>(strMsg5);
    ::wprintf(L"wMsg2 : {0}", wMsg2);
}



void buf_conv()
{
    char* pBuf = "abc123!@#";
    auto buf = gcnew array<Byte>(1024);
    System::Runtime::InteropServices::Marshal::Copy((IntPtr)pBuf, buf, 0, 10);
}



void test_list()
{
    List<String^> list;
    list.Add(L"1");
    list.Add(L"2");
    list.Add(L"3");
    list.Add(L"가");
    list.Add(L"나");
    list.Add(L"다");

    for each (auto item in list)
    {
        Console::WriteLine(L"item : {0}", item);
    }
}



class NativeClass
{
public:
    NativeClass() {}
    ~NativeClass() {}

    gcroot<String^> m_str;
};

void test_managed_member_in_native_class()
{
    NativeClass ncObj;
    ncObj.m_str = gcnew String(L"가나다abc");
    Console::WriteLine(L"ncObj.m_str : {0}", ncObj.m_str);
}



int main(array<System::String ^> ^args)
{
    //hello();


    //new_delete_finilize();


    //stack_variable();
    //gcheap_variable();



    //print_cur_dir_files();



    //set_value_test();



    //string_conv();



    //test_list();



    test_managed_member_in_native_class();



    ::getchar();
    return 0;
}