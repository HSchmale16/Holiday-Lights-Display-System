/** Implemenation of functions defined in ../include/admin.hpp
 * @author Henry Schmale
 * @date January 11, 2015
 */

#include "../include/Admin.hpp"
#include "../Defaults.hpp"
#include "../include/HolidayLights.hpp" // for db commands
#include "../include/Gui.hpp"
#include "../include/Synthesis.hpp"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <glog/logging.h>

extern int SERVER_RUNS_FOR_SEC; // how long the server should run for

int admin::parseArgs(int argc, char** argv) {
    if(argc <= 1) {
        admin::args::noArgs();
        return 1;
    }
    std::vector<std::string> args = admin::args::createArgVector(argc, argv);
    for(unsigned int i = 0;  i < args.size(); i++) {
        for(unsigned int j = 0; j < admin::args::NUM_POSSIBLE_ARGS; j++) {
            if(args[i].compare(admin::args::POSSIBLE_ARGS[j]) == 0) {
                switch(j) {
                case HELP_ARG:
                    LOG(INFO) << "Just printing the help and then exiting";
                    admin::args::help();
                    return 1;
                case START_ARG:
                    if(args.size() > (i + 1)) {
                        SERVER_RUNS_FOR_SEC = strtol(args[i+1].c_str(),
                                                     NULL, 10);
                        LOG(INFO) << "Server has been set to run for "
                                  <<SERVER_RUNS_FOR_SEC << " Seconds";
                    } else {
                        // No Num specified, just run forever
                        SERVER_RUNS_FOR_SEC = 0;
                        LOG(INFO) << "Server has been set to run forever";
                    }
                    return 0;
                case UPDATE_DB_ARG:
                    LOG(INFO) << "Performing update of media table in the "
                              << "database";
                    system("./updateDB.sh"); //!< @todo make crossplatform
                    return 1;
                case CREATE_DB_ARG:
                    LOG(INFO) << "Just creating a database file then exiting";
                    hl::initDB();
                    hl::shutdown();
                    return 1;
                case MAKE_SHOWS_ARG:
                    /// @todo add ncurses based show editor call here
                    LOG(INFO) << "Launching show editor";
                    admin::initSongEditor();
                    return 1;
                }
            }
        }
    }
    // huh, bad args must've been passed, so quit
    LOG(FATAL) << "Bad Arguements were passed to the programs";
    return admin::args::badArgs();
}

// Song Editor Init
int admin::initSongEditor() {
    // init
    hl::initDB();
    int rc = syn::se::ShowEditor();	// begin show editor, this blocks
    // shut down
    hl::shutdown();
    return rc;
}

// --- Implementation of  admin::args functions below ---
std::vector<std::string> admin::args::createArgVector(int argc, char ** argv) {
    std::vector<std::string> vec;
    for(int i = 1; i < argc; i++) {
        std::string s;
        int j = 0;
        while(argv[i][j] != '\0') {
            s += argv[i][j];
            j++;
        }
        vec.push_back(s);
    }
    return vec;
}

int admin::args::noArgs() {
    printf("No args passed to program\n");
    printf("Usage: HolidayLights {args}\n");
    printf("See help for more information: HolidayLights --help\n");
    return ARG_FAIL;
}

int admin::args::badArgs() {
    printf("Bad Args passed to program\n");
    printf("Usage: HolidayLights {args}\n");
    printf("See help for more information: HolidayLights --help\n");
    return ARG_FAIL;
}

int admin::args::help() {
    using namespace std;
    cout << "--help\tPrints out the help message, then quits" << endl;
    cout << "--start n\tStarts the server and runs for n seconds" << endl;
    cout << "--updateDB\tUpdate the media table by grabbing metadata using a"
         << "bash script. Then exits." << endl;
    cout << "--createDB\tCreates the database file then exit" << endl;
    cout << "--makeShow\tOpen the show editor program." << endl;
    return 0;
}
