#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iomanip>
#include "Graphe.h"

int main ( )
{

    Graphe b ( "txt/cubetown.txt" , "txt/cubetown_weights_0.txt" );
    b.afficher ( );
    return 0;
}

