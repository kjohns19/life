#include <cmath>
#include <iostream>
#include "Grid.h"
#include <cstdlib>

Grid::Grid(bool wrap):
   m_width(100), m_height(100), m_buffer1(), m_buffer2(),
   m_cells(&m_buffer1), m_next(&m_buffer2),
   m_sm(), m_wrap(wrap)
{
   resize(m_width, m_height);
}
Grid::Grid(int width, int height, bool wrap):
   m_width(width), m_height(height), m_buffer1(), m_buffer2(),
   m_cells(&m_buffer1), m_next(&m_buffer2),
   m_sm(), m_wrap(wrap)
{
   resize(m_width, m_height);
}
Grid::Grid(int width, int height, const StateMachine& sm, bool wrap):
   m_width(width), m_height(height), m_buffer1(), m_buffer2(),
   m_cells(&m_buffer1), m_next(&m_buffer2),
   m_sm(sm), m_wrap(wrap)
{
   resize(m_width, m_height);
}

void Grid::resize(int width, int height)
{
   if (width <= 0 || height <= 0)
      return;
   state_t def = m_sm.getDefaultState();
   int min = std::min(height, (int)m_cells->size());
   for(int i=0;i<min;i++)
      (*m_cells)[i].resize(width, def);
   m_cells->resize(height, std::vector<state_t>(width, def));

   (*m_next) = (*m_cells);

   m_width = width;
   m_height = height;
}

void Grid::randomize(int x, int y, int width, int height)
{
   std::vector<state_t> states = m_sm.getValidStates();
   int size = states.size();
   for(int i=0;i<height;i++)
      for(int j=0;j<width;j++)
      {
         int xx = j+x;
         int yy = i+y;
         int r = rand() % size;
         (*m_cells)[yy][xx] = states[r];
      }
}

void Grid::update()
{
   for(int i=0;i<m_height;i++)
   {
      std::vector<state_t>& row = (*m_cells)[i];
      std::vector<state_t>& rowNext = (*m_next)[i];
      for(int j=0;j<m_width;j++)
      {
         int count = getNeighborCount(j, i);
         rowNext[j] = m_sm.getNextState(row[j], (symbol_t) count);
      }
   }
   std::swap(m_cells, m_next);
}

void Grid::convertCoordinate(int& x, int& y) const
{
   x = (m_width + (x % m_width)) % m_width;
   y = (m_height + (y % m_height)) % m_height;
}

state_t Grid::getState(int x, int y) const
{
   if (x < 0 || x >= m_width || y < 0 || y >= m_height)
   {
      if (m_wrap)
         convertCoordinate(x, y);
      else
         return m_sm.getDefaultState();
   }
   return (*m_cells)[y][x];
}
void Grid::setState(int x, int y, state_t state)
{
   if (x < 0 || x >= m_width || y < 0 || y >= m_height)
   {
      if (m_wrap)
         convertCoordinate(x, y);
      else
         return;
   }
   (*m_cells)[y][x] = state;
}
int Grid::getNeighborCount(int x, int y) const
{
   int count = 0;
   state_t def = m_sm.getDefaultState();
   for(int i=y-1;i<=y+1;i++)
      for(int j=x-1;j<=x+1;j++)
      {
         if (i != y || j != x)
         {
            state_t state = getState(j, i);
            if (state != def)
               count++;
         }
      }
   return count;
}
