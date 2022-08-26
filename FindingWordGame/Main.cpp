#include <iostream>
#include <conio.h>
#include <dos.h>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
	int los[256];		//Highest number of word length
	int wordsnumber = 10;//Number of words in txt file
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
	void showHint();
	void play();
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


void Words::DrawWord()
{
	int intline = 0;
	char tab[256];
	srand((unsigned)time(NULL));
	int number = rand()%wordsnumber;
	std::fstream wordsfile("Words.txt", std::ios::in);
		while (getline(wordsfile, word))
		{
			if (number == intline){
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
		else
			std::cout << "Nope! Try Again!";
	} while (word!=answer);

}

void Words::showHint()
{

}

void Words::play()
{
	Words* FirstWord = new Words;
	while (1)
	{
		FirstWord->Inicialize();
		FirstWord->OpeningFile();
		FirstWord->DrawWord();
		FirstWord->FindAnswer();
		FirstWord->DeleteWord();
	}
}
int main()
{
	Words play;
	play.play();
}
