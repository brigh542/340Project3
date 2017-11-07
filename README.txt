Description: Project3 is an implementation of a Minix file system, which uses a mounted image provided by the user as its content.  The following functions were implemented, a short description of each will follow: help, mount, unmount, showsuper, traverse, showzone, and quit.  We chose not to implement the optional showfile method. Proper syntax and usage is provided in the help function.

Help: gives available functions and proper syntax
Mount: mounts an image file provided by the user
Unmount: unmounts a mounted image
Showsuper: displays general information about the super block of the Minix system
Traverse: displays a directory listing, similar to the Linux ls command
Showfile: displays the hex dump of a specified file
Showzone: displays all ASCII characters in a specified zone
Quit: unmounts a mounted image, if present, and exits the program


Contribution:

	Ryan Schreiber 45%

	Brighid Rancour 55%



Compiling Instructions: In the project directory, execute the command "make" which will execute the makefile and create a program executable titled "minix"


Execution Instructions: After compiling, to execute the program, enter "./minix" at the prompt; this will execute the program.  From this point, the functions described above will be available for use with proper syntax.



Existing Bugs: We were unable to get the traverse -l function to work correctly, it is causing a segmentation fault; the traverse function without the switch, however, functions properly.  Showzone displays column headers and row numbers, but not the contents of the zone.



Sample Outputs: 

minix: help
Help

Commands:
help
	 displays this help
minimount <argument>
	 mounts a local minix disk
	 <argument> is the name of the image file to mount
miniumount
	 unmounts the currently mounted disk
(function displays all commands, but some were left out of this readme for the sake of length.)



minix: minimount imagefile.img
Disk mounted.


minix: miniumount
Disk has been unmounted.

minix: showsuper
number of inodes:	3424
number of zones:	10240
number of imap_blocks:	1
number of zmap_blocks:	2
first data zone:	112
log zone size:	0
max size:	268966912
magic:	5007
state:	0
zones:	0



minix: traverse
..
A.cla
Aloop1.cla
Aloop1.jav
Aloop2.cla
Aloop2.jav
Aloop3.cla
Aloop3.jav
B.cla
Condit.cla
Condit.jav
D.cla
Demo.cla
Demo.jav
dir1
PolyTest.cla
PolyTest.jav
some.cla
some.java






minix: showfile Demo.jav
70 75 62 6c 69 63 20 63 6c 61 73 73 20 44 65 6d 
6f 20 7b 0a 0a 70 75 62 6c 69 63 20 73 74 61 74 
69 63 20 76 6f 69 64 20 6d 61 69 6e 28 53 74 72 
69 6e 67 5b 5d 20 61 72 67 73 29 20 7b 0a 20 20 
20 20 63 61 6c 6c 65 72 28 29 3b 0a 7d 0a 0a 70 
75 62 6c 69 63 20 73 74 61 74 69 63 20 76 6f 69 
64 20 63 61 6c 6c 65 72 28 29 20 7b 0a 20 20 20 
20 53 79 73 74 65 6d 2e 6f 75 74 2e 70 72 69 6e 
(function displays many more lines, but they were left out of readme for the sake of length)


