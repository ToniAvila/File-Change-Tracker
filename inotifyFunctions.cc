/*
 * Filename      inotifyFunctions.cc
 * Date          5/7/2021
 * Author        Toni Avila
 * Email         txa180025@utdallas.edu
 * Course        SE 3377.0W6 Spring 2021
 * Version       1.0
 * Copyright     2021, All Rights Reserved
 *
 * Description
 *       This file creates our inotify interface, checking for errors
 *       along the way. We utilize popen to get the results of the date
 *       command, and system to create the .versions directory  and copy files.
 *
 */


#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include <map>
#include <string>
#include <rude/config.h>
#include "hw6header.h"
#include <fstream>
#include <csignal>
#include <sys/inotify.h>
#include <linux/limits.h>
#include <stdlib.h>

using namespace std;

#define MAX_EVENTS 1024
#define bufsiz  (sizeof(struct inotify_event)) + PATH_MAX + 1
#define LEN_NAME 16
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (MAX_EVENTS * (EVENT_SIZE + LEN_NAME))

string convertToString(char*, int);

void inotifyFunctions(){
 
  // define strings and inotify return checkers
  int fd, wd;
  string pathToWatch = confMap[wdir];
  string dateContents;
  string filename;
  char buffer[BUF_LEN];

  string createVersions = "mkdir -p " +  pathToWatch  + "/.versions";
  string versionsPath = confMap[wdir] + "/.versions/";
  FILE *cmdOutput;
  string cmd = "date '+%Y.%m.%d-%H:%M:%S'"; 
  char* line;
  char tmpbuffer[1024]; 

  // create versions subfolder
  system(createVersions.c_str());  

  // initialize inotify  
  fd = inotify_init();

  // check for error
  if(fd == -1){
    log << "inotfiy init failed. exiting" << endl;
    exit(EXIT_FAILURE);
  }

  // add inotify watch
  wd = inotify_add_watch(fd, pathToWatch.c_str(), IN_CLOSE_WRITE);

  // check for add watch error
  if(wd == -1){
    log << "inotify add watch failed. exiting" << endl;
    exit(EXIT_FAILURE);
  }

  // log message, watching directory
  log << "watching " << pathToWatch << endl;

  string final;
  

  // nested loop for inotify
  while(true){

    int length;
    int i = 0;

    // read length
    length  = read(fd, buffer, BUF_LEN);
    if(length < 0)    log << "read failed bro" << endl;

    // loop to check for IN_MODIFY event
    while(i < length){
      struct inotify_event * event = (struct inotify_event*) &buffer[i];

      if(event->len){
	if(event->mask & IN_CLOSE_WRITE){
	  log << "-------------------" << endl;
	  log << "IN_CLOSE_WRITE event found." << endl;

	  // get date command output
	  cmdOutput = popen(cmd.c_str(), "r");

	  // read date command output
	  line = fgets(tmpbuffer, 1024, cmdOutput);
	  if(line == NULL){
	    fgets(tmpbuffer, 1024, cmdOutput);
	  }

	  if(!cmdOutput){
	    log << "Date command failed." << endl;
	    exit(EXIT_FAILURE);
	  }

	  // creating new filename with date
 	  dateContents = convertToString(line, 0);
	  filename = convertToString(event->name, event->len);
	  final = filename + "." + dateContents;


	  // copy file to .versions folder (cp)
	  cmd = "cp " + pathToWatch + "/" + filename + " " + versionsPath + final;
	  system(cmd.c_str());
	 
	  if(confMap[verb] == "true"){
	    log << "Verbose output enabled." << endl;
	    log << "Command: " +  cmd;
	    log << "New file created in .versions -> " + final;
	  }
	  log << "-------------------" << endl;
	  cmd = "date '+%Y.%m.%d-%H:%M:%S'";

	}



	i += EVENT_SIZE + event->len;
      }

    }

  }

  // cleaning up inotify and popen
  inotify_rm_watch(fd, wd);
  close(fd);
  log.close();
  pclose(cmdOutput);
}

string convertToString(char*a, int len){
  if(a == NULL)
    return ""; 

 string s = a;
 return s;
}
