#include <iostream>
#include <windows.h>
#include <time.h>
#include <string>
#include <fstream>
#include "CGame.h"

int main()
{
  try
  {
    CGame game;      
    game.play();
  }
  catch(string x)
  {
    cout<<x;
  }
  system("pause");
}
