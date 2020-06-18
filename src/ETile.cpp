/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 24/05/2020.
 */

#include "ETile.h"


int GetRank(int position) {
    // board is represented by 1D array, one row is long 10 elements
    // indexes from 0 - 19 and 100 - 119 used as borders for board
    // rank is the second digit of the position, however, first on board position is indexed by 21
    // for easier use (indexing in an array) rank is decremented by 2
    return position / 10 - 2;
}

int GetFile(int position) {
    // board is represented by 1D array, one row is long 10 elements
    // indexes with first digit 0 and 9 used as borders for board
    // file is the first digit of the position, however, first on board position is indexed by 21
    // for easier use (indexing in an array) file is decremented by 1
    return position % 10 - 1;
}

int TileToIndex(const std::string & position) {
    if (position.length() != 2)
        return OFFBOARD;

    if ('a' > position[0] || position[0] > 'h' || '1' > position[1] || position[1] > '8')
        return OFFBOARD;

    int file = position[0] - 'a';
    int rank = position[1] - '1';

    // board is represented by 1D array, one row is long 10 elements
    // first position start at 21
    return 21 + file + rank * 10;
}

std::string IndexToTile(int index) {
    std::string res;
    // rank is second digit
    int file = index % 10;
    // rank is first digit
    int rank = index / 10;


    if (1 > file || file > 8 || 2 > rank || rank > 9)
        return "OFFBOARD";

    res.push_back(file - 1 + 'a');
    res.push_back(rank - 2 + '1');

    return res;
}

bool IsOffBoard(int position) {
    // indexes from 0 - 19 and 100 - 119 used as borders for board
    // indexes with first digit 0 and 9 used as borders for board
    if (position % 10 == 0 || position % 10 == 9)
        return true;
    if (0 <= position && position <= 19)
        return true;
    if (100 <= position && position <= 119)
        return true;
    return false;
}
