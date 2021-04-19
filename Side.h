#ifndef SIDE_H
#define SIDE_H

#include <iostream>
#include <vector>
#include <algorithm>

class Board;

// It may contain additional types, constants, and non-member function declarations you find useful to add.

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
	return Side(NSIDES - 1 - s); // Returns the opposite side of the side passed in
}


//publicly accessible functionality 
////////////////////////////////




////////////////////////////////
class Hole
{
public:
	Hole(Side side, int sequence, int beans)
		:m_Side(side),m_Number(sequence),m_Beans(beans),m_Next(nullptr){}

	
	/*
	
	~Hole()
	{
		std::cerr << "Deleted a Hole" << std::endl;
	}
	
	*/
	

	Side returnSide() const
	{
		return m_Side; // Return the side this hole is on
	}

	int returnNumber() const
	{
		return m_Number; // Return the sequence number of this hole (0 means a pot)
	}

	int returnBeans() const
	{
		return m_Beans; // Return the number of beans in this hole
	}

	void addBeans(int num) // Add num beans into this hole
	{
		m_Beans += num; 
	}

	void setBeans(int num) // Set the number of beans in this hole to num
	{
		m_Beans = num;
	}

	void removeBeans(int num)// Remove num beans from this hole
	{
		m_Beans -= num;
	}

	void setNextPtr(Hole* next) // Set the pointer to the next hole
	{
		m_Next = next;
	}

	Hole* returnNextPtr() // Return the pointer that points to the next hole
	{
		return m_Next;
	}

	void removeAllBeans() // Remove all the beans from this hole
	{
		m_Beans = 0;
	}

private:
	Side m_Side; // The side this hole is on
	int m_Number; // The sequence number of this hole
	int m_Beans; // The number of beans in this hole

	Hole* m_Next; // Pointer to next hole
};





#endif