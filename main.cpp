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
void umplere(matrice &a,int i,int j,int nrLinii,int nrColoane)
{
    int di[]={-1,-1,0,1,1,1,0,-1},dj[]={0,1,1,1,0,-1,-1,-1};
    for(int k=0;k<8;k++)
    {
        int l=i+di[k]; int c=j+dj[k];
        if(l>=0&&l<nrLinii&&c<nrColoane&&c>=0)
            if(a.mat[l][c].val!=-1)
                a.mat[l][c].val++;
    }
}
void generare_harta(matrice &a,int nrLinii,int nrColoane,int nrBombe)
{
    for(int i=0;i<nrLinii;i++)
        for(int j=0;j<nrColoane;j++)
        {
            a.mat[i][j].val=0;  a.mat[i][j].deschisa=0;a.mat[i][j].marcat=0;
        }
    srand((unsigned)time(0));
    int i=0;unsigned int l,c;
    while(i<nrBombe)
    {
        i++;
        l=rand()%nrLinii;
        c=rand()%nrColoane;
        while(a.mat[l][c].val==-1)
        {
            l=rand()%nrLinii; c=rand()%nrColoane;
        }
        a.mat[l][c].val=-1;
    }
    for(int i=0;i<nrLinii;i++)
        for(int j=0;j<nrColoane;j++)
            if(a.mat[i][j].val==-1)
                umplere(a,i,j,nrLinii,nrColoane);

}
int dl[]={-1,-1,0,1,1,1,0,-1}, dc[]={0,1,1,1,0,-1,-1,-1};
void BKT_Fill(matrice &a, int i, int j,int nrLinii,int nrColoane)
{
    a.mat[i][j].deschisa=1;
    for(int dir=0;dir<8;dir++)
    {
        int ln=i+dl[dir];
        int cn=j+dc[dir];
        if(ln>=0&&ln<nrLinii&&cn>=0&&cn<nrColoane&&a.mat[ln][cn].deschisa==0)
            if(a.mat[ln][cn].val==0)
                BKT_Fill(a,ln,cn,nrLinii,nrColoane);
            else
                a.mat[ln][cn].deschisa=1;

    }
}
int corect(matrice a,int nrLinii,int nrColoane)
{
    for(int i=0;i<nrLinii;i++)
        for(int j=0;j<nrLinii;j++)
            {if(a.mat[i][j].val==-1&&a.mat[i][j].marcat==0)
                return 0;
            if(a.mat[i][j].val!=-1&&a.mat[i][j].deschisa==0)
                return 0;}
    return 1;
}
void deschidere (matrice &a,int i, int j,int nrLinii,int nrColoane)
{
    if(a.mat[i][j].deschisa==1) return;
    if(a.mat[i][j].marcat==1) return;
    if(a.mat[i][j].val!=0) {a.mat[i][j].deschisa=1; return;}
    BKT_Fill(a,i,j,nrLinii,nrColoane);
}
void afisare(matrice a,int nrLinii,int nrColoane,int flags)
{   cout<<setw(2)<<" "<<'|';int OK=0;
    if(nrColoane<10)
        OK=1;
    if(OK==0)
    {for(unsigned int i=0;i<10;i++)
        cout<<setw(2)<<i;
    for(unsigned int i=10;i<nrColoane;i++)
        cout<<setw(2)<<char(i-10+'A');}
    else
     for(unsigned int i=0;i<nrColoane;i++)
        cout<<setw(2)<<i;
        cout<<endl;
    for(unsigned int i=0;i<nrLinii;i++)
    {   if(i<10)
            cout<<setw(2)<<i<<'|'<<" ";
        else
            cout<<setw(2)<<char(i-10+'A')<<'|'<<" ";
        for(unsigned int j=0;j<nrColoane;j++)
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
void afisare_pierdere(matrice a,int nrLinii,int nrColoane)
{   int bombeRamase=0;
   cout<<setw(2)<<'|';int OK=0;
    if(nrColoane<10)
        OK=1;
    if(OK==0)
    {for(unsigned int i=0;i<10;i++)
        cout<<setw(2)<<i;
    for(unsigned int i=10;i<nrColoane;i++)
        cout<<setw(2)<<char(i-10+'A');}
    else
     for(unsigned int i=0;i<nrColoane;i++)
        cout<<setw(2)<<i;
        cout<<endl;
    for(unsigned int i=0;i<nrLinii;i++)
    {
        cout<<i<<'|'<<" ";
        for(unsigned int j=0;j<nrColoane;j++)
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
{   char sir[20],continua[20];
    cout<<"Doriti sa vedeti regulile jocului MINESWEEPER?(DA/NU) ";
    cin>>sir;
    while(!(strcmp(sir,"da")==0||strcmp(sir,"DA")==0||strcmp(sir,"Da")==0||strcmp(sir,"nu")==0||strcmp(sir,"NU")==0||strcmp(sir,"Nu")==0))
        cin>>sir;
    if(strcmp(sir,"da")==0||strcmp(sir,"DA")==0||strcmp(sir,"Da")==0)
        {
            int n=1;
            switch(n)
{
     case 1:
             cout << "\n\r   O tabla contine anumite bombe, pe care jucatorul trebuie sa le intuiasca. Prin introducerea coordonatelor unui patrat impreuna cu caracterul 'd', acesta se deschide si valoarea sa arata numarul de bombe din cele 8 patrate invecinate lui (in cazul in care patratul e la margine, numarul de vecini este mai mic decat 8).";
            n++;
     case 2:
        cout<<"\n\r   Pentru marcarea unui patrat, pe care il consideri ca fiind bomba, cu un stegulet, poti introduce caracterul 'f'; altfel, pentru a-l demarca, se poate folosi caracterul 'u'.";
        n++;
     case 3:
        cout<<"\n\r   Jocul se termina cu succes cand toate patratele, cu exceptia bombelor, sunt descoperite. Jocul este pierdut cand se deschide un patrat ce ascunde o bomba.";
            break;
}
    cout<<endl;
    cout<<"\n   Doriti sa continuati jocul? ";
        cin>>continua;
        while(!(strcmp(continua,"da")==0||strcmp(continua,"DA")==0||strcmp(continua,"Da")==0||strcmp(continua,"nu")==0||strcmp(continua,"NU")==0||strcmp(continua,"Nu")==0))
            cin>>continua;
        if(strcmp(continua,"nu")==0||strcmp(continua,"NU")==0||strcmp(continua,"Nu")==0)
            return 0;
        system("cls");
        }
    matrice a;
    char tip[20];
    cout<<"Sunteti incepator, intermediar sau expert?"<<endl;
    cin.getline(tip,20);
    while(!(strcmp(tip,"incepator")==0||strcmp(tip,"Incepator")==0||strcmp(tip,"intermediar")==0||strcmp(tip,"Intermediar")==0||strcmp(tip,"expert")==0||strcmp(tip,"Expert")==0))
         cin.getline(tip,20);
    int nrLinii,nrColoane, nrBombe;
    if(strcmp(tip,"incepator")==0||strcmp(tip,"Incepator")==0)
        {
            nrLinii=9; nrColoane=9; nrBombe=10;
        }
    else
        if(strcmp(tip,"intermediar")==0||strcmp(tip,"Intermediar")==0)
    {
        nrLinii=9; nrColoane=16; nrBombe=20;
    }
    else
        {
            nrLinii=16; nrColoane=16; nrBombe=40;
        }
    generare_harta(a,nrLinii,nrColoane,nrBombe);
    int flags=nrBombe;
    afisare(a,nrLinii,nrColoane,flags);
    int x,y;char s,l,c;
    cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;
    cin>>l>>c;
    while(!((l>='0'&&l<='9'||l>='A'&&l<='Z')&&(c>='0'&&c<='9'||c>='A'&&c<='Z')))
       { cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;cin>>l>>c;}
    if(l>='0'&&l<='9')
        x=int(l-'0');
    else
        x=int(l-'A'+10);
    if(c>='0'&&c<='9')
        y=int(c-'0');
    else
        y=int(c-'A'+10);
    cout<<"Dati f (flag/marcare mina) sau d (deschide) sau u (unflag/demarcare mina)."<<" ";
    cin>>s;
    if(a.mat[x][y].val==-1&&s=='d')
    {   system("cls");cout<<"Ai pierdut. Mai incearca!"<<endl;
        afisare_pierdere(a,nrLinii,nrColoane); return 0;
    }
    while(corect(a,nrLinii,nrColoane)==0)
    {   if((s!='d'&&s!='f'&&s!='u')||!(x>=0&&x<nrLinii&&y>=0&&y<nrColoane))
        {
        cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;
        cin>>l>>c;
        while(!((l>='0'&&l<='9'||l>='A'&&l<='Z')&&(c>='0'&&c<='9'||c>='A'&&c<='Z')))
        { cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;cin>>l>>c;}
        if(l>='0'&&l<='9')
            x=int(l-'0');
        else
            x=int(l-'A'+10);
        if(c>='0'&&c<='9')
            y=int(c-'0');
        else
            y=int(c-'A'+10);
        cout<<"Dati f (flag/marcare mina) sau d (deschide) sau u (unflag/demarcare mina)."<<" ";
        cin>>s;
        cout<<endl;continue;}
        if(s=='d')
            {deschidere(a,x,y,nrLinii,nrColoane); system("cls"); afisare(a,nrLinii,nrColoane,flags);}
        else
            if(s=='f')
        {
            a.mat[x][y].marcat=1; flags--; system("cls"); afisare(a,nrLinii,nrColoane,flags);
        }
        else
        {
            a.mat[x][y].marcat=0; system("cls"); afisare(a,nrLinii,nrColoane,flags);
        }
        if(corect(a,nrLinii,nrColoane)==1)
        {
            system("cls"); cout<<"Ai castigat!"; return 0;
        }
        cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;
        cin>>l>>c;
        while(!((l>='0'&&l<='9'||l>='A'&&l<='Z')&&(c>='0'&&c<='9'||c>='A'&&c<='Z')))
            { cout<<"Dati coordonatele casutei pe care vreti sa o deschideti/marcati/demarcati."<<endl;cin>>l>>c;}
        if(l>='0'&&l<='9')
            x=int(l-'0');
        else
            x=int(l-'A'+10);
        if(c>='0'&&c<='9')
            y=int(c-'0');
        else
            y=int(c-'A'+10);
        cout<<"Dati f (flag/marcare mina) sau d (deschide) sau u (unflag/demarcare mina)."<<" ";
        cin>>s; cout<<endl;
        if(a.mat[x][y].val==-1&&s=='d')
            {
            system("cls");
            cout<<"Ai pierdut. Mai incearca!"<<endl;
            afisare_pierdere(a,nrLinii,nrColoane);
            return 0;}
    }
    return 0;
}
