#include <fstream>
#include "Graphe.h"
#include <functional>
#include <algorithm>
#include <unordered_set>
#include <memory>

Graphe::Graphe ( std::vector<Sommet*> mS , std::vector<Arrete*> mA )
: m_sommets ( mS ) , m_arretes ( mA )
{
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
        m_sommets.push_back ( new Sommet{id1, x1, y1});
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

    int nombrecout;
    ifs2 >> nombrecout;
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
        for ( int i = 0; i < nombrecout; ++i )
        {
            float coutnbr;
            ifs2 >> coutnbr;
            if ( ifs1.fail ( ) )
                throw std::runtime_error ( "Probleme lecture donn�es arrete" );
            Cout.push_back ( coutnbr );
        }
        m_arretes.push_back( new Arrete{id2, x2, y2, Cout}  );
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


void Graphe::afficherallegro(BITMAP*buffer,double x, double y,int proportion) const
{
    for ( auto it : m_arretes )
    {

        int sommet1id = it->gets1 ( );
        int sommet2id = it->gets2 ( );

        Sommet* n1;
        Sommet* n2;
        for ( auto it2 : m_sommets )
        {
            if(sommet1id == it2->getid())
            {
                n1 = it2;
            }
            if(sommet2id == it2->getid())
            {
                n2 = it2;
            }
        }

        for ( int j = 5; j >= -5; j-- )
        {
            for ( int i = -5; i <= 5; i++ )
            {
                line ( buffer , (x + n1->getx ( ) + i)/proportion , (y + n1->gety ( ) + i)/proportion , (x + n2->getx ( ) + j)/proportion , (y + n2->gety ( ) + j)/proportion , makecol ( 255 , 255 , 255 ) );
            }
        }
        textprintf_centre_ex ( buffer , font , (x + ( n1->getx ( ) + n2->getx ( ) ) / 2)/proportion , (y + ( n1->gety ( ) + n2->gety ( ) ) / 2)/proportion , makecol ( 0 , 0 , 0 ) , makecol ( 255 , 255 , 255 ) , "%d" , it->getid ( ) );
    }
    int texte1 = 0;
    for ( auto it : m_arretes )
    {
        std::vector<float> couts;
        couts = it->getcout ( );
        textprintf_centre_ex ( buffer , font , x + SCREEN_W - 300 , y + 100 + texte1 , makecol ( 0 , 0 , 0 ) , makecol ( 255 , 255 , 255 ) , "Cout de %d --> " , it->getid ( ) );
        int texte2 = 0;
        for ( auto it2 : couts )
        {
            textprintf_centre_ex ( buffer , font , x + SCREEN_W - 200 + texte2 , y + 100 + texte1 , makecol ( 0 , 0 , 0 ) , makecol ( 255 , 255 , 255 ) , "%f " , it2 );
            texte2 += 100;
        }
        texte1 += 10;
    }

    for ( auto it : m_sommets )
    {
        circlefill ( buffer , (x + it->getx ( ))/proportion , (y + it->gety ( ))/proportion , 100/(proportion*10) , makecol ( 255 , 0 , 0 ) );
        textprintf_centre_ex ( buffer , font , (x + it->getx ( ))/proportion , (y + it->gety ( ) )/proportion, makecol ( 255 , 255 , 0 ) , makecol ( 255 , 0 , 0 ) , "%d" , it->getid ( ) );
    }
}

void Graphe::afficherallegrotout(BITMAP*buffer,double x, double y,int proportion) const
{
    std::vector<std::vector<bool>> Ttgraphes;
    Graphe b(m_sommets,m_arretes);
    Ttgraphes=b.bruteforce(1);
    int k=x,l=y;
    std::vector<Arrete*> ArretesN;

    for(unsigned int i = 0; i < Ttgraphes.size ( ); i++)
    {
        for ( unsigned int j = 0; j < Ttgraphes[i].size ( ); j++ )
        {
            if ( Ttgraphes [ i ] [ j ] == true )
            {
                ArretesN.push_back ( b.getarretes() [ j ]  );
            }
        }
        Graphe* a = new Graphe ( b.getsommets() , ArretesN );
        a->afficherallegro(buffer,k,l,proportion);
        k+=500;
        if (k >= 5000)
        {
            //l+=500;
            l+=500;
            k=0;
        }
        ArretesN.clear();
    }
}

/**std::vector<Arrete*> Graphe::Kruskal ( size_t cout_id ) const
{

    //Map Solution
    std::unordered_map<int , Arrete*> solution;

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
    std::vector<std::pair<int , Arrete*>> vec;
    std::copy ( m_arretes.begin ( ) , m_arretes.end ( ) ,
        std::back_inserter<std::vector<std::pair<int , Arrete*>>> ( vec ) );


    //trier le vector en fonction du cout reçu en parametre
    auto sortFunction = [ = ] ( const std::pair<int , Arrete*> & p1 , const std::pair<int , Arrete*> & p2 ) {
        return p1.second->getcout ( ).at ( cout_id ) < p2.second->getcout ( ).at ( cout_id );
    };
    std::sort ( vec.begin ( ) , vec.end ( ) , sortFunction );



    //Algo de Kruskal
//pour chaque arete
    for ( auto& a : vec )
    {
        //Trouver les sommets
        auto s1 = composantesConnexes.find ( a.second->gets1 ( ) );
        auto s2 = composantesConnexes.find ( a.second->gets2 ( ) );

        //S'ils ne sont pas sur la meme composante connexe
        if ( *( s1->second ) != *( s2->second ) )
        {
            //Inserer l'arete
            solution.insert ( { a.first, a.second } );

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

    std::vector<Arrete*> Arretesvec;
    for ( auto it : solution )
    {
        Arretesvec.push_back ( it.second );
    }
    return Arretesvec;
}**/

std::vector<std::vector<bool>> Graphe::bruteforce ( bool tri)
{
    std::vector<Sommet*> Sommetsmap = m_sommets;
    std::vector<Arrete*> Arretesvec = m_arretes;

    std::vector<bool> compteur(Arretesvec.size ( )+1, 0);
    std::vector<std::vector<bool>> compteurs;

    while ( compteur [ compteur.size ( ) - 1 ] != 1 )
    {

        /// Tri
        if (tri == true)
        {
            int j = 0;
            for ( unsigned int i = 0; i < compteur.size ( ); i++ )
            {

                if ( compteur [ i ] == 1 )
                {
                    j++;
                }
            }
            if(j==Sommetsmap.size()-1)
            {
                std::vector<Arrete*> ArretesN;
                for ( unsigned int j = 0; j < compteur.size(); j++ )
                {
                    if ( compteur [ j ] == true )
                    {
                        ArretesN.push_back ( m_arretes [j]  );
                    }
                }
                Graphe* a = new Graphe ( m_sommets , ArretesN );
                std::vector<int> connexe;
                for (int j = 0; j < m_sommets.size( ); j++ )
                {
                    connexe.push_back(j);

                }
                for(auto it: ArretesN)
                {
                    int s1 = it->gets1();
                    int s2 = it->gets2();

                    if(connexe[s1] == connexe[s2])
                    {
                        break;
                    }

                    for ( unsigned int j = 0; j < connexe.size(); j++ )
                    {
                        if(connexe[j] == connexe[s2])
                        {
                            connexe[j] = connexe[s1];
                        }
                    }
                    connexe[s2] = connexe[s1];
                }
                int temp=0;
                for (int j = 0; j < m_sommets.size( ); j++ )
                {
                    if(connexe[j] == connexe[0])
                    {
                        temp++;
                    }
                }

                if(temp==m_sommets.size())
                {
                    compteurs.push_back(compteur);
                }
            }
        }
        else
        {
            compteurs.push_back(compteur);
        }


        /// Compteur

        for ( unsigned int i = 0; i < compteur.size ( ); i++ )
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
    return compteurs;
}
