#include <iostream>
#include "Graphe.h"
#include <fstream>

std::ostream& operator<<( std::ostream& out , std::vector<float> vec )
{
    for ( auto& a : vec )
        out << a << " ";
    return out;
}

int main ( )
{
    std::ifstream ifs ( "fichier.txt" );
    Graphe b ( "txt/manhattan.txt" , "txt/manhattan_weights_0.txt" );
    size_t size1 , size2;
    ifs >> size1 >> size2;
    std::vector<std::vector<bool>> BruteForce_Manhattan;
    for ( size_t i = 0; i < size1; i++ )
    {
        std::vector<bool> temp;
        for ( size_t j = 0; j < size2; j++ )
        {
            bool a;
            ifs >> a;
            temp.push_back ( a );
        }
        BruteForce_Manhattan.push_back ( temp );
    }
    auto par = b.Pareto ( BruteForce_Manhattan );
    std::cout << par.size ( ) << std::endl;
    for ( auto& a : par )
        std::cout << a->poidsTotaux ( ) << std::endl;
    std::cin.get ( );
}


