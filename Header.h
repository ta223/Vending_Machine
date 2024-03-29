#pragma once
#include "String.h"
#include <vector>

class MessageHistory {

public:
	void NewMessage(const char* message);
	void ClearMessage();
	void DisplayMessage();
	void AppendMessage(const char* message);

private:
	class String msg;
};


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
	int operator + (int n_add);
	int operator - (int n_sub);

	double ShowPrice();	//shows price in pounds
	int GetPricePence();	//get price in pence
	void SetPrice(int pence);	//set price

private:
	int price;	//price in pence


};

class CoinList {

public:
	CoinList();
	void AddCoin(int value);
	void DeleteLastCoin();
	void TraverseList(class MessageHistory &msg_history);
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

class ItemList{

public:
	std::vector<class Item> item_list;	//array where all items are stored
	void GetDefaultItems();
	int FindItem(const char *name);
	void ShowItems();

};