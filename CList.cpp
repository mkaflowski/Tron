#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include "CList.h"
#include "CStage.h"

CList::CList(int x, int y)  
{
     position.X=x; 
     position.Y=y; 
     next=NULL;
     numberOfElements=0;
}

CList::~CList()
{         
     if(next != NULL)
        delete next;
}

void CList::addToList(int x, int y)
{
     CList *runner = this;
     while(runner->next != NULL)
           runner = runner->next;
     runner->next = new CList(x,y);
     
     numberOfElements++;
}

void CList::removeAll()
{
     if(next != NULL)
     {
        delete next;
        next = NULL;
     }
     numberOfElements = 0;
}

int CList::find(COORD element) //najwczeœniej dodany ma najwiêkszy nr; 0-nie ma elementu
{
    int number = numberOfElements;
    CList *runner = this;
    if(number)
       runner = runner->next;
       
    while(number)
    {
          if(runner->position.X == element.X && runner->position.Y == element.Y)
             return number;
          runner = runner->next;
          number--;
    }
    return number;
}
