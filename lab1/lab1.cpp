#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <conio.h>
const int horisontalLengthOfMenu = 33;
const int verticalLengthOfMenu = 3;
const int amountOfWords = 4;
bool IsMenuDisplayed = false; // отображается ли меню
bool echoMode = true;
/*переместить курсор по координатам*/
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
/*получить координаты консоли*/
void GetConsoleCursorPosition(int& x, int& y)
{
    COORD c;
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
    {
        c = cbsi.dwCursorPosition;
        x = c.X;
        y = c.Y;
    }
    else
    {
        x = 0;
        y = 0;
        std::cout << "ERROR";
    }
}

/*создание меню*/
void createmenu(std::string& str) {
    std::string menu[]{
    " Цвет вывода ",
    " Фон ",
    " Эхо ",
    " Выход ",
    };
    str += "+";
    for (int i = 0; i < horisontalLengthOfMenu; i++) str += "-";
    str += "+\n";
    for (int i = 0; i < amountOfWords; i++) {
        if (i % 2 == 0) str += "|" + menu[i] + "|";
        else str += menu[i];
    }
    str += "|\n";
    str += "+";
    for (int i = 0; i < horisontalLengthOfMenu; i++) str += "-";
    str += "+\n";

}
/*переключить отображение меню*/
void SwitchEchoMode(bool condition) {
    echoMode = condition;
}
void SwitchIsMenuDisplayed(bool condition) {
    IsMenuDisplayed = condition;
}

void ChangeColor(const char* attrubute)
{
    std::string color = "color ";
    int static font = 0, background = 7;
    int _font = font; // последний цвет шрифта 
    int _background = background; // последний цвет фона
    do {
        if (!strcmp(attrubute, "font"))
            while (_font == font || font == background)
                font = rand() % 16;
        else if (!strcmp(attrubute, "background"))
            while (_background == background || font == background)
                background = rand() % 16;
    } while (font == background);
    if (!strcmp(attrubute, "default"))
    {
        font = 7, background = 0;
    }

    if (background > 9) color += char(background + 55);
    else color += std::to_string(background);
    if (font > 9) color += char(font + 55);
    else color += std::to_string(font);

    system(color.data());
}
/*закрасить меню*/
void HideMenu(std::string textUnderMenu[]) {

    for (int i = 0; i < 3; i++) {
        gotoxy(0, i);
        std::cout << textUnderMenu[i];
    }
    for (int i = 0; i < 3; i++) {
        for (int j = textUnderMenu[i].length(); j < 35; j++) {
            gotoxy(j, i);
            std::cout << (char)32;
        }
    }
    SwitchIsMenuDisplayed(false);
}
/*скрыть меню*/
void HideMenu(std::string textUnderMenu[], int x, int y) {
    gotoxy(0, 20);
    for (int i = 0; i < verticalLengthOfMenu; i++) {
        for (int j = 0; j < horisontalLengthOfMenu + 2; j++) {
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    gotoxy(x, y);
    SwitchIsMenuDisplayed(false);
}
/*выбор пункта меню*/

void ChoiseMenu(int x, int y, std::string textUnderMenu[]) {
    if (y) {
        if (x >= 1 && x <= 13) {
            ChangeColor("font");
            SwitchEchoMode(false);
        }
        else if (x >= 15 && x <= 19) {
            ChangeColor("background");
            SwitchEchoMode(false);

        }
        else if (x >= 21 && x <= 25)
        {
            SwitchEchoMode(true);
            
        }
        else if (x >= 27 && x <= 33) {
            
            exit(0);
        }
    }
}
/*недает курсору выйти за границы*/

void CheckBorders(int& x, int& y) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= 120) x = 120;
}
/*отобразить меню*/
void DisplayMenu(int x, int y, std::string& str) {
    gotoxy(x, y);
    std::cout << str.data();
    SwitchIsMenuDisplayed(true);
}


enum { ENTER = 13, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80 };
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    ChangeColor("default");
    std::cout << "вывод меню на клавишу F2";
    std::string menu;
    createmenu(menu);
    std::string textUnderMenu[3];
    int x1 = 0, y1 = 0;
    int x2 = 0, y2 = 0;
    int step = 1;
    char c;
    SwitchEchoMode(false); // запрет на эхо мод в начале программы
    bool help = true; // чтобы очистить экран с подсказкой перед первым вызовом меню
    while (true) {
        c = _getch();
        switch (c) {
        case 60: {
            if (help) {
                system("cls");
                help = false;
            }
            if (!IsMenuDisplayed) 
                DisplayMenu(0, 20, menu); 

            x1 = 0, y1 = 20;
            gotoxy(x1, y1);
            break;
        }
        case 0: break;
        case LEFT: if (IsMenuDisplayed) { gotoxy(x1 -= step, y1); } break;
        case RIGHT: if (IsMenuDisplayed) { gotoxy(x1 += step, y1); } break;
        case UP: if (IsMenuDisplayed) { gotoxy(x1, y1 -= step); } break;
        case DOWN: if (IsMenuDisplayed) { gotoxy(x1, y1 += step); } break;
        case ENTER: if (IsMenuDisplayed) {
            ChoiseMenu(x1, y1, textUnderMenu);
            HideMenu(textUnderMenu, x2, y2);
            break;
        }
        }
        if (c == 0 || c == 60 || c == 13 || c == 8) continue;
        if (!IsMenuDisplayed && echoMode) {
            if ((c == LEFT || c == RIGHT || c == UP || c == DOWN)) {
                gotoxy(--x2, y2);
                std::cout << " ";
                gotoxy(x2, y2);
                continue;
            }
            else std::cout << c;
            GetConsoleCursorPosition(x2, y2);
            if (x2 >= 0 && x2 <= 35 && y2 >= 0 && y2 <= 2) {
                textUnderMenu[y2] += c;
            }
        }
        if (IsMenuDisplayed) {
            if (c == 100 || c == -30) {
                
                return 0;
            }
            if (c == 97 || c == -12) {
                ChangeColor("background");
                HideMenu(textUnderMenu, x2, y2);
                SwitchEchoMode(false);
            }
            if (c == 39 || c == -3) {
                
                HideMenu(textUnderMenu, x2, y2);
                SwitchEchoMode(true);
            }
            if (c == 119 || c == -10)
            {
                ChangeColor("font");
                HideMenu(textUnderMenu, x2, y2);
                SwitchEchoMode(false);
            }
        }
        CheckBorders(x1, y1);
    }
    system("pause");
    return 0;
}