#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "moteur.h"

class Fenetre
{
	public:

	Fenetre(int largeur, int hauteur); //Constructeur de la classe fenetre
	void changerResolution(int largeur, int hauteur); //accesseurs sur les deux parametre de la classe et appelle la fonction ecrireResolution
	int getHauteur() const; //accesseur
	int getLargeur() const;
	void boutonValiderParametres(sf::RenderWindow &App, sf::Event &Event, sf::Sprite &Checkeur, sf::Sprite &ValiderReso, sf::Sprite &Case1, sf::Sprite &Case2, sf::Sprite &Case3, std::string &code);


	private:

    int m_largeur; //largeur de la fenetre
	int m_hauteur; //hauteur de la fenetre

};

///Plutôt que de créer un autre fichier contenant des fonctions et procédures, je les écrit ici
bool cliqueBouton(sf::Event &Event, sf::Sprite &BoutonJ); //test si on clique sur un sprite, renvoie true si c'est le cas
bool sourisAuDessusBoutons(sf::Event &Event, sf::Sprite &Bouton); // teste si la souris est au-dessus d'un sprite
int recupererResolution(int numero); //Fonction qui retourne la hauteur ou la largeur de la fenetre inscrit dans un fichier texte, numero=0 largeur, 1=hauteur
void ecrireResolutionRD(int largeur, int hauteur); //ecris la nouvelle résolution sélectionnée dans un fichier texte
                                                   //ce fichier est lu à chaque ouverture de l'application et détermine la résolution de la fenetre


void caseResolution(sf::RenderWindow &App, sf::Event &Event, sf::Sprite &Case1, sf::Sprite &Case2, sf::Sprite &Case3, sf::Sprite &Checkeur, int &param); //on place le checker sur la case cliquée dans les parametres
void setXYCheckeur(sf::Sprite &Checkeur, Fenetre Fen, sf::Sprite &Case1, sf::Sprite &Case2, sf::Sprite &Case3); //position du checkeur avant l'ouverture de la page des parametres en corrélation avec les dimensions de la fenetre
void initialiserImageSurGrille(sf::Image &Image, int largeur, int hauteur, sf::Sprite Sprite[]); //on initialise la future position des cubes de la grille du morpion (position et dimensions des sprites)
void afficherGrille(sf::RenderWindow &App, sf::Sprite Sprite[]); //Afichage des cubes de la grille du morpion.
void cliqueGrille(sf::Event &Event, sf::Sprite cube[], sf::Sprite rond[], sf::Sprite croix[], int &joueur, char tableau[3][3], sf::RenderWindow &App, int affiche[2][9]); //détecte le clique sur la grille, place l'image en fonction du joueur (X ou O) et fait jouer le joueur dans le moteur.
void afficherChoixSurGrille(sf::Sprite cube[], int affiche[2][9], sf::Sprite rond[], sf::Sprite croix[], sf::RenderWindow &App); //affiche X ou O en fonction du tableau affiche[][].
void toucheGrille(sf::Event &Event, int &joueur, char tableau[3][3], int affiche[2][9]); //Pour jouer avec le pavé numérique
int recupererToucheAppuyee(sf::Event &Event); //renvoie le keycode de la touche du clavier appuyée en partie

#endif // FENETRE_H_INCLUDED
