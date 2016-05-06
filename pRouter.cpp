#include "stdafx.h"
#include <string>
#include "pRouter.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <bitset>
#include <sstream>

using namespace std;
	pRouter::pRouter()
	{
		ofstream table;
		ofstream packets;
	}
	pRouter::pRouter(string fileT, string fileP)
	{
		subnetMask[0]=255;
		subnetMask[1]=255;
		subnetMask[2]=255;
		subnetMask[3]=0;
		loadTable(fileT);
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
				cout<<aSegments[i][j]<<".";
			cout<<endl;
		}
		routePacket(fileP);
	}
	void pRouter::loadTable(string fileT)
	{
		ifstream table;
		table.open(fileT);
		string line;
		int iNum=0;
		if(table.is_open())
				while(getline(table, line))
				{
					string address;
					string interface;
					address= line.substr(0, line.find(":"));
					line.erase(0, 1+line.find(":"));
					interface= line;
					string str;
					for(int i=0; i<4; i++)
					{
						str=address.substr(0, address.find("."));
						aSegments[iNum][i]=atoi(str.c_str());
						address.erase(0, 1+address.find("."));
					}
					iNum++;
				}
		table.close();
	}
	int pRouter::routePacket(string fileP)
	{
		ifstream packets;
		packets.open(fileP);
		string line;
		if(packets.is_open())
			while(getline(packets, line))
			{
				int i=-1;
				int iResult;
				do{
					++i;
					iResult=compare(line, i);
					//cout<<"output of comparison: "<<iResult<<endl;
				}while(!iResult);
				stringstream destAddress;
				destAddress<<aSegments[i][0]<<'.'<<aSegments[i][1]<<'.'<<aSegments[i][2]<<'.'<<aSegments[i][3]<<'.';
				string da=destAddress.str();
				message(line, da, i);
			}
		return 0;
	}
	int pRouter::compare(string line, int s)
	{
		//cout<<"Comparing"<<line<<" To interface "<<s<<endl;
		for(int i=0; i<4; i++)
		{
			//cout<<"mask "<<subnetMask[i]<<endl;
			//cout<<"table "<<aSegments[s][i]<<endl;
			//cout<<"dest "<<line<<endl;
			bitset<8> mask(subnetMask[i]);
			bitset<8> tableBits(aSegments[s][i]);
			bitset<8> destBits(atoi(line.substr(0, line.find(".")).c_str()));
			line.erase(0, 1+line.find("."));
			for(int m=0; m<8; m++)
			{
				if(!mask[m])
					return 1;
				if(destBits[m]&!tableBits[m])
					return 0;
			}
			//cout<<"no decision made"<<endl;
		}
		return 1;
	}
	void pRouter::message(string destination, string sentTo, int interface)
	{
		cout<<"Packet with destination address " <<destination<<" will be forwarded to "
			<<sentTo<<" out on interface S"<<interface<<endl;
	}