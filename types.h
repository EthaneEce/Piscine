#ifndef VarS_H_INCLUDED
#define VarS_H_INCLUDED
#include <iostream>

struct Var
{
public:
    virtual ~Var ( ) = default;
};

struct Integer : public Var
{
    int value;
    Integer ( int v ) : value ( v ) {}
};

struct Float : public Var
{
    float value;
    Float ( const float& v ) : value ( v ) {};
};

struct String : public Var
{
    std::string value;
    String ( const std::string& v ) : value ( v ) {};
};

#endif // VarS_H_INCLUDED