#pragma once
#pragma once

#include <iostream>
#include "CList.h"

using namespace std;

class CStage
{
      string levelnr;
      int checksum;
      
      void getStageInfo();
      int calcChecksum();
      bool checkChecksum(int test);
      
      public:
             CList *wall;
             
             CStage(string x);
             ~CStage();
             void drawStage();
             
};
