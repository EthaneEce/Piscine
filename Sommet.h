#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>

class Sommet
{
public:
    ///constructeur qui reçoit en params les données du sommet
    Sommet ( int , double , double );
    void afficherData ( ) const;

    /// Retourne l'id du sommet et ses différents voisins
    int getid ( )const;
    double getx ( )const;
    double gety ( )const;

    ~Sommet ( );


private:

    /// Données spécifiques du sommet
    int m_id; // Identifiant
    double m_x , m_y; // Position

};

#endif // SOMMET_H_INCLUDED
