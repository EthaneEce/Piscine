#include <fstream>
#include "Graphe.h"
#include <functional>
#include <algorithm>
#include <set>
#include <memory>
#include "Timer.h"
Graphe::Graphe ( std::vector<Sommet*> mS , std::vector<Arrete*> mA )
    : m_sommets ( mS ) , m_arretes ( mA )
{
    nbCouts = m_arretes [ 0 ]->getcout ( ).size ( );
}


Graphe::Graphe ( const Graphe& src , const std::vector<bool>& vec )
{
    std::vector<Arrete*> temp;
    for ( size_t i = 0; i < vec.size ( ); i++ )
    {
        if ( vec.at ( i ) & true ) {
            temp.push_back ( src.m_arretes.at ( i ) );
        }
    }
    *this = Graphe ( src.m_sommets , temp );
}

Graphe::Graphe ( std::string nomFichier1 , std::string nomFichier2 )
{
    std::ifstream ifs1 { nomFichier1 };
    if ( !ifs1 )
        throw std::runtime_error ( "Impossible d'ouvrir en lecture " + nomFichier1 );

    std::ifstream ifs2 { nomFichier2 };
    if ( !ifs2 )
        throw std::runtime_error ( "Impossible d'ouvrir en lecture " + nomFichier2 );

    int ordre;
    ifs1 >> ordre;
    if ( ifs1.fail ( ) )
        throw std::runtime_error ( "Probleme lecture ordre du graphe" );

    int id1;
    double x1 , y1;
    //lecture des sommets
    for ( int i = 0; i < ordre; ++i )
    {
        ifs1 >> id1;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donnees sommet" );
        ifs1 >> x1;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donnees sommet" );
        ifs1 >> y1;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donnees sommet" );
        m_sommets.push_back ( new Sommet { id1, x1, y1 } );
    }

    int taille , taille2;
    ifs1 >> taille;
    if ( ifs1.fail ( ) )
        throw std::runtime_error ( "Probleme lecture taille du graphe" );
    ifs2 >> taille2;
    if ( ifs2.fail ( ) )
        throw std::runtime_error ( "Probleme lecture taille du graphe2" );
    if ( taille != taille2 )
        throw std::runtime_error ( "Probleme de taille des arretes, elles ne coincident pas" );

    ifs2 >> nbCouts;
    //std::cout<<nombrecout<<"aze"<<std::endl;
    if ( ifs2.fail ( ) )
        throw std::runtime_error ( "Probleme lecture nombre des couts du graphe2" );

    int id2;
    int x2 , y2;

    //lecture des arrete
    for ( int i = 0; i < taille; ++i )
    {
        ifs1 >> id2;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donn�es arrete" );
        ifs1 >> x2;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donn�es arrete" );
        ifs1 >> y2;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donn�es arrete" );
        std::vector<float> Cout;
        int arreteid;
        ifs2 >> arreteid;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donn�es arrete" );
        if ( arreteid != id2 )
            throw std::runtime_error ( "Probleme de id des arretes, elles ne coincident pas" );
        for ( size_t j = 0; j < nbCouts; ++j )
        {
            float coutnbr;
            ifs2 >> coutnbr;
            if ( ifs1.fail ( ) )
                throw std::runtime_error ( "Probleme lecture donn�es arrete" );
            Cout.push_back ( coutnbr );
        }
        m_arretes.push_back ( new Arrete { id2, x2, y2, Cout } );
    }
}

Graphe::~Graphe ( )
{
    //dtor
}

void Graphe::afficher ( ) const
{
    std::cout << "graphe : " << std::endl;
    std::cout << "ordre : " << m_sommets.size ( ) << std::endl;
    for ( auto it : m_sommets )
    {
        std::cout << "->";
        it->afficherData ( );
        std::cout << std::endl;
    }
    std::cout << "taille : " << m_arretes.size ( ) << std::endl;
    for ( auto it : m_arretes )
    {
        std::cout << "->";
        it->afficherData ( );
        std::cout << std::endl;
    }
}




std::vector<Arrete*> Graphe::Kruskal ( size_t cout_id ) const
{
    Timer t ( "Kruskal" );
    //Map Solution
    std::vector<Arrete*> solution;

    //Associer un sommet et sa composante connexe
    std::unordered_map<int , std::shared_ptr<int>> composantesConnexes;

    //Au déput chaque sommet est sur une composante connexe
    int i = 0;
    for ( auto& a : m_sommets )
    {
        composantesConnexes.insert ( { a->getid ( ), std::make_shared<int> ( i ) } );
        i++;
    }

    //Vector dans lequel on va mettre notre map d'aretes
    std::vector<Arrete*> vec ( m_arretes );


    //trier le vector en fonction du cout reçu en parametre
    auto sortFunction = [ & ] ( Arrete * a1 , Arrete * a2 ) {
        return a1->getcout ( ).at ( cout_id ) < a2->getcout ( ).at ( cout_id );
    };

    std::sort ( vec.begin ( ) , vec.end ( ) , sortFunction );



    //Algo de Kruskal
//pour chaque arete
    for ( auto& a : vec )
    {
        //Trouver les sommets
        auto s1 = composantesConnexes.find ( a->gets1 ( ) );
        auto s2 = composantesConnexes.find ( a->gets2 ( ) );

        //S'ils ne sont pas sur la meme composante connexe
        if ( *( s1->second ) != *( s2->second ) )
        {
            //Inserer l'arete
            solution.push_back ( a );


            //Mettre à jour pour que les sommets sont sur la meme composante connexe
            if ( s1->second.use_count ( ) < s2->second.use_count ( ) )
                s1->second = s2->second;
            else if ( s2->second.use_count ( ) == 1 )
                s2->second = s1->second;
            else
                *( s1->second ) = *( s2->second );


            //Si on a inséré ordre_graphe - 1 aretes, on stop la boucle
            if ( solution.size ( ) == m_sommets.size ( ) - 1 )
                break;
        }
    }

    return solution;
}

std::vector<Graphe*> Graphe::Pareto ( const std::vector<std::vector<bool>> & vec )
{
    std::vector<Graphe*> solution;
    for ( auto a : vec )
    {
        solution.push_back ( new Graphe ( *this , a ) );
    }
    auto sortFunction = [ = ] ( Graphe * g1 , Graphe * g2 )
    {
        auto v1 = g1->poidsTotaux ( );
        auto v2 = g2->poidsTotaux ( );
        return v1.at ( 0 ) < v2.at ( 0 );
    };
    std::sort ( solution.begin ( ) , solution.end ( ) , sortFunction );


    return solution;
}

std::vector<std::vector<bool>> Graphe::bruteforce ( )
{
    Timer t ( "brute force" );
    std::vector<std::vector<bool>> solution;

    std::vector<Sommet*> Sommetsmap = m_sommets;
    std::vector<Arrete*> Arretesvec = m_arretes;
    std::vector<Graphe*> TtGraphes;
    std::vector<Arrete*> ArretesN;

    std::vector<int> compteur ( Arretesvec.size ( ) , 0 );

    while ( true )
    {
        for ( unsigned int i = 0; i < Arretesvec.size ( ); i++ )
        {
            if ( compteur [ i ] == 2 )
            {
                compteur [ i ] = 0;
                compteur [ i + 1 ] += 1;
            }
        }
        if ( ( compteur [ compteur.size ( ) - 1 ] == 1 ) )
        {
            break;
        }
        for ( unsigned int i = 0; i < Arretesvec.size ( ); i++ )
        {
            if ( compteur [ i ] == 1 )
            {
                ArretesN.push_back ( Arretesvec [ i ] );
            }
            // std::cout << compteur [ i ];
        }
        // Graphe* a = new Graphe ( Sommetsmap , ArretesN );
     //    TtGraphes.push_back ( a );
         //a->afficher();

        compteur [ 0 ] += 1;
        // std::cout << std::endl;
         //system("pause");
    }
    return solution;
}
float Graphe::distanceEuclidienne ( int s1 , int s2 )
{
    auto x = m_sommets [ s1 ]->getx ( ) - m_sommets [ s2 ]->getx ( );
    auto y = m_sommets [ s2 ]->gety ( ) - m_sommets [ s2 ]->gety ( );
    auto dist = ( x * x ) + ( y * y );
    dist = sqrt ( dist );
    return ( float ) dist;
}

std::vector<float> Graphe::poidsTotaux ( )
{
    std::vector<float>solution;
    for ( size_t i = 0; i < nbCouts; i++ )
    {
        float total = 0.0f;
        for ( auto& a : m_arretes ) {
            total += a->getcout ( ).at ( i );
        }
        solution.push_back ( total );
    }
    return solution;
}
