#include "StateMachine.h"
#include <cstdarg>
#include <iostream>
#include <string>
#include <sstream>


StateMachine::StateMachine():
   m_transitions(), m_default_state(0) {}

StateMachine StateMachine::generate(state_t def, int count, ...)
{
   StateMachine sm;
   sm.setDefaultState(def);

   va_list v;
   va_start(v, count);

   for(int i=0;i<count;i++)
   {
      state_t from = (state_t) va_arg(v, int);
      state_t to = (state_t) va_arg(v, int);

      const char* symbolStr = va_arg(v, const char*);
      int symbol;
      std::stringstream ss;
      ss << symbolStr;
      while(ss >> symbol)
         sm.addTransition(from, to, (symbol_t)symbol);
   }
   va_end(v);

   return sm;
}

void StateMachine::addTransition(state_t from, state_t to, symbol_t symbol)
{
   std::pair<map_t::iterator, bool> ins = m_transitions.insert(
      std::make_pair(from, trans_t()));
   ins.first->second[symbol] = to;
}

state_t StateMachine::getNextState(state_t current, symbol_t symbol) const
{
   /*if (current == 0 && symbol == 3)
      return 1;
   else if (current == 1 && (symbol == 2 || symbol == 3))
      return 1;
   return 0;*/
   map_t::const_iterator it1 = m_transitions.find(current);
   if (it1 == m_transitions.end())
      return m_default_state;
   trans_t::const_iterator it2 = it1->second.find(symbol);
   if (it2 == it1->second.end())
      return m_default_state;
   return it2->second;
}

std::vector<state_t> StateMachine::getValidStates() const
{
   std::vector<state_t> states;
   for(map_t::const_iterator it = m_transitions.begin();
       it != m_transitions.end(); ++it)
   {
      states.push_back(it->first);
   }
   return states;
}

const StateMachine StateMachine::AMOEBA = 
   StateMachine::generate(0, 2, 0, 1, "3 5 7", 1, 1, "1 3 5 8");
const StateMachine StateMachine::ASSIMILATION = 
   StateMachine::generate(0, 2, 0, 1, "3 4 5", 1, 1, "4 5 6 7");
const StateMachine StateMachine::COAGULATIONS = 
   StateMachine::generate(0, 2, 0, 1, "3 7 8", 1, 1, "2 3 5 6 7 8");
const StateMachine StateMachine::CONWAY = 
   StateMachine::generate(0, 2, 0, 1, "3", 1, 1, "2 3");
const StateMachine StateMachine::CORAL = 
   StateMachine::generate(0, 2, 0, 1, "4 5 6 7 8", 1, 1, "3");
const StateMachine StateMachine::DAYANDNIGHT = 
   StateMachine::generate(0, 2, 0, 1, "3 6 7 8", 1, 1, "3 4 6 7 8");
const StateMachine StateMachine::DIAMOEBA = 
   StateMachine::generate(0, 2, 0, 1, "3 5 6 7 8", 1, 1, "5 6 7 8");
const StateMachine StateMachine::FLAKES = 
   StateMachine::generate(0, 2, 0, 1, "3", 1, 1, "0 1 2 3 4 5 6 7 8");
const StateMachine StateMachine::GNARL = 
   StateMachine::generate(0, 2, 0, 1, "1", 1, 1, "1");
const StateMachine StateMachine::HIGHLIFE = 
   StateMachine::generate(0, 2, 0, 1, "3 6", 1, 1, "2 3");
const StateMachine StateMachine::INVERSELIFE = 
   StateMachine::generate(0, 2, 0, 1, "0 1 2 3 4 7 8", 1, 1, "0 1 2 3 4 6 7 8");
const StateMachine StateMachine::LONGLIFE = 
   StateMachine::generate(0, 2, 0, 1, "3 4 5", 1, 1, "5");
const StateMachine StateMachine::MAZE = 
   StateMachine::generate(0, 2, 0, 1, "3", 1, 1, "1 2 3 4 5");
const StateMachine StateMachine::MAZECTRIC = 
   StateMachine::generate(0, 2, 0, 1, "3", 1, 1, "1 2 3 4");
const StateMachine StateMachine::MOVE = 
   StateMachine::generate(0, 2, 0, 1, "3 6 8", 1, 1, "2 4 5");
const StateMachine StateMachine::PSEUDOLIFE = 
   StateMachine::generate(0, 2, 0, 1, "3 5 7", 1, 1, "2 3 8");
const StateMachine StateMachine::REPLICATOR = 
   StateMachine::generate(0, 2, 0, 1, "1 3 5 7", 1, 1, "1 3 5 7");
const StateMachine StateMachine::SEEDS = 
   StateMachine::generate(0, 1, 0, 1, "2");
const StateMachine StateMachine::SERVIETTES = 
   StateMachine::generate(0, 1, 0, 1, "2 3 4");
const StateMachine StateMachine::STAINS = 
   StateMachine::generate(0, 2, 0, 1, "3 6 7 8", 1, 1, "2 3 5 6 7 8");
const StateMachine StateMachine::TWOBYTWO = 
   StateMachine::generate(0, 2, 0, 1, "3 6", 1, 1, "1 2 5");
const StateMachine StateMachine::THREEFOURLIFE = 
   StateMachine::generate(0, 2, 0, 1, "3 4", 1, 1, "3 4");
const StateMachine StateMachine::WALLEDCITIES = 
   StateMachine::generate(0, 2, 0, 1, "4 5 6 7 8", 1, 1, "2 3 4 5");
