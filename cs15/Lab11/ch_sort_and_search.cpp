#include <iostream>
#include <string>
#include "ch_sort_and_search.h"
#include "en47_vis_txt.h"

using namespace std;

// NAME: Ezequiel Ramirez
// DATE: 10/04/24
// CLASS: EN 47

/***************************************************************************/
void sort(patient A[], int lo, int hi, patient spare[], int x_data, int y_data)
{
      //PICK ONE OF THESE TWO AND REMOVE THE COMMENTS!!!
//    bubble_sort(A,lo,hi);
//    insertion_sort(A,lo,hi);

       // (un)comment this lines to use mergesort
       ch_merge_sort(A, lo, hi, spare, x_data, y_data);
}

void bubble_sort(int values[],int lo, int hi)
{
    /*Works through the entire array from lo to hi, comparing 
      the values in pairs and swapping positions, if necessary, 
      so that the maximum element ends up in the position 
      values[hi].  Repeats so the next largest is in values[hi-1]
      and so forth until the smallest element is in values[lo] */
      
      // Main loop to iterate through each item
       for (int i = hi; i > 0; i--)
       {
	      // Loop to go through the array and compare values
              for (int j = 0; j < i; j++)
              {
                     en47_mouse_wait();

                     // Highlight the first item
                     if (j == 0)
                     {
                            //en47_draw_histogram(lo, values[lo], ERASE);
                            //en47_draw_histogram(lo, values[lo], HIGHLIGHT);    
                            en47_mouse_wait();
                     } 
		     
		     // Swap values if the following value is smaller than the current value
                     if (values[lo+j] > values[lo+j+1])
                     {
			    // Erase both items to be able to swap them afterwards
                            //en47_draw_histogram(lo+j, values[lo+j], ERASE);
                            //en47_draw_histogram(lo+j+1, values[lo+j+1], ERASE);

			    // Swap both items
                            int temp;
                            temp = values[lo+j];
                            values[lo+j] = values[lo+j+1];
                            values[lo+j+1] = temp;

			    // Swap value in the histogram and highlight the new current value
                            //en47_draw_histogram(lo+j, values[lo+j], DRAW);
                            //en47_draw_histogram(lo+j+1, values[lo+j+1], HIGHLIGHT);
                     }
			
		     // If the current item is at the end of the second loop, erase the highlight
                     else if (lo+j == i)
                     {
                            //en47_draw_histogram(lo+j, values[lo+j], ERASE);  
                            //en47_draw_histogram(lo+j, values[lo+j], DRAW);
                            //en47_draw_histogram(lo+j, values[lo], ERASE);  
                            //en47_draw_histogram(lo+j, values[lo], DRAW);                            
                     }

		     // Highlight new current value and erase former highlight
                     else
                     {
                            //en47_draw_histogram(lo+j+1, values[lo+j+1], ERASE);  
                            //en47_draw_histogram(lo+j+1, values[lo+j+1], HIGHLIGHT);
                            //en47_draw_histogram(lo+j, values[lo+j], ERASE);  
                            //en47_draw_histogram(lo+j, values[lo+j], DRAW);
                     }
              }            
       }
}

void insertion_sort(int values[], int lo, int hi)
{
    /*Assumes that the first integer values[lo] is in sorted order.
      Compares the second integer to the first and swaps if necessary.
      Then considers the third integer.  Makes swaps as needed until
      it is in correct position.  Continues.  Assumes that the first
      i integers are in sorted order.  Compares the i+1 st integer against
      the ith and so forth, swapping as necessary, until it is also in
      the correct position 
      */
       
       // Main loop to iteate through each value
       for (int i = lo; i <= hi; i++)
       {
	      // Marker to swap values until in correct position
              int j = 0; 
              
              // For the first item, just highlight the current item and then pass to second one
              if (i == lo)
              {
                     //en47_draw_histogram(i, values[i], HIGHLIGHT);
                     en47_mouse_wait();
                     continue;  
              }

              // Loop to swap until in correct spot
              while (i-1-j >= lo && values[i-1-j] > values[i-j])
              {
                     // Erase both items to be able to swap them afterwards

                     // Swap items
                     int temp;
                     temp = values[i-j];
                     values[i-j] = values[i-1-j];
                     values[i-1-j] = temp;

                     // Add one to the swap marker
                     j++;     
              }
              
              // Erase highlight
	       //en47_draw_histogram(i-j, values[i-j], ERASE);

              // When value is greater, erase highlight
              if (values[i-j] > values[i-j-1])
              {
                     //en47_draw_histogram(i-j, values[i-j], ERASE);
                     //en47_draw_histogram(i-j, values[i-j], DRAW);                  
              }
       }

}

	
/*****************************************************************/

int search(patient A[], int lo, int hi, patient query, bool reverse, int x_data, int y_data)
{
       //PICK ONE OF THESE TWO AND REMOVE THE COMMENTS!!!!
//     return (sequential_search(A,lo,hi,query));
     return (ch_binary_search(A,lo,hi,query, reverse, x_data, y_data));
       return (1);  //remove this line when one of the other functions is eavailable!!
}

int sequential_search(int values[], int lo, int hi, int query)
{
	/*
       Walks through the array, one value at a time, checking for
          the query element 
       If the value was found, this function returns the value's index.
       If the value was NOT found, this function returns -1.
       */

       // Searching variable
       int search_index = 1;

       // Draw all items for each search
       for (int i = lo; i <= hi; i++)
       {
            //en47_draw_histogram(i, values[i], DRAW);  
       }

       // Searching loop, iterates through each item from first to last
       for (int i = lo; i <= hi; i++)
       {
              // For the first item, highlight
              //if (i == lo) en47_draw_histogram(i, values[i], HIGHLIGHT);

              // For all the others, erase anterior highlight and then highligh current item
              //else
              //{
                     //en47_draw_histogram(i-1, values[i-1], ERASE);
                     //en47_draw_histogram(i-1, values[i-1], DRAW);
                     //en47_draw_histogram(i, values[i], HIGHLIGHT);
              //}

              // If the current item is the same as the query, highlight in another color and return index
              if (values[i] == query)
              {
                     //en47_draw_histogram(i, values[i], ERASE);
                     //en47_draw_histogram(i, values[i], 2*HIGHLIGHT);
                     en47_mouse_wait();
                     break;
              }

              // If the value is greater than the query, erase highlight
              else if (values[i] > query)
              {
                   //en47_draw_histogram(i, values[i], ERASE);
                   //en47_draw_histogram(i, values[i], DRAW);
              }
              en47_mouse_wait();
              search_index++;
       }
       // If the item was found, return the index
       if (values[search_index] == query) return search_index;

       // If the value was not found, return -1
       else return (-1); 

}

int ch_binary_search(patient values[], int lo, int hi, patient query, bool reverse, int x_data, int y_data)
{
	/*
       First compares the query element against the middle (median)
       value.   Then compares against either the 1/4 or the 3/4
       value, as appropriate. 
       
       Output: 
       If the value was found, this function returns the value's index.
       If the value was NOT found, this function returns -1.
       */
       
       // Local variables to record the index and to get the median
       int median = (lo + hi)/2;
       int i = 0;

       // Main searching loop
       while (lo <= hi)
       {
              if (query.data[x_data] == values[median].data[x_data])
              {
                     return median;       
              }

              // If computing the lower convex hull
              if (reverse)
              {
                     // If the query is smaller than the median
                     if (query.data[x_data] < values[median].data[x_data])
                     {
                            // Update hi variable to search from one less the median to lo
                            lo = median + 1;
                     }

                     // If the query is greater than the median
                     else
                     {
                            //Update lo variable to search from one more than the median and to hi
                            hi = median - 1;
                     }                   
              }

              // If computing top part of convex hull
              else
              {
                     // If the query is smaller than the median
                     if (query.data[x_data] < values[median].data[x_data])
                     {
                            // Update hi variable to search from one less the median to lo
                            hi = median - 1;
                     }

                     // If the query is greater than the median
                     else
                     {
                            //Update lo variable to search from one more than the median and to hi
                            lo = median + 1;
                     }
              }

              // In any case, update the median
              median = (lo + hi)/2;
       }

       // In case the value was found in the bottom part of the convex hull, return its index
       return median;
}

void ch_merge_sort(patient values[], int lo, int hi, patient spare[], int x_data, int y_data)
{
       if (hi > lo) 
       {
              int mid = (lo + hi)/2;
              ch_merge_sort(values, lo, mid, spare, x_data, y_data);
              ch_merge_sort(values, mid+1, hi, spare, x_data, y_data);
              ch_merge(values, lo, mid, mid+1, hi, spare, x_data, y_data);
       }
}

void ch_merge(patient values[], int begin0, int end0, int begin1, int end1, patient spare[], int x_data, int y_data)
{
       // one sorted sublist in the array values[] goes from begin0 until end0
       // the other sorted sublist goes from begin1 until end1 and begin1 = end0 + 1
       // the whole section of the array that we are looking at goes from begin0 to begin0 until end1.
       int lo = begin0,
       hi = end1,
       count = lo;

       // while there are still elements in each sublist,
       // compare the first element in each sublist, and move the smaller to spare[count].
       // after every move, draw and then wait
       while (begin0 <= end0 && begin1 <= end1)
       {
              // If the second element is greater than the first element 
              // draw the first element in the lower histogram and transfer to spare array
              if (values[begin0].data[x_data] <= values[begin1].data[x_data])
              {
                     spare[count] = values[begin0];
                     values[begin0].data[x_data] = 0;
                     begin0++;
              }

              // If the second element is smaller than the first element 
              // draw the second element in the lower histogram and transfer to spare array

              else if (values[begin0].data[x_data] > values[begin1].data[x_data])
              {
                     spare[count] = values[begin1];
                     values[begin1].data[x_data] = 0;
                     begin1++;
              }
	      count++;
       }

       // If one sublist becomes empty, transfer the remaining elements in the other sublist
       // to the spare[] array. Draw and then wait.
       
       // If the first sublist becomes empty
       if (begin0 >= end0 && values[end0].data[x_data] == 0)
       {
              // Loop to transfer all the remaining elements to spare
              for (int i = begin1; i <= end1; i++)
              {
                     // If the value is not zero, draw the lower histogram and transfer the values
                     if (values[i].data[x_data] != 0)
                     {
                            spare[count] = values[i];
                            values[i].data[x_data] = 0;
                            count++;                            
                     }

              }
       }

       // If the second sublist becomes empty
       else if (begin1 >= end1 && values[end1].data[x_data] == 0)
       {
              // Loop to transfer all the remaining elements to spare
              for (int i = begin0; i <= end0; i++)
              {
                     if (values[i].data[x_data] != 0)
                     {
                            // If the value is not zero, draw the lower histogram and transfer the values
                            spare[count] = values[i];
                            values[i].data[x_data] = 0;
                            count++;                            
                     }

              }
       }

       // copy the sorted numbers back from spare[] array back into the values[] array.
       // draw and then wait
       for (int i = lo; i <= hi; i++)
       {
              values[i] = spare[i];
       }
}

/*****************************************************************/
