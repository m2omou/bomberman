#include "MyGame.hpp"
#include "Menu.hpp"
#include "SerializableFactory.hpp"
#include "ScoreManager.hpp"

int		main()
{
  try
    {
      MyGame	mainGame;

      SerializableFactory::registerMyGame(&mainGame);
      SerializableFactory::init();
      mainGame.run();
    }
  catch (std::exception &e)
    {
      std::cout << e.what() << std::endl;
      return (0);
    }
  return (0);
}
