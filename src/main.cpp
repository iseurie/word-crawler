#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>

#include "searchpool.hpp"
#include "ifparse.hpp"

using namespace std;
using namespace search;

int main(int argc, char* argv[]) {
    SearchPool pool;
    vector<string> terms;
    if(argc < 2) {
        int rows;
        int cols;
        string blob;

        vector<string> map;
        cout << "Enter row count: ";
        cin >> rows;
        if(!cin) {
            cerr << "Please enter a numerical value." << endl;
            return 1;
        }

        cout << "Enter column count: ";
        cin >> cols;
        if(!cin) {
            cerr << "Please enter a numerical value." << endl;
            return 1;
        }

        cout << "Enter character pool: ";
        cin >> blob;

        cout << "Enter terms to find, delimited with semicolons: ";
        string line;
        while(getline(cin, line, ';')) {
            terms.push_back(line);
        }
    } else if(argc == 2) {
        try {
            pool = read::read(string(argv[1]), &terms);
        } catch(const exception& e) {
            cerr << "Failed to read file: " << e.what() << endl;
            return 1;
        }
    } else {
        cout << "Too many arguments!" << endl;
        return 1;
    }

    for(int i = 0; i < terms.size(); ++i) {
        vector<array<point_s, 2>> hits = pool.find(terms[i]);
        if(hits.size() != 0) {
            cout << "Hit '" << terms[i] << ":'" << endl;
            for(int h = 0; h < hits.size(); ++h) {
                cout << '\t' << "At column " << hits[h][0].x 
                        << ", row " << hits[h][0].y
                        << " by vector " << hits[h][1].x 
                        << ", " << hits[h][1].y;
            }
        }
    }
}
