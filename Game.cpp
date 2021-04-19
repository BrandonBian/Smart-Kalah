#include "Game.h"
#include "Side.h"
#include "Board.h"
#include "Player.h"

Game::Game(const Board& b, Player* south, Player* north)
	:m_Board(b)
{
	/*
	Construct a Game to be played with the indicated players on a copy of the board b.
	The player on the south side always moves first.
	*/
		
	//m_Board = b;
	   	  
	m_SouthPlayer = south;
	m_NorthPlayer = north;
	m_MovesThisTurn = SOUTH; // South side always moves first.
}

void Game::display() const
{
	/*
	Display the game's board in a manner of your choosing, provided you show the names of
	the players and a reasonable representation of the state of the board.
	*/

	///////////// Print the North Player's name /////////////////

	std::cout << "      ";
	std::cout << m_NorthPlayer->name() << std::endl;

	///////////// Print the North holes /////////////////
	
	std::cout << "  ";
	for (int i = 1; i <= m_Board.holes(); i++)
		std::cout << " " << m_Board.beans(NORTH, i) << " ";
	std::cout << std::endl;

	///////////// Print the pots /////////////////

	std::cout << " "; // A space before the north pot
	std::cout << m_Board.beans(NORTH, 0); // Print the North pot

	for (int i = 1; i <= m_Board.holes(); i++)
		std::cout << "   ";
	std::cout << m_Board.beans(SOUTH, 0); // Print the South pot
	std::cout << std::endl;
	///////////// Print the South holes /////////////////

	std::cout << "  ";
	for (int i = 1; i <= m_Board.holes(); i++)
		std::cout << " " << m_Board.beans(SOUTH, i) << " ";
	std::cout << std::endl;
	///////////// Print the South Player's name /////////////////
	std::cout << "      ";
	std::cout << m_SouthPlayer->name() << std::endl;

}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	/*
	If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else.
	Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie.
	If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
	*/
	if (m_Board.beansInPlay(SOUTH) != 0 && m_Board.beansInPlay(NORTH) != 0)// Still has beans on each side, game not over
	{
		over = false;
		return;
	}
	
	over = true;

	//if the game is a tie
	if (m_Board.beans(SOUTH, 0) == m_Board.beans(NORTH, 0))
	{
		hasWinner = false;
		return;
	}

	//if the game has a winner
	if (m_Board.beans(SOUTH, 0) > m_Board.beans(NORTH, 0))
	{
		hasWinner = true;
		winner = SOUTH;
		return;
	}

	else
	{
		hasWinner = true;
		winner = NORTH;
		return;
	}


}

bool Game::move()
{
	/*
	If the game is over, return false. Otherwise, make a complete move for the player whose turn it is
	(so that it becomes the other player's turn) and return true.
	"Complete" means that the player sows the seeds from a hole and takes any additional turns required or
	completes a capture. If the player gets an additional turn,
	you should display the board so someone looking at the screen can follow what's happening.
	*/

	if (m_Board.beansInPlay(SOUTH) == 0 || m_Board.beansInPlay(NORTH) == 0)// Game is over
		return false;
	int moveChoice;
	Side endSide;
	int endHole;
	int beansCaptured;

	// Let the player makes a complete move/////////

	if (m_MovesThisTurn == SOUTH) // South player makes move
	{
		//std::cout << m_SouthPlayer->name() << " makes move" << std::endl;
		
		bool extraTurn = false;

		///////////////////// Make move and check if additional moves needed [Make A Complete Move] /////////////////////
		
		do
		{
			if (extraTurn == true)
			{
				std::cout << m_SouthPlayer->name() << "Gets Another Turn!" << std::endl;
				display(); // Display the game board
				std::cout << std::endl;
			}
			/// Make a move /// 
			moveChoice = m_SouthPlayer->chooseMove(m_Board, SOUTH);
			std::cout << m_SouthPlayer->name() << " chooses hole: " << moveChoice << std::endl;
			m_Board.sow(SOUTH, moveChoice, endSide, endHole);
					

			extraTurn = true;
		} 
		while (m_Board.beansInPlay(SOUTH) != 0 && m_Board.beansInPlay(NORTH) != 0
			&& endSide == SOUTH && endHole == 0);
			// While a move can be made AND the player has to make this move (because the last bean is put in own pot)
		
		///////////////////////////////////////////////////////////////
		/////////////////////// Capture?/////////////////////

		if (endSide == SOUTH && endHole != 0 && m_Board.beans(endSide,endHole)==1)
			// If the end hole is player's own hole, and it previously is empty (indicating now it should be only 1 bean)
		{
			
		
			if (m_Board.beans(NORTH, endHole) != 0)// If the opposite hole is not empty ----- Captures!
			{
				beansCaptured = m_Board.beans(NORTH, endHole);//Get the number of beans in the opposite hole
				beansCaptured++; // Plus the one bean in this end hole

				m_Board.moveToPot(SOUTH, endHole, SOUTH);
				m_Board.moveToPot(NORTH, endHole, SOUTH);
			}
		}
		
		//////////////////////////////////////////

		m_MovesThisTurn = NORTH; // Exchange the player who should go next turn
	}



	else // North player makes move
	{
		
		///////////////////// Make move and check if additional moves needed /////////////////////

		bool extraTurn = false;
		do
		{
			if (extraTurn == true)
			{
				std::cout << m_NorthPlayer->name() << " Gets Another Turn!" << std::endl;
				display(); // Display the game board
				std::cout << std::endl;
			}
			/// Make a move /// 
			moveChoice = m_NorthPlayer->chooseMove(m_Board, NORTH);
			std::cout << m_NorthPlayer->name() << " chooses hole: " << moveChoice << std::endl;
			m_Board.sow(NORTH, moveChoice, endSide, endHole);

			extraTurn = true;

		} while (m_Board.beansInPlay(SOUTH) != 0 && m_Board.beansInPlay(NORTH) != 0
			&& endSide == NORTH && endHole == 0);
		// While a move can be made AND the player has to make this move (because the last bean is put in own pot)

	///////////////////////////////////////////////////////////////
	/////////////////////// Capture?/////////////////////

		if (endSide == NORTH && endHole != 0 && m_Board.beans(endSide, endHole) == 1)
			// If the end hole is player's own hole, and it previously is empty (indicating now it should be only 1 bean)
		{
			//std::cout << "Capture! " << m_NorthPlayer->name()<<"Gets Another Turn!" << std::endl;
			
			if (m_Board.beans(SOUTH, endHole) != 0)// If the opposite hole is not empty ----- Captures!
			{
				beansCaptured = m_Board.beans(SOUTH, endHole);//Get the number of beans in the opposite hole
				beansCaptured++; // Plus the one bean in this end hole

				m_Board.moveToPot(SOUTH, endHole, NORTH);
				m_Board.moveToPot(NORTH, endHole, NORTH);
			}
		}

		//////////////////////////////////////////

		m_MovesThisTurn = SOUTH; // Exchange the player who should go next turn
	}
	
	
	display();
	std::cout << std::endl;

	//////////////////////////////////////////
	//////////////////////////////////////////
	//////////////Check to see if the game is over after this move

	if (m_Board.beansInPlay(SOUTH) == 0 || m_Board.beansInPlay(NORTH) == 0)// Game is over
	{
		for (int i = 1; i <= m_Board.holes(); i++)
		{
			if (m_Board.beans(SOUTH, i) != 0)// If there is beans left
			{
				//std::cout << "Sweeping beans in South holes to South pot" << std::endl;
				m_Board.moveToPot(SOUTH, i, SOUTH); // Move them into corresponding pot
			}

			if (m_Board.beans(NORTH, i) != 0)// If there is beans left
			{
				//std::cout << "Sweeping beans in North holes to North pot" << std::endl;
				m_Board.moveToPot(NORTH, i, NORTH); // Move them into corresponding pot
			}
		}
		std::cout << "Sweeping beans from holes to pots. Cleaning up the board." << std::endl;
		display();
		std::cout << std::endl;

	}
	


	
	return true;
}


void Game::play()
{
	/*
	Play the game. Display the progress of the game in a manner of your choosing,
	provided that someone looking at the screen can follow what's happening.
	If neither player is interactive, then to keep the display from quickly scrolling through the whole game,
	it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until
	ENTER is pressed. (The ignore function for input streams is useful here.)
	Announce the winner at the end of the game. You can apportion to your liking the responsibility for
	displaying the board between this function and the move function. (Note: If when this function is called,
	South has no beans in play, so can't make the first move,
	sweep any beans on the North side into North's pot and act as if the game is thus over.)
	*/
	
	bool gameOver = false;
	bool hasWinner = false;
	Side winner;

	if (m_Board.beansInPlay(SOUTH) == 0) // South side's holes are already empty
	{
		for (int i = 1; i <= m_Board.holes(); i++)
		{
			
			if (m_Board.beans(NORTH, i) != 0)// If there is beans left
			{
				m_Board.moveToPot(NORTH, i, NORTH); // Move them into corresponding pot
			}
		}

		display();

		std::cout << "		Game Over!" << std::endl;
		std::cout << "========================" << std::endl;
		std::cout << m_NorthPlayer->name() << " Wins!" << std::endl;
	}

	else if (m_Board.beansInPlay(NORTH) == 0) // North side's holes are already empty
	{
		for (int i = 1; i <= m_Board.holes(); i++)
		{

			if (m_Board.beans(SOUTH, i) != 0)// If there is beans left
			{
				m_Board.moveToPot(SOUTH, i, SOUTH); // Move them into corresponding pot
			}
		}

		display();


		std::cout << "		Game Over!" << std::endl;
		std::cout << "========================" << std::endl;
		std::cout << m_SouthPlayer->name() << " Wins!" << std::endl;
	}

	else
	{
		bool southPlayerInteractive = m_SouthPlayer->isInteractive();
		bool northPlayerInteractive = m_NorthPlayer->isInteractive();

		if (!southPlayerInteractive && !northPlayerInteractive) // Two computer players
		{
			std::cout << "		Game Start!" << std::endl;
			std::cout << "========================" << std::endl;
			display(); // Display the game board
			std::cout << std::endl;

			while (gameOver != true) // Game not over
			{

				std::cout << "Press ENTER to continue";
				std::cin.ignore(10000, '\n');

				move(); // Players take turns to make move

				std::cout << std::endl;

				status(gameOver, hasWinner, winner);// Check the game's status
			}

			std::cout << "		Game Over!" << std::endl;
			std::cout << "========================" << std::endl;

			if (hasWinner == false)//Game is a tie
				std::cout << "Game is a TIE" << std::endl;
			if (winner == SOUTH)
				std::cout << m_SouthPlayer->name() << " Wins!" << std::endl;
			if (winner == NORTH)
				std::cout << m_NorthPlayer->name() << " Wins!" << std::endl;

		}

		else
		{
			std::cout << "		Game Start!" << std::endl;
			std::cout << "========================" << std::endl;
			display(); // Display the game board
			std::cout << std::endl;

			while (gameOver != true) // Game not over
			{

				move(); // Players take turns to make move

				std::cout << std::endl;

				status(gameOver, hasWinner, winner);// Check the game's status
			}

			std::cout << "		Game Over!" << std::endl;
			std::cout << "========================" << std::endl;

			if (hasWinner == false)//Game is a tie
				std::cout << "Game is a TIE" << std::endl;
			if (winner == SOUTH)
				std::cout << m_SouthPlayer->name() << " Wins!" << std::endl;
			if (winner == NORTH)
				std::cout << m_NorthPlayer->name() << " Wins!" << std::endl;
		}
	}
}


int Game::beans(Side s, int hole) const
{
		
	return m_Board.beans(s, hole);
}