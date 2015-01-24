# Holiday-Lights-Display-System

	This project is about creating a server process to control some lights
driven by microcontrollers. It is meant to run on a traditional desktop computer
that is connected to a couple of arduinos with ethernet shields on them. It is
meant to allow you select from a couple of shows (you program the shows
yourself) held in an SQLite database or you can let the server generate the show
to the music based on frequency analysis.

# Important notes
* MP3 Files are not supported. Use ogg or wav files instead.
* The source code in the arduino folder is meant to be uploaded to an arduino or
other arduino compatible microcontroller. You'll need to modify the IP, Port
and MAC_ADDRESS vars for you LAN. As well as how many channels are being ran on
that controller.
* Note flags to glog have to be set through enviroment variables

#How To Build
This is written with assumption that you're running a Fedora or yum based distro.
The prefered compiler is GCC.

## Requirements
The following packages (as named in the fedora repos) are required to build
and run:
* `SFML-devel`
* `sqlite3-devel`
* `ncurses-devel`
* `cdk-devel` (Curses development kit)
* `libsndfile-devel`
* `glog-devel` (Note: on fedora you also need to grab `gflags-devel` )
* ` ffmpeg`
These are the packages as named on the Fedora repo.

## instructions
1. Make sure you have all the dependices (listed above) installed.
2. Have a directory with all the music you'll be running on the light system
server. You'll need to enter this during config.
It will ask you if you want to move or copy the files to the server 
resources folder later during the configuration.
3. run install.sh
4. Follow the on screen prompts

The install script will build the program and install it in your home directory.
It will also perform basic configuration on the program.

#Depends on
* SFML (Simple Fast Multimedia Library)
* SQLite3
* ncurses
* google glog
* ffmpeg
* libsndfile 
* Curses Development Kit
