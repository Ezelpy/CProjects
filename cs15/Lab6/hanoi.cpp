/*  FILENAME:
 *  NAME: EZEQUIEL RAMIREZ  
 *  DATE: 10/17.24
 *  COURSE: EN47
 *
 */

#include <iostream>
#include "en47_vis_txt.h"

// function declarations
void towers_of_hanoi(int n, int from, int to, int spare, int poles[3][21]);
void move_disk(int from, int to, int poles[3][21]);
int find_top(int pole, int poles[3][21]);

int main () {

    int num_disks = 0;		// total number of disks
    int hi = 21;		// Highest number of the array
    int poles[3][21];		// configurations of disks on each pole

    // print out directions
    cout << "DIRECTIONS: The purpose of this program is to solve the Towers of Hanoi puzzle.\n";
    cout << "This puzzle consists in a series of increasingly sized disks placed in one of the three poles,\n";
    cout << "and the goal is to transfer all the disks to the rightmost pole without putting a bigger disk\n";
    cout << "on top of a smaller one. This program will ask you to input the amount of disks used for the game and\n";
    cout << "it will output the finished Towers of Hanoi game.\n\n";


    // get user to input number of disks -- the number has to be between 3 and 20.
    do
    {
        cout << "Please enter the number of disks you want to move (only between 3 and 20): ";
        cin >> num_disks; 
    }
    while (num_disks < 3 || num_disks > 20);
    
    // initialize poles: put num_disks disks on pole 0, smaller disks on top of bigger ones
    // and no disks on either of pole 1 or pole 2.
    for (int i = 0; i < hi; i++)
    {
        if (i < num_disks) poles[0][i] = num_disks - i; 
        else poles[0][i] = 0;
    }

    // Spare and to poles initializing
    for (int i = 1; i < 3; i++)
    {
        for (int j = 0; j < hi; j++)
        {
            poles[i][j] = 0;
        }   
    }

    // open display and draw the original configuration of all disks on pole 0
    en47_display(200, 100);
    en47_draw_towers(poles);
    en47_wait();


    // now call the towers_of_hanoi function to move all disk from pole 0 to pole 2,
    // using pole 1 for "spare".

    towers_of_hanoi(num_disks, 0, 2, 1, poles);
    en47_wait();
    en47_close();
}

void towers_of_hanoi(int n, int from, int to, int spare, int poles[3][21]) {

    // if there is more than 1 disk on the "from" pole,
    // then recursively move all but 1 of them to the "spare" pole
    // and do a en47_wait();
    if (n >= 1)
    {
        towers_of_hanoi(n - 1, from, spare, to, poles);
        en47_wait(); 
    
        // now announce that you will move a disk #n from pole "from" to pole "to" followed by a "\n".
        // and then call the funcation the function move_disk() that will actually make the move!    
        cout << "Disk #" << n << " will be moved from pole " << from << " to pole " << to << ".\n";
        move_disk(from, to, poles);


        // redraw the poles and then do a en47_wait();
        en47_draw_towers(poles);
        en47_wait();


        // now recursively move the disks that you moved temporariliy to "spare" on top of the one you 
        // just moved to the "to" pole, using the "from" pole as the new "spare"
        towers_of_hanoi(n - 1, spare, to, from, poles);
    }
    
}

void move_disk(int from, int to, int poles[3][21]) {

    int from_top = 0,
	to_top = 0;

    // first find the location of the top disk on the 'from' pole
    from_top = find_top(from, poles);

    // now find the location of the top disk on the 'to' pole
    to_top = find_top(to, poles);

    // now move the disk, taking it out of the "from_top" position on the pole "from"
    // and putting it into the empty "to_top  + 1" position on the pole "to
    poles[to][to_top + 1] = poles[from][from_top];
    poles[from][from_top] = 0;
}

int find_top(int pole, int poles[3][21])
{
    // Function to find the top of the pole
    // This function receives a pole and it returns the index of the top disk
    int top = 0;

    // Loop to iterate through the pole
    for (int i = 0; i < 21; i++)
    {
	// If the number is zero, return the index of the previous disk
        if (poles[pole][i] == 0)
        {
            top = i - 1;
            break;
        }
    }
    return top;
}

