# Welcomre to Mamat, 044101
#
# This is the project's Makefile. It contains the instructions for compiling
# the projects C files, and then link the generated objects into an executable.
# This simple file will compile "main.c" to "main.o" and then link it (with C
# runtime library) to the executable "prog.exe".
#
# To compile, open the terminal in the folder that contains
# this file and run "make".
#
# To clean, open the terminal in the folder that contains
# this file and run "make clean".
#
# All eclipse projects in this machine are under /home/mamat/Documents/

#Defenitions
CXX = g++
CXXFLAGS = -Wall -Wextra -L. -g -O3
RM = rm -f 
OBJS = ip.o port.o field.o string.o


all:firewall.exe libfirewall.so

libfirewall.so: $(OBJS)
	$(CXX) $(CXXFLAGS) -fpic -shared $(OBJS) -o libfirewall.so
	
firewall.exe: main.cpp libfirewall.so
	$(CXX) $(CXXFLAGS) main.cpp -o firewall.exe -lfirewall -linput -L.

#Dependencies - 
	
main.o: main.cpp string.h ip.h port.h field.h input.h
	$(CXX) $(CXXFLAGS) -c main.cpp
ip.o: ip.cpp ip.h string.h field.h input.h
	$(CXX) $(CXXFLAGS) -c ip.cpp
port.o: port.cpp port.h string.h field.h input.h
	$(CXX) $(CXXFLAGS) -c port.cpp
field.o: field.cpp field.h ip.h port.h string.h input.h
	$(CXX) $(CXXFLAGS) -c field.cpp
string.o: string.cpp string.h input.h
	$(CXX) $(CXXFLAGS) -c string.cpp

#Clean
clean:
	rm -rf *.o firewall.exe libfirewall.so
