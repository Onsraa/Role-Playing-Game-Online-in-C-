#include <ncurses.h>
#include <string.h>
#include <stdbool.h>
#include "./Struct/struct.h"

#define ARROW_UP KEY_UP
#define ARROW_DOWN KEY_DOWN

enum menu {START_ADVENTURE = 0, CHECK_CHARACTERS = 1, CHECK_ITEMS = 2, SAVE = 3, EXIT = 4};

void startingMenu()
{
    int i, c, currentItem = 0;
    int numItems = 5;
    char *menuItems[] = { "Start adventure", "Check characters", "Check items", "Save", "Exit" };
    char *selectedItem;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int terminalWidth = getmaxx(stdscr);
    int terminalHeight = getmaxy(stdscr);
    int menuX;
    int menuY = (terminalHeight - numItems) / 2;

    while (true)
    {
        clear();

        for (i = 0; i < numItems; i++)
        {
            menuX = (terminalWidth - strlen(menuItems[i])) / 2;
            int x = menuX;
            int y = menuY + i;

            if (i == currentItem)
            {
                mvprintw(y, x - 3, ">> ");
                printw("%s", menuItems[i]);
                mvprintw(y, x + strlen(menuItems[i]), " <<");
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

            int selection;

            if(selectedItem == "Start adventure"){
                selection = START_ADVENTURE;
            }else if(selectedItem == "Check characters"){
                selection = CHECK_CHARACTERS;
            }else if(selectedItem == "Check items"){
                selection = CHECK_ITEMS;
            }else if(selectedItem == "Save"){
                selection = SAVE;
            }else{
                selection = EXIT;
            }
            
            switch(selection){
                case START_ADVENTURE:
                    break;
                case CHECK_CHARACTERS:
                    break;
                case CHECK_ITEMS:
                    break;
                case SAVE:
                    break;
                case EXIT:
                    break;
            }

            refresh();
            getch();
            break;
        }
    }

    endwin();
}
