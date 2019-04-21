#include "_Graphe.h"
#include <fstream>
#include <string>
#include <iostream>
#include <limits>
#include "Graphe.h"
//Constructeur 
_Graphe::_Graphe ( const Graphe& g , size_t idxPoidsTranspose )
{

    //Lecture des _Sommets
    auto sommets = g.getsommets ( );
    auto Aretes = g.getAretes ( );
    for ( auto& a : sommets )
    {
        int id = a->getid ( );
        double x = a->getx ( );
        double y = a->gety ( );
        m__Sommets.insert ( { id, new _Sommet ( id,x,y ) } );
    }

    //Lecture des Aretes
    for ( auto& a : Aretes )
    {
        int id1 , id2;
        id1 = a->gets1 ( );
        id2 = a->gets2 ( );
        float poids = a->getcout ( ).at ( idxPoidsTranspose );

        //trouver le _Sommet
        auto s1 = m__Sommets.find ( id1 );

        //trouver son voisin 
        auto s2 = m__Sommets.find ( id2 );

        //les associer
        s1->second->ajouterArete ( s2->second , poids );
        s2->second->ajouterArete ( s1->second , poids );
    }

}

_Graphe::~_Graphe ( )
{
    for ( auto& a : m__Sommets )
        delete a.second;
}

void _Graphe::afficher ( ) const
{
    for ( auto& a : m__Sommets )
    {
        a.second->afficher ( );
    }
}


std::unordered_map<int , float> _Graphe::dijkstra ( const size_t depart ) const
{
    float infini = std::numeric_limits<float>::max ( );

    //trouver le _Sommet de départ dans la map
    auto it = m__Sommets.find ( depart );
    if ( depart >= m__Sommets.size ( ) )
        throw std::exception ( "Impossible de trouver la valeur de depart" );
    //map avec laquelle on va faire le boulot (on va éviter de bidouiller les valeurs de la map m__Sommets)
    std::unordered_map<int , float>map;

    //copier la map m__Sommets et initialiser les distances à l'infini
    for ( auto& a : m__Sommets ) {
        map.insert ( { a.first,  infini } );
    }

    //faire dijkstra a partir du _Sommet de depart
    auto sol = it->second->dijsktra ( map );
    sol [ depart ] = 0;
    return sol;
}


