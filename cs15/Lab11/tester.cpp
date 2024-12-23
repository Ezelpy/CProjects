/*
 * tester.cpp
 *
 * Course: EN47
 *
 * NAME: Ezequiel Ramirez
 * DATE: 12/05/24
 *
 * This program will use 3 sets of diabetes data taken from a group of
 * 100 patients.  Each set of data is a diabetes indicator, but no 1 set
 * is 100% accurate.  Each patient also has been classified as being
 * in one of the following three categories: N - Normal, I - IGT (pre-
 * diabetic), or D - Type 2 Diabetic.  This program will calculate an
 * error statistic for each of the diabetic hulls which are derived
 * from the 3 possible pairings of the data sets.  The error statistic
 * will be equal to the percentage of IGT points that fall inside the
 * diabetic hull plus 2 times the percentage of normal points that fall
 * within the diabetic hull.
 */

#include <iostream>
#include <cstring>
#include "en47_vis_txt.h"
#include "ch_sort_and_search.h"
#include "convex_hull.h"

using namespace std;

int main () {

    patient normal[100],		// array of normal patients
	    IGT[100],			// array of IGT patients
	    diabetic[100],		// array of diabetic patients
	    normal_hull[100],		// array of normal hull
	    IGT_hull[100],		// array of IGT hull
	    diabetic_hull[100],		// array of diabetic hull
	    temp_patient,
		spare[100];

    int i, 				// loop control variable
	x_data,				// the index (0-2) of the data that is
					  // currently being plotted on the x-axis
	y_data,				// the index (0-2) of the data that is
					  // currently being plotted on the y-axis
	num_normal = 0,			// number of normal patients
	num_IGT = 0,			// number of IGT patients
	num_diabetic = 0,		// number of diabetic patients

	normal_stats[2],		// percentage of IGT patients in normal
					  // hull [0], and percentage of diabetic
					  // patients in normal hull [1]
	IGT_stats[2],			// percentage of normal patients in IGT
					  // hull [0], and percentage of diabetic
					  // patients in IGT hull [1]
	diabetic_stats[2],		// percentage of normal patients in diabetic
					  // hull [0], and percentage of IGT
					  // patients in diabetic hull [1]
	diabetic_error[3] = {0,0,0};	// this will be the indicator of the best
					  // pair of tests, it will be equal to
					  // the percentage of IGT points that
					  // fall inside the diabetic hull plus
					  // 2 times the percentage of normal
					  // points that fall within the hull

    my_point normal_hull_info,		// info about normal hull
					  // x: index of point with largest x-value
					  // y: number of points in hull
					  // ID: unused
	     IGT_hull_info,		// info about IGT hull
	     diabetic_hull_info;	// info about diabetic hull


    char classification;			// patient classification (N, I, or D)

    data_set data_sets[3];		// array of the data set names
    strcpy(data_sets[0].name, "FPG\0     ");
    strcpy(data_sets[1].name, "HbA1c\0   ");
    strcpy(data_sets[2].name, "FSM\0     ");
	
    //Display instructions
    cout << "\nThis program will use 3 sets of diabetes data taken from a group of\n"
	 << "100 patients.  Each set of data is a diabetes indicator, but no 1 set\n"
	 << "is 100% accurate.  Each patient also has been classified as being\n"
	 << "in one of the following three categories: N - Normal, I - IGT (pre-\n"
	 << "diabetic), or D - Type 2 Diabetic.  This program will calculate an\n"
	 << "error statistic for each of the diabetic hulls which are derived \n"
	 << "from the 3 possible pairings of the data sets.  The error statistic\n"
	 << "will be equal to the percentage of IGT points that fall inside the\n"
	 << "diabetic hull plus 2 times the percentage of normal points that fall\n"
	 << "within the diabetic hull.\n\n"
	 << "Enter up to 100 patients by first entering an ID number followed\n"
	 << "by Test 1, then Test 2, then Test 3, and then that patient's class-\n"
	 << "ification (N, I, or D).  Example - 23 245 789 323 D (ID T1 T2 T3 C).\n"
	 << "Enter an ID number of -1 after you have entered all of the patients.\n\n"
	 << "Normal points are drawn in green.\n"
	 << "IGT points are drawn in blue.\n"
	 << "Diabetic points are drawn in red.\n\n";

    // read in data until an ID of -1 or until 100 points are entered
    i = 0;
    cin >> temp_patient.ID;
    while ((i < 100) && (temp_patient.ID != -1)) {
        // read in the three test scores and the classification for temp_patient.ID
	cin >> temp_patient.data[0] 
	    >> temp_patient.data[1] 
	    >> temp_patient.data[2]
	    >> classification;

        // copy the temp_patient into ONE of the normal[], IGT[], or diabetic[] arrays 
        // and then increment the number of elements in that array.
		
		// Normal patients array
		if (classification == 'N')
		{
			normal[num_normal] = temp_patient;
			num_normal++;
		}

		// IGT patients array
		else if (classification == 'I')
		{
			IGT[num_IGT] = temp_patient;
			num_IGT++;
		}

		// Diabetic patients array
		else if (classification == 'D')
		{
			diabetic[num_diabetic] = temp_patient;
			num_diabetic++;
		}

        // increment the number of patients
	i++;

        // get a new temp_patient.ID
	cin >> temp_patient.ID;
    }

    // display drawing window
    // all the coordinates are between 0 and 1000
    en47_display(-100, 1100, -100, 1100);

    // draw x and y axes
    en47_draw_segment(0, -100, 0, 1100);
    en47_draw_segment(-100, 0, 1100, 0);

    // first use data set 0 as x and data set 1 as y
    // then use data set 1 as x and data set 2 as y
    // then use data set 2 as x and data set 0 as y

    for (int which_data = 0; which_data < 3; which_data++) 
	{

		x_data = which_data;
		y_data = (which_data + 1) % 3;

		// draw all of the points: normal-> green, IGT -> blue, diabetic -> red.
		// and wait for a mouse click

		// Normal points
		for (int j = 0; j < num_normal; j++)
		{
			en47_draw_point(normal[j].data[x_data], normal[j].data[y_data], GREEN);
		}

		// IGT points
		for (int j = 0; j < num_IGT; j++)
		{
			en47_draw_point(IGT[j].data[x_data], IGT[j].data[y_data], BLUE);
		}

		// Diabetic points
		for (int j = 0; j < num_normal; j++)
		{
			en47_draw_point(diabetic[j].data[x_data], diabetic[j].data[y_data], RED);
		}
		en47_mouse_wait();

		// clear the screen, and then draw the x- and y-axes again.
		en47_clear();

	    // draw x and y axes
		en47_draw_segment(0, -100, 0, 1100);
		en47_draw_segment(-100, 0, 1100, 0);

	// sort the arrays of points by x_data using a modified version
	// of merge sort and using <classification>_hull as a spare array
	ch_merge_sort(normal, 0, num_normal - 1, spare, x_data, y_data);
	ch_merge_sort(IGT, 0, num_IGT - 1, spare, x_data, y_data);
	ch_merge_sort(diabetic, 0, num_diabetic - 1, spare, x_data, y_data);

	// *** FIND AND DRAW ALL HULLS **************************

	// find and draw the convex hull of the normal patients
	normal_hull_info = compute_convex_hull(normal, num_normal, normal_hull, x_data, y_data);

	// draw all the normal points
	for (int j = 0; j < num_normal; j++)
	{
		en47_draw_point(normal[j].data[x_data], normal[j].data[y_data], GREEN);
	}
	en47_mouse_wait();

	// mouse wait, then clear the screen and redraw the x- and y-axes
	en47_clear();
	
	// draw x and y axes
	en47_draw_segment(0, -100, 0, 1100);
	en47_draw_segment(-100, 0, 1100, 0);

	// find and draw the convex hull of the IGT patients
	IGT_hull_info = compute_convex_hull(IGT, num_IGT, IGT_hull, x_data, y_data);

	// draw all the IGT points
	for (int j = 0; j < num_IGT; j++)
	{
		en47_draw_point(IGT[j].data[x_data], IGT[j].data[y_data], BLUE);
	}

    	// mouse wait, then clear the screen and redraw the x- and y-axes
	en47_mouse_wait();
	en47_clear();

		// draw x and y axes
	en47_draw_segment(0, -100, 0, 1100);
	en47_draw_segment(-100, 0, 1100, 0);

	// find and draw the convex hull of the diabetic patients 
	diabetic_hull_info = compute_convex_hull(diabetic, num_diabetic, diabetic_hull, x_data, y_data);

	// draw all the diabetic points
	for (int j = 0; j < num_diabetic; j++)
	{
		en47_draw_point(diabetic[j].data[x_data], diabetic[j].data[y_data], RED);
	}

    	// mouse wait, then clear the screen and redraw the x- and y-axes
	en47_mouse_wait();
	en47_clear();

		// draw x and y axes
	en47_draw_segment(0, -100, 0, 1100);
	en47_draw_segment(-100, 0, 1100, 0);

	// *** TEST FOR OTHER POINTS IN HULLS *******************

	// reset stats counters
	for (i = 0; i < 2; i++) {
	    normal_stats[i] = 0;
	    IGT_stats[i] = 0;
	    diabetic_stats[i] = 0;
	}

	// redraw the normal hull and all the normal points in green
	draw_hull_and_points(normal_hull, normal, normal_hull_info.y, num_normal, x_data, y_data, GREEN);

	// now test IGT patients to see if they are inside convex hull of the normal patients
	for (i = 0; i < num_IGT; i++) {
	    // if IGT[i] is inside the normal_hull,
	    //       normal_stats[0]++
	    //       en47_draw_point() in blue
		bool point_found = point_in_hull(normal_hull, normal_hull_info.y, normal_hull_info.x, IGT[i], x_data, y_data);

		if (point_found)
		{
			normal_stats[0]++;
			en47_draw_point(IGT[i].data[x_data], IGT[i].data[y_data], BLUE);
		}

	    // } else 
	    //      en47_draw_open_point() in blue.
		else en47_draw_open_point(IGT[i].data[x_data], IGT[i].data[y_data], BLUE);
	}

        // now test the diabetic patients to see if they are inside the normal convex hull
	for (i = 0; i < num_diabetic; i++) {
            // if diabetic[i] is inside the normal_hull,
            //      normal_stats[1]++
            //      en47_draw_point() in red
		bool point_found = point_in_hull(normal_hull, normal_hull_info.y, normal_hull_info.x, diabetic[i], x_data, y_data);

		if (point_found)
		{
			normal_stats[1]++;
			en47_draw_point(diabetic[i].data[x_data], diabetic[i].data[y_data], RED);
		}

	    //} else
            //	     en47_draw_open_point() in red  
		else en47_draw_open_point(diabetic[i].data[x_data], diabetic[i].data[y_data], RED);
	}


        // mouse wait, then clear the screen and redraw the x- and y-axes
		en47_mouse_wait();
		en47_clear();

			// draw x and y axes
		en47_draw_segment(0, -100, 0, 1100);
		en47_draw_segment(-100, 0, 1100, 0);

	// redraw the IGT hull and all the IGT points in blue
	draw_hull_and_points(IGT_hull, IGT, IGT_hull_info.y, num_IGT, x_data, y_data, BLUE);

	// now test patients with normal classification for containment 
	// within the IGT hull
	for (i = 0; i < num_normal; i++) {
	    //if normal[i] is inside the IGT_hull,
	    //       IGT_stats[0]++;
            //       en47_draw_point() in green

		bool point_found = point_in_hull(IGT_hull, IGT_hull_info.y, IGT_hull_info.x, normal[i], x_data, y_data);

		if (point_found)
		{
			IGT_stats[0]++;
			en47_draw_point(normal[i].data[x_data], normal[i].data[y_data], GREEN);
		}

	    //} else
            //	      en47_draw_open_point() in green
		else en47_draw_open_point(normal[i].data[x_data], normal[i].data[y_data], GREEN);
		
	}

        // now test diabetic patients for conatainment in the IGT hull
	for (i = 0; i < num_diabetic; i++) {
	    // if diabetic[i] is in the IGT hull 
            //        IGT_stats[1]++;
            //	      en47_draw_point() in red

		bool point_found = point_in_hull(IGT_hull, IGT_hull_info.y, IGT_hull_info.x, diabetic[i], x_data, y_data);

		if (point_found)
		{
			IGT_stats[1]++;
			en47_draw_point(diabetic[i].data[x_data], diabetic[i].data[y_data], RED);
		}

	    //} else
	    //	en47_draw_open_point() in red
		else en47_draw_open_point(diabetic[i].data[x_data], diabetic[i].data[y_data], RED);
	}

        // mouse wait, then clear the screen and redraw the x- and y-axes
		en47_mouse_wait();
		en47_clear();

			// draw x and y axes
		en47_draw_segment(0, -100, 0, 1100);
		en47_draw_segment(-100, 0, 1100, 0);

	// redraw the diabetic hull and all the diabetic points
	draw_hull_and_points(diabetic_hull, diabetic, diabetic_hull_info.y, num_diabetic, x_data, y_data, RED);

	// now test patients with non-diabetic classifications for containment 
	// within the diabetic hull
	for (i = 0; i < num_IGT; i++) {
	     // if IGT[i] is inside the diabetic hull
	     //       diabetic_stats[1]++;
             //	      en47_draw_point() in blue

		bool point_found = point_in_hull(diabetic_hull, diabetic_hull_info.y, diabetic_hull_info.x, IGT[i], x_data, y_data);

		if (point_found)
		{
			diabetic_stats[1]++;
			en47_draw_point(IGT[i].data[x_data], IGT[i].data[y_data], BLUE);
		}

	     //  } else
	     //	        en47_draw_open_point() in blue
		else en47_draw_open_point(IGT[i].data[x_data], IGT[i].data[y_data], BLUE);
	}

	for (i = 0; i < num_normal; i++) {
	     // if normal[i] is inside the diabetic hull
	     //	        diabetic_stats[0]++;
             //		en47_draw_point() in green

		bool point_found = point_in_hull(diabetic_hull, diabetic_hull_info.y, diabetic_hull_info.x, normal[i], x_data, y_data);

		if (point_found)
		{
			diabetic_stats[0]++;
			en47_draw_point(normal[i].data[x_data], normal[i].data[y_data], GREEN);
		}

	    // } else
            //		en47_draw_open_point() in green
		else en47_draw_open_point(normal[i].data[x_data], normal[i].data[y_data], GREEN);
	}

        // mouse wait, then clear the screen and redraw the x- and y-axes
		en47_mouse_wait();
		en47_clear();

			// draw x and y axes
		en47_draw_segment(0, -100, 0, 1100);
		en47_draw_segment(-100, 0, 1100, 0);


	// *** OUTPUT STATISTICS ********************************
	// LOOK BACK at the top of main() where the variables for statistics were declared
	// See how they are defined and what we want to keep and report.
	// NOTE: 100% of the normal points will be in the normal convex hull, so what we need
	// to test is what percent of the IGT points are also inside the normal hull
	// as well as what person of the diabetic points are inside the normal hull.
	// In the same way,100% of the IGT points are inside the IGT hull, and 100% of the 
	// diabetic points are inside the diabetic hull.  We want to know what percentage of
	// the *other* points are inside the *wrong* convex hull.


	cout << "***************************************************************\n\n"
	     << "The x-coordinates are scaled data from the " 
	     << data_sets[x_data].name << " test.\n"
	     << "The y-coordinates are scaled data from the " 
	     << data_sets[y_data].name << " test.\n\n"
	     << "\t\tNormal\tIGT\tDiabetic\n";

	// calculate error percentages, and output normal_stats
	// normal_stats[0] is currently the number of IGT points inside the normal hull.
	// BUT we want the percentage of IGT points inside the normal hull.
	// So we need to divide by the total number of IGT points and then multiple by 100.
	int IGT_normal_hull = (normal_stats[0]*100)/num_IGT;

	// normal_stats[1] is currently the number of diabetic points inside the normal hull.
	// BUT we want the percentage of diabetic points inside the normal hull.
	// So we need to divide by the total number of diabetic points and then multiple by 100.
	int diabetic_normal_hull = (normal_stats[1]*100)/num_diabetic;

        // Output the stats for the Normal Hull
        //     The row needs to be labelled "Normal Hull\t"
        //     100% is the percentage of normal points inside
        //     normal_stats[0] will be the percentage of IGT points inside
        //     normal_state[1] will be the percentage of diabetic points inside
        //     AND we need to end with a newline
	cout << "Normal Hull\t" << "@100%\t@" << IGT_normal_hull  << "%\t@" << diabetic_normal_hull  << "%" << endl;

	// calculate error percentages, and output IGT_stats
	int normal_IGT_hull = (IGT_stats[0]*100)/num_normal;
	int diabetic_IGT_hull = (IGT_stats[1]*100)/num_diabetic;
	cout << "IGT Hull\t" << "@" << normal_IGT_hull << "%\t@100%\t@" << diabetic_IGT_hull  << "%" << endl;

	// calculate error percentages, and output diabetic_stats
	int normal_diabetic_hull = (diabetic_stats[0]*100)/num_normal;
	int IGT_diabetic_hull = (diabetic_stats[1]*100)/num_IGT;
	cout << "Diabetic Hull\t" << "@" << normal_diabetic_hull  << "%\t@" <<  IGT_diabetic_hull << "%\t@100%" << endl;

	// calculate diabetic_error[x_data] according to the rule given when we declared local data
	diabetic_error[x_data] = normal_diabetic_hull * 2 + IGT_diabetic_hull;

        // output diabetic_error[x_data]
	cout << "Error statistic:\t@" << diabetic_error[x_data] << "\n\n";


	// *** REDRAW *******************************************

	// redraw all the points and all the hulls
	draw_hull_and_points(diabetic_hull, diabetic, diabetic_hull_info.y, num_diabetic, x_data, y_data, RED);
	draw_hull_and_points(IGT_hull, IGT, IGT_hull_info.y, num_IGT, x_data, y_data, BLUE);
	draw_hull_and_points(normal_hull, normal, normal_hull_info.y, num_normal, x_data, y_data, GREEN);

        // mouse wait, then clear the screen and redraw the x- and y-axes
		en47_mouse_wait();
		en47_clear();

			// draw x and y axes
		en47_draw_segment(0, -100, 0, 1100);
		en47_draw_segment(-100, 0, 1100, 0);
    }

    // FINAL DECISION OF WHICH TWO TESTS ARE BEST
    if ((diabetic_error[0] < diabetic_error[1]) && (diabetic_error[0] < diabetic_error[2]))
	cout << "The combination of the " << data_sets[0].name << " test and the "
	     << data_sets[1].name << " test (#0 and #1) is the best measure.\n\n";

    else if (diabetic_error[1] < diabetic_error[2])
	cout << "The combination of the " << data_sets[1].name << " test and the "
	     << data_sets[2].name << " test (#1 and #2) is the best measure.\n\n";

    else
	cout << "The combination of the " << data_sets[2].name << " test and the "
	     << data_sets[0].name << " test (#2 and #0) is the best measure.\n\n";
}