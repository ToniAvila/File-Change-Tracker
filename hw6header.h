/*
 * Filename      hw6header.h
 * Date          5/7/2021
 * Author        Toni Avila
 * Email         txa180025@utdallas.edu
 * Course        SE 3377.0W6 Spring 2021
 * Version       1.0
 * Copyright     2021, All Rights Reserved
 *
 * Description
 *        This is the header file for all our cc files.
 *        Holds prototypes and enum, as well as utilizing extern.
 *
 */


#ifndef    hw6header_h
#define    hw6header_h


#include <string>
#include <map>
#include <fstream>

using namespace std;

extern map<int, string> confMap;
extern fstream log;
extern fstream fileWPid;

enum data{daem, inFile, verb, logfile, password, numVer, wdir};

void parseCommandLine(int, char* argv[]);
void parseConfigFile(bool);
void processControl();
void signalHandler(int);
void inotifyFunctions();

#endif
