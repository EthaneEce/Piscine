#include <iostream>
#include "Graphe.h"


int main ( )
{
    Graphe b ( "txt/triville.txt" , "txt/triville_weights_0.txt" );
    std::cin.get ( );

    b.Kruskal ( );
    std::cin.get ( );
}


