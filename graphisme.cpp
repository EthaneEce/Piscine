#include "graphisme.h"

int menu(BITMAP* buffer, Graphe& a, FONT* font1)
{
    int choix = 0;
    std::string fichier1,fichier2;
    int broadway = 0,cubetown = 0,manhattan = 0,triville = 0;
    int weight;
    BITMAP* fond = load_bitmap("Images/fond.bmp",nullptr);

    do
    {
        draw_sprite(buffer,fond,0,0);
        broadway = draw_bouton(  SCREEN_W/10,6*SCREEN_H/10,2.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Broadway",font1,buffer);
        cubetown = draw_bouton(3*SCREEN_W/10,6*SCREEN_H/10,4.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Cubetown",font1,buffer);
        manhattan= draw_bouton(5*SCREEN_W/10,6*SCREEN_H/10,6.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Manhattan",font1,buffer);
        triville = draw_bouton(7*SCREEN_W/10,6*SCREEN_H/10,8.5*SCREEN_W/10,6*SCREEN_H/10+50,makecol(29,240,17),makecol(20,186,12),3,"Triville",font1,buffer);
        draw_sprite(screen,buffer,0,0);
    }while(broadway == 0 && cubetown == 0 && manhattan == 0 && triville == 0);

    free(font1);
    if (broadway == 1)
    {
        fichier1 = "txt/broadway.txt";
    }
    if (cubetown == 1)
    {
        fichier1 = "txt/cubetown.txt";
    }
    if (manhattan == 1)
    {
        fichier1 = "txt/manhattan.txt";
    }
    if (triville == 1)
    {
        fichier1 = "txt/triville.txt";
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
            // On renvoie un 1 si le bouton est enfonc�
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

    // Renvoi : 1 si le bouton a �t� cliqu�, 0 sinon
    return retour;
}
