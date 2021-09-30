/*
 * Filename      hw6main.cc
 * Date          5/7/2021
 * Author        Toni Avila
 * Email         txa180025@utdallas.edu
 * Course        SE 3377.0W6 Spring 2021
 * Version       1.0
 * Copyright     2021, All Rights Reserved
 *
 * Description
 *       This is our main function. Defines the map and files and calls
 *       methods for operation.
 *
 */


#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <string>
#include "hw6header.h"
#include <fstream>

using namespace std;


map<int, string> confMap;
fstream fileWPid;
fstream log;

int main(int argc, char* argv[]){
  parseCommandLine(argc, argv);
  parseConfigFile(true);
  processControl();

   
  return 0;
}
