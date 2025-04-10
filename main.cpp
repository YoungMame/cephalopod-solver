#include <cstdint>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "board_hash.hpp"
using namespace std;
using namespace board_hash;

//global variables
std::unordered_set<uint32_t>	finalBoards;
std::unordered_map<int64_t, bool> triedBoards;

struct Pos {
	int x, y;
};

void    hitRecursivly(int depth, uint32_t board);

bool	isPlateEnded(uint32_t board)
 {
 	for (int i = 0; i < 3; i++)
 	{
 		for (int j = 0; j < 3; j++)
 		{
 			if (getSquare(i, j, board) == 0)
 				return (false);
 		}
 	}
 	return (true);
 }

// trying all solutions possible on the current pos
// including capture and non capture
void hitSolutions(int depth, uint32_t board, int l, int c) {
    std::vector<Pos> container;
    bool isEdited = false;
    bool isAlone = true;

    if (l > 0) container.push_back({l - 1, c});
    if (l < 3 - 1) container.push_back({l + 1, c});
    if (c > 0) container.push_back({l, c - 1});
    if (c < 3 - 1) container.push_back({l, c + 1});

    int size = container.size();
    for (int firstSideIndex = 0; firstSideIndex < size; firstSideIndex++) {
        for (int sidesCount = firstSideIndex + 1; sidesCount < size; sidesCount++) {
            int sum = 0;
            int validCount = 0;
            uint32_t boardCopy = board;
            uint32_t editedBoard = boardCopy;

            for (int sideIndex = 0; sideIndex <= sidesCount - firstSideIndex; sideIndex++) {
                int squareValue = getSquare(container[firstSideIndex + sideIndex].x, container[firstSideIndex + sideIndex].y, boardCopy);
                if (sum + squareValue > 6)
                    break;
                if (squareValue > 0) {
                    sum += squareValue;
                    validCount++;
                    isEdited = true;
                    setSquare(container[firstSideIndex + sideIndex].x, container[firstSideIndex + sideIndex].y, editedBoard, 0);
                }
            }
			if (isEdited && validCount > 1)
			{
				
				boardCopy = editedBoard;
				setSquare(l, c, boardCopy, sum);
				if (depth == 0 || isPlateEnded(boardCopy))
					return (finalBoards.insert(boardCopy), static_cast<void>(0));
				else
				{
					isAlone = false;
					hitRecursivly(depth - 1, boardCopy);
				}
			}
        }
    }

    if (isAlone) {
        setSquare(l, c, board, 1);
        if (depth < 0 || isPlateEnded(board)) {
            finalBoards.insert(board);
        } else {
            hitRecursivly(depth - 1, board);
        }
    }
}

// call hitSolutions on all empty squares
void    hitRecursivly(int depth, uint32_t board)
{
	int64_t key = getHashKey(board, depth);
	std::vector<int> emptySquares;
	if (triedBoards[key])
		return;
	int i = 0;
	while (i < 3)
	{
		int 	j = 0;
		while (j < 3)
		{
			if (getSquare(i, j, board) == 0)
			{
				hitSolutions(depth, board, i, j);
			}
			j++;
		}
		i++;
	}
	triedBoards[key] = true;
}

// logs a 32 bits board
void	showBoard(uint32_t board)
{
	
	std::cout << "___" << std::endl
	<< 			getSquare(0, 0, board)
	<< 			getSquare(0, 1, board)
	<< 			getSquare(0, 2, board)
	<<			std::endl
	<< 			getSquare(1, 0, board)
	<< 			getSquare(1, 1, board)
	<< 			getSquare(1, 2, board)
	<<			std::endl
	<< 			getSquare(2, 0, board)
	<< 			getSquare(2, 1, board)
	<< 			getSquare(2, 2, board)
	<<			std::endl
	<<			"___"
	<< 			std::endl;
}

int main()
{
    uint32_t board = 0;
    int depth;
    cin >> depth; cin.ignore();
    for (int i = 0; i < 9; i++) {
        int value;
        cin >> value;

		setSquare(i / 3, i % 3, board, value);
        cin.ignore();
    }
	hitRecursivly(depth, board);
	for (std::unordered_set<uint32_t>::iterator it = finalBoards.begin(); it != finalBoards.end(); it++)
	{
		showBoard(*it);
	}

    return (1);
}