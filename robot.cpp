#include "robot.h"
#include <SFML/System.hpp>
#include <iomanip>
#include <iostream>

using namespace std;

Robot::Robot()
{
}

int Robot::getDifficulte() {return m_difficulte;}

void Robot::setDifficulte(int i)
{
    if(i==1 || i==0)
        m_difficulte=i;
    else
        m_difficulte=1; //si on pirate le jeu, ce sera alors obligatoirement difficile.
}

int Robot::getPions(int x, int y)
{
    return m_pions[x][y];
}

void Robot::setPions(char tab[3][3])
{
    int x, y;
    for(y=0;y<3;y++)
    {
        for(x=0;x<3;x++)
        {
            m_pions[x][y]=tab[x][y];
        }
    }

}

void Robot::calculerProchainCoup()
{
    if(m_difficulte==0)
        calculerCoupAleatoire();
    else
        calculerCoupIntelligent();
}

void Robot::calculerCoupAleatoire()
{
    //unsigned int InitialSeed = sf::Randomizer::GetSeed();
    int tot=0;
    int gauche[9];
    int droite[9];
    for(int i=0;i<3;i++)
    {
        for(int y=0;y<3;y++)
        {
            if(m_pions[i][y]=='.')
            {
                gauche[tot]=i;
                droite[tot]=y;
                tot++;
            }
        }
    }
    if(tot>0)
    {
        int alea=sf::Randomizer::Random(0, tot-1);
        /*cout <<"variable tot : "<< tot <<endl; //sequence de debugage
        cout <<"variable alea : "<< alea <<endl;
        cout <<"variable gauche[alea] : "<< gauche[alea] <<endl;
        cout <<"variable droite[alea] : "<< droite[alea] <<endl;*/
        m_pions[gauche[alea]][droite[alea]]='X';
        positionChoix=calculerPositionChoix(gauche[alea], droite[alea]);
    }
}

void Robot::calculerCoupIntelligent()
{
    choix[0]='Z';
    choix[1]='Z';
    int i, y; int ennemi=0;
    for(i=0;i<3;i++)
    {
        for(y=0;y<3;y++)
        {
            if(m_pions[i][y]=='O')
                ennemi++;
        }
    }
    if((ennemi==1 || ennemi==0) && m_pions[1][1]=='.')
    {
        m_pions[1][1]='X';
        positionChoix=calculerPositionChoix(1, 1);
    }
    else if(ennemi==1 && m_pions[1][1]=='O')
    {
        m_pions[2][2]='X';
        positionChoix=calculerPositionChoix(2, 2);
    }
    else if(deuxAlignes('X') || deuxAlignes('O'))
    {
        m_pions[choix[0]][choix[1]]='X';
        positionChoix=calculerPositionChoix(choix[0], choix[1]);
    }
    else if(m_pions[0][1]=='O' && m_pions[1][1]=='X' && m_pions[1][0]=='O' && ennemi==2 && m_pions[0][0]=='.')
    { //cas très particulier
        m_pions[0][0]='X';
        positionChoix=calculerPositionChoix(0, 0);
    }
    else if(m_pions[0][1]=='O' && m_pions[1][1]=='X' && m_pions[1][0]=='O' && ennemi==2 && m_pions[0][0]=='.')
    { //cas très particulier
        m_pions[0][0]='X';
        positionChoix=calculerPositionChoix(0, 0);
    }
    else if(m_pions[0][2]=='O' && m_pions[1][1]=='X' && m_pions[1][0]=='O' && ennemi==2 && m_pions[0][0]=='.')
    { //cas très particulier
        m_pions[0][0]='X';
        positionChoix=calculerPositionChoix(0, 0);
    }
    else if(m_pions[2][0]=='O' && m_pions[1][1]=='X' && m_pions[0][1]=='O' && ennemi==2 && m_pions[1][2]=='.')
    { //cas très particulier
        //m_pions[2][2]=='O'
        m_pions[1][2]='X';
        positionChoix=calculerPositionChoix(1, 2);
    }
    else if(m_pions[2][2]=='O' && m_pions[1][1]=='X' && m_pions[0][1]=='O' && ennemi==2 && m_pions[1][2]=='.')
    { //cas très particulier
        m_pions[1][0]='X';
        positionChoix=calculerPositionChoix(1, 0);
    }
    else if(m_pions[1][2]=='O' && m_pions[1][1]=='X' && m_pions[2][2]=='X' && m_pions[0][0]=='O' && ennemi==2 && m_pions[2][0]=='.')
    { //cas très particulier
        m_pions[2][0]='X';
        positionChoix=calculerPositionChoix(2, 0);
    }
    else if(tripleCentre())
    {
        m_pions[0][1]='X';
        positionChoix=calculerPositionChoix(0, 1);
    }
    else if(tripleDouble())
    {
        m_pions[2][0]='X';
        positionChoix=calculerPositionChoix(2, 0);
    }
    else
        calculerCoupAleatoire();
}

bool Robot::tripleDouble()
{
    int tot=0; int y=0; int x; int ennemi=0;
    if(caseVide()>=6)
    {
        for(x=0;x<3;x++)
        {
            if(m_pions[x][y]!='.')
                tot++;

            if(m_pions[x][y]=='O')
                ennemi++;

            if(tot==3 && ennemi==2 && m_pions[1][1]=='O')
                return true;

            y++;
        }
        tot=0; y=2; ennemi=0;
        for(x=0;x<3;x++)
        {
            if(m_pions[x][y]!='.')
                tot++;

            if(m_pions[x][y]=='O')
                ennemi++;

            if(tot==3 && ennemi==2 && m_pions[1][1]=='O')
                return true;

            y--;
        }
    }
    else
        return false;
}

bool Robot::deuxAlignes(char lettre)
{
    int x, y; int tot=0;
    for(x=0;x<3;x++)
    {
        for(y=0;y<3;y++)
        {
            if(m_pions[x][y]==lettre)
                tot++;
            else
            {
                choix[0]=x;
                choix[1]=y;
            }
        }

        if(tot==2 && m_pions[choix[0]][choix[1]]=='.')
            return true;
        tot=0;
    }
    tot=0;
    for(y=0;y<3;y++)
    {
        for(x=0;x<3;x++)
        {
            if(m_pions[x][y]==lettre)
                tot++;
            else
            {
                choix[0]=x;
                choix[1]=y;
            }
        }

        if(tot==2 && m_pions[choix[0]][choix[1]]=='.')
            return true;
        tot=0;
    }
    tot=0; y=0;
    for(x=0;x<3;x++)
    {
        if(m_pions[x][y]==lettre)
            tot++;
        else
        {
            choix[0]=x;
            choix[1]=y;
        }

        if(x==2 && tot==2 && m_pions[choix[0]][choix[1]]=='.')
            return true;

        y++;
    }
    tot=0; y=2;
    for(x=0;x<3;x++)
    {
        if(m_pions[x][y]==lettre)
            tot++;
        else
        {
            choix[0]=x;
            choix[1]=y;
        }

        if(x==2 && tot==2 && m_pions[choix[0]][choix[1]]=='.')
            return true;

        y--;
    }
    return false;
}

bool Robot::tripleCentre()
{
    int tot=0; int y=0; int x; int ennemi=0;
    for(x=0;x<3;x++)
    {
        if(m_pions[x][y]!='.')
            tot++;

        if(m_pions[x][y]=='O')
            ennemi++;

        if(tot==3 && ennemi==2 && m_pions[1][1]=='X')
            return true;

        y++;
    }
    tot=0; y=2; ennemi=0;
    for(x=0;x<3;x++)
    {
        if(m_pions[x][y]!='.')
            tot++;

        if(m_pions[x][y]=='O')
            ennemi++;

        if(tot==3 && ennemi==2 && m_pions[1][1]=='X')
            return true;

        y--;
    }
    return false;
}

int Robot::getPositionChoix()
{
    return positionChoix;
}

int Robot::calculerPositionChoix(int x, int y)
{
    if(x==0)
    {
        if(y==0)
        return 6;
        else if(y==1)
        return 3;
        else
        return 0;
    }
    else if(x==1)
    {
        if(y==0)
        return 7;
        else if(y==1)
        return 4;
        else
        return 1;
    }
    else
    {
        if(y==0)
        return 8;
        else if(y==1)
        return 5;
        else
        return 2;
    }
}

void Robot::afficherGrille()
{
    int x, y;
    for(y=0;y<3;y++)
    {
        for(x=0;x<3;x++)
        {
            cout << m_pions[x][y];
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl;
}

int Robot::caseVide()
{
    int totvide=0;
    for(int xe=0;xe<3;xe++)
    {
        for(int ye=0;ye<3;ye++)
        {
            if(m_pions[xe][ye]=='.')
                totvide++;
        }
    }
    return totvide;
}
