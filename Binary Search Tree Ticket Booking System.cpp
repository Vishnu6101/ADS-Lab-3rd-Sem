#include<bits/stdc++.h>
using namespace std;

// Structure for storing theatre details.
struct theatre
{
    int id;
    float fare;
    float amount;
    string type;
    theatre *left, *right;
};

//Class containing the functions to create a node
//insert a node in BST and also to display it.
class THEATRE
{
public:
    theatre* createNode(int id, float fare, string type);
    theatre* insertNode(theatre* root, int id, float fare, string type);
    theatre* display(theatre* root);
};

// Function to create a new node with user inputted theatre details
theatre* THEATRE::createNode(int id, float fare, string type)
{
    theatre* newTheatre = new theatre;
    newTheatre->id = id;
    newTheatre->fare = fare;
    newTheatre->type = type;
    // Calculating the rise in fare
    if(newTheatre->type == "AC")
        newTheatre->amount = fare + (fare * 0.18);
    else
        newTheatre->amount = fare + (fare * 0.12);
    newTheatre->left = newTheatre->right = NULL;
    return newTheatre;
}

//function to insert a node in BST
theatre* THEATRE::insertNode(theatre* root, int id, float fare, string type)
{
    if(root == NULL)
    {
        theatre* temp = createNode(id, fare, type);
        return temp;
    }
    if(id < root->id)
        root->left = insertNode(root->left, id, fare, type);
    else if(id > root->id)
        root->right = insertNode(root->right, id, fare, type);

    return root;
}

//Function to display the BST
theatre* THEATRE::display(theatre* root)
{
    if(root != NULL)
    {
        cout<<root->id<<"\t\t"<<root->fare<<"\t\t"<<root->amount<<"\t\t"<<root->type<<endl;
        display(root->left);
        display(root->right);
    }
}

//Driver code
int main()
{
    THEATRE TicketBookingPlatform;
    theatre* root = NULL;
    int choice,id;
    float fare;
    string type;
    cout<<"~~~BINARY SEARCH TREE ONLINE TICKET BOOKING PORTAL~~~"
            <<"\n1.Insert Theatre Details\n2.Display Theatre Details\n3.Exit\n"
            <<"Enter your choice:";
    while(1)
    {
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter the Theatre Details to be insert:";
            cin>>id>>fare>>type;
            root = TicketBookingPlatform.insertNode(root, id, fare, type);
            break;
        case 2:
            cout<<"The Theatre Details are : \n";
            cout<<"---------------------------------------------------------\n";
            cout<<"Id\t\tfare\t\tamount\t\ttype\n";
            cout<<"---------------------------------------------------------\n";
            TicketBookingPlatform.display(root);
            cout<<"---------------------------------------------------------\n";
            break;
        case 3:
            exit(0);
            break;
        default:
            cout<<"\nEnter correct choice:";
        }
    }
    return 0;
}
