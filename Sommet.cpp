#include "sommet.h"
#include "iomanip"

Sommet::Sommet ( int id , double x , double y ) :m_id { id } , m_x { x } , m_y { y }
{}

int Sommet::getid ( )const
{
    return m_id;
}

double Sommet::gety ( )const
{
    return m_x;
}

double Sommet::getx ( )const
{
    return m_y;
}

void Sommet::afficherData ( ) const {
    std::cout << "    " << m_id << " : " << "(x,y)=(" << m_x << "," << m_y << ")" << std::endl;
}

Sommet::~Sommet ( )
{
    //dtor
}
