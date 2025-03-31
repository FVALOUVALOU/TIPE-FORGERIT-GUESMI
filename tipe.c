#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct arbre
{
  int score;
  int carte_nous;
  int carte_adv;
  struct arbre *enfants[16];
};
typedef struct arbre arbre;

arbre *create_arbre(int x,int y)
{
 arbre *a = malloc(sizeof(arbre));
 assert (a!=NULL);
 int i;
 for (i=0;i<16;i=i+1)
  a->enfants[i] = NULL;

 a->carte_nous = x;
 a->carte_adv = y;
 a->score = 0;

 return a;
}

arbre *init_arbre(int x,int y,int *tab1,int *tab2)
{
 arbre *a = create_arbre(x,y);
 int i=0;
 int j=0;
 int n=0;
 tab1[x-1]=0;
 tab2[y-1]=0;
 while (j!=4 && i!=4)
 {
  if (j==4)
   j=0;
  if (tab1[i]*tab2[j]!=0)
    {
     a->enfants[n] = init_arbre(tab1[i],tab2[j],tab1,tab2);
     n=n+1;
    }
  j = j+1;
  if (j % 4 == 0)
   i=i+1;
 }
 return a;
}

void init_score(arbre *a,int score_pred)
{
  if (a==NULL)
    return;

  int adv = a->carte_adv;
  int nous = a->carte_nous;
  int i;

 if (adv>nous)
   a->score = score_pred-1;
 else if (nous>adv)
   a->score = score_pred+1;
 else
   a->score = score_pred;

 for (i=0;i<16;i=i+1)
   init_score(a->enfants[i],a->score);
return;
}

void free_arbre(arbre **addr_a)
{
 arbre *a = *addr_a;
 if (addr_a == NULL)
   {free(addr_a);
    return;}
 int i;

 for (i=0;i<16;i=i+1)
   free_arbre(&(a->enfants[i]));

 free(a);
 free(addr_a);
return;
}


int main ()
{
 int tab1[4]= {1,2,3,4};
 int tab2[4] = {1,2,3,4};
 arbre *a = init_arbre(1,2,tab1,tab2);
 init_score(a,0);
 free_arbre(&a);
return 0;
}
