#include "sudoku.h"
//variables globales
int CasesDeLigne[9][9], CasesDeColonne[9][9] , CasesDeRegion[9][9];
int grille[81];
int n=3;
int main(int argc, char *argv[])
{
  if ( argc != 2 ) {
    printf( "Usage : sudoku fileSource \n" );
    exit(1);
  }
  if (!lire(argv[1]))
  {
    printf("Impossible de lire la grille");
    exit (1);
  }
  printf("\nInitial grid:\n");
  Afficher();
  remplirTables_n();
  printf("\nExecution:\n" );
  sudoku();
  return 0;
}


/**lire la grille **/
int lire(char *file ){
  FILE *  f = fopen(file, "r");
  if(f==NULL) return 0;
  int c,i=0,cell;
  while ((c = fgetc(f)) != EOF)
  {
    if(c>='0' && c<='9'){
      c=c-'0';
      if(!c)cell=1022;
      else{
        cell=1;
        while(c){
          cell<<=1;
          c--;
        }
      }
      grille[i]=cell;
      i++;
    }
  }
  fclose(f);
  if(i!=81)return 0;
  return 1;


}

/** Afficher la grille **/
void Afficher() {
  unsigned char i,j,n=3,bit;
  unsigned short valeur;
  for (i = 0; i < n*n; i++) {
    if (i % n == 0)
    printf("\n");
    printf("%2u",i + 1);
    for (j = 0; j < n*n; j++) {
      if (j % n == 0)
      printf("  ");
      valeur = grille[n*n*i+j];
      bit = 0;
      if (poids(valeur) == 1) {
        while (valeur > 1UL) {
          valeur = valeur >> 1;
          bit++;
        }
        printf("\033[1;33m\033[40m%u \033[0m",bit);
      }
      else
      printf("\033[0;36m\033[40m%u \033[0m",poids(grille[n*n*i+j]));
    }
    printf("\n");
  }
}

/**calcule le poids de Hamming d'un entier**/
int poids(int n){
  int poids=0;
  while(n){
    n &= n-1;
    poids++;
  }
  return poids;
}
/** Remplir les tableaux qui contiennent les indices des cases selon les lignes ,colonnes et regions**/
void remplirTables_nn(){
  //complexité quadratique (polynomiale) O(n^2) n=9
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      CasesDeLigne[i][j]=9*i+j+1;
      CasesDeColonne[i][j]=9*j+i+1;
      CasesDeRegion[i][j]=(j%3)+(j/3)*9+1+(i*3)+(i/3)*18;
    }
  }

}

/** Remplir les tableaux qui contiennent les indices des cases selon les lignes ,colonnes et regions**/
void remplirTables_n(){
  //complexité linéaire  O(n) n=81
  for (size_t i = 0; i < 81; i++) {
    CasesDeLigne[i/9][i%9]=i+1;

    //CasesDeColonne[i/9][i%9]=(i%9)*9+i/9+1;
    CasesDeColonne[i%9][i/9]=i+1;

    //CasesDeRegion[i/9][i%9]=((i%9)%3)+((i%9)/3)*9+1+(i/9*3)+(i/9/3)*18  ;
    CasesDeRegion[i/9][i%9]=(i%3)+((i%9)/3)*9+1+(i/9*3)+(i/27)*18  ;

  }
}

// afficher un tableau 9*9
void afficherTable(int table[9][9]){
  for (int i = 0; i < 9; i++) {
    printf("\n[");
    for (int j = 0; j < 9; j++) {
      printf(" %d  ",table[i][j] );
      if(j!=8)printf(",");
      if (table[i][j]/10==0)printf(" ");
    }
    printf("]");
    if(i!=8)printf(",");
  }
}
/** retrouver en fonction de l'indice d'une case la table L qui adresse la liste des numéros des cases dans la même ligne*/
int * MemeLigne(int cellule){
  //complexité constante O(1)
  return CasesDeLigne[(cellule-1)/9];
}

/** retrouver en fonction de l'indice d'une case la table C qui adresse la liste des numéros des cases dans la même colonne*/
int * MemeColonne(int cellule){
  //complexité constante O(1)
  return CasesDeColonne[(cellule-1)%9];
}

/** retrouver en fonction de l'indice d'une case la table R qui adresse la liste des numéros des cases dans la même region*/
int * MemeRegion(int c){
  //complexité quadratique (polynomiale) O(n^2)
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      if(CasesDeRegion[i][j]==c)return CasesDeRegion[i];
    }
  }
  //TODO
  //complexité constante O(1)
  //trouver k [0-80] en fonction de c num de la cellule tq c=(k%3)+((k%9)/3)*9+1+(k/9*3)+(k/27)*18;
  //calculer i à partir de k  i=k/9
  //retourner   CasesDeRegion[i]
  return NULL;
  //return CasesDeRegion[((c%3)+((c%9)/3)*9+1+((c/9)*3)+(c/27)*18)/9];
}

void Parite(){
  int * memeLigne,*memeColonne,*memeRegion;
  int i;
  for (int cellule = 1; cellule < 82; cellule++)
  if (poids(grille[cellule-1]) == 2)
  {
    memeLigne=MemeLigne(cellule);
    memeColonne=MemeColonne(cellule);
    memeRegion=MemeRegion(cellule);
    i=0;
    while ((i < 9) && ((grille[cellule-1] != grille[memeLigne[i]-1]) ||(cellule ==memeLigne[i])))
      i++;
    if (i < 9)
      for (int j = 0; j < 9; j++)
        if ((j != i) && (memeLigne[j]!=cellule))
          grille[memeLigne[j]-1] &= ~grille[cellule-1];

    i=0;
    while ((i < 9) && ((grille[cellule-1] != grille[memeColonne[i]-1]) ||(cellule ==memeColonne[i])))
      i++;
    if (i < 9)
      for (int j = 0; j < 9; j++)
        if ((j != i)  && (memeColonne[j]!=cellule))
          grille[memeColonne[j]-1] &= ~grille[cellule-1];

    i=0;
    while ((i < 9) && ((grille[cellule-1] != grille[memeRegion[i]-1]) ||(cellule ==memeRegion[i])))
      i++;
    if (i < 9)
      for (int j = 0; j < 9; j++)
        if ((j != i)  && (memeRegion[j]!=cellule))
          grille[memeRegion[j]-1] &= ~grille[cellule-1];
  }
}
void Exclusivite(){
  int  *memeLigne,*memeColonne,*memeRegion;
  for (int cellule = 1; cellule < 82; cellule++)
  if (poids(grille[cellule-1]) == 1) {

    memeLigne=MemeLigne( cellule);
    memeColonne=MemeColonne(cellule);
    memeRegion=MemeRegion(cellule);
    for (int i = 0; i < 9; i++) {

      if(memeLigne[i]!=cellule)grille[memeLigne[i]-1] &= ~grille[cellule-1];
      if(memeColonne[i]!=cellule) grille[memeColonne[i]-1] &= ~grille[cellule-1];
      if(memeRegion[i]!=cellule)grille[memeRegion[i]-1] &= ~grille[cellule-1];

    }
  }

}
void Unicite(){
  int  *memeLigne,*memeColonne,*memeRegion;
  for (int cellule = 1; cellule < 82; cellule++)
  if (poids(grille[cellule-1]) > 1) {
    memeLigne=MemeLigne( cellule);
    memeColonne=MemeColonne(cellule);
    memeRegion=MemeRegion(cellule);
    int ligne = grille[cellule-1];
    int colonne = grille[cellule-1];
    int region = grille[cellule-1];
    for (int i = 0; i < 9; i++) {
      if(memeLigne[i]!=cellule)ligne &= ~grille[memeLigne[i]-1];
      if(memeColonne[i]!=cellule) colonne &= ~grille[memeColonne[i]-1];
      if(memeRegion[i]!=cellule)region &= ~grille[memeRegion[i]-1];

    }
    if (ligne)
    grille[cellule-1] = ligne;
    else if (colonne)
    grille[cellule-1] = colonne;
    else if (region)
    grille[cellule-1] = region;
  }
}
/** appliquer les règles EUP tant qu'au moins un vecteur caractéristique a été modifié **/
/** renvoie la case contenant le vecteur caractéristique de plus petit poids !=1**/
int BouclerRegles(){
  int poidsMin,poidsCellule,celluleMin;
  int poidsTotal=0;//le poids total de l'itération en cours
  int poidsRef=-1;// poids de réference=poids total de la dérnier itération

  //arrêter lorsque le poids total ne change plus
  while (poidsTotal != poidsRef) {
    //appliquer les règles
    Exclusivite();
    Unicite();
    Parite();

    //afficher la grille
    printf("\n\n");
    Afficher();
    poidsRef=poidsTotal;
    poidsTotal=0;
    celluleMin = -1;
    poidsMin = 9;
    // calculer le poids total & retrouver la cellule du poids min != 1
    for (size_t cellule = 0; cellule < 81; cellule++) {
      poidsCellule = poids(grille[cellule]);
      poidsTotal+=poidsCellule;

      if (poidsCellule > 1 && poidsCellule < poidsMin) {
        poidsMin = poidsCellule;
        celluleMin = cellule;
      }
    }
  }
  return celluleMin;

}

int sudoku(){
  int cellule, bit,trouve=0;
  int B[81];
  cellule=BouclerRegles();
  if (cellule>=0){
    bit=1;
    while (bit <= 9 && !trouve){
      if ((1 << bit) & (grille[cellule] > 0))
      {for (size_t i = 0; i < 91; i++) B[i]=grille[i];
        grille[cellule] = 1 << bit;
        trouve=sudoku();
        if(!trouve)
        for (size_t i = 0; i < 91; i++) grille[i]=B[i];
      }
      bit++;
    }
  }
  return 1;

}
