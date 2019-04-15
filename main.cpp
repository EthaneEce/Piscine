#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

void lancerToutAllegro(int largeur, int hauteur);

int main()
{
    int a =0;

    lancerToutAllegro(400,400);

    BITMAP*perso;
    perso=load_bitmap("persotest.bmp",NULL);
    do{
        draw_sprite(screen,perso,0,0);

    }while(a==0);

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

