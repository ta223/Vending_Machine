#pragma once
#include "String.h"
#include <vector>

class Item {

public:
	Item(const char* _name_, double _price_, int _item_number_);

	class String name;
	double price;
	int item_number;
	int n;	//how many of this item are available in the machine

	class Item *next, *prev;
	friend class ItemList;

};

class CoinList {

public:
	CoinList();
	void AddCoin(double value);
	void DeleteLastCoin();
	void TraverseList();
	void DeleteEverything();
	
	void Pay(double amount);

	double total_value;

private:
	std::vector<double> coin_list;

	bool sorted;
	void SortList();
	void GiveChange(double change);

};
