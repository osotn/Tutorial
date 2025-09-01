#include <ncurses.h>

int main() {
    // Initialize the ncurses library and set up the terminal for curses mode
    initscr(); 


    // Измеряем размер экрана в рядах и колонках
    int row, col, ch;
    getmaxyx(stdscr, row, col);
  
    // перемещение курсора в стандартном экране
    move(row / 2, col / 2 - 10);

    // Print "Hello World !!!" to the standard screen (stdscr)
    printw("Hello World !!!"); 


        raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    	printw("Type any character to see it in bold\n");
	ch = getch();			/* If raw() hadn't been called
					 * we have to press enter before it
					 * gets to the program 		*/
	if(ch == KEY_F(1))		/* Without keypad enabled this will */
		printw("F1 Key pressed");/*  not get to us either	*/
					/* Without noecho() some ugly escape
					 * charachters might have been printed
					 * on screen			*/
	else
	{	printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}

    // Refresh the screen to display the changes
    refresh(); 

    // Wait for a single character input from the user before proceeding
    getch(); 

    // End curses mode, restoring the terminal to its original state
    endwin(); 

    return 0;
}
