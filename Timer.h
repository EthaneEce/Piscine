#pragma once
#include <chrono>
#include <iostream>


class Timer
{
private:
    std::chrono::system_clock::time_point debut;
    std::chrono::system_clock::time_point fin;
    std::string m_functionName;
public:
    Timer ( std::string functionName = "" ) : m_functionName ( functionName )
    {
        debut = std::chrono::high_resolution_clock::now ( );
    }
    ~Timer ( )
    {
        fin = std::chrono::high_resolution_clock::now ( );
        auto duree = fin - debut;
        std::cout
            << std::endl << "L'execution de la fonction '"
            << m_functionName << "' a pris : "
            << duree.count ( ) / 1000000.0 << " ms" << std::endl;
    }
};
