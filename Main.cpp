#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include <random>

int player{}; //
int nextPlayer{ 1 }; 
int otherPlayer{}; //
int handValue[3]{}; //
std::string hands[3][21]
{	
	{".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","."},
	{".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","."},
	{".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","."}
};
int cardAmount[3]{}; 
int won{};
std::mt19937 random{ static_cast<std::mt19937::result_type>(std::time(nullptr)) }; //
std::uniform_int_distribution number{ 1, 13 };//
std::uniform_int_distribution type{ 1, 4 };//
bool stand[3]{1,0,0};

void save()
{
	std::ofstream save;
	save.open("number.txt");

	save << nextPlayer << '\n'
			<< won << '\n';
	int r{};
	for (int d : cardAmount)
	{
		save << cardAmount[r] << '\n';
		r++;
	}
	r = 0;
	for (int d : handValue)
	{
		save << handValue[r] << '\n';
		r++;
	}
	for (int i{}; i < 3; i++)
	{
		for (int ii{}; ii < 21; ii++)
		{
			save << hands[i][ii] << '\n';
		}
	}
	r = 0;
	for (int d : stand)
	{
		save << stand[r] << '\n';
		r++;
	}
	save.close();
}

void load()
{
	std::ifstream load;
	load.open("number.txt");

	load >> nextPlayer >>
		won;

	int r{};
	for (int d : cardAmount)
	{
		load >> cardAmount[r];
		r++;
	}
	r = 0;
	for (int d : handValue)
	{
		load >> handValue[r];
		r++;
	}
	for (int i{}; i < 3; i++)
	{
		for (int ii{}; ii < 21; ii++)
		{
			load >> hands[i][ii];
		}
	}
	r = 0;
	for (int d : stand)
	{
		load >> stand[r];
		r++;
	}

	load.close();
}

std::string generateCard()
{
	std::string card{};
	switch (number(random))
	{
	case 1:
	{
		card += "A";
		handValue[player] += 1;
		break;
	}
	case 2:
	{
		card += "2";
		handValue[player] += 2;
		break;
	}
	case 3:
	{
		card += "3";
		handValue[player] += 3;
		break;
	}
	case 4:
	{
		card += "4";
		handValue[player] += 4;
		break;
	}
	case 5:
	{
		card += "5";
		handValue[player] += 5;
		break;
	}
	case 6:
	{
		card += "6";
		handValue[player] += 6;
		break;
	}
	case 7:
	{
		card += "7";
		handValue[player] += 7;
		break;
	}
	case 8:
	{
		card += "8";
		handValue[player] += 8;
		break;
	}
	case 9:
	{
		card += "9";
		handValue[player] += 9;
		break;
	}
	case 10:
	{
		card += "10";
		handValue[player] += 10;
		break;
	}
	case 11:
	{
		card += "J";
		handValue[player] += 10;
		break;
	}
	case 12:
	{
		card += "Q";
		handValue[player] += 10;
		break;
	}
	case 13:
	{
		card += "K";
		handValue[player] += 10;
		break;
	}
	default:
		break;
	}

	switch (type(random))
	{
	case 1:
	{
		card += "*";
		break;
	}
	case 2:
	{
		card += "$";
		break;
	}
	case 3:
	{
		card += "#";
		break;
	}
	case 4:
	{
		card += "^";
		break;
	}
	default:
		break;
	}
	return card;
}

void printHands()
{
	std::cout << "Dealer: ";
	for (int i{}; i < 21; i++)
	{
		std::cout << hands[0][i] << " ";
	}
	std::cout << "Value = " << handValue[0];
	std::cout << std::endl;
	std::cout << "Player1: ";
	for (int i{}; i < 21; i++)
	{
		std::cout << hands[1][i] << " ";
	}
	std::cout << "Value = " << handValue[1];
	std::cout << std::endl;
	std::cout << "Player2: ";
	for (int i{}; i < 21; i++)
	{
		std::cout << hands[2][i] << " ";
	}
	std::cout << "Value = " << handValue[2];
	std::cout << std::endl;
}

int main()
{
	save();
	std::cout << "Which Player Are You (1/2)? ";
	std::cin >> player;

	if (player == 1)
	{
		otherPlayer = 2;

		player = 0;
		for (int i{}; i < 3; i++)
		{
			hands[0][cardAmount[0]] = generateCard();
			cardAmount[0]++;
		}
		player = 1;
		save();
	}
	else
	{
		otherPlayer = 1;
	}

	while (won != 1)
	{
		int choice{};
		std::cout << "Waiting" << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));

		load();
		if (stand[0] == true && stand[1] == true && stand[2] == true)
		{
			won = 1;
		}
		while (stand[player] == false && nextPlayer == player)
		{
			std::system("cls");
			printHands();
			std::cout << "Hit or Stand?(0/1)";
			std::cin >> choice;

			if (choice == 0 && handValue[player] < 21)
			{
				hands[player][cardAmount[player]] = generateCard();
				cardAmount[player]++;
			}
			else
			{
				stand[player] = true;
			}
			save();
		}
		nextPlayer = otherPlayer;
		save();
	}

	std::system("CLS");
	std::cout << "Final scores:\n";
	std::cout << "Dealer = " << handValue[0] << '\n';
	std::cout << "Player1 = " << handValue[1] << '\n';
	std::cout << "Player2 = " << handValue[2] << '\n';
	std::system("pause>nul");
	return 0;
}
