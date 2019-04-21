#include <iostream>
#include "Graphe.h"
#include <fstream>
#include "_Graphe.h"


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
        Graphe g ( "txt\\manhattan.txt" , "txt\\manhattan_weights_1.txt" );


        //Optimisation Bi Objectif (Partie2)
        auto sol1 = g.optimBiObj ( g.bruteforce ( 1 ) );
        for ( auto& a : sol1 )
            std::cout << a->getPoidsTotaux ( ) << std::endl;


        //Optimisation Partielle (Parie 3)
        auto sol = g.optimPartielle ( g.bruteforce ( 2 ) , 1 );
        std::cout << sol.size ( ) << std::endl;
        for ( auto& a : sol )
            std::cout << a->getPoidsTotaux ( ) << std::endl;


    }
    catch ( const std::exception & e )
    {
        std::cerr << e.what ( ) << std::endl;
    }
    std::cin.get ( );
}