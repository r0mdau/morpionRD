#include <fstream>
#include "fenetre.h"

using namespace std;

Fenetre::Fenetre(int largeur, int hauteur) : m_largeur(largeur), m_hauteur(hauteur)
{
}

void Fenetre::changerResolution(int largeur, int hauteur)
{
	m_largeur=largeur;
	m_hauteur=hauteur;
	//on ecrit la nouvelle resolution dans le fichier
	ecrireResolutionRD(largeur, hauteur);
}

int Fenetre::getHauteur() const {return m_hauteur;}

int Fenetre::getLargeur() const {return m_largeur;}

void ecrireResolutionRD(int largeur, int hauteur)
{
	string const nomFichier("texte/resolution.rd");
    ofstream monFlux(nomFichier.c_str());

    if(monFlux)
    {
        monFlux << largeur << endl;
        monFlux << hauteur << endl;
    }
    else
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
}

int recupererResolution(int numero)
{
	ifstream monFlux2("texte/resolution.rd");
    string ligne;
	int i=0;
	int largeur[2];
	//On lit ligne par ligne le fichier jusqu'à ce qu'il n'y ait plus d'enregistrements.
	while(getline(monFlux2, ligne))
	{
		//on convertit la chaine récupérer par getLine en int avec la fonction atoi
		largeur[i] = atoi(ligne.c_str());
		i++;
	}
	return largeur[numero];
}

void caseResolution(sf::RenderWindow &App, sf::Event &Event, sf::Sprite &Case1, sf::Sprite &Case2, sf::Sprite &Case3, sf::Sprite &Checkeur, int &param)
{
	if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.MouseButton.X > Case1.GetPosition().x) && (Event.MouseButton.X < Case1.GetPosition().x+Case1.GetSize().x) && (Event.MouseButton.Y > Case1.GetPosition().y) && (Event.MouseButton.Y < Case1.GetPosition().y+Case1.GetSize().y))
	{
		Checkeur.SetX(Case1.GetPosition().x);
		Checkeur.SetY(Case1.GetPosition().y);
	}
	else if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.MouseButton.X > Case2.GetPosition().x) && (Event.MouseButton.X < Case2.GetPosition().x+Case2.GetSize().x) && (Event.MouseButton.Y > Case2.GetPosition().y) && (Event.MouseButton.Y < Case2.GetPosition().y+Case2.GetSize().y))
	{
		Checkeur.SetX(Case2.GetPosition().x);
		Checkeur.SetY(Case2.GetPosition().y);
	}
	else if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.MouseButton.X > Case3.GetPosition().x) && (Event.MouseButton.X < Case3.GetPosition().x+Case3.GetSize().x) && (Event.MouseButton.Y > Case3.GetPosition().y) && (Event.MouseButton.Y < Case3.GetPosition().y+Case3.GetSize().y))
	{
		Checkeur.SetX(Case3.GetPosition().x);
		Checkeur.SetY(Case3.GetPosition().y);
	}
	param=1;
}

void setXYCheckeur(sf::Sprite &Checkeur, Fenetre Fen, sf::Sprite &Case1, sf::Sprite &Case2, sf::Sprite &Case3)
{
	if(Fen.getLargeur()==1152)
	{
		Checkeur.SetX(Case1.GetPosition().x);
		Checkeur.SetY(Case1.GetPosition().y);
	}
	else if(Fen.getLargeur()==1024)
	{
		Checkeur.SetX(Case2.GetPosition().x);
		Checkeur.SetY(Case2.GetPosition().y);
	}
	else
	{
		Checkeur.SetX(Case3.GetPosition().x);
		Checkeur.SetY(Case3.GetPosition().y);
	}
}

void Fenetre::boutonValiderParametres(sf::RenderWindow &App, sf::Event &Event, sf::Sprite &Checkeur, sf::Sprite &ValiderReso, sf::Sprite &Case1, sf::Sprite &Case2, sf::Sprite &Case3, string &code)
{
    int x, y;
	if (cliqueBouton(Event, ValiderReso)){
		if(Checkeur.GetPosition().y==Case1.GetPosition().y){
		    x=1152; y=864;
		}else if(Checkeur.GetPosition().y==Case2.GetPosition().y){
		    x=1024; y=768;
		}else{
		    x=800; y=600;
		}

		code="accueil";
		ecrireResolutionRD(x, y);
        //App.Create(sf::VideoMode(x, y), "Jeu du morpion par Romain Dauby");
        //changerResolution(x, y);
        //si l'on décommente ces deux lignes, il faudrait relancer le gestionnaire de ressources.
	}
}

bool cliqueBouton(sf::Event &Event, sf::Sprite &BoutonJ)
{
	if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.MouseButton.X > BoutonJ.GetPosition().x) && (Event.MouseButton.X < BoutonJ.GetPosition().x+BoutonJ.GetSize().x) && (Event.MouseButton.Y > BoutonJ.GetPosition().y) && (Event.MouseButton.Y < BoutonJ.GetPosition().y+BoutonJ.GetSize().y))
	return true;
	else
	return false;
}

void initialiserImageSurGrille(sf::Image &Image, int largeur, int hauteur, sf::Sprite Sprite[])
{
	int y=0; int x=0; unsigned int i;
	for(i=0;i<9;i++){
		Sprite[i].SetImage(Image);
		if(i%3==0 && i>1){
			x=0;
			//espacement vertical entre chaque cube de la grille
			y+=hauteur*0.20;
		}
		Sprite[i].SetX(largeur/3.8+x); //Position X du 1er cube de la grille (cube tout en bas à gauche)
		Sprite[i].SetY(hauteur*0.7-y); //Position Y du 1er cube de la grille (cube tout en bas à gauche)
		Sprite[i].Resize(largeur*0.15, largeur*0.15);
		//espacement horizontal entre chaque cube de la grille
		x+=largeur*0.151;
	}
}

void afficherGrille(sf::RenderWindow &App, sf::Sprite Sprite[])
{
	int i;
	for(i=8;i>=0;i--){
		App.Draw(Sprite[i]);
	}
}

void cliqueGrille(sf::Event &Event, sf::Sprite cube[], sf::Sprite rond[], sf::Sprite croix[], int &joueur, char tableau[3][3], sf::RenderWindow &App, int affiche[2][9])
{
	int i;
	for(i=0; i<9;i++){
		if(cliqueBouton(Event, cube[i])){
			jouer(joueur, tableau, i);
			if(joueur%2==0){
				//App.Draw(rond[i]);
				if(affiche[1][i]==0 && affiche[0][i]==0)
                    affiche[0][i]=1;
                else
                    joueur--;
			}else{
				//App.Draw(croix[i]);
				if(affiche[0][i]==0 && affiche[1][i]==0)
                    affiche[1][i]=1;
                else
                    joueur--;
            }
			joueur++;
		}
	}
}

void toucheGrille(sf::Event &Event, int &joueur, char tableau[3][3], int affiche[2][9])
{
    int i;
    if((Event.Type == sf::Event::KeyPressed) && ((Event.Key.Code<=58 && Event.Key.Code>=49) || (Event.Key.Code<=305 && Event.Key.Code>=296)))
    {
        i=recupererToucheAppuyee(Event);
        jouer(joueur, tableau, i);
        if(joueur%2==0)
        {
            //App.Draw(rond[i]);
            if(affiche[1][i]==0 && affiche[0][i]==0)
            {
                affiche[0][i]=1;
                joueur++;
            }
        }
        else
        {
            //App.Draw(croix[i]);
            if(affiche[0][i]==0 && affiche[1][i]==0)
            {
                affiche[1][i]=1;
                joueur++;
            }
        }
    }
}

int recupererToucheAppuyee(sf::Event &Event)
{
//  6 | 7 | 8
//  3 | 4 | 5
//  0 | 1 | 2
    int i;
    for(i=0;i<9;i++)
    {
        if(Event.Key.Code==49+i || Event.Key.Code==296+i)
        return i;
    }
}

void afficherChoixSurGrille(sf::Sprite cube[], int affiche[2][9], sf::Sprite rond[], sf::Sprite croix[], sf::RenderWindow &App)
{
    int i;
	for(i=0; i<9;i++){
            if(affiche[0][i]==1)
                App.Draw(rond[i]);
            if(affiche[1][i]==1)
                App.Draw(croix[i]);
    }
}

bool sourisAuDessusBoutons(sf::Event &Event, sf::Sprite &Bouton)
{
    //test la position actuelle du curseur ainsi que sa position future
    //si le curseur est au-dessus du sprite, alors on l'affiche !
    if((Event.MouseMove.X < Bouton.GetPosition().x+Bouton.GetSize().x && Event.MouseMove.X>Bouton.GetPosition().x &&
        Event.MouseMove.Y<Bouton.GetPosition().y+Bouton.GetSize().y && Event.MouseMove.Y>Bouton.GetPosition().y) ||
       (Event.MouseButton.X < Bouton.GetPosition().x+Bouton.GetSize().x && Event.MouseButton.X>Bouton.GetPosition().x &&
        Event.MouseButton.Y<Bouton.GetPosition().y+Bouton.GetSize().y && Event.MouseButton.Y>Bouton.GetPosition().y))
    {
        return true;
    }
    else
        return false;
}
