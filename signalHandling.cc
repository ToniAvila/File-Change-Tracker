/*
 * Filename      signalHandling.cc
 * Date          5/7/2021
 * Author        Toni Avila
 * Email         txa180025@utdallas.edu
 * Course        SE 3377.0W6 Spring 2021
 * Version       1.0
 * Copyright     2021, All Rights Reserved
 *
 * Description
 *       This file contains our signal handler function. It
 *       responds to signals SIGINT/SIGTERM and SIGHUP
 *
 */


#include <csignal>
#include "hw6header.h"
#include <stdlib.h>


using namespace std;


void signalHandler(int num){

  if(num == SIGINT || num == SIGTERM){
   
    log << "Signal SIGINT or SIGTERM received, closing log and removing file with pid." << endl;
    log.close();
    fileWPid.close();
    remove("cs3377dirmond.pid");

    exit(SIGINT);

  }else if(num == SIGHUP){
    // reread conf file
    parseConfigFile(false);
    log << "Received sighup, re reading config file." << endl;
    // when re reading, cannot change pass or wdir
  }
 
}
