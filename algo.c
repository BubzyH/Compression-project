#include "functions.h"

void readMatriceMap(int **map, char nameFile[30]) // complete la matrice et recupere les coordonnées des villes
{
    FILE *fichier = fopen(nameFile, "r");

    int e = 0;
    if (fichier == NULL) 
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i != nbrLigne; i++) //lie la matrice à la recherche des villes
    {
        for (int j = 0; j != nbrColonne; j++)
        {
            fscanf(fichier, "%d", &map[i][j]);
            if (map[i][j] == e + 1) // verifie si le nbr correspond à un numero de ville, puis récuperer ses coordonnées
            {
                villeCoord[e].x = j + 1;
                villeCoord[e].y = i + 1;
                e++;
            }
        }
    }

    fclose(fichier);
}

float distance(int a, int b) // calcule de distance entre deux points, fonction non utilisé
{                            // mettre un nombre entre 0 et 16
    float dist = 0;          // sqrt(pow(villeCoord[b].x - villeCoord[a].x, 2) + pow(villeCoord[b].y - villeCoord[a].y, 2));
    return dist;
}

void calculeMatricePoid(float **matricePoid) //calcule la matrice de poid
{
    
    int **connection;
    connection = allocationMatDyn(nbrVille, nbrVille);

    FILE *fconnection = fopen("connection.txt", "r");

    if (fconnection == NULL) // complete la matrice de connection en lisant le fichier de connection
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i != nbrVille; i++)
    {
        for (int j = 0; j != nbrVille; j++)
        {
            fscanf(fconnection, "%d", &connection[i][j]);
        }
    }

    fclose(fconnection);

    // calcule matrice de poid:
    // lecture des connections des villes
    for (int i = 0; i != nbrVille; i++)
    {
        for (int j = 0; j != nbrVille; j++)
        {
            if (connection[i][j] == 1)
            {
                matricePoid[i][j] = sqrt(pow(villeCoord[j].x - villeCoord[i].x, 2) + pow(villeCoord[j].y - villeCoord[i].y, 2)); // distance(i, j);
            }
            else
            {
                matricePoid[i][j] = -1;
            }
        }
    }
    //libere de la memoire
    libMat(nbrVille, connection);
}

float Somme(float a, float somme_poids)
{
    somme_poids = a + somme_poids;
    return somme_poids;
}

void Prim(float **matricePoid, float *somme_poids, char fichierChemin[30])
{
    clear();

    FILE *fchemin = fopen(fichierChemin, "w"); // création d'un fichier stockant les aretes de l'arbre
    int ligne;                                 //  lignes
    int col;                                   //  colonnes
    int nb_arete;                              // nombre d'arête
    int marque[nb_sommet];                     // tableau stockant les sommets marqués

    memset(marque, false, sizeof(marque)); // initialisation du tableau marque à l'état faux par défaut
    nb_arete = 0;
    marque[0] = true; // On marque le premier sommet pour commencer

    if (fchemin == NULL) // test de l'ouverture de chemin.txt
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }

    // Tant que le nombre d'aretes du chemin est inférieur au nmobre de sommets moins un
    while (nb_arete < nb_sommet - 1)
    {
        int min = X; // le min prend une grande valeur supérieur a tout les poids du graphe
        ligne = 0;
        col = 0;

        for (int i = 0; i < nb_sommet; i++)
        {
            if (marque[i])
            {
                for (int j = 0; j < nb_sommet; j++)
                {
                    if ((!marque[j]) && (matricePoid[i][j] != -1))
                    {
                        if (min > matricePoid[i][j])
                        {
                            min = matricePoid[i][j];
                            col = j;
                            ligne = i;
                        }
                    }
                }
            }
        }

        printf("%s <---> %s", ville[ligne], ville[col]); // affiche l'arete

        printf("\033[%d;%dH", nb_arete + 1, 30);
        printf("|| Poids = %5.1f\n", matricePoid[ligne][col]); // affiche le poids de l'arete 
        //écriture des resultats dans un fichier pour la compression
        fprintf(fchemin, "%s <---> %s", ville[ligne], ville[col]);
        if (nb_arete != nb_sommet - 2)
        {
            fprintf(fchemin, ", ");
        }
        marque[col] = true;
        nb_arete++;

        // Somme des poids des arêtes de l’arbre couvrant de poids minimum
        *somme_poids = Somme(matricePoid[ligne][col], *somme_poids);
    }
    fclose(fchemin);
}