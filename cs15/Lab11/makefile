#
# makefile for convex hull with diabetes data
# 
# Course: EN 47 
# Last modified: November 26, 2023
#
# NOTE: this uses LEDA 6.1 so before running anything type "use leda61"
#

LEDALib = /usr/cots/leda-6.1
LFLAG = -L$(LEDALib) -lleda -lX11 -lm
INC = -I$(LEDALib)/incl

default: diabetes_txt diabetes_vis

diabetes_txt: tester.cpp en47_txt.o ch_sort_and_search.o convex_hull.o
	g++ tester.cpp convex_hull.o en47_txt.o ch_sort_and_search.o -o diabetes_txt 
	chmod 770 diabetes_txt

diabetes_vis: tester.cpp en47_vis.o ch_sort_and_search.o convex_hull.o
	g++ tester.cpp convex_hull.o en47_vis.o ch_sort_and_search.o -o diabetes_vis $(INC) $(LFLAG) 
	chmod 770 diabetes_vis

convex_hull.o: convex_hull.cpp convex_hull.h
	g++ -c convex_hull.cpp $(INC)
	chmod 660 convex_hull.o

ch_sort_and_search.o: ch_sort_and_search.cpp ch_sort_and_search.h
	g++ -c ch_sort_and_search.cpp $(INC)
	chmod 660 ch_sort_and_search.o

#en47_txt.o: en47_txt.cpp en47_vis_txt.h
#	g++ -c en47_txt.cpp $(INC)
#	chmod 660 en47_txt.o

#en47_vis.o: en47_vis.cpp en47_vis_txt.h
#	g++ -c en47_vis.cpp $(INC)
#	chmod 660 en47_vis.o

clean:
	rm -f *.o diabetes_txt diabetes_vis core a.out
