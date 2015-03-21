#!/bin/bash
# @author Henry Schmale
# @date January 11, 2015
# @file install.sh
# This script updates the HolidayLightsSystem Media Table based on files in the
# resources folder

# db File name
dbFile="lights.db"

updateMedia(){
    # Empty the media table
    sqlite3 $dbFile "Delete from Media;"
    for f in $( find resources/songs -name "*.ogg" ) ; do
	    echo "Found $f"
	    insert="Insert into MEDIA(name, path) values('$f', 'resources/songs/$f');"
	    sqlite3 $dbFile "$insert"
    done
}

