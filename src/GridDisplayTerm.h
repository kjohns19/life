#ifndef GRID_DISPLAY_TERM
#define GRID_DISPLAY_TERM

#include "Grid.h"

class GridDisplayTerm
{
public:
   GridDisplayTerm(const Grid& grid):
      m_grid(&grid) {}

   const Grid& getGrid() { return *m_grid; }
   void setGrid(const Grid& grid) { m_grid = &grid; }

   void display() const { display(0, 0, m_grid->getWidth(), m_grid->getHeight()); }
   void display(int x, int y, int width, int height) const;
private:
   const Grid* m_grid;
};

#endif //GRID_DISPLAY_TERM
