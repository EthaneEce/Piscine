#include "graphisme.h"

int menu(BITMAP* buffer, Graphe& a, FONT* font1)
{
    int choix = 0;
    std::string fichier1;
    int broadway = 0,cubetown = 0,manhattan = 0,triville = 0, poids = 0;
    int weight;
    BITMAP* fond = load_bitmap("Images/fond.bmp",nullptr);

    do
    {
        draw_sprite(buffer,fond,0,0);
        broadway = draw_bouton(  SCREEN_W/10,6*SCREEN_H/10,2.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Broadway",font1,buffer);
        cubetown = draw_bouton(3*SCREEN_W/10,6*SCREEN_H/10,4.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Cubetown",font1,buffer);
        manhattan= draw_bouton(5*SCREEN_W/10,6*SCREEN_H/10,6.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Manhattan",font1,buffer);
        triville = draw_bouton(7*SCREEN_W/10,6*SCREEN_H/10,8.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Triville",font1,buffer);


        if (broadway == 1)
            choixPoids(buffer,fond,font1,"txt/broadway.txt",a);
        if (cubetown == 1)
            choixPoids(buffer,fond,font1,"txt/cubetown.txt",a);
        if (manhattan == 1)
            choixPoids(buffer,fond,font1,"txt/manhattan.txt",a);
        if (triville == 1)
            choixPoids(buffer,fond,font1,"txt/triville.txt",a);


        draw_sprite(screen,buffer,0,0);
    }
    while(!key[KEY_ESC]);
    free(font1);
}
void choixPoids(BITMAP* buffer,BITMAP* fond, FONT* font1,std::string fichier1, Graphe& b)
{
    int poids1 = 0, poids2 = 0, poids3= 0;
    std::string fichier2 = fichier1;
    for(size_t i =0;i<4;i++;)
        fichier1.pop_back();
    bool quit = false;
    rest(100);
    do
    {
        draw_sprite(buffer,fond,0,0);
        poids1 = draw_bouton(1.75*SCREEN_W/10,6*SCREEN_H/10,3.25*SCREEN_W/10,6*SCREEN_H/10+50,makecol(43,105,200),makecol(30,73,138),3,"Poids 1",font1,buffer);
        poids2 = draw_bouton(4.25*SCREEN_W/10,6*SCREEN_H/10,5.75*SCREEN_W/10,6*SCREEN_H/10+50,makecol(43,105,200),makecol(30,73,138),3,"Poids 2",font1,buffer);
        poids3 = draw_bouton(6.75*SCREEN_W/10,6*SCREEN_H/10,8.25*SCREEN_W/10,6*SCREEN_H/10+50,makecol(43,105,200),makecol(30,73,138),3,"Poids 3",font1,buffer);
        draw_sprite(screen,buffer,0,0);

        if(poids1==1)
        {
            quit=true;
            b = Graphe (fichier2,fichier1+"_weights_"+"0");
        }
        else if(poids2==1)
        {
            quit=true;
            b = Graphe (fichier2,fichier1+"_weights_"+"1");
        }
        else if(poids3==1)
        {
            quit=true;
            b = Graphe (fichier2,fichier1+"_weights_"+"2");
        }
    }
    while(quit==false);

    choixUtilisationGraph(buffer,fond,font1,b);

}
void choixUtilisationGraph(BITMAP* buffer, BITMAP* fond, FONT* font1, Graphe& b)
{

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
