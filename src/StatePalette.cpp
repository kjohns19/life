#include "StatePalette.h"

void StatePalette::setColor(state_t state, const sf::Color& color)
{
   m_colors[state] = color;
}
const sf::Color& StatePalette::getColor(state_t state) const
{
   std::map<state_t, sf::Color>::const_iterator it = m_colors.find(state);
   if (it != m_colors.end())
      return it->second;
   return m_def;
}

void StatePalette::removeColor(state_t state)
{
   m_colors.erase(state);
}
