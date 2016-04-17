#pragma once

#include "CHero.h"

class CGame
{
      CHero *hero1;
      CHero *hero2;
      CStage *stage;
      int speed;
      
      void control();
      int whoWon();
      void updateScore();
      void clearScreen();
      
      public:
             CGame();
             ~CGame();
             void play();
};
