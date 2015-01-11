# Holiday-Lights-Display-System

	This project is about creating a server process to control some lights
driven by microcontrollers. It is meant to run on a traditional desktop computer
that is connected to a couple of arduinos with ethernet shields on them. It is
meant to allow you select from a couple of shows (you program the shows
yourself) held in an SQLite database or you can let the server generate the show
to the music based on frequency analysis.

#How To Build
You can build this using code::blocks on linux (preferably a yum based distro).
This is written with assumption that you're running a Fedora based distro.
The prefered compiler is GCC.

1. Make sure you have the following packages installed: sqlite3-devel, 
SFML-devel
2. Open the codeblocks project file in codeblocks
3. Change the build target to "release"
4. Build it
5. Exit codeblocks
6. Run the install script. The install script moves the binary to your home
directory under the directory called Holiday-Lights-Server-System, and walks you
through initial set-up.

#Depends on
* SFML (Simple Fast Multimedia Library)
* SQLite3
