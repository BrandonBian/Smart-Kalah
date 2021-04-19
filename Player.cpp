#include "Player.h"

Player::Player(std::string name)//Create a Player with the indicated name.
{
	m_Name = name;
}

std::string Player:: name() const//Return the name of the player.
{
	return m_Name;
}


bool Player::isInteractive() const // Virtual
{
	//Return false if the player is a computer player.
	//Return true if the player is human. Most kinds of players will be computer players.
	
	return false; // Default return false, only human player returns true
}

Player::~Player()// Virtual Destructor
{

}


////////////////////////////////////////////////
//Human Player implementations

HumanPlayer::HumanPlayer(std::string name) // Constructor
	:Player(name){
}


bool HumanPlayer::isInteractive() const
{
	return true;//Return true if the player is human (only HumanPlayer::isInteractive should return true)
}

int HumanPlayer::chooseMove(const Board& b, Side s) const// the Human player chooses move
{
	//If no move is possible, return -1.
	if (b.beansInPlay(s) == 0) // No beans in this side's hole
		return -1;

	
	//prompting a person running the program for a move 
	//(reprompting if necessary until the person enters a valid hole number)
	//and returning that choice.

	int choice;
	
	std::cout << "What is your move (Input a VALID hole number which HAS BEANS inside): ";
	std::cin >> choice;
	std::cin.ignore(10000, '\n');

	while (choice <= 0 || choice > b.holes() || b.beans(s, choice) == 0) // Invalid choice
	{
		std::cout << "Invalid move! Please choose another hole: ";
		std::cin >> choice;
		std::cin.ignore(10000, '\n');
	}
	
	return choice;
	
}


////////////////////////////////////////////////
//BadPlayer implementations


BadPlayer::BadPlayer(std::string name) // Constructor
	:Player(name) {
}

int BadPlayer::chooseMove(const Board& b, Side s) const// the Bad computer player chooses move
{
	//If no move is possible, return -1.
	if (b.beansInPlay(s) == 0) // No beans in this side's hole
		return -1;

	// Arbitrary Default: chooses the valid hole with least sequence number

	for (int i = 1; i <= b.holes(); i++) // Go through all the holes (except for the pot) on one side
	{
		if (b.beans(s, i) != 0) // If this hole has beans in it
			return i;
	}
	
	return -1;


}



////////////////////////////////////////////////
//SmartPlayer implementations

SmartPlayer::SmartPlayer(std::string name) // Constructor
	:Player(name) {
}

int SmartPlayer::chooseMove(const Board& b, Side s) const// the Smart computer player chooses move
{
	//If no move is possible, return -1.
	if (b.beansInPlay(s) == 0) // No beans in this side's hole
		return -1;


	
	/*
	/////////////////////////// Same as Bad Player - FOR NOW!
	// Arbitrary Default: chooses the valid hole with least sequence number

	for (int i = 1; i <= b.holes(); i++) // Go through all the holes (except for the pot) on one side
	{
		if (b.beans(s, i) != 0) // If this hole has beans in it
			return i;
	}

	return -1;
	
	*/



	///////////////////////////////////////////////////////////////////////////////////////////////////

	int bestHole; // Indicate the best Hole to sow from

	for (int k = 1; k <= b.holes(); k++)
	{
		if (b.beans(s, k) != 0)
			bestHole = k;
	}

	Side mySide = s;


	Board testBoard(b); // Make a copy of the board so can modify without altering the original one

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Find the Best Move
	///////////////////////////////////////////////////////////////////////////////////////////////////

//	int bestHole;
	int bestValue = -1000;

	for (int i = 1; i <= testBoard.holes(); i++) // For each hole
	{
		// We make a move///////////////////////////////////////////////////////

		if (testBoard.beans(s, i) != 0) // If the hole can be sowed (i.e. it is not empty)
		{

			///////////////////// Make move and check if additional moves needed [Make A Complete Move] /////////////////////

			makeCompleteMove(testBoard, s, i);


			// compute evaluation function for this move.

			int value = minimax(testBoard, 0, opponent(s), mySide);

			// Unmake the move
			testBoard = b;

			// If the current value is larger than best value, then update best value
			if (value > bestValue)
			{
				bestValue = value;
				bestHole = i;// Update the best hole to indicate this hole number
			}

		}

	}

	return bestHole; // Return the choice --- that is, the hole with the best evaluated value



}





////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SmartPlayer::evaluate(const Board& b, Side s) const // Evaluate the value when Side s is the maximizer's side
{
	int returnValue = 0;

	returnValue += 10 * (b.beans(s, 0) - b.beans(opponent(s), 0));
	//The greater the difference between the number of beans in my pot and the number in my opponent's, the better

	returnValue += b.beansInPlay(s); // More beans in maximizer's hole, the better
	returnValue -= b.beansInPlay(opponent(s)); // More beans in maximizer's hole, the better

	return returnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SmartPlayer::minimax(Board&b, int depth, Side s, Side mySide) const
{
	Board testBoard(b);

	int score = evaluate(testBoard, mySide);

	if (depth > 4) // We only run this many in depth
		return score;



	if (testBoard.beansInPlay(SOUTH) == 0 || testBoard.beansInPlay(NORTH) == 0) // The game is over
	{

		if (testBoard.beans(mySide, 0) > testBoard.beans(opponent(mySide), 0)) // I win
			score += 9999;
		if (testBoard.beans(mySide, 0) < testBoard.beans(opponent(mySide), 0)) // I lose
			score -= 9999;

		return score;
	}


	if (s == mySide) // Then Side s is the maximizer
	{
		int best = -1000;
		for (int i = 1; i <= testBoard.holes(); i++) // For each hole
		{
			// We make a move///////////////////////////////////////////////////////

			if (testBoard.beans(s, i) != 0) // If the hole can be sowed (i.e. it is not empty)
			{


				//Board original(testBoard);// Record the board before the move

				//// Make a complete move
				makeCompleteMove(testBoard, s, i);

				// Call minimax recursively and choose the maximum value 
				best = std::max(best, minimax(testBoard, depth + 1, opponent(s), mySide));

				// Undo the move

				testBoard = b;
			}

		}

		return best;
	}


	else // Then Side s is the minimizier (opponent)
	{
		int best = 1000;
		for (int i = 1; i <= testBoard.holes(); i++) // For each hole
		{
			if (testBoard.beans(s, i) != 0) // If the hole can be sowed (i.e. it is not empty)
			{
				// Opponent makes a move

				makeCompleteMove(testBoard, s, i); // Make a move

				// Call minimax recursively and choose the minimum value 
				best = std::min(best, minimax(testBoard, depth + 1, opponent(s), mySide));

				// Undo the move

				testBoard = b;
			}

		}

		return best;
	}


}

void SmartPlayer::makeCompleteMove(Board& board, Side side, int hole) const
{
	if (board.beansInPlay(SOUTH) == 0 || board.beansInPlay(NORTH) == 0)// Game is over
		return;
	
	
	int moveChoice = hole;
	Side endSide=opponent(side);
	int endHole;

	bool extraTurn = false;

	///////////////////// Make move and check if additional moves needed [Make A Complete Move] /////////////////////

	
	do
	{
		/// Make a move ///
		if (extraTurn)
		{
			int maxValue = -100000;
			for (int j = 1; j <= board.holes(); j++)
			{
				Board boardCopy(board);

				makeCompleteMove(boardCopy, side, j); // "Makes" a complete move
				int value = evaluate(boardCopy, side); // And evaluate how good this move is

				if (value > maxValue) // If this is the best move it can be
				{
					maxValue = value;
					moveChoice = j; // Select this move
				}

				board = boardCopy; // "Unmake" the move
			}


		}

		board.sow(side, moveChoice, endSide, endHole);
		extraTurn = true;

	} while (board.beansInPlay(side) != 0 && board.beansInPlay(opponent(side)) != 0
		&& endSide == side && endHole == 0);
	   	
	

	// While a move can be made AND the player has to make this move (because the last bean is put in own pot)

	//board.sow(side, moveChoice, endSide, endHole);

	///////////////////////////////////////////////////////////////
	/////////////////////// Capture?/////////////////////

	if (endSide == side && endHole != 0 && board.beans(endSide, endHole) == 1)
		// If the end hole is player's own hole, and it previously is empty (indicating now it should be only 1 bean)
	{
		if (board.beans(opponent(side), endHole) != 0)// If the opposite hole is not empty ----- Captures!
		{

			board.moveToPot(side, endHole, side);
			board.moveToPot(opponent(side), endHole, side);
		}
	}


	////////////////////////////////////////// Move Ended		

}


