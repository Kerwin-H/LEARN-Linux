#include "db.hpp"
#include"httplib.h"

#define WWWROOT "./wwwroot"
using namespace httplib;


void DishInsert(const Request &req, Response &rsp){

	return;
}

void DishDelete(const Request &req, Response &rsp){

	return;
}
void DishUpdate(const Request &req, Response &rsp){

	return;
}
void DishGetAll(const Request &req, Response &rsp){

	return;
}
void DishGetone(const Request &req, Response &rsp){

	return;
}



void OrderInsert(const Request &req, Response &rsp){

	return;
}

void OrderDelete(const Request &req, Response &rsp){

	return;
}
void OrderUpdate(const Request &req, Response &rsp){

	return;
}
void OrderGetAll(const Request &req, Response &rsp){

	return;
}
void OrderGetone(const Request &req, Response &rsp){

	return;
}
int main()
{
	Server server;
	server.set_base_dir(WWWROOT);
	//²Ë
	server.Post("/dish", DishInsert);
	server.Delete(R"(/dish(\d+))", DishDelete);
	server.Put(R"(/dish(\d+))", DishUpdate);
	server.Get(R"(/dish)", DishGetAll);
	server.Get(R"(/dish(\d+))", DishGetone);

	//¶©µ¥
	server.Post("/order", OrderInsert);
	server.Delete(R"(/order(\d+))", OrderDelete);
	server.Put(R"(/order(\d+))", OrderUpdate);
	server.Get(R"(/order)", OrderGetAll);
	server.Get(R"(/order(\d+))", OrderGetone);

	server.listen("0.0.0.0", 9000);

	return 0;
}

void dish_test()
{
	// order_sys::TableDish dish;

	// /*Json::Value val;
	// val["id"]=3;
	// val["name"] = "ÂéÆÅ¶¹¸¯"; 
	// val["price"] = 1900;

	// //dish.Insert(val);
	// //dish.Update(val);
	// dish.Delete(3);*/

	// Json::Value val;
	// Json::StyledWriter writer;
	// //dish.SelectAll(&val);
	// dish.SelectOne(2, &val);

	// std::cout << writer.write(val) << std::endl;
}

void order_test()
{

	order_sys::TableOrder order;
	// Json::Value val;
	// val["id"]=3;

	// val["dishes"].append(1);

	// val["status"]=1;

	//order.Insert(val);

	//order.Update(val);
	//order.Delete(3);

	Json::Value val;
	Json::StyledWriter writer;

	order.SelectOne(1, &val);

	std::cout << writer.write(val) << std::endl;
}


class Solution {
public:
	double myPow(double x, long n) {
		if (!n) return 1;
		if (n < 0) n = -n, x = 1 / x;
		double result = 1;
		while (n) {
			if (n & 1) result *= x;
			x *= x, n >>= 1;
		}
		return result;
	}
};
