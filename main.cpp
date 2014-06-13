#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "fenetre.h"
#include "moteur.h"
#include "robot.h"
#include "tcp.h"
#include <SFML/Graphics.hpp>

using namespace std;

//Premiere dimension pour dire si on affiche rien, un rond ou une croix
//Seconde dimension du tableau pour donner le numéro de la position de l'élément
int affiche[2][9];

int main(int argc, char *argv[])
{
    int x, y;
    string code="accueil";
    int param=0;
    int score1=0;
    int score2=0;
    char tableau[3][3];
    int joueur=1;
    //[rond/croix][numero cube]


	ifstream monFlux("texte/resolution.rd");  //Ouverture d'un fichier en lecture

	int largeur, hauteur;
	if(monFlux && recupererResolution(0)<2000 && recupererResolution(1)<2000){
		largeur=recupererResolution(0);
		hauteur=recupererResolution(1);
	}else{ //valeurs par défaut si l'ouverture du fichier resolution.rd ne s'effectue pas correctement.
		largeur=800;
		hauteur=600;
	}

    initialiserTableau(tableau);

    Fenetre FenetreP(largeur, hauteur);
	Fenetre &FenetrePrincipale=FenetreP;
	//Fenetre FenetrePrincipale(largeur, hauteur);
	Robot Ordi;
	Robot &Ordinateur=Ordi;
    Tcp ConnectionTcp(2435);
    Tcp &Conn=ConnectionTcp;

    //Déclaration du second thread
	sf::Thread Thread(&ThreadFunction, &Ordinateur);

    //chargement de la fenetre
	sf::RenderWindow App(sf::VideoMode(largeur, hauteur), "Jeu du morpion par Romain Dauby");


    //Ici on charge toutes les ressources (images et textes) requis pour le morpion en mémoire
	sf::Image Image;
	if (!Image.LoadFromFile("icones/fermer.png"))
	    return EXIT_FAILURE;

	sf::Sprite Sprite(Image);
	Sprite.Resize(FenetrePrincipale.getLargeur()*0.09375, FenetrePrincipale.getLargeur()*0.09375);
	Sprite.SetX(FenetrePrincipale.getLargeur()-Sprite.GetSize().x);
	Sprite.SetY(FenetrePrincipale.getHauteur()-Sprite.GetSize().y);

	sf::Image BoutonJouer;
	if (!BoutonJouer.LoadFromFile("icones/bouton.png"))
	    return EXIT_FAILURE;

	sf::Sprite BoutonJ(BoutonJouer);
	BoutonJ.Resize(FenetrePrincipale.getLargeur()*0.09375, FenetrePrincipale.getLargeur()*0.09375);
	BoutonJ.SetX(FenetrePrincipale.getLargeur()/3-BoutonJ.GetSize().x/2);
	BoutonJ.SetY(FenetrePrincipale.getHauteur()/3);

	sf::Sprite BoutonJ2(BoutonJouer);
	BoutonJ2.Resize(FenetrePrincipale.getLargeur()*0.09375, FenetrePrincipale.getLargeur()*0.09375);
	BoutonJ2.SetX(FenetrePrincipale.getLargeur()/3-BoutonJ2.GetSize().x/2);
	BoutonJ2.SetY(FenetrePrincipale.getHauteur()/2+BoutonJ2.GetSize().y);

	sf::Sprite BoutonReseau(BoutonJouer);
	BoutonReseau.Resize(FenetrePrincipale.getLargeur()*0.09375, FenetrePrincipale.getLargeur()*0.09375);
	BoutonReseau.SetX(FenetrePrincipale.getLargeur()/3-BoutonJ2.GetSize().x/2);
	BoutonReseau.SetY((BoutonJ.GetPosition().y+BoutonJ2.GetPosition().y)/2);

	sf::Image BoutonSet;
	if (!BoutonSet.LoadFromFile("icones/bouton-settings.png"))
	    return EXIT_FAILURE;

    sf::Sprite BoutonRS(BoutonSet);
	BoutonRS.Resize(FenetrePrincipale.getLargeur()*0.09375, FenetrePrincipale.getLargeur()*0.09375);
	BoutonRS.SetX(FenetrePrincipale.getLargeur()/3-BoutonJ2.GetSize().x/2);
	BoutonRS.SetY((BoutonJ.GetPosition().y+BoutonJ2.GetPosition().y)/2);
	sf::Sprite BoutonS(BoutonSet);
	BoutonS.Resize(FenetrePrincipale.getLargeur()*0.09375, FenetrePrincipale.getLargeur()*0.09375);
	BoutonS.SetX(FenetrePrincipale.getLargeur()/3-BoutonJ.GetSize().x/2);
	BoutonS.SetY(FenetrePrincipale.getHauteur()/3);

	sf::Sprite BoutonS2(BoutonSet);
	BoutonS2.Resize(FenetrePrincipale.getLargeur()*0.09375, FenetrePrincipale.getLargeur()*0.09375);
	BoutonS2.SetX(FenetrePrincipale.getLargeur()/3-BoutonJ2.GetSize().x/2);
	BoutonS2.SetY(FenetrePrincipale.getHauteur()/2+BoutonJ2.GetSize().y);

	sf::Image BoutonRet;
	if (!BoutonRet.LoadFromFile("icones/retour.png"))
	    return EXIT_FAILURE;

	sf::Sprite Retour(BoutonRet);
	Retour.Resize(FenetrePrincipale.getLargeur()*0.09375, FenetrePrincipale.getLargeur()*0.09375);
	Retour.SetX(0);
	Retour.SetY(FenetrePrincipale.getHauteur()-Retour.GetSize().y);

	sf::Image Case;
	if (!Case.LoadFromFile("icones/case.png"))
	    return EXIT_FAILURE;

	sf::Sprite Case1(Case);
	Case1.Resize(FenetrePrincipale.getLargeur()*0.06, FenetrePrincipale.getLargeur()*0.06);
	Case1.SetX(FenetrePrincipale.getLargeur()/2-Case1.GetSize().x*3);
	Case1.SetY(FenetrePrincipale.getHauteur()/2-Case1.GetSize().y*3);
	sf::Sprite Case2(Case);
	Case2.Resize(FenetrePrincipale.getLargeur()*0.06, FenetrePrincipale.getLargeur()*0.06);
	Case2.SetX(FenetrePrincipale.getLargeur()/2-Case1.GetSize().x*3);
	Case2.SetY(FenetrePrincipale.getHauteur()/2);
	sf::Sprite Case3(Case);
	Case3.Resize(FenetrePrincipale.getLargeur()*0.06, FenetrePrincipale.getLargeur()*0.06);
	Case3.SetX(FenetrePrincipale.getLargeur()/2-Case1.GetSize().x*3);
	Case3.SetY(FenetrePrincipale.getHauteur()/2+Case1.GetSize().y*3);

	sf::Image Check;
	if (!Check.LoadFromFile("icones/check.png"))
	    return EXIT_FAILURE;

    sf::Sprite Checkeur(Check);
    Checkeur.Resize(FenetrePrincipale.getLargeur()*0.06, FenetrePrincipale.getLargeur()*0.06);
    // Dans la section parametres, on place deja l'image CHECK sur la case correspondante.
    setXYCheckeur(Checkeur, FenetrePrincipale, Case1, Case2, Case3);

    sf::Image Valid;
	if (!Valid.LoadFromFile("icones/validerReso.png"))
	    return EXIT_FAILURE;

    sf::Sprite ValiderReso(Valid);
    ValiderReso.Resize(FenetrePrincipale.getLargeur()*0.1, FenetrePrincipale.getLargeur()*0.1);
	ValiderReso.SetX(FenetrePrincipale.getLargeur()/2-ValiderReso.GetSize().x);
	ValiderReso.SetY(FenetrePrincipale.getHauteur()-ValiderReso.GetSize().y);


	sf::Image Croix;
	if (!Croix.LoadFromFile("icones/croix.png"))
	    return EXIT_FAILURE;
	    sf::Image Rond;
	if (!Rond.LoadFromFile("icones/rond.png"))
	    return EXIT_FAILURE;
	sf::Image Cube;
	if (!Cube.LoadFromFile("icones/cube.png"))
	    return EXIT_FAILURE;

	sf::Sprite cube[9];
	initialiserImageSurGrille(Cube, FenetrePrincipale.getLargeur(), FenetrePrincipale.getHauteur(), cube);
	sf::Sprite rond[9];
	initialiserImageSurGrille(Rond, FenetrePrincipale.getLargeur(), FenetrePrincipale.getHauteur(), rond);
	sf::Sprite croix[9];
	initialiserImageSurGrille(Croix, FenetrePrincipale.getLargeur(), FenetrePrincipale.getHauteur(), croix);

    //Chargment de la police et des textes
	sf::Font MyFont;
	if (!MyFont.LoadFromFile("texte/police.ttf", 50))
	{
		// Erreurr...
	}
	//Taille idéale 50 pour une largeur d'écran de 1024 px, de meme pour la position :)
	// la taille de la fenetre * 0.050 met la police de présentation à la bonne taille en fonction de la largeur de la fenetre.
	sf::String Text("Bienvenue dans le jeu du morpion", MyFont, FenetrePrincipale.getLargeur()*0.05);
	//FenetrePrincipale.getLargeur()*0.20 = 200/1024...
	//FenetrePrincipale.getHauteur()*0.027 = 20/752 20 étant la position y idéale pour le titre avec une hauteur de fenetre de 752 px.
	Text.Move(FenetrePrincipale.getLargeur()*0.20, FenetrePrincipale.getHauteur()*0.027);

	sf::String ValidReso("valider", MyFont, FenetrePrincipale.getLargeur()*0.05);
	ValidReso.Move(FenetrePrincipale.getLargeur()/2, FenetrePrincipale.getHauteur()-ValiderReso.GetSize().y+FenetrePrincipale.getHauteur()*0.027);

	sf::String Reso1("1152 x 864", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Reso1.Move(Case1.GetPosition().x+Case1.GetSize().x, Case1.GetPosition().y);
	sf::String Reso2("1024 x 768", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Reso2.Move(Case2.GetPosition().x+Case2.GetSize().x, Case2.GetPosition().y);
	sf::String Reso3("800 x 600", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Reso3.Move(Case3.GetPosition().x+Case3.GetSize().x, Case3.GetPosition().y);

	sf::String Param("Choisir sa resolution", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Param.Move(FenetrePrincipale.getLargeur()*0.35, FenetrePrincipale.getHauteur()*0.027);

	sf::String TextJeu("Jouer une partie", MyFont, FenetrePrincipale.getLargeur()*0.05);
	TextJeu.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/3+FenetrePrincipale.getHauteur()*0.033);

	sf::String TextPar("Parametres", MyFont, FenetrePrincipale.getLargeur()*0.05);
	TextPar.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/2+BoutonS.GetSize().y+FenetrePrincipale.getHauteur()*0.033);

	sf::String Joueur1("1 Joueur (I.A.)", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Joueur1.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/3+FenetrePrincipale.getHauteur()*0.033);
	sf::String Joueur2("2 Joueurs", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Joueur2.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/2+BoutonS.GetSize().y+FenetrePrincipale.getHauteur()*0.033);

	sf::String Reseau("Partie en réseau", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Reseau.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, (Joueur1.GetPosition().y+Joueur2.GetPosition().y)/2);

	sf::String Serveur("Créer partie", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Serveur.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/3+FenetrePrincipale.getHauteur()*0.033);
	sf::String Client("Rejoindre partie", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Client.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/2+BoutonS.GetSize().y+FenetrePrincipale.getHauteur()*0.033);

	sf::String IAAleatoire("I.A. aleatoire", MyFont, FenetrePrincipale.getLargeur()*0.05);
	IAAleatoire.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/3+FenetrePrincipale.getHauteur()*0.033);

	sf::String IAIntelligente("I.A. intelligente", MyFont, FenetrePrincipale.getLargeur()*0.05);
	IAIntelligente.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/2+BoutonS.GetSize().y+FenetrePrincipale.getHauteur()*0.033);

	sf::String TextRetour("retour", MyFont, FenetrePrincipale.getLargeur()*0.04);
	TextRetour.Move(Retour.GetSize().x, FenetrePrincipale.getHauteur()-Retour.GetSize().y/1.2);

	sf::String J1("Joueur 1", MyFont, FenetrePrincipale.getLargeur()*0.03);
	J1.Move(0, FenetrePrincipale.getHauteur()/3);
	sf::String J2("Joueur 2", MyFont, FenetrePrincipale.getLargeur()*0.03);
	J2.Move(FenetrePrincipale.getLargeur()/1.2, FenetrePrincipale.getHauteur()/3);
	sf::String J2IA("Ordinateur", MyFont, FenetrePrincipale.getLargeur()*0.03);
	J2IA.Move(FenetrePrincipale.getLargeur()/1.2, FenetrePrincipale.getHauteur()/3);

    //conversion sert à convertir un entier en chaine de caractere : string
	sf::String Score1(conversion(0), MyFont, FenetrePrincipale.getLargeur()*0.1);
	Score1.Move(FenetrePrincipale.getLargeur()*0.0125, FenetrePrincipale.getHauteur()/3+FenetrePrincipale.getHauteur()*0.1);
	sf::String Score2(conversion(0), MyFont, FenetrePrincipale.getLargeur()*0.1);
	Score2.Move(FenetrePrincipale.getLargeur()-FenetrePrincipale.getLargeur()*0.17, FenetrePrincipale.getHauteur()/3+FenetrePrincipale.getHauteur()*0.1);

	sf::String GagneJ1("Le joueur 1 gagne la partie !", MyFont, FenetrePrincipale.getLargeur()*0.05);
	sf::String GagneJ2("Le joueur 2 gagne la partie !", MyFont, FenetrePrincipale.getLargeur()*0.05);
	sf::String GagnePC("L'ordinateur gagne la partie !", MyFont, FenetrePrincipale.getLargeur()*0.05);
	sf::String MatchNull("Match nul !", MyFont, FenetrePrincipale.getLargeur()*0.05);
	GagneJ1.Move(FenetrePrincipale.getLargeur()*0.20, FenetrePrincipale.getHauteur()*0.027);
	MatchNull.Move(FenetrePrincipale.getLargeur()*0.3, FenetrePrincipale.getHauteur()*0.027);
	GagnePC.Move(FenetrePrincipale.getLargeur()*0.20, FenetrePrincipale.getHauteur()*0.027);
	GagneJ2.Move(FenetrePrincipale.getLargeur()*0.20, FenetrePrincipale.getHauteur()*0.027);

    sf::String Rejouer("Rejouer", MyFont, FenetrePrincipale.getLargeur()*0.05);
	Rejouer.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/3+FenetrePrincipale.getHauteur()*0.033);
    sf::String PageAccueil("Page Accueil", MyFont, FenetrePrincipale.getLargeur()*0.05);
	PageAccueil.Move(FenetrePrincipale.getLargeur()/3+BoutonJ.GetSize().x, FenetrePrincipale.getHauteur()/2+BoutonS.GetSize().y+FenetrePrincipale.getHauteur()*0.033);
	///Fin chargement des ressources

	///Démarrage de la boucle du jeu pour l'affichage des images
	while (App.IsOpened())
	{
        Score1.SetText(conversion(score1));
        Score2.SetText(conversion(score2));
		// Process events
		sf::Event Event;
		while (App.GetEvent(Event))
		{
		    // Close window : exit
		    if (Event.Type == sf::Event::Closed)
		        App.Close();

		    // Escape key : exit
		    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
		        App.Close();
		    //clic sur le bouton fermer en bas à droite de la page
			if(cliqueBouton(Event, Sprite))
				App.Close();

            ///On change de page avec la variable code
			if(code=="accueil")
			{
				if(cliqueBouton(Event, BoutonJ))
					code="jouer";
				if(cliqueBouton(Event, BoutonJ2))
					code="parametres";
				// effacer l'écran
				App.Clear();
				App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Text);
				App.Draw(TextJeu);
				App.Draw(TextPar);
				//on position l'image du check sur la case correspondante à la résolution actuelle du jeu
				//avant que l'utilisateur n'ouvre la section parametres
				setXYCheckeur(Checkeur, FenetrePrincipale, Case1, Case2, Case3);
				//si la souris est au-dessus d'un des deux boutons, on affiche la seconde image
				//qui indique que le bouton est sélectionné
				if(sourisAuDessusBoutons(Event, BoutonJ))
                    App.Draw(BoutonS);
                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="jouer")
			{
				if(cliqueBouton(Event, Retour))
					code="accueil";
				if(cliqueBouton(Event, BoutonJ))
					code="difficulte";
				if(cliqueBouton(Event, BoutonJ2))
					code="2players";
                if(cliqueBouton(Event, BoutonReseau))
					code="reseau";

				App.Clear();
				App.Draw(Retour);
				App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(BoutonReseau);
				App.Draw(Reseau);
				App.Draw(Text);
				App.Draw(Joueur1);
				App.Draw(Joueur2);
				App.Draw(TextRetour);
				if(sourisAuDessusBoutons(Event, BoutonJ))
                App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonReseau))
                App.Draw(BoutonRS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);

				initialiserTableau(tableau);
				score1=0; score2=0;
			}
			else if(code=="parametres")
			{
				if(cliqueBouton(Event, Retour))
					code="accueil";

				App.Clear();
				App.Draw(Case1);
				App.Draw(Case2);
				App.Draw(Case3);
				App.Draw(Reso1);
				App.Draw(Reso2);
				App.Draw(Reso3);
				App.Draw(Retour);
				App.Draw(Param);
				caseResolution(App, Event, Case1, Case2, Case3, Checkeur, param);
				if(param==1)
					App.Draw(Checkeur);

				App.Draw(ValiderReso);
				App.Draw(ValidReso);

				App.Draw(TextRetour);
				FenetrePrincipale.boutonValiderParametres(App, Event, Checkeur, ValiderReso, Case1, Case2, Case3, code);
			}
			else if(code=="difficulte")
			{
				if(cliqueBouton(Event, BoutonJ))
					code="aleatoire";
				if(cliqueBouton(Event, BoutonJ2))
					code="intelligente";
				if(cliqueBouton(Event, Retour))
					code="jouer";

				App.Clear();
				App.Draw(Retour);
				App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Text);
				App.Draw(IAAleatoire);
				App.Draw(IAIntelligente);
				App.Draw(TextRetour);
				initialiserTableau(tableau);
				initialiserAffiche(affiche);
				if(sourisAuDessusBoutons(Event, BoutonJ))
                App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="2players")
			{
				if(cliqueBouton(Event, Retour))
					code="jouer";

				App.Clear();
				App.Draw(J1);
				App.Draw(J2);
				App.Draw(Score1);
				App.Draw(Score2);
				App.Draw(Retour);
				App.Draw(Text);
				App.Draw(TextRetour);
				//CUBE
				afficherGrille(App, cube);
				cliqueGrille(Event, cube, rond, croix, joueur, tableau, App, affiche);
				toucheGrille(Event, joueur, tableau, affiche);
				afficherChoixSurGrille(cube, affiche, rond, croix, App);
                if(gagne(tableau) && joueur%2==0){
                    code="GagneJ2";
                    score2++;
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }

                if(gagne(tableau) && joueur%2!=0){
                    code="GagneJ1";
                    score1++;
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }

                if(nulle(tableau))
                {
                    code="Nulle";
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }

			}
			else if(code=="aleatoire")
			{
			    if(Ordinateur.getDifficulte()==1)
                {
                    score1=0;score2=0;
                }
			    Ordinateur.setDifficulte(0);
				if(cliqueBouton(Event, Retour))
					code="difficulte";

				App.Clear();
				App.Draw(J1);
				App.Draw(J2IA);
				App.Draw(Retour);
				App.Draw(Text);
				App.Draw(Score1);
				App.Draw(Score2);
				App.Draw(TextRetour);
				//CUBE
				afficherGrille(App, cube);
				if(joueur%2==0)
				{
                    Ordinateur.setPions(tableau);
                    Ordinateur.calculerProchainCoup();
                    for(y=0;y<3;y++)
                    {
                        for(x=0;x<3;x++)
                        {
                            tableau[x][y]=Ordinateur.getPions(x, y);
                        }
                    }
                    affiche[0][Ordinateur.getPositionChoix()]=1;
                    //afficherGrilleConsole(tableau);
                    //Ordinateur.afficherGrille();
                    joueur++;
				}
				else
				{
                    cliqueGrille(Event, cube, rond, croix, joueur, tableau, App, affiche);
                    toucheGrille(Event, joueur, tableau, affiche);
                }

				afficherChoixSurGrille(cube, affiche, rond, croix, App);
                if(gagne(tableau) && joueur%2!=0){
                    code="GagnePC";
                    score2++;
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }

                if(gagne(tableau) && joueur%2==0){
                    code="GagneJ1PC";
                    score1++;
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }

                if(nulle(tableau))
                {
                    code="NulleOrdi";
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }
			}
			else if(code=="intelligente")
			{
			    if(Ordinateur.getDifficulte()==0)
                {
                    score1=0; score2=0;
                }
			    //On passe le parametre du robot à intelligent.
			    Ordinateur.setDifficulte(1);
				if(cliqueBouton(Event, Retour))
					code="difficulte";

				App.Clear();
				App.Draw(J1);
				App.Draw(J2IA);
				App.Draw(Retour);
				App.Draw(Text);
				App.Draw(Score1);
				App.Draw(Score2);
				App.Draw(TextRetour);
				//CUBE
				afficherGrille(App, cube);
				if(joueur%2==0)
				{
                    Ordinateur.setPions(tableau);
                    Thread.Launch();
                    Thread.Wait();
                    for(int y=0;y<3;y++)
                    {
                        for(int x=0;x<3;x++)
                        {
                            tableau[x][y]=Ordinateur.getPions(x, y);
                        }
                    }
                    affiche[0][Ordinateur.getPositionChoix()]=1;
                    //afficherGrilleConsole(tableau);
                    //Ordinateur.afficherGrille();
                    joueur++;
				}
				else
				{
                    cliqueGrille(Event, cube, rond, croix, joueur, tableau, App, affiche);
                    toucheGrille(Event, joueur, tableau, affiche);
                }

				afficherChoixSurGrille(cube, affiche, rond, croix, App);
                if(gagne(tableau) && joueur%2!=0){
                    code="GagnePC";
                    score2++;
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }

                if(gagne(tableau) && joueur%2==0){
                    code="GagneJ1PC";
                    score1++;
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }

                if(nulle(tableau))
                {
                    code="NulleOrdi";
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }
			}
			else if(code=="reseau")
			{
                if(cliqueBouton(Event, Retour))
					code="jouer";
                if(cliqueBouton(Event, BoutonJ))// ||
                {
                    Conn.setType('s');
                    Conn.connection();
                    code="partieReseau";
                }
                if( cliqueBouton(Event, BoutonJ2))
                {
                    Conn.setType('c');
                    Conn.connection();
                    code="partieReseau";
                }

                App.Clear();
                App.Draw(Text);
                App.Draw(Retour);
                App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Serveur);
				App.Draw(Client);
				App.Draw(TextRetour);
				App.Draw(Retour);

				if(sourisAuDessusBoutons(Event, BoutonJ))
                    App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);

			}
			else if(code=="partieReseau")
			{
                if(cliqueBouton(Event, Retour))
                {
                    Conn.fermerConnextion();
                    code="jouer";
                }

				App.Clear();
				App.Draw(J1);
				App.Draw(J2);
				App.Draw(Retour);
				App.Draw(Text);
				App.Draw(Score1);
				App.Draw(Score2);
				App.Draw(TextRetour);
				//CUBE
				afficherGrille(App, cube);
                if(Conn.getType()=='s')
                {
                    if(Conn.getTour()%2==0)
                        Conn.recevoir(tableau, affiche);
                    else
                    {
                        Conn.cliqueGrille(Event, cube, rond, croix, tableau, App, affiche);
                        Conn.toucheGrille(Event, tableau, affiche);
                    }
                }
                else
                {
                    if(Conn.getTour()%2==0)
                    {
                        Conn.cliqueGrille(Event, cube, rond, croix, tableau, App, affiche);
                        Conn.toucheGrille(Event, tableau, affiche);
                    }
                    else
                        Conn.recevoir(tableau, affiche);
                }

                afficherChoixSurGrille(cube, affiche, rond, croix, App);
                if(gagne(tableau) && Conn.getTour()%2!=0){
                    code="GagneJ2Reseau";
                    score2++;
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }

                if(gagne(tableau) && Conn.getTour()%2==0){
                    code="GagneJ1Reseau";
                    score1++;
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }

                if(nulle(tableau))
                {
                    code="NulleReseau";
                    initialiserTableau(tableau);
                    initialiserAffiche(affiche);
                }
			}
            else if(code=="GagneJ1")
			{
			    if(cliqueBouton(Event, BoutonJ))
					code="2players";
				if(cliqueBouton(Event, BoutonJ2))
					code="accueil";
			    App.Clear();
			    App.Draw(GagneJ1);//fond marrond :)
			    //App.Draw(MatchNull);//fond marrond :)
			    App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Rejouer);
				App.Draw(PageAccueil);

				if(sourisAuDessusBoutons(Event, BoutonJ))
                    App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="GagneJ1Reseau")
			{
			    if(cliqueBouton(Event, BoutonJ))
					code="partieReseau";
				if(cliqueBouton(Event, BoutonJ2))
                {
                    Conn.fermerConnextion();
                    code="accueil";
                }
			    App.Clear();
			    App.Draw(GagneJ1);//fond marrond :)
			    //App.Draw(MatchNull);//fond marrond :)
			    App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Rejouer);
				App.Draw(PageAccueil);

				if(sourisAuDessusBoutons(Event, BoutonJ))
                    App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="GagneJ2Reseau")
			{
			    if(cliqueBouton(Event, BoutonJ))
					code="partieReseau";
				if(cliqueBouton(Event, BoutonJ2))
                {
                    Conn.fermerConnextion();
                    code="accueil";
                }
			    App.Clear();
			    App.Draw(GagneJ2);//fond marrond :)
			    //App.Draw(MatchNull);//fond marrond :)
			    App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Rejouer);
				App.Draw(PageAccueil);

				if(sourisAuDessusBoutons(Event, BoutonJ))
                    App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="GagneJ2")
			{
			    if(cliqueBouton(Event, BoutonJ))
					code="2players";
				if(cliqueBouton(Event, BoutonJ2))
					code="accueil";
			    App.Clear();
			    App.Draw(GagneJ2);//fond marrond :)
			    App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Rejouer);
				App.Draw(PageAccueil);
				if(sourisAuDessusBoutons(Event, BoutonJ))
                App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="GagneJ1PC")
			{
			    joueur=0;
			    if(cliqueBouton(Event, BoutonJ))
			    {
			        if(Ordinateur.getDifficulte()==0)
                        code="aleatoire";
                    else
                        code="intelligente";
			    }
				if(cliqueBouton(Event, BoutonJ2))
					code="accueil";
			    App.Clear();
			    App.Draw(GagneJ1);//fond marrond :)
			    App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Rejouer);
				App.Draw(PageAccueil);
				if(sourisAuDessusBoutons(Event, BoutonJ))
                App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="GagnePC")
			{
			    joueur=0;
			    if(cliqueBouton(Event, BoutonJ))
			    {
			        if(Ordinateur.getDifficulte()==0)
                        code="aleatoire";
                    else
                        code="intelligente";
			    }
				if(cliqueBouton(Event, BoutonJ2))
					code="accueil";
			    App.Clear();
			    App.Draw(GagnePC);//fond marrond :)
			    App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Rejouer);
				App.Draw(PageAccueil);
				if(sourisAuDessusBoutons(Event, BoutonJ))
                App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="Nulle")
			{
			    if(cliqueBouton(Event, BoutonJ))
					code="2players";
				if(cliqueBouton(Event, BoutonJ2))
					code="accueil";
			    App.Clear();
			    App.Draw(MatchNull);//fond marrond :)
			    App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Rejouer);
				App.Draw(PageAccueil);
				if(sourisAuDessusBoutons(Event, BoutonJ))
                App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="NulleReseau")
			{
			    if(cliqueBouton(Event, BoutonJ))
					code="partieReseau";
				if(cliqueBouton(Event, BoutonJ2))
				{
                    Conn.fermerConnextion();
                    code="accueil";
                }
			    App.Clear();
			    App.Draw(MatchNull);//fond marrond :)
			    App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Rejouer);
				App.Draw(PageAccueil);

				if(sourisAuDessusBoutons(Event, BoutonJ))
                    App.Draw(BoutonS);
                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
			else if(code=="NulleOrdi")
			{
			    if(cliqueBouton(Event, BoutonJ))
			    {
			        if(Ordinateur.getDifficulte()==0)
                        code="aleatoire";
                    else
                        code="intelligente";
			    }
				if(cliqueBouton(Event, BoutonJ2))
					code="accueil";
			    App.Clear();
			    App.Draw(MatchNull);//fond marrond :)
			    App.Draw(BoutonJ);
				App.Draw(BoutonJ2);
				App.Draw(Rejouer);
				App.Draw(PageAccueil);
				if(sourisAuDessusBoutons(Event, BoutonJ))
                    App.Draw(BoutonS);

                if(sourisAuDessusBoutons(Event, BoutonJ2))
                    App.Draw(BoutonS2);
			}
        App.Draw(Sprite);
        // Finally, display rendered frame on screen
		App.Display();
		}
	}

	return EXIT_SUCCESS;
}
