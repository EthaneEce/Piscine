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
    Graphe ( std::vector<Sommet*> , std::vector<Arrete*> );
    Graphe ( const Graphe& src , const std::vector<bool>& vec );
    Graphe ( ) = default;
    ~Graphe ( );
    std::vector<std::vector<bool>> bruteforce ( );
    float distanceEuclidienne ( int s1 , int s2 );
    std::vector<float> poidsTotaux ( );
    std::vector<Sommet*> getsommets ( ) { return m_sommets; };
    std::vector<Arrete*> getarretes ( ) { return m_arretes; };
    void afficher ( ) const;
    std::vector<Arrete*> Kruskal ( size_t cout_id = 0 ) const;
    std::vector<Graphe*> Pareto ( const std::vector<std::vector<bool>>& vec );
private:

    size_t nbCouts = 0;
    std::vector<Sommet*> m_sommets;
    std::vector<Arrete*> m_arretes;
};

#endif // GRAPHE_H
