#ifndef GRID_DISPLAY_H
#define GRID_DISPLAY_H

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "StatePalette.h"

class GridDisplay : public sf::Drawable
{
public:
   explicit GridDisplay(const Grid& grid);
   GridDisplay(const Grid& grid, int cellSize);

   void setGrid(const Grid& grid) { m_grid = &grid; }
   const Grid& getGrid() const { return *m_grid; }

   void setPalette(const StatePalette& palette) { m_colors = palette; }
   StatePalette& getPalette() { return m_colors; }
   const StatePalette& getPalette() const { return m_colors; }

   void setDrawGrid(bool drawGrid) { m_drawGrid = drawGrid; }
   bool getDrawGrid() const { return m_drawGrid; }

   void setCellSize(int cellSize) { m_cellSize = cellSize; }
   int getCellSize() const { return m_cellSize; }

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
   const Grid* m_grid;
   mutable sf::Image m_img;
   StatePalette m_colors;
   bool m_drawGrid;
   int m_cellSize;
};

#endif //GRID_DISPLAY_H
