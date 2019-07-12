#include "Header.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

Item::Item(const char* _name_, int _price_, int _item_number_): name(_name_), price(_price_), item_number(_item_number_), n(1) {}


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

double Item::ShowPrice() {

	return static_cast<double>(price) / static_cast<double>(100.0);

}

int Item::GetPricePence() { return price; }

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
	char msg[100];
	for (int i = 0; i < size - 1; i++) {

		double coin = (double)coin_list[i] / (double)100.0;
		sprintf(msg, "%f GBP, ", coin);
		msg_history.AppendMessage(msg);

	}

	sprintf(msg, "%f GBP\n", (double )coin_list[size - 1]/(double)100.0);
	msg_history.AppendMessage(msg);

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

	return (double)total_value / (double)100.0;

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

	if (msg.IsVoid() == false) printf("\nMSG:%s\n", (char *)msg);


}

void MessageHistory::AppendMessage(const char* message) {

	msg = msg + message;

}