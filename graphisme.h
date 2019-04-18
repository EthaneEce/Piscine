#ifndef GRAPHISME_H_INCLUDED
#define GRAPHISME_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <string.h>
#include <iomanip>
#include "Graphe.h"

int draw_bouton(int posx, int posy, int pos2x, int pos2y, int color1, int color2, int profondeur, char* texte,FONT* font1,BITMAP* buffer);
int menu(BITMAP* buffer, Graphe& a, FONT* font1);
int choixPoids(BITMAP* buffer,BITMAP* fond, FONT* font1,std::string fichier1, Graphe& b);


#endif // GRAPHISME_H_INCLUDED
