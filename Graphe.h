#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <iomanip>
#include "allegro.h"
#include "Sommet.h"
#include "Arete.h"
#include <cmath>


class Graphe
{
public:

    /// Constructeur
    Graphe ( std::string nomFichier1 , std::string nomFichier2 );
    Graphe ( const std::vector<Sommet*>& sommets_src , const std::vector<Arete*>& aretes_src );
    Graphe ( const Graphe& src , const std::vector<bool>& vec );
    Graphe ( ) = default;
    ~Graphe ( ) = default;

    ///attributs
    std::vector<Sommet*> getsommets ( )const { return m_sommets; }; // Retourne les sommets
    std::vector<Arete*> getAretes ( )const { return m_Aretes; }; // Retourne les aretes
    std::vector<float> getPoidsTotaux ( ) const;

    ///Affichage
    void afficher ( ) const; // Affiche sur la console le graphes et ses attibuts
    void afficherallegro ( BITMAP* buffer , double x , double y , int proportion ) const; // Affiche le graphe sur allegro

    ///Outils
    std::vector<Arete*> Kruskal ( size_t cout_id = 0 ) const;
    std::vector<Graphe*> optimPartielle ( const std::vector<std::vector<bool>>& solutionsAdmissibles , const size_t idxPoids = 0 )const;
    std::vector<Graphe*> optimBiObj ( const std::vector<std::vector<bool>>& solutionsAmissibles )const;
    std::vector<float> poidsTotaux ( );
    float distanceEuclidienne ( int s1 , int s2 )const;
    std::vector<std::vector<bool>> bruteforce ( int tri ) const;  // Fait un brute force different en fonction du int en parametre



protected:

private:

    std::vector<Graphe*> Pareto ( std::vector<Graphe*>& solutionsAdmissibles )const;
    size_t nbCouts = 0;
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_Aretes;
    std::vector<float> m_poidsTotaux;
    std::vector<float> poidsTotaux ( )const;

};

#endif // GRAPHE_H
