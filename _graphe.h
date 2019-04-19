#pragma once
#include <unordered_map>
#include "_Sommet.h"
class Graphe;
class _Graphe
{
public:
    _Graphe ( const Graphe& g );
    void afficher ( ) const;
    void dijkstra ( const int depart ) const;
private:
    std::unordered_map<int , _Sommet*> m__Sommets;
};

