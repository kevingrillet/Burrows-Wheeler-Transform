//
//  burrowsWheelerTransform.cpp
//  Projet Codage Cryptographie
//  Source: https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform
//  TODO: Ajouter un parametre pour faire une sortie console de debug.
//
//  Created by Kévin GRILLET & Anthony BASTARD on 18/10/2016.
//  Copyright © 2016 Kévin GRILLET & Anthony BASTARD. All rights reserved.
//

#include "burrowsWheelerTransform.hpp"

/**
 * Constructeurs de la classe BurrowsWheelerTransform
 * @version 1
 * Si aucun paramètre, la classe initialise decalage à droite.
 * @param 0: utilisera rotation a droite, 1: utilisera rotation a gauche.
 */
BurrowsWheelerTransform::BurrowsWheelerTransform():decalage(0){};
BurrowsWheelerTransform::BurrowsWheelerTransform(int i){
    if(i==0||i==1){
        decalage=i;
    }else{
        decalage=0;
    }
};

/**
 * Applique la rotation des charactères vers la gauche
 * @version 1
 * @param chaineACoder chaine à laquelle on applique la rotation
 * @param tailleChaineACoder taille de chaineACoder
 * @param tableauChaines pointeur pour stocker le résultat
 * @return vector<string>* vecteur contenant toutes les string de la rotation
 */
void BurrowsWheelerTransform::decalageGauche(string chaineACoder, int tailleChaineACoder, vector<string>* tableauChaines){
    tableauChaines->push_back(chaineACoder);
    for (int i=0; i<tailleChaineACoder-1; i++) {
        char charactereDebut = tableauChaines->at(i).data()[0];
        string chaineFin = tableauChaines->at(i).substr(1, tailleChaineACoder-1);
        string chaineSortie = chaineFin.insert(tailleChaineACoder-1, 1, charactereDebut);
        tableauChaines->push_back(chaineSortie);
    }
}

/**
 * Applique la rotation des charactères vers la droite
 * @version 1
 * @param chaineACoder chaine à laquelle on applique la rotation
 * @param tailleChaineACoder taille de chaineACoder
 * @param tableauChaines pointeur pour stocker le résultat
 * @return vector<string>* vecteur contenant toutes les string de la rotation
 */
void BurrowsWheelerTransform::decalageDroite(string chaineACoder, int tailleChaineACoder, vector<string>* tableauChaines){
    tableauChaines->push_back(chaineACoder);
    for (int i=0; i<tailleChaineACoder-1; i++) {
        char charactereFin = tableauChaines->at(i).data()[tailleChaineACoder-1];
        string chaineDebut = tableauChaines->at(i).substr(0, tailleChaineACoder-1);
        string chaineSortie = chaineDebut.insert(0, 1, charactereFin);
        tableauChaines->push_back(chaineSortie);
    }
}


/**
 * 
 * @param chaineACoder chaine à laquelle on applique la rotation
 * @version 1
 * @param tailleChaineACoder taille de chaineACoder
 * @param tableauChaines pointeur pour stocker le résultat
 * @return string la chaine codee
 */
string BurrowsWheelerTransform::codage(string chaineACoder, int tailleChaineACoder, vector<string>* tableauChaines){
    string chaineCodee = "";
    int positionChaineACoder = 0;
    for (int i=0; i<tailleChaineACoder; i++) {
        if (tableauChaines->at(i)==chaineACoder) {
            positionChaineACoder = i + 1;
        }
        chaineCodee = chaineCodee.insert(i, 1,tableauChaines->at(i).data()[tailleChaineACoder-1]);
    }
    chaineCodee = to_string(positionChaineACoder) + chaineCodee;
    return chaineCodee;
}

/**
 * Applique le codage Burrows-Wheeler
 * @version 1
 * @see BurrowsWheelerTransform::decalageDroite
 * @see BurrowsWheelerTransform::decalageGauche
 * @see BurrowsWheelerTransform::codage
 * @param chaineACoder chaine a coder
 * @return string la chaine encodee
 */
string BurrowsWheelerTransform::encode(string chaineACoder){
    string chaineCodee;
    int tailleChaineACoder = (int) chaineACoder.length();
    vector<string> tableauChaines;
    if(decalage==0){
        decalageDroite(chaineACoder, tailleChaineACoder, &tableauChaines);
    }else{
        decalageGauche(chaineACoder, tailleChaineACoder, &tableauChaines);
    }
    sort(tableauChaines.begin(), tableauChaines.end());
    return codage(chaineACoder, tailleChaineACoder, &tableauChaines);
}

/**
 * Applique le decodage Burrows-Wheeler
 * @version 1
 * @param chaineADecoder chaine a decoder
 * @return string la chine decodee
 */
string BurrowsWheelerTransform::decode(string chaineADecoder){
    bool positionTrouvee = false;
    int position = 0;
    int taillePosition = 0;
    do {
        if (isdigit(chaineADecoder.data()[taillePosition])) {
            position = position * 10 + (chaineADecoder.data()[taillePosition] - '0');
            taillePosition++;
        }else{
            positionTrouvee=true;
        }
    } while (!positionTrouvee);
    int tailleChaineADecoder = (int) chaineADecoder.length();
    string chaineADecoderSansPosition = chaineADecoder.substr(taillePosition, tailleChaineADecoder-taillePosition);
    int tailleChaineADecoderSansPosition = (int) chaineADecoderSansPosition.length();
    string chaineADecoderTriee = chaineADecoderSansPosition;
    sort(chaineADecoderTriee.begin(), chaineADecoderTriee.end());
    
    string chaineDecodee = "";
    int positionCourante = position;
    char lettreCourante;
    int nombreIterations;
    int nombreIterationsRecherche;
    do{
        lettreCourante = (char) NULL;
        nombreIterations = 0;
        for(int i = 0; i<positionCourante; i++){
            if (lettreCourante != chaineADecoderTriee.data()[i]) {
                lettreCourante = chaineADecoderTriee.data()[i];
                nombreIterations = 1;
            }else{
                nombreIterations++;
            }
        }
        chaineDecodee.append(&chaineADecoderTriee.data()[positionCourante-1],1);
        nombreIterationsRecherche=0;
        for (int i = 0; i<=tailleChaineADecoderSansPosition; i++) {
            if(lettreCourante==chaineADecoderSansPosition.data()[i]){
                nombreIterationsRecherche++;
                if (nombreIterations==nombreIterationsRecherche) {
                    positionCourante=i+1;
                }
            }
        }
    }while(positionCourante != position);
    return chaineDecodee;
}
