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
    Graphe(std::string nomFichier1,std::string nomFichier2);
    Graphe ( const std::vector<Sommet*>& sommets_src , const std::vector<Arete*>& aretes_src);
    Graphe ( const Graphe& src , const std::vector<bool>& vec);
    Graphe() = default;
    ~Graphe();

    std::vector<Sommet*> getsommets(){return m_sommets;};
    std::vector<Arete*> getarretes(){return m_Aretes;};

    void afficher() const;
    void afficherallegro(BITMAP *buffer, double x, double y, int proportion) const;

    std::vector<Arete*> Kruskal(size_t cout_id = 0) const;

    float distanceEuclidienne ( int s1 , int s2 )const;
    std::vector<float> getPoidsTotaux ( ) const;
    std::vector<std::vector<bool>> bruteforce(int tri) const;

    std::vector<Graphe*> optimPartielle ( const std::vector<std::vector<bool>>& solutionsAdmissibles, const size_t idxPoids = 0 )const;
    std::vector<Graphe*> optimBiObj ( const std::vector<std::vector<bool>>& solutionsAmissibles )const;


protected:

private:

    std::vector<Graphe*> Pareto ( std::vector<Graphe*>& solutionsAdmissibles )const;
    size_t nbCouts = 0;
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_Aretes;
    std::vector<float> m_poidsTotaux;
    std::vector<float> poidsTotaux ( );

};

#endif // GRAPHE_H
