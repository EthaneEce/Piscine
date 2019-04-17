#include <iostream>
#include "Graphe.h"

void lancerToutAllegro(int largeur, int hauteur);

int main ( )
{

    size_t lng = 1200,lrg =800;
    lancerToutAllegro(lng,lrg);
    BITMAP*buffer;
    buffer=create_bitmap(lng,lrg);

    Graphe b("txt/broadway.txt","txt/broadway_weights_0.txt");
    //b.afficherallegro(100,100,2);
    std::vector<Graphe*> Ttgraphes = b.bruteforce();
    int i=0,j=0;
    for(auto it:Ttgraphes)
    {
        it->afficherallegro(buffer,i,j,2);
        i+=150;
        if (i >= 1500)
        {
            j+=150;
            i=0;
        }
    }
    draw_sprite(screen,buffer,0,0);
    do{}while(!key[KEY_ESC]);

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

    //Graphe b("txt/cubetown.txt","txt/cubetown_weights_0.txt");
    //b.afficher();
    //b.afficherallegro();

    //do{}while(!key[KEY_ESC]);

    //std::vector<Graphe*> Ttgraphes = bruteforce(b);


    /**Graphe p (b.getSommets(),b.Kruskal(0));
    p.afficherallegro(500,100,2);
    do{}while(!key[KEY_ESC]);**/

    //Graphe p (b.getSommets(),b.Kruskal(0));
    //p.afficherallegro();

/*
    Graphe c ( "txt/broadway.txt" , "txt/broadway_weights_0.txt" );

    std::unordered_map<int,Arrete*> vec = c.Kruskal ( 0 );
    for ( auto& a : vec )
        a.second->afficherData ( );
    b.afficher ( );
    auto sol = b.bruteforce ( );
    return 0;
    */
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



