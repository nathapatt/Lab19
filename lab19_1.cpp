#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream source;
    source.open(filename);
    string textline;
    int a,b,c;
    char name[100];
    while(getline(source,textline)){
        char format[] = "%[^:]: %d %d %d";
        sscanf(textline.c_str(),format,name,&a,&b,&c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
}


void getCommand(string &command,string &key){
    cout << "Please input your command: ";
    string x;
    char cc[100],kk[100];
    getline(cin,x);
    char format[] = "%s %[^\n]";
    sscanf(x.c_str(),format,cc,kk);
    command = cc;
    key = kk;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned i=0;i<names.size();i++){
        string x =toUpperStr(names[i]);
        if(x==key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            found = true;
        }
    }
    if(!found)
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned i=0;i<names.size();i++){
        char y = toupper(grades[i]);
        char z = key[0];
        if(y == z){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found)
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}