#include <iostream>
#include "Graphe.h"
#include <fstream>
#include "svgfile.h"
std::ostream& operator<<( std::ostream& out , std::vector<float> vec )
{
    for ( auto& a : vec )
        out << a << " ";
    return out;
}

int main ( )
{
    Svgfile svg;
    Graphe g ( "txt\\triville.txt" , "txt\\triville_weights_1.txt" );
    Graphe b ( g.getsommets ( ) , g.Kruskal ( 0 ) );
    b.dessiner ( svg );
    std::cin.get ( );
}


