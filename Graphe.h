#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <iomanip>
#include "allegro.h"
#include "Sommet.h"
#include "Arrete.h"
#include <cmath>

class Graphe
{
public:
    Graphe(std::string nomFichier1, std::string nomFichier2);
    Graphe();
    ~Graphe();
    void afficher() const;
    std::vector<Arrete<float> *> Kruskal(size_t cout_id) const;
    inline int distanceEuclidienne(int s1, int s2)
    {
        auto _s1 = m_sommets.find(s1);
        auto _s2 = m_sommets.find(s2);
        auto x = _s1->second->getx() - _s2->second->getx();
        auto y = _s1->second->gety() - _s2->second->gety();
        auto dist = (x * x) + (y * y);
        dist = sqrt(dist);
    }

protected:
private:
    std::unordered_map<int, Sommet *> m_sommets;
    std::unordered_map<int, Arrete<float> *> m_arretes;
};

#endif // GRAPHE_H
