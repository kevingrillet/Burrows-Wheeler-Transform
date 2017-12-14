//
//  fichier.cpp
//  Projet Codage Cryptographie
//  TODO: Ajouter un parametre pour faire une sortie console de debug.
//
//  Created by Kévin GRILLET & Anthony BASTARD on 5/12/2016.
//  Copyright © 2016 Kévin GRILLET & Anthony BASTARD. All rights reserved.
//

#include "fichier.hpp"

/**
 * Constructeurs de la classe Fichier
 * @version 1
 */
Fichier::Fichier(){}

/**
 * Renvoie le contenu du fichier en parametre
 * @version 1
 * @param nomFichier nom du fichier a lire
 * @return string contenu du fichier
 */
string Fichier::lire(string nomFichier){
    string retour="";
    ifstream fichier(nomFichier.c_str(), ios::in);
    if(fichier){
        string ligne;
        while(getline(fichier, ligne)){
			retour+=ligne;
        }
        fichier.close();
    }else{
        cerr << "Erreur à l'ouverture !" << endl;
    }
    return retour;
}

/**
 * Ecrit dans le fichier en parametre
 * Le cree si il n'existe pas
 * @version 1
 * @param nomFichier nom du fichier a ecrire
 * @param chaine a ecrire
 */
void Fichier::ecrire(string nomFichier, string chaine){
    ofstream fichier(nomFichier, ios::app);
	if(fichier){
		fichier<<chaine;
		fichier.close();
	}else{
        cerr << "Erreur à l'ouverture !" << endl;
    }
}
