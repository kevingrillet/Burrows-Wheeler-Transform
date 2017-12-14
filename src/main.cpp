//
//  main.cpp
//  Projet Codage Cryptographie
//  TODO: Gestion DEBUG_LEVEL en parametre.
//  TODO: Gestion d'exception (fichier introuvable, char non reconnu, decodage impossible)
//  TODO: Interface QT
//
//  Created by Kévin GRILLET & Anthony BASTARD on 18/10/2016.
//  Copyright © 2016 Kévin GRILLET & Anthony BASTARD. All rights reserved.
//

#include "main.hpp"
#include "burrowsWheelerTransform.cpp"
#include "moveToFront.cpp"
#include "huffman.cpp"
#include "fichier.cpp"

const int DEBUG_LEVEL = 1;

/**
 * Fonction principale
 * @version 3
 * @see afficherAide
 * @see encoderFichier
 * @see decoderFichier
 * @param argc nombre d'arguments
 * @param argv tableau des arguments
 * @return int 0 si OK
 */
int main(int argc, char const *argv[]){
    cout<<"Projet Cryptographie v1.0"<<endl;
    if(argc==1){
        bool loop=true;
        while(loop){
            int commande = -1;
            string nomFic="";
            cout<<"Menu:"<<endl;
            cout<<"  1: Encoder"<<endl;
            cout<<"  2: Decoder"<<endl;
            cout<<"  3: Aide"<<endl<<endl;
            cout<<"  0: Quitter"<<endl;
            cout<<"Entrez votre choix: ";
            cin>>commande;
            switch(commande){
                case 0:
                    loop=false;
                break;
                case 1:
                    cout<<"Entrez le nom du fichier: ";
                    while(nomFic==""){
                        cin>>nomFic;
                    }
                    encoderFichier(nomFic);
                break;
                case 2:
                    cout<<"Entrez le nom du fichier: ";
                    while(nomFic==""){
                        cin>>nomFic;
                    }
                    decoderFichier(nomFic);
                break;
                case 3:
                    afficherAide();
                break;
                default:
                    cout<<"Commande non reconnue."<<endl;
            }
        }
        return 0;
    }else if(argc==3){
        if(strcmp(argv[1],"-e")){
            encoderFichier(argv[2]);
        }else if(strcmp(argv[1],"-d")){
            decoderFichier(argv[2]);
        }else{
            cout<<"Parametre non reconnue."<<endl;
        }
    }
    afficherAide();
    return 0;
}

/**
 * Affiche l'aide
 * @version 1.0
 */
void afficherAide(){
    cout<<"Utilisation:"<<endl;
    cout<<"  ./main"<<endl;
    cout<<"    Version graphique"<<endl;
    cout<<"  ./main -[hed] [nomFic]"<<endl;
    cout<<"    -h: affiche l'aide'"<<endl;
    cout<<"    -e: encode le fichier"<<endl;
    cout<<"    -d: decode le fichier"<<endl;
}

/**
 * Applique l'encodage au fichier
 * @version 1.0
 * @see Fichier
 * @see BurrowsWheelerTransform
 * @see MoveToFront
 * @see Huffman
 * @see Fichier::lire
 * @see BurrowsWheelerTransform::encode
 * @see MoveToFront::encode
 * @see Huffman::encode
 * @see Fichier::ecrire
 * @param fichier Fichier qui sera encode
 */
void encoderFichier(string fichier){
    Fichier* fic = new Fichier();
    BurrowsWheelerTransform* BWT = new BurrowsWheelerTransform();
    MoveToFront* MTF = new MoveToFront();
    Huffman* HT = new Huffman();

    string chaine = fic->lire(fichier);
    //float tailleChaine = (float)chaine.length()*8;
    if (DEBUG_LEVEL>0) {
        cout<<"Chaine à encoder: "<<endl<<chaine<<endl<<endl;
    }

    chaine = BWT->encode(chaine);
    if (DEBUG_LEVEL>0) {
        cout<<"<===== BWTEncode =====>"<<endl<<chaine<<endl<<endl;
    }

    chaine = MTF->encode(chaine);
    if (DEBUG_LEVEL>0) {
        cout<<"<===== MTFEncode =====>"<<endl<<chaine<<endl<<endl;
    }
    
    chaine = HT->encode(chaine);
    if (DEBUG_LEVEL>0) {
        cout<<"<=== HuffmanEncode ===>"<<endl<<chaine<<endl<<endl;
    }
    fic->ecrire("encode_"+fichier,chaine);

    //float tailleCompresse = (float)chaine.length();
    //float compression = 1 - tailleCompresse/tailleChaine;   
    //cout<<"Compression: "<<compression<<endl;
}

/**
 * Applique le decodage au fichier
 * @version 1.0
 * @see Fichier
 * @see BurrowsWheelerTransform
 * @see MoveToFront
 * @see Huffman
 * @see Fichier::lire
 * @see BurrowsWheelerTransform::decode
 * @see MoveToFront::decode
 * @see Huffman::decode
 * @see Fichier::ecrire
 * @param fichier Fichier qui sera decode
 */
void decoderFichier(string fichier){
    Fichier* fic = new Fichier();
    Huffman* HT = new Huffman();
    MoveToFront* MTF = new MoveToFront();
    BurrowsWheelerTransform* BWT = new BurrowsWheelerTransform();

    string chaine = fic->lire(fichier);
    if (DEBUG_LEVEL>0) {
        cout<<"Chaine à decoder: "<<endl<<chaine<<endl<<endl;
    }

    chaine = HT->decode(chaine);
    if (DEBUG_LEVEL>0) {
        cout<<"<=== HuffmanDecode ===>"<<endl<<chaine<<endl<<endl;
    }

    chaine = MTF->decode(chaine);
    if (DEBUG_LEVEL>0) {
        cout<<"<===== MTFDecode =====>"<<endl<<chaine<<endl<<endl;
    }
    chaine = BWT->decode(chaine);
    if (DEBUG_LEVEL>0) {
        cout<<"<===== BWTDecode =====>"<<endl<<chaine<<endl<<endl;
    }
    fic->ecrire("decode_"+fichier,chaine);
}
