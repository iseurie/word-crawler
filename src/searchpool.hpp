#ifndef HXX_SEARCHPOOL
#define HXX_SEARCHPOOL

#include <string>
#include <vector>
#include <array>

namespace search {
struct point_s {
    unsigned short x;
    unsigned short y;
};

class SearchPool {
    public:
        SearchPool();
        SearchPool(unsigned short& rows, unsigned short& cols, 
                std::string& blob);
        SearchPool(const std::vector<std::string>& map);
        std::vector<std::array<point_s, 2>> find(const std::string& term);
    private:
        std::vector<std::string> charMap;
        std::vector<point_s> scan(const point_s& point, 
                const std::string& term);
};


}

#endif
