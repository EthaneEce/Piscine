#include <iostream>
#include "Graphe.h"


int main ( )
{

    Graphe b ( "txt/broadway.txt" , "txt/broadway_weights_0.txt" );
    std::vector<Arrete*> vec = b.Kruskal ( 0 );
    for ( auto& a : vec )
        a->afficherData ( );
    b.afficher ( );
    std::cin.get ( );

    return 0;
}


