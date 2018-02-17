# IMT2531 Graphics Programming - Assignment 1 Pacman
### Jone Skaara (473181)
### Johannes Gabriel Aas (473183)

//FORMAT LATER ON.

Scalable stuff:	Map can have any number of tiles in both dimensions.
				Game supports any number of portals read from level-file.
				Game supports any number of ghosts read from level-file.
				Game supports any number of level-files.
				//DESCRIPTION OF SCALABILITY OF SPRITE AND SPRITEANIMATED.
				//DESCRIPTION OF RESOURCEMANAGER-SOLUTION.

main.cpp is clean.

We handle input in such a way that the player can press up while moving horizontally, causing Pacman
to move up at first chance.


Ghosts try to close the gap between them and Pacman, but randomly choses to go another way.
They only make choices in direction when they are allowed to do so, I.E. whenever they hit a
junction or end of a corridor.


We made a lot of different classes and some sub-classes which each do their own different thing.

We had extensive use of commits and detailed messages.
We used the issueboard on GitLab with proper labels.
