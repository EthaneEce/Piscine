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
    Graphe b ( "txt/broadway.txt" , "txt/broadway_weights_0.txt" );

    auto bf = b.bruteforce ( );
    auto par = b.Pareto ( bf );
    for ( auto& a : par )
        std::cout << a->poidsTotaux ( ) << std::endl;
    std::cin.get ( );
}


