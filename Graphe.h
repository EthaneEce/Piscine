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
        Graphe();
        ~Graphe();
        void afficher() const;
        std::vector<Arrete*> Kruskal(size_t cout_id)const;

    protected:

    private:
        std::unordered_map<int,Sommet*> m_sommets;
        std::unordered_map<int,Arrete*> m_arretes;
};

#endif // GRAPHE_H
