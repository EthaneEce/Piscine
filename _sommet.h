#pragma once
#include <unordered_map>
class _Sommet
{
private:
    int m_id;

    //on definit un voisin avec un pointeur sur _Sommet et le poids de l'arrete
    std::vector<std::pair<_Sommet* , float>> m_voisins;
public:
    _Sommet ( int id );
    void ajouterArrete ( _Sommet* s , const float poids );
    void afficher ( ) const;

    //on prend en parametre le _Sommet de destination et la map contenant tous les _Sommets du _Graphe
    std::vector<std::string> dijsktra ( std::unordered_map<int , float>& map ) const;
};

