#pragma once
#include <Windows.h>
#include <mutex>
#include <string>
#include <iostream>
#include "NativeTypes.h"
#include "scrNativeHandler.h"

typedef UINT64 Address;
typedef UINT64 HASH;

typedef void* (*RageFunction)(rage::scrNativeCallContext* context);

HASH HashString(const std::string& functionName);
uint64_t FindFunctionAddress(const HASH functionHash);

Vector3* GetVector();
void DeleteVector(Vector3 * vector);
float ToFloat(UINT32 value);

Ped Call_PLAYER_PED_ID();

uintptr_t* GetEntityStruct(Entity entity);
size_t GetAllEntities(Entity* arrayOfEntities, size_t size);
size_t GetAllPeds(Ped* arrayOfPeds, size_t size);
size_t GetAllVehicles(Vehicle* arrayOfVehicles, size_t size);
size_t GetAllObjects(Object* arrayOfObjects, size_t size);

void NativeReset();
void NativePush(void* arg);
void* NativeCall(UINT64 FunctionAddress);

std::mutex& GetCallMutex();

bool InitNativeCaller();



template <typename R>
R Call(HASH FunctionHash)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();
        return (R)NativeCall(Address);
    }
    /* Need to add terminate this script function */

    return (R)0;
}

template<typename R, typename T1>
R Call(HASH FunctionHash, T1 p1)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();
        NativePush(*(void**)&p1);
        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2>
R Call(HASH FunctionHash, T1 p1, T2 p2)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();
        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();
        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();
        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);

        return (R)NativeCall(Address);
    }

    return (R)0;
}
template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);
        NativePush(*(void**)&p24);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);
        NativePush(*(void**)&p24);
        NativePush(*(void**)&p25);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);
        NativePush(*(void**)&p24);
        NativePush(*(void**)&p25);
        NativePush(*(void**)&p26);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);
        NativePush(*(void**)&p24);
        NativePush(*(void**)&p25);
        NativePush(*(void**)&p26);
        NativePush(*(void**)&p27);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);
        NativePush(*(void**)&p24);
        NativePush(*(void**)&p25);
        NativePush(*(void**)&p26);
        NativePush(*(void**)&p27);
        NativePush(*(void**)&p28);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28, T29 p29)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);
        NativePush(*(void**)&p24);
        NativePush(*(void**)&p25);
        NativePush(*(void**)&p26);
        NativePush(*(void**)&p27);
        NativePush(*(void**)&p28);
        NativePush(*(void**)&p29);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28, T29 p29, T30 p30)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);
        NativePush(*(void**)&p24);
        NativePush(*(void**)&p25);
        NativePush(*(void**)&p26);
        NativePush(*(void**)&p27);
        NativePush(*(void**)&p28);
        NativePush(*(void**)&p29);
        NativePush(*(void**)&p30);

        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28, T29 p29, T30 p30, T31 p31)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);
        NativePush(*(void**)&p24);
        NativePush(*(void**)&p25);
        NativePush(*(void**)&p26);
        NativePush(*(void**)&p27);
        NativePush(*(void**)&p28);
        NativePush(*(void**)&p29);
        NativePush(*(void**)&p30);
        NativePush(*(void**)&p31);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
R Call(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28, T29 p29, T30 p30, T31 p31, T32 p32)
{
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        std::lock_guard<std::mutex> lock(GetCallMutex());
        NativeReset();

        NativePush(*(void**)&p1);
        NativePush(*(void**)&p2);
        NativePush(*(void**)&p3);
        NativePush(*(void**)&p4);
        NativePush(*(void**)&p5);
        NativePush(*(void**)&p6);
        NativePush(*(void**)&p7);
        NativePush(*(void**)&p8);
        NativePush(*(void**)&p9);
        NativePush(*(void**)&p10);
        NativePush(*(void**)&p11);
        NativePush(*(void**)&p12);
        NativePush(*(void**)&p13);
        NativePush(*(void**)&p14);
        NativePush(*(void**)&p15);
        NativePush(*(void**)&p16);
        NativePush(*(void**)&p17);
        NativePush(*(void**)&p18);
        NativePush(*(void**)&p19);
        NativePush(*(void**)&p20);
        NativePush(*(void**)&p21);
        NativePush(*(void**)&p22);
        NativePush(*(void**)&p23);
        NativePush(*(void**)&p24);
        NativePush(*(void**)&p25);
        NativePush(*(void**)&p26);
        NativePush(*(void**)&p27);
        NativePush(*(void**)&p28);
        NativePush(*(void**)&p29);
        NativePush(*(void**)&p30);
        NativePush(*(void**)&p31);
        NativePush(*(void**)&p32);


        return (R)NativeCall(Address);
    }

    return (R)0;
}

template <typename R>
R FastCall(HASH FunctionHash)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}

template <typename R, typename T1>
R FastCall(HASH FunctionHash, T1 p1)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2>
R FastCall(HASH FunctionHash, T1 p1, T2 p2)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17 >
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        context.PushArg(p24);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        context.PushArg(p24);
        context.PushArg(p25);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        context.PushArg(p24);
        context.PushArg(p25);
        context.PushArg(p26);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        context.PushArg(p24);
        context.PushArg(p25);
        context.PushArg(p26);
        context.PushArg(p27);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        context.PushArg(p24);
        context.PushArg(p25);
        context.PushArg(p26);
        context.PushArg(p27);
        context.PushArg(p28);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28, T29 p29)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        context.PushArg(p24);
        context.PushArg(p25);
        context.PushArg(p26);
        context.PushArg(p27);
        context.PushArg(p28);
        context.PushArg(p29);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28, T29 p29, T30 p30)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        context.PushArg(p24);
        context.PushArg(p25);
        context.PushArg(p26);
        context.PushArg(p27);
        context.PushArg(p28);
        context.PushArg(p29);
        context.PushArg(p30);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28, T29 p29, T30 p30, T31 p31)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        context.PushArg(p24);
        context.PushArg(p25);
        context.PushArg(p26);
        context.PushArg(p27);
        context.PushArg(p28);
        context.PushArg(p29);
        context.PushArg(p30);
        context.PushArg(p31);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}
template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
R FastCall(HASH FunctionHash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22, T23 p23, T24 p24, T25 p25, T26 p26, T27 p27, T28 p28, T29 p29, T30 p30, T31 p31, T32 p32)
{
    rage::scrNativeCallContext context;
    uint64_t ArgsStack[32] = { 0 };
    Address Address;

    Address = FindFunctionAddress(FunctionHash);

    if (Address) {
        context.m_ReturnValue = ArgsStack;
        context.m_Args = ArgsStack;
        context.reset();
        context.PushArg(p1);
        context.PushArg(p2);
        context.PushArg(p3);
        context.PushArg(p4);
        context.PushArg(p5);
        context.PushArg(p6);
        context.PushArg(p7);
        context.PushArg(p8);
        context.PushArg(p9);
        context.PushArg(p10);
        context.PushArg(p11);
        context.PushArg(p12);
        context.PushArg(p13);
        context.PushArg(p14);
        context.PushArg(p15);
        context.PushArg(p16);
        context.PushArg(p17);
        context.PushArg(p18);
        context.PushArg(p19);
        context.PushArg(p20);
        context.PushArg(p21);
        context.PushArg(p22);
        context.PushArg(p23);
        context.PushArg(p24);
        context.PushArg(p25);
        context.PushArg(p26);
        context.PushArg(p27);
        context.PushArg(p28);
        context.PushArg(p29);
        context.PushArg(p30);
        context.PushArg(p31);
        context.PushArg(p32);
        return (R)((RageFunction)Address)(&context);
    }

    return (R)0;
}