#include "MovableCharacter"
#include "constants.h"

class Ghost : MovableCharacter
{
	private:

	public:
		//MovableCharacter(int Id, int x, int y)
		Ghost(int Id) : public MovableCharacter(Id)				//Call base-class constructor:
		{
			lives = STARTING_LIVES;
		}


		~Ghost()
		{

		}

};
