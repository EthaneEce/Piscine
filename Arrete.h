#ifndef ARRETE_H
#define ARRETE_H
#include <iostream>
#include <vector>
#include "svgfile.h"
class Arrete
{
public:
    Arrete ( int id , int s1 , int s2 , std::vector<float> Cout );
    Arrete (const size_t nbCouts );
    ~Arrete ( ) = default;
    void afficherData ( ) const;
    int getid ( ) const;
    int gets1 ( ) const;
    int gets2 ( ) const;
    std::vector<float> getcout ( ) const;

protected:
private:
    int m_id;
    int m_s1 , m_s2;
    std::vector <float> m_Couts;
};

#endif // ARRETE_H
