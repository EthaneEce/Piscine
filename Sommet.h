#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>

class Sommet
{
public:
    ///constructeur qui re�oit en params les donn�es du sommet
    Sommet ( int , double , double );
    void afficherData ( ) const;

    /// Retourne l'id du sommet et ses diff�rents voisins
    int getid ( )const;
    double getx ( )const;
    double gety ( )const;

    ~Sommet ( );


private:

    /// Donn�es sp�cifiques du sommet
    int m_id; // Identifiant
    double m_x , m_y; // Position

};

#endif // SOMMET_H_INCLUDED
