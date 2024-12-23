/*
  Put here a header with you name, the date, the filename,
  and a description of what is here.
  Remember to comment all your files
  Name: Ezequiel Ramirez
  Date: 11/08/2024
  Filename: convex_hull.cpp
  Description: Calculation of convex hull
 */

#include "convex_hull.h"
#include "ch_sort_and_search.h"
#include <iostream>

using namespace std;

//You are giving this function at the bottom
bool right(int ax, int ay, int bx, int by, int cx, int cy);


/*** Function Definitions ***********************************************/

my_point compute_convex_hull(patient A[], int num, patient CH[], int x_data, int y_data)
{
    int i,                //counting the number of convex hull points
        j,                //counting the number of points in A[] that we have processed
        top,              //the number of convex hull points on the top
        tot;              //the total number of convex hull points
    my_point ret;         //struct that will be returned

    //we currently have exactly 1 point that we are *sure* is on the CH.
    CH[0]=A[0];           //the point of smallest x-coord is definitely on the CH 
    i= 1;                 //we only know for sure that we have 1 point on the CH
    j = 1;

    //we always need to have a second candidate point in order to begin testing
    //let's test whether this point is also on the CH.
    CH[1] = A[1]; i++; j++;

    en47_draw_segment(CH[0].data[x_data], CH[0].data[y_data], CH[1].data[x_data], CH[1].data[y_data]);
    //now for every other point of the input set A[], from 2 to num-1, 
        //as long as i>1, check whether the new point makes a right turn with the last segment that was drawn. 
        //if not, redraw the BLUE edge in ORANGE, wait, remove the last candidate CH point and try again.
    for (j; j < num; j++)
    {   
        // Draw segment of the candidate CH point     
        en47_draw_segment(CH[i-1].data[x_data], CH[i-1].data[y_data], A[j].data[x_data], A[j].data[y_data]); 
        //en47_wait(200);

        // Loop to check for right turns
        // Keeps looping until a right turn is found or i == 1
        while (i > 1 && !right(CH[i-2].data[x_data], CH[i-2].data[y_data], CH[i-1].data[x_data], CH[i-1].data[y_data], A[j].data[x_data], A[j].data[y_data]))
        {
            // Draw incorrect segments in orange
            // Last segment
            en47_draw_segment(CH[i-1].data[x_data], CH[i-1].data[y_data], A[j].data[x_data], A[j].data[y_data], WHITE); 

            // Second to last segment
            en47_draw_segment(CH[i-2].data[x_data], CH[i-2].data[y_data], CH[i-1].data[x_data], CH[i-1].data[y_data], WHITE); 
            en47_wait(25);

            // Decrease i by one to "eliminate" the incorrect candidate from the convex hull
            i--; 
        }

        //FINALLY either i==1 so you need to add a new point, OR we have a right turn.
        //Either way, increment i and add the point A[j] to the convex hull, wait, and
        //then draw the next candidate edge in BLUE:
        en47_draw_segment(CH[i-1].data[x_data], CH[i-1].data[y_data], A[j].data[x_data], A[j].data[y_data]);
        CH[i] = A[j]; i++;
    }
   //now that j== num-1, we have gone through all of the points once. 
   //we know that A[num-1] has the largest x-coordinate so it went on the CH.
   //And we have finished calculating the top part of the CH.  

   top = i;        
   
   //Now we shift to the bottom part of the convex hull. 
   //The point A[num-1] is on both the top part and the bottom part of CH.
   //SO we have one point for sure!  In the same way as we did for the top part,
   //we need to add a second candidate point and draw the segment:
   CH[i] = A[j-2];
   
   en47_draw_segment(CH[i-1].data[x_data], CH[i-1].data[y_data], A[j-2].data[x_data], A[j-2].data[y_data]);
   i++;
   //now we are working our way back from right-to-left, so
   //for every other point of the input set A[], from num-3 down to 0
       //as long as we have stayed on the bottom of the convex hull, in other words we are at
       //least as far around as top, check whether the next point makes a right turn with the last segment drawn.
       //if not, redraw the BLUE edge in ORANGE, wait, remove the last candidate CH point, and try again.
    for (j = num - 3; j >= 0; j--)
    {
        // Draw segment of the candidate CH point     
        en47_draw_segment(CH[i-1].data[x_data], CH[i-1].data[y_data], A[j].data[x_data], A[j].data[y_data]);

        // Loop to check for right turns
        // Keeps looping until a right turn is found or i == top
        while (i > top && !right(CH[i-2].data[x_data], CH[i-2].data[y_data], CH[i-1].data[x_data], CH[i-1].data[y_data], A[j].data[x_data], A[j].data[y_data]))
        {
            // Draw incorrect segments in orange
            // Last segment
            en47_draw_segment(CH[i-1].data[x_data], CH[i-1].data[y_data], A[j].data[x_data], A[j].data[y_data], WHITE);

            // Second to last segment
            en47_draw_segment(CH[i-2].data[x_data], CH[i-2].data[y_data], CH[i-1].data[x_data], CH[i-1].data[y_data], WHITE);
            en47_wait(25);

            // Decrease i by one to "eliminate" the incorrect candidate from the convex hull
            i--; 
        }

       //FINALLY either i==top so you need to add a new point, OR we have a right turn.
       //Either way, increment i and add the point A[j] to the convex hull, wait, and
       //then draw the next candidate edge in BLUE:
       en47_draw_segment(CH[i-1].data[x_data], CH[i-1].data[y_data], A[j].data[x_data], A[j].data[y_data]); 
       CH[i] = A[j]; i++;
    }



   //now that j==0, we have gone through all of the points a second time, so we are done..  
   tot = i;
 
   //Now redraw all of the points of A[] in ORANGE, and the points of CH[] in BLUE.
   //And finally redraw all of the CH edges in BLUE.

   // Loop to draw all points in A[] in ORANGE
   //for (int k=0; k < num; k++)
   //{
   //     en47_draw_point(A[k].data[x_data],  A[k].data[y_data], ORANGE);
   //}

   // Loop to redraw all points in CH[] in BLUE and all of the CH segments in BLUE
   for (int k = 0; k < i-1; k++)
   {
        // Points
        //en47_draw_point(CH[k].data[x_data],  CH[k].data[y_data], BLUE);

        //Segments
        en47_draw_segment(CH[k].data[x_data],  CH[k].data[y_data], CH[k+1].data[x_data],  CH[k+1].data[y_data]);
   }


   //return the number of Convex Hull vertices in the upper and lower part
   ret.x = top;
   ret.y = tot - 1;
   return ret;
}

bool right(int ax, int ay, int bx, int by, int cx, int cy)
{
   int DX1, DX2;
   int DY1, DY2;

   DY1 = by - ay;
   DY2 = cy - by;
   DX1 = bx - ax; 
   DX2 = cx - bx;
   return (DY1 * DX2 > DY2 * DX1); 
}

bool point_in_hull(patient CH[], int num, int big_x, patient test_point, int x_data, int y_data)
{
    if (test_point.data[x_data] > CH[0].data[x_data] && test_point.data[x_data] < CH[big_x-1].data[x_data])
    {
        // Search for upper and lower coordinates of the highest x-value that is lower than testpoint.x
        int upper_coordinate = ch_binary_search(CH, 0, big_x-1, test_point, false, x_data, y_data);
        int lower_coordinate = ch_binary_search(CH, big_x-1, num, test_point, true, x_data, y_data);

        // Testing for right turns
        bool upper_check = right(CH[upper_coordinate].data[x_data], CH[upper_coordinate].data[y_data], CH[upper_coordinate+1].data[x_data], CH[upper_coordinate+1].data[y_data], test_point.data[x_data], test_point.data[y_data]);
        bool lower_check = right(CH[lower_coordinate].data[x_data], CH[lower_coordinate].data[y_data], CH[lower_coordinate+1].data[x_data], CH[lower_coordinate+1].data[y_data], test_point.data[x_data], test_point.data[y_data]);
        
        // If both right turns are true, then the point is in the convex hull and return true
        if (upper_check && lower_check) return true;

        // If not, return false as the point is not in the convex hull
        else return false;
    }
    else return false;
}

/* 
    This function draws the hull and the points inside the hull for a given type
    
    INPUT: a patient-type array of the points that conform the convex hull of the diabetic type (patient hull[]),
    a patient-type array of the points of the diabetic type (patient hull_points[]), 
    the total number of points that conform the convex hull (int num_hull),
    the total number of points in the hull_points[] array (int num_points),
    the x_data (int x_data), y_data (int y_data), and the desired color for the visual as an integer (int col).
    
    It can accept any as input: diabetic, IGT or normal.

    OUTPUT: no output, only visuals of the convex hull and convex hull points.

    Custom function Eze
*/
void draw_hull_and_points(patient hull[], patient hull_points[], int num_hull, int num_points, int x_data, int y_data, int col)
{
	for (int j = 0; j < num_hull; j++)
    {
        //Segments
    	en47_draw_segment(hull[j].data[x_data], hull[j].data[y_data], hull[j+1].data[x_data], hull[j+1].data[y_data], col);
    }

	for (int j = 0; j < num_points; j++)
	{
		 // Points
        en47_draw_point(hull_points[j].data[x_data], hull_points[j].data[y_data], col);
	}
}
