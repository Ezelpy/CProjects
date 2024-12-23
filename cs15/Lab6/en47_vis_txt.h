/*
 * Course: EN47
 * Last updated: July 11, 2001
 *
 */

#ifndef EN47_VIS_TXT_H 
#define EN47_VIS_TXT_H 

#define ERASE -1
#define DRAW 0
#define HIGHLIGHT 1

using namespace std;

void en47_display();			// open the window
void en47_display(int, int);		// open the window and specify size
void en47_close(); 			// close the window
void en47_clear(); 			// clear the window
void en47_draw_trapezoid(int, int, int, int);
void en47_draw_upper_histogram(int, int, int);
void en47_draw_lower_histogram(int, int, int);
void en47_draw_histogram(int, int, int);
void en47_draw_towers(int[3][21]);
void en47_wait();
void en47_mouse_wait();

#endif
