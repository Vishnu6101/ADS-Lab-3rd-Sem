#include<bits/stdc++.h>
using namespace std;

// function to perform insertion sort
vector <pair<string,int>> insertionSort(vector <pair<string, int>> vec, int n)
{
    int i,j,calorie;
    string food;
    for(j = 1; j < n; j++)
    {
        //storing the food and calorie values of the current food item
        food = vec[j].first;
        calorie = vec[j].second;
        i = j - 1;
        // looping till i >= 0 and sorting
        while(i >= 0 && vec[i].second > calorie)
        {
            vec[i+1] = vec[i];
            i--;
        }
        // storing the current food item in i+1 th position
        vec[i+1].first = food;
        vec[i+1].second = calorie;
    }
    return vec;     // returning the sorted vector
}
int main()
{
    vector <pair<string, int>> foodAndCalorie;

    //manually inserting food and calorie values in random manner
    foodAndCalorie.push_back(make_pair("Low Fat Milk", 121));
    foodAndCalorie.push_back(make_pair("Yogurt", 225));
    foodAndCalorie.push_back(make_pair("Chocolate Milk", 208));
    foodAndCalorie.push_back(make_pair("Apple Juice", 111));
    foodAndCalorie.push_back(make_pair("Dates", 228));
    foodAndCalorie.push_back(make_pair("Watermelon", 50));
    foodAndCalorie.push_back(make_pair("Baked Potato", 220));
    foodAndCalorie.push_back(make_pair("Biscuit", 103));
    foodAndCalorie.push_back(make_pair("Oat Meal", 110));
    foodAndCalorie.push_back(make_pair("Rice", 232));
    foodAndCalorie.push_back(make_pair("Beans", 269));
    foodAndCalorie.push_back(make_pair("Pudding", 161));
    foodAndCalorie.push_back(make_pair("Noodles", 159));
    foodAndCalorie.push_back(make_pair("Pizza", 290));
    foodAndCalorie.push_back(make_pair("Pancake", 41));

    int choice,calorie,count = 0;

    cout<<"***FOOD AND CALORIE INSERTION SORT***\n";
    cout<<"Enter 1 for Sorted Food and Calorie List\nEnter 2 for Recommendations\nEnter 3 for Exit\n";
    while(1)
    {
        cin>>choice;
        switch(choice)
        {
        case 1:         // Sorting
            cout<<"The Sorted Food and Calorie List is :\n";
            foodAndCalorie = insertionSort(foodAndCalorie,foodAndCalorie.size());
            cout<<"-----------------------------------------\n";
            cout<<left<<setw(20)<<"Food"<<"Calories\n";
            cout<<"-----------------------------------------\n";
            for(auto itr : foodAndCalorie)      // Printing
                cout<<left<<setw(20)<<itr.first<<itr.second<<endl;
            cout<<"-----------------------------------------\n";
            break;
        case 2:         // Recommendation
            cout<<"Welcome to our recommendation system\nPlease enter the required calorie value : ";
            cin>>calorie;
            cout<<"-----------------------------------------\n";
            cout<<left<<setw(20)<<"Food"<<"Calories\n";
            cout<<"-----------------------------------------\n";
            for(auto itr : foodAndCalorie)      //Recommending food items by searching the vector
            {
                if(itr.second >= calorie - 15 && itr.second <= calorie + 15)
                {
                    cout<<left<<setw(20)<<itr.first<<itr.second<<endl;
                    count++;
                }
            }
            cout<<"-----------------------------------------\n";
            if(count >= 1)
                cout<<"These are our recommendations for you!!!\n";
            else
                cout<<"Sorry we have no recommendations for you. Please try different calorie value between 50 and 300\n";
            count = 0;
            break;
        case 3:       //Exit
            cout<<"Come Again!!!\n";
            exit(0);
            break;
        default:
            cout<<"Enter a valid number\n";
        }
    }
    return 0;
}
