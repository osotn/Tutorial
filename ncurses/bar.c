#include <ncurses.h>
#include <unistd.h> // для usleep

int main() {
    // Ініціалізація ncurses
    initscr();
    noecho();          // не виводити символи, які ми натискаємо
    curs_set(0);       // сховати курсор

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); // отримати розмір вікна

    int width = 50;               // ширина прогрес-бару
    int start_x = (max_x - width) / 2;
    int start_y = max_y / 2;

    for (int i = 0; i <= width; i++) {
        // Малюємо рамку
        mvprintw(start_y - 1, start_x, "Loading: %d%%", (i * 100) / width);
        mvaddch(start_y, start_x - 1, '[');
        mvaddch(start_y, start_x + width, ']');

        // Малюємо заповнення
        for (int j = 0; j < i; j++) {
            mvaddch(start_y, start_x + j, '#');
        }

        refresh();         // оновити екран, щоб побачити зміни
        usleep(50000);     // затримка 50 мс
    }

    mvprintw(start_y + 2, start_x + 15, "Done! Press any key.");
    getch();               // чекати натискання клавіші
    endwin();              // завершити роботу з ncurses

    return 0;
}

