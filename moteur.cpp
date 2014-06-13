#include <sstream>
#include "moteur.h"
#include "robot.h"

using namespace std;

//  6 | 7 | 8
//  3 | 4 | 5
//  0 | 1 | 2
int associerCubeTableauX(int i)
{
    int x;
    if(i==0 || i==3 || i==6)
        x=0;
    else if(i==1 || i==4 || i==7)
        x=1;
    else
        x=2;
    return x;
}

int associerCubeTableauY(int i)
{
    int y;
    if(i==7 || i==8 || i==6)
        y=0;
    else if(i==3 || i==4 || i==5)
        y=1;
    else
        y=2;
    return y;
}

void jouer(int joueur, char tableau[3][3], int position)
{
    int x, y;
    x=associerCubeTableauX(position);
    y=associerCubeTableauY(position);
	if(joueur%2==0 && tableau[x][y]=='.')
        tableau[x][y]='X';

	if(joueur%2!=0 && tableau[x][y]=='.')
        tableau[x][y]='O';

}

bool nulle(char tableau[3][3])
{
	int x, y, nul; nul=0;
	for(x=0; x<3; x++)
	{
		for(y=0; y<3; y++)
		{
			if(tableau[x][y]=='.')
			nul++;
		}
	}
	if(nul==0)
	return true;
	else
	return false;
}

void initialiserTableau(char tableau[3][3])
{
	int x, y;
	for(x=0; x<3; x++)
        for(y=0; y<3; y++)
            tableau[x][y]='.';
}

bool gagne(char tableau[3][3])
{
	int x=0; int y=0;
	for(y=0;y<3;y++){
		if(tableau[x][y]==tableau[x+1][y] && tableau[x+1][y]==tableau[x+2][y] && (tableau[x][y]=='X' || tableau[x][y]=='O'))
		return true;
	}
	y=0; x=0;
	for(x=0;x<3;x++){
		if(tableau[x][y]==tableau[x][y+1] && tableau[x][y+1]==tableau[x][y+2] && (tableau[x][y]=='X' || tableau[x][y]=='O'))
		return true;
	}
	y=0; x=0;
	if(tableau[x][y]==tableau[x+1][y+1] && tableau[x+1][y+1]==tableau[x+2][y+2] && (tableau[x][y]=='X' || tableau[x][y]=='O'))
		return true;
	y=2; x=0;
	if(tableau[x][y]==tableau[x+1][y-1] && tableau[x+1][y-1]==tableau[x+2][y-2] && (tableau[x][y]=='X' || tableau[x][y]=='O'))
		return true;

	return false;
}

string conversion(int x)
{
// créer un flux de sortie
    ostringstream oss;
    // écrire un nombre dans le flux
    oss << x;
    // récupérer une chaîne de caractères
    string result = oss.str();
    return result;
}

void initialiserAffiche(int affiche[2][9])
{
    int i, y;
    for(y=0;y<2;y++)
        for(i=0;i<9;i++)
            affiche[y][i]=0;
}

//fonction permettant de faire des tests pour conaitre les valeurs de la grille de test (gagnant/perdant)
void afficherGrilleConsole(char tableau[3][3])
{
    int x, y;
    for(y=0;y<3;y++)
    {
        for(x=0;x<3;x++)
        {
            cout << tableau[x][y];
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl;
}

void ThreadFunction(void* UserData)
{
    Robot* Ordinateur = static_cast<Robot*>(UserData);
    Ordinateur->calculerProchainCoup();
}
