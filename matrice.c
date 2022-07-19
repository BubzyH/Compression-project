#include "functions.h"

int **allocationMatDyn(int NB_L, int NB_C)//alloc matrice int
{
	int **mat;

	mat = (int **)malloc(NB_L * sizeof(int *));
	if (mat == NULL)
	{
		perror("Erreur d'allocation memoire\n");
		exit(0);
	}

	for (int i = 0; i != NB_L; i++)
	{
		mat[i] = (int *)calloc(NB_C, sizeof(int));
		if (mat[i] == NULL)
		{
			perror("Erreur d'allocation memoire\n");
			exit(0);
		}
	}
	return mat;
}

float **allocationMatDynFloat(int NB_L, int NB_C)//alloc matrice float
{
	float **mat;

	mat = (float **)malloc(NB_L * sizeof(float *));
	if (mat == NULL)
	{
		perror("Erreur d'allocation memoire\n");
		exit(0);
	}

	for (int i = 0; i != NB_L; i++)
	{
		mat[i] = (float *)calloc(NB_C, sizeof(float));
		if (mat[i] == NULL)
		{
			perror("Erreur d'allocation memoire\n");
			exit(0);
		}
	}
	return mat;
}

void afficheMat(int NB_L, int NB_C, int **mat)//affiche une matrice en int
{
	for (int i = 0; i != NB_L; i++)
	{
		for (int j = 0; j != NB_C; j++)
		{
			printf("%2d ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void afficheMatFloat(int NB_L, int NB_C, float **mat)//affiche une matrice en float
{
	for (int i = 0; i != NB_L; i++)
	{
		for (int j = 0; j != NB_C; j++)
		{
			printf("%5.1f ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void libMat(int NB_L, int **mat)//libere matrice int
{
	for (int i = 0; i != NB_L; i++)
	{
		free(mat[i]);
		mat[i] = NULL;
	}
	free(mat);
	mat = NULL;
}
void libMatFloat(int NB_L, float **mat)//libere matrice float
{
	for (int i = 0; i != NB_L; i++)
	{
		free(mat[i]);
		mat[i] = NULL;
	}
	free(mat);
	mat = NULL;
}
void tailleMatrice(char nameFile[30]) //recupere la taille d'une matrice dans un fichier
{
	char c;
	FILE *fichier = fopen(nameFile, "r");
	if (fichier == NULL)
	{
		perror("Error opening file.");
		exit(EXIT_FAILURE);
	}
	while ((c = fgetc(fichier)) != EOF)
	{
		if (c == '\n') //compte les lignes
		{
			nbrLigne++;
		}
		else if (nbrLigne == 0) //comptage de colonne
		{
			if (c != ' ' && c != 13)//igniore certains caractere specifique au fichier et les espaces
			{
				nbrColonne++;
			}
		}
	}
	fclose(fichier);
}


