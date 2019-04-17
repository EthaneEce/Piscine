#include <iostream>
#include "Graphe.h"


std::ostream& operator<<( std::ostream& out , std::vector<float> vec )
{
    for ( auto& a : vec )
        out << a << " ";
    return out;
}
int main ( )
{
    Graphe b ( "txt/triville.txt" , "txt/triville_weights_0.txt" );
    auto par = b.Pareto ( b.bruteforce ( ) );
    for ( auto& a : par )
        std::cout << a->poidsTotaux ( ) << std::endl;
    std::cin.get ( );
}


