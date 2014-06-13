#include <SFML/Network.hpp>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tcp.h"

using namespace std;

Tcp::Tcp(const unsigned short p_Port) : Port(p_Port)
{
    connected=false;
    tour=0;
}
Tcp::~Tcp()
{
}

void Tcp::fermerConnextion()
{
    Client.Close();
    Server.Close();
}

void Tcp::setServeurAdress()
{
    if(!connected)
    {
        cout<<"Entrez l'adresse ip du serveur de jeu : ";
        cin >> ServerAddress;
        cout <<endl;
    }
}

void Tcp::setTour(int numero) {tour=numero;}
int Tcp::getTour() const {return tour;}
char Tcp::getType() const {return type;}

void Tcp::setType(char p_type)
{
    type=p_type;
    if(type=='s')
    {
        leter='X';
        leterEnnemi='O';
    }
    else
    {
        leter='O';
        leterEnnemi='X';
    }
}

void Tcp::connection()
{
    if(type=='s')
    {
        if (!Server.Listen(Port))
        {
            cout<<"Erreur lecture du port"<<endl;
            return;
        }
        cout << "Adresse locale du serveur : "<<ServerAddress.GetLocalAddress()<<" sur le port " << Port<<endl;
        cout << "Adresse internet du serveur : "<<ServerAddress.GetPublicAddress()<<" sur le port " << Port<<endl;
        cout<<"Pour vous accepter les connexions depuis internet, veuillez activer le port "<<Port<<" dans votre routeur en TCP!"<<endl;
        cout<<endl<< "En attente de connection... " << endl;

        // Wait for a connection
        sf::IPAddress ClientAddress;
        Server.Accept(Client, &ClientAddress);
        cout << "Client connecte : " << ClientAddress << endl;
        Client.SetBlocking(false);
        Server.SetBlocking(false);
   }
   else
   {
       setServeurAdress();
        // Connect to the specified server
        if (Client.Connect(Port, ServerAddress) != sf::Socket::Done)
            return;
        cout << "Connected to server " << ServerAddress <<endl;
        Client.SetBlocking(false);
    }
    connected=true;
}

void Tcp::envoyer()
{
    if(type=='s')
    {
        if (Client.Send(Packet) != sf::Socket::Done)
            return;
        Packet.Clear();
   }
   else
   {
        if (Client.Send(Packet) != sf::Socket::Done)
            return;
        Packet.Clear();
   }
   tour++;
}

void Tcp::recevoir(char tableau[3][3], int affiche[2][9])
{
   if(type=='s')
   {
        if (Client.Receive(Packet) != sf::Socket::Done)
            return;
   }
   else
   {
        if (Client.Receive(Packet) != sf::Socket::Done)
            return;
   }
   tour++;
   ecrireTableauRecu(tableau, affiche);
}

int Tcp::recupererToucheXY(int x, int y)
{
    //  6 | 7 | 8
    //  3 | 4 | 5
    //  0 | 1 | 2
    if(x==0 && y==2)
        return 0;
    else if(x==1 && y==2)
        return 1;
    else if(x==2 && y==2)
        return 2;
    else if(x==0 && y==1)
        return 3;
    else if(x==1 && y==1)
        return 4;
    else if(x==2 && y==1)
        return 5;
    else if(x==0 && y==0)
        return 6;
    else if(x==1 && y==0)
        return 7;
    else
        return 8;
}

void Tcp::ecrireTableauRecu(char tableau[3][3], int affiche[2][9])
{
    int i;
    int x;
    int y;
    Packet >> x >> y;
    if(tableau[x][y]=='.')
        tableau[x][y]=leterEnnemi;

    i=recupererToucheXY(x, y);
    if(tour%2==0)
        affiche[0][i]=1;
    else
        affiche[1][i]=1;
    Packet.Clear();
}

void Tcp::cliqueGrille(sf::Event &Event, sf::Sprite cube[], sf::Sprite rond[], sf::Sprite croix[], char tableau[3][3], sf::RenderWindow &App, int affiche[2][9])
{
	int i;
	for(i=0; i<9;i++){
		if(cliqueBouton(Event, cube[i])){
			jouer(tableau, i);
			if(tour%2==0){
				//App.Draw(rond[i]);
				if(affiche[1][i]==0 && affiche[0][i]==0)
                    affiche[0][i]=1;
                else
                    cout<<"Erreur d'affichage !"<<endl;
			}else{
				//App.Draw(croix[i]);
				if(affiche[0][i]==0 && affiche[1][i]==0)
                    affiche[1][i]=1;
                else
                    cout<<"Erreur d'affichage !"<<endl;
            }
		}
	}
}

void Tcp::toucheGrille(sf::Event &Event, char tableau[3][3], int affiche[2][9])
{
    int i;
    if((Event.Type == sf::Event::KeyPressed) && ((Event.Key.Code<=58 && Event.Key.Code>=49) || (Event.Key.Code<=305 && Event.Key.Code>=296)))
    {
        i=recupererToucheAppuyee(Event);
        jouer(tableau, i);
        if(tour%2==0){
        //App.Draw(rond[i]);
            if(affiche[1][i]==0 && affiche[0][i]==0)
                affiche[0][i]=1;
            else
                cout<<"Erreur d'affichage !"<<endl;
        }else{
            //App.Draw(croix[i]);
            if(affiche[0][i]==0 && affiche[1][i]==0)
                affiche[1][i]=1;
            else
                cout<<"Erreur d'affichage !"<<endl;
        }
    }
}

int Tcp::associerCubeTableauY(int i)
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

void Tcp::jouer(char tableau[3][3], int position)
{
    int x, y;
    char lettre;
    x=associerCubeTableauX(position);
    y=associerCubeTableauY(position);
    if(tableau[x][y]=='.')
    {
        tableau[x][y]=leter; //lettre X pour serveur et O pour client
        Packet << x << y;
        envoyer();
    }
}
