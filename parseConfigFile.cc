/*
 * Filename      parseConfigFile.cc
 * Date          5/7/2021
 * Author        Toni Avila
 * Email         txa180025@utdallas.edu
 * Course        SE 3377.0W6 Spring 2021
 * Version       1.0
 * Copyright     2021, All Rights Reserved
 *
 * Description
 *      This file parses the contents of a
 *      config file. Also allows for rereading.
 *
 *
 */


#include <iostream>
#include <map>
#include <string>
#include <rude/config.h>
#include "hw6header.h"
#include <stdlib.h>

using namespace std;


void parseConfigFile(bool readAll){

  rude::Config config;
  
  string verbose, logF, pass, versions, directory;

  // if config file opens
  if(config.load(confMap[inFile].c_str())){

    // setting section and querying string values
    config.setSection("Parameters");
    verbose = config.getStringValue("Verbose");
    logF = config.getStringValue("LogFile");
    pass = config.getStringValue("Password");
    versions = config.getStringValue("NumVersions");
    directory = config.getStringValue("WatchDir");

    // if any field is empty, output error messafe to stdout and exit
    if(verbose.empty() || logF.empty() || pass.empty() || versions.empty() || directory.empty()) {
      cout << "Error in config file, missing data. Exiting.." << endl;
      exit(EXIT_FAILURE);
    }

  }else{
    cout << "Config file could not be opened. Exiting..." << endl;
    exit(EXIT_FAILURE); 
 }


  // filling map according to passed bool, cannot overwrite pass or wdir
  if(readAll){
    confMap[verb] = verbose;
    confMap[logfile] = logF;
    confMap[password] = pass;
    confMap[numVer] = versions;
    confMap[wdir] = directory;
  }else{
    confMap[verb] = verbose;
    confMap[logfile] = logF;
    confMap[numVer] = versions;
  }

}
