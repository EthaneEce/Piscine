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
        Svgfile svg;
        Graphe g ( "txt\\cubetown.txt" , "txt\\cubetown_weights_0.txt" );
        _Graphe b ( g );
        for ( auto& a : b.dijkstra ( 1 ) ) {
            std::cout << "Sommet " << a.first << ", distance " << a.second << std::endl;
        }

    }
    catch ( const std::exception & e )
    {
        std::cerr << e.what ( ) << std::endl;
    }
    std::cin.get ( );
}