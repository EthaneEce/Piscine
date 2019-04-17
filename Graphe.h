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
    Graphe(std::string nomFichier1,std::string nomFichier2);
    Graphe(std::vector<Sommet*>,std::vector<Arrete*>);
    Graphe() = default;
    ~Graphe();
    std::vector<Sommet*> getsommets(){return m_sommets;};
    std::vector<Arrete*> getarretes(){return m_arretes;};
    void afficher() const;
    void afficherallegro(BITMAP *buffer, double x, double y, int proportion) const;
    void afficherallegrotout(BITMAP*buffer,double x, double y,int proportion) const;
    std::vector<Arrete*> Kruskal(size_t cout_id = 0) const;
    std::vector<std::vector<bool>> bruteforce(bool tri);
    inline int distanceEuclidienne(int s1, int s2)
    {
        Sommet* _s1;
        Sommet* _s2;
        for ( auto it : m_sommets )
        {
            if(s1 == it->getid())
            {
                _s1 = it;
            }
            if(s2 == it->getid())
            {
                _s2 = it;
            }
        }
        auto x = _s1->getx() - _s2->getx();
        auto y = _s1->gety() - _s2->gety();
        auto dist = (x * x) + (y * y);
        dist = sqrt(dist);
        return dist;
    }

protected:
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arrete*> m_arretes;
};

#endif // GRAPHE_H
