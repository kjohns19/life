#ifndef STATE_PALETTE_H
#define STATE_PALETTE_H

#include <map>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"

class StatePalette
{
public:
   StatePalette():
      m_colors(), m_def(sf::Color::Black) {}

   void setColor(state_t state, const sf::Color& color);
   const sf::Color& getColor(state_t state) const;
   void removeColor(state_t state);

   void setDefaultColor(const sf::Color& color) { m_def = color; }
   const sf::Color& getDefaultColor() { return m_def; }
private:
   std::map<state_t, sf::Color> m_colors;
   sf::Color m_def;
};

#endif //STATE_PALETTE_H
