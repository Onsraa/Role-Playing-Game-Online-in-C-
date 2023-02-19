#include <ncurses.h>
#include <string.h>
#include <stdbool.h>
#include "./Struct/struct.h"

#define ARROW_UP KEY_UP
#define ARROW_DOWN KEY_DOWN

enum menu
{
    START_ADVENTURE = 0,
    CHECK_CHARACTERS = 1,
    CHECK_ITEMS = 2,
    SAVE = 3,
    EXIT = 4
};

void startingMenu()
{
    int i, c, currentItem = 0;
    int numItems = 5;
    char *menuItems[] = {"Start adventure", "Check characters", "Check items", "Save", "Exit"};
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

            if (selectedItem == "Start adventure")
            {
                selection = START_ADVENTURE;
            }
            else if (selectedItem == "Check characters")
            {
                selection = CHECK_CHARACTERS;
            }
            else if (selectedItem == "Check items")
            {
                selection = CHECK_ITEMS;
            }
            else if (selectedItem == "Save")
            {
                selection = SAVE;
            }
            else
            {
                selection = EXIT;
            }

            switch (selection)
            {
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

void start(User *user)
{

    if (!user)
    {
        printf("User not found\n");
        exit(EXIT_FAILURE);
    }

    char answer;

    if (!user->characters)
    {
        do
        {
            system("clear");
            printf("Welcome, let's initialize your first " COLOR_GREEN_TERMINAL "character" COLOR_RESET_TERMINAL ".\n\n");
            printf("You ready ? (y)es - (n)o\n\n");
            if (scanf("%c", &answer) != 1)
            {
                while (fgetc(stdin) != '\n')
                    ;
            };
        } while (answer != 'y' && answer != 'n');

        switch (answer)
        {
        case 'y':
            initializeNewCharacter(user);
            break;
        case 'n':
            exit(EXIT_SUCCESS);
            break;
        }
    }

    character_menu(user);
}

void character_menu(User *user)
{

    int choice;

    Character * current_character = user->characters[user->used_character - 1];

    do
    {
        system("clear");
        printf("What do you want to do ?\n\n");
        printf("1 - Choose a character\n");
        printf("2 - Open the bag\n");
        printf("3 - Add a new character\n");
        printf("4 - Delete a character\n");
        printf("5 - Delete all characters\n");
        printf("6 - Exit\n\n");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 6);

    switch (choice)
    {
    case 1:
        chooseCharacter(user);
        break;
    case 2:
        showBag(user, current_character);
        break;
    case 3:
        chooseNewClass(user);
        break;
    case 4:
        deleteCharacter(user);
        break;
    case 5:
        deleteAllCharacters(user);
        break;
    case 6:
        break;
    }
}
