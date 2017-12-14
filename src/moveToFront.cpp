//
//  moveToFront.cpp
//  Projet Codage Cryptographie
//  Source: https://en.wikipedia.org/wiki/Move-to-front_transform
//  TODO: Ajouter un parametre pour faire une sortie console de debug.
//  TODO: Passer en paramètre la borne basse et borne haute de la table ascii // Passer par map.
//
//  Created by Kévin GRILLET & Anthony BASTARD on 19/10/2016.
//  Copyright © 2016 Kévin GRILLET & Anthony BASTARD. All rights reserved.
//

#include "moveToFront.hpp"

/**
 * Nombre de symboles de la table ascii,
 * moins les 31 premiers spéciaux,
 * soit de " " à "~".
 * Source: http://www.table-ascii.com/
 */
const int NB_SYMBOLES = 126-31;

/**
 * Constructeurs de la classe MoveToFront
 * @version 1
 */
MoveToFront::MoveToFront(){};

/**
 * Applique le codage MoveToFront
 * @version 1
 * @param chaineACoder chaine a coder
 * @return string la chaine encodee
 */
string MoveToFront::encode(string chaineACoder){
    string chaineCodee = "";
    
    char tableSymboles[NB_SYMBOLES];
    for( int x = 0; x < NB_SYMBOLES; x++ ){
        if (x!=NB_SYMBOLES) {
            /**
             * Ajout d'espace, 32ème symbole.
             * @see NB_SYMBOLES
             */
            tableSymboles[x] = x + ' ';
        }
    }
    
    for (int i=0; i<(int) chaineACoder.length(); i++) {
        for (int j=0; i<NB_SYMBOLES; j++) {
            if (chaineACoder.data()[i]==tableSymboles[j]) {
                if (i>0) {
                    chaineCodee.append(" ");
                }
                chaineCodee.append(to_string(j));
                
                char tmp = tableSymboles[j];
                for (int x=j-1; x>=0; x--) {
                    tableSymboles[x+1]=tableSymboles[x];
                }
                tableSymboles[0]=tmp;
                break;
            }
        }
    }
    
    return chaineCodee;
}

/**
 * Applique le decodage MoveToFront
 * @version 1
 * @param chaineADecoder chaine a decoder
 * @return string la chaine decodee
 */
string MoveToFront::decode(string chaineADecoder){
    string chaineDecodee = "";
    
    char tableSymboles[NB_SYMBOLES];
    for( int x = 0; x < NB_SYMBOLES; x++ ){
        tableSymboles[x] = x + ' ';
    }
    
    for (int i=0; i<(int) chaineADecoder.length(); i++) {
        if (chaineADecoder.data()[i] != ' ') {
            int symbole=0;
            bool symboleTrouve=false;
            do {
                if (isdigit(chaineADecoder.data()[i])) {
                    symbole = symbole * 10 + (chaineADecoder.data()[i] - '0');
                    i++;
                }else{
                    symboleTrouve=true;
                }
            } while (!symboleTrouve);
            
            char tmp = tableSymboles[symbole];
            stringstream oss;
            oss<<tmp;
            chaineDecodee.append(oss.str());
            
            for (int x=symbole-1; x>=0; x--) {
                tableSymboles[x+1]=tableSymboles[x];
            }
            tableSymboles[0]=tmp;
        }
    }
    return chaineDecodee;
}
