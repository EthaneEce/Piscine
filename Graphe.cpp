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



Graphe::Graphe ( const std::vector<std::shared_ptr<Sommet>>& mS ,
    const std::vector<std::shared_ptr<Arete>>& mA ,
    const std::string& nom_graphe )
    : m_sommets ( mS ) , m_Aretes ( mA ) , graphName ( nom_graphe )
{
    nbCouts = m_Aretes [ 0 ]->getcout ( ).size ( );
    m_poidsTotaux = poidsTotaux ( );
}

Graphe::Graphe ( const Graphe& src , const std::vector<bool>& vec , const std::string& nom_graphe ) : graphName ( src.graphName )
{
    std::vector<std::shared_ptr<Arete>> temp;
    for ( size_t i = 0; i < vec.size ( ); i++ )
    {
        if ( vec.at ( i ) & true ) {
            temp.push_back ( src.m_Aretes.at ( i ) );
        }
    }
    if ( temp.empty ( ) )
        temp.push_back ( std::make_shared<Arete> ( src.nbCouts ) );
    *this = Graphe ( src.m_sommets , temp );
    m_poidsTotaux = poidsTotaux ( );
}

Graphe::Graphe ( std::string nomFichier1 , std::string nomFichier2 ) : graphName ( nomFichier1 + " | " + nomFichier2 )
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
        m_sommets.push_back ( std::make_shared <Sommet > ( id1 , x1 , y1 ) );
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
        m_Aretes.push_back ( std::make_shared <Arete> ( id2 , x2 , y2 , Cout ) );
    }
    m_poidsTotaux = poidsTotaux ( );
}


void Graphe::afficher ( ) const
{
    std::cout << "graphe : " << std::endl;
    std::cout << "ordre : " << m_sommets.size ( ) << std::endl;
    for ( auto& it : m_sommets )
    {
        std::cout << "->";
        it->afficherData ( );
        std::cout << std::endl;
    }
    std::cout << "taille : " << m_Aretes.size ( ) << std::endl;
    for ( auto& it : m_Aretes )
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

        std::shared_ptr<Sommet> n1;
        std::shared_ptr<Sommet> n2;
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

std::vector<std::shared_ptr<Arete>> Graphe::Kruskal ( size_t cout_id ) const
{
    if ( cout_id >= m_poidsTotaux.size ( ) )
        throw std::runtime_error ( "Cout n'existe pas" );
    Timer t ( "Kruskal a partir du graphe " + graphName );
    //Map Solution
    std::vector<std::shared_ptr<Arete>> solution;

    //Associer un sommet et sa composante connexe
    std::vector<int> composantesConnexes;

    //Au déput chaque sommet est sur une composante connexe
    for ( size_t i = 0; i < m_sommets.size ( ); i++ )
    {
        composantesConnexes.push_back ( i );
    }

    //Vector dans lequel on va mettre notre map d'Aretes
    std::vector<std::shared_ptr<Arete>> vec ( m_Aretes );


    //trier le vector en fonction du cout reçu en parametre
    auto sortFunction = [ & ] ( std::shared_ptr<Arete> & a1 , std::shared_ptr<Arete> & a2 ) {
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


            //Mettre à jour pour que les sommets soient sur la meme composante connexe
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


std::vector<std::shared_ptr<Graphe>> Graphe::Pareto ( std::vector<std::shared_ptr<Graphe>> & solution ) const
{
    Timer t ( "Pareto pour le graphe " + graphName );
    const constexpr float infini = std::numeric_limits<float>::max ( );

    size_t IDXpoidsCourant = 0;

    //Pour chaque poids allant de 0 à nombre de couts totaux - 1
    while ( IDXpoidsCourant < nbCouts - 1 )
    {

        //Tronquer les éléments qui seront certainement dominées
        {
            //Initialiser nos comparateurs
            float min = infini;           //Cout minimal courant
            float nMinCout = infini;      //Cout suivant du graphe qui le cout minimal


            //Récupérer le cout minimal (ce sera le premier élément du vector quand on le trie) 
            for ( auto& a : solution )
            {
                if ( a->m_poidsTotaux.at ( IDXpoidsCourant ) < min ) {
                    min = a->m_poidsTotaux.at ( IDXpoidsCourant );
                    nMinCout = a->m_poidsTotaux.at ( IDXpoidsCourant + 1 );
                }
            }

            //Supprimer toutes les solutions dominées par celle qu'on vient de trouver
            solution.erase ( std::remove_if ( solution.begin ( ) , solution.end ( ) ,
                [ = ] ( std::shared_ptr<Graphe > & g ) {
                    return g->getPoidsTotaux ( ).at ( IDXpoidsCourant + 1 ) > nMinCout;
                } ) , solution.end ( ) );
        }

        //Trier le vector solution
        auto sortFunction = [ = ] ( std::shared_ptr<Graphe> & g1 , std::shared_ptr<Graphe> & g2 )
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

            if ( Cout < pivot )
            {
                pivot = Cout;
                auto iterator = std::remove_if ( a + 1 , solution.end ( ) ,
                    [ = ] ( std::shared_ptr<Graphe> & g ) {
                        return g->getPoidsTotaux ( ).at ( IDXpoidsCourant + 1 ) >= pivot;
                    } );
                solution.erase ( iterator , solution.end ( ) );
                a++;
            }
        }


        IDXpoidsCourant++;
    }

    //Un dernier parcours pour nettoyer les valeurs qui ont 1 cout égal
    for ( size_t i = 0; i < nbCouts - 1; i++ )
    {
        size_t j = 0;
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
            j++;
        }
    }
    return solution;
}


std::vector<std::shared_ptr<Graphe>> Graphe::optimPartielle ( const std::vector<std::vector<bool>> & solutionsAdmissibles ,
    const size_t idxPoids ) const
{
    Timer t ( "Optimisation partielle, Graphe " + graphName );
    std::vector<_Graphe*> stash;

    std::vector<std::shared_ptr<Graphe>> solution;
    std::cout << "Dijkstra..." << std::endl;
    {
        Timer t1 ( "Dijkstra pour chaque solution" );
        for ( auto& a : solutionsAdmissibles )
        {
            Graphe G ( *this , a );
            _Graphe* _g = new _Graphe ( G , idxPoids );
            float total = 0.0f;
            for ( size_t i = 0; i < m_sommets.size ( ); ++i )
            {
                auto dij = _g->dijkstra ( i );
                for ( auto& b : dij )
                {
                    total += b.second;
                }
            }
            G.m_poidsTotaux.at ( idxPoids ) = total;

            solution.push_back ( std::make_shared <Graphe> ( G ) );
            stash.push_back ( _g );


            if ( solution.size ( ) >= 50000 )
            {
                solution = Pareto ( solution );

                for ( auto& a : stash )
                    delete a;
                stash.clear ( );

            }
        }
    }


    for ( auto& a : stash )
        delete a;
    stash.clear ( );


    return Pareto ( solution );
}
std::vector<std::shared_ptr<Graphe>> Graphe::optimBiObj ( const std::vector<std::vector<bool>> & solutionsAmissibles )const
{
    Timer ( "Optimisation bi-objectif, Graphe " + graphName );
    std::vector<std::shared_ptr<Graphe>> solution;
    //Remplir le vector avec toutes les solutions admissibles
    for ( auto& a : solutionsAmissibles )
    {
        solution.push_back ( std::make_shared <Graphe> ( *this , a ) );
        if ( solution.size ( ) >= 50000 )
            solution = Pareto ( solution );
    }

    return Pareto ( solution );
}
std::vector<float> Graphe::getPoidsTotaux ( ) const
{
    return m_poidsTotaux;
}


std::vector<std::vector<bool>> Graphe::bruteforce ( int tri )const
{
    Timer t ( "Brute force pour le graphe : " + graphName );
    std::vector<std::shared_ptr<Sommet>> Sommetsmap = m_sommets;
    std::vector<std::shared_ptr<Arete>> Aretesvec = m_Aretes;

    std::vector<bool> compteur ( Aretesvec.size ( ) + 1 , 0 );
    std::vector<std::vector<bool>> compteurs;

    while ( compteur.back ( ) != 1 )
    {

        /// Compteur : Compte le nombre d'aretes
        unsigned int j = 0;
        for ( unsigned int i = 0; i < compteur.size ( ) - 1; i++ )
        {
            if ( compteur [ i ] == 1 )
            {
                j++;
            }
        }

        /// Tri
        if ( tri == 1 ) //Sans cycles et tous les sommets reliés
        {
            if ( j == Sommetsmap.size ( ) - 1 )
            {
                std::vector<std::shared_ptr<Arete>> AretesN;
                for ( unsigned int k = 0; k < compteur.size ( ) - 1; k++ )  // Traduction du tableau de bool en tableau d'aretes
                {
                    if ( compteur [ k ] == 1 )
                    {
                        AretesN.push_back ( m_Aretes [ k ] );
                    }
                }

                std::vector<int> connexe;  // Tableau de connexité
                for ( size_t l = 0; l < m_sommets.size ( ); l++ )
                {
                    connexe.push_back ( l );
                }
                for ( auto it : AretesN )
                {
                    int s1 = it->gets1 ( );
                    int s2 = it->gets2 ( );

                    if ( ( connexe [ s1 ] ) == ( connexe [ s2 ] ) )  // Break si meme numéro
                    {
                        break;
                    }
                    for ( int m = 0; m < connexe.size ( ); m++ )  // Changement des meme numeros
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
                }

                if ( temp == m_sommets.size ( ) ) // Si tout les numéros du tableau de connexité sont les memes, On pushback le compteur
                {
                    compteurs.push_back ( compteur );
                }
            }
        }
        else if ( tri == 2 ) //Avec cycles et tous les sommets reliés
        {
            if ( j >= Sommetsmap.size ( ) - 1 )
            {
                std::vector<std::shared_ptr<Arete>> AretesN;
                for ( unsigned int k = 0; k < compteur.size ( ) - 1; k++ )  // Traduction du tableau de bool en tableau d'aretes
                {
                    if ( compteur [ k ] == 1 )
                    {
                        AretesN.push_back ( m_Aretes [ k ] );
                    }
                }

                std::vector<int> connexe;  // Tableau de connexité
                for ( size_t l = 0; l < m_sommets.size ( ); l++ )
                {
                    connexe.push_back ( l );
                }
                for ( auto it : AretesN )
                {
                    int s1 = it->gets1 ( );
                    int s2 = it->gets2 ( );

                    for ( int m = 0; m < connexe.size ( ); m++ )  // Changement des meme numeros
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
                }

                if ( temp == m_sommets.size ( ) )   // Si tout les numéros du tableau de connexité sont les memes, On pushback le compteur
                {
                    compteurs.push_back ( compteur );
                }
            }
        }
        else // Toutes les solutions possibles
        {
            compteurs.push_back ( compteur );
        }




        /// Compteur

        for ( size_t i = 0; i < compteur.size ( ); i++ ) // Cheche un endroit ou il y a un 0,le remplace par un 1 et remplace toutes les valeurs qui sont avant par 0
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
    }
    std::cout << " compteur" << tri << " : " << compteurs.size ( ) << std::endl; // Affiche le nombre de solutions
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

std::vector<float> Graphe::poidsTotaux ( )const
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
