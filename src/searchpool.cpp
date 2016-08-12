#include <string>
#include <functional>
#include <vector>
#include <cmath>
#include <array>

#include "searchpool.hpp"

using namespace std;

namespace search {

SearchPool::SearchPool() {
    this->charMap = vector<string>();
}

SearchPool::SearchPool(unsigned short& rows, unsigned short& cols,
        string& blob) {
    for(int x = 0; x < rows; ++x) {
        for(int y = 0; y < cols; ++y) {
            if(x + y <= blob.length()) {
                charMap[x][y] = blob.c_str()[x + y];
            } else {
                charMap[x][y] = '\0';
            }
        }
    }
    this->charMap = charMap;
}

SearchPool::SearchPool(const vector<string>& map) {
    this->charMap = map;
}

vector<array<point_s, 2>> SearchPool::find(const string& term) {
    vector<array<point_s, 2>> ret;
    for(unsigned short x = 0; x < charMap.size(); ++x) {
        for(unsigned short y = 0; charMap[0].size(); ++y) {
            vector<point_s> hits = scan((point_s){x, y}, term);
            for(unsigned short i = 0; i < hits.size() / term.length(); ++i) {
                array<point_s, 2> p;
                if(hits.size() - i * term.length() > term.length()) {
                    p[0] = hits[0];
                    p[1] = (point_s) {
                        abs(hits[1].x - hits[0].x),
                        abs(hits[1].y - hits[0].y) }; 
                } else {
                    p[0] = (point_s) { 0, 0 };
                    p[1] = (point_s) { 0, 0 };
                }
                ret.push_back(p);
            }
            return ret;
        }
    }
}

vector<point_s> SearchPool::scan(const point_s& point, const string& term) {
    vector<point_s> ret;
    char map[3][3];

    for(int x = 0; x < charMap.size(); ++x) {
        for(int y = 0; y < charMap[0].size(); ++y) {
            for(int mx = 0; mx < 3; ++mx) {
                for(int my = 0; my < 3; ++my) {
                    map[mx][my] = charMap
                            [(point.x - 1) + mx]
                            [(point.y - 1) + my];
                }
            }
        }
    }

    for(int mx = 0; mx < 3; ++mx) {
        for(int my = 0; my < 3; ++my) {
            if(map[mx][my] == term[mx + my]) {
                ret.push_back((point_s) {
                    (point.x - 1) + mx,
                    (point.y - 1) + my });
            }
        }
    }
}
}
