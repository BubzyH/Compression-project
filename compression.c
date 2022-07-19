#include "functions.h"

void mapCompression(char nomFichier[38], int **map)
{
    int tmp = map[0][0];
    char fichierCompress[38];
    int compte = 0;

    sprintf(fichierCompress, "%s.compress", nomFichier); // rajout de l'extension .compress

    FILE *fcompress = fopen(fichierCompress, "w");

    if (fcompress == NULL)
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }

    fprintf(fcompress, "%d %d ", nbrColonne, nbrLigne); // ecrit le nbr de ligne et de colonne

    for (int i = 0; i != nbrLigne; i++)
    {
        for (int j = 0; j != nbrColonne; j++)
        {
            if (map[i][j] == tmp) // si le nombre et pareil que le precédent, ca incremente
            {
                compte++;
            }
            else if (compte >= 4) // si la repetetion de nombre est terminé et que le nombre se repete plus de 4 fois, la chaine est compressé
            {
                fprintf(fcompress, "$%d%d ", compte, tmp);
                compte = 1;
                tmp = map[i][j];
            }
            else
            {
                for (int i = 0; i < compte; i++) // si le caractere est ecrit moins de 4fois, il est ecrit normalement
                {
                    fprintf(fcompress, "%d ", tmp);
                }
                compte = 1;
                tmp = map[i][j];
            }
        }
    }
    // ecrit le dernier caractere
    if (compte >= 4)
    {
        fprintf(fcompress, "$%d%d ", compte, tmp);
    }
    else
    {
        for (int i = 0; i < compte; i++)
        {
            fprintf(fcompress, "%d ", tmp);
        }
    }
    fclose(fcompress);
}

void mapDecompression(char fichierCompress[38], char fichierDecompress[38])
{

    char buffer[10];
    int j = 0;
    int i = 0;
    int repeat = 0;
    int repeatTab[10];
    int nbr;
    int tailleBuffer;
    int e = 0;
    coord tailleMap;

    FILE *fcompress = fopen(fichierCompress, "r"); // fichier in
    if (fcompress == NULL)
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }
    FILE *fdecompress = fopen(fichierDecompress, "w"); // fichier out
    if (fdecompress == NULL)
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }
    // récupere la taille de la matrice
    if (fscanf(fcompress, "%d", &tailleMap.x) != EOF)
        ;
    if (fscanf(fcompress, "%d", &tailleMap.y) != EOF)
        ;

    while (fscanf(fcompress, "%s", buffer) != EOF)
    {
        repeat = 0;
        if (buffer[0] == '$') // si le caractere est compressé
        {
            tailleBuffer = strlen(buffer);
            nbr = buffer[tailleBuffer];                // recupere la valeur à repeter
            for (int i = 0; i < tailleBuffer - 2; i++) // convertie le tableau buffer en int (la valeur du milieu qui correspond au nombre de repetition)
            {
                repeat = (10 * repeat) + (buffer[tailleBuffer - (tailleBuffer - 1) + i] - '0');
            }
        }
        else // si il est pas compressé
        {
            nbr = 0;
            tailleBuffer = strlen(buffer);
            for (int i = 0; i < tailleBuffer; i++) // convertie le tableau buffer en int
            {
                nbr = (10 * nbr) + (buffer[i] - '0');
            }
            repeat = 1;
        }
        for (int e = 0; e < repeat; e++) // complete le fichier
        {
            fprintf(fdecompress, "%d ", nbr);
            j++;
            if (j == tailleMap.x) // retour à la ligne
            {
                j = 0;
                fprintf(fdecompress, "\n");
                i++;
                if (i == tailleMap.y)
                {
                    break;
                }
            }
        }
    }
    fclose(fcompress);
    fclose(fdecompress);
}

void compressHuffman(char *fichierChemin)
{
    clear();
    char input[500];
    long int nbrCaractere = 0; // nombre de caractere differents dans le chemin
    int lettreEnregistre = 0;  // nombre de caracteree differents enregistrés
    char fichierCompress[30];
    char occurenceLettre[256];
    int occurenceRepetition[256];
    int ok; // flag de verification
    int e;  // valeur de substitution à i
    // valeur permettant de faire la convertion en binaire:
    int n;
    int emplacement;
    int premierUn;

    sprintf(fichierCompress, "%s.compress", fichierChemin);
    FILE *fcompress = fopen(fichierCompress, "w");
    if (fcompress == NULL)
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }

    FILE *fchemin = fopen(fichierChemin, "r");
    if (fcompress == NULL)
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }

    fscanf(fchemin, "%[^\n]", input); // recupere le chemin, la premiere ligne du fichier

    nbrCaractere = strlen(input); // recupere le nombre de caractere

    // libere de la memoire
    fclose(fchemin);

    // comptage occurance:

    for (int i = 0; i < nbrCaractere; i++)
    {
        ok = 1;
        for (int e = 0; e <= lettreEnregistre; e++) // verifie si la lettre n'a pas deja ete traitée
        {
            if (input[i] == occurenceLettre[e])
            {
                ok = 0;
            }
        }

        if (ok == 1) // si elle n'a pas ete traité:
        {
            occurenceLettre[lettreEnregistre] = input[i];
            occurenceRepetition[lettreEnregistre] = 0;
            for (int x = 0; x < nbrCaractere; x++) // compte le nombre d'occurence du caractere
            {
                if (input[x] == occurenceLettre[lettreEnregistre])
                {
                    occurenceRepetition[lettreEnregistre] = occurenceRepetition[lettreEnregistre] + 1;
                }
            }
            lettreEnregistre++;
        }
    }

    int **bufferValeurBinaire = allocationMatDyn(lettreEnregistre, 5);
    int **valeurBinaire = allocationMatDyn(lettreEnregistre, 5);

    // trie des occurences, du plus grand au plus petit
    int bufferInt;
    char bufferChar;
    for (int i = 0; i < lettreEnregistre; i++)
    {
        for (int e = 0; e < lettreEnregistre - 1; e++)
        {
            if (occurenceRepetition[e] < occurenceRepetition[e + 1])
            {
                bufferInt = occurenceRepetition[e];
                occurenceRepetition[e] = occurenceRepetition[e + 1];
                occurenceRepetition[e + 1] = bufferInt;

                bufferChar = occurenceLettre[e];
                occurenceLettre[e] = occurenceLettre[e + 1];
                occurenceLettre[e + 1] = bufferChar;
            }
        }
    }
    // generation de l'arbre binaire et affichage:
    printf(" char | occ | binaire\n");
    printf("---------------------\n");
    fprintf(fcompress, " char | occ | binaire\n");
    fprintf(fcompress, "---------------------\n");

    for (int i = 0; i < lettreEnregistre; i++) // pour toutes les lettres enregistrées:
    {
        emplacement = 0;
        premierUn = 0;
        e = i;
        n = 0;

        while (e != 0) // convertie son suffixe en binaire
        {
            bufferValeurBinaire[i][5 - n - 1] = e % 2;
            e /= 2;

            n++;
        }
        // affichage
        printf(" '%c' | %2d |  ", occurenceLettre[i], occurenceRepetition[i]);
        fprintf(fcompress, " '%c' | %2d |  ", occurenceLettre[i], occurenceRepetition[i]);

        for (int j = 0; j <= 4; j++) // enleve les 0 à gauche en trop
        {
            if (i == 0) // enregistre la premiere valeur..
            {
                valeurBinaire[i][0] = 0;
                printf("%d", valeurBinaire[i][emplacement]);
                fprintf(fcompress, "%d", valeurBinaire[i][emplacement]);
                break;
            }
            else if (premierUn == 0 && bufferValeurBinaire[i][j] == 1)
            {
                premierUn = 1;
            }
            if (premierUn == 1)
            {
                valeurBinaire[i][emplacement] = bufferValeurBinaire[i][j];
                printf("%d", valeurBinaire[i][emplacement]);
                fprintf(fcompress, "%d", valeurBinaire[i][emplacement]);
                emplacement++;
            }
        }

        printf("\n");
        fprintf(fcompress, "\n");
    }
    // affichage
    printf("---------------------\n");
    fprintf(fcompress, "---------------------\n");
    fprintf(fcompress, "nombre de caractere dans le chemin : %ld\n", nbrCaractere);
    printf("nombre de caractere dans le chemin : %ld\n", nbrCaractere);

    // liberation de la memoire
    libMat(lettreEnregistre, valeurBinaire);
    libMat(lettreEnregistre, bufferValeurBinaire);
    fclose(fcompress);
}

/*void decompressHuffman(char* fichierCompress){
    FILE *fcompress = fopen(fichierCompress, "r");
    if (fcompress == NULL)
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }
    int taille;
    if (fscanf(fcompress, "%d", &taille) != EOF);
    char decompression[taille];
    char buffer[10];
    int codage[20];
    if (fscanf(fcompress, "%s", buffer) != EOF);//debut ignoré
    int e=0;
    int i=0;
    int number;
    while(i!= taille){
        if (fscanf(fcompress, "%s",buffer) != EOF);
        codage[e]=buffer[0];
        if(buffer[1]==NULL){

            e++;
        }
        else{
            number = buffer[1];
            //codage == number
        }

17
1 0A 1 0 0R 1P 1 0B 1T
111 0 100 0 111 0 111 0 110 0 100 110 0 101 0 101 0
0000



fclose(fcompress);
}
}*/