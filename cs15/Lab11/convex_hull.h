/*
 * convex_hull.h
 *
 * Course: EN47
 * Last modified: August 2, 2001
 *
 */


#include "en47_vis_txt.h"

my_point compute_convex_hull(patient A[], int num, patient CH[], int x_data, int y_data);
bool point_in_hull(patient CH[], int num, int big_x, patient test_point, int x_data, int y_data);
bool point_in_hull_2(patient CH[], int lo, int hi, patient test_point, int x_data, int y_data);

void draw_hull_and_points(patient hull[], patient hull_points[], int num_hull, int num_points, int x_data, int y_data, int col);