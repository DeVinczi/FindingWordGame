#include <iostream>
#include <conio.h>
#include <dos.h>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define WIN_WIDTH 600

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 20;
}
class Words 
{
protected:
	std::string word;
	std::fstream wordsfile;
	char tab[256];
	int los[256];		//Highest number of word length
	const int wordsnumber = 9;//Number of words in txt file
	Words* nextWord;
public:
	/*bool is_open();*/
	void Inicialize();
	void Clean();
	Words* NextWordFunc();
	void DeleteWord();
	void DrawWord();
	void OpeningFile();
	void RandomNumbers();
	void FindAnswer();
	std::string& toupper(std::string &x);
	void showHint(int x);
	void play();
	void func();
};


void Words::Inicialize()
{
	nextWord = nullptr;
}

void Words::Clean()
{
	if (nextWord != nullptr)
	{
		nextWord->Clean();
		delete nextWord;
		nextWord = nullptr;
	}
}
Words *Words::NextWordFunc()
{
	return (nextWord);
}
void Words::DeleteWord()
{
	//Looking for last word;
	Words* LastWord = this;
	while (LastWord->nextWord != NULL)
		LastWord = LastWord->nextWord;
	Words* NewWord = new Words;
	NewWord->Inicialize();
	/*NewWord->DrawWord();*/
	LastWord->nextWord = NewWord;
}

void Words::OpeningFile() 
{
	std::fstream wordsfile("Words.txt", std::ios::in);
	if(!wordsfile.is_open())	std::cout << "error";
}

void Words::RandomNumbers()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < word.size(); i++) {
		los[i] = i;
	}

	for (int i = 0; i < word.size(); i++) {    // Draw
		int temp = los[i];
		int randomIndex = rand() % word.size();
		los[i] = los[randomIndex];
		los[randomIndex] = temp;
	}
}

std::vector<int> digit;
void Words::func()
{
	for (int i = 0; i <= wordsnumber; i++)
		digit.push_back(i);
	srand((unsigned)time(NULL));
	for (int i = 1; i <digit.size(); i++) {    // Draw 0-last word
		int temp = digit[i];
		int numbers = rand() % wordsnumber;
		digit[i] = digit[numbers];
		digit[numbers] = temp;
	}
}

void Words::DrawWord()
{
	int intline = 0;
	int number = digit[digit.size()-1];
	if(!digit.empty()) digit.pop_back();

	std::fstream wordsfile("Words.txt", std::ios::in);
	while (getline(wordsfile, word))
	{
		if (number == intline) {
			strcpy_s(tab, word.c_str());
			for (int i = 0; i < word.size(); i++)
			{
				RandomNumbers();
				std::cout << tab[los[i]];
			}
			break;
		}
		intline++;
	}

}

std::string& Words::toupper(std::string &x)
{
	std::transform(x.begin(), x.end(), x.begin(), ::toupper);
	return x;
}
void Words::FindAnswer()
{
	int hint = 0;
	std::string answer;
	do {
		std::cout << '\n';
		std::cin >> answer;
		std::cin.sync_with_stdio();
		toupper(answer);
		if (word == answer)
		{
			std::cout << "Good JOB MATE!\n";
		}
		else if (answer == "9")
		{
			showHint(hint);
			hint++;
		}
		else
			std::cout << "Nope! Try Again!";
	} while (word != answer);
}

void Words::showHint(int x)
{
	std::vector<char> hintVEC;
	for(int i = 0; i<word.size();i++) hintVEC.push_back(tab[i]);
	for (int j = 0; j <= x; j++) {
		std::cout << hintVEC[j];
	}
		std::cout << std::setfill('*') << std::setw(word.size() - x);
}

void Words::play()
{
	Words* FirstWord = new Words;
	FirstWord->func();
	while (1)
	{
		FirstWord->Inicialize();
		FirstWord->OpeningFile();
		FirstWord->DrawWord();
		FirstWord->FindAnswer();
		if (digit.empty())
		{
			std::cout << "It was last word!";
		}
		FirstWord->DeleteWord();
	}
}
int main()
{
	Words play;
	play.play();
}
