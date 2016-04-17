#include <iostream>
#include <windows.h>
#include <string>
#include "CHero.h"
#include "CStage.h"

using namespace std;

CHero::CHero(int x, int y, char head='x', int startX, int startY)
{     
      HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
                  
      points = 0;           
                 
      lastmove.X = firstMove.X = startX;
      lastmove.Y = firstMove.Y = startY;
      
      position.X = startPosition.X = x;
      position.Y = startPosition.Y = y;
      
      visited = new CList(-1,-1);
      
      character = head;
      SetConsoleCursorPosition(console,position);
      cout<<character;
}

CHero::~CHero()
{
      delete visited;
}

bool CHero::dettectBodyCollision(CHero *second)
{
     if(visited->find(position))
        return 1;
     else if(second->visited->find(position))
        return 1;
     else
        return 0;
}

bool CHero::dettectWallCollision(CStage *stage)
{
     if(stage->wall->find(position))
        return 1;
     else
        return 0;
}

void CHero::move(int x, int y)
{
      HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

      SetConsoleCursorPosition(console,position);
      cout<<character;
      
      if((lastmove.X == -x && lastmove.Y == y)||(lastmove.X == x && lastmove.Y == -y))
      {
         x = lastmove.X;
         y = lastmove.Y;            
      }
      
      lastmove.X = x;
      lastmove.Y = y;
      
      visited->addToList(position.X, position.Y);
      
      position.X += x;
      position.Y += y;
}

void CHero::reset()
{
      lastmove.X = firstMove.X;
      lastmove.Y = firstMove.Y;
      
      position.X = startPosition.X;
      position.Y = startPosition.Y;
      
      visited->removeAll();
}
