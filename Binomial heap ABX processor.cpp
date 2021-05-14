#include<iostream>
using namespace std;

//Structure for a node in the binomial heap
struct node
{
	int time;
	int job_id;
	int degree;
	struct node *child;
	struct node *sibling;
	struct node *parent;
};

//Class containing all the functions for binomial heap
class binomialheap
{
public:
    node *head;
    //Constructor
    binomialheap()
	{
		head = NULL;
	}

	//Function to create an single node
	node *createnode(int id, int  time)
	{
		node *root;
		root = new node;
		root->child = root->sibling = root->parent = NULL;
		root->degree = 0;
		root->job_id = id;
		root->time = time;
	}

	//Function to Insert a node in binomial heap
	//by performing Merge and Union operations
	void Insert(node *root)
	{
		head = Merge(head, root);
		head = Union(head);
		cout<<"Inserted successfully"<<endl;
	}

	//Function to Merge two binomial heaps
	node *Merge(node *root1, node *root2)
	{
		node *head1;
		node *temp;
		if(!root1)
			return root2;
		if(!root2)
			return root1;
		if(root1->degree <= root2->degree)
		{
			head1 = root1;
			root1 = root1->sibling;
		}
		else
		{
			head1 = root2;
			root2 = root2->sibling;
		}
		temp = head1;
		while(root1 && root2)
		{
		    //If root1->deg is less or equal make it as sibling of temp and update temp
			if(root1->degree <= root2->degree)
			{
				temp->sibling = root1;
				root1 = root1->sibling;
			}
			//If root2->deg is less or equal make it as sibling of temp and update temp
			else
			{
				temp->sibling = root2;
				root2 = root2->sibling;
			}
			temp = temp->sibling;
		}
		//Make the remaining binomial tree as sibling of temp.
		if(root1)
			temp->sibling = root1;
		else
            temp->sibling = root2;
		return head1;
	}

	//Function to perform Union on binomial heap after merging the heap elements
	// by using 3 pointers prev, curr, next.
	node *Union(node *root)
	{
		node *temp;
		node *prev;
		node *current;
		node *next;
		node *head1;
		prev = NULL;
		current = root;
		next = current->sibling;
		if(!root->sibling)
			return root;
		while(next)
		{
		    // Case 1 simply move on when curr->deg and next->deg are different
			if(current->degree != next->degree)
			{
				if(!prev)
					head1 = current;
				prev = current;
				current = next;
				next = next->sibling;
			}
			else
			{
			    // case 2 move on when curr->deg and next->next->deg are equal
				if(next->sibling && next->sibling->degree == current->degree)
				{
					if(!prev)
						head1 = current;
					prev = current;
					current = next;
					next = next->sibling;
				}
				// Case 3 when curr->deg and next->deg are equal but not next->next->deg
				//then make the greater value node as a child of lesser value node
				else
				{
				    //When curr->time is greater make next as parent of curr
					if(current->time > next->time)
					{
						if(prev)
							prev->sibling = next;
						current->sibling = NULL;
						Link(next, current);
						current = next;
						next = next->sibling;
					}
					// When curr->time is lesser make curr as the parent of next
					else
					{
						current->sibling = next->sibling;
						next->sibling = NULL;
						Link(current, next);
						next = current->sibling;
					}
				}
			}
		}
		if(!prev)
			head1 = current;
		return head1;
	}

	//Function to Link two binomial trees by making root1 as the parent of root2
	void Link(node *root1, node *root2)
	{
		root1->degree++;  //Increment root1->deg
		root2->parent = root1; //Make root1 as parent of root2
		if(!root1->child) //If root1 has no child
		{
			root1->child = root2;
			return;
		}
		//If root1 has child
		root1 = root1->child;
		while(root1->sibling)
			root1 = root1->sibling;
		root1->sibling = root2; //Make root 2 as the last sibling of root1
	}

	//Function to delete the minimum element from the binomial heap
	node *ExtractMin()
	{
		node *temp;
		node *x;
		if(!head)
			return NULL;
		temp = getMin(); // Finding the minimum element
		if(temp == head)
		{
			head = head->sibling;
			// If only one element is in the heap
			if(!head && temp->degree == 0)
				return temp;
		}
		else
		{
			x = head;
			//Connecting x->sibling with temp->sibling
			while(x->sibling != temp)
				x = x->sibling;
			x->sibling = x->sibling->sibling;
		}
		temp->sibling = NULL;
		x = temp->child;
		//Removing all the parent pointers of min node
		while(x)
		{
			x->parent = NULL;
			x = x->sibling;
		}
		x = temp->child;
		temp->child = NULL;
		//Reconstructing the binomial heap
		head = Merge(head, x);
		head = Union(head);
		temp->degree = 0;
		return temp;
	}

	//Function to get the minimum element in the binomial heap
	node *getMin()
	{
		int min;
		node *temp, *minimum;
		temp = head;
		min = head->time;
		minimum = head;
		head = head->sibling;
		while(head)
		{
		    //If less than min reassigning min and minimum
			if(head->time < min)
			{
				min = head->time;
				minimum = head;
			}
			head = head->sibling;
		}
		head = temp;
		return minimum;
	}

	//Function to print the binomial heap elements
	void printHeap(node *root)
	{
	    if(!root)
	        return;
	    else
        {
            cout<<root->time<<"(B"<<root->degree<<")"<<"\t";
            if(root->child)
                printHeap(root->child);
            printHeap(root->sibling);
        }
	}
};

int main()
{
	binomialheap JobList;
	node *root;
	int time, jobId, choice;
	cout<<"***ABX PROCESSOR BINOMIAL HEAP JOB LIST***\n";
    cout<<"Press 1 to Insert a Job \nPress 2 to delete Minimum time Job\n"
        <<"Press 3 to Print the Job list\nPress 4 to exit"<<endl;
	while(1)
	{
	    cout<<"Enter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
			    //Insertion of a node in binomial heap
				cout<<"Enter job Id and Time : ";
				cin>>jobId>>time;
				root = JobList.createnode(jobId, time);
				JobList.Insert(root);
				break;
			case 2:
			    //Deleting the minimum element in a binomial heap
				root=JobList.ExtractMin();
				if(!root)
					cout<<"Empty Heap"<<endl;
				else
				{
				    cout<<"The job with JobID "<<root->job_id<<" of time "<<root->time<<"ns has been completed"<<endl;
                    free(root);
				}
				break;
            case 3:
                //Printing the binomial heap
                root = JobList.head;
                cout<<"The Jobs in the JobList are :\n";
                JobList.printHeap(root);
                cout<<endl;
                break;
            case 4:
                //EXIT
                cout<<"***EXIT***";
                exit(0);
			default:
				cout<<"Invalid input!!!"<<endl;
		}
	}
	return 0;
}
