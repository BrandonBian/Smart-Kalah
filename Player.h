#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include "Side.h"

class Player
{

public:

	Player(std::string name);
	//Create a Player with the indicated name.

	std::string name() const;
	//Return the name of the player.

	virtual bool isInteractive() const;
	//Return false if the player is a computer player.
	//Return true if the player is human. Most kinds of players will be computer players.


	virtual int chooseMove(const Board& b, Side s) const = 0;
	//Every concrete class derived from this class must implement this function so that 
	//if the player were to be playing side s and had to make a move given board b,
	//the function returns the move the player would choose. If no move is possible, return -1.


	virtual ~Player();
	//Since this class is designed as a base class, it should have a virtual destructor.


private:

	std::string m_Name;// Player's name

};

/*
A HumanPlayer chooses its move by prompting a person running the program for a move 
(reprompting if necessary until the person enters a valid hole number), and returning that choice.
We will never test for a situation where the user doesn't enter an integer when prompted for a hole number. 
(The techniques for dealing with the issue completely correctly are a distraction to this project, 
and involve either a function like stoi or strtol, or the type istringstream.)
*/


class HumanPlayer :public Player
{
public:
	
	HumanPlayer(std::string name); // Constructor

	virtual bool isInteractive() const;//Return true if the player is human.

	virtual int chooseMove(const Board& b, Side s) const; // the Human player chooses move
};


/*
A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. 
"Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. 
The point of this class is to have an easy-to-implement class that at least plays legally.
*/

class BadPlayer :public Player
{
public:

	BadPlayer(std::string name); // Constructor

	virtual int chooseMove(const Board& b, Side s) const; // the Bad computer player chooses move
};


class SmartPlayer :public Player
{
public:

	SmartPlayer(std::string name); // Constructor

	virtual int chooseMove(const Board& b, Side s) const; // the Smart computer player chooses move


private:
	
	int evaluate(const Board& b, Side s) const; // Evaluate the value (give a high value for a board if maximizer (Side s)'s turn 
								//or a low value for the board if minimizer's turn)
	
	int minimax(Board&b, int depth, Side s, Side mySide) const;// It considers all 
// the possible ways the game can go and returns 
// the value of the board 

	///int findBestMove(Board& b, Side s, Side mySide) const;

	void makeCompleteMove(Board& board, Side side, int hole) const;

};



#endif