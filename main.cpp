#include <iostream>
#include "Graphe.h"


std::ostream& operator<<( std::ostream& out , std::vector<float> vec )
{
    for ( auto& a : vec )
        out << a << " ";
    return out;
}
int main ( )
{
    Graphe b ( "txt/broadway.txt" , "txt/broadway_weights_0.txt" );
    std::vector<bool> vec1 { false, true, false, true, true };
    std::vector<bool> vec2 { false, true, true, false, true };
    std::vector<bool> vec3 { false, true, true, true, false };
    std::vector<bool> vec4 { true, false, false, true, true };
    std::vector<bool> vec5 { true, false, true, false, true };
    std::vector<bool> vec6 { true, false, true, true, false };
    std::vector<bool> vec7 { true, true, false, false, true };
    std::vector<bool> vec8 { true, true, false, true, false };

    std::vector<std::vector<bool>>vec { vec1 ,
                vec2 , vec3 , vec4 ,
                vec5 , vec6 , vec7 , vec8 };

    auto par = b.Pareto ( vec );
    for ( auto& a : par )
        std::cout << a->poidsTotaux ( ) << std::endl;
    std::cin.get ( );
}


