#include<bits/stdc++.h>
using namespace std;

pair<string,int> BinarySearch(vector<pair<string,int>> vecstr,string x)
{
    // Initializing lower and upper bounds
    int lower = 0;
    int upper = vecstr.size() - 1;

    while (lower <= upper)
    {
        //Calculating mid, comparing the name with the name in the vector
        // and updating lower and upper based on the conditions and returning if equal
        int mid = lower + (upper - lower) / 2;

        if (vecstr[mid].first < x)
            lower = mid + 1;
        if (vecstr[mid].first > x)
            upper = mid - 1;
        if (vecstr[mid].first == x)
            return vecstr[mid];
    }
    return make_pair("Not found",0);
}

int main()
{
    //Map to store call logs
    map<string,pair<__int64,int>> call_log;

    //Inserting some random entries
    call_log.insert(pair<string,pair<__int64,int>>("Vishnu", make_pair(9832367231, 10)));
    call_log.insert(pair<string,pair<__int64,int>>("Anand", make_pair(9678787832, 2)));
    call_log.insert(pair<string,pair<__int64,int>>("Rishi", make_pair(9174354632, 5)));
    call_log.insert(pair<string,pair<__int64,int>>("Ravi", make_pair(9378543742, 7)));

    //Initializing an iterator
    map<string,pair<__int64,int>>::iterator itr;

    //Initializing a Vector so that it can be passed in the BinarySearch function
    vector<pair<string,int>> vecstr;
    vector<pair<string,int>>:: iterator vecitr;
    //Copying the values from map to vector
    for(auto itr : call_log)
        vecstr.push_back(make_pair(itr.first,itr.second.second));

    int choice;
    string name;
    __int64 phno;
    pair<string,int> call_details;
    cout<<"~~~CALL LOG~~~\nEnter 1 to insert\nEnter 2 to delete\nEnter 3 to Search\nEnter 4 to print the Call log\n";
    do
    {
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter the name and the phone number to insert : ";
            cin>>name>>phno;
            //Searching the entry
            call_details = BinarySearch(vecstr,name);
            //If not present inserting as a new entry
            if(call_details.second == 0)
                call_log.insert(pair<string,pair<__int64,int>>(name,make_pair(phno, 1)));
            else
            {
                    //If already present incrementing its value
                    call_details = BinarySearch(vecstr,name);
                    if(call_details.second != 0)
                    {
                        call_log[name].second++;
                    }
            }
            vecstr.clear();
            // Copying all the values to Vector
            for(auto itr : call_log)
                vecstr.push_back(make_pair(itr.first,itr.second.second));

            cout<<"Inserted Successfully\n";
            break;
        case 2:
            cout<<"Enter the name to delete from call log : ";
            cin>>name;
            //Deleting an entry from call log
            if(call_log.erase(name))
                cout<<"Deleted Successfully\n";
            else
                cout<<name<<" is not Found in the call log\n";
            break;
        case 3:
            cout<<"Enter the name to search : ";
            cin>>name;
            cout<<"\nSearching "<<"'"<<name<<"'"<<"....";
            call_details = BinarySearch(vecstr,name);//function for Binary Search
            if(call_details.second != 0)
                cout<<"Found \n"<<call_details.first<<"'s calls are Received "<<call_details.second<<" times"<<endl;
            else
                cout<<"Not Found\n";
            break;
        case 4:
            cout<<"Printing the call log\n";
            cout<<"--------------------------------------------\n";
            cout<<"Name\tPhone number\tReceived calls\n";
            cout<<"--------------------------------------------\n";
            for(itr = call_log.begin(); itr != call_log.end(); itr++)
                cout<<itr->first<<"\t"<<itr->second.first<<"\t"<<itr->second.second<<endl;
            cout<<"--------------------------------------------\n";
            break;
        default:
            cout<<"---XXXX---\n";
        }
    }while(choice > 0 && choice <=4);

    return 0;
}
