#include<bits/stdc++.h>
using namespace std;
bool CheckAnagram(string str1, string str2)
{
    // Converting the string to lowercase
    transform(str1.begin(),str1.end(),str1.begin(),::tolower);
    transform(str2.begin(),str2.end(),str2.begin(),::tolower);

    // Checking the string length if not equal return false
    if(str1.length() != str2.length())
        return false;
    else
    {
        // Map to store letter and its frequency
        map<char,int> Anagram;
        //Incrementing for every letter in str1
        for(char c : str1)
            Anagram[c] += 1;

        //Decrementing the letter's value for every letter in str2
        for(char c : str2)
            Anagram[c] -= 1;

        map<char,int>::iterator itr;

        // Checking for 0 values using Linear Search
        // if non zero value found return false else true
        for(itr = Anagram.begin(); itr != Anagram.end(); itr++)
        {
            if(itr->second != 0)
                return false;
        }
        return true;
    }
}

int main()
{
    cout<<"~~~LINEAR SEARCH ANAGRAM~~~\n";
    string str1,str2;
    cout<<"Enter two Strings : \n";
    cin>>str1>>str2;
    if(CheckAnagram(str1,str2)) //function to check Anagram
        cout<<str1<<" and "<<str2<<" are "<<"Anagram\n";
    else
        cout<<str1<<" and "<<str2<<" are "<<"Not Anagram\n";
    return 0;
}
