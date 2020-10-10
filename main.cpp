#include <iostream>
#include <cassert>
using namespace std;

const int NDIM = 3;
const char LIBRE='.';
using Grille = char [NDIM][NDIM];
/**
    Accesseur d'une case du plateau
    @param[in] gr - un plateau
    @param[in] j - numéro de ligne
    @param[in] k - numéro de colonne
    @return la valeaur en (j,k) de gr
    @pre (j,k) dans [o..NDIM[
*/
inline char evalCase(const Grille& gr, int j, int k){
    assert(0 <= j and j < NDIM and 0 <= k and k < NDIM);
    return gr[j][k];
}

/**
    Modifieur d'une case du plateau
    @param[in,out] gr - un plateau
    @param[in] j - numéro de ligne
    @param[in] k - numéro de colonne
    @param[in] valeur - la valeur
*/
inline void fixerCase(Grille& gr, int ligne, int colonne, char valeur){
    assert(0 <= ligne and ligne < NDIM and 0 <= colonne and colonne < NDIM);
    gr[ligne][colonne] = valeur;
}
/**
    @param[out] gr - Grille
*/
void initialiserPlateau (Grille& gr){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            gr[i][j] = '.';
        }
    }
}
/**
    @param[in] gr - Grille
*/
void afficherPlateau(const Grille& gr){
    system("cls");
    cout<<"             Morpion version 1.0"<<endl;
    cout<<endl<<" ";for(int x=0;x<48;x++){cout<<"#";}cout<<endl;
    cout<<" #   Y: 0           1               2           #"<<endl<<" # X    ";
    for(int x=0;x<40;x++){cout<<"_";}cout<<"#"<<endl;
    for(int i = 0; i < 3; ++i){
        cout<<" # "<< i;
        for(int j = 0; j < 3; ++j){
            cout<<"    " <<gr[i][j] <<"    \t";
        }
        cout<<"#"<<endl;
        //cout << endl;
    }
    cout<<" ";for(int x=0;x<48;x++){cout<<"#";}cout<<endl;

}
/**
    Test de case dans un plateau
    @param[in] nl - numéro de ligne
    @param[in] nc - numéro de colonne
    @param[in] gr - un plateau
    @return Vrai si (nl, nc) est dans gr
*/
bool dansPlateau(int nl, int nc, const Grille& gr){
    return (0 <= nl and nl < NDIM and 0 <= nc and nc <NDIM);
}
/**
    Teste un alignement de trois cases depuis (ix,jx)
    @param[in] joueur - numéro de joueur
    @param[in] ix - ligne de départ
    @param[in] jx - colonne de début
    @param[in] iincr - incrément en ligne
    @param[in] jincr - incrément en colonne
    @param[in] gr - un plateau
    @return Vrai si alignement, Faux sinon
*/
bool alignement(int joueur, int ix, int jx, int iincr, int jincr, const Grille& gr)
{
    assert(joueur == 'X' or joueur == 'O');
    bool b = true;
    int k = 0;
    while (k< NDIM and b)
    {
        b = b and (evalCase(gr,ix,jx) == joueur);
        ix += iincr, jx += jincr;
        ++k;
    }
    return b;
}
/**
    @param[in] joueur - Lettre du joueur
    @param[out] gr - Grille
*/

void jouer (char joueur, Grille& gr){
    int colonne, ligne;
    cout << ">>>>>> (x,y): ";
    cin >> ligne>> colonne;
    cout << endl;
    while(not dansPlateau(ligne,colonne,gr)){
        cout <<"ERREUR !" << endl;
        cout << ">>>>>> (x,y): ";
        cin >> ligne >> colonne;
        cout << endl;
    }
    fixerCase(gr,ligne,colonne,joueur);
}
/**
    Teste si joueur à gagné
    @param[in] joueur - numéro de joueur
    @param[in] gr - un plateau
    @return Vrai si joueur à gagné, faux sinon
    @pre joueur dans [-1..1]
*/
bool victoire(int joueur,const Grille& gr){
    assert (joueur == 'O' or joueur == 'X');
    return alignement(joueur,0,0,0,1,gr) // ligne 0
    or alignement(joueur, 1,0,0,1,gr) // ligne 1
    or alignement(joueur, 2,0,0,1,gr) // ligne 2
    or alignement(joueur, 0,0,1,0,gr) // colonne 0
    or alignement(joueur, 0,1,1,0,gr) // colonne 1
    or alignement(joueur, 0,2,1,0,gr) // colonne 2
    or alignement(joueur, 0,0,1,1,gr) // diag 1
    ;
}
/**
    @param[in] gr - Grille
*/

bool plateauBloque(const Grille& gr) {
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(evalCase(gr,i,j) == LIBRE) return false;
        }
    }
    return true;
}

/**
    @param[in] gr - Grille
*/

char joueurSuivant (const char &joueur) {
    if(joueur == 'X') return 'O';
    return 'X';
}

void jeuMorpion(){
    Grille gr;
    initialiserPlateau(gr);
    afficherPlateau(gr);
    char joueur = 'X';
    bool finJeu = false;
    while (not finJeu){
        jouer (joueur, gr);
        afficherPlateau(gr);
        if (victoire(joueur,gr)){
            cout<<"Le joueur:" << joueur << " gagne "<<endl;
            finJeu = true;
        }
        else if (plateauBloque(gr)){
            cout<<">>>>LOOSERS"<<endl;
            finJeu = true;
        }
        else{
            joueur = joueurSuivant (joueur);
        }
    }
}
int main(){
    jeuMorpion();
}
/*
Etudiant en Informatique
Faculté des Sciences et Techniques(FST)
Université de Haute Alsace Mulhouse
Brunstatt-FRANCE
*/
