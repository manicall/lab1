#include <conio.h>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>
using namespace std;

class Menu {

	int first_menu_top = 0, first_menu_bottom = 2, first_menu_left = 0, first_menu_right;
	int second_menu0_top = first_menu_bottom, second_menu0_bottom, second_menu0_left, second_menu0_right;
	int second_menu1_top = first_menu_bottom, second_menu1_bottom, second_menu1_left, second_menu1_right;
	int choosen_point = 0;
	int point_of_menu = 0, level_of_menu = 0;
	vector<string> first_menu, second_menu0, second_menu1;
	vector<string> points_of_first_menu = { "Съедобные грибы", "Несъедобные грибы" };
	vector<vector<string> > points_of_second_menu = {
		{"Белый гриб", "Козляк", "Опёнок осенний"},
		{"Мухомор красный", "Строфария говняная", "Сатанинский гриб"}
	};
	vector<vector<string> > descriptions = {
	{
		"Различные разновидности белого гриба произрастают в лиственных, хвойных и смешанных лесах с начала лета до октября (с перерывами), образуя микоризу с различными видами деревьев.",
		"Козляк похож на моховик, только шляпка его очень выпуклая, сверху покрыта словно коричневой кожей, слегка клейкая.",
		"Шляпка диаметром 2 - 9, очень вариабельная, выпуклая, затем плоско - распростертая с загнутыми краями, с плоской депрессией в центре, затем края шляпки могут выгибаться и вверх."
	},
	{
		"Мухомор красный (лат. Amanita muscaria) — ядовитый психоактивный гриб рода Мухомор, или Аманита (лат. Amanita) порядка агариковых (лат. Agaricales), относится к базидиомицетам.",
		"Небольшой пластинчатый гриб с размером шляпки до 2,5 сантиметров. Растёт с середины августа, встречаются как по отдельности, так и массово.",
		"Сатанинский гриб(лат.Rubroboletus satanas) — ядовитый(по некоторым данным, условно съедобный) гриб из рода Rubrobolet семейства Болетовые(лат.Boletaceae)."
	}
	};

	void print_description() {
		gotoxy(0, 20);
		cout << descriptions[choosen_point][point_of_menu];
	}

	string padTo(std::string str, const size_t num, const char paddingChar = ' ')
	{
		string res;
		if (num > str.size())
			str.insert(str.size(), num - str.size(), paddingChar);
		res = str;
		return res;
	}
	string padTo(const size_t num, const char paddingChar = ' ')
	{
		string res;
		res.insert(0, num, paddingChar);
		return res;
	}

	enum {
		BACKSPACE = 8, ENTER = 13, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80
	};

	void gotoxy(int x, int y)
	{
		COORD c = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}

	void create_first_menu() {
		first_menu_right = ("| " + points_of_first_menu[0] + " | " + points_of_first_menu[1] + " |").size();

		first_menu.push_back("+" + padTo(first_menu_right - 2, '-') + "+");
		first_menu.push_back("| " + points_of_first_menu[0] + " | " + points_of_first_menu[1] + " |");
		first_menu.push_back("+" + padTo(first_menu_right - 2, '-') + "+");
	}

	void create_second_menu0() {
		vector<int> sizes;
		for (auto point : points_of_second_menu[0]) {
			sizes.push_back(point.size());
		}
		int max_length = *max_element(sizes.begin(), sizes.end());
		second_menu0.push_back("+" + padTo(max_length + 2, '-') + "+");
		for (auto point : points_of_second_menu[0]) 
			second_menu0.push_back("| " + padTo(point, max_length) + " | ");
		second_menu0.push_back("+" + padTo(max_length + 2, '-') + "+");

		second_menu1_left = ("| " + padTo(max_length, max_length) + " | ").size();
	}

	void create_second_menu1() {
		vector<int> sizes;
		for (auto point : points_of_second_menu[1]) {
			sizes.push_back(point.size());
		}
		int max_length = *max_element(sizes.begin(), sizes.end());
		second_menu1.push_back("+" + padTo(max_length + 2, '-') + "+");
		for (auto point : points_of_second_menu[1]) 
			second_menu1.push_back("| " + padTo(point, max_length) + " | ");
		second_menu1.push_back("+" + padTo(max_length + 2, '-') + "+");
	}

	void display_first_menu() {
		for (int i = 0; i < 3; i++) {
			gotoxy(0, i);
			cout << first_menu[i];
		}
		light_point_of_first_menu();
	}

	void display_second_menu() {
		if (!choosen_point)
			for (int i = first_menu_bottom; i < second_menu0.size() + first_menu_bottom; i++) {
				gotoxy(0, i);
				cout << second_menu0[i - first_menu_bottom];
			}
		else
			for (int i = 3; i < second_menu1.size() + first_menu_bottom; i++) {
				gotoxy(second_menu1_left - 2, i);
				cout << second_menu1[i - first_menu_bottom];
			}
		light_point_of_second_menu();
	}

	void Choise() {

		switch (level_of_menu) {
		case 0:
			choosen_point = point_of_menu;
			point_of_menu = 0;
			level_of_menu++;
			display_second_menu();
			break;
		case 1:
			print_description();
			break;
		}

	}

	void HideMenu() {
		if (level_of_menu == 1) {
			system("cls");
			level_of_menu--;
			point_of_menu = 0;
			display_first_menu();
		}
	}

	void Changepoint_of_menu(int direction)
	{
		if (level_of_menu == 0) {
			if (point_of_menu > 0)
				if (direction == LEFT)
					--point_of_menu;
			if (point_of_menu < 1)
				if (direction == RIGHT)
					++point_of_menu;
		}
		else { 	
		if (point_of_menu > 0)
			if (direction == UP)
				--point_of_menu;
		if (point_of_menu < 2)
			if (direction == DOWN)
				++point_of_menu;
		}
	}

	void ChangeColor(std::string color) {
		{
			if (color == "default")
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((7 << 4) | 0));
			if (color == "reverse_default")
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | 7));
		};
	}

	void light_point_of_first_menu() {
		ChangeColor("reverse_default");
		string text = "| " + points_of_first_menu[0] + " | " + points_of_first_menu[1] + " |";
		int x = text.find(points_of_first_menu[point_of_menu]);
		gotoxy(x, 1);
		cout << points_of_first_menu[point_of_menu];
		ChangeColor("default");
	}

	void light_point_of_second_menu() {
		ChangeColor("reverse_default");
		if (!choosen_point) {
			gotoxy(second_menu0_left + 2, second_menu0_top + point_of_menu + 1);
			cout << points_of_second_menu[choosen_point][point_of_menu];
		}
		else
		{
			gotoxy(second_menu1_left, second_menu1_top + point_of_menu + 1);
			cout << points_of_second_menu[choosen_point][point_of_menu];
		}

		ChangeColor("default");
	}

public:

	Menu() {
		create_first_menu();
		create_second_menu0();
		create_second_menu1();
		display_first_menu();
	}

	void Control() {

		char code = _getch();
		switch (code) {
		case 8: HideMenu(); break;
		case 13:  Choise(); return;
		case LEFT:	 Changepoint_of_menu(code); break;
		case RIGHT:  Changepoint_of_menu(code); break;
		case UP:     Changepoint_of_menu(code); break;
		case DOWN:   Changepoint_of_menu(code); break;
		default: return;
		}
		if (!level_of_menu)
			display_first_menu();
		else
			display_second_menu();

	}
};


int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	CONSOLE_CURSOR_INFO CCI;
	CCI.bVisible = false;
	CCI.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
	Menu menu;

	while (true) {	
		menu.Control();
	}

}