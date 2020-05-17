#include <stdlib.h>
#include <stdio.h>
//lire une grille à partir d'un fichier
int lire(char * file);
//afficher la grille
void Afficher();
//calculer le poids de hamming d'un int
int poids(int n);
void afficherTable(int table[9][9]);
void remplirTables_n();
void remplirTables();
int * MemeLigne(int ligne);
int * MemeColonne(int colonne);
int * MemeRegion(int region);

void Exclusivite();
void Parite();
void Unicite();

int BouclerRegles();
int sudoku();
