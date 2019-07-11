#include "Header.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

Item::Item(const char* _name_, double _price_, int _item_number_): name(_name_), price(_price_), item_number(_item_number_), n(1) 
{}


CoinList::CoinList() : total_value(0), sorted(false) {}

void CoinList::AddCoin(double value) {

	int i = -1;
		i = static_cast<int>(coin_list.size()) - 1;

	coin_list.push_back(value);
	total_value += value;

	if (i >=0 && value < coin_list[i]) sorted = false;

}

void CoinList::DeleteLastCoin() {

	int size = static_cast<int>(coin_list.size());	
	double value = coin_list[size - 1];
	total_value -= value;
	coin_list.pop_back();
	
}

void CoinList::TraverseList() {

	int size = static_cast<int>(coin_list.size());
	
	for (int i = 0; i < size - 1; i++) printf("%f GBP, ", coin_list[i]);
	printf("%f GBP\n\n", coin_list[size - 1]);

	printf("Total amount: %f\n\n", total_value);

}

void CoinList::DeleteEverything() {

	int size = static_cast<int>(coin_list.size());

	for (int i = size - 1; i >= 0; i--) {

		total_value -= coin_list[i];
		coin_list.pop_back();

	}
}

void CoinList::SortList() {
	
	int size = static_cast<int>(coin_list.size());
	sort(coin_list.begin(), coin_list.begin() + size);

}

void CoinList::Pay(double amount) {

	if (sorted == false) SortList();
	double payed_amount = 0;

	while (payed_amount < amount) {

		total_value -= coin_list[0];
		payed_amount += coin_list[0];
		coin_list.erase(coin_list.begin());

	}

	GiveChange(payed_amount - amount);

}

void CoinList::GiveChange(double change) {

	if (change <= 0.0) return;

	double coins[8] = { 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1.0 , 2.0 };


	while (change > 0) {

		bool flag = false;

		for (int i = 0; i < 8; i++) {

			if (coins[i] > change) {
				double value = coins[i - 1], prev_val = coins[i];
				if (i > 0) { coin_list.push_back(value); change -= value; flag = true; total_value += value; break; }
				else { coin_list.push_back(prev_val); change -= prev_val; flag = true; total_value += prev_val; break; }
			}

		}

		if (flag == false) {
			coin_list.push_back(coins[7]); change -= 2.0; total_value += 2.0;
		}

	}
	
}