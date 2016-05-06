// packetRouter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pRouter.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	pRouter("rtable.txt", "s1.txt");
	cin.ignore();
	return 0;
}

