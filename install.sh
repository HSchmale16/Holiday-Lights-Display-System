#!/bin/sh
# @author Henry Schmale
# @date January 11, 2015
# @file install.sh
# installs the Holiday Lights System and performs default config on it
# USAGE: ./install.sh INSTALL_DIRECTORY SONG_SEARCH_DIR

#initial arg check
if [ -z $1 ] ; then
	echo "INSTALL_DIR is undefined"
	echo "Usage: ./install.sh INSTALL_DIR SONG_SEARCH_DIR"
	echo "  INSTALL_DIR       The Directory to install to"
	echo "  SONG_SEARCH_DIR   The directory search for songs in"
	exit
fi
if [ -z $2 ] ; then
	echo "SONG_SEARCH_DIR is not defined"
	echo "Usage: ./install.sh INSTALL_DIR SONG_SEARCH_DIR"
	echo "  INSTALL_DIR       The Directory to install to"
	echo "  SONG_SEARCH_DIR   The directory search for songs in"
	exit
fi

# -- Global Variables --
# project name
project="Holiday-Lights-Display-System"
# executable name
exe="HolidayLights.out"
# config file name
cfgFile="resources/cfg.ini"
# db File name
dbFile="lights.db"
#install directory, value depends args passed
c="."
if [ -z $1 ] ; then
	installDir=~/$project
else
	if [ -d $1 ] ; then
		installDir=$1
		if [ $installDir = $c ] ; then
			installDir=$(pwd)
		fi
	else
		echo "Install Directory is Invalid"
		exit
	fi
fi
# song search directory
if [ -z $2 ] ; then
	songSearchDir=~/Music	#default music directory
else
	if [ -d $1 ] ; then
		songSearchDir=$2
		if [ $installDir = $c ] ; then
			installDir=$(pwd)
		fi
	else
		echo "Song Search Directory is Invalid"
		exit
	fi
fi
# song resources folder, where to put the songs
songResDir=$installDir/resources/songs


#declare functions
# builds the program and moves it to it's working directory
function BuildMv
{
	# make/build the program
	make
	
	# move to the install directory
	mkdir $installDir
	mv ./$exe $installDir
	
	# copy necessay scripts to prog directory
	cp ./updateDB.sh $installDir	#database update script
}

# set up the prgm's working directory
function SetUpDir
{
	cd $installDir	# change to working directory
	mkdir resources
	cd resources
	mkdir songs 	# this directory holds the song data
	cd ..			# return from the resources directory
}

#database configurator
# configures the database
function dbCfg
{
	./$exe --createDB # create the database file
	cd resources/songs
	rm -rf *
	cd ../..
	# copy/move the selected files to the songs resource folder
	echo "Copying Files"
	for file in $( ls $songSearchDir ) ; do
		if [ -e $songSearchDir/$file ]; then #check file existance
			cp $songSearchDir/$file $songResDir
		fi
	done
	# begin conversion
	echo "converting files"
	cd $songResDir
	for f in $( ls ) ; do
		ffmpeg -v quiet -i $f $f.ogg
	done
	rm -r *.mp3 # remove incompatible files
	rm -r *.MP3
	# add to database
	cd $installDir
	for f in $( ls resources/songs ) ; do
		inst="Insert into MEDIA(name, path) values('$f', 'resources/songs/$f');"
		sqlite3 $dbFile "$inst"
	done
	# @todo configure devices
	quit="n"
	echo -n "Configure devices now (y/n)? "
	read moreDevs
	until [ $moreDevs = $quit ] ; do
		echo -n "Enter Device Name: "
		read devName
		echo -n "Enter Device IP Address: "
		read devIP
		echo -n "Enter Device Listening Port: "
		read devPort
		echo -n "Enter Device Channels: "
		read devCh
		# create querry
		q="INSERT INTO DEVICES(NAME, IP, PORT, CHANNELS) VALUES('$devName', '$devIP', $devPort, $devCh);"
		sqlite3 $dbFile "$q"
		q="Create table if not exists $devName_SHOWS(ID INT NOT NULL AUTOINCREMENT, SHOW_HM TEXT, SHOW_GEN TEXT);"
		sqlite3 $dbFile "$q"
		echo -n "Do you have more devices to enter (y/n)? "
		read moreDevs
	done
}

# MAIN INSTALL SCRIPT
# Check if the defined directories are ok
echo "Installing to: $installDir"
echo "Searching for music in: $songSearchDir"
echo "Is this OK? Press Enter to Continue, otherwise ctrl-c to cancel."
read # Wait for response
BuildMv
SetUpDir
dbCfg
