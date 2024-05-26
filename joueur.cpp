#include "joueur.h"

joueur::joueur(){

}

bool joueur::getIndexQuadActif1()
{
    return indexQuadActif1;
}

std::string joueur::getNameQuadActif(){
    if (indexQuadActif1){
        return q1->getName();
    }
    else{
        return q2->getName();
    }
}

void joueur::switchIndexQuadActif1()
{
    indexQuadActif1 = !indexQuadActif1 ;
}

terrain* joueur::getTerrainActif()
{
    return terrainActif;
}

void joueur::setTerrainActif(terrain* newTerrainActif)
{

    terrainActif = newTerrainActif;
    terrainInitialized = true;
}

void joueur::addQuad1(quadrimon* q)
{
    q1=q;
}

void joueur::addQuad2(quadrimon* q)
{
    q2=q;
}

int joueur::effet_terrain(bool autre_terrain_existe, terrain* terrain_autre_joueur) // return : 0=default, 1=joueur a perdu, 2= grotte,
    // autre terrain existe sert a eviter les erreurs sur un joueur qui prend chat alors que l'autre joueur n'a pas de terrain
{
    if(terrainInitialized){ // verifie qu'un terrain a été initialisé pour eviter les errerus de pointeurs null
        if (terrainActif->getTerrain_enable()){ //VERIFIE SI LE TERRAIN EST ACTIF
            std::string nom_terrain = terrainActif->getName();
            if(nom_terrain=="chat" && autre_terrain_existe){
                nom_terrain = terrain_autre_joueur->getName();

                // PARTIE OU ON VERIFIE MANUELLEMENT CAR IL FAUDRAIT CHANGER DES VARIABLES DE TERRAINS
                if(nom_terrain=="infirmerie"){
                    if(est_attaque(-1000,10)){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE + type a 10 pour être sur de ne pas activer d'avantage de type
                        return 1;
                    }
                } else if (nom_terrain=="ouragan"){
                    if(est_attaque(-100,10)){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE + type a 10 pour être sur de ne pas activer d'avantage de type
                        return 1;
                    }
                } else if (nom_terrain=="marais"){
                    if(est_attaque(50,10)){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE + type a 10 pour être sur de ne pas activer d'avantage de type
                        return 1;
                    }
                }
            }

            if (terrainActif->getEffet_spe()){
                if(est_attaque(terrainActif->getValue(),10)){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE + type a 10 pour être sur de ne pas activer d'avantage de type
                    return 1;
                }
            } else {
                if(nom_terrain=="grotte"){
                    return 2;
                } else if (nom_terrain=="toile"){
                    if(!terrainActif->getEffet_unique_done()){

                        if(q1->getAttaque()>100){
                            q1->setAttaque(q1->getAttaque()-100);
                        }else{
                            q1->setAttaque(0); // Pour eviter d'avoir une attaque qui heal l'adversaire
                        }

                        if(q2->getAttaque()>100){
                            q2->setAttaque(q2->getAttaque()-100);
                        }else{
                            q2->setAttaque(0); // Pour eviter d'avoir une attaque qui heal l'adversaire
                        }
                        terrainActif->setEffet_unique_done(true);
                    }
                }else if (nom_terrain=="plage"){
                    double_boost=true;
                    if(!terrainActif->getEffet_unique_done()){
                        q1->setType(3);
                        q2->setType(3);
                        terrainActif->setEffet_unique_done(true);
                    }

                }else if (nom_terrain=="volcan"){
                    if(!terrainActif->getEffet_unique_done()){

                        if(q1->getType()==1&& !q1_ko){
                            q1->setAttaque(q1->getAttaque()+100);
                        }
                        q1->setType(1);
                        if(q2->getType()==1&& !q2_ko){
                            q1->setAttaque(q1->getAttaque()+100);
                        }
                        q2->setType(1);
                        terrainActif->setEffet_unique_done(true);
                    }

                }else if (nom_terrain=="foret"){
                    if (q1->getType_origine()==2 && !q1_ko){
                        q1->setPv(q1->getPv()+50);
                    }
                    if (q2->getType_origine()==2 && !q2_ko){
                        q2->setPv(q2->getPv()+50);
                    }

                    if(!terrainActif->getEffet_unique_done()){
                        q1->setType(2);
                        q2->setType(2);
                        terrainActif->setEffet_unique_done(true);
                    }

                }
            }
            getTerrainActif()->reduc_tour();
        }
    }
    return 0;
}

bool joueur::est_attaque(int degats, int type) // Renvoie true si plus de quadrimon vivant, false sinon
{
    double k =attaque_boostee(type);
    std::cout<<k<<std::endl;
    if (indexQuadActif1) {
        q1->setPv(q1->getPv()-k*degats);
        if (q1->getPv()<=0) {
            q1_ko=true;
            if (q2_ko) return true;
            switchIndexQuadActif1();
        }
    } else {
        q2->setPv(q2->getPv()-k*degats);
        if (q2->getPv()<=0){
            q2_ko=true;
            if (q1_ko) return true;
            switchIndexQuadActif1();
        }
    }
    return false;
}

int joueur::degats_a_infliger()
{
    if (indexQuadActif1) return q1->getAttaque();
    return q2->getAttaque();
}

int joueur::get_type_attaque(){
    if (indexQuadActif1) return q1->getType();
    return q2->getType();
}
std::string joueur::get_q1_txt()
{
    return q1->toString();
}

std::string joueur::get_q2_txt()
{
    return q2->toString();
}

bool joueur::getQ1_ko() const
{
    return q1_ko;
}

bool joueur::getQ2_ko() const
{
    return q2_ko;
}

double joueur::attaque_boostee(int type_attaque) //RENVOIE LE COEFF D AVANTAGE SUR LE TYPE DU QUAD ACTIF
{
    //std::cout<<type_attaque<<double_boost<<std::endl;
    if(type_attaque==3){ //CAS SPECIAL CAR NE REPOND PAS A LA REGLE DU +1 : type1 > type2 > type3 > type1
        if(indexQuadActif1){
            if(q1->getType()==1){
                if (double_boost){
                    return 2.5;
                }
                return 2;
            }
        }else{
            if(q2->getType()==1){
                if (double_boost){
                    return 2.5;
                }
                return 2;
            }
        }
    } else {
        if(indexQuadActif1){
            if(q1->getType()-type_attaque == 1){
                return 2;
            }
        } else {
            if(q2->getType()-type_attaque == 1){
                return 2;
            }
        }
    }
    return 1;
}

bool joueur::getTerrainInitialized() const
{
    return terrainInitialized;
}
