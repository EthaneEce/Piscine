#include <iostream>
#include "Graphe.h"

int main ( )
{

    Graphe b ( "txt/broadway.txt" , "txt/broadway_weights_0.txt" );
    b.afficher ( );
    std::cin.get ( );
    return 0;
}



