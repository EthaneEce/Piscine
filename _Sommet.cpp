#include "_Sommet.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector>
_Sommet::_Sommet ( int id , double x , double y ) : m_id ( id ) , m_x ( x ) , m_y ( y )
{
}

void _Sommet::ajouterArete ( _Sommet* s , const float poids )
{
    m_voisins.push_back ( std::make_pair ( s , poids ) );
}


void _Sommet::afficher ( ) const
{
    for ( auto& a : m_voisins )
    {
        std::cout
            << "["
            << m_id
            << ", "
            << a.first->m_id
            << "]"
            << " = "
            << a.second
            << std::endl;
    }
}



class myComparator
{
public:
    bool operator() ( const std::pair<float , const _Sommet*>& p1 ,
        const std::pair<float , const _Sommet*>& p2 )
    {
        return p1.first > p2.first;
    }
};

//retourne un vector de string qui représentent le chemin à prendre
std::unordered_map<int , float> _Sommet::dijsktra ( std::unordered_map<int , float>& map )const
{
    //map qui associe un _Sommet à son meilleur prédecesseur
    std::unordered_map<int , float> l_pred;

    //Associer un sommet à une distance
    std::priority_queue<std::pair<float , const _Sommet*> ,
        std::vector<std::pair<float , const _Sommet*>> ,
        myComparator>pq;

    //appliquer l'algo de dijkstra
    pq.push ( std::make_pair ( 0 , this ) );
    while ( !pq.empty ( ) )
    {
        std::pair<float , const _Sommet*> u = pq.top ( );
        pq.pop ( );
        for ( auto& a : u.second->m_voisins ) {
            auto it = map.find ( a.first->m_id );
            if ( it->second > a.second + u.first ) {
                it->second = a.second + u.first;
                pq.push ( std::make_pair ( it->second , a.first ) );

                //mettre a jour le meilleur predecesseur pour un _Sommet 
                l_pred [ a.first->m_id ] = it->second;
            }
        }
    }
    return l_pred;

}




