#include "pacman.hpp"
#include "constants.h"

//Each space in the map except for the walls are tiles:
class InputManager
{
	private:
		Pacman pacman;
		;

	public:
		//Constructor:
		InputManager()
		{
			pacman = new Pacman;

		}


		//Deconstructor:
		~InputManager()
		{

		}

		void update()
		{
			//PULL INPUT W,A,S,D,ESC,ENTER,UPARROW,DOWNARROW.
			//IF(W,A,S,D) pacman.updateDesiredDir(W,A,S,D);
			//
		}

};
