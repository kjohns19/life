#include <SFML/Graphics.hpp>
#include <iostream>
#include "GridDisplay.h"
#include "Grid.h"
#include "StatePalette.h"

GridDisplay::GridDisplay(const Grid& grid):
   m_grid(&grid), m_drawGrid(true), m_cellSize(16)
{
   m_img.create(m_grid->getWidth(), m_grid->getHeight());
}
GridDisplay::GridDisplay(const Grid& grid, int cellSize):
   m_grid(&grid), m_drawGrid(true), m_cellSize(cellSize)
{
   m_img.create(m_grid->getWidth(), m_grid->getHeight());
}

void GridDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   int width = m_grid->getWidth();
   int height = m_grid->getHeight();

   if (m_img.getSize().x != width || m_img.getSize().y != height)
   {
      std::cout << "Huh" << std::endl;
      m_img.create(width, height);
   }

   for(int i=0;i<height;i++)
      for(int j=0;j<width;j++)
      {
         state_t state = m_grid->getState(j, i);
//         if (state == 0)
//            continue;
         m_img.setPixel(j, i, m_colors.getColor(state));
      }

   sf::Transform old = states.transform;
   states.transform.scale(m_cellSize, m_cellSize, 0, 0);
   sf::Texture tex;
   tex.loadFromImage(m_img);
   sf::Sprite image(tex);
   target.draw(image, states);
   states.transform = old;

   //Draw the grid lines
   if (m_drawGrid)
   {
      sf::RectangleShape rect;
      rect.setFillColor(sf::Color::Black);
      //Horizontal
      rect.setSize(sf::Vector2f(width*m_cellSize, 1));
      for(int i=0;i<height;i++)
      {
         rect.setPosition(0, i*m_cellSize);
         target.draw(rect, states);
      }
      //Vertical
      rect.setSize(sf::Vector2f(1, height*m_cellSize));
      for(int i=0;i<width;i++)
      {
         rect.setPosition(i*m_cellSize, 0);
         target.draw(rect, states);
      }
   }
}
