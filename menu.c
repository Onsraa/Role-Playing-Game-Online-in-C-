#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

#define ARROW_UP KEY_UP
#define ARROW_DOWN KEY_DOWN

int main(void)
{
    int i, c, currentItem = 0;
    int numItems = 5;
    char *menuItems[] = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
    char *selectedItem;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int terminalWidth = getmaxx(stdscr);
    int terminalHeight = getmaxy(stdscr);
    int menuX = (terminalWidth - strlen(menuItems[0])) / 2;
    int menuY = (terminalHeight - numItems) / 2;

    while (true)
    {
        clear();

        for (i = 0; i < numItems; i++)
        {
            int x = menuX;
            int y = menuY + i;

            if (i == currentItem)
            {
                attron(A_REVERSE);
                mvprintw(y, x - 2, ">> ");
                printw("%s", menuItems[i]);
                mvprintw(y, x + strlen(menuItems[i]), " <<");
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(y, x, "%s", menuItems[i]);
            }
        }

        refresh();
        c = getch();

        if (c == ARROW_UP)
        {
            currentItem--;
            if (currentItem < 0)
            {
                currentItem = numItems - 1;
            }
        }
        else if (c == ARROW_DOWN)
        {
            currentItem++;
            if (currentItem == numItems)
            {
                currentItem = 0;
            }
        }
        else if (c == '\n')
        {
            selectedItem = menuItems[currentItem];
            mvprintw(menuY+numItems+1, menuX, "Selected: %s", selectedItem);
            refresh();
            getch();
            break;
        }
    }

    endwin();
    return 0;
}
