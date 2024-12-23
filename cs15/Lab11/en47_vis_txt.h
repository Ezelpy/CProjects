/*
 * en47_vis_txt.h
 *
 * Course: EN47
 * Last updated: July 27, 2001
 *
 */

#ifndef EN47_VIS_TXT_H 
#define EN47_VIS_TXT_H 

#define WHITE 	0
#define BLACK	1
#define RED	2
#define GREEN	3
#define BLUE	4
#define YELLOW	5
#define VIOLET	6
#define ORANGE	7

using namespace std;

struct my_point {
    int x, y;
    int ID;
};

struct patient {
    int ID;
    int data[3];
};

struct data_set {
    char name[10];
};

// open the window
void en47_display();

// open the window and specify size
void en47_display(int width, int height);

// open the window and specify:
// minx, maxx, miny, maxy
void en47_display(int minx, int maxx, int miny, int maxy);

// close the window
void en47_close();

// clear the window
void en47_clear();

// draw a point
void en47_draw_point(int x, int y);
void en47_draw_point(int x, int y, int col);
void en47_draw_open_point(int x, int y);
void en47_draw_open_point(int x, int y, int col);

// draw a line segment
void en47_draw_segment(int x1, int y1, int x2, int y2);	
void en47_draw_segment(int x1, int y1, int x2, int y2, int col);

// draw the polygon with num points specified by the points in poly
void en47_draw_poly(my_point poly[], int num);
void en47_draw_poly(my_point poly[], int num, int col);

// draw the polygon with num points specified by the patients in poly
// use x_data and y_data to determine which fields of the data array in
// poly to use
void en47_draw_poly(patient poly[], int num, int x_data, int y_data);
void en47_draw_poly(patient poly[], int num, int x_data, int y_data, int col);

void en47_draw_trapezoid(int, int, int, int);
void en47_draw_upper_histogram(int, int, int);
void en47_draw_lower_histogram(int, int, int);
void en47_draw_histogram(int, int, int);
void en47_draw_towers(int[3][21]);
void en47_wait();
void en47_mouse_wait();
void en47_wait(int milliseconds);
#endif
