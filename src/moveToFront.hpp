//
//  moveToFront.hpp
//  Projet Codage Cryptographie
//
//  Created by Kévin GRILLET & Anthony BASTARD on 19/10/2016.
//  Copyright © 2016 Kévin GRILLET & Anthony BASTARD. All rights reserved.
//

#pragma once
#ifndef moveToFront_hpp
#define moveToFront_hpp

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class MoveToFront{
    public:
        MoveToFront();
        string encode(string chaineACoder);
        string decode(string chaineADecoder);
};

#endif /* moveToFront_hpp */
