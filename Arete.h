#ifndef Arete_H
#define Arete_H
#include <iostream>
#include <vector>
#include "svgfile.h"

class Arete
{
public:
    Arete ( int id , int s1 , int s2 , std::vector<float> Cout );
    Arete ( const size_t nbCouts );
    ~Arete ( ) = default;
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

#endif // Arete_H
