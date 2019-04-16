#include "Arrete.h"


template<typename T>
Arrete<T>::Arrete ( int id , int s1 , int s2 , std::vector<T> Cout )
    :m_id ( id ) , m_s1 ( s1 ) , m_s2 ( s2 ) , m_Cout ( Cout )
{}


template<typename T>
void Arrete<T>::afficherData ( ) const {
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
template<typename T>
int Arrete<T>::getid ( )const
{
    return m_id;
}
template<typename T>
int Arrete<T>::gets1 ( )const
{
    return m_s1;
}
template<typename T>
int Arrete<T>::gets2 ( )const
{
    return m_s2;
}
template<typename T>
std::vector<T> Arrete<T>::getcout ( )const
{
    return m_Cout;
}

