#pragma once
#include <unordered_map>
#include "_Sommet.h"
class Svgfile;
class Graphe;
class _Graphe
{
public:
    _Graphe ( const Graphe& g );
    void afficher ( ) const;
    std::unordered_map<int , float> dijkstra ( const int depart ) const;
    void dessiner ( Svgfile& svgout )const;
private:
    std::unordered_map<int , _Sommet*> m__Sommets;
};

