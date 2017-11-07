Description: Project3 is an implementation of a Minix file system, which uses a mounted image provided by the user as its content.  The following functions were implemented, a short description of each will follow: help, mount, unmount, showsuper, traverse, showzone, and quit.  We chose not to implement the optional showfile method. Proper syntax and usage is provided in the help function.

Help: gives available functions and proper syntax
Mount: mounts an image file provided by the user
Unmount: unmounts a mounted image
Showsuper: displays general information about the super block of the Minix system
Traverse: displays a directory listing, similar to the Linux ls command
Showzone: displays all ASCII characters in a specified zone
Quit: unmounts a mounted image, if present, and exits the program


Contribution:

	Ryan Schreiber 47%

	Brighid Rancour 53%



Compiling Instructions: In the project directory, execute the command "make" which will execute the makefile and create a program executable titled "minix"


Execution Instructions: After compiling, to execute the program, enter "minix" at the prompt; this will execute the program.  From this point, the functions described above will be available for use with proper syntax.



Existing Bugs: We were unable to get the traverse function to work correctly, and it was left out of the final implementation.



Sample Outputs: 
