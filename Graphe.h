#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <iomanip>
#include "allegro.h"
#include "Sommet.h"
#include "Arete.h"
#include <cmath>
#include <memory>


class Graphe
{
public:


    /// Constructeurs  et destructeurs
    Graphe ( std::string nomFichier1 , std::string nomFichier2 );
    Graphe ( const std::vector<std::shared_ptr<Sommet>>& sommets_src , const std::vector<std::shared_ptr<Arete>>& Aretes_src , const std::string& nom_graphe = "" );
    Graphe ( const Graphe& src , const std::vector<bool>& vec , const std::string& nom_graphe = "" );
    Graphe ( ) = default;
    ~Graphe ( ) = default;

    ///Algorithmes
    std::vector<std::vector<bool>> bruteforce ( int tri = 0 )const;
    std::vector<std::shared_ptr<Arete>> Kruskal ( size_t cout_id = 0 ) const;
    std::vector<std::shared_ptr<Graphe>> optimBiObj ( const std::vector<std::vector<bool>>& solutionsAmissibles )const;
    std::vector<std::shared_ptr<Graphe>> optimPartielle ( const std::vector<std::vector<bool>>& solutionsAdmissibles , const size_t idxPoids = 0 )const;

    ///Affichage
    void afficherallegro ( BITMAP* buffer , double x , double y , int proportion ) const; // Affiche le graphe sur allegro
    void afficher ( ) const;

    ///Util
    float distanceEuclidienne ( int s1 , int s2 )const;
    std::vector<std::shared_ptr<Sommet>> getsommets ( )const { return m_sommets; };
    std::vector<std::shared_ptr<Arete>> getAretes ( )const { return m_Aretes; };
    std::vector<float> getPoidsTotaux ( )const;

private:

    std::vector<std::shared_ptr<Graphe>> Pareto ( std::vector<std::shared_ptr<Graphe>>& solutionsAdmissibles )const;

    ///Attributs
    size_t nbCouts = 0;
    std::vector<std::shared_ptr<Sommet>> m_sommets;
    std::vector<std::shared_ptr<Arete>> m_Aretes;
    std::string graphName;
    std::vector<float> m_poidsTotaux;
    std::vector<float> poidsTotaux ( )const;

};

#endif // GRAPHE_H
