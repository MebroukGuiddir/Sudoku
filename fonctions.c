#include "fonctions.h"
/**

**/
int lire(char *file,int * grille ){
  FILE *  f = fopen(file, "r");
  if(f==NULL) return 0;
  int c,i=0,cell;
  while ((c = fgetc(f)) != EOF)
   {
    if(c>='0' && c<='9'){
      c=c-'0';
      if(!c)cell=0;
      else{
        cell=1;
        while(c){
          cell<<=1;
          c--;
        }
      }
        printf("%d\n",cell );
        grille[i]=cell;
      i++;
    }
   }
if(i!=81)return 0;
return 1;
fclose(f);

}
void Afficher(int *G) {
  unsigned char i,j,n=3,bit;
  unsigned short valeur;
  for (i = 0; i < n*n; i++) {
      if (i % n == 0)
          printf("\n");
      printf("%2u",i + 1);
      for (j = 0; j < n*n; j++) {
          if (j % n == 0)
              printf("  ");
          valeur = G[n*n*i+j];
          bit = 0;
          if (poids(valeur) == 1) {
              while (valeur > 1UL) {
                  valeur = valeur >> 1;
                  bit++;
              }
              printf("\033[1;33m\033[40m%u \033[0m",bit);
          }
          else
            printf("\033[0;36m\033[40m%u \033[0m",poids(G[n*n*i+j]));
        }
      printf("\n");
}
}
int poids(int n){
   int poids=0;
   while(n){
     n &= n-1;
     poids++;
   }
   return poids;
}
//complexite n^2 avec n=9
void remplirTables(int  CasesDeLigne[9][9],int CasesDeColonne[9][9] ,int CasesDeRegion[9][9]){

  for (int i = 0; i < 9; i++) {
     for (int j = 0; j < 9; j++) {
         CasesDeLigne[i][j]=9*i+j+1;
         CasesDeColonne[i][j]=9*j+i+1;
         CasesDeRegion[i][j]=(j%3)+(j/3)*9+1+(i*3)+(i/3)*18;
     }
  }

}
//complexite N avec N=81
void remplirTables_n(int CasesDeLigne[9][9],int CasesDeColonne[9][9] ,int CasesDeRegion[9][9]){

  for (int i = 0; i < 81; i++) {
         CasesDeLigne[i/9][i%9]=i+1;
         //CasesDeColonne[i/9][i%9]=(i%9)*9+i/9+1;
         CasesDeColonne[i%9][i/9]=i+1;
         CasesDeRegion[i/9][i%9]=i;

  }
}
void afficherTable(int table[9][9]){
  for (int i = 0; i < 9; i++) {
     printf("\n");
     for (int j = 0; j < 9; j++) {
        printf(" %d ",table[i][j] );
        if (table[i][j]/10==0)printf(" ");
     }
  }
}

int * MemeLigne(int  CasesDeLigne[9][9],int ligne){
  return &CasesDeLigne[(ligne-1)/9];
}
int * MemeClonne(int  CasesDeColonne[9][9],int colonne){
  return &CasesDeColonne[(colonne-1)%9];
}
int * MemeRegion(int  CasesDeRegion[9][9],int region){
  return &CasesDeRegion[(region-1)%9];
}

void Parite(int **grille){
  /*int * memeLigne,memeClonne,memeRegion;
  int i;
  for (int cell = 0; cell < 81; cell++)
      if (weight(Grid[cell]) == 2)
        {
          memeLigne=MemeLigne( CasesDeLigne,case);
          memeClonne=MemeClonne(CasesDeColonne,case);
          memeRegion=MemeRegion(CasesDeRegion,case);
  	i=0;
  	while ((i < 8) && (cell != memeLigne[i]))
  	  i++;
  	if (i < 8)
  	  for (int j = 0; j < 8; j++)
  	    if (j != i)
  	      grille[memeLigne[j]] &= ~cell;
  	i = 0;
  	while ((i < 8) && (cell != memeClonne[i]))
  	  i++;
  	if (i < 8)
  	  for (int j = 0; j < 8; j++)
  	    if (j != i)
  	      grille[memeClonne[j]] &= ~cell;
  	i = 0;
  	while ((i < 8) && (cell != memeRegion[i]))
  	  i++;
  	if (i < 8)
  	  for (int j = 0; j < 8; j++)
  	    if (j != i)
  	      grille[memeRegion[j]] &= ~cell;
        }*/
}
void Exclusivite(int *grille){
  int * memeLigne,memeClonne,memeRegion;
  int ml,mc,mr;
  for (int cellule = 0; cellule < 81; cellule++)
     if (poids(grille[cellule]) == 1) {
        memeLigne=MemeLigne( CasesDeLigne,cellule);
        memeClonne=MemeClonne(CasesDeColonne,cellule);
        memeRegion=MemeRegion(CasesDeRegion,cellule);
	for (int i = 0; i < 8; i++) {
      ml=memeLigne[i];
      mc=memeClonne[i];
      mr=memeRegion[i];
	    grille[ml] &= ~grille[cellule];
	    grille[mc] &= ~grille[cellule];
	    grille[mr] &= ~grille[cellule];
	    }
    }

}
void Unicite(int **G){
  /**for (var cell = 0; cell < 81; cell++)
   if (weight(Grid[cell]) > 1) {
 GR = LCR(cell);
       var auxL = Grid[cell];
 var auxC = Grid[cell];
       var auxR = Grid[cell];
 for (var i = 0; i < 8; i++) {
     auxL &= ~Grid[GR.L[i]];
     auxC &= ~Grid[GR.C[i]];
     auxR &= ~Grid[GR.R[i]];
     }
 if (auxL)
   Grid[cell] = auxL;
 else if (auxC)
   Grid[cell] = auxC;
 else if (auxR)
   Grid[cell] = auxR;
 }*/
}
