#pragma once
#include "String.h"
#include <vector>

class Item {

public:
	Item(const char* _name_, int _price_, int _item_number_);

	class String name;
	int item_number;
	int n;	//how many of this item are available in the machine
	
	int operator ++ ();	//prefix overload
	int operator ++ (int);	//post fix overload
	int operator -- ();
	int operator -- (int);

	double ShowPrice();	//shows price in pounds
	int GetPricePence();

private:
	int price;	//price in pence


};

class CoinList {

public:
	CoinList();
	void AddCoin(int value);
	void DeleteLastCoin();
	void TraverseList();
	void DeleteEverything();
	
	void Pay(int amount);
	double ShowTotal();
	int GetTotalPence();
	

private:
	std::vector<int> coin_list;

	bool sorted;
	void SortList();
	void GiveChange(int change);
	int total_value;

};
