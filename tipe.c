#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct arbre
{
  int score;
  float score_fin;
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

void init_score(arbre *a,float score_pred)
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

void remonte(arbre *a)
{
 if (a==NULL)
  return;
 int i;
 float acc=0.0;
 int tmp=0;
 for (i=0;i<16;i=i+1)
  {
    if (a->enfants[i]!=NULL)
      {
       remonte(a->enfants[i]);
       acc = acc + a->enfants[i]->score_fin;
       tmp = tmp+1;
       acc=acc/tmp;
       a->score_fin = acc;
      }
  }
  if (acc ==0.0)
    a->score_fin = (float)a->score;
  return;
}

int reponce(arbre*a)
{
  int i;
  float max = -6.0;
  int res=-1;
  for (i=0;i<16;i=i+1)
   {
    if(a->enfants[i] != NULL  && a->enfants[i]->score_fin > max)
     {max = a->enfants[i]->score_fin;
      res = a->enfants[i]->carte_nous;}
   }
 return res;
}

void free_arbre(arbre *a)
{
 int i;
 if (a == NULL)
     return;

 for (i=0;i<16;i=i+1)
   {if (a->enfants[i]!=NULL)
     free_arbre(a->enfants[i]);}

 free(a);
return;
}


int main ()
{
 int tab1[4]= {1,2,3,4};
 int tab2[4] = {1,2,3,4};
 int carte_a_joue;
 arbre *a = init_arbre(1,2,tab1,tab2);
 init_score(a,0);
 carte_a_joue = reponce(a);
 printf("%d",carte_a_joue);
 free_arbre(a);
return 0;
}
