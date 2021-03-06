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
int menu(BITMAP* buffer, Graphe& a, FONT* font1,FONT* titre);                                                     //Choix du graphe dans le dossier txt. On rentre dans les sous programmes qui suivent en "cascade"
void choixPoids(BITMAP* buffer,BITMAP* fond, FONT* font1,FONT*titre,std::string fichier1, Graphe& b,int nbPoids); //Sélection du fichier poids correspondant à la ville choisie
void choixUtilisationGraph(BITMAP* buffer, BITMAP* fond, FONT* font1,FONT* titre, Graphe& b,std::string nom);     //Sélection de l'utilisation du graphe. On va appeler les différentes méthodes de Graphe pour les dessiner
void dessinerBrut(BITMAP*buffer,Graphe b,std::vector<std::vector<bool>> Ttgraphes,double x, double y,int proportion);
void dessinersolPareto ( BITMAP * buffer , std::vector<std::shared_ptr <Graphe>> p , double x , double y , int proportion );
void dessinerPareto ( BITMAP * buffer , Graphe b , double x , double y , std::vector<std::vector<bool>> Ttgraphes , std::vector<std::vector<bool>> Ttgraphes2 , std::vector<std::shared_ptr<Graphe>> Pareto , bool dess , bool pareto2 );


#endif // GRAPHISME_H_INCLUDED
