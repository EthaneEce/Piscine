#include "graphisme.h"

int menu(BITMAP* buffer, Graphe& a, FONT* font1, FONT* titre)
{
    std::string fichier1;
    int broadway = 0,cubetown = 0,manhattan = 0,triville = 0;
    BITMAP* fond = load_bitmap("Images/fond.bmp",nullptr);
    draw_sprite(screen,fond,0,0);
    do
    {
        draw_sprite(buffer,fond,0,0);
        textout_centre_ex(buffer,titre,"Selection du graphe",SCREEN_W/2,3*SCREEN_H/10,makecol(0,0,0),makecol(255,0,255));
        broadway = draw_bouton(  SCREEN_W/10,6*SCREEN_H/10,2.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Broadway",font1,buffer);
        cubetown = draw_bouton(3*SCREEN_W/10,6*SCREEN_H/10,4.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Cubetown",font1,buffer);
        manhattan= draw_bouton(5*SCREEN_W/10,6*SCREEN_H/10,6.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Manhattan",font1,buffer);
        triville = draw_bouton(7*SCREEN_W/10,6*SCREEN_H/10,8.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Triville",font1,buffer);

        draw_sprite(screen,buffer,0,0);

        if (broadway == 1)
        {
            choixPoids(buffer,fond,font1,titre,"txt/broadway.txt",a,3);
            draw_sprite(screen,fond,0,0);
        }
        if (cubetown == 1)
        {
            choixPoids(buffer,fond,font1,titre,"txt/cubetown.txt",a,1);
            draw_sprite(screen,fond,0,0);
        }
        if (manhattan == 1)
        {
            choixPoids(buffer,fond,font1,titre,"txt/manhattan.txt",a,3);
            draw_sprite(screen,fond,0,0);
        }
        if (triville == 1)
        {
            choixPoids(buffer,fond,font1,titre,"txt/triville.txt",a,2);
            draw_sprite(screen,fond,0,0);
        }
    }
    while(!key[KEY_ESC]);

    free(font1);
}
void choixPoids(BITMAP* buffer,BITMAP* fond, FONT* font1, FONT* titre,std::string fichier1, Graphe& b,int nbPoids)
{
    draw_sprite(screen,fond,0,0);
    int poids1 = 0, poids2 = 0, poids3= 0;
    std::string fichier2 = fichier1;
    for(size_t i =0;i<4;i++)
        fichier1.pop_back();
    bool quit = false;
    std::string titr = "Fichier de poids de "+fichier1;
    const char* ouai = titr.c_str();
    rest(100);
    do
    {
        draw_sprite(buffer,fond,0,0);
        textout_centre_ex(buffer,titre,ouai,SCREEN_W/2,3*SCREEN_H/10,makecol(0,0,0),makecol(255,0,255));
        if(nbPoids>=1)
            poids1 = draw_bouton(1.75*SCREEN_W/10,6*SCREEN_H/10,3.25*SCREEN_W/10,6*SCREEN_H/10+50,makecol(43,105,200),makecol(30,73,138),3,"Poids 1",font1,buffer);
        if(nbPoids>=2)
            poids2 = draw_bouton(4.25*SCREEN_W/10,6*SCREEN_H/10,5.75*SCREEN_W/10,6*SCREEN_H/10+50,makecol(43,105,200),makecol(30,73,138),3,"Poids 2",font1,buffer);
        if(nbPoids>=3)
            poids3 = draw_bouton(6.75*SCREEN_W/10,6*SCREEN_H/10,8.25*SCREEN_W/10,6*SCREEN_H/10+50,makecol(43,105,200),makecol(30,73,138),3,"Poids 3",font1,buffer);

        draw_sprite(screen,buffer,0,0);

        if(poids1==1)
        {
            quit=true;
            b = Graphe (fichier2,fichier1+"_weights_0.txt");
        }
        else if(poids2==1)
        {
            quit=true;
            b = Graphe (fichier2,fichier1+"_weights_1.txt");
        }
        else if(poids3==1)
        {
            quit=true;
            b = Graphe (fichier2,fichier1+"_weights_2.txt");
        }
    }
    while(quit==false);

    free((char*)ouai);
    choixUtilisationGraph(buffer,fond,font1,titre,b,fichier1);

}
void choixUtilisationGraph(BITMAP* buffer, BITMAP* fond, FONT* font1, FONT* titre, Graphe& b,std::string nom)
{
    draw_sprite(screen,fond,0,0);
    for(size_t i =0;i<4;i++)
        nom.erase(0,1);
    int kruskal1 = 0,kruskal2 = 0, pareto = 0, brutforce = 0, base = 0, quitter =0,quitter2 = 0;
    bool quit = false;
    std::string titr = "Traitement de "+nom;
    const char* ouai = titr.c_str();
    rest(100);

    do
    {
        draw_sprite(buffer,fond,0,0);

        base =      draw_bouton(3.7*SCREEN_W/10,  5*SCREEN_H/10,6.3*SCREEN_W/10,5.5*SCREEN_H/10,makecol(43,105,200),makecol(30,73,138),3,"Afficher le Graphe",font1,buffer);
        kruskal1 =   draw_bouton(1.7*SCREEN_W/10,5.8*SCREEN_H/10,4.5*SCREEN_W/10,6.3*SCREEN_H/10,makecol(43,105,200),makecol(30,73,138),3,"Appliquer Kruskal 1",font1,buffer);
        kruskal2 =   draw_bouton(5.5*SCREEN_W/10,5.8*SCREEN_H/10,8.3*SCREEN_W/10,6.3*SCREEN_H/10,makecol(43,105,200),makecol(30,73,138),3,"Appliquer Kruskal 2",font1,buffer);
        brutforce = draw_bouton(3.5*SCREEN_W/10,6.6*SCREEN_H/10,6.5*SCREEN_W/10,7.1*SCREEN_H/10,makecol(43,105,200),makecol(30,73,138),3,"Solutions du BrutForce",font1,buffer);
        pareto =    draw_bouton(3.7*SCREEN_W/10,7.4*SCREEN_H/10,6.3*SCREEN_W/10,7.9*SCREEN_H/10,makecol(43,105,200),makecol(30,73,138),3,"Frontiere de Pareto",font1,buffer);
        quitter =   draw_bouton(3.7*SCREEN_W/10,8.2*SCREEN_H/10,6.3*SCREEN_W/10,8.7*SCREEN_H/10,makecol(43,105,200),makecol(30,73,138),3,"Changer de Graphe",font1,buffer);
        textout_centre_ex(buffer,titre,ouai,SCREEN_W/2,3*SCREEN_H/10,makecol(0,0,0),makecol(255,0,255));

        draw_sprite(screen,buffer,0,0);

        if(base==1)
        {
            clear_bitmap(buffer);
            do
            {
                draw_sprite(buffer,fond,0,0);
                b.afficherallegro(buffer,0,0,1);
                quitter2 =   draw_bouton(4.5*SCREEN_W/10,9.4*SCREEN_H/10,5.5*SCREEN_W/10,9.9*SCREEN_H/10,makecol(43,105,200),makecol(30,73,138),3,"Quitter",font1,buffer);
                draw_sprite(screen,buffer,0,0);
            }while(quitter2 == 0);
            draw_sprite(screen,fond,0,0);
        }
        else if(kruskal1==1||kruskal2==1)
        {
            Graphe a {b.getsommets(),((kruskal1 == 1) ? b.Kruskal(0) : b.Kruskal(1))};
            clear_bitmap(buffer);
            do
            {
                draw_sprite(buffer,fond,0,0);
                a.afficherallegro(buffer,0,0,1 );

                quitter2 =   draw_bouton(4.5*SCREEN_W/10,9.4*SCREEN_H/10,5.5*SCREEN_W/10,9.9*SCREEN_H/10,makecol(43,105,200),makecol(30,73,138),3,"Quitter",font1,buffer);
                draw_sprite(screen,buffer,0,0);
            }while(quitter2 == 0);
            draw_sprite(screen,fond,0,0);
        }
        else if(pareto==1)
        {

        }
        else if(brutforce==1)
        {
            draw_sprite(screen,fond,0,0);
            clear_bitmap(buffer);
            std::vector<std::vector<bool>> t = b.bruteforce(1);
            do
            {
                draw_sprite(buffer,fond,0,0);
                dessinerBrut(buffer,b,t,0,0,(nom == "manhattan" || nom == "triville") ? 3  : 2  );
                quitter2 =   draw_bouton(4.5*SCREEN_W/10,9.4*SCREEN_H/10,5.5*SCREEN_W/10,9.9*SCREEN_H/10,makecol(43,105,200),makecol(30,73,138),3,"Quitter",font1,buffer);
                draw_sprite(screen,buffer,0,0);
            }while(quitter2 == 0);
            rest(200);
            draw_sprite(screen,fond,0,0);
        }
        else if(quitter==1)
        {
            quit = true;
        }
    }
    while(quit==false);

    free((char*)ouai);
}

void dessinerBrut(BITMAP*buffer,Graphe b,std::vector<std::vector<bool>> Ttgraphes,double x, double y,int proportion)
{
    int k=x,l=y;
    std::vector<Arrete*> ArretesN;

    for(unsigned int i = 0; i < ((Ttgraphes.size()<20) ? Ttgraphes.size() : 20 ); i++)
    {
        for ( unsigned int j = 0; j < Ttgraphes[i].size ( ); j++ )
        {
            if ( Ttgraphes [ i ] [ j ] == true )
            {
                ArretesN.push_back ( b.getarretes() [ j ]  );
            }
        }
        Graphe a = Graphe ( b.getsommets() , ArretesN );
        a.afficherallegro(buffer,k,l,proportion);
        k+=500;
        if (k >= 2500)
        {
            //l+=500;
            l+=500;
            k=0;
        }
        ArretesN.clear();
    }
}

/* ****************************************************************************************************
*                    SOURCE :                                                                        *
* https://codes-sources.commentcamarche.net/source/31767-dessin-d-un-bouton-a-enfoncer-en-allegro-c  *
*                                                                                                    *
******************************************************************************************************/

///fonction affichant un bouton texte et renvoie si on clique dessus
// -> permet l'affichage d'un bouton avec effet d'enfoncement du clique
// -> il retourne 1 si on clique et 0 si on ne clique pas
int draw_bouton(int posx, int posy, int pos2x, int pos2y, int color1, int color2, int profondeur, char* texte,FONT* font1,BITMAP* buffer)
{
    int pos_mouse=1; // Pour savoir si la souris est sur le bouton
    int color; // Pour definir la couleur du bouton
    int c_hg; // Couleur du coin haut gauche
    int c_bd; // Couleur du coin bas droite
    int texte_x; // Position du texte en x
    int texte_y; // Position du texte en y
    int retour=0; // Renvoi
    int i;


    if(profondeur >5)
        profondeur=5;
    if(profondeur <=0)
        profondeur=1;

    // Si la souris est sur le bouton on modifie la valeur de pos_mouse
    if(mouse_x>=posx && mouse_x<=pos2x && mouse_y>=posy && mouse_y<=pos2y)
    {
        pos_mouse=2;
        // Si l'utilisateur clique sur le bouton
        if(mouse_b & 1)
        {
            pos_mouse=3;
            // On renvoie un 1 si le bouton est enfoncé
            retour=1;
        }
    }
    else
        pos_mouse=1;


    // Changement des couleurs pour les effets de perspective et pour savoir si la souris est sur le bouton
    switch(pos_mouse)
    {
    case 1:
        c_hg=255;
        c_bd=0;
        color=color1;
        texte_x=(posx+pos2x)/2;
        texte_y=(posy+pos2y)/2;
        break;
    case 2:
        c_hg=255;
        c_bd=0;
        color=color2;
        texte_x=(posx+pos2x)/2;
        texte_y=(posy+pos2y)/2;
        break;
    case 3:
        c_hg=0;
        c_bd=255;
        color=color2;
        texte_x=((posx+pos2x)/2)+profondeur;
        texte_y=((posy+pos2y)/2)+profondeur;
        break;
    }


    // Dessin de lignes blanches et noires pour la perspective
    for(i=0; i!=profondeur; i++)
    {
        hline(buffer,posx,posy+i,pos2x-i,makecol(c_hg,c_hg,c_hg));
        vline(buffer,posx+i,posy,pos2y-i,makecol(c_hg,c_hg,c_hg));
        hline(buffer,posx+i,pos2y-i,pos2x,makecol(c_bd,c_bd,c_bd));
        vline(buffer,pos2x-i,posy+i,pos2y,makecol(c_bd,c_bd,c_bd));
    }

    // Remplissage du bouton
    rectfill(buffer,posx+profondeur,posy+profondeur,pos2x-profondeur,pos2y-profondeur,color);
    // Ecriture du texte


    //textprintf_centre(buffer,font1,texte_x,texte_y,makecol(255,255,255),"%s",texte);

    textout_centre_ex(buffer,font1,texte,texte_x,texte_y-13,makecol(255,255,255),color);

    ///textout(buffer,font,texte,texte_x,texte_y,makecol(255,255,255));

    // Renvoi : 1 si le bouton a été cliqué, 0 sinon
    return retour;
}
