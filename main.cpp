#include <iostream>
#include "Graphe.h"

void lancerToutAllegro(int largeur, int hauteur);


std::ostream& operator<<( std::ostream& out , std::vector<float> vec )
{
    for ( auto& a : vec )
        out << a << " ";
    return out;
}

int main()
{
    size_t lng = 1200,lrg =800;
    lancerToutAllegro(lng,lrg);
    BITMAP*buffer;
    buffer=create_bitmap(lng,lrg+10000);

            circlefill ( buffer , 1000, 100 , 100 , makecol ( 255 , 0 , 0 ) );


    Graphe b("txt/manhattan.txt","txt/manhattan_weights_0.txt");
    //b.afficherallegro(buffer,100,100,2);

    b.afficherallegrotout(buffer,0, 0,5) ;

    int x=0;
    int y=0;


    draw_sprite(screen,buffer,0,0);
    do{
    if((key[KEY_DOWN]))
    {

            y+=800;
            std::cout << y<<","<<std::endl;
            blit(buffer,screen,x,y,0,0,lng,lrg);
            rest(100);

    }
    if((key[KEY_UP]))
    {

            y-=800;
            std::cout << y<<","<<std::endl;
            blit(buffer,screen,x,y,0,0,lng,lrg);
            rest(100);

    }



    }while(!key[KEY_ESC]);

    auto par = b.Pareto ( b.bruteforce ( 1 ) );
    for ( auto& a : par )
    std::cout << a->poidsTotaux ( ) << std::endl;
    //system("pause");


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



