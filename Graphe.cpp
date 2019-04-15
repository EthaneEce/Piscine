#include <fstream>
#include "Graphe.h"

Graphe::Graphe()
{
    //ctor
}

Graphe::Graphe(std::string nomFichier1,std::string nomFichier2)
{
    std::ifstream ifs1{nomFichier1};
    if (!ifs1)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier1 );

    std::ifstream ifs2{nomFichier2};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier2 );

    int ordre;
    ifs1 >> ordre;
    if ( ifs1.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int id1;
    double x1,y1;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs1>>id1; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs1>>x1; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs1>>y1; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id1,new Sommet{id1,x1,y1}});
    }

    int taille,taille2;
    ifs1 >> taille;
    if ( ifs1.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    ifs2 >> taille2;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe2");
    if ( taille!=taille2 )
        throw std::runtime_error("Probleme de taille des arretes, elles ne coincident pas");

    int nombrecout;
    ifs2 >> nombrecout;
    //std::cout<<nombrecout<<"aze"<<std::endl;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture nombre des couts du graphe2");

    int id2;
    int x2,y2;

    //lecture des arrete
    for (int i=0; i<taille; ++i)
    {
        ifs1>>id2; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données arrete");
        ifs1>>x2; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données arrete");
        ifs1>>y2; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données arrete");
        std::vector<float> Cout;
        int arreteid;
        ifs2>>arreteid; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données arrete");
        if(arreteid != id2)
            throw std::runtime_error("Probleme de id des arretes, elles ne coincident pas");
        for (int i=0; i<nombrecout; ++i)
        {
            float coutnbr;
            ifs2 >> coutnbr; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données arrete");
            Cout.push_back(coutnbr);
        }
        m_arretes.insert({id2,new Arrete{id2,x2,y2,Cout}});
    }


}

Graphe::~Graphe()
{
    //dtor
}

void Graphe::afficher() const
{
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"ordre : "<<m_sommets.size()<<std::endl;
    for(auto it: m_sommets)
    {
        std::cout<< "->";
        it.second->afficherData();
        std::cout<< std::endl;
    }
    std::cout<<"taille : "<<m_arretes.size()<<std::endl;
    for(auto it: m_arretes)
    {
        std::cout<< "->";
        it.second->afficherData();
        std::cout<< std::endl;
    }

}
