#include <iostream>

#include "GridDisplayTerm.h"

void GridDisplayTerm::display(int x, int y, int width, int height) const
{
   for(int i=0;i<height;i++)
   {
      for(int j=0;j<width;j++)
      {
         int xx = i+x;
         int yy = j+y;
         state_t state = m_grid->getState(xx, yy);
         char c;
         if (state <= 9)
            c = '0' + state;
         else if (state <= 35)
            c = 'A' + (state-10);
         else
            c = '#';
         std::cout << c;
      }
      std::cout << std::endl;
   }
   /*std::cout << "----------" << std::endl;

   for(int i=0;i<height;i++)
   {
      for(int j=0;j<width;j++)
      {
         int xx = i+x;
         int yy = j+y;
         int count = m_grid->getNeighborCount(xx, yy);
         std::cout << (char)('0' + count);
      }
      std::cout << std::endl;
   }*/
}
