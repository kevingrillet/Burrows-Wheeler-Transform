//
//  burrowsWheelerTransform.hpp
//  Projet Codage Cryptographie
//
//  Created by Kévin GRILLET & Anthony BASTARD on 18/10/2016.
//  Copyright © 2016 Kévin GRILLET & Anthony BASTARD. All rights reserved.
//

#pragma once
#ifndef burrowsWheelerTransform_hpp
#define burrowsWheelerTransform_hpp

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class BurrowsWheelerTransform{
    private:
        int decalage;
        void decalageGauche(string chaineACoder, int tailleChaineACoder, vector<string>* tableauChaines);
        void decalageDroite(string chaineACoder, int tailleChaineACoder, vector<string>* tableauChaines);
        string codage(string chaineACoder, int tailleChaineACoder, vector<string>* tableauChaines);
    public:
        BurrowsWheelerTransform();
        BurrowsWheelerTransform(int i);
        string encode(string chaineACoder);
        string decode(string chaineADecoder);
};

#endif /* burrowsWheelerTransform_hpp */
