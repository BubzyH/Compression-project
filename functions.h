#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define clear() printf("\033[H\033[J") // clear la console
#define X 1000                         // très grand nombre supérieur a tout les poids du graphe
#define nb_sommet 17                   // nombre de villes

typedef struct coord{
    int x;
    int y;
}coord;

struct coord villeCoord[17];
// variables


// affichage
extern int const nombreMenu;
extern int const offsetAffichage;
extern int const margeAffx;
extern int const margeAffy;

// taille de la map
extern int nbrLigne;
extern int nbrColonne;

// ville
extern int nbrVille;
extern char *ville[17];


// function menu.c

extern void affichageMenu();
extern int inputInt(int min, int max, int x, int y);
extern void displayMenu(char sentence[30], int nbr);
extern void drawMaquette(char fichier[]);
extern void inputString(char input[30], int x, int y);
extern void demandeInputString(char inputElement[30], char demande[35], char maquette[30]);
extern void affichePhrase(char maquetteSSMenu[30], char phrase[40]);

// function matrice.c

extern int **allocationMatDyn(int NB_L, int NB_C);
extern float **allocationMatDynFloat(int NB_L, int NB_C);
extern void afficheMat(int NB_L, int NB_C, int **mat);
extern void afficheMatFloat(int NB_L, int NB_C, float **mat);
extern void libMat(int NB_L, int **mat);
extern void libMatFloat(int NB_L, float **mat);
extern void tailleMatrice();

// function compression.c

extern void mapCompression(char nomFichier[38],int **map);
extern void mapDecompression(char fichierCompress[38],char fichierDecompress[38]);
void compressHuffman(char* fichierChemin);

// algo.c
extern void readMatriceMap(int** map,char nameFile[30]);
extern void calculeMatricePoid(float **matricePoid);
void Prim(float **matricePoid, float *somme_poids,char fichierChemin[30]);
extern float Somme(float a, float somme_poids);