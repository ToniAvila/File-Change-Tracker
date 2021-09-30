#!/usr/bin/make -f
#
# Filename:		Makefile
# Date:			05/06/2021
# Author:		Toni Avila
# Email:		txa180025@utdallas.edu
# Version:		1.0
# Copyright:	        2021, All Rights Reserved
#
# Description:
#
#	A makefile that takes care of 
#	creating dependencies and that builds our program.


# Set up needed values to support make's implicit commands
CXX = g++
CPPFLAGS = -I/home/011/t/tx/txa180025/include 
CXXFLAGS = -Wall

LDFLAGS = -L/home/011/t/tx/txa180025/lib
LDLIBS = -lrudeconfig

PROJECTNAME = Homework6
EXEC = hw6exe


SRCS = hw6main.cc parseCommandLine.cc parseConfigFile.cc processControl.cc signalHandling.cc inotifyFunctions.cc

#HEADERS = $(wildcard *.h)
OBJS := $(patsubst %.cc,%.o,$(SRCS))

# These targets don't create files that Make should inspect
.PHONY: all clean backup

all: $(EXEC)


# Clean up files that we can regenerate or that we don't care about.

clean:
	rm -f $(OBJS) *.d *~ $(EXEC)

cleanWOEXEC:
	rm -f $(OBJS) *.d *~ 

# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


#  This is a rule to link the files.  Pretty standard

$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) -static $(OBJS) $(LDFLAGS) $(LDLIBS) $(CPPFLAGS)


Makefile: $(SRCS:.cc=.d)

# Backup Target.   You should perform a "make backup" command often

backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


# Include the dependency files created by the PreProcessor.  The
# dash in front of the command keeps the system from complaining
# if the files do not exist.  This rule is used in conjunction
# with the magic "Makefile" target above.

-include $(SRCS:.cc=.d)

