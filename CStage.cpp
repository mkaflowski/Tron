#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include "CStage.h"


using namespace std;

CStage::CStage(string x)
{
     levelnr = x;
     wall = new CList(-1,-1);
     getStageInfo();
}

CStage::~CStage()
{       
      delete wall;
}

void CStage::drawStage()
{
     HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD top = {0,0};

     string fileName = "stages/stage" + levelnr + ".txt";
     
     string draw;
     ifstream stageFile(fileName.c_str());
     
     if(stageFile.good())
     { 
       while(getline(stageFile,draw))
             cout<<draw<<endl;
     }
     else
       cout<<"STAGE ERROR\n";
       
     SetConsoleCursorPosition(console,top);
}

void CStage::getStageInfo()
{
     HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD top = {0,0};
     
     SetConsoleCursorPosition(console,top);
     
     string error;
     
     string fileName = "stages/stage" + levelnr + ".txt";
     ifstream stageFile(fileName.c_str());
     
     string chcName = "stages/stage" + levelnr + ".CHC";
     ifstream chcFile(chcName.c_str());
     if(chcFile.good())
     {
        chcFile>>checksum;
     }
     else
     {
         error = "ERROR - THERE IS NO CHECKSUM FILE\n";
         throw error;
     }
     
     string tmp;
     int j=0;
     
     if(stageFile.good())
     { 
       if(!checkChecksum(calcChecksum()))
       {
         error = "ERROR - CHECKSUM DOESN'T MATCH\n";
         throw error;
       }
       while(getline(stageFile,tmp))
             {
                 for(int i=0; i<tmp.length(); i++)
                 {
                     if(tmp[i]=='#')
                        wall->addToList(i,j);
                 }
                 
                 j++;
             }
     }
     else
     {
         error = "STAGE ERROR\n";
         throw error;
     }
}

int CStage::calcChecksum()
{
     int result=0;
     string fileName = "stages/stage" + levelnr + ".txt";
     ifstream stageFile(fileName.c_str());
     
     int i = 1;
     char sign;
     while(stageFile>>sign)
     {
           result += sign + i;
           i++;
     }
     return result;
}

bool CStage::checkChecksum(int test)
{
     if(test == checksum)
        return true;
     return false;
}
