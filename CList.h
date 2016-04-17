#pragma once

class CList
{
      COORD position;
      CList *next;
      int numberOfElements;
      
      public:
             CList(int x, int y);  
             ~CList();
             //functions:
             void addToList(int x, int y);
             void removeAll();
             int find(COORD element);
};
