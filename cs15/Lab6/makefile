#
# makefile for hanoi.cpp
# 
# Course: EN 47 
# Date: Summer 2019 in prepartion for Spring 2020
#
# NOTE: this uses LEDA 6.1 so before running anything type "use leda61"

LEDALib = /usr/cots/leda-6.1
LFLAG = -L$(LEDALib) -lleda -lX11 -lm
INC = -I$(LEDALib)/incl

default: hanoi_txt hanoi_vis

hanoi_txt: en47_txt.o hanoi.cpp
	g++ hanoi.cpp en47_txt.o -o hanoi_txt 
	chmod 770 hanoi_txt

hanoi_vis: en47_vis.o hanoi.cpp
	g++ hanoi.cpp en47_vis.o -o hanoi_vis $(INC) $(LFLAG) 
	chmod 770 hanoi_vis

#en47_txt.o: en47_txt.cpp en47_vis_txt.h
	#g++ -c en47_txt.cpp $(INC)
	#chmod 660 en47_txt.o
#
#en47_vis.o: en47_vis.cpp en47_vis_txt.h
	#g++ -c en47_vis.cpp $(INC)
	#chmod 660 en47_vis.o

clean:
	rm -f en47_txt.o en47_vis.o hanoi_txt hanoi_vis core a.out
