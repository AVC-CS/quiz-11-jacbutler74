#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
int rewritesplitwords(string filename, char delim);
string MFN(string stname, int thisyear);

struct Name{
        string stname;
        string gender;
        string name;
        int year;
        int count;
};

int rewritesplitwords(string filename, char delim) {
    ifstream ifs;
    ofstream ofs;
    vector<Name> n;
    struct Name name;
    stringstream sline;
    string line, num;
    int count = 0;
    ifs.open(filename);

    if(ifs.is_open()) {
        while (getline(ifs, line)) {
            sline << line;
            getline(sline, name.stname, delim);
            getline(sline, name.gender, delim);
            getline(sline, num, delim);
            name.year = stoi(num);
            getline(sline, name.name, delim);
            getline(sline, num, delim);
            name.count = stoi(num);
            n.push_back(name);
            ++count;
            sline.str(" ");
            sline.clear(); 
        }
    }

    ofs.open("split.txt");
    if(ofs.is_open()) {
        for (int i = 0; i < count; ++i) {
            ofs << n[i].stname << "\t" << n[i].gender << "\t" << n[i].year << "\t" << n[i].name << "\t" << n[i].count << endl;
        }
    }
    
    return count;
}

string MFN(string stname, int thisyear) {
    ifstream ifs;
    stringstream str;
    string state, name, line, temp, maxname;
    int year, max = 0, count;

    ifs.open("split.txt");

    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            str << line;
            str >> state >> temp >> year >> name >> count;
            if ((state == stname) && (year == thisyear) && (count > max)) {
                max = count;
                maxname = name;
            }
            str.str(" ");
            str.clear();
        }
    }

    return maxname;
}