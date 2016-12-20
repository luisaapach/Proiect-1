#include <stdlib.h>
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
    int i=0;
    while(i<9)
    {
        i++;
        int l=rand()%9;
        int c=rand()%9;
        while(a.mat[l][c].val!=0)
        {
            l=rand()%9; c=rand()%9;
        }
        a.mat[l][c].val=-1; a.mat[l][c].deschisa=0;
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(a.mat[i][j].val!=-1)
                {a.mat[i][j].val=nr_bombe(a,i,j); a.mat[i][j].deschisa=0;}
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
    int x,y; char s;
    cin>>x>>y;
    cout<<"Dati f(flag/marcare mina) sau d(deschide)";
    cin>>s;
    if(a.mat[x][y].val==-1&&s=='d')
    {   cout<<"Ai pierdut. Mai incearca!"<<endl;
        afisare_pierdere(a); return 0;
    }
    while(castig(a)==0)
    {
        if(s=='d')
            {deschidere(a,x,y); system("cls"); afisare(a);}
        else
        {
            a.mat[x][y].marcat=1; system("cls"); afisare(a);
        }
        if(castig(a)==1)
        {
            system("cls"); cout<<"Ai castigat!"; return 0;
        }
        cin>>x>>y;
        cout<<"Dati f(flag/marcare mina) sau d(deschide)";
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
