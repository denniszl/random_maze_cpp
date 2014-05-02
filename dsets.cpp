#include "dsets.h"

void DisjointSets::addelements(int num)
{
	for(int i = 0; i < num; i++)
		dset.push_back(-1);
}

int DisjointSets::find(int elem)
{
	if(dset[elem] < 0)
		return elem;
	else
		return dset[elem] = find(dset[elem]);
}

/*bool DisjointSets::isBigger(int rootA, int rootB) const
{
	return rootA <= rootB;
}*/

void DisjointSets::setunion(int a, int b)
{
	// My assumption here is that a and b are not the roots.
	int roota = find(a);
	int rootb = find(b);
	int newSize = dset[roota] + dset[rootb];
	if(dset[roota] <= dset[rootb])
	{
		dset[rootb] = roota;
		dset[roota] = newSize;
	}
	else
	{
		dset[roota] = rootb;
		dset[rootb] = newSize;
	}
}


