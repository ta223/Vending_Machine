#include <stdio.h>
#include <stdlib.h>
#include "Console.h"
#include "String.h"
#include "Header.h"
#include <vector>

using namespace std;

vector<class Item> item_list;	//array where all items are stored

void GetDefaultItems() {

	item_list.push_back(Item("Pepsi", 30, 1));
	item_list.push_back(Item("Coca cola", 245, 2));
	item_list.push_back(Item("Mars", 345, 3));
	item_list.push_back(Item("Fanta", 25, 4));


}

void ShowItems() {

	int size = (int)item_list.size();

	for (int i = 0; i < size; i++) {
		printf("#%d. %s %f GBP, %d left\n", i + 1, (char *)item_list[i].name, item_list[i].ShowPrice(), item_list[i].n);
	}

	printf("\n\n\n");
}

int main() {

	GetDefaultItems();

	class Console console;
	class CoinList coin_list;

	while (1) {

		ShowItems();

		printf("Total: %f\n", coin_list.ShowTotal());

		printf("cmd:");
		class String command = console.Stdin_str();

		if (command.IsCoin()) {

			int coin = command.GetCoin();
			coin_list.AddCoin(coin);
		
		}

		int item_num = -1;
		if (sscanf(static_cast<char *>(command), "BUY <%d>", &item_num) != EOF && item_num != -1)  {
			
			int size_list = static_cast<int>(item_list.size());
			
			if (item_num >= 1 && item_num <= size_list) {

				if (item_list[item_num - 1].n >= 0) {

					if (coin_list.GetTotalPence() >= item_list[item_num - 1].GetPricePence()) {

						int price = item_list[item_num - 1].GetPricePence();

						coin_list.Pay(price);
						--item_list[item_num - 1];

						printf("You have purchased item %d at the price of %f\n", item_num, item_list[item_num - 1].ShowPrice());
						printf("Total remaining: %f\n\n", coin_list.ShowTotal());

					} else printf("You do not have enough money\n\n");


				} else printf("Item has run out of stock\n\n");

			} else printf("Item does not exist\n\n");

			printf("Press ENTER to continue:"); console.fflush_stdin();

		}

		if (command == "COIN RETURN") {

			printf("Returning:");
			coin_list.TraverseList();
			coin_list.DeleteEverything();

			printf("Press anything to continue:");
			console.Stdin_str();

		}
		

		if (command == "SERVICE") {


		}

		CLEAR_CONSOLE;

	}


	return 0;
}