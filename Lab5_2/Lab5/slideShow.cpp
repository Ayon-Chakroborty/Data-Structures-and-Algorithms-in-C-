//--------------------------------------------------------------------
//
//  Laboratory 5, Programming Exercise 1                 slideshow.cpp
//
//  (Shell) Slide show program
//
//  Updated: 2008-03-12
//--------------------------------------------------------------------

// Displays a slide show.

// Uncomment the following line if running in windows
//#define WIN32

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

#include "ListLinked.cpp"


//--------------------------------------------------------------------

// This is a very ugly way to wait for a specified amount of time.
// It is ugly because it runs the CPU the whole time, instead of
// just suspending the process for the required time period.
// However, it is also very portable.  This function should work on
// all platforms that support ANSI C++.  Feel free to replace this
// with something nicer (such as sleep or usleep) if you so choose.
void wait(int secs) 
{
    int start=clock();

    while (clock() < start + secs * CLOCKS_PER_SEC);
}

//--------------------------------------------------------------------

class Slide
{
  public:
    static const int HEIGHT = 10,		// Slide dimensions
                     WIDTH  = 36;

    void display () const;			// Display slide and pause

  private:

    char image [HEIGHT][WIDTH];  	   // Slide image
    int pause;				   // Seconds to pause after
   					   //  displaying slide

    friend istream& operator>> (istream& in, Slide& slide);
    friend ostream& operator<< (ostream& out, const Slide& slide);
};

//--------------------------------------------------------------------

int main ()
{
    List<Slide> slideShow;    	    // Slide show
    slideShow.showStructure();
    Slide currSlide;                // Slide
    char filename[81];              // Name of slide show file


    // Read the slide show from the specified file.

    cout << endl << "Enter the name of the slide show file : ";
    cin >> filename;

    ifstream slideFile ( filename );

    if ( !slideFile )
    {
       cout << "Error opening file " << filename << endl;
    }
    else
    {
       // Read in the slides one-by-one. (Your code below)
        while (slideFile >> currSlide) {
            //use currSlide object to build the slideShow list object
            //using insert function to build the slideShow linkedlist
            slideShow.insert(currSlide);
        }




       // Close the file. (Your code below)
        slideFile.close();


       // Display the slide show slide-by-slide. (Your code below)
        //first, move the cursor to the head of the linkedlist (slideshow list object)
        slideShow.gotoBeginning();
        //using loop to call display() function of each slide object
        while (slideFile >> currSlide) {
            //using slideShow.getCursor() to obtain the dataItem of the listNode
            slideShow.getCursor();
            currSlide.display();
            //using gotonext() to go to through the slideShow list slide-byslide
            slideShow.gotoNext();
        }




    }

    return 0;
}

//--------------------------------------------------------------------

istream& operator>> (istream& inFile, Slide& slide)

// Read a slide from inFile.

{
    char sec; //This is used to read the seconds for pausing
    inFile >> slide.pause;
    inFile.get(sec);
    // Read a slide from inFile. (Your code below)
    for (int j = 0; j < Slide::HEIGHT; j++) {
        inFile.getline(slide.image[j], Slide::HEIGHT, '\n' ); //3 parameters: 1. image, 2, length of row to read, 3. change to newline symbol
    }
    return inFile;
}

//--------------------------------------------------------------------

ostream& operator<< (ostream& out, const Slide& slide)

{
    // Display a slide. (Your code below)
    for (int j = 0; Slide::HEIGHT; j++) {

    //for (j=0; Slide::HEIGHT; j++) {
        cout << slide.image[j]; //display jth row of the image data member of the current slide object
        cout << endl;
    }



    return out;
}


void Slide:: display () const

{
    //This should compile and run on both Windows and Unix
    //Feel free to change this if you want to do something nicer.
    #ifdef WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Display a slide and pause. (Your code below)

        cout << *this;
        wait(pause);



}
