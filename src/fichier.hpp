//
//  fichier.hpp
//  Projet Codage Cryptographie
//
//  Created by Kévin GRILLET & Anthony BASTARD on 5/12/2016.
//  Copyright © 2016 Kévin GRILLET & Anthony BASTARD. All rights reserved.
//

#pragma once
#ifndef fichier_hpp
#define fichier_hpp

#include <string>
#include <fstream>
using namespace std;

class Fichier{
    public:
        Fichier();
        string lire(string nomFichier);
        void ecrire(string nomFichier, string chaine);
};

#endif /* fichier_hpp */
