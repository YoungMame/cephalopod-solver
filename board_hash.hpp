#pragma once
#include <iostream>
#include <cstdint>

namespace board_hash {
	int			getSquare(int line, int column, uint32_t board);
	void		setSquare(int line, int column, uint32_t &board, int value);
	int64_t 	getHashKey(uint32_t board, int depth);
	uint32_t	getHashKeyBoard(int64_t hashKey);
	uint32_t	getHashKeyDepth(int64_t hashKey);
}