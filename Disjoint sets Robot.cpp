#include <bits/stdc++.h>
using namespace std;

// Structure to store place name, parent of the place and its rank.
struct Robot
{
    string place;
    int rank, parent;
};

// Class for implementing Disjoint set
class DisjSet
{
    Robot *robot;
    int no_of_places;

public:
    bool flag;
	DisjSet(int no_of_places)
	{
        robot = new Robot[no_of_places];
		this->no_of_places = no_of_places;
		flag = false;
		makeSet();
	}
	// Function to create and initialize all the place as separate sets.
	void makeSet()
	{
		for (int i = 0; i < no_of_places; i++)
        {
            robot[i].place = "Place " + to_string(i); //Place name
			robot[i].parent = i;  // Place's Parent
			robot[i].rank = 0; // Place rank
		}
	}
	// Finds set of given place
	int find(int place)
	{
		if (robot[place].parent != place)
			robot[place].parent = find(robot[place].parent);

		return robot[place].parent;
	}
    // Function to union two places that the robot visits
	void Union(int place1, int place2)
	{
	    // Finding the parents of two places
		int parent1 = find(place1);
		int parent2 = find(place2);

		// if same parent no union is performed
		if (parent1 == parent2)
        {
            cout<<"The food is already delivered to place " + to_string(place2)<<endl;
            return;
        }
        // if parent1 rank is less than parent 2 rank
        // make parent 2 as parent of parent 1
		if (robot[parent1].rank < robot[parent2].rank)
        {
			robot[parent1].parent = parent2;
		}
		// if parent 1 rank is greater than parent 2 rank
        // make parent 1 as parent of parent 2
		else if (robot[parent1].rank > robot[parent2].rank)
		{
			robot[parent2].parent = parent1;
		}
        // make parent 2 as parent of parent 1 and increment rank of parent 2 by 1
		else
		{
			robot[parent1].parent = parent2;
			robot[parent2].rank = robot[parent2].rank + 1;
		}
		cout<<"The food has been delivered from Place " + to_string(place1) + " to Place " + to_string(place2)<<endl;
		flag = true;
	}
	// Function to check whether the food is delivered to all the places.
	bool FoodDelivery()
	{
	    int root = robot[0].parent;
	    for(int i = 0; i < no_of_places; i++)
        {
            if(root != robot[i].parent)
                return false;
        }
        return true;
	}
	// Function to print the visited places by the robot
	void print()
	{
	    cout<<setw(7)<<"place"<<setw(10)<<"Parent"<<endl;
	    for(int i = 0; i < no_of_places; i++)
        {
            cout<<setw(7)<<robot[i].place;
            cout<<setw(10)<<robot[i].parent;
            cout<<endl;
        }
	}
};

int main()
{
    cout<<"***ROBOT FOOD DELIVERY USING DISJOINT SETS***";
    int choice, startingPlace, destination, noOfPlaces;
    bool success;
    // Declaring a region with 10 different places.
    cout<<"\nEnter the number of places you want to deliver food : ";
    cin>>noOfPlaces;
    DisjSet robotObj(noOfPlaces);
    cout<<"\nEnter the starting Place : ";
    cin>>startingPlace;
    cout<<"\nEnter 1 to select the destination Place for the Robot to deliver Food\n"
    <<"Enter 2 to Print the visited place\nEnter 3 to EXIT\n";
    while(1) //Infinite loop till 3 is pressed.
    {
        cin>>choice;
        switch(choice)
        {
        case 1:
            //Insertion
            cout<<"Enter the Place to Deliver Food : ";
            cin>>destination; // Get two places
            robotObj.Union(startingPlace,destination);
            if(robotObj.flag)
                startingPlace = destination;
            robotObj.flag = false;
            break;
        case 2:
            //Printing
            cout<<"The Robot Path :\n";
            robotObj.print();
            break;
        case 3:
            //Exit
            if(robotObj.FoodDelivery())
            {
                cout<<"Food has been delivered to all your destinations...\nThank you for using our Bot Service!!!\n";
                exit(0);
            }

            else
                cout<<"Food has NOT been delivered to all your destinations...\nPlease select different destination\n";
            break;
        default:
            cout<<"Enter a valid number\n";
        }
    }
	return 0;
}
