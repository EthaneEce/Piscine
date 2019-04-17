#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <iomanip>
#include "Sommet.h"
#include "Arrete.h"
#include <cmath>

class Graphe
{
public:
    Graphe ( std::string nomFichier1 , std::string nomFichier2 );
    Graphe ( std::unordered_map<int , Sommet*> , std::unordered_map<int , Arrete*> );
    Graphe ( ) = default;
    ~Graphe ( );
    void afficher ( ) const;
    std::unordered_map<int , Arrete*> Kruskal ( size_t cout_id = 0 ) const;
    std::vector<std::vector<bool>> bruteforce ( );
    float distanceEuclidienne ( int s1 , int s2 );
    std::vector<float> poidsTotaux ( );
    std::unordered_map<int , Sommet*> getSommets ( )const { return m_sommets; }

private:
    size_t nbCouts = 0;
    std::unordered_map<int , Sommet*> m_sommets;
    std::unordered_map<int , Arrete*> m_arretes;
};

#endif // GRAPHE_H
