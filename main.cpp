#include <iostream>
#include "Graphe.h"
#include <fstream>
#include "svgfile.h"
#include "_graphe.h"

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
        auto sol = g.optimPartielle ( g.bruteforce ( ) , 1 );
        for ( auto& a : sol )
            std::cout << a->getPoidsTotaux ( ) << std::endl;
    }
    catch ( const std::exception & e )
    {
        std::cerr << e.what ( ) << std::endl;
    }
    std::cin.get ( );
}