#ifndef HXX_SEARCHPOOL
#define HXX_SEARCHPOOL

#include <string>
#include <vector>
#include <array>

namespace search {
struct point_s {
    int x, y;
};

class SearchPool {
    public:
        SearchPool();
        SearchPool(int rows, const char* blob);
        SearchPool(const std::vector<std::string> map);
        std::vector<std::array<point_s, 2>> 
                find(const std::string term);
    private:
        std::vector<std::string> charMap;
        bool streaks(const std::array<point_s, 2> vec, std::string term);
};


}

#endif
