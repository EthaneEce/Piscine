#include <iostream>
#include "Graphe.h"


int main ( )
{
    Graphe b ( "txt/triville.txt" , "txt/triville_weights_0.txt" );
    std::cin.get ( );

    auto sol = b.Kruskal ( );
    Graphe g ( b.getsommets ( ) , sol );
    auto vec = g.poidsTotaux ( );
    std::cin.get ( );
}


