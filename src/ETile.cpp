/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 24/05/2020.
 */

#include "ETile.h"


int GetRank(int position) {
    return position / 10 - 2;
}

int GetFile(int position) {
    return position % 10 - 1;
}

int TileToIndex(const std::string & position) {
    if (position.length() != 2)
        return 0;

    if ('a' > position[0] || position[0] > 'h' || '1' > position[1] || position[1] > '8')
        return OFFBOARD;

    int file = position[0] - 'a';
    int rank = position[1] - '1';

    return 21 + file + rank * 10;
}

std::string IndexToTile(int index) {
    std::string res;
    int file = index % 10;
    int rank = index / 10;

    if (1 > file || file > 8 || 2 > rank || rank > 9)
        return "OFFBOARD";

    res.push_back(file - 1 + 'a');
    res.push_back(rank - 2 + '1');

    return res;
}

bool IsOffboard(int position) {
    if (position % 10 == 0 || position % 10 == 9)
        return true;
    if (0 <= position && position <= 19)
        return true;
    if (100 <= position && position <= 119)
        return true;
    return false;
}
