#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <string.h>
#include "Graphe.h"

void lancerToutAllegro(int largeur, int hauteur);

int main()
{

    lancerToutAllegro(1900,1000);

    /**BITMAP*perso;
    perso=load_bitmap("persotest.bmp",NULL);
    do{
        draw_sprite(screen,perso,0,0);

    }while(a==0);
    while(!key[KEY_0])
    {int j = 300;
    textprintf_centre_ex(screen,font,100,100,makecol(255,255,0),0,"Valeur de j : %d",j);}
    void line(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
    void rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
    void circlefill(BITMAP *bmp, int x, int y, int radius, int color);
    **/

    Graphe b("txt/manhattan.txt","txt/manhattan_weights_0.txt");
    b.afficher();
    b.afficherallegro();
    while(!key[KEY_SPACE])
    {}



    return 0;
}END_OF_MAIN();

void lancerToutAllegro(int largeur, int hauteur)
{
    /// initialisation générale
    allegro_init();
    /// pour utiliser le clavier
    install_keyboard();
    /// pour utiliser la souris
    install_mouse();
    /// initialisation du MODE GRAPHIQUE
    //on fixe le mode couleur (8, 16, 24 ou 32 bits)
    set_color_depth(desktop_color_depth());
    // on essaie d’ouvrir une fenêtre de largeur*hauteur pixels
    // si l’ouverture échoue on quitte
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,largeur,hauteur,0,0)!=0)
    {
        allegro_message("probleme mode graphique : %s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    /// si on veut afficher le pointeur de souris
    show_mouse(screen);
}

