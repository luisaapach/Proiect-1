#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
struct matrice
{
    struct { int val; unsigned int deschisa; unsigned int marcat;}mat[17][17];
};
void umplere(matrice &a,int i,int j,int dim)
{
    int di[]={-1,-1,0,1,1,1,0,-1},dj[]={0,1,1,1,0,-1,-1,-1};
    for(int k=0;k<8;k++)
    {
        int l=i+di[k]; int c=j+dj[k];
        if(l>=0&&l<dim&&c<dim&&c>=0)
            if(a.mat[l][c].val!=-1)
                a.mat[l][c].val++;
    }
}
void generare_harta(matrice &a,int dim)
{
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
        {
            a.mat[i][j].val=0;  a.mat[i][j].deschisa=0;a.mat[i][j].marcat=0;
        }
    srand((unsigned)time(0));
    int i=0;unsigned int l,c;
    while(i<dim)
    {
        i++;
        l=rand()%dim;
        c=rand()%dim;
        while(a.mat[l][c].val==-1)
        {
            l=rand()%dim; c=rand()%dim;
        }
        a.mat[l][c].val=-1;
    }
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
            if(a.mat[i][j].val==-1)
                umplere(a,i,j,dim);

}
int dl[]={-1,-1,0,1,1,1,0,-1}, dc[]={0,1,1,1,0,-1,-1,-1};
void BKT_Fill(matrice &a, int i, int j,int dim)
{
    a.mat[i][j].deschisa=1;
    for(int dir=0;dir<8;dir++)
    {
        int ln=i+dl[dir];
        int cn=j+dc[dir];
        if(ln>=0&&ln<dim&&cn>=0&&cn<dim&&a.mat[ln][cn].deschisa==0)
            if(a.mat[ln][cn].val==0)
                BKT_Fill(a,ln,cn,dim);
            else
                a.mat[ln][cn].deschisa=1;

    }
}
int corect(matrice a,int dim)
{
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
            {if(a.mat[i][j].val==-1&&a.mat[i][j].marcat==0)
                return 0;
            if(a.mat[i][j].val!=-1&&a.mat[i][j].deschisa==0)
                return 0;}
    return 1;
}
void deschidere (matrice &a,int i, int j,int dim)
{
    if(a.mat[i][j].deschisa==1) return;
    if(a.mat[i][j].marcat==1) return;
    if(a.mat[i][j].val!=0) {a.mat[i][j].deschisa=1; return;}
    BKT_Fill(a,i,j,dim);
}
void afisare(matrice a,int dim,int flags)
{   cout<<setw(2)<<" "<<'|';
    for(unsigned int i=0;i<10;i++)
        cout<<setw(2)<<i;
    for(unsigned int i=10;i<dim;i++)
        cout<<setw(2)<<char(i-10+'A');
    cout<<endl;
    for(unsigned int i=0;i<dim;i++)
    {   if(i<10)
            cout<<setw(2)<<i<<'|'<<" ";
        else
            cout<<setw(2)<<char(i-10+'A')<<'|'<<" ";
        for(unsigned int j=0;j<dim;j++)
            if(a.mat[i][j].deschisa==0&&a.mat[i][j].marcat==0)
                cout<<'X'<<" ";
            else
                if(a.mat[i][j].marcat==1)
                    cout<<'F'<<" ";
                else
                cout<<a.mat[i][j].val<<" ";
        cout<<endl;
    }
    cout<<"Mai aveti disponibile "<<flags<<" flag-uri."<<endl;
}
void afisare_pierdere(matrice a,int dim)
{   int bombeRamase=0;
    cout<<setw(2)<<" "<<'|';
    for(unsigned int i=0;i<10;i++)
        cout<<setw(2)<<i;
    for(unsigned int i=10;i<dim;i++)
        cout<<setw(2)<<char(i-10+'A');
    for(unsigned int i=0;i<dim;i++)
    {
        cout<<i<<'|'<<" ";
        for(unsigned int j=0;j<dim;j++)
            if(a.mat[i][j].val==-1)
                {cout<<char(254)<<" ";
                if(a.mat[i][j].marcat==0)
                    bombeRamase++;}
            else
                if(a.mat[i][j].deschisa==0)
                    cout<<'X'<<" ";
                else
                    cout<<a.mat[i][j].val<<" ";
        cout<<endl;
    }
    cout<<"Mai aveati de descoperit "<<bombeRamase<<" mine.";
}

int main(void)
{
    matrice a;
    char tip[20];
    cout<<"Sunteti incepator sau intermediar?"<<endl;
    cin.getline(tip,20);
    while(!(strcmp(tip,"incepator")==0||strcmp(tip,"Incepator")==0||strcmp(tip,"intermediar")==0||strcmp(tip,"Intermediar")==0))
         cin.getline(tip,20);
    int dimensiune;
    if(strcmp(tip,"incepator")==0||strcmp(tip,"Incepator")==0)
        dimensiune=9;
    else
        dimensiune=16;
    generare_harta(a,dimensiune);
    int flags=dimensiune;
    afisare(a,dimensiune,flags);
    int x,y;char s,t[100];
    cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;
    while(t[1]!=' '&&strlen(t)!=3&&!((t[0]>='0'&&t[0]<='9'||t[0]>='A'&&t[0]<='Z')&&(t[2]>='0'&&t[2]<='9'||t[2]>='A'&&t[2]<='Z')))
        cin.getline(t,100);
    if(t[0]>='0'&&t[0]<='9')
        x=int(t[0]-'0');
    else
        x=int(t[0]-'A'+10);
    if(t[2]>='0'&&t[2]<='9')
        y=int(t[2]-'0');
    else
        y=int(t[2]-'A'+10);
    cout<<"Dati f (flag/marcare mina) sau d (deschide) sau u (unflag/demarcare mina)."<<" ";
    cin>>s;
    if(a.mat[x][y].val==-1&&s=='d')
    {   system("cls");cout<<"Ai pierdut. Mai incearca!"<<endl;
        afisare_pierdere(a,dimensiune); return 0;
    }
    while(corect(a,dimensiune)==0)
    {   if((s!='d'&&s!='f'&&s!='u')||!(x>=0&&x<dimensiune&&y>=0&&y<dimensiune))
        {cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;
    while(t[1]!=' '&&strlen(t)!=3&&!((t[0]>='0'&&t[0]<='9'||t[0]>='A'&&t[0]<='Z')&&(t[2]>='0'&&t[2]<='9'||t[2]>='A'&&t[2]<='Z')))
        cin.getline(t,100);
    if(t[0]>='0'&&t[0]<='9')
        x=int(t[0]-'0');
    else
        x=int(t[0]-'A'+10);
    if(t[2]>='0'&&t[2]<='9')
        y=int(t[2]-'0');
    else
        y=int(t[2]-'A'+10);
    cout<<"Dati f (flag/marcare mina) sau d (deschide) sau u (unflag/demarcare mina)."<<" ";
    cin>>s; continue;}
        if(s=='d')
            {deschidere(a,x,y,dimensiune); system("cls"); afisare(a,dimensiune,flags);}
        else
            if(s=='f')
        {
            a.mat[x][y].marcat=1; flags--; system("cls"); afisare(a,dimensiune,flags);
        }
        else
        {
            a.mat[x][y].marcat=0; system("cls"); afisare(a,dimensiune,flags);
        }
        if(corect(a,dimensiune)==1)
        {
            system("cls"); cout<<"Ai castigat!"; return 0;
        }
        while(t[1]!=' '&&strlen(t)!=3&&!((t[0]>='0'&&t[0]<='9'||t[0]>='A'&&t[0]<='Z')&&(t[2]>='0'&&t[2]<='9'||t[2]>='A'&&t[2]<='Z')))
                cin.getline(t,100);
        if(t[0]>='0'&&t[0]<='9')
            x=int(t[0]-'0');
        else
            x=int(t[0]-'A'+10);
        if(t[2]>='0'&&t[2]<='9')
            y=int(t[2]-'0');
        else
            y=int(t[2]-'A'+10);
        cout<<"Dati f (flag/marcare mina) sau d (deschide) sau u (unflag/demarcare mina)."<<" ";
        cin>>s;
        if(a.mat[x][y].val==-1&&s=='d')
            {
            system("cls");
            cout<<"Ai pierdut. Mai incearca!"<<endl;
            afisare_pierdere(a,dimensiune);
            return 0;}
    }
    return 0;
}
