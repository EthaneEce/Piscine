#include "Arrete.h"

Arrete::Arrete ( int id , int s1 , int s2 , std::vector<float> Cout )
    :m_id ( id ) , m_s1 ( s1 ) , m_s2 ( s2 ) , m_Cout ( Cout )
{}

Arrete::~Arrete ( )
{
    //dtor
}

void Arrete::afficherData ( ) const {
    std::cout
        << "Arrete " << m_id
        << " : " << std::endl <<
        "Sommets(" << m_s1
        << "," << m_s2 << ")"
        << std::endl
        << "Couts : ";
    for ( auto it : m_Cout )
    {
        std::cout << it << ", ";
    }
    std::cout << std::endl << std::endl;
}

int Arrete::getid ( )const
{
    return m_id;
}

int Arrete::gets1 ( )const
{
    return m_s1;
}
int Arrete::gets2 ( )const
{
    return m_s2;
}
std::vector<float> Arrete::getcout ( )const
{
    return m_Cout;
}

