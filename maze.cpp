#include "maze.h"
#include <iostream>
using namespace std;

SquareMaze::SquareMaze()
{
//empty
}

void SquareMaze::makeMaze(int width, int height)
{
	w = width;
	h = height;
	DisjointSets connected;
	connected.addelements(width*height); // For cycle detection.
	std::vector< pair< int,  pair<int, int>  > > temp;
	for(int i = 0; i < width; i++)
	{
		vector< pair<bool,bool>  > row;
		for(int j = 0; j < height; j++)
		{
			pair<int, int> tmp(i,j);
	/*		tmp.first = i;
			tmp.second = j; */
			temp.push_back(std::make_pair(0, tmp)); // right
			temp.push_back(std::make_pair(1, tmp)); // down
			row.push_back(std::make_pair(true, true));
		}
		maze.push_back(row);
	}
	
	/*Ensures that we get a new maze most of the time.*/
	std::random_shuffle(temp.begin(), temp.end());
	
	for(std::vector< pair< int,  pair<int, int>  > >::iterator it = 
	temp.begin(); it != temp.end(); it++)
	{
		int x = it->second.first;
		int y = it->second.second;
		int d = it->first;
//		cout << "(" << x << "," << y << ")\n";
			switch(d)
			{
			case 0:
				if(x < width-1)
				{
					if(connected.find(y*width+x) != connected.find(y*width+x+1))
					{
						setWall(x, y, d, false);
						connected.setunion(y*width+x, (y*width+x+1));
					}
					else
					{
						setWall(x, y, d, true);
//						connected.setunion(x*y, (x*y)+1);
					}
				
				
				}
				break;
			case 1:
				if(y < height-1)
				{
				if(connected.find(y*width+x) != connected.find((y+1)*width+x))
					{
						setWall(x, y, d, false);
						connected.setunion(y*width+x, ((y+1)*width+x));
					}
					else
					{
						setWall(x, y, d, true);
//						connected.setunion(x*y, x*(y+1));
					}
				}
				break;
			default:
				cout << "No." << endl;
				return;
				break;
			}//switch
	}
	/*
	Note about the code commented below:
	This code is probably a little buggy and incomplete, but it's also a naive implementation.
	While for small mazes it's pretty useful, once the maze size gets sufficiently large,
	it's far too slow to consider using.
	*/
	
/*	srand(time(0));
	int rwidth = rand()%width;
	int rheight = rand()%height;*/
	
/*	for(int i = rwidth; i < width; i++)
	{
		for(int j = rheight; j < height; j++)
		{
			if(connected.find(i*j) != connected.find((i*j)+1) )
				setWall(i, j, 0, false);
			else
				setWall(i, j, 0, true);
			if( connected.find(i*j) != connected.find(i*(j+1)) )
				setWall(i, j, 1, false);
			else
				setWall(i, j, 1, true);
			
			connected.setunion(i*j, (i*j)+1);
			connected.setunion(i*j, (i*(j+1)));
		}
	}
	
	for(int k = 0; j > rwidth; k++)
	{
		for(int z = 0; z > rheight; z++)
		{
			if(connected.find(k*z) != connected.find((k*z)+1) )
				setWall(k, z, 0, false);
			else
				setWall(k,z, 0, true);
			if( connected.find(k*z) != connected.find(k*(z+1)) )
				setWall(k, z, 1, false);
			else
				setWall(k,z, 1, true);
				
			connected.setunion(k*z, (k*z)+1);
			connected.setunion(k*z, (k*(z+1)));
		}
	} */
	
	

}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
	//bool temp = false;
	switch(dir)
	{
		case 0:
		if(x < w)
			return !(maze[x][y].first);
			break;
		case 1:
		if(y < h)
			return !(maze[x][y].second);
			break;
		case 2:
			if(x != 0)
				return !(maze[x-1][y].first);
			break;
		case 3:
			if(y != 0)
				return !(maze[x][y-1].second);
			break;
		default:
			return false;
			break;
	}
	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{ // This segfaults currently. Possibly fixed?
		switch(dir)
		{
			case 0:
				maze[x][y].first = exists;
				break;
			case 1:
				maze[x][y].second = exists;
				break;
			default:
				return;
		}
}

vector<int> SquareMaze::solveMaze()
{
	vector<int> sol;
	vector <int> bestv;
	vector< vector<bool > > process;
	for(int i = 0; i < w; i++)
	{
		vector<bool> temp;
		for(int j = 0; j < h; j++)
		{
			temp.push_back(false);
		}
		process.push_back(temp);
	}
	solveMaze(sol, 0, 0, process, bestv);
	return bestv;
}

void SquareMaze::solveMaze(vector<int> & solution, int x, int y, vector< vector<bool > > & processing, vector<int> & best)
{
/*	if(! (canTravel(x, y, 0) || canTravel(x, y, 1) || canTravel(x, y, 2) || canTravel(x,y,3) ) )
	{
//		solution.push_back(dir);
		return solution;
	} */
	if(processing[x][y] == false)
	{
		processing[x][y] = true;
		if(canTravel(x,y,0))
		{
			solution.push_back(0);
			solveMaze(solution, x+1, y, processing, best);
			solution.pop_back();
	/*		if(solution.size() >= temp.size() && y == h)
				return solution;
			else
				return temp; */
		}

		if(canTravel(x,y,1))
		{
//			processing[x][y] = true;
			solution.push_back(1);
			solveMaze(solution, x, y+1, processing, best);
			solution.pop_back();
	/*		if(solution.size() >= temp.size() && y == h)
				return solution;
			else
				return temp; */
		}
	
		if(canTravel(x,y,2))
		{
//			processing[x][y] = true;
			solution.push_back(2);
			solveMaze(solution, x-1, y, processing, best);
			solution.pop_back();
	/*		if(solution.size() >= temp.size() && y == h)
				return solution;
			else
				return temp; */
		}
	
		if(canTravel(x,y,3))
		{
//			processing[x][y] = true;
			solution.push_back(3);
			solveMaze(solution, x, y-1, processing, best);
			solution.pop_back();
	/*		if(solution.size() >= temp.size() && y == h)
				return solution;
			else
				return temp; */
		}
	if(y == h-1 && solution.size() >= best.size())
		best = solution;
	}
}

PNG * SquareMaze::drawMaze() const
{
	PNG * theMaze = new PNG(w*10+1, h*10+1);
	
	for(int i = 0; i < w*10; i++)
	{
		(*theMaze)(i, 0)->red = 0;
		(*theMaze)(i, 0)->green = 0;
		(*theMaze)(i, 0)->blue = 0;		
	}
		
	for(int i = 0; i < h*10; i++)
	{
		(*theMaze)(0, i)->red = 0;
		(*theMaze)(0, i)->green = 0;
		(*theMaze)(0, i)->blue = 0;
	}
	
	for(int k = 1; k < 10; k++)
	{
		(*theMaze)(k,0)->red = 255;
		(*theMaze)(k,0)->green = 255;
		(*theMaze)(k,0)->blue = 255;
	}
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			if(maze[i][j].first)
			{
				for(int k = 0; k <= 10; k++)
				{
					(*theMaze)((i+1)*10,(j*10)+k)->red = 0;
					(*theMaze)((i+1)*10,(j*10)+k)->green = 0;
					(*theMaze)((i+1)*10,(j*10)+k)->blue = 0;
				}
			}
			if(maze[i][j].second)
			{
				for(int k = 0; k <= 10; k++)
				{
					(*theMaze)(i*10+k,(j+1)*10)->red = 0;
					(*theMaze)(i*10+k,(j+1)*10)->green = 0;
					(*theMaze)(i*10+k,(j+1)*10)->blue = 0;
				}
			}
		}
	}
//	PNG* theMazeptr = &theMaze;
	return theMaze;
}			
			

PNG * SquareMaze::drawMazeWithSolution()
{ // 0 = x+11 1 = y+11 2 = x-11 3 = y-11
	PNG * theMaze = drawMaze();
	vector<int> tmp = solveMaze();
	//GOGOGOGOGO
	int s = tmp.size();
	int x1 = 5;
	int y1 = 5;
	RGBAPixel red_kun; // red_kun
	red_kun.red = 255;
	red_kun.green = 0;
	red_kun.blue = 0;
	for(int i = 0; i < s; i++)
	{
		switch(tmp[i])
		{
			case 0:
			{
				int temp = x1+10;
				for(int k = x1; k <= temp; k++)
				{
					*(*theMaze)(k, y1) = red_kun;
				}
				x1 = x1+10;
				break;
			}
			case 1:
			{
				int temp = y1+10;
				for(int k = y1; k <= temp; k++)
				{
					*(*theMaze)(x1, k) = red_kun;
				}
				y1 = y1+10;
				break;
			}
			case 2:
			{
				int temp = x1-10;
				for(int k = temp; k <= x1; k++)
				{
					*(*theMaze)(k, y1) = red_kun;
				}
				x1 = x1-10;
				break;
			}
			case 3:
			{
				int temp = y1-10;
				for(int k = temp; k <= y1; k++)
				{
					*(*theMaze)(x1, k) = red_kun;
				}
				y1 = y1-10;
				break;
			}
			default:
				return theMaze;
		}
	}
	for(int i = 1; i < 10; i++)
	{
		(*theMaze)(x1-5+i,y1+5)->red = 255;
		(*theMaze)(x1-5+i,y1+5)->green = 255;
		(*theMaze)(x1-5+i,y1+5)->blue = 255;
	}
	return theMaze;
}
