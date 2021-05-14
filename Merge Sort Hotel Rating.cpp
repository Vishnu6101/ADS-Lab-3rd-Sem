#include<bits/stdc++.h>
using namespace std;

// function to sort and merge two arrays
void merge(float *arr, int lb, int mid, int ub)
{
    int i,j,k;
    float arr1[ub - lb + 1];
    i = lb;
    j = mid + 1;
    k = 0;
    // Sorting in decreasing order
    while(i <= mid && j <= ub)
    {
        if(arr[i] >= arr[j])
        {
            arr1[k] = arr[i];
            i++;
        }
        else
        {
            arr1[k] = arr[j];
            j++;
        }
        k++;
    }
    // Copying the remaining elements
    if(i > mid)     // if right array has extra elements
    {
        while(j <= ub)
        {
            arr1[k] = arr[j];
            j++;
            k++;
        }
    }
    else        // if left array has extra elements
    {
        while(i <= mid)
        {
            arr1[k] = arr[i];
            i++;
            k++;
        }
    }
    // Copying the array elements into original array
    for(int i = lb; i <= ub; i++)
        arr[i] = arr1[i - lb];
}
// function to divide the original array by recursive call
void mergeSort(float *arr, int lb, int ub)
{
    if(lb < ub)
    {
        int mid = (lb+ub)/2;
        mergeSort(arr,lb,mid);      //Dividing the array by recursive calling of mergeSort()
        mergeSort(arr,mid + 1,ub);
        merge(arr,lb,mid,ub);       // Combining the divided arrays and sorting by merge()
    }
}

int main()
{
    vector <pair<string, float>> HotelRatingList; // for unsorted hotel list
    vector <pair<string, float>> SortedHRL;  // for sorted hotel list

    // random entry of hotels with their ratings
    HotelRatingList.push_back(make_pair("Hotel A",9.0));
    HotelRatingList.push_back(make_pair("Hotel B",7.3));
    HotelRatingList.push_back(make_pair("Hotel C",9.3));
    HotelRatingList.push_back(make_pair("Hotel D",8.1));
    HotelRatingList.push_back(make_pair("Hotel E",7.5));
    HotelRatingList.push_back(make_pair("Hotel F",6.0));
    HotelRatingList.push_back(make_pair("Hotel G",8.0));
    HotelRatingList.push_back(make_pair("Hotel H",9.7));
    HotelRatingList.push_back(make_pair("Hotel I",9.0));
    HotelRatingList.push_back(make_pair("Hotel J",5.5));
    HotelRatingList.push_back(make_pair("Hotel K",8.8));

    cout<<"***HOTEL RATING MERGE SORT***\n";
    cout<<"Enter 1 for Sorted List\nEnter 2 for Hotel Recommendation\nEnter 3 for Exit\n";

    int choice, n , i, j;
    n = HotelRatingList.size();
    float arr[n], rating;

    // Copying the ratings in an array
    for(int i = 0; i< n;i++)
        arr[i] = HotelRatingList[i].second;

    while(1)
    {
        cin>>choice;
        switch(choice)
        {
        case 1:     // Displaying sorted hotel rating list
            cout<<"The Sorted Hotel Rating List :\n";
            mergeSort(arr,0,n-1); // calling the mergeSort function and sorting the array of ratings
            // matching the hotel names with their ratings and storing in a new vector
            for(i = 0;i < n;i++)
            {
                j = 0;
                while(arr[i] != HotelRatingList[j].second)
                    j++;
                SortedHRL.push_back(make_pair(HotelRatingList[j].first,arr[i]));
                HotelRatingList.erase(HotelRatingList.begin() + j); // deleting the hotel after storing in sorted list
            }
            // Printing the sorted vector
            cout<<"------------------------------------------\n";
            cout<<left<<setw(10)<<"Hotels"<<"Rating\n";
            cout<<"------------------------------------------\n";
            for(auto i : SortedHRL)
                cout<<left<<setw(10)<<i.first<<i.second<<endl;
            cout<<"------------------------------------------\n";
            break;
        case 2:     // Recommendation
            cout<<"Welcome to our Hotel Recommendation system\n";
            cout<<"Enter the rating of the hotel : ";
            cin>>rating;
            cout<<"------------------------------------------\n";
            cout<<left<<setw(10)<<"Hotels"<<"Rating\n";
            cout<<"------------------------------------------\n";
            for(auto i : SortedHRL)       //Recommending food items by searching the vector
            {
                if(i.second >= rating - 0.5 && i.second <= rating + 0.5)
                    cout<<left<<setw(10)<<i.first<<i.second<<endl;
            }
            cout<<"------------------------------------------\n";
            cout<<"These are our recommendations for you!!!\n";
            break;
        case 3:     //Exit
            cout<<"Visit Again\n";
            exit(0);
            break;
        default:
            cout<<"Enter a valid number\n";
        }
    }
    return 0;
}
