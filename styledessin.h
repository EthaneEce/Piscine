#ifndef STYLEDESSIN_H_INCLUDED
#define STYLEDESSIN_H_INCLUDED

#include "couleur.h"

struct StyleDessin
{
    /// Aretes
    bool dessinerAretes = true;
    double epaisseurArete = 2;
    Couleur couleurArete = {0, 0, 0};

    /// Sommets
    bool dessinerSommets = true;
    double rayonSommet = 5;
    Couleur couleurSommet = {0, 0, 0};

    /// Sommets sélectionnés
    double rayonSommetSelect = 10;
    double epaisseurSommetSelect = 3;
    Couleur couleurSommetSelect = {0, 0, 0};
};


#endif // STYLEDESSIN_H_INCLUDED
