#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include "CGame.h"

using namespace std;

CGame::CGame()
{
      HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD top = {0,0};
      COORD size = {100,50};
      COORD menu = {40,22};
      SetConsoleScreenBufferSize(console, size);      
      string dumb;
      
      SetConsoleCursorPosition(console,menu);
      cout<<"        TRON\n\n\t\t\t\t        by Mateusz Kaflowski\n\t\t\t\t           AGH WIMIiP 2012\n\n\t\t\t\t            PRESS ENTER";
      while(GetAsyncKeyState(VK_RETURN) == false){}
      getline(cin, dumb);
      
      string levelnr;
      bool good = 0;;
      do
      {
          clearScreen();
          SetConsoleCursorPosition(console,menu);
          cout<<"CHOOSE LEVEL(1-3): ";
          cin>>levelnr;
          string fileName = "stages/stage" + levelnr + ".txt";
          fstream test;
          test.open(fileName.c_str());
          if(test.good()) 
             good = true;
          else
          {
             SetConsoleCursorPosition(console,menu);
             cout<<"TEHRE IS NO LEVEL NUMBER "<<levelnr;
             Sleep(2000);
          }
          test.close();
      } while(!good);
      
      speed = 70;
      hero1 = new CHero(1,1,'x',1,0);
      hero2 = new CHero(size.X-3,size.Y-4,'z',-1,0);
      stage = new CStage(levelnr);
      Sleep(2000);
}

CGame::~CGame()
{
      delete hero1;
      delete hero2;
      delete stage;
}

void CGame::control()
{                                                      
      if(GetAsyncKeyState(0x41) != false)
         hero1->move(-1,0);
      else if(GetAsyncKeyState(0x44) != false)
         hero1->move(1,0);
      else if(GetAsyncKeyState(0x53) != false)
         hero1->move(0,1);
      else if(GetAsyncKeyState(0x57) != false)
         hero1->move(0,-1);
      else
         hero1->move(hero1->lastmove.X, hero1->lastmove.Y);
      //second hero--------------------------------------- 
     
      if(GetAsyncKeyState(VK_LEFT) != false)
         hero2->move(-1,0);
      else if(GetAsyncKeyState(VK_RIGHT) != false)
         hero2->move(1,0);
      else if(GetAsyncKeyState(VK_DOWN) != false)
         hero2->move(0,1);
      else if(GetAsyncKeyState(VK_UP) != false)
         hero2->move(0,-1);
      else
         hero2->move(hero2->lastmove.X, hero2->lastmove.Y);
      
}

void CGame::updateScore()
{
      HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD size = {100,50};
      
      if(whoWon() == 1)
         hero1->points++;
      else if(whoWon() == 2)
         hero2->points++;
         
      COORD score;
      score.X = 0;
      score.Y = size.Y-2;
      SetConsoleCursorPosition(console,score);
      cout<<"SCORE:\t"<<hero1->character<<": "<<hero1->points<<"\t"<<hero2->character<<": "<<hero2->points;
}

void CGame::play()
{
      HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD top = {0,0};
      COORD size = {100,50};
      COORD menu = {40,22};
      
      while(hero1->points!=1)
      {
          SetConsoleCursorPosition(console,top);
          stage->drawStage();
          updateScore();
          
          while(true)
          {
              if(GetAsyncKeyState(VK_ESCAPE) != false)
                 break;
              control();
              if(whoWon())
                 break;
              Sleep(speed);
          }
          if(GetAsyncKeyState(VK_ESCAPE) != false)
                 break;
          updateScore();
          hero1->reset();
          hero2->reset();
          Sleep(1000);
      }
}

int CGame::whoWon()
{
    /* 0-none
       1-first
       2-second
       3-draw*/
       int who=0;
       if(hero1->dettectBodyCollision(hero2) || hero1->dettectWallCollision(stage))
          who = 2;
       if(hero2->dettectBodyCollision(hero1) || hero2->dettectWallCollision(stage))
          who++;
       return who;
}

void CGame::clearScreen()
{
     HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD top = {0,0};
     SetConsoleCursorPosition(console,top);
     
     for(int i=0; i<50; i++)
         for(int j=0; j<100; j++)
             cout<<" ";
}
