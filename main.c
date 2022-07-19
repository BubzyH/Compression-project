#include "functions.h"

// affichage:
int const offsetAffichage = 4; // Affichage avec X de décallage
int const margeAffx = 5;       // marge de l'affichage à l'interrieur du cadre du menu
int const margeAffy = 3;
int const nombreMenu = 9;  // numero d'option dans le menu principal
int const inputCaseY = 14; // ligne où l'on ecrit

// fichiers
char maquetteMenu[20] = "./maquette_menu.txt";
char maquetteSousMenu[30] = "./maquette_sous_menu.txt";
char maquetteSSMenu[30] = "./maquette_ss_menu.txt";
char fichierMap[30] = "carte.txt";
char fileSave[30] = "carte2.txt";
char fichierChemin[30] = "chemin.txt";
char fichierCompress[30] = "carte.txt.compress";

int nbrLigne = 0;
int nbrColonne = 0;

int nbrVille = 17;
char *ville[17] = {"lille", "paris", "brest", "rennes", "strasbourg", "orleans", "nantes", "dijon", "clermont-Ferrand", "lyon", "geneve", "bordeaux", "grenoble", "nice", "toulouse", "montpellier", "perpignan"};

int main(void)
{
    // initiailisation
    float somme_poids = 0;
    int choix;
    int **map;
    float **matricePoids;
    int ok = 0;           // flag, calcule de poids fait 0=non
    float saveSommePoids;

    demandeInputString(fichierMap, "Nom du fichier Map", maquetteSousMenu); // a enlever pour debug
    tailleMatrice(fichierMap);
    map = allocationMatDyn(nbrLigne, nbrColonne);
    matricePoids = allocationMatDynFloat(nbrVille, nbrVille);
    readMatriceMap(map, fichierMap);
    calculeMatricePoid(matricePoids);

    while (1)
    {

        affichageMenu(maquetteMenu); // a enlever pour debug
        printf("\033[%d;%dH", inputCaseY + offsetAffichage + margeAffy, offsetAffichage + margeAffx);
        printf("choisissez une action: ");
        choix = inputInt(1, nombreMenu, margeAffx + 25, inputCaseY + margeAffy);

        switch (choix)
        {
        case 1: // affichage map et coordonnée des villes

            clear();
            afficheMat(nbrLigne, nbrColonne, map);
            // affiche ville + coord
            for (int i = 0; i < nbrVille; i++)
            {
                printf("\033[%d;%dH", i + 2, nbrColonne * 3 + 3);
                printf("║%d) %s: [%d,%d]\n", i + 1, ville[i], villeCoord[i].x, villeCoord[i].y);
            }
            printf("\033[%d;%dH", nbrLigne + 2, 2);

            printf("Appuyez sur entrée pour continuer... ");
            while (getchar() != '\n') // attendre l'utilisateur
                continue;
            break;
        case 2: // affichage de la matrice de poids
            clear();
            printf("\n");
            afficheMatFloat(nbrVille, nbrVille, matricePoids);

            printf("Appuyez sur entrée pour continuer... ");
            while (getchar() != '\n') // attendre l'utilisateur
                continue;
            break;
        case 3: // affichage arbre couvrant de poid minimum
            clear();
            demandeInputString(fichierChemin, "Nom du fichier chemin à créer", maquetteSousMenu); // a enlever pour debug
            Prim(matricePoids, &somme_poids, fichierChemin);

            printf("\nUn fichier a été créé\n");
            ok = 1;
            printf("Appuyez sur entrée pour continuer... ");
            while (getchar() != '\n') // attendre l'utilisateur
                continue;
            break;
        case 4: // affichage somme des poids
            clear();
            if (ok == 0)
            {
                printf("\nCalculez d'abord l'arbre couvrant minimum.\n\n");
            }
            else
            {
                if (somme_poids != 0)
                {
                    saveSommePoids = somme_poids;
                }
                printf("\nLa somme des poids des arêtes de l’arbre couvrant de poids minimum est de %5.1f et %5.1f km à l'echelle de la carte.\n\n",saveSommePoids, saveSommePoids*10); // fois 10 pour mettre a l'echelle
                somme_poids = 0;
            }
            printf("Appuyez sur entrée pour continuer... ");
            while (getchar() != '\n') // attendre l'utilisateur
                continue;
            break;
        case 5: // compression chemin
            clear();
            if (ok == 0)
            {
                printf("\nCalculez d'abord l'arbre couvrant minimum.\n\n");
            }
            else
            {
                compressHuffman(fichierChemin);
            }
            printf("Appuyez sur entrée pour continuer... ");
            while (getchar() != '\n') // attendre l'utilisateur
                continue;
            break;
        case 6: // decompression chemin
            clear();
            printf("\n Fonctionnalitée absente...\n\n");
            printf("Appuyez sur entrée pour continuer... ");
            while (getchar() != '\n') // attendre l'utilisateur
                continue;
            break;
        case 7: // compresser la map
            clear();
            printf("\n Un fichier .compress a été créé.");
            mapCompression(fichierMap, map);
            while (getchar() != '\n') // attendre l'utilisateur
                continue;
            break;
        case 8: // décompresser une map
            clear();
                demandeInputString(fichierCompress, "Le nom du fichier à décompressé", maquetteSousMenu);
                demandeInputString(fileSave, "Le nom du fichier à enregistrer", maquetteSousMenu);
                mapDecompression(fichierCompress, fileSave);
            break;
        case 9: // quitter
            // liberation de la memoire
            libMat(nbrLigne, map);
            libMatFloat(nbrVille, matricePoids);
            clear();
            exit(0);
            break;
        }
    }

    return 0;
}