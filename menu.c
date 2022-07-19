#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void affichageMenu(char maquetteMenu[20])
{
    // init de laffichage
    printf("\r");
    clear();

    drawMaquette(maquetteMenu); // affiche le cadre du menu

    char menu[9][30] = {// differente option du menu
                        {"Voir la carte"},
                        {"Voir matrice de poid"},
                        {"Arbre de poids minimum"},
                        {"Somme des poids"},
                        {"Compresser la solution"},
                        {"Décompresser la solution"},
                        {"Compresser la map"},
                        {"Décompresser la map"},
                        {"Quitter"}};

    for (int i = 1; i < nombreMenu + 1; i++) // affichage des differentes options
    {
        displayMenu(menu[i - 1], i);
    }
}

void drawMaquette(char fichier[]) // lit un fichier texte et l'affiche dans la console
{
    FILE *maquette = fopen(fichier, "r");

    char *ligne = NULL;
    size_t len = 0;
    size_t read;
    for (int i = 0; i < offsetAffichage; i++) // offset de l'affichage en y
    {
        printf("\n");
    }

    while ((read = getline(&ligne, &len, maquette)) != -1) // lecture du fichier
    {
        for (int i = 0; i < offsetAffichage; i++) // offset de laffichage en x
        {
            printf(" ");
        }
        printf("%s", ligne); // affichage des caracteres
    }

    fclose(maquette);
}

void displayMenu(char sentence[30], int placement) // affiche chaque option à son emplacement
{
    int ligne = (placement - 1) / 2 + 1;
    int colonne = 0;
    char sentenceAff[35];

    sprintf(sentenceAff, "%d)", placement); // rajout du numero de l'option
    strcat(sentenceAff, sentence);

    if (placement % 2 == 0) // met le menu sur l'une des deux colonnes
    {
        colonne = 1;
    }
    // affichage
    printf("\033[%d;%dH", 2 * ligne + offsetAffichage + margeAffy, offsetAffichage + margeAffx + colonne * 35);
    printf("%s", sentenceAff);
}
// entrée protegé pour un int
int inputInt(int min, int max, int x, int y)
{
    x = x + offsetAffichage;
    y = y + offsetAffichage;
    int ok;
    int number;
    int test;
    char *line;
    size_t linelen;
    do
    {
        printf("\033[%d;%dH", y, x); // positionnement du curseur
        ok = 0;
        test = 0;
        line = NULL;
        linelen = 0;

        if (getline(&line, &linelen, stdin) > 0) // lecture
        {
            test = sscanf(line, "%5d", &number);
        }
        else if (test == 0 || number < min || number > max) // verif de l'input
        {
            // reset de l'input
            printf("\033[%d;%dH", y, x);
            printf("                                              ");
            // msg d'erreur
            printf("\033[%d;%dH", y + 1, x);
            printf("Ce nombre ne convient pas! Reessayez");
            ok = 1;
        }

    } while (ok != 0);

    // clear de l'input et du message d'erreur
    printf("\033[%d;%dH", y + 1, x);
    for (int i = 0; i < sizeof "Ce nombre ne convient pas! Reessayez     "; i++)
    {
        printf(" ");
    }

    printf("\033[%d;%dH", y, x);
    printf("                                              ║                  "); //à changer si on change la maquette
    printf("\033[%d;%dH", y, x + 3);

    return number;
}
// entrée protegé pour un string
void inputString(char input[30], int x, int y)
{
    x = x + offsetAffichage;
    y = y + offsetAffichage;
    int test;
    int ok;
    char *line = NULL;
    do
    {
        ok = 0;
        size_t linelen = 0;
        printf("\033[%d;%dH", y, x);             // positionnement du curseur
        if (getline(&line, &linelen, stdin) > 0) // lecture
        {
            test = sscanf(line, "%18s", input);
        }

        if (test <= 0 || strlen(input) == 0) // verif de l'input
        {
            // reset de l'input
            printf("\033[%d;%dH", y, x);
            printf("         ");
            // msg d'erreur
            printf("\033[%d;%dH", y + 1, x);
            printf("Ce nom ne convient pas");
            ok = 1;
        }
    } while (ok != 0);
    // clear input et message d'erreur
    printf("\033[%d;%dH", y + 1, x);
    for (int i = 0; i < sizeof "Ce nom ne convient pas"; i++)
    {
        printf(" ");
    }
    printf("\033[%d;%dH", y, x);
    printf("                                                           ║                  "); //à changer si on change la maquette
    // printf("\033[%d;%dH", y, x + 3);
}

void demandeInputString(char inputElement[30], char demande[35], char maquette[30])
{
    clear();
    //  affichage du sous menu
    drawMaquette(maquette);

    printf("\033[%d;%dH", margeAffy + offsetAffichage + 2, margeAffx + offsetAffichage);
    printf("%s :", demande);

    // input
    inputString(inputElement, +margeAffx, margeAffy + 3);
}
