#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
struct matrice
{
    struct { int val; unsigned int deschisa; unsigned int marcat;}mat[10][10];
};
int nr_bombe(matrice a,int i,int j)
{
    int nr=0; a.mat[i][j].val=0;
    int di[]={-1,-1,0,1,1,1,0,-1},dj[]={0,1,1,1,0,-1,-1,-1};
    for(int k=0;k<8;k++)
    {
        int l=i+di[k]; int c=j+dj[k];
        if(l>=0&&l<=8&&c<=8&&c>=0)
            if(a.mat[l][c].val==-1)
                nr++;
    }
    return nr;
}
void generare_harta(matrice &a)
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            a.mat[i][j].val=0;  a.mat[i][j].deschisa=0;a.mat[i][j].marcat=0;
        }
    srand((unsigned)time(0));
    int i=0; int l,c;
    while(i<8)
    {
        i++;

        l=rand()%9;
        c=rand()%9;
        while(a.mat[l][c].val==-1)
        {
            l=rand()%9; c=rand()%9;
        }
        a.mat[l][c].val=-1;
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(a.mat[i][j].val!=-1)
                {a.mat[i][j].val=nr_bombe(a,i,j);}
}
int dl[]={-1,-1,0,1,1,1,0,-1}, dc[]={0,1,1,1,0,-1,-1,-1};
void BKT_Fill(matrice &a, int i, int j)
{
    a.mat[i][j].deschisa=1;
    for(int dir=0;dir<8;dir++)
    {
        int ln=i+dl[dir];
        int cn=j+dc[dir];
        if(ln>=0&&ln<=8&&cn>=0&&cn<=8&&a.mat[ln][cn].deschisa==0)
            if(a.mat[ln][cn].val==0)
                BKT_Fill(a,ln,cn);
            else
                a.mat[ln][cn].deschisa=1;

    }
}
int corect(matrice a)
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            {if(a.mat[i][j].val==-1&&a.mat[i][j].marcat==0)
                return 0;
            if(a.mat[i][j].val!=-1&&a.mat[i][j].deschisa==0)
                return 0;}
    return 1;
}
void deschidere (matrice &a,int i, int j)
{
    if(a.mat[i][j].deschisa==1) return;
    if(a.mat[i][j].marcat==1) return;
    if(a.mat[i][j].val!=0) {a.mat[i][j].deschisa=1; return;}
    BKT_Fill(a,i,j);
}
void afisare(matrice a)
{   cout<<" "<<'|'<<"_";
    for(unsigned int i=0;i<9;i++)
        cout<<i<<"_";
    cout<<endl;
    for(unsigned int i=0;i<9;i++)
    {
        cout<<i<<'|'<<" ";
        for(unsigned int j=0;j<9;j++)
            if(a.mat[i][j].deschisa==0&&a.mat[i][j].marcat==0)
                cout<<'X'<<" ";
            else
                if(a.mat[i][j].marcat==1)
                    cout<<'F'<<" ";
                else
                cout<<a.mat[i][j].val<<" ";
        cout<<endl;
    }
}
void afisare_pierdere(matrice a)
{
    cout<<" "<<'|'<<"_";
    for(unsigned int i=0;i<9;i++)
        cout<<i<<"_";
    cout<<endl;
    for(unsigned int i=0;i<9;i++)
    {
        cout<<i<<'|'<<" ";
        for(unsigned int j=0;j<9;j++)
            if(a.mat[i][j].val==-1)
                cout<<char(254)<<" ";
            else
                if(a.mat[i][j].deschisa==0)
                    cout<<'X'<<" ";
                else
                    cout<<a.mat[i][j].val<<" ";
        cout<<endl;
    }
}

int main(void)
{
    matrice a;
    generare_harta(a);
    afisare(a);
    int x,y; char s;
    cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;
    cin>>x>>y;
    cout<<"Dati f (flag/marcare mina) sau d (deschide) sau u (unflag/demarcare mina)."<<" ";
    cin>>s;
    if(a.mat[x][y].val==-1&&s=='d')
    {   system("cls");cout<<"Ai pierdut. Mai incearca!"<<endl;
        afisare_pierdere(a); return 0;
    }
    while(corect(a)==0)
    {   if((s!='d'&&s!='f'&&s!='u')||!(x>=0&&x<=8&&y>=0&&y<=8))
        {cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl; cin>>x>>y; cout<<"Dati f (flag/marcare mina) sau d (deschide) sau u (unflag/demarcare mina)."<<" ";cin>>s; continue;}
        if(s=='d')
            {deschidere(a,x,y); system("cls"); afisare(a);}
        else
            if(s=='f')
        {
            a.mat[x][y].marcat=1; system("cls"); afisare(a);
        }
        else
        {
            a.mat[x][y].marcat=0; system("cls"); afisare(a);
        }
        if(corect(a)==1)
        {
            system("cls"); cout<<"Ai castigat!"; return 0;
        }
        cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;
        cin>>x>>y;
        cout<<"Dati f (flag/marcare mina) sau d (deschide) sau u (unflag/demarcare mina)."<<" ";
        cin>>s;
        if(a.mat[x][y].val==-1&&s=='d')
            {
            system("cls");
            cout<<"Ai pierdut. Mai incearca!"<<endl;
            afisare_pierdere(a);
            return 0;}
    }
    return 0;
}
