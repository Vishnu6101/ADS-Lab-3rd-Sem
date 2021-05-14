#include<bits/stdc++.h>
using namespace std;

// Structure for storing CPU jobs with priority and job id.
struct CPUjob
{
    int priority,job_id;
};

// Class containing the necessary functions for building a min heap
class CPU_JOB
{
public:
    CPUjob *jobList;
    int capacity;// total size of the heap
    int heap_size;// number of elements in the heap

    //Constructor
    CPU_JOB(int capacity);

    //Function to find the parentJob of a given node x.
    int parentJob(int i)
    {
        return (i-1)/2;
    }

    //Function to insert a CPU job with priority and job id.
    void insertJob(int priority, int job_id);

    //Function for printing the CPU jobs.
    void printCPUjobs();

    //Function for swapping two CPU jobs while inserting
    void swapJobs(CPUjob *x, CPUjob *y);
};

//Constructor
CPU_JOB::CPU_JOB(int cap)
{
    heap_size = 0;
    capacity = cap;
    jobList = new CPUjob[cap];// creating an array of structure of size cap
}

//Function for inserting a CPU job in heap
void CPU_JOB::insertJob(int priority,int job_id)
{
    //Checking Overflow condition
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertJob\n";
        return;
    }

    heap_size++;
    int i = heap_size - 1;
    // Inserting job_id and priority
    jobList[i].priority = priority;
    jobList[i].job_id = job_id;

    // checking min heap property if violated swapping
    while (i != 0 && jobList[parentJob(i)].priority > jobList[i].priority)
    {
       swapJobs(&jobList[i], &jobList[parentJob(i)]);
       i = parentJob(i);
    }
}

// Function for swapping two jobs
void CPU_JOB::swapJobs(CPUjob *x, CPUjob *y)
{
    CPUjob temp = *x;
    *x = *y;
    *y = temp;
}

//Function for printing the CPU jobs
void CPU_JOB::printCPUjobs()
{
    if(heap_size != 0)
    {
        cout<<"----------------------------------\n";
        cout<<"Priority\tJob ID\n";
        cout<<"----------------------------------\n";
        //Looping the heap and printing each element
        for(int i=0;i<heap_size;i++)
        {
            cout<<jobList[i].priority<<"\t\t"<<jobList[i].job_id<<endl;
        }
        cout<<"----------------------------------\n";
    }
    else
        cout<<"No jobs right now...\n";
}

//Driver code
int main()
{
    cout<<"***CPU SCHEDULING USING HEAP DATA STRUCTURE***\n";
    int choice, priority, job_id;
    CPU_JOB heap(100); // Heap size is 100
    cout<<"Capacity of the Heap is : "<<heap.capacity<<endl;
    cout<<"\nEnter 1 to insert a CPU job\nEnter 2 for Printing the Heap\nEnter 3 to EXIT\n";
    while(1) //Infinite loop till 3 is pressed.
    {
        cin>>choice;
        switch(choice)
        {
        case 1:
            //Insertion
            cout<<"Enter the priority and CPU job : ";
            cin>>priority>>job_id;
            heap.insertJob(priority,job_id);
            break;
        case 2:
            //Printing
            cout<<"The CPU Scheduling is as follows :\n";
            heap.printCPUjobs();
            break;
        case 3:
            //Exit
            exit(0);
        default:
            cout<<"Enter a valid number\n";
        }
    }
    return 0;
}
