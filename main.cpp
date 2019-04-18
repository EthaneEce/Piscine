#include <iostream>
#include "Graphe.h"
#include <fstream>

std::ostream& operator<<( std::ostream& out , std::vector<float> vec )
{
    for ( auto& a : vec )
        out << a << " ";
    return out;
}

int main ( )
{
    std::ifstream ifs ( "fichier.txt" );
    Graphe b ( "txt/manhattan.txt" , "txt/manhattan_weights_0.txt" );

    auto par = b.Pareto ( b.bruteforce ( ) );
    std::cout << par.size ( ) << std::endl;
    for ( auto& a : par )
        std::cout << a->poidsTotaux ( ) << std::endl;
    std::cin.get ( );
}


