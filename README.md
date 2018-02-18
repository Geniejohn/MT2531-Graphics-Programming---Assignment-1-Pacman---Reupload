# IMT2531 Graphics Programming - Assignment 1 Pacman
### Jone Skaara (473181)
### Johannes Gabriel Aas (473183)


#### Scalable stuff. Game Supports:
* Level having any number of tiles in both dimensions.
* Any number of portals read from level-file.
* Any number of ghosts read from level-file(max is one ghost per traversable tile).
* Any number of level-files.
* Level symbols are interchangeable.
* Any number of different sprites of different sizes, spritesheet subdivisions(and which subdivision to use for a single sprite).
* Any number of different sprite animations of different playback speeds. Of course, most of the spite attributes apply as well. 
* Any number of textures loaded at a time. Loaded from a list of files in configuration.


#### Other stuff we do well:
* Wrote game without a graphics library like SDL2 or SFML doing all the important graphics stuff for us.
* The map loader compares the characters in level-file to const-values in constants.h and creates the
  map accordingly. This makes it very flexible and scalable.
* Silky smooth Pacman controlls.

* Sturdy navigation-framework which is compatible with all future types of movableCharacter-subclasses.

* main.cpp is clean, since all the big tasks are done by appropriate managers.

* We handle input in such a way that the player can press up while moving horizontally, causing Pacman
  to move up at first chance.

* Ghosts try to close the gap between them and Pacman, but randomly choose to go another way.
  They only make choices in direction when they are allowed to do so, I.E. whenever they hit a
  junction or end of a corridor.

* We weighted modularibility in our design, leading us to create some mangagers that handle their seperate areas of the program.
  Examples of this are: 
  	- A list of assets loaded is kept in configuration, and loaded with a loop, rather than being hard-coded.
  	- If you have an AI, adding it as an enemy is as simple as adding it's texture file to the load list, a new vector,  
  	  switch-case to the level loader and its constructor, upddate, and draw in gameloop.  
  	  Not mentioning a const char to describe what it looks like in the level file.
	- Adding elements like Sprites, Animations, numeric counters is even simpler. Just construct it, and draw it.

* We had extensive use of commits and descriptive commit messages.
* We used the issue-board on GitLab with proper labels to track what was missing, done, ready, and thing that could be improved.


#### Stuff that is almost there:
* Even though the counter that displays the score is ready, detecting the item pickups is ready,  
  we were unable to increment the score counter due to a problem with circle-includes. We're litterally missing a function call.
* The endgame screen, Pacman loosing lives when hit, respawning(with INV frames), detecting last pellet pickup is ready. 
  However, activating the endgame screen is currently impossible due to another problem with circle-includes.
* Due to our focus on modularibility, adding an gameObject like The Cherry would be very easy.  
  However, we have not done this yet due to focusing on more vital features.