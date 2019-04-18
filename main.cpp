#include <iostream>
#include "Graphe.h"

void lancerToutAllegro(int largeur, int hauteur);

std::ostream& operator<<( std::ostream& out , std::vector<float> vec )
{
    size_t lng = 1200,lrg =800;
    lancerToutAllegro(lng,lrg);
    BITMAP*buffer;
    buffer=create_bitmap(lng,lrg+10000);

            circlefill ( buffer , 1000, 100 , 100 , makecol ( 255 , 0 , 0 ) );


    Graphe b("txt/triville.txt","txt/triville_weights_0.txt");
    //b.afficherallegro(buffer,100,100,2);
    //std::vector<std::vector<bool>> Ttgraphes = b.bruteforce(1);
    //int k=0,l=0;

    b.afficherallegrotout(buffer,0, 0,5) ;

    /**for ( int j = 5; j >= -5; j-- )
    {
            for ( int i = -5; i <= 5; i++ )
            {
                fastline ( buffer , (100 - i) , (100 - i), (200 + j) , (200 + j) , makecol ( 255 , 255 , 255 ) );
                fastline ( buffer , (200 + j) , (200 + j) ,(100 - i) , (100 - i) , makecol ( 255 , 255 , 255 ) );
            }
    }**/


    /**for(auto it:Ttgraphes)
    {
        it->afficherallegro(buffer,i,j,2);
        i+=150;
        if (i >= 1500)
        {
            j+=150;
            i=0;
        }
    }**/

    int x=0;
    int y=0;


    draw_sprite(screen,buffer,0,0);
    do{
    if((key[KEY_DOWN]))
    {

            y+=800;
            std::cout << y<<",";
            blit(buffer,screen,x,y,0,0,lng,lrg);
            rest(100);

    }
    if((key[KEY_UP]))
    {

            y-=800;
            std::cout << y<<",";
            blit(buffer,screen,x,y,0,0,lng,lrg);
            rest(100);

    }

    Graphe b ( "txt/triville.txt" , "txt/triville_weights_0.txt" );
    auto par = b.Pareto ( b.bruteforce ( 1 ) );
    for ( auto& a : par )
    std::cout << a->poidsTotaux ( ) << std::endl;
    system("pause");

    }while(!key[KEY_ESC]);

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

    //std::cout << Ttgraphes.size();
    //do{}while(!key[KEY_ESC]);

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



