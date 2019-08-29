# PortalGame

**Description:**
  - A prototype / framework for a simple 2D "Portal game" clone made mainly to test out some simple physics 
  and entity management mechanisms (Made in c++ using the SFML library)
  - Also contains a basic Level editor (Made in python using the pygame library)
  
**Requirements:**
  1. Linux operating system
  2. GCC compiler
  3. Python >= 2 interpreter

**Installing and running the game (Linux):**
  1. *Installing SFML*
      - Exectute the command `sudo apt-get install libsfml-dev` using the terminal
      - A more comprehensive installation guide can be found at (https://www.sfml-dev.org/tutorials/2.5/start-linux.php)
      
  2. *Installing pygame*
      - Execute the command `sudo apt-get install python-pygame` using the terminal
      - A more comprehensive installation guide can be found at (https://www.pygame.org/wiki/GettingStarted)
      
  3. *Running the launcher*
      - Go to the directory where you cloned or downloaded the repository
      - To run the launcher exectue the command `./launcher` using the terminal
      - From the launcher you can build the game, run the game, run the level editor and view the existing levels
      
 **Game controls:**
   - W, A, S, D for movement
   - Right and Left mouse buttons for shooting portals
   - Escape to exit the game
   
 **Editor controls:**
   - W, A, S, D for moving the camera
   - Left mouse to select and use tools
   - Right mouse to delete entities (tiles)
   - Escape to exit the editor
