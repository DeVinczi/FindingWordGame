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

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

class Words 
{
protected:
	std::string word;
	std::fstream wordsfile;
	int los[10];
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
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {     
		los[i] = i;
	}

	for (int i = 0; i < 10; i++) {    // losujemy
		int temp = los[i];
		int randomIndex = rand() % 10;
		los[i] = los[randomIndex];
		los[randomIndex] = temp;
	}
}
void Words::DrawWord()
{
	int intline = 0;
	char tab[256];
	srand(time(NULL));
	int number = rand()%4;
	std::fstream wordsfile("Words.txt", std::ios::in);
		while (getline(wordsfile, word))
		{
			if (number == intline) {
				strcpy_s(tab, word.c_str());
				for (int i = 0; i < word.size(); i++)
				{
					std::cout << tab[los[10]];
				}
			}
			intline++;
	}
}

int main()
{
	//Words p1;
	//p1.OpeningFile();
	//p1.DrawWord();
	Words* FirstWord = new Words;
	FirstWord->Inicialize();
	FirstWord->OpeningFile();
	FirstWord->DrawWord();
}
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <conio.h>
//
//using namespace std;
//class OsobaCL
//{
//protected:
//    string m_imie;
//    string m_nazwisko;
//    OsobaCL* m_nastepnaOsoba;
//public:
//    void Inicjuj();
//    void Sprzatnij();
//    void Wypelnij();
//    OsobaCL* GetNastepnaOsoba();
//    void ShowDaneOsoby(int fImieWidth = 12, int fNazwiskoWidth = 20);
//    void DodajOsobeNaKoniec();
//};
//
//void OsobaCL::Inicjuj()
//{
//    m_nastepnaOsoba = NULL;
//}
//
//void OsobaCL::Sprzatnij()
//{
//    if (m_nastepnaOsoba != NULL)
//    {
//        m_nastepnaOsoba->Sprzatnij();
//        delete m_nastepnaOsoba;
//        m_nastepnaOsoba = NULL;
//    }
//}
//
//OsobaCL* OsobaCL::GetNastepnaOsoba()
//{
//    return(m_nastepnaOsoba);
//}
//
//void OsobaCL::Wypelnij()
//{
//    cout << "Podaj imie: ";
//    cin >> m_imie;
//    cout << "Podaj nazwisko: ";
//    cin >> m_nazwisko;
//}
//
//void OsobaCL::ShowDaneOsoby(int fImieWidth, int fNazwiskoWidth)
//{
//    cout << setw(fImieWidth) << m_imie << " " << setw(fNazwiskoWidth) << m_nazwisko << endl;
//}
//
//void OsobaCL::DodajOsobeNaKoniec()
//{
//    //Szukanie ostatniej osoby
//    OsobaCL* tOstatniaOsoba = this; //Zapisanie wskaŸnika obecnej osoby do zmiennej
//    while (tOstatniaOsoba->m_nastepnaOsoba != NULL) tOstatniaOsoba = tOstatniaOsoba->m_nastepnaOsoba;
//
//    //Utworzenie nowej osoby i zapisanie do ostatniej osoby
//    OsobaCL* tNowaOsoba = new OsobaCL;
//    tNowaOsoba->Inicjuj();
//    tNowaOsoba->Wypelnij();
//    tOstatniaOsoba->m_nastepnaOsoba = tNowaOsoba;
//}
//
//int main()
//{
//    /*Utworzenie pierwszej osoby*/
//    OsobaCL* tPierwszaOsoba = new OsobaCL;
//    tPierwszaOsoba->Inicjuj();
//
//    /*Wype³nienie pierwszej osoby*/
//    tPierwszaOsoba->Wypelnij();
//
//    /*Wczytywanie kolejnych osób*/
//    char tZnak;
//    do
//    {
//        cout << "Czy chcesz dodac nowa osobe? (T/N) ";
//        do
//        {
//            tZnak = _getch();
//        } while ((tZnak != 'n') && (tZnak != 'N') && (tZnak != 't') && (tZnak != 'T'));
//
//        cout << tZnak << endl;
//        if ((tZnak == 't') || (tZnak == 'T')) tPierwszaOsoba->DodajOsobeNaKoniec(); //Dodawanie nowej osoby
//
//    } while ((tZnak != 'n') && (tZnak != 'N'));
//
//    /*Wyœwietlanie wszystkich osób*/
//    OsobaCL* tWyswietlOsoby = tPierwszaOsoba;
//    while (tWyswietlOsoby != NULL)
//    {
//        tWyswietlOsoby->ShowDaneOsoby();
//        tWyswietlOsoby = tWyswietlOsoby->GetNastepnaOsoba();
//    }
//
//    /*Zwalnianie pamiêci*/
//    tPierwszaOsoba->Sprzatnij();
//    delete tPierwszaOsoba;
//
//    _getch();
//    return 0;
//}