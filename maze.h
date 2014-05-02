#include "dsets.h"

#ifndef _MAZE_H_
#define _MAZE_H_

class SquareMaze
{

	public: 

		SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
	
		vector<int> solveMaze();
		PNG * drawMaze() const;
		PNG * drawMazeWithSolution();
	
	private:
		
//		DisjointSets connected;
		std::vector< std::vector< std::pair<bool, bool> > > maze;
		int w;
		int h;
		void solveMaze(vector<int> & solution, int x, int y, vector< vector<bool > > & processing, vector<int> & best);
	//	PNG * theMaze;
	//	PNG * themaze;
	//	PNG * themazesol;
//		std::stack randomized;
};

#endif
