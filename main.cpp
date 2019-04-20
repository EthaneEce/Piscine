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
        Graphe g ( "txt\\broadway.txt" , "txt\\broadway_weights_0.txt" );
        _Graphe b ( g , 1 );
        float total = 0.0f;
        for ( int i = 0; i < g.getsommets ( ).size ( ); ++i )
            for ( auto& a : b.dijkstra ( i ) ) {
                total += a.second;
            }
        std::cout << total;

    }
    catch ( const std::exception & e )
    {
        std::cerr << e.what ( ) << std::endl;
    }
    std::cin.get ( );
}