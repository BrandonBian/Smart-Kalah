#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole) // Constructor
{
	//If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.

	m_NumOfHoles = nHoles;
	m_InitialBeans = nInitialBeansPerHole;

	if (nHoles <= 0)
		m_NumOfHoles= 1;
	if (nInitialBeansPerHole < 0)
		m_InitialBeans = 0;

	m_AllHoles = m_NumOfHoles + 1;// All holes = all normal holes + one pot (for each side)

	/////////////////////////////////////////////////
	// Initialize the empty pots for each side

	m_SouthHole.push_back(new Hole(SOUTH, 0, 0));

	m_NorthHole.push_back(new Hole(NORTH, 0, 0));


	/////////////////////////////////////////////////
	
	for (int i = 1; i < m_NumOfHoles+1; i++)
	{
		m_SouthHole.push_back(new Hole(SOUTH, i, m_InitialBeans)); // Initialize the South holes
	}

	for (int i = 1; i < m_NumOfHoles+1; i++)
	{
		m_NorthHole.push_back(new Hole(NORTH, i, m_InitialBeans)); // Initialize the North holes
	}

	/////////////////////////////////////////////////
	// Set up the Next pointers for these holes

	m_SouthHole[0]->setNextPtr(m_NorthHole[m_NumOfHoles]); // South pot's next hole is the last north hole
	m_NorthHole[0]->setNextPtr(m_SouthHole[1]); // North pot's next hole is the first south hole

	for (int j = 1; j <= m_NumOfHoles; j++)
	{
		m_NorthHole[j]->setNextPtr(m_NorthHole[j - 1]); // for North holes, the next hole is the previous North hole 
	}

	for (int j = 1; j < m_NumOfHoles; j++)
	{
		m_SouthHole[j]->setNextPtr(m_SouthHole[j + 1]); // for North holes, the next hole is the next South hole 
	}

	m_SouthHole[m_NumOfHoles]->setNextPtr(m_SouthHole[0]);// The last South hole's next hole is the South pot

	/////////////////////////////////////////////////
}


Board::Board(const Board& other) // Copy Constructor
{
	m_NumOfHoles = other.m_NumOfHoles;
	m_InitialBeans = other.m_InitialBeans;
	m_AllHoles = other.m_AllHoles;
	
	/////////////////////////////////////////////////
	// Initialize the empty pots for each side

	m_SouthHole.push_back(new Hole(SOUTH, 0, 0));

	m_NorthHole.push_back(new Hole(NORTH, 0, 0));


	/////////////////////////////////////////////////

	for (int i = 1; i < m_NumOfHoles + 1; i++)
	{
		m_SouthHole.push_back(new Hole(SOUTH, i, m_InitialBeans)); // Initialize the South holes
	}

	for (int i = 1; i < m_NumOfHoles + 1; i++)
	{
		m_NorthHole.push_back(new Hole(NORTH, i, m_InitialBeans)); // Initialize the North holes
	}

	/////////////////////////////////////////////////
	// Set up the Next pointers for these holes

	m_SouthHole[0]->setNextPtr(m_NorthHole[m_NumOfHoles]); // South pot's next hole is the last north hole
	m_NorthHole[0]->setNextPtr(m_SouthHole[1]); // North pot's next hole is the first south hole

	for (int j = 1; j <= m_NumOfHoles; j++)
	{
		m_NorthHole[j]->setNextPtr(m_NorthHole[j - 1]); // for North holes, the next hole is the previous North hole 
	}

	for (int j = 1; j < m_NumOfHoles; j++)
	{
		m_SouthHole[j]->setNextPtr(m_SouthHole[j + 1]); // for North holes, the next hole is the next South hole 
	}

	m_SouthHole[m_NumOfHoles]->setNextPtr(m_SouthHole[0]);// The last South hole's next hole is the South pot


	
	/////////////////////////////////////////////////
	// Give these copied holes their corresponding beans
	/////////////////////////////////////////////////

	for (int i = 0; i <= m_NumOfHoles; i++)
	{
		m_SouthHole[i]->removeAllBeans();
		m_SouthHole[i]->addBeans(other.m_SouthHole[i]->returnBeans()); // Give South holes thier beans
	}

	for (int i = 0; i <= m_NumOfHoles; i++)
	{
		m_NorthHole[i]->removeAllBeans();
		m_NorthHole[i]->addBeans(other.m_NorthHole[i]->returnBeans()); // Give South holes thier beans
	}
	

}


Board& Board::operator = (const Board& other) // Assignment Operator
{
	if (this != &other)
	{
		for (int i = 0; i < m_AllHoles; i++)
			delete m_SouthHole[i];
		for (int j = 0; j < m_AllHoles; j++)
			delete m_NorthHole[j];

		m_SouthHole.clear();
		m_NorthHole.clear();
		

		
		m_NumOfHoles = other.m_NumOfHoles;
		m_InitialBeans = other.m_InitialBeans;
		m_AllHoles = other.m_AllHoles;

		/////////////////////////////////////////////////
		// Initialize the empty pots for each side

		m_SouthHole.push_back(new Hole(SOUTH, 0, 0));

		m_NorthHole.push_back(new Hole(NORTH, 0, 0));


		/////////////////////////////////////////////////

		for (int i = 1; i < m_NumOfHoles + 1; i++)
		{
			m_SouthHole.push_back(new Hole(SOUTH, i, m_InitialBeans)); // Initialize the South holes
		}

		for (int i = 1; i < m_NumOfHoles + 1; i++)
		{
			m_NorthHole.push_back(new Hole(NORTH, i, m_InitialBeans)); // Initialize the North holes
		}

		/////////////////////////////////////////////////
		// Set up the Next pointers for these holes

		m_SouthHole[0]->setNextPtr(m_NorthHole[m_NumOfHoles]); // South pot's next hole is the last north hole
		m_NorthHole[0]->setNextPtr(m_SouthHole[1]); // North pot's next hole is the first south hole

		for (int j = 1; j <= m_NumOfHoles; j++)
		{
			m_NorthHole[j]->setNextPtr(m_NorthHole[j - 1]); // for North holes, the next hole is the previous North hole 
		}

		for (int j = 1; j < m_NumOfHoles; j++)
		{
			m_SouthHole[j]->setNextPtr(m_SouthHole[j + 1]); // for North holes, the next hole is the next South hole 
		}

		m_SouthHole[m_NumOfHoles]->setNextPtr(m_SouthHole[0]);// The last South hole's next hole is the South pot



		/////////////////////////////////////////////////
		// Give these copied holes their corresponding beans
		/////////////////////////////////////////////////

		for (int i = 0; i <= m_NumOfHoles; i++)
		{
			m_SouthHole[i]->removeAllBeans();
			m_SouthHole[i]->addBeans(other.m_SouthHole[i]->returnBeans()); // Give South holes thier beans
		}

		for (int i = 0; i <= m_NumOfHoles; i++)
		{
			m_NorthHole[i]->removeAllBeans();
			m_NorthHole[i]->addBeans(other.m_NorthHole[i]->returnBeans()); // Give South holes thier beans
		}

	}

	return *this;
}




Board::~Board() // Destructor
{
	for (int i = 0; i < m_AllHoles; i++)
		delete m_SouthHole[i];
	for (int j = 0; j < m_AllHoles; j++)
		delete m_NorthHole[j];

	m_SouthHole.clear();
	m_NorthHole.clear();

	//std::cerr << "deleted board" << std::endl;

}



int Board::holes() const
{
	return m_NumOfHoles;
}


int Board::beans(Side s, int hole) const
{
	
	if (hole<0 || hole>m_NumOfHoles)// If the hole number is invalid
		return -1;
	
	if (s == SOUTH)
		return m_SouthHole[hole]->returnBeans(); // Return the number of beans in South Hole

	else if (s == NORTH)
		return m_NorthHole[hole]->returnBeans(); // Return the number of beans in North Hole

	else
		return -1;// Invalid condition

}


int Board::beansInPlay(Side s) const
{
	////Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.

	int totalNorthBeans = 0;
	int totalSouthBeans = 0;

	if (s == SOUTH)
	{
		for (int i = 1; i <= m_NumOfHoles; i++)
			totalSouthBeans += m_SouthHole[i]->returnBeans();
		return totalSouthBeans;
	}

	else if (s == NORTH)
	{
		for (int i = 1; i <= m_NumOfHoles; i++)
			totalNorthBeans += m_NorthHole[i]->returnBeans();
		return totalNorthBeans;
	}

	else
		return -1; // Invalid condition
	
}


int Board::totalBeans() const
{
	////Return the total number of beans in the game, including any in the pots.

	int totalBeans = 0;

	for (int i = 0; i <= m_NumOfHoles; i++) // For the beans in South Holes
		totalBeans += m_SouthHole[i]->returnBeans();

	for (int i = 0; i <= m_NumOfHoles; i++) // For the beans in North Holes
		totalBeans += m_NorthHole[i]->returnBeans();

	return totalBeans;
}


bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	//If the hole indicated by (s,hole) is empty or invalid or a pot, 

	if (hole < 0 || hole > m_NumOfHoles)// Hole is invalid
		return false;

	if (hole == 0)// The hole is a pot
		return false;

	if (s == SOUTH) // South Holes
	{
		if (m_SouthHole[hole]->returnBeans() == 0)// No beans inside this hole, indicating an empty hole
			return false;
	}
	
	if (s == NORTH) // North Holes
	{
		if (m_NorthHole[hole]->returnBeans() == 0)// No beans inside this hole, indicating an empty hole
			return false;
	}

	//////////////////////////////// Remove the beans
	
	int beansRemoved; // Indicate the number of beans removed from this hole

	if (s == SOUTH) // South Holes
	{
		beansRemoved = m_SouthHole[hole]->returnBeans();// indicate the number of beans removed
		m_SouthHole[hole]->removeBeans(beansRemoved);//the beans are removed from hole (s,hole)
	}
					  
	if (s == NORTH) // North Holes
	{
		beansRemoved = m_NorthHole[hole]->returnBeans();// indicate the number of beans removed
		m_NorthHole[hole]->removeBeans(beansRemoved);//the beans are removed from hole (s,hole)
	}
	
	//////////////////////////////// Start Sowing

	if (s == SOUTH)// South Holes
	{
		Hole* holeToBeSowed = m_SouthHole[hole]->returnNextPtr(); // Indicate the hole to be sowed

		for (int x = 0; x < beansRemoved -1; x++) // For each bean removed (not yet made the last move)
		{
			if (holeToBeSowed == m_NorthHole[0]) //If the hole to be sowed is opponent's pot, skip it
			{
				holeToBeSowed = holeToBeSowed->returnNextPtr(); // Move to the following hole
				x--; // Bean not sowed
				continue;
			}
			holeToBeSowed->addBeans(1);// Add one bean to the hole to be sowed
			holeToBeSowed = holeToBeSowed->returnNextPtr();// Move to the following hole
		}// At this point, holeToBeSowed should point to the hole where the last bean goes to
		 
		if (holeToBeSowed == m_NorthHole[0]) //If the hole to be sowed is opponent's pot, skip it
			holeToBeSowed = holeToBeSowed->returnNextPtr(); // Move to the following hole
		holeToBeSowed->addBeans(1);// Add one bean to the hole to be sowed

		endSide = holeToBeSowed->returnSide(); // Record the end side
		endHole = holeToBeSowed->returnNumber(); // Record the end hole number

	}


	if (s == NORTH)// North Holes
	{
		Hole* holeToBeSowed = m_NorthHole[hole]->returnNextPtr(); // Indicate the hole to be sowed

		for (int x = 0; x < beansRemoved -1 ; x++) // For each bean removed (not yet made the last move)
		{
			if (holeToBeSowed == m_SouthHole[0]) //If the hole to be sowed is opponent's pot, skip it
			{
				holeToBeSowed = holeToBeSowed->returnNextPtr(); // Move to the following hole
				x--; // Bean not sowed
				continue;
			}
			holeToBeSowed->addBeans(1);// Add one bean to the hole to be sowed
			holeToBeSowed = holeToBeSowed->returnNextPtr();// Move to the following hole
		}

		if (holeToBeSowed == m_SouthHole[0]) //If the hole to be sowed is opponent's pot, skip it
			holeToBeSowed = holeToBeSowed->returnNextPtr(); // Move to the following hole
		holeToBeSowed->addBeans(1);// Add one bean to the hole to be sowed

		endSide = holeToBeSowed->returnSide(); // Record the end side
		endHole = holeToBeSowed->returnNumber(); // Record the end hole number


	}
	
	return true;
}


bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	////If the indicated hole is invalid or a pot, return false without changing anything.
	
	if (hole<0 || hole > m_NumOfHoles)// Hole is invalid
		return false;
	if (hole == 0)// The hole is a pot
		return false;

	
	///////////////////////////////////////////////
	//Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.

	int allTheBeans;

	if (s == SOUTH) // South Holes
	{
		allTheBeans = m_SouthHole[hole]->returnBeans(); // Get the number of all the beans in hole (s,hole)
		m_SouthHole[hole]->removeBeans(allTheBeans); // Remove all the beans from this hole
	}

	else // North Holes
	{
		allTheBeans = m_NorthHole[hole]->returnBeans(); // Get the number of all the beans in hole (s,hole)
		m_NorthHole[hole]->removeBeans(allTheBeans); // Remove all the beans from this hole
	}

	if (potOwner == SOUTH) // If potOwner is South player
		m_SouthHole[0]->addBeans(allTheBeans); // Add the beans into South player's pot (0 position)

	else// If potOwner is North player
		m_NorthHole[0]->addBeans(allTheBeans); // Add the beans into North player's pot (0 position)

		
	return true;
}


bool Board::setBeans(Side s, int hole, int beans)
{
	//If the indicated hole is invalid or beans is negative,
	if (hole<0 || hole > m_NumOfHoles)
		return false;

	if (beans < 0)
		return false;


	if (s == SOUTH)//South hole
	{
		m_SouthHole[hole]->setBeans(beans);
	}
	
	if (s == NORTH)//North hole
	{
		m_NorthHole[hole]->setBeans(beans);
	}
		
	
	return true;
}

