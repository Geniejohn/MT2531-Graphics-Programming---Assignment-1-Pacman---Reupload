#include "MovableCharacter"
#include "constants.h"
#include "glm/glm/glm.hpp"

class Pacman : MovableCharacter
{
	private:
		int lives;

	public:
		//MovableCharacter(int Id, int x, int y)
		Pacman(int Id) : public MovableCharacter(Id)			//Call base-class constructor:
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
