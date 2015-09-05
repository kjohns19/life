#ifndef GRID_H
#define GRID_H

#include <vector>
#include "StateMachine.h"

class Grid
{
public:
   /*Constructors*/
   explicit Grid(bool wrap = false);
   Grid(int width, int height, bool wrap = false);
   Grid(int width, int height, const StateMachine& sm, bool wrap = false);

   /*Updates every cell based on the state machine*/
   void update();

   /*Resizes the grid*/
   void resize(int width, int height);

   void randomize() { randomize(0, 0, m_width, m_height); }
   void randomize(int x, int y, int width, int height);

   /*Gets the state of a cell*/
   state_t getState(int x, int y) const;
   /*Sets the state of a cell*/
   void setState(int x, int y, state_t state);

   int getWidth() const { return m_width; }
   int getHeight() const { return m_height; }

   /*Returns whether the cells wrap around edges*/
   bool getWrap() const { return m_wrap; }
   /*Sets whether the cells wrap around edges*/
   void setWrap(bool wrap) { m_wrap = wrap; }

   /*Gets the state machine used to update cells*/
   StateMachine& getStateMachine() { return m_sm; }
   const StateMachine& getStateMachine() const { return m_sm; }
   /*Sets the state machine used to update cells*/
   void setStateMachine(const StateMachine& sm) { m_sm = sm; }

   int getNeighborCount(int x, int y) const;
private:
   void convertCoordinate(int& x, int& y) const;

   int m_width, m_height;
   std::vector<std::vector<state_t> > m_buffer1, m_buffer2;
   std::vector<std::vector<state_t> >* m_cells, *m_next;
   StateMachine m_sm;
   bool m_wrap;
};

#endif //GRID_H
