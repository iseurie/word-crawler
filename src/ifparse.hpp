#ifndef HXX_IFPARSE
#define HXX_IFPARSE

#include <vector>
#include <fstream>

#include "searchpool.hpp"

namespace read {
    enum error : unsigned short {
        err_not_open = 1,
        err_parsing_failed = 2
    };

    using namespace std;
    search::SearchPool read(const string& path, vector<string>* terms) {
        ifstream input;
        input.open(path);
        if(!input.is_open()) {
            throw err_not_open;
        }
        vector<string> map;

        int rows;

        input >> rows;
        map.resize(rows);

        for ( int i = 0; i < rows; i++ ) {
            input >> map[i];
        }
        while(input) {
            string term;
            input >> term;
            if ( term.length() > 0 ) {
                terms->push_back(term);
            }
        }

        return search::SearchPool(map);
    }
}
#endif
