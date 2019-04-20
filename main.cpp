#include <iostream>
#include "Graphe.h"
#include "graphisme.h"
#include <fstream>
#include "_Graphe.h"

void lancerToutAllegro(int largeur, int hauteur);

std::ostream& operator<<( std::ostream& out , std::vector<float> vec )
{
    for ( auto& a : vec )
        out << a << " ";
    return out;
}


int main()
{
    lancerToutAllegro(1200,800);
    BITMAP*buffer=create_bitmap(SCREEN_W,SCREEN_H);
    Graphe b("txt/broadway.txt","txt/broadway_weights_0.txt");
    FONT* font1= load_font("font/font3.pcx",nullptr,nullptr);
    FONT* titre = load_font("font/Peignot.pcx",nullptr,nullptr);

    int choix = menu(buffer,b,font1,titre);

    return 0;
}END_OF_MAIN();

void lancerToutAllegro(int largeur, int hauteur)
{
    /// initialisation g�n�rale
    allegro_init();
    /// pour utiliser le clavier
    install_keyboard();
    /// pour utiliser la souris
    install_mouse();
    /// initialisation du MODE GRAPHIQUE
    //on fixe le mode couleur (8, 16, 24 ou 32 bits)
    set_color_depth(desktop_color_depth());
    // on essaie d�ouvrir une fen�tre de largeur*hauteur pixels
    // si l�ouverture �choue on quitte
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,largeur,hauteur,0,0)!=0)
    {
        allegro_message("probleme mode graphique : %s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    /// si on veut afficher le pointeur de souris
    show_mouse(screen);
}
