#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Console.h"
#include "String.h"
#include "Header.h"
#include <vector>


using namespace std;

void ServiceLoop(class Console &console, class MessageHistory &msg_history, class ItemList &item_list) {

	CLEAR_CONSOLE;
	
	msg_history.ClearMessage();

	while (1) {

		cout << "1. Add Items\n2. Remove Items\n3. Exit\n\n";
		msg_history.DisplayMessage();
		cout << "cmd:";
		class String command = console.Stdin_str();

		if (command == "Add Items") {

			msg_history.ClearMessage();
			cout << "Enter the item name, its price, and the quantity:";
			command = console.Stdin_str_nocommas();	//get input with no commas
			char name[100];
			double price = -1.0;
			int n = -1;
			istringstream string(static_cast<char*>(command));

			/*if valid input*/
			if(string >> static_cast<char*>(name) >> price >> n &&  n != -1 && price != -1.0){

				int index = item_list.FindItem(name);
				ostringstream out;

				if (index == -1) { 

					out << "Item " << name << " does not exist\n";
					msg_history.NewMessage(out.str().c_str()); 
					goto end;

				}

				item_list.item_list[index]+n;
				int pence = static_cast<int>(price*static_cast<double>(100.0));
				item_list.item_list[index].SetPrice(pence);
				out << "Item added succesfully\n";
				msg_history.NewMessage(out.str().c_str());

			} else msg_history.NewMessage("Invalid input\n");

		}

		if (command == "Remove Items") {

			msg_history.ClearMessage();
			cout << "Enter item name and quantity:";
			command = console.Stdin_str_nocommas();
			char name[100];
			int quantity = -1;
			istringstream string(static_cast<char*>(command));

			if (string >> name >> quantity && quantity != -1) {

				int index = item_list.FindItem(static_cast<char *>(name));
				ostringstream out;

				if (index == -1) {

					out << "Item " << name << " does not exist\n";
					msg_history.NewMessage(out.str().c_str());
					goto end;

				}

				if (item_list.item_list[index].n != 0) {

					item_list.item_list[index] - quantity;
					if (item_list.item_list[index].n < 0) item_list.item_list[index].n = 0;
					out << "Item succesfully removed\n";
					msg_history.NewMessage(out.str().c_str());
					goto end;

				}

				out << "Item has 0 stocsk\n";
				msg_history.NewMessage(out.str().c_str());

			} else msg_history.NewMessage("Invalid input\n");

		}

		if (command == "Exit") break;

		end: {
			CLEAR_CONSOLE;
		}

	}

	msg_history.ClearMessage();
	CLEAR_CONSOLE;

}

void UserLoop(class Console &console, class CoinList &coin_list, class MessageHistory &msg_history, class ItemList &item_list) {

	while (1) {

		item_list.ShowItems();	//display all the items available
		cout << "Total: " << coin_list.ShowTotal() << " GBP" << endl;
		msg_history.DisplayMessage();	//dipslay messages such as "You purchased this item..." or "COins returned:..."
		cout << "cmd:";
		class String command = console.Stdin_str();	//Get string input

		if (command.IsCoin()) {	//check if string input is a coin

			int coin = command.GetCoin();
			coin_list.AddCoin(coin);
			msg_history.ClearMessage();

		}

		/*Check if user wants to buy something*/
		int item_num = -1;
		
		if (sscanf(static_cast<char *>(command), "BUY <%d>", &item_num) != EOF && item_num != -1) {

			int size_list = static_cast<int>(item_list.item_list.size());

			if (item_num >= 1 && item_num <= size_list) {	//if item exists

				if (item_list.item_list[item_num - 1].n >= 0) {	//if there are stocks to buy

					if (coin_list.GetTotalPence() >= item_list.item_list[item_num - 1].GetPricePence()) {	//if user has enough money

						int price = item_list.item_list[item_num - 1].GetPricePence();

						coin_list.Pay(price);	//pay the price and get change
						--item_list.item_list[item_num - 1];	//reduce the amount of stocks available

						/*Poll message*/
						ostringstream out;
						out << "You have purchased " << static_cast<char *>(item_list.item_list[item_num - 1].name) << 
							" at the price of " << item_list.item_list[item_num - 1].ShowPrice() << " GBP\n";
						msg_history.NewMessage(out.str().c_str());

					}else msg_history.NewMessage("You do not have enough money\n");

				}else msg_history.NewMessage("Item is not on stock at the moment\n");

			}else msg_history.NewMessage("Item does not exist\n");

		}

		if (command == "COIN RETURN") {

			if (coin_list.GetTotalPence() != 0) {

				msg_history.NewMessage("Returned Coins:");
				coin_list.TraverseList(msg_history);
				coin_list.DeleteEverything();

			} else msg_history.NewMessage("You did not insert any coin\n");

		}

		if (command == "SERVICE") {

			printf("Enter password:");
			class String password = console.Stdin_str();
			if (password == "1234abc")
				ServiceLoop(console, msg_history, item_list);

		}

		CLEAR_CONSOLE;

	}

}

int main() {

	class ItemList item_list;
	item_list.GetDefaultItems();
	class Console console;
	class CoinList coin_list;
	class MessageHistory msg_history;

	UserLoop(console, coin_list, msg_history, item_list);

	return 0;
}