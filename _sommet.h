#pragma once
#include <unordered_map>
class Svgfile;
class _Sommet
{
private:
    int m_id;
    double m_x , m_y;
    //on definit un voisin avec un pointeur sur _Sommet et le poids de l'Arete
    std::vector<std::pair<_Sommet* , float>> m_voisins;
public:
    _Sommet ( int id, double x, double y );
    void ajouterArete ( _Sommet* s , const float poids );
    void afficher ( ) const;
    void dessiner ( Svgfile& svgout );
    //on prend en parametre le _Sommet de destination et la map contenant tous les _Sommets du _Graphe
    std::unordered_map<int , float> dijsktra ( std::unordered_map<int , float>& map ) const;
};

