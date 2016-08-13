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

        cout << "Enter table contents: ";
        cin >> blob;
        pool = SearchPool(rows, blob.c_str());

        cout << "Enter terms to find, delimited with ';': ";
        string termBufStr;
        cin >> termBufStr;
        stringstream termBuf(termBufStr);
        for(string term; getline(termBuf, term, ';'); terms.push_back(term));
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
        if(hits.size() > 0) {
            cout << "Hit '" << terms[i] << "': " << endl;
            for(int i = 0; i < hits.size(); ++i) {
                cout << '\t' << "at column " << hits[i][0].x 
                        << ", row " << hits[i][0].y
                        << " by vector (" << hits[i][1].x 
                        << ", " << hits[i][1].y << ')';
                if(i <= hits.size()) cout << ';';
                cout << endl;
            }
        } else {
            cout << "Term '" << terms[i] << "' not found" << endl;
        }
    }
}
