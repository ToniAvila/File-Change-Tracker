/*
 * Filename      parseCommandLine.cc
 * Date          5/7/2021
 * Author        Toni Avila
 * Email         txa180025@utdallas.edu
 * Course        SE 3377.0W6 Spring 2021
 * Version       1.0
 * Copyright     2021, All Rights Reserved
 *
 * Description
 *          This file parses our command line using
 *          tclap.
 *
 */

#include <iostream>
#include <tclap/CmdLine.h>
#include <map>
#include <string>
#include "hw6header.h"

using namespace std;


void parseCommandLine(int argc, char* argv[]){

  // initializing tclap objects
  TCLAP::CmdLine cmd("SE 3377.0W6 Assignment 6", ' ', "1.0");
  TCLAP::SwitchArg daemon("d", "daemon", "run in daemon mode?", cmd, false);
  TCLAP::UnlabeledValueArg<string> infileArg("infile", "name of input file", false, "cs3377dirmond.conf", "config name", false);

  cmd.add(infileArg);

  cmd.parse(argc, argv);

  // seting daemon value
  if(daemon.getValue())
    confMap[daem] = "true";
  else 
    confMap[daem]= "false";
  
  // setting infile value
  confMap[inFile] = infileArg.getValue();

}
