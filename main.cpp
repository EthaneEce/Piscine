#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <string.h>
#include <iomanip>
#include "Graphe.h"
#include "graphisme.h"

void lancerToutAllegro(int largeur, int hauteur);

std::vector<Graphe*> bruteforce(Graphe b);

int main ( )
{

    lancerToutAllegro(1200,800);
    BITMAP*buffer;
    buffer=create_bitmap(SCREEN_W,SCREEN_H);

    Graphe b("txt/broadway.txt","txt/broadway_weights_0.txt");
    FONT* font1= load_font("font/font3.pcx",nullptr,nullptr);

    int choix = menu(buffer,b,font1);


    /*
    //b.afficherallegro(100,100,2);
    std::vector<Graphe*> Ttgraphes = bruteforce(b);
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
    do{}while(!key[KEY_ESC]);*/

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
    std::cin.get ( ); */


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

std::vector<Graphe*> bruteforce(Graphe b)
{
    std::unordered_map<int,Sommet*> Sommetsmap = b.getsommets();
    std::unordered_map<int,Arrete*> Arretesmap = b.getarretes();
    std::vector<Arrete*> Arretesvec;
    std::vector<Graphe*> TtGraphes;

    for(auto it: Arretesmap)
    {
        Arretesvec.push_back(it.second);
    }

    std::unordered_map<int,Arrete*> ArretesN;

    std::vector<int> compteur;

    for (int i=0;i <= Arretesvec.size();i++)
    {
        compteur.push_back(0);
    }

    while(true)
    {
        for(int i=0;i<Arretesvec.size();i++)
        {
            if(compteur[i] == 2)
            {
                compteur[i]=0;
                compteur[i+1]+=1;
            }
        }
        if((compteur[compteur.size()-1] == 1) )
         {
             break;
         }
        for(int i=0;i<Arretesvec.size();i++)
        {
            if(compteur[i] == 1)
            {
                ArretesN.insert( {Arretesvec[i]->getid(),Arretesvec[i]} );
            }
            std::cout<<compteur[i];
        }
        Graphe *a =  new Graphe(Sommetsmap,ArretesN);
        TtGraphes.push_back(a);
        a->afficher();

        compteur[0]+=1;
         std::cout<<std::endl;
         //system("pause");
         ArretesN.clear();
    }

    /**for (i;i<Arretesvec.size();i++)
    {
        j=i+1;
        ArretesN.insert( {Arretesvec[i]->getid(),Arretesvec[i]} );
        Graphe *a =  new Graphe(Sommetsmap,ArretesN);
        a->afficher();
        TtGraphes.push_back(a);
        for(j;j<Arretesvec.size();j++)
        {
            ArretesN.insert( {Arretesvec[j]->getid(),Arretesvec[j]} );
            Graphe *b =  new Graphe(Sommetsmap,ArretesN);
            b->afficher();
            TtGraphes.push_back(b);
        }
        ArretesN.clear();
    }**/

    std::cout<<"fin";

    return TtGraphes;
}


