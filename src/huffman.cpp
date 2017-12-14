//
//  huffman.cpp
//  Projet Codage Cryptographie
//  Source: https://en.wikipedia.org/wiki/Huffman_coding
//  TODO: Ajouter un parametre pour faire une sortie console de debug.
//
//  Created by Kévin GRILLET & Anthony BASTARD on 01/12/2016.
//  Copyright © 2016 Kévin GRILLET & Anthony BASTARD. All rights reserved.
//

#include "huffman.hpp"

bool sortFunction(pair<string, Node*> i, pair<string, Node*> j){
    if (i.second->getFrequence() == j.second->getFrequence())
        return i.first < j.first;
    return i.second->getFrequence() < j.second->getFrequence();
}

/**
 * Constructeurs de la classe Node
 * @version 1
 * @param c charactere
 * @param f frequence
 */
Node::Node(string c, int f):chaine(c), frequence(f), filsGauche(NULL), filsDroit(NULL){};

/**
 * Definit la frequence
 * @version 1
 * @param f frequence
 */
void Node::setFrequence(int f){
    frequence = f;
}

/**
 * Ajoute les fils
 * @version 1
 * @param fg filsGauche
 * @param fd filsDroit
 */
void Node::addFils(Node* fg, Node* fd){
    filsGauche = fg;
    filsDroit = fd;
}

/**
 * Renvoie la chaine
 * @version 1
 * @return string chaine
 */
string Node::getChaine(){
    return chaine;
}

/**
 * Renvoie la frequence
 * @version 1
 * @return int frequence
 */
int Node::getFrequence(){
    return frequence;
}

/**
 * Renvoie le filsGauche
 * @version 1
 * @return Node* filsGauche
 */
Node* Node::getFilsGauche(){
    return filsGauche;
}

/**
 * Renvoie le filsDroit
 * @version 1
 * @return Node* filsDroit
 */
Node* Node::getFilsDroit(){
    return filsDroit;
}

/**
 * Construit la table de hash pour l'encodage
 * @version 1
 * @see Node::getFilsGauche
 * @see Node::getFilsDroit
 * @see Node::makeHash
 * @param tree pointeur vers l'arbre
 * @return map<string,string> map contenant le charactere et son code
 */
void Node::makeHash(map<string,string>* hash, string code){
    if(getFilsGauche()&&getFilsDroit()){
        getFilsGauche()->makeHash(hash,code+"0");
        getFilsDroit()->makeHash(hash,code+"1");
    }else{
        /**DEBUG
        cout<<chaine<<" "<<code<<endl;
        */
        hash->operator[](chaine)=code;
    }
}

/**
 * Renvoie le fils gauche et droit sous forme de string
 * @version 1
 * @see Node::getFilsGauche
 * @see Node::getFilsDroit
 * @see Node::toString
 * @see Node::getChaine
 * @see Node::getFrequence
 * @return string liste des fils avec frequence de la forme:
 *                [fg.char]:[fg.frequence];[fd.char]:[fd.frequence];
 */
string Node::toString(){
    if(getFilsGauche()&&getFilsDroit()){
        string fg = getFilsGauche()->toString();
        string fd = getFilsDroit()->toString();
        return fg + ";" + fd;
    }else{
        return getChaine()+":"+to_string(getFrequence());
    }
}

/**
 * Permet une sortie graphique de l'arbre
 * @see Node::getFilsGauche
 * @see Node::getFilsDroit
 * @see Node::print
 * @param offset Decalage pour aider la visualisation
 */
void Node::print(int offset){
    for(int i=0; i<offset; i++){
        cout<<" ";
    }
    cout<<getChaine()<<":"<<to_string(getFrequence())<<endl;
    if(getFilsGauche()&&getFilsDroit()){
        getFilsGauche()->print(offset+1);
        getFilsDroit()->print(offset+1);
    }
}

/**
 * Parcours de l'arbre par rapport au premier charactere de la chaine a decoder
 * @version 1
 * @see Node::getFilsGauche
 * @see Node::getFilsDroit
 * @see Node::decode
 * @see Node::getChaine
 * @param chaineADecoder pointeur vers la chaine a decoder
 * @return string le charactere decode (feuille)
 */
string Node::decode(string* chaineADecoder){
    /**DEBUG
    cout<<getChaine()<<" "<<chaineADecoder->data()<<endl;
    */
    if(chaineADecoder->length()>0){
        if(string(1,chaineADecoder->at(0))==to_string(0)){
            if(getFilsGauche()){
                chaineADecoder->erase(chaineADecoder->begin());
                return getFilsGauche()->decode(chaineADecoder);
            }else{
                return getChaine();
            }
        }else if(string(1,chaineADecoder->at(0))==to_string(1)){
            if(getFilsDroit()){
                chaineADecoder->erase(chaineADecoder->begin());
                return getFilsDroit()->decode(chaineADecoder);
            }else{
                return getChaine();
            }
        }else{
            cerr<<"Erreur lors du decodage dans la lecture de l'arbre"<<endl;
            return "ERROR";
        }
    }else{
        return getChaine();
    }
}

/**
 * Constructeurs de la classe Tree
 * @version 1
 * @param Node* racine de l'arbre
 */
Tree::Tree(Node* r):root(r){};

/**
 * Renvoie la racine de l'arbre
 * @version 1
 * @return Node* racine de l'arbre
 */
Node* Tree::getRoot(){
    return root;
}

/**
 * Renvoie l'arbre sous forme de string
 * @version 1
 * @return string liste des feuilles avec frequence de la forme:
 *         [char]:[frequence];[char]:[frequence];...
 */
string Tree::toString(){
    return getRoot()->toString()+";";
}

/**
 * Permet une sortie graphique de l'arbre
 * @version 1
 * @see Node::print
 */
void Tree::print(){
    getRoot()->print(0);
}

/**
 * Appel la racine pour le decodage
 * @version 1
 * @see Node::decode
 * @param chaineADecoder pointeur vers la chaine a decoder
 * @return string le charactere decode
 */
string Tree::decode(string* chaineADecoder){
    return getRoot()->decode(chaineADecoder);
}

/**
 * Constructeurs de la classe Huffman
 * @version 1
 */
Huffman::Huffman(){}

/**
 * Construit la map histogramme
 * @version 1
 * @see Node::Node
 * @see Node::setFrequence
 * @param chaineAEncoder chaine a encoder
 * @return map<string, Node*> contenant la map histogramme
 */
map<string, Node*> Huffman::histogram(string chaineAEncoder){
    map<string, Node*> histogramme;
    for(int i=0; i<(int)chaineAEncoder.length(); i++){
        string charactere = string(1,chaineAEncoder.at(i));
        if(histogramme[charactere]){
            histogramme[charactere]->setFrequence(histogramme[charactere]->getFrequence()+1);
        }else{
            histogramme[charactere] = new Node(charactere,1);
        }
    }
    return histogramme;
}

/**
 * Construit la l'arbre a partir de la map histogramme
 * @version 1
 * @see Node::Node
 * @see Node::getFrequence
 * @see Node::addFils
 * @param mapHistogramme map de l'histogramme
 * @return Tree* contenant la racine de l'arbre
 */
Tree* Huffman::makeTree(map<string, Node*> mapHistogramme){
    vector<pair<string, Node*>> histogramme(mapHistogramme.begin(), mapHistogramme.end());
    while(histogramme.size()>1){
        sort(histogramme.begin(), histogramme.end(),sortFunction);
        
        pair<string,Node*> filsGauche = histogramme[0];
        pair<string,Node*> filsDroit = histogramme[1];
        string concat = filsGauche.first+filsDroit.first;
        int frequence = filsGauche.second->getFrequence()+filsDroit.second->getFrequence();
        histogramme.erase(histogramme.begin(),histogramme.begin()+2);

        pair<string, Node*> racine=make_pair(concat, new Node(concat,frequence));
        racine.second->addFils(filsGauche.second, filsDroit.second);
        histogramme.push_back(racine);
    }
    return new Tree(histogramme[0].second);
}

/**
 * Construit la table de hash pour l'encodage
 * @version 1
 * @see Node::makeHash
 * @param tree pointeur vers l'arbre
 * @return map<string,string> map contenant le charactere et son code
 */
map<string,string> Huffman::makeHash(Tree* tree){
    map<string,string> hash;
    tree->getRoot()->makeHash(&hash,"");
    return hash;
}

/**
 * Applique le codage Huffman
 * @version 1
 * @see Huffman::histogram
 * @see Huffman::makeTree
 * @see Huffman::makeHash
 * @param chaineAEncoder chaine a coder
 * @return string la chaine encodee
 */
string Huffman::encode(string chaineAEncoder){
    map<string,Node*> histogramme = histogram(chaineAEncoder);
    Tree* arbre = makeTree(histogramme);
    map<string,string> hash = makeHash(arbre);

    /**DEBUG
    cout<<"ARBRE"<<endl;
    arbre->print();
    cout<<endl<<"HASH"<<endl;
    vector<pair<string,string>> hash2(hash.begin(), hash.end());
    for (vector<pair<string,string>>::iterator it = hash2.begin() ; it != hash2.end(); ++it){
        cout<<it->first<<" "<<it->second<<endl;;
    }*/

    string chaineEncodee = "";
    for(int i=0; i<(int)chaineAEncoder.length(); i++){
        chaineEncodee+=hash[string(1,chaineAEncoder.at(i))];
    }
    return arbre->toString()+"/"+chaineEncodee;
}

/**
 * Applique le decodage Huffman
 * @version 1
 * @see Huffman::makeTree
 * @param chaineADecoder chaine a decoder
 * @return string la chaine decodee
 */
string Huffman::decode(string chaineADecoder){
    bool key = true;
    map<string,Node*> histogramme;
    string separateur = "/";
    string separateurHisto = ";";
    string chaineDecodee = "";
    string chaineCode = "";
    for(int i=0; i<(int)chaineADecoder.length(); i++){
        if(string(1,chaineADecoder.at(i))==separateur){
            key = false;
        }else{ 
            if(key){
                string charactere = string(1,chaineADecoder.at(i));
                i+=2;
                int frequence=0;
                while(string(1,chaineADecoder.at(i))!=separateurHisto){
                    frequence*=10;
                    frequence+=stoi(string(1,chaineADecoder.at(i)).c_str());
                    i++;
                }
                histogramme[charactere] = new Node(charactere,frequence);
            }else{
                chaineCode+=string(1,chaineADecoder.at(i));
            }
        }
    }
    Tree* arbre = makeTree(histogramme);

    /**DEBUG
    cout<<"ARBRE"<<endl;
    arbre->print();
    */

    while((int)chaineCode.length()>0){
        /** DEBUG
        //cout<<chaineDecodee<<" "<<chaineCode<<endl;
        */
        chaineDecodee+=arbre->getRoot()->decode(&chaineCode);
    }
    return chaineDecodee;
}
