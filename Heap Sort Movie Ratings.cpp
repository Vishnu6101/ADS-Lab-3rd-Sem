#include<bits/stdc++.h>
using namespace std;

// structure to store the movie name and it's rating
struct MovieAndRatings
{
    string movie;
    float rating;
};

// class containing the movie rating list, heap size, capacity
// and the functions to insert, sort, print and HeapifyMovie movies
class MovieRatingHeapSort
{
public:
    MovieAndRatings *movieRatingList;
    int capacity;// total heap size
    int heap_size;// number of elements in the heap

    //Constructor
    MovieRatingHeapSort(int capacity);

    // function to find the parentMovie of a movie
    int parentMovie(int i) { return (i-1)/2; }

    // function to find the leftMovie movie of a movie
    int leftMovie(int i) { return (2*i + 1); }

    // function to find the rightMovie movie of a movie
    int rightMovie(int i) { return (2*i + 2); }

    // function to swap two movies
    void swapMovies(MovieAndRatings *x, MovieAndRatings *y);

    // function to heapify the min element while sorting
    void HeapifyMovie(int );

    // function to insert a movie and it's rating
    void insertMovie(string movie, float rating);

    //function to sort the movie rating list
    MovieAndRatings SortMovieList();

    // function to print th move rating list
    void printMovieList(int );
};

MovieRatingHeapSort::MovieRatingHeapSort(int cap)
{
    heap_size = 0;
    capacity = cap;
    // creating an array of structure of size cap
    movieRatingList = new MovieAndRatings[cap];
}

void MovieRatingHeapSort::insertMovie(string movie, float rating)
{
    //checking for overflow condition, if true returning
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertMovie\n";
        return;
    }

    heap_size++;
    int i = heap_size - 1;
    // inserting the movie and it's rating
    movieRatingList[i].movie = movie;
    movieRatingList[i].rating = rating;

    // checking min heap property if violated swapping
    while (i != 0 && movieRatingList[parentMovie(i)].rating > movieRatingList[i].rating)
    {
       swapMovies(&movieRatingList[i], &movieRatingList[parentMovie(i)]);
       i = parentMovie(i);
    }
}

MovieAndRatings MovieRatingHeapSort::SortMovieList()
{
    // empty heap condition
    if (heap_size <= 0)
        return movieRatingList[0];
    // when only one element is present in the heap
    if (heap_size == 1)
    {
        // Decrement heap size and return the movie list[0]
        heap_size--;
        return movieRatingList[0];
    }

    // more than one element in the heap
    MovieAndRatings root = movieRatingList[0];
    //swap first and the last movie and heapify the last movie
    swapMovies(&movieRatingList[0], &movieRatingList[heap_size-1]);
    heap_size--;
    HeapifyMovie(0);

    return root;
}

void MovieRatingHeapSort::HeapifyMovie(int i)
{
    // calculating the left and the right movies
    int l = leftMovie(i);
    int r = rightMovie(i);
    // checking min heap property if violates modifying the least rating values
    int least = i;
    if (l < heap_size && movieRatingList[l].rating < movieRatingList[i].rating)
        least = l;
    if (r < heap_size && movieRatingList[r].rating < movieRatingList[least].rating)
        least = r;
    // if least is not the same then swapping both the movies and heapify it
    if (least != i)
    {
        swapMovies(&movieRatingList[i], &movieRatingList[least]);
        HeapifyMovie(least);
    }
}

// function to swap two movies
void MovieRatingHeapSort::swapMovies(MovieAndRatings *x, MovieAndRatings *y)
{
    MovieAndRatings temp = *x;
    *x = *y;
    *y = temp;
}

void MovieRatingHeapSort::printMovieList(int size)
{
    //Looping the movie rating list and printing every movie
    cout<<"---------------------------\n";
    cout<<left<<setw(20)<<"Movie\t"<<"Rating\n";
    cout<<"---------------------------\n";
    for(int i = 0; i < size; i++)
        cout<<left<<setw(20)<<movieRatingList[i].movie<<"\t"<<movieRatingList[i].rating<<endl;
    cout<<"---------------------------\n";
}

// Driver code
int main()
{
    //required variables
    int cap,choice,size;
    string movie;
    float rating;
    // vector used for restoring
    vector <pair<string,float>> MovRatvec;
    // iterator for the vector
    vector <pair<string,float>>::iterator itr;
    cout<<"***MOVIE RATINGS HEAP SORT***\n";
    cout<<"Enter the capacity of the Movie Rating List: ";
    cin>>cap;// getting the capacity of the heap
    MovieRatingHeapSort MovieRatingList(cap);// creating an empty heap of size cap
    cout<<"Enter 1 to insert a Movie and it's Rating\n"
    <<"Enter 2 for Movie Rating List\n"
    <<"Enter 3 for Printing the Movie Rating List\nEnter 4 to EXIT\n";
    while(1)
    {
        cin>>choice;
        switch(choice)
        {
        case 1:
            // Insertion
            cout<<"Enter the Movie Name and it's Rating to insert : ";
            cin>>movie>>rating;
            // Inserting in both the heap and vector
            MovieRatingList.insertMovie(movie,rating);
            MovRatvec.push_back(make_pair(movie,rating));
            break;
        case 2:
            size = MovieRatingList.heap_size;
            cout<<"Sorted the Movie Rating List.........\n";
            // sorting till the heap size becomes 0
            while(MovieRatingList.heap_size > 0)
                MovieRatingList.SortMovieList();
            //printing the movie list after sorting
            MovieRatingList.printMovieList(size);
            // restoring the heap elements
            for(itr = MovRatvec.begin() ; itr != MovRatvec.end(); itr++)
                MovieRatingList.insertMovie(itr->first,itr->second);
            break;
        case 3:
            // printing the movie list
            MovieRatingList.printMovieList(MovieRatingList.heap_size);
            cout<<endl;
            break;
        case 4:
            //exit
            exit(0);
        default:
            cout<<"Enter a valid number\n";
        }
    }
    return 0;
}
