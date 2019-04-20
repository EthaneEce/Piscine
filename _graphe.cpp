#include "_Graphe.h"
#include <fstream>
#include <string>
#include <iostream>
#include <limits>
#include "Graphe.h"
#include "svgfile.h"
//Constructeur 
_Graphe::_Graphe ( const Graphe& g , size_t idxPoidsTranspose )
{

    //Lecture des _Sommets
    auto sommets = g.getsommets ( );
    auto aretes = g.getarretes ( );
    for ( auto& a : sommets )
    {
        int id = a->getid ( );
        double x = a->getx ( );
        double y = a->gety ( );
        m__Sommets.insert ( { id, new _Sommet ( id,x,y ) } );
    }

    //Lecture des arretes
    for ( auto& a : aretes )
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
        s1->second->ajouterArrete ( s2->second , poids );
        s2->second->ajouterArrete ( s1->second , poids );
    }

}

void _Graphe::afficher ( ) const
{
    for ( auto& a : m__Sommets )
    {
        a.second->afficher ( );
    }
}

//surcharge de l'operteur << pour pouvoir afficher un vector avec std::cout<<vec
std::ostream& operator<<( std::ostream& out , const std::vector<std::string>& vec ) {
    for ( auto& a : vec )
        out << a << " ";
    return out;
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

void _Graphe::dessiner ( Svgfile & svgout ) const
{
    for ( auto& a : m__Sommets )
        a.second->dessiner ( svgout );
}


