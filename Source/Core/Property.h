#pragma once

#define PROPERTY(Type, Name) \
private:\
    Type Name;

#define PROPERTY_R(Type, Name) \
private:\
    Type Name; \
public: \
    inline const Type & Get##Name() const { return Name; } \
private:

#define PROPERTY_W(Type, Name) \
private:\
    Type Name; \
public: \
    inline void Set##Name(const Type &value) { Name = value; } \
private:

#define PROPERTY_RW(Type, Name) \
private:\
    Type Name; \
public: \
    inline const Type & Get##Name() const { return Name; } \
    inline void Set##Name(const Type &value) { Name = value; } \
private:
