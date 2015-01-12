# Holiday-Lights-Display-System

	This project is about creating a server process to control some lights
driven by microcontrollers. It is meant to run on a traditional desktop computer
that is connected to a couple of arduinos with ethernet shields on them. It is
meant to allow you select from a couple of shows (you program the shows
yourself) held in an SQLite database or you can let the server generate the show
to the music based on frequency analysis.

# Important notes
* MP3 Files are not supported. Use ogg or wav files instead.
* The source code in the arduino folder is meant to be uploaded to an arduino.
You'll need to modify the IP, Port and MAC_ADDRESS vars for you LAN.

#How To Build
This is written with assumption that you're running a Fedora or yum based distro.
The prefered compiler is GCC.
## Requirements
The following packages are required to build and run:
* SFML-devel
* sqlite3-devel
* ncurses-devel
* ffmpeg

## instructions
1. Have a directory with all the music you'll be running on the light system
server. You'll need to enter this during config.
It will ask you if you want to move or copy the files to the server 
resources folder later during the configuration.
2. run install.sh
3. Follow the on screen prompts

The install script will build the program and install it in your home directory.
It will also perform basic configuration on the program.

#Depends on
* SFML (Simple Fast Multimedia Library)
* SQLite3
* ncurses
