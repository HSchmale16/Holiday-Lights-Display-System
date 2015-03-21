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
    # OGGS
    for f in $( find . -name "*.ogg" ) ; do
	    echo "Found $f"
	    insert="Insert into MEDIA(name, path)\
         values('$f', '$f');"
	    sqlite3 $dbFile "$insert"
    done
}

updateMedia
