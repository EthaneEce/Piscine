#include <iostream>
#include "Graphe.h"
#include <fstream>
#include "_Graphe.h"
#include "svgfile.h"


std::ostream& operator<<( std::ostream& out , std::vector<float> vec )
{
    for ( auto& a : vec )
        out << a << " ";
    return out;
}


int main ( )
{
    try
    {
        Graphe g ( "txt\\broadway.txt" , "txt\\broadway_weights_0.txt" );

        //Optimisation Partielle (Parie 3)
        auto sol = g.optimPartielle ( g.bruteforce ( 2 ) , 1 );
        for ( auto& a : sol )
            std::cout << a->getPoidsTotaux ( ) << std::endl;

        //Optimisation Bi Objectif (Partie2)
        auto sol1 = g.optimBiObj ( g.bruteforce ( 1 ) );
        for ( auto& a : sol1 )
            std::cout << a->getPoidsTotaux ( ) << std::endl;

    }
    catch ( const std::exception & e )
    {
        std::cerr << e.what ( ) << std::endl;
    }
    std::cin.get ( );
}