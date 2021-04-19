
#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif


#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;


//////////////////////////////////////



int main()
{
	Board board(3, 3);
	board.setBeans(SOUTH, 1, 0);
	board.setBeans(SOUTH, 2, 0);
	board.setBeans(SOUTH, 3, 0);
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	
	Game g(board, &bp1, &bp2);

	g.play();
}

