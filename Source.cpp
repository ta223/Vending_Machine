#include "Header.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

Item::Item(const char* _name_, int _price_, int _item_number_): name(_name_), price(_price_), item_number(_item_number_), n(_item_number_) {}


int Item::operator ++ () {
	++n;
	return n;
}

int Item::operator ++ (int) {

	n++;
	return n;
}


int Item::operator -- () {

	--n;
	return n;

}


int Item::operator -- (int) {

	n--;
	return n;

}

int Item::operator + (int n_add) {

	n += n_add;
	return n;
}

int Item::operator - (int n_sub) {

	n -= n_sub;
	return n;

}

double Item::ShowPrice() {

	return static_cast<double>(price) / static_cast<double>(100.0);

}

int Item::GetPricePence() { return price; }

void Item::SetPrice(int pence) {
	price = pence;
}

CoinList::CoinList() : total_value(0), sorted(false) {}

void CoinList::AddCoin(int value) {

	int i = -1; i = static_cast<int>(coin_list.size()) - 1;

	coin_list.push_back(value);
	total_value += value;

	if (i >=0 && value < coin_list[i]) sorted = false;

}

void CoinList::DeleteLastCoin() {

	int size = static_cast<int>(coin_list.size());	
	int value = coin_list[size - 1];
	total_value -= value;
	coin_list.pop_back();
	
}

void CoinList::TraverseList(class MessageHistory &msg_history) {

	int size = static_cast<int>(coin_list.size());
	ostringstream out;
	msg_history.ClearMessage();
	double coin = static_cast<double>(coin_list[0]) / static_cast<double>(100.0);
	out << coin << " GBP, ";
	msg_history.NewMessage((out.str()).c_str());

	for (int i = 1; i < size - 1; i++) {

		out.str("");
		out.clear();
		coin = static_cast<double>(coin_list[i]) / static_cast<double>(100.0);
		out << coin << " GBP, ";
		msg_history.AppendMessage((out.str()).c_str());

	}

	out.str("");
	out.clear();
	out << static_cast<double>(coin_list[size - 1]) / static_cast<double>(100.0) << " GBP\n";
	msg_history.AppendMessage((out.str()).c_str());

}

void CoinList::DeleteEverything() {

	coin_list.clear();
	total_value = 0;

}

void CoinList::SortList() {
	
	int size = static_cast<int>(coin_list.size());
	sort(coin_list.begin(), coin_list.begin() + size);

}

void CoinList::Pay(int amount) {

	int change = total_value - amount;
	DeleteEverything();
	
	GiveChange(change);

}

void CoinList::GiveChange(int change) {

	if (change <= 0.0) return;

	int coins[] = { 1, 2, 5, 10, 20, 50, 100 , 200 };

	while (change > 0) {

		bool flag = false;

		for (int i = 0; i < 8; i++) {

			if (coins[i] > change) {

				int value = coins[i - 1];
				AddCoin(value); flag = true; change -= value; 
				break;

			}

		}

		if (flag == false) { AddCoin(200); change -= 200; }
		
	}
	
}

double CoinList::ShowTotal() {

	return static_cast<double>(total_value) / static_cast<double>(100.0);

}

int CoinList::GetTotalPence() {
	return total_value;
}

void MessageHistory::NewMessage(const char* message) {

	msg = message;

}

void MessageHistory::ClearMessage() {

	msg.Clear();
}

void MessageHistory::DisplayMessage() {

	if (msg.IsVoid() == false) cout << endl << "MSG:" << msg << endl;

}

void MessageHistory::AppendMessage(const char* message) {

	msg = msg + message;

}

void ItemList::GetDefaultItems() {

	item_list.push_back(Item("Pepsi", 210, 20));
	item_list.push_back(Item("CocaCola", 175, 25));
	item_list.push_back(Item("Mars", 80, 17));
	item_list.push_back(Item("Fanta", 150, 10));
	item_list.push_back(Item("Snickers", 75, 10));
	item_list.push_back(Item("Doritos", 70, 5));

	/*add more stuff here*/
}

int ItemList::FindItem(const char *name) {

	char *lowercase_name = String::LowerCase(name);	//convert to lower case

	int size = (int)item_list.size();
	for (int i = 0; i < size; i++) {

		class String item_name = String::LowerCase(static_cast<char *>(item_list[i].name));	//convert item name to lower case
		if (item_name == (static_cast<const char*>(lowercase_name))) return i;	//now the comparison is not case sensitive

	}

	return -1;
}

void ItemList::ShowItems() {

	int size = (int)item_list.size();

	for (int i = 0; i < size; i++) 
		cout << "#" << i + 1 << ". "<< static_cast<char *>(item_list[i].name) << " " << item_list[i].ShowPrice() << " GBP, " <<
			item_list[i].n << " left" << endl;
	
	cout << "\n\n\n";

}
