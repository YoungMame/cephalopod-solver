#include "board_hash.hpp"

// return the value of a square at l x c position from 0 to 9
int board_hash::getSquare(int line, int column, uint32_t board) {
    int index = line * 3 + column;
    return (board >> (index * 3)) & 0x7;  // 0x7 = 0b111 = 3 bits
}

// set the value of a square at l x c position from 0 to 9
void board_hash::setSquare(int line, int column, uint32_t &board, int value) {
    int index = line * 3 + column;
    int shift = index * 3;
    int mask = 0x7 << shift;
    board = (board & ~mask) | ((value & 0x7) << shift);
}


// return the hash of a given board and a given depth
// ( a 64 bits value, 32 bits for board, 32 bits for depth )
int64_t board_hash::getHashKey(uint32_t board, int depth) {
	return (((int64_t)board << 32) | depth);
}

// return the board stored inside a 64 bits value
uint32_t board_hash::getHashKeyBoard(int64_t hashKey) {
	return ((uint32_t)(hashKey >> 32));
}

// return the depth stored inside a 64 bits value
uint32_t board_hash::getHashKeyDepth(int64_t hashKey) {
	return ((uint32_t)hashKey);
}
