#ifndef TCP_H_INCLUDED
#define TCP_H_INCLUDED

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "fenetre.h"
#include "moteur.h"

class Tcp
{
    private:
    const unsigned short Port; //Port utilisé pour le jeu
    char type; //client ou serveur ? , c ou s
    int tour; //synchronisation, le client ne pourra pas jouer en meme temps que le serveur
    bool connected; //si connecté alors vaut vrai
    char chaine[]; //
    char leter; //croix ou rond en fonction que la machine soit client ou serveur;
    char leterEnnemi; //donc l'autre machine possède l'autre lettre de jeu
    sf::IPAddress ServerAddress;
    sf::SocketTCP Server;
    sf::SocketTCP Client;
    sf::Packet Packet;

    void jouer(char tableau[3][3], int position);
    int associerCubeTableauY(int i);
    void envoyer();
    void ecrireTableauRecu(char tableau[3][3], int affiche[2][9]);
    int recupererToucheXY(int x, int y);


	public:
	Tcp(const unsigned short p_Port); //constructeur
	~Tcp();
	void fermerConnextion();
	void setServeurAdress();
	void setTour(int numero);
	int getTour() const;
    void setType(char p_type);
    char getType() const;
    void connection();
    void recevoir(char tableau[3][3], int affiche[2][9]);
    void toucheGrille(sf::Event &Event, char tableau[3][3], int affiche[2][9]);
    void cliqueGrille(sf::Event &Event, sf::Sprite cube[], sf::Sprite rond[], sf::Sprite croix[], char tableau[3][3], sf::RenderWindow &App, int affiche[2][9]);

};

#endif // TCP_H_INCLUDED
