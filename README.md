# Vending_Machine

This short readme describes some important aspects of the code. Not everything is described here as most of the code is readable and intuitive (or at least i hope so).

*FILE OVERVIEW 

The files console.cpp and Console.h contains some functions useful for setting up a command line interface. Not everything in these 2 files are relevant for this assessment because I wrote them last year for my University projects (originally written in C).
The files String.h and String.cpp define the String class. I wrote this class instead of using std::string to make it more intuitive and readable. The class, in fact, contains overloaded binary operators that can be used between objects of class String or between an object and a variable of type char*. It also contains functions dedicated specifically for this project, like IsCoin(), GetCoin() and LowerCase().

The files Header.h, API.cpp and Main.cpp are the ones that build the whole system for a vending machine.

*COMMAND LINE UI 

The command line interface loop is very similar to a video game while loop. The main while loop displays the same objects with updated values at every cycle. The code follows this kind of pattern:

class Console console;

while(1){

  /*print some messages*/

  printf("cmd:"); class String command = console.Stdin_str();

  if(command == "Input"){ .... }

  if(command == "Another input") { ... }

  CLEAR_CONSOLE;

}

The CLEAR_CONSOLE macro clears everything on the screen, so that at the start of a new cycle, the same objects will be printed but with updated values. The macro is defined in Console.h and its implementation depends whether we are on Win32 or a Unix like system.

*MESSAGE POLLING SYSTEM 

The file Header.h contains a class (class MessageHistory) to poll string outputs. The polling system is used to display messages when the user buys something or the SERVICE functions are used. So for example, when the user buys something, the class MessageHistory receives the message "You have purchased this item etc..." and displays it for the rest of the iterations until another message overrides the old one or the message is deleted.

*PAYMENT METHOD 

I had thought about two methods to receive payments from a list of coins and was struggling to decide which one would be a better implementation. The first method, which is the one implemented in this project, is very simple and is a lot faster. It simply clears the entire list of coin the user has and uses an algorithm (which i am going to discuss later) to return the change with a suitable combination of coins. The second method is the same algorithm to return the change.

*CHANGE RETURNING ALGORITHM 

The objective of this algorithm is to find a suitable combination of coins that adds up to a certain target value and it goes in the following way:

  1. Define all coins in a sorted array For example: int coin = [1p, 2p, 5p, 10p, 20p, 50p, 100p, 200p]

  2. Iterate over the coin array and look for the 1st element that is higher than the target value

  3. If the value is found, then add the previous value to the user's coin list and subtract this value to the target value. For example, if the target value is 30p, the first coin in the coin array that is higher than 30p is 50p. So we add 20p to the user's coin list and subtract 20p from target value (so now target value becomes 50p-20p = 30p)

  4. If the value is not found, it means that the target value is higher than the coin with the highest value. In that case, we simply add the highest coin to the user's coin list and subtract it with the target value. For example, if the target value is 5£, then we simply add 2£ to user's coin list and subtract 2£ to the target value

  5. Repeat from step 2 until target value becomes zero.

Now the second payment method i was talking about implements the same exact algorithm described above. With the only difference that the possible type of coins is defined by the user's coin list. However, applying this algorithm twice, both for payment and change returning would require extra computing power and from my own experience, it seems that vending machines use the first payment method.
