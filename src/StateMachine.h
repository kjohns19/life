#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <map>
#include <vector>

typedef unsigned char state_t;
typedef unsigned char symbol_t;

class StateMachine
{
public:

   static StateMachine generate(state_t def, int count, ...);

   StateMachine();

   void addTransition(state_t from, state_t to, symbol_t symbol);
   void setDefaultState(state_t state) { m_default_state = state; }

   std::vector<state_t> getValidStates() const;

   state_t getDefaultState() const { return m_default_state; }
   state_t getNextState(state_t current, symbol_t symbol) const;
private:
   typedef std::map<symbol_t, state_t> trans_t;
   typedef std::map<state_t, trans_t> map_t;
   map_t m_transitions;
   state_t m_default_state;


public:
   static const StateMachine AMOEBA;
   static const StateMachine ASSIMILATION;
   static const StateMachine COAGULATIONS;
   static const StateMachine CONWAY;
   static const StateMachine CORAL;
   static const StateMachine DAYANDNIGHT;
   static const StateMachine DIAMOEBA;
   static const StateMachine FLAKES;
   static const StateMachine GNARL;
   static const StateMachine HIGHLIFE;
   static const StateMachine INVERSELIFE;
   static const StateMachine LONGLIFE;
   static const StateMachine MAZE;
   static const StateMachine MAZECTRIC;
   static const StateMachine MOVE;
   static const StateMachine PSEUDOLIFE;
   static const StateMachine REPLICATOR;
   static const StateMachine SEEDS;
   static const StateMachine SERVIETTES;
   static const StateMachine STAINS;
   static const StateMachine TWOBYTWO;
   static const StateMachine THREEFOURLIFE;
   static const StateMachine WALLEDCITIES;
};

#endif //STATE_MACHINE_H
