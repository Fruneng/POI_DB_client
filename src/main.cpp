/*
 * main.cpp
 *
 *  Created on: 2013-1-30
 *      Author: viewin-cc
 */
#include "RCF_Fun.h"
#include <vector>
#include "../poi.pb.h"

void SetCloud(poi::Clouds& clouds, std::string username)
{
	clouds.set_username(username);
	(*clouds.mutable_gps()).set_lng(120.123456);
	(*clouds.mutable_gps()).set_lat(30.123456);

//	std::string ser = clouds.SerializeAsString();
//
//	poi::Clouds clouds2;
//	clouds2.ParseFromString(ser);
//
//	std::cout << clouds.DebugString();
}

int main(int argc, char** argv)
{
	poi::Clouds clouds0;
	poi::Clouds clouds1;
	poi::Clouds clouds2;
	poi::Clouds clouds3;
	poi::Clouds clouds4;
	SetCloud(clouds0, "zunceng0");
	SetCloud(clouds1, "zunceng1");
	SetCloud(clouds2, "zunceng2");
	SetCloud(clouds3, "zunceng3");
	SetCloud(clouds4, "zunceng4");

	RCF::RcfInitDeinit rcfInit;
	RCF::TcpEndpoint tcp("192.168.16.236", 50002);
	RcfClient<POIDB_RPC_FUN> rcfclient(tcp);

	try{
		rcfclient.insert("clouds", 120.123455, 30.123456, 0,
				clouds0.username(), clouds0.SerializeAsString());
		rcfclient.insert("clouds", 120.123455, 30.123456, 0,
				clouds1.username(), clouds1.SerializeAsString());
		rcfclient.insert("clouds", 120.123455, 30.123456, 0,
				clouds2.username(), clouds2.SerializeAsString());
		rcfclient.insert("clouds", 120.123455, 30.123456, 0,
				clouds3.username(), clouds3.SerializeAsString());
		rcfclient.insert("clouds", 120.123455, 30.123456, 0,
				clouds4.username(), clouds4.SerializeAsString());

		//for(int i = 0 ; i < 10000 ; i++){

		std::vector<std::string> reslut;
		if(rcfclient.query2("clouds",120.123456, 30.123456, 15, reslut) == 0)
		{
			std::vector<std::string>::iterator it = reslut.begin();
			printf("reslut start:\n");
			while(it != reslut.end())
			{
				poi::Clouds tmp;
				tmp.ParseFromString(*it);
				std::cout << tmp.DebugString() << std::endl;
				it++;
			}
			printf("reslut finished!\n");
		}
		else
		{
			printf("return failed!\n");
		}
//		if(i%1000 == 0)
//			printf("%d\n",i);

		//}

	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

