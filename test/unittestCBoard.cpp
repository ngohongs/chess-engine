/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 18/06/2020.
 */

#include <cassert>
#include "../src/CBoard.h"
#include "../src/FENTest.h"


int main() {
    // source: https://www.chessprogramming.org/Perft_Results
    CBoard test;
    assert(test.ReadFEN(START_FEN));
    assert(test.PerftTest(1) == 20);
    assert(test.PerftTest(2) == 400);
    assert(test.PerftTest(3) == 8902);

    assert(test.ReadFEN(PERFT1));
    assert(test.PerftTest(1) == 48);
    assert(test.PerftTest(2) == 2039);
    assert(test.PerftTest(3) == 97862);

    assert(test.ReadFEN(PERFT2));
    assert(test.PerftTest(1) == 14);
    assert(test.PerftTest(2) == 191);
    assert(test.PerftTest(3) == 2812);
    assert(test.PerftTest(4) == 43238);

    assert(test.ReadFEN(PERFT3));
    assert(test.PerftTest(1) == 6);
    assert(test.PerftTest(2) == 264);
    assert(test.PerftTest(3) == 9467);

    assert(test.ReadFEN(PERFT4));
    assert(test.PerftTest(1) == 6);
    assert(test.PerftTest(2) == 264);
    assert(test.PerftTest(3) == 9467);

    assert(test.ReadFEN(PERFT5));
    assert(test.PerftTest(1) == 44);
    assert(test.PerftTest(2) == 1486);
    assert(test.PerftTest(3) == 62379);
  
    assert(test.ReadFEN(PERFT6));
    assert(test.PerftTest(1) == 46);
    assert(test.PerftTest(2) == 2079);
    assert(test.PerftTest(3) == 89890);

    return 0;
}
