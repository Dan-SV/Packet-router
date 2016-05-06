#include "stdafx.h"
#include <string>
#include <vector>
#define PROUTER_H
using namespace std;
class pRouter
{
private:
	int aSegments[4][4];
	int dest[4];
	int subnetMask[4];
public:
	pRouter();
	pRouter(string table, string packets);
	void loadTable(string tablename);
	int routePacket(string packets);
	int compare(string s, int i);
	void message(string n, string t, int w);
};