#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <SFML/Graphics.hpp>

void initialiserTableau(char tableau[3][3]); //initialise le tableau
void initialiserAffiche(int affiche[2][9]);//initialise l'affichage des croix et des ronds
bool gagne(char tableau[3][3]); //teste si un joueur a gagné
bool nulle(char tableau[3][3]); //Teste si la partie est nulle
void jouer(int joueur, char tableau[3][3], int position); //insère un caractère X ou O en fonction du joueur dans les dimensions du tableau en fonction
// du cube cliqué
int associerCubeTableauX(int i); //associe le numero du cube avec le numero de la première dimension du tableau
int associerCubeTableauY(int i); //associe le numero du cube avec le numero de la seconde dimension du tableau
std::string conversion(int x); //convertit un entier en string
void afficherGrilleConsole(char tableau[3][3]); //affiche le tableau en console pour faire des tests
void ThreadFunction(void* UserData); //second thread

#endif // MOTEUR_H_INCLUDED
