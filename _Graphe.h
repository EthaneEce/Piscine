#pragma once
#include <unordered_map>
#include "_Sommet.h"

class Graphe;
class _Graphe
{
public:
    _Graphe ( const Graphe& g , const size_t idxPoidsTranspose );
    ~_Graphe ( );
    void afficher ( ) const;
    std::unordered_map<int , float> dijkstra ( const size_t depart ) const;
    void dessiner ( Svgfile& svgout ) const;
private:
    std::unordered_map<int , _Sommet*> m__Sommets;
};

