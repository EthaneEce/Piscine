#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iomanip>
#include "Graphe.h"

int main ( )
{

    Graphe b ( "txt/cubetown.txt" , "txt/cubetown_weights_0.txt" );
    b.afficher ( );
    return 0;
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
        //a->afficher();

        compteur[0]+=1;
         std::cout<<std::endl;
         //system("pause");
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


