#include <fstream>
#include "Graphe.h"
#include <functional>
#include <algorithm>
#include <set>
#include <memory>
#include "Timer.h"
#include <limits>
#include "Graphe.h"
#include "_graphe.h"


Graphe::Graphe ( const std::vector<Sommet*>& mS , const std::vector<Arete*>& mA )
: m_sommets ( mS ) , m_Aretes ( mA )
{
    nbCouts = m_Aretes [ 0 ]->getcout ( ).size ( );
    m_poidsTotaux = poidsTotaux ( );
}

Graphe::Graphe ( const Graphe& src , const std::vector<bool>& vec )
{
    std::vector<Arete*> temp;
    for ( size_t i = 0; i < vec.size ( ); i++ )
    {
        if ( vec.at ( i ) & true ) {
            temp.push_back ( src.m_Aretes.at ( i ) );
        }
    }
    if ( temp.empty ( ) )
        temp.push_back ( new Arete ( src.nbCouts ) );
    *this = Graphe ( src.m_sommets , temp );
    m_poidsTotaux = poidsTotaux ( );
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
        throw std::runtime_error ( "Probleme de taille des Aretes, elles ne coincident pas" );

    ifs2 >> nbCouts;
    if ( ifs2.fail ( ) )
        throw std::runtime_error ( "Probleme lecture nombre des couts du graphe2" );

    int id2;
    int x2 , y2;

    //lecture des Arete
    for ( int i = 0; i < taille; ++i )
    {
        ifs1 >> id2;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donn�es Arete" );
        ifs1 >> x2;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donn�es Arete" );
        ifs1 >> y2;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donn�es Arete" );
        std::vector<float> Cout;
        int Areteid;
        ifs2 >> Areteid;
        if ( ifs1.fail ( ) )
            throw std::runtime_error ( "Probleme lecture donn�es Arete" );
        if ( Areteid != id2 )
            throw std::runtime_error ( "Probleme de id des Aretes, elles ne coincident pas" );
        for ( size_t j = 0; j < nbCouts; ++j )
        {
            float coutnbr;
            ifs2 >> coutnbr;
            if ( ifs1.fail ( ) )
                throw std::runtime_error ( "Probleme lecture donn�es Arete" );
            Cout.push_back ( coutnbr );
        }
        m_Aretes.push_back ( new Arete { id2, x2, y2, Cout } );
    }
    m_poidsTotaux = poidsTotaux ( );
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
    std::cout << "taille : " << m_Aretes.size ( ) << std::endl;
    for ( auto it : m_Aretes )
    {
        std::cout << "->";
        it->afficherData ( );
        std::cout << std::endl;
    }
}


void Graphe::afficherallegro ( BITMAP* buffer , double x , double y , int proportion ) const
{
    for ( auto it : m_Aretes )
    {

        int sommet1id = it->gets1 ( );
        int sommet2id = it->gets2 ( );

        Sommet* n1;
        Sommet* n2;
        for ( auto it2 : m_sommets )
        {
            if ( sommet1id == it2->getid ( ) )
            {
                n1 = it2;
            }
            if ( sommet2id == it2->getid ( ) )
            {
                n2 = it2;
            }
        }

        /**for ( int j = 5; j >= -5; j-- )
        {
            for ( int i = -5; i <= 5; i++ )
            {
                line ( buffer , (x + n1->getx ( ) + i)/proportion , (y + n1->gety ( ) + i)/proportion , (x + n2->getx ( ) + j)/proportion , (y + n2->gety ( ) + j)/proportion , makecol ( 255 , 255 , 255 ) );
            }
        }**/
        triangle ( buffer , ( x + n1->getx ( ) - 5 ) / proportion , ( y + n1->gety ( ) - 5 ) / proportion , ( x + n2->getx ( ) - 5 ) / proportion , ( y + n2->gety ( ) - 5 ) / proportion , ( x + n1->getx ( ) + 5 ) / proportion , ( y + n1->gety ( ) + 5 ) / proportion , makecol ( 255 , 255 , 255 ) );
        triangle ( buffer , ( x + n1->getx ( ) + 5 ) / proportion , ( y + n1->gety ( ) + 5 ) / proportion , ( x + n2->getx ( ) - 5 ) / proportion , ( y + n2->gety ( ) - 5 ) / proportion , ( x + n2->getx ( ) + 5 ) / proportion , ( y + n2->gety ( ) + 5 ) / proportion , makecol ( 255 , 255 , 255 ) );
        textprintf_centre_ex ( buffer , font , ( x + ( n1->getx ( ) + n2->getx ( ) ) / 2 ) / proportion , ( y + ( n1->gety ( ) + n2->gety ( ) ) / 2 ) / proportion , makecol ( 0 , 0 , 0 ) , makecol ( 255 , 0 , 255 ) , "%d" , it->getid ( ) );
    }
    int texte1 = 0;
    for ( auto it : m_Aretes )
    {
        std::vector<float> couts;
        couts = it->getcout ( );
        textprintf_centre_ex ( buffer , font , x + SCREEN_W - 170 , y + 100 + texte1 , makecol ( 0 , 0 , 0 ) , makecol ( 255 , 0 , 255 ) , "Cout de %d --> " , it->getid ( ) );
        int texte2 = 0;
        for ( auto it2 : couts )
        {
            textprintf_centre_ex ( buffer , font , x + SCREEN_W - 100 + texte2 , y + 100 + texte1 , makecol ( 0 , 0 , 0 ) , makecol ( 255 , 0 , 255 ) , "%.02f " , it2 );
            texte2 += 60;
        }
        texte1 += 10;
    }

    for ( auto it : m_sommets )
    {
        circlefill ( buffer , ( x + it->getx ( ) ) / proportion , ( y + it->gety ( ) ) / proportion , 100 / ( proportion * 10 ) , makecol ( 255 , 0 , 0 ) );
        textprintf_centre_ex ( buffer , font , ( x + it->getx ( ) ) / proportion , ( y + it->gety ( ) ) / proportion , makecol ( 255 , 255 , 0 ) , makecol ( 255 , 0 , 0 ) , "%d" , it->getid ( ) );
    }
}

std::vector<Arete*> Graphe::Kruskal ( size_t cout_id ) const
{

    //Timer t ( "Kruskal a partir du graphe " + graphName );

    //Map Solution
    std::vector<Arete*> solution;

    //Associer un sommet et sa composante connexe
    std::vector<int> composantesConnexes;

    //Au déput chaque sommet est sur une composante connexe
    for ( size_t i = 0; i < m_sommets.size ( ); i++ )
    {
        composantesConnexes.push_back ( i );
    }

    //Vector dans lequel on va mettre notre map d'Aretes
    std::vector<Arete*> vec ( m_Aretes );


    //trier le vector en fonction du cout reçu en parametre
    auto sortFunction = [ & ] ( Arete * a1 , Arete * a2 ) {
        return a1->getcout ( ).at ( cout_id ) < a2->getcout ( ).at ( cout_id );
    };

    std::sort ( vec.begin ( ) , vec.end ( ) , sortFunction );



    //Algo de Kruskal
//pour chaque Arete
    for ( auto& a : vec )
    {
        //Trouver les sommets
        auto s1 = composantesConnexes.at ( a->gets1 ( ) );
        auto s2 = composantesConnexes.at ( a->gets2 ( ) );

        //S'ils ne sont pas sur la meme composante connexe
        if ( s1 != s2 )
        {
            //Inserer l'Arete
            solution.push_back ( a );


            //Mettre à jour pour que les sommets sont sur la meme composante connexe
            for ( auto& b : composantesConnexes ) {
                if ( b == s1 )
                    b = s2;
            }

            //Si on a inséré ordre_graphe - 1 Aretes, on stop la boucle
            if ( solution.size ( ) == m_sommets.size ( ) - 1 )
                break;
        }
    }

    return solution;
}


std::vector<Graphe*> Graphe::Pareto ( std::vector<Graphe*> & solution ) const
{
    //Timer t ( "Pareto pour le graphe " + graphName );
    const constexpr float infini = std::numeric_limits<float>::max ( );

    size_t IDXpoidsCourant = 0;

    //Pour chaque poids allant de 0 à nombre de couts totaux - 1
    while ( IDXpoidsCourant < nbCouts - 1 )
    {

        //Tronquer les éléments qui seront certainement dominées
        {
            //Initialiser nos comparateurs
            float min_ = infini;           //Cout minimal courant
            float nMinCout = infini;      //Cout suivant du graphe qui la cout minimal


            //Récupérer le cout minimal (ce sera le premier élément du vector quand on le trie)
            for ( auto& a : solution )
            {
                if ( a->m_poidsTotaux.at ( IDXpoidsCourant ) < min_ ) {
                    min_ = a->m_poidsTotaux.at ( IDXpoidsCourant );
                    nMinCout = a->m_poidsTotaux.at ( IDXpoidsCourant + 1 );
                }
            }
            //Supprimer toutes les solutions dominées par celle qu'on vient de trouver
            solution.erase ( std::remove_if ( solution.begin ( ) , solution.end ( ) ,
                [ = ] ( Graphe * g ) {
                    return g->getPoidsTotaux ( ).at ( IDXpoidsCourant + 1 ) > nMinCout;
                } ) , solution.end ( ) );
        }

        //Trier le vector solution
        auto sortFunction = [ = ] ( Graphe * g1 , Graphe * g2 )
        {
            auto v1 = g1->getPoidsTotaux ( );
            auto v2 = g2->getPoidsTotaux ( );
            return v1.at ( IDXpoidsCourant ) < v2.at ( IDXpoidsCourant );
        };
        std::sort ( solution.begin ( ) , solution.end ( ) , sortFunction );


        //Pour chaque élément, l'enlever s'il est dominé par une autre solution
        float pivot = infini;
        for ( auto a = solution.begin ( ); a != solution.end ( ); )
        {
            float Cout = ( *a )->m_poidsTotaux.at ( IDXpoidsCourant + 1 );
            float pCout = ( *a )->m_poidsTotaux.at ( IDXpoidsCourant );

            if ( Cout < pivot )
            {
                pivot = Cout;
                a++;
                auto iterator = std::remove_if ( a , solution.end ( ) ,
                    [ = ] ( Graphe * g ) {
                        return g->getPoidsTotaux ( ).at ( IDXpoidsCourant + 1 ) >= pivot;
                    } );
                solution.erase ( iterator , solution.end ( ) );
            }
        }


        IDXpoidsCourant++;
    }


    //Un dernier parcours pour nettoyer les valeurs qui ont 1 cout égal
    for ( size_t i = 0; i < nbCouts - 1; i++ )
    {
        for ( auto a = solution.begin ( ); a != solution.end ( ) - 1; )
        {
            auto it = *a;
            auto nextIt = *( a + 1 );
            if ( it->m_poidsTotaux.at ( i ) == nextIt->m_poidsTotaux.at ( i ) )
            {
                if ( it->m_poidsTotaux.at ( i + 1 ) < nextIt->m_poidsTotaux.at ( i + 1 ) )
                {
                    a = solution.erase ( a + 1 );
                }
                else {
                    a = solution.erase ( a );
                }
            }
            else {
                a++;
            }
        }
    }
    return solution;
}




std::vector<Graphe*> Graphe::optimPartielle ( const std::vector<std::vector<bool>> & solutionsAdmissibles ,
    const size_t idxPoids ) const
{
    //Timer t ( "Optimisation partielle, Graphe " + graphName );

    std::vector<Graphe*> solution;
    for ( auto& a : solutionsAdmissibles )
    {
        Graphe G ( *this , a );
        _Graphe _g ( G , idxPoids );
        float total = 0.0f;
        for ( size_t i = 0; i < m_sommets.size ( ); ++i )
        {
            auto dij = _g.dijkstra ( i );
            for ( auto& b : dij )
            {
                total += b.second;
            }
        }
        G.m_poidsTotaux.at ( idxPoids ) = total;
        solution.push_back ( new Graphe ( G ) );
    }


    return Pareto ( solution );
}

std::vector<Graphe*> Graphe::optimBiObj ( const std::vector<std::vector<bool>> & solutionsAmissibles )const
{
    Timer ( "Optimisation bi-objectif, Graphe " + graphName );
    std::vector<Graphe*> solution;
    //Remplir le vector avec toutes les solutions admissibles
    for ( auto& a : solutionsAmissibles )
    {
        solution.push_back ( new Graphe ( *this , a ) );
    }

    return Pareto ( solution );
}

std::vector<float> Graphe::getPoidsTotaux ( ) const
{
    return m_poidsTotaux;
}




std::vector<std::vector<bool>> Graphe::bruteforce ( int tri )const
{
    //Timer t ( "Brute force pour le graphe : " + graphName );
    std::vector<Sommet*> Sommetsmap = m_sommets;
    std::vector<Arete*> Aretesvec = m_Aretes;

    std::vector<bool> compteur ( Aretesvec.size ( ) + 1 , 0 );
    std::vector<std::vector<bool>> compteurs;

    while ( compteur.back ( ) != 1 )
    {

        /// Compteur
        int j = 0;
        for ( unsigned int i = 0; i < compteur.size ( ) - 1; i++ )
        {
            if ( compteur [ i ] == 1 )
            {
                j++;
            }
        }

        /// Tri
        if ( tri == 1 )
        {
            if ( j == Sommetsmap.size ( ) - 1 )
            {
                std::vector<Arete*> AretesN;
                for ( unsigned int k = 0; k < compteur.size ( ) - 1; k++ )
                {
                    if ( compteur [ k ] == 1 )
                    {
                        AretesN.push_back ( m_Aretes [ k ] );
                    }
                }

                std::vector<int> connexe;
                for ( size_t l = 0; l < m_sommets.size ( ); l++ )
                {
                    connexe.push_back ( l );
                }
                for ( auto it : AretesN )
                {
                    int s1 = it->gets1 ( );
                    int s2 = it->gets2 ( );
                    //std::cout<<s1<<":"<<connexe[s1]<<","<<s2<<":"<<connexe[s2];

                    if ( ( connexe [ s1 ] ) == ( connexe [ s2 ] ) )
                    {
                        //std::cout<<"break : ("<<s1<<","<<s2<<")"<<" ";
                        break;
                    }
                    for ( unsigned int m = 0; m < connexe.size ( ); m++ )
                    {
                        if ( ( connexe [ m ] == connexe [ s2 ] ) && ( m != s2 ) )
                        {
                            connexe [ m ] = connexe [ s1 ];
                        }
                    }
                    connexe [ s2 ] = connexe [ s1 ];
                }
                size_t temp = 0;
                for ( size_t n = 0; n < m_sommets.size ( ); n++ )
                {
                    if ( connexe [ n ] == connexe [ 0 ] )
                    {
                        temp++;
                    }
                    //std::cout<<connexe[j];
                }

                if ( temp == m_sommets.size ( ) )
                {
                    compteurs.push_back ( compteur );
                    //std::cout<<"oui";
                }//std::cout<<std::endl;
            }
        }
        else if ( tri == 2 )
        {
            std::vector<Arete*> ArretesN;
            for ( unsigned int k = 0; k < compteur.size ( ) - 1; k++ )
            {
                if ( compteur [ k ] == 1 )
                {
                    ArretesN.push_back ( m_Aretes [ k ] );
                }
            }
            std::vector<Sommet*> sommets = m_sommets;
            for(auto it: ArretesN)
            {

                for(int i=0;i<sommets.size();i++)
                {
                    if((it->gets1() == sommets[i]->getid())||(it->gets2() == sommets[i]->getid()))
                    {
                        sommets.erase(sommets.begin()+i);
                    }
                }

            }
            if(sommets.empty())
            {
                compteurs.push_back ( compteur );
            }
        }
        else
        {
            compteurs.push_back ( compteur );
        }




        /// Compteur

        for ( size_t i = 0; i < compteur.size ( ); i++ )
        {
            if ( compteur [ i ] == 1 )
            {
                compteur [ i ] = 0;
            }
            else
            {
                compteur [ i ] = 1;
                break;
            }
        }
        for ( unsigned int i = 0; i < compteur.size ( ); i++ )
        {
            //std::cout<<compteur[i];
        }//std::cout<<std::endl;
    }
    std::cout << compteurs.size ( ) << std::endl;
    return compteurs;
}

float Graphe::distanceEuclidienne ( int s1 , int s2 )  const
{
    auto x = m_sommets [ s1 ]->getx ( ) - m_sommets [ s2 ]->getx ( );
    auto y = m_sommets [ s1 ]->gety ( ) - m_sommets [ s2 ]->gety ( );
    auto dist = ( x * x ) + ( y * y );
    dist = sqrt ( dist );
    return ( float ) dist;
}

std::vector<float> Graphe::poidsTotaux ( ) const
{
    std::vector<float>solution;
    for ( size_t i = 0; i < nbCouts; i++ )
    {
        float total = 0.0f;
        for ( auto& a : m_Aretes ) {
            total += a->getcout ( ).at ( i );
        }
        solution.push_back ( total );
    }
    return solution;
}
