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
        std::vector<Arrete*> vec;
        std::vector<float>sommes ( g.getsommets ( ).size ( ) , 0 );
        for ( size_t i = 0; i < g.getsommets ( ).size ( ); ++i )
        {
            auto dij = b.dijkstra ( i );
            for ( auto& a : dij )
            {
                sommes [ a.first ] += a.second;
            }
        }

        for ( auto& a : sommes )
            total += a;
        std::cout << total;

    }
    catch ( const std::exception & e )
    {
        std::cerr << e.what ( ) << std::endl;
    }
    std::cin.get ( );
}