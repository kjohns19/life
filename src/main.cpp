#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "GridDisplay.h"
#include "StatePalette.h"
#include "StateMachine.h"

int main()
{
   const StateMachine* sms[] = {
      &StateMachine::AMOEBA,
      &StateMachine::ASSIMILATION,
      &StateMachine::COAGULATIONS,
      &StateMachine::CONWAY,
      &StateMachine::CORAL,
      &StateMachine::DAYANDNIGHT,
      &StateMachine::DIAMOEBA,
      &StateMachine::FLAKES,
      &StateMachine::GNARL,
      &StateMachine::HIGHLIFE,
      &StateMachine::INVERSELIFE,
      &StateMachine::LONGLIFE,
      &StateMachine::MAZE,
      &StateMachine::MAZECTRIC,
      &StateMachine::MOVE,
      &StateMachine::PSEUDOLIFE,
      &StateMachine::REPLICATOR,
      &StateMachine::SEEDS,
      &StateMachine::SERVIETTES,
      &StateMachine::STAINS,
      &StateMachine::TWOBYTWO,
      &StateMachine::THREEFOURLIFE,
      &StateMachine::WALLEDCITIES
   };
   const char* smStrs[] = {
      "AMOEBA",
      "ASSIMILATION",
      "COAGULATIONS",
      "CONWAY",
      "CORAL",
      "DAYANDNIGHT",
      "DIAMOEBA",
      "FLAKES",
      "GNARL",
      "HIGHLIFE",
      "INVERSELIFE",
      "LONGLIFE",
      "MAZE",
      "MAZECTRIC",
      "MOVE",
      "PSEUDOLIFE",
      "REPLICATOR",
      "SEEDS",
      "SERVIETTES",
      "STAINS",
      "TWOBYTWO",
      "THREEFOURLIFE",
      "WALLEDCITIES"
   };
   int sm_count = sizeof(sms) / sizeof(StateMachine*);
   int currentSM = 0;

   srand(time(NULL));
   Grid grid(400, 300);

   //grid.setStateMachine(StateMachine::CONWAY);
   grid.setStateMachine(*sms[currentSM]);

   StateMachine sm;
   sm.setDefaultState(0);
   sm.addTransition(0, 1, 3);
   sm.addTransition(1, 1, 2);
   sm.addTransition(1, 1, 3);

   /*grid.setState(3, 3, 1);
   grid.setState(4, 3, 1);
   grid.setState(5, 3, 1);
   grid.setState(5, 2, 1);
   grid.setState(4, 1, 1);

   grid.setState(8, 8, 1);
   grid.setState(8, 9, 1);
   grid.setState(9, 8, 1);
   grid.setState(9, 9, 1);*/

   grid.randomize();
   /*int w = grid.getWidth();
   int h = grid.getHeight();
   for(int i=0;i<50;i++)
   {
      grid.setState(w/2+i, h/2, 1);
      grid.setState(w/2-1-i, h/2, 1);
   }*/
   grid.setWrap(true);

   sm.addTransition(0, 2, 6);
   for(int i=0;i<5;i++)
      sm.addTransition(2, 2, i);
   for(int i=5;i<9;i++)
      sm.addTransition(2, 1, i);

   GridDisplay display(grid, 3);
   display.setDrawGrid(false);

   int width = grid.getWidth()*display.getCellSize();
   int height = grid.getHeight()*display.getCellSize();
   sf::RenderWindow window(sf::VideoMode(width, height), "Life!");
   window.setFramerateLimit(100);

   StatePalette& palette = display.getPalette();
   palette.setColor(0, sf::Color::White);
   palette.setColor(1, sf::Color::Black);
   palette.setColor(2, sf::Color(128, 128, 128));
   palette.setDefaultColor(sf::Color::Blue);

   unsigned long long int iteration = 0;


   bool pause = false;
   
   while (window.isOpen())
   {
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            window.close();
         else if (event.type == sf::Event::MouseButtonPressed)
         {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
               std::cout << "RANDOM!" << std::endl;
               grid.randomize();
            }
            else if (event.mouseButton.button == sf::Mouse::Left)
            {
               currentSM++;
               if (currentSM >= sm_count)
                  currentSM = 0;
               std::cout << smStrs[currentSM] << std::endl;
               grid.setStateMachine(*sms[currentSM]);
            }
         }
         else if (event.type == sf::Event::KeyPressed)
         {
            if (event.key.code == sf::Keyboard::Space)
            {
               pause = !pause;
               if (pause)
                  std::cout << "Paused: " << iteration << std::endl;
               else
                  std::cout << "Unpaused" << std::endl;
            }
            else if (event.key.code == sf::Keyboard::S)
            {
               if (pause)
               {
                  iteration++;
                  grid.update();
                  std::cout << "Step: " << iteration << std::endl;
               }
            }
         }
      }
      if (!pause)
      {
         iteration++;
         grid.update();
      }

      window.clear(palette.getColor(0));
      window.draw(display);
      window.display();
   }
   return 0;
}
