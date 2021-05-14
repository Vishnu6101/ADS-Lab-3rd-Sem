#include <bits/stdc++.h>
using namespace std;

// Class containing the variables for storing user details and required pointers
class UserDetails
{
public:
    int user_id;
    string time;
    UserDetails *left;
    UserDetails *right;
    int height;
};

// function to get maximum  of two integers
int max(int a, int b)
{
    return a>b?a:b;
}

// function to get the  height of the user root
int height(UserDetails *user)
{
    if (user == NULL)
        return 0;
    return user->height;
}
// Get Balance factor of user root
int getBalance(UserDetails *user)
{
    if (user == NULL)
        return 0;
    return height(user->left) - height(user->right);
}

// Function to create a node and store user details
UserDetails* newNode(int id, string time)
{
    UserDetails* userDetails = new UserDetails();
    userDetails->user_id = id;
    userDetails->time = time;
    userDetails->left = userDetails->right = NULL;
    userDetails->height = 1;
    return userDetails;
}

// function to right rotate subtree rooted with x and return the modified root
UserDetails *rightRotate(UserDetails *x)
{
    UserDetails *y = x->left;
    UserDetails *T2 = y->right;

    // Perform rotation
    y->right = x;
    x->left = T2;

    // Update heights
    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
      // Return new root
    return y;
}

// function to left rotate subtree rooted with x and return the modified root
UserDetails *leftRotate(UserDetails *x)
{
    UserDetails *y = x->right;
    UserDetails *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;

    return y;
}


// Recursive function to UserEntry a key in the subtree and returns the new root of the subtree.
UserDetails* UserEntry(UserDetails* root, int id, string time)
{
    //normal BST insertion
    if (root == NULL)
        return newNode(id,time);

    if (time < root->time)
        root->left = UserEntry(root->left, id, time);
    else if (time > root->time)
        root->right = UserEntry(root->right, id,time);
    else // Equal keys are not allowed in BST
        return root;

    // height updation
    root->height = 1 + max(height(root->left),height(root->right));

    // store the balance factor
    int balance = getBalance(root);

    // Left Left Case
    if(balance > 1 && time < root->left->time)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && time > root->right->time)
        return leftRotate(root);

    // Left Right Case
    if(balance > 1 && time > root->left->time)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && time < root->right->time)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // return the (unchanged) root pointer
    return root;
}

// function to print preorder traversal of the tree.
void preOrder(UserDetails *root)
{
    if(root != NULL)
    {
        cout<<root->user_id<<"\t"<<root->time<<"\n";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// function to find the inorder predecessor of a node
UserDetails * inorderpred(UserDetails* root)
{
    UserDetails* current = root;
    while (current->right != NULL)
         current = current->right;
      return current;
}

// Recursive function to delete a UserDetails with user id
UserDetails* UserExit(UserDetails *root,int id)
{
    if (root == NULL)
        return root;

    if (id < root->user_id)
        root->left=UserExit(root->left,id);

    else if(id > root->user_id)
        root->right=UserExit(root->right,id);


    else
    {
        // either left or right child
        if((root->left==NULL) || (root->right==NULL))
        {
            UserDetails *temp = root->left?root->left:root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp;
            free (temp);
        }
        else
        {
            UserDetails* temp=inorderpred(root->right);
            // Copy the inorder predecessor's user_id to this root
            root->user_id=temp->user_id;
            // Delete the inorder predecessor
            root->right = UserExit(root->right,temp->user_id);
        }
    }
    if (root==NULL)
    return root;

    // UPDATE HEIGHT OF THE CURRENT root
    root->height = 1 + max(height(root->left),height(root->right));

    // GET THE BALANCE FACTOR
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Driver Code
int main()
{
    int choice, id;
    string time2;
    tm* time1;// variable for storing time
    time_t now = time(0);

    UserDetails *root = NULL;

    cout<<"***AVL TREE LIBRARY ENTRY AND EXIT***\n";
    cout<<"Enter 1 to Entry\nEnter 2 to see the Entry List\nEnter 3 to EXIT\nEnter 4 to quit\n";
    cout<<"Enter your choice : ";
    while(1)
    {
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter the name to UserEntry : ";
            cin>>id;
            now = time(0);
            time1 = localtime(&now);// storing the present time
            // converting the time to string
            time2 = to_string(time1->tm_hour) + ":" + to_string(time1->tm_min) + ":" + to_string(time1->tm_sec);
            root = UserEntry(root, id, time2); // inserting user id with entry time
            cout<<"Inserted Successfully\n";
            break;
        case 2:
            cout<<"The Entry List is :\n";
            cout<<"-----------------------------\n";
            cout<<"User ID\tEntry Time\n";
            cout<<"-----------------------------\n";
            // printing the tree
            preOrder(root);
            cout<<"-----------------------------\n";
            break;
        case 3:
            cout<<"Enter the name to delete : ";
            cin>>id;
            // deleting when the user exits the library
            root = UserExit(root, id);
            break;
        case 4:
            exit(0);
            break;
        default:
            cout<<"Enter a valid number\n";
        }
    }
    return 0;
}
