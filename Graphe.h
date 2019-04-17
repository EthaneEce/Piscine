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
    Graphe(std::unordered_map<int, Sommet *>, std::unordered_map<int, Arrete *>);
    Graphe() = default;
    ~Graphe();
    void afficher() const;
    void afficherallegro(BITMAP *buffer, double x, double y, int proportion) const;
    std::unordered_map<int, Arrete *> Kruskal(size_t cout_id = 0) const;
    std::vector<Graphe *> bruteforce();
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
    std::unordered_map<int, Arrete *> m_arretes;
};

#endif // GRAPHE_H
