#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <iomanip>
#include "allegro.h"
#include "Sommet.h"
#include "Arrete.h"

class Graphe
{
    public:
        Graphe(std::string nomFichier1,std::string nomFichier2);
        Graphe(std::unordered_map<int,Sommet*>,std::unordered_map<int,Arrete*>);
        ~Graphe();
        std::unordered_map<int,Sommet*> getsommets(){return m_sommets;};
        std::unordered_map<int,Arrete*> getarretes(){return m_arretes;};
        void afficher() const;
        void afficherallegro(double x, double y,int proportion) const;
        std::unordered_map<int,Arrete*> Kruskal(size_t cout_id)const;
        std::unordered_map<int,Sommet*> getSommets(){return m_sommets;};

    protected:

    private:
        std::unordered_map<int,Sommet*> m_sommets;
        std::unordered_map<int,Arrete*> m_arretes;
};

#endif // GRAPHE_H
