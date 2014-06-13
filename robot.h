#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

class Robot
{
    private:
    //difficulte à 0 = robot aleatoire
    //difficulte à 1 = intelligence max
    int m_difficulte;
    char m_pions[3][3];
    int positionChoix;
    int choix[2];


    int calculerPositionChoix(int x, int y);
    void calculerCoupAleatoire();
    void calculerCoupIntelligent();
    bool deuxAlignes(char lettre); //test si deux pions ennemis sont sur la meme ligne et si la 3eme case de la ligne est vide
    bool tripleCentre();
    bool tripleDouble();
    int caseVide();


	public:
	Robot();
	void calculerProchainCoup(); //fonction qui renvoie vers 2 autres fonctions en fonction du niveau de difficulté
    int getDifficulte();//accesseur
    void setDifficulte(int i);//accesseur
    int getPions(int x, int y);//accesseur
    void setPions(char tab[3][3]); //accesseur
    int getPositionChoix(); //accesseur
    void afficherGrille(); //affiche le tableau récupéré par l'ordinateur en console pour faire des tests

};

#endif // ROBOT_H_INCLUDED
