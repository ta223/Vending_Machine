#include <stdio.h>
#include <stdlib.h>
#include "Console.h"
#include "String.h"
#include "Header.h"
#include <vector>

using namespace std;

vector<class Item> item_list;	//array where all items are stored

void GetDefaultItems() {

	item_list.push_back(Item("Pepsi", 210, 20));
	item_list.push_back(Item("Coca cola", 175, 25));
	item_list.push_back(Item("Mars", 80, 17));
	item_list.push_back(Item("Fanta", 150, 10));
	item_list.push_back(Item("Snickers", 75, 10));
	item_list.push_back(Item("Doritos", 70, 5));

	/*add more stuff here*/
}

int FindItem(const char *name) {

	char *lowercase_name = String::LowerCase(name);	//convert to lower case

	int size = (int)item_list.size();
	for (int i = 0; i < size; i++) {

		class String item_name = String::LowerCase( (char *)item_list[i].name   );	//convert item name to lower case
		if (item_name == (const char *)lowercase_name) return i;	//now the comparison is not case sensitive

	}

	return -1;
}

void ShowItems() {

	int size = (int)item_list.size();

	for (int i = 0; i < size; i++) {
		printf("#%d. %s %.2f GBP, %d left\n", i + 1, (char *)item_list[i].name, item_list[i].ShowPrice(), item_list[i].n);
	}

	printf("\n\n\n");
}

void ServiceLoop(class Console &console, class MessageHistory &msg_history) {

	CLEAR_CONSOLE;
	
	msg_history.ClearMessage();

	while (1) {

		printf("1. Add Items\n2. Remove Items\n3. Exit\n\n");
		msg_history.DisplayMessage();

		printf("cmd:");
		class String command = console.Stdin_str();

		if (command == "Add Items") {

			msg_history.ClearMessage();

			printf("Enter the item name, its price, and the quantity:");
			command = console.Stdin_str_nocommas();	//get input with no commas

			char name[100];
			double price = -1.0;
			int n = -1;

			/*if valid input*/
			if (sscanf((char *)command, "%s %lf %d\n", (char *)name, &price, &n) != EOF && n != -1 && price != -1.0) {

				int index = FindItem(name);
				char msg[100];

				if (index == -1) { 
					sprintf(msg, "Item %s does not exist\n", name);
					msg_history.NewMessage(msg); 
					goto end;
				}

				item_list[index]+n;
				int pence = (int)(price*(double)100.0);
				item_list[index].SetPrice(pence);

				sprintf(msg, "Item added succesfully\n");
				msg_history.NewMessage(msg);

			}

			else msg_history.NewMessage("Invalid input\n");

		}

		if (command == "Remove Items") {

			msg_history.ClearMessage();

			printf("Enter item name and quantity:");
			command = console.Stdin_str_nocommas();

			char name[100];
			int quantity = -1;
			if ( sscanf((char *)command, "%s %d\n", (char *)name, &quantity) !=EOF && quantity != -1) {

				int index = FindItem((char *)name);
				char msg[100];

				if (index == -1) {
					sprintf(msg, "Item %s does not exist", (char *)name);
					msg_history.NewMessage(msg);
					goto end;
				}

				if (item_list[index].n != 0) {

					item_list[index] - quantity;
					if (item_list[index].n < 0) item_list[index].n = 0;

					sprintf(msg, "Item removed succesfully\n");
					msg_history.NewMessage(msg);
					goto end;

				}

				sprintf(msg, "Item has 0 stocks\n");
				msg_history.NewMessage(msg);

			}

			else msg_history.NewMessage("Invalid input\n");

		}

		if (command == "Exit") break;

		end: {
			CLEAR_CONSOLE;
		}

	}

	msg_history.ClearMessage();
	CLEAR_CONSOLE;

}

int main() {

	GetDefaultItems();

	class Console console;
	class CoinList coin_list;
	class MessageHistory msg_history;

	while (1) {

		ShowItems();	//display all the items available

		printf("Total: %f\n", coin_list.ShowTotal());

		msg_history.DisplayMessage();	//dipslay messages such as "You purchased this item..." or "COins returned:..."

		printf("cmd:");
		class String command = console.Stdin_str();	//Get string input

		if (command.IsCoin()) {	//check if string input is a coin

			int coin = command.GetCoin();
			coin_list.AddCoin(coin);
			msg_history.ClearMessage();
		
		}

		/*Check if user wants to buy something*/
		int item_num = -1;
		if (sscanf(static_cast<char *>(command), "BUY <%d>", &item_num) != EOF && item_num != -1)  {
			
			int size_list = static_cast<int>(item_list.size());
			
			if (item_num >= 1 && item_num <= size_list) {	//if item exists

				if (item_list[item_num - 1].n >= 0) {	//if there are stocks to buy

					if (coin_list.GetTotalPence() >= item_list[item_num - 1].GetPricePence()) {	//if user has enough money

						int price = item_list[item_num - 1].GetPricePence();

						coin_list.Pay(price);	//pay the price and get change
						--item_list[item_num - 1];	//reduce the amount of stocks available

						/*Poll message*/
						char msg[100];

						sprintf(msg, "You have purchased '%s' (item #%d) at the price of %f GBP\n", 
							(char *)item_list[item_num-1].name, item_num, item_list[item_num - 1].ShowPrice());

						msg_history.NewMessage(msg);

					} else msg_history.NewMessage((char *)"You do not have enough money\n");


				} else msg_history.NewMessage((char *)"Item is not on stock at the moment\n");

			} else msg_history.NewMessage((char *)"Item does not exist\n");

		
		}

		if (command == "COIN RETURN") {

			msg_history.NewMessage("Returned Coins:");
			coin_list.TraverseList(msg_history);
			coin_list.DeleteEverything();

		}
		

		if (command == "SERVICE") 
			ServiceLoop(console, msg_history);

		
		CLEAR_CONSOLE;

	}


	return 0;
}