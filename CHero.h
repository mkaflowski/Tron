#pragma once

#include "CList.h"
#include "CStage.h"

class CHero
{
      COORD position; // position of the head
      COORD startPosition;
      COORD firstMove;
      
      
      public:
             CHero(int x, int y, char head, int startX=0, int startY=0);
             ~CHero();
             //variables:
             CList *visited;
             COORD lastmove;
             char character;
             int points;
             //functions:
             bool dettectBodyCollision(CHero *second);
             bool dettectWallCollision(CStage *stage);
             void move(int x, int y);
             void reset();
};
