#include "Arete.h"
#include <limits>

Arete::Arete ( int id , int s1 , int s2 , std::vector<float> Cout )
    :m_id ( id ) , m_s1 ( s1 ) , m_s2 ( s2 ) , m_Couts ( Cout )
{}

Arete::Arete ( const size_t nbCouts ) : m_id ( 0 ) , m_s1 ( 0 ) , m_s2 ( 0 )
{
    const constexpr float infinity = std::numeric_limits<float>::max ( );
    m_Couts = std::vector<float> ( nbCouts , infinity );
}


void Arete::afficherData ( ) const {
    std::cout
        << "Arete " << m_id
        << " : " << std::endl <<
        "Sommets(" << m_s1
        << "," << m_s2 << ")"
        << std::endl
        << "Couts : ";
    for ( auto it : m_Couts )
    {
        std::cout << it << ", ";
    }
    std::cout << std::endl << std::endl;
}
int Arete::getid ( )const
{
    return m_id;
}
int Arete::gets1 ( )const
{
    return m_s1;
}
int Arete::gets2 ( )const
{
    return m_s2;
}
std::vector<float> Arete::getcout ( )const
{
    return m_Couts;
}


