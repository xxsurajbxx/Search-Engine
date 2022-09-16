#include <iostream>
#include <map>
#include <fstream>

using namespace std;

void clear() {
    #ifdef _WIN32
    system("cls");
    #endif
    #ifdef __linux__
    system("clear");
    #endif
    #ifdef __APPLE__
    system("clear");
    #endif
}

void getResults(string filenames[], int numofnames) {
    #ifdef _WIN32
    system("mkdir Temporary_Results");
    for(int i=0; i<numofnames; i++) {
        system(("copy Photos\\"+filenames[i]+" TEMP_"+filenames[i]+" > nul").c_str());
        system(("move TEMP_"+filenames[i]+" Temporary_Results > nul").c_str());
    }
    system("start Temporary_Results");
    #endif
    #ifdef __linux__
    system("clear");
    #endif
    #ifdef __APPLE__
    system("clear");
    #endif
}

void deleteResults() {
    #ifdef _WIN32
    system("del Temporary_Results /q");
    system("rd Temporary_Results");
    #endif
    #ifdef __linux__
    system("clear");
    #endif
    #ifdef __APPLE__
    system("rm -R Temporary_Results");
    #endif
}

bool containsNumbers(string str) {
    char integers[10]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for(int i=0; i<str.length(); i++) {
        for(int x=0; x<10; x++) {
            if(str[i]==integers[x]) {
                return true;
            }
        }
    }
    return false;
}

int getNumberofSpaces(string str) {
    int numofspaces=0;
    for(int i=0; i<str.length(); i++) {
        if(str[i]==' ') {numofspaces++;}
    }
    return numofspaces;
}

int getNumberofLines(string filename) {
    ifstream file;
    file.open(filename);
    string line;
    int numofLines=0;
    while(getline(file, line)) {
        numofLines++;
    }
    return numofLines;
}

int getNumberofTags(string filename) {
    ifstream file;
    file.open(filename);
    string line;
    int numoftags=0;
    while(getline(file, line)) {
        if(line[0]!='\0'&&line[0]!='\t') {
            numoftags++;
        }
    }
    return numoftags;
}

int getNumberofItems(string filename, int numoftags) {
    ifstream file;
    file.open(filename);
    string line;
    int numofitems=0;
    int nums[numoftags];
    int temp=0;
    while(getline(file, line)) {
        if(line[0]!='\0'&&line[0]=='\t') {
            numofitems++;
        }
        else {
            nums[temp++] = numofitems;
            numofitems=0;
        }
    }
    int x=0;
    for(int i=0; i<numoftags; i++) {
        if(x<nums[i]) {x=nums[i];}
    }
    return x;
}

int removeDuplicates(string* arr, int size) {
    string x[size];
    int cntr=0;
    for(int i=0; i<size; i++) {
        bool a=false;
        for(int b=0; b<cntr; b++) {
            if(x[b]==arr[i]) {a=true;}
        }
        if(!a) {
            x[cntr++] = arr[i];
        }
    }
    for(int i=0; i<size; i++) {
        if(i<cntr) {
            arr[i]=x[i];
        }
        else {arr[i]="";}
    }
    return cntr;
}

void LowerCase(string* arr, int arrsize) {
    map<char, char> upperstolowers = {{'A','a'},{'B','b'},{'C','c'},{'D','d'},{'E','e'},{'F','f'},{'G','g'},{'H','h'},{'I','i'},{'J','j'},{'K','k'},{'L','l'},{'M','m'},{'N','n'},{'O','o'},{'P','p'},{'Q','q'},{'R','r'},{'S','s'},{'T','t'},{'U','u'},{'V','v'},{'W','w'},{'X','x'},{'Y','y'},{'Z','z'}};
    char uppers[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char lowers[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for(int i=0; i<arrsize; i++) {
        if(!containsNumbers(arr[i])) {
            for(int x=0; x<arr[i].length(); x++) {
                bool isupper = false;
                for(int a=0; a<26; a++) {
                    if(arr[i][x]==uppers[a]) {isupper=true;}
                }
                if(x==0&&!isupper&&arr[i][x]!='+'&&arr[i][x]!='-') {
                    for(int v=0; v<26; v++) {
                        if(arr[i][x]==lowers[v]) {
                            arr[i][x] = uppers[v];
                            break;
                        }
                    }
                }
                if(isupper&&x!=0) {
                    arr[i][x]=upperstolowers[arr[i][x]];
                }
            }
            if(arr[i]=="And") {
                arr[i] = "and";
            }
        }
    }
}

int main() {
    const string fileName="test.txt";
    string line;
    int numofLines=getNumberofLines(fileName);
    int numofTags=getNumberofTags(fileName);
    int numofVals=0;
    int numofWords;
    int temp=0;
    bool usesSigns=false;
    string lines[numofLines];
    string tags[numofTags];
    int ValuesperTag[numofTags];
    string values[numofTags][getNumberofItems(fileName, numofTags)];
    ifstream file;
    file.open(fileName);
    if(file.is_open()) {
        numofLines=0;
        numofTags=0;
        numofVals=0;
        while(getline(file, line)) {
            lines[numofLines++] = line;
        }
        for(int i=0; i<numofLines; i++) {
            if(lines[i][0]!='\0') {
                if(lines[i][0]=='\t') {
                    values[numofTags][numofVals++] = string(lines[i].begin()+1, lines[i].end());
                }
                else {
                    if(i!=0) {
                        ValuesperTag[numofTags] = numofVals;
                        tags[++numofTags] = lines[i];
                    }
                    else {
                        tags[numofTags] = lines[i];
                    }
                    numofVals=0;
                }
            }
        }
        ValuesperTag[numofTags++] = numofVals;
    }
    else {
        cout << "Error: cannot open " << fileName;
        cin.get();
        return -1;
    }
    label:
    cout << "\t+-----------------------+\n\t| Suraj's Search Engine |\n\t+-----------------------+" << endl;
    cout << endl;
    cout << "Enter Your Search Criteria: ";
    getline(cin, line);
    numofWords=getNumberofSpaces(line)+1;
    string words[numofWords];
    int lastSpace=0;
    temp=0;
    for(int i=0; i<line.length(); i++) {
        if(line[i]==' ') {
            words[temp++] = string(line.begin()+lastSpace, line.begin()+i);
            lastSpace=i+1;
        }
        else if(i==line.length()-1) {
            words[temp]=line.substr(lastSpace, i+1);
        }
    }
    LowerCase(&words[0], numofWords);
    if(words[0]=="Help") {
        cout << endl;
        cout << "Enter locations, years or names to narrow down your search" << endl;
        cout << "Keep in mind that the operations process from left to right so search accordingly" << endl << endl;
        cout << "Syntax: " << endl;
        cout << "\tEvery word has to start with a capital letter" << endl;
        cout << "\tEvery symbol and keyword must be separated with a space (this includes signs like \"+\", \"and\", and \"-\")" << endl << endl;
        cout << "To get all the results for each keyword, either just type the words out or use the \"+\" sign" << endl;
        cout << "\tFor example: if you typed, \"Beach Suraj 2003\" or \"Beach + Suraj + 2003\" it grabs every picture from 2003, every picture from the Beach and every picture of Suraj" << endl << endl;
        cout << "To get results of multiple keywords at once, use the \"and\" keyword" << endl;
        cout << "\tFor example: if you typed, \"Beach and Suraj and 2003\" it grabs every picture of Suraj at the Beach, taken during 2003" << endl << endl;
        cout << "To get results of one keyword without results of another, use the \"-\"sign" << endl;
        cout << "\tFor example: if you typed, \"Beach - Suraj - 2003\" it grabs every picture taken on the beach without Suraj, and not taken during 2003" << endl;
        cout << endl << endl;
        cout << "Press Enter to Continue...";
        cin.get();
        clear();
        goto label;
    }
    else if(words[0]=="Exit") {return 0;}
    int numofKeywords=0;
    for(int i=0; i<numofWords; i++) {
        if(words[i]=="+"||words[i]=="-"||words[i]=="and") {
            numofKeywords++;
            usesSigns=true;
        }
        else {
            for(int x=0; x<numofTags; x++) {
                if(words[i]==tags[x]) {
                    numofKeywords++;
                    break;
                }
                else if(tags[x].find('/')!=string::npos) {
                    int counter123=0;
                    for(int a=0; a<tags[x].length(); a++) {
                        if(tags[x][a]=='/') {counter123++;}
                    }
                    string tagkwords[counter123];
                    counter123=0;
                    int lastpos=0;
                    bool b=false;
                    for(int a=0; a<tags[x].length(); a++) {
                        if(tags[x][a]=='/') {
                            tagkwords[counter123++] = string(tags[x].begin()+lastpos, tags[x].begin()+a);
                            lastpos=a+1;
                        }
                    }
                    tagkwords[counter123++] = string(tags[x].begin()+lastpos, tags[x].end());
                    for(int a=0; a<counter123; a++) {
                        if(words[i]==tagkwords[a]) {
                            numofKeywords++;
                            b=true;
                            break;
                        }
                    }
                    if(b) {break;}
                }
            }
        }
    }
    string keywords[numofKeywords];
    int returnValsperTag[numofKeywords];
    numofKeywords=0;
    for(int i=0; i<numofWords; i++) {
        if(words[i]=="+") {
            keywords[numofKeywords++] = "+";
        }
        else if(words[i]=="-") {
            keywords[numofKeywords++] = "-";
        }
        else if(words[i]=="and") {
            keywords[numofKeywords++] = "and";
        }
        else {
            for(int x=0; x<numofTags; x++) {
                if(words[i]==tags[x]) {
                    keywords[numofKeywords++] = words[i];
                    break;
                }
                else if(tags[x].find('/')!=string::npos) {
                    int counter123=0;
                    for(int a=0; a<tags[x].length(); a++) {
                        if(tags[x][a]=='/') {counter123++;}
                    }
                    string tagkwords[counter123];
                    counter123=0;
                    int lastpos=0;
                    bool b=false;
                    for(int a=0; a<tags[x].length(); a++) {
                        if(tags[x][a]=='/') {
                            tagkwords[counter123++] = string(tags[x].begin()+lastpos, tags[x].begin()+a);
                            lastpos=a+1;
                        }
                    }
                    tagkwords[counter123++] = string(tags[x].begin()+lastpos, tags[x].end());
                    for(int a=0; a<counter123; a++) {
                        if(words[i]==tagkwords[a]) {
                            keywords[numofKeywords++] = tagkwords[a];
                            b=true;
                            break;
                        }
                    }
                    if(b) {break;}
                }
            }
        }
    }
    string potentialReturnValues[numofKeywords][getNumberofItems(fileName, getNumberofTags(fileName))];
    int numofReturnValues=0;
    for(int i=0; i<numofKeywords; i++) {
        if(keywords[i]=="+"||keywords[i]=="-"||keywords[i]=="and") {
            returnValsperTag[numofReturnValues] = 0;
            numofReturnValues++;
        }
        else {
            for(int x=0; x<numofTags; x++) {
                if(keywords[i]==tags[x]) {
                    for(int y=0; y<ValuesperTag[x]; y++) {
                        potentialReturnValues[numofReturnValues][y] = values[x][y];
                    }
                    returnValsperTag[numofReturnValues] = ValuesperTag[x];
                    numofReturnValues++;
                    break;
                }
                else if(tags[x].find('/')!=string::npos) {
                    int counter123=0;
                    for(int a=0; a<tags[x].length(); a++) {
                        if(tags[x][a]=='/') {counter123++;}
                    }
                    string tagkwords[counter123];
                    counter123=0;
                    int lastpos=0;
                    bool b=false;
                    for(int a=0; a<tags[x].length(); a++) {
                        if(tags[x][a]=='/') {
                            tagkwords[counter123++] = string(tags[x].begin()+lastpos, tags[x].begin()+a);
                            lastpos=a+1;
                        }
                    }
                    tagkwords[counter123++] = string(tags[x].begin()+lastpos, tags[x].end());
                    for(int a=0; a<counter123; a++) {
                        if(keywords[i]==tagkwords[a]) {
                            for(int y=0; y<ValuesperTag[x]; y++) {
                                potentialReturnValues[numofReturnValues][y] = values[x][y];
                            }
                            returnValsperTag[numofReturnValues] = ValuesperTag[x];
                            numofReturnValues++;
                            b=true;
                            break;
                        }
                    }
                    if(b==true) {break;}
                }
            }
        }
    }
    string returnValues[getNumberofItems(fileName, getNumberofTags(fileName))*numofKeywords];
    numofReturnValues=0;
    int a=0;
    bool checklist[numofKeywords];
    if(usesSigns) {
        for(int i=1; i<numofKeywords-1; i+=2) {
            if(keywords[i]=="+") {
                usesSigns=true;
                if(!checklist[i-1]) {
                    for(int x=0; x<returnValsperTag[i-1]; x++) {
                        returnValues[numofReturnValues++] = potentialReturnValues[i-1][x];
                    }
                    checklist[i-1] = true;
                    checklist[i] = true;
                    checklist[i+1] = true;
                }
                for(int x=0; x<returnValsperTag[i+1]; x++) {
                    returnValues[numofReturnValues++] = potentialReturnValues[i+1][x];
                }
                numofReturnValues = removeDuplicates(&returnValues[0], numofReturnValues);
            }
            else if(keywords[i]=="-") {
                usesSigns=true;
                if(!checklist[i-1]) {
                    for(int x=0; x<returnValsperTag[i-1]; x++) {
                        returnValues[numofReturnValues++] = potentialReturnValues[i-1][x];
                    }
                    checklist[i-1] = true;
                    checklist[i] = true;
                    checklist[i+1] = true;
                }
                string newarray[numofReturnValues];
                int actualsize=0;
                for(int s=0; s<numofReturnValues; s++) {
                    bool a=true;
                    for(int x=0; x<returnValsperTag[i+1]; x++) {
                        if(returnValues[s]==potentialReturnValues[i+1][x]) {a=false;}
                    }
                    if(a) {newarray[actualsize++]=returnValues[s];}
                }
                for(int y=0; y<numofReturnValues; y++) {
                    if(y<actualsize) {
                        returnValues[y] = newarray[y];
                    }
                    else {
                        returnValues[y] = "";
                    }
                }
                numofReturnValues=actualsize;
            }
            else if(keywords[i]=="and") {
                usesSigns=true;
                if(!checklist[i-1]) {
                    for(int x=0; x<returnValsperTag[i-1]; x++) {
                        returnValues[numofReturnValues++] = potentialReturnValues[i-1][x];
                    }
                    checklist[i-1] = true;
                    checklist[i] = true;
                    checklist[i+1] = true;
                }
                string newarray[numofReturnValues];
                int actualsize=0;
                for(int y=0; y<numofReturnValues; y++) {
                    for(int x=0; x<returnValsperTag[i+1]; x++) {
                        if(potentialReturnValues[i+1][x]==returnValues[y]) {
                            newarray[actualsize++] = returnValues[y];
                        }
                    }
                }
                for(int y=0; y<numofReturnValues; y++) {
                    if(y<actualsize) {
                        returnValues[y] = newarray[y];
                    }
                    else {
                        returnValues[y] = "";
                    }
                }
                numofReturnValues=actualsize;
                numofReturnValues = removeDuplicates(&returnValues[0], numofReturnValues);
            }
        }
    }
    else {
        for(int i=0; i<numofKeywords; i++) {
            for(int x=0; x<returnValsperTag[i]; x++) {
                returnValues[numofReturnValues++] = potentialReturnValues[i][x];
            }
        }
        numofReturnValues = removeDuplicates(&returnValues[0], numofReturnValues);
    }
    cout << endl;
    if(returnValues>0) {
        cout << "Press Enter to View Your Results...";
        cin.get();
        getResults(returnValues, numofReturnValues);
        cout << endl;
        cout << "Press Enter to Finish...";
        cin.get();
        deleteResults();
    }
    else {
        cout << "No Results Were Found..." << endl;
        cout << endl;
        cout << "Press Enter to Finish...";
        cin.get();
    }
}