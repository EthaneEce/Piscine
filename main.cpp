#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <string.h>
#include <iomanip>
#include "Graphe.h"


int main ( )
{

    lancerToutAllegro(1900,1000);

    /**BITMAP*perso;
    perso=load_bitmap("persotest.bmp",NULL);
    do{
        draw_#include <iostream>
#include <iomanip>sprite(screen,perso,0,0);

    }while(a==0);
    while(!key[KEY_0])
    {int j = 300;
    textprintf_centre_ex(screen,font,100,100,makecol(255,255,0),0,"Valeur de j : %d",j);}
    void line(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
    void rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
    void circlefill(BITMAP *bmp, int x, int y, int radius, int color);
    **/

    Graphe b("txt/cubetown.txt","txt/cubetown_weights_0.txt");
    b.afficher();
    b.afficherallegro();

    do{}while(!key[KEY_ESC]);


    Graphe b ( "txt/broadway.txt" , "txt/broadway_weights_0.txt" );
    std::vector<Arrete*> vec = b.Kruskal ( 0 );
    for ( auto& a : vec )
        a->afficherData ( );
    b.afficher ( );
    std::cin.get ( );

    return 0;
}


