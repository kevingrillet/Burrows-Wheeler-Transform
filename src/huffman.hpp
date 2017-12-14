//
//  huffman.hpp
//  Projet Codage Cryptographie
//
//  Created by Kévin GRILLET & Anthony BASTARD on 01/12/2016.
//  Copyright © 2016 Kévin GRILLET & Anthony BASTARD. All rights reserved.
//

#pragma once
#ifndef huffman_hpp
#define huffman_hpp

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Node{
    private:
        string chaine;
        int frequence;
        Node* filsGauche;
        Node* filsDroit;
    public:
        Node(string chaine, int frequence);
        void setFrequence(int frequence);
        void addFils(Node* fg, Node* fd);
        string getChaine();
        int getFrequence();
        Node* getFilsGauche();
        Node* getFilsDroit();
        void makeHash(map<string,string>* hash, string code);
        string toString();
        void print(int offset);
        string decode(string* chaineADecoder);
};

class Tree{
    private:
        Node* root;
    public:
        Tree(Node* root);
        Node* getRoot();
        string toString();
        void print();
        string decode(string* chaineADecoder);
};

class Huffman{
    private:
        map<string, Node*> histogram(string chaineAEncoder);
        Tree* makeTree(map<string, Node*> mapHistogramme);
        map<string,string> makeHash(Tree* tree);
    public:
        Huffman();
        string encode(string chaineAEncoder);
        string decode(string chaineADecoder);
};

#endif /* huffman_hpp */
