# Holiday-Lights-Display-System

	This project is about creating a server process to control some lights
driven by microcontrollers. It is meant to run on a traditional desktop computer
that is connected to a couple of arduinos with ethernet shields on them. It is
meant to allow you select from a couple of shows (you program the shows
yourself) held in an SQLite database or you can let the server generate the show
to the music based on frequency analysis.

# Important notes
* MP3 Files are not supported. Use ogg or wav files instead.

#How To Build
This is written with assumption that you're running a Fedora based distro.
The prefered compiler is GCC.

1. Make sure you have the following packages installed: 
sqlite3-devel, SFML-devel
2. Have a directory with all the music you'll be running on the light system
server. You'll need to enter this during config.
It will ask you if you want to move or copy the files to the server resources
folder latter during the configuration.
3. run install.sh
4. Follow the on screen prompts

The install script will build the program and install it in your home directory.
It will also perform basic configuration on the program.

#Depends on
* SFML (Simple Fast Multimedia Library)
* SQLite3
