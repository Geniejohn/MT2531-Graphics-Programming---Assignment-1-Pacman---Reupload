#include "MovableCharacter"
#include "constants.h"
#include "glm/glm/glm.hpp"

extern Level level;

class Pacman : public MovableCharacter
{
	private:
		int lives;

	public:
		//MovableCharacter(int Id, int x, int y)
		//Call base-class constructor:
		Pacman(int Id) : MovableCharacter(Id, pacman, glm::vec2(GHOST_SPEED*level.retTSize()[0], GHOST_SPEED*level.retTSize()[0]))
		{
			lives = STARTING_LIVES;
		}


		~Pacman()
		{

		}

		glm::vec2 retTilePos()
		{
			return MovableCharacter::tPos;
		}


		void update()
		{
			MovableCharacter::update();
		}


};
