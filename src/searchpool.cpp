#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <sstream>

#include "searchpool.hpp"

using namespace std;

namespace search {

SearchPool::SearchPool() {
    this->charMap = vector<string>();
}

SearchPool::SearchPool(int rows, const char* blob ) {
    int cols = strlen(blob) / rows;
    charMap.resize(rows);
    for(int x = 0; x < rows; ++x) {
        for(int y = 0; y < cols; ++y) {
            charMap[x].insert(charMap[x].end(), blob[x*cols + y]);
        }
    }
}

SearchPool::SearchPool(const vector<string> map) {
    this->charMap = map;
}

vector<array<point_s, 2>> SearchPool::find(const string term) {
    vector<array<point_s, 2>> ret;
    for(int x = 0; x < charMap.size(); ++x) {
        for(int y = 0; y < charMap[0].size(); ++y) {
            for(int mx = 0; mx < 3; ++mx) {
                for(int my = 0; my < 3; ++my) {
                    if(mx + my == 0) break;
                    array<point_s, 2> p {
                            (point_s) { x, y },
                            (point_s) { (mx - 1), (my - 1) } };
                    if(streaks(p, term)) ret.push_back(p);
                }
            }
        }
    }
    return ret;
}

bool SearchPool::streaks(const array<point_s, 2> vec, string term) {
    for(int i = 0; i < term.length(); ++i) {
        int x = vec[0].x + vec[1].x * i;
        int y = vec[0].y + vec[1].y * i;
        if(y >= charMap.size() || y < 0) return false;
        if(x >= charMap[i].size() || x < 0) return false;
        if(charMap[y][x] != term[i]) return false;
    }
    return true;
}
}
