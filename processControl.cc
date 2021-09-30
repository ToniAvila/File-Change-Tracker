/*
 * Filename      processControl.cc
 * Date          5/7/2021
 * Author        Toni Avila
 * Email         txa180025@utdallas.edu
 * Course        SE 3377.0W6 Spring 2021
 * Version       1.0
 * Copyright     2021, All Rights Reserved
 *
 * Description 
 *       This file sets up our signal handlers and opens our log/pid 
 *       files as needed. We also utlilize fork() to create a child
 *       process if specified by the value in the map.
 *
 *
 */


#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <string>
#include "hw6header.h"
#include <fstream>
#include <csignal>
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;



void processControl(){
  struct stat buf;
  string pidStr= "cs3377dirmond.pid";
  // registering signal handlers
  signal(SIGINT, signalHandler);
  signal(SIGTERM, signalHandler);
  signal(SIGHUP, signalHandler);


  // checking pidfile status
  if(stat(pidStr.c_str(), &buf) == 0){
    cerr << "Pid file aready exists. Exiting." << endl;
    exit(EXIT_FAILURE);
  }


  // opening logfile  
  log.open(confMap[logfile].c_str(), ios::out);
  if(!(log.is_open())){
    cout << "unable to open log file. Exiting" << endl;
    exit(EXIT_FAILURE);
  }


  cout << "Creating new file CS3377dirmond.pid" << endl;
  fileWPid.open("cs3377dirmond.pid", ios::out);
  if(confMap[daem] == "false"){
    fileWPid << (long)getpid() << endl;
    fileWPid.close();
  }

  cout << "Information will be written to log file." << endl;  

  // if daemon
  if(confMap[daem] == "true"){

    pid_t forkVal = fork();

    // error
    if(forkVal < 0){
      log << "Error when forking" << endl;
      exit(EXIT_FAILURE);
    }else if(forkVal == 0){
      log << "In child (after fork call)" << endl;
      fileWPid << (long) getpid() << endl;
      fileWPid.close();
    }
    else exit(EXIT_SUCCESS);
  }
 
 

   inotifyFunctions();
  
}
