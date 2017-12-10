#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "HashTable.h"
using namespace std;

int Hasher(const string& key);

struct subject
{
    string subjectCode;
    int count;
};

void sort(string arr[], int length);


int main()
{
    
    HashTable<string, bool, 750> seenValues(Hasher);
    HashTable<string,  int, 200> uniqueSubjects(Hasher);
    
    int duplication = 0;
    char* token;
    char buf[1000];
    const char* const tab = "\t";
    
    ifstream file;
    file.open("dvc-schedule.txt");
    if(!file.good()){throw "I/0 Error";}
    
    while (file.good())
    {
        string line;
        getline(file, line);
        strcpy(buf, line.c_str());
        
        if (buf[0] == 0) continue;
        
        const string term(token = strtok(buf, tab));
        const string section((token = strtok(0, tab)) ? token : "");
        const string course((token = strtok(0, tab)) ? token : "");
        if (course.find('-') == string::npos) continue;
        const string subjectCode(course.begin(), course.begin() + course.find('-'));
        
        const string termAndSection = term + section;
        
        if (subjectCode.find(':') != string::npos) continue;
        
        if (seenValues[termAndSection])
        {
            duplication++;
        }
        else
        {
            seenValues[termAndSection] = true;
            uniqueSubjects[subjectCode]++;
        }
    }
    file.close();
    
    cout << "\nDuplicates: " << duplication << endl;
    
    Queue<string> subjects = uniqueSubjects.keys();
    
    int length = subjects.size();
    string subjectArray[length];
    
    for (int i = 0; i < length; i++)
    {
        subjectArray[i] = subjects.front();
        subjects.pop();
    }
    
    sort(subjectArray, length);
    
    for (int i = 0; i < length; i++){
        if (subjectArray[i].length() <= 3){
            cout << subjectArray[i] << "\t\t" << uniqueSubjects[subjectArray[i]] << " section(s)" << endl;
            continue;
        }
        cout << subjectArray[i] << "\t" << uniqueSubjects[subjectArray[i]] << " section(s)" << endl;
    }
    return 0;
}

int Hasher(const string& key)
{
    int hashed = 0;
    for (int i = 0; i < key.length(); i++)
        hashed += key.at(i);
    return hashed;
};

void sort(string ar[], int length)
{
    for (int i = 0; i < length; i++)
        for (int j = 0; j < length - 1; j++)
            if (ar[j] > ar[j+1])
                swap(ar[j],ar[j+1]);
}
