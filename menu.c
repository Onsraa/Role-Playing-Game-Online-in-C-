#include <ncurses.h>
#include <string.h>
#include <stdbool.h>
#include "./Struct/struct.h"
#include "./sql.h"

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

void introduction(User *user){

    char choice;

    do{
        system("clear");
        printf("Welcome to the " COLOR_RED_TERMINAL "unrealm" COLOR_RESET_TERMINAL ".\n\nDo you want to start a new adventure ? (y)es - (n)o\n\n");
        scanf("%c", &choice);
    }while(choice != 'y' && choice != 'n');

    switch(choice){
        case 'y':
            start(user);
            break;
        case 'n':
            system("clear");
            printf("Oh okay.. bye then.\n\n");
            exit(EXIT_SUCCESS);
    }
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
            introduction(user);
            break;
        }
    }

    main_menu(user);
}


void main_menu(User *user){

    int answer;

    int difficulty = 1;
    int auto_mode = 1;
    int dialogue = 1;

    do{
        system("clear");
        printf("#####################[MENU]#####################\n\n");
        printf("1 - Start adventure !\n");
        printf("2 - Check characters\n");
        printf("3 - Modify parameters\n");
        printf("4 - Save data\n");
        printf("5 - Leave unrealm\n\n");
        printf("################################################\n\n");

        scanf("%d", &answer);
    }while(answer < 1 || answer > 5);
    
    switch(answer){
        case 1:
            generateMap(user, returnCurrentCharacter(user), difficulty, auto_mode, dialogue);
            break;
        case 2:
            character_menu(user);
            break;
        case 3:
            break;
        case 4:
            sendUserInfoToDB(user);
            break;
        case 5:
            break;
    }
}

void character_menu(User *user)
{

    int choice;

    if (user->used_character != 0)
    {
        Character *current_character = user->characters[user->used_character - 1];

        do
        {
            system("clear");
            printf("What do you want to do ?\n\n");
            printf("1 - Choose a character\n");
            printf("2 - Open the bag\n");
            printf("3 - Add a new character\n");
            printf("4 - Delete a character\n");
            printf("5 - Delete all characters\n");
            printf("6 - Show stats\n");
            printf("7 - Menu\n\n");
            scanf("%d", &choice);
        } while (choice < 1 || choice > 7);

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
            do{
                system("clear");
                characterStats(current_character);
                printf("0 - Leave\n\n");
                scanf("%d", &choice);
            } while (choice != 0);
            main_menu(user);
            break;
        case 7:
            main_menu(user);
            break;
        }
    }
    else
    {
        do
        {
            system("clear");
            printf("What do you want to do ?\n\n");
            printf("1 - Create first character\n");
            printf("2 - Exit\n\n");
            scanf("%d", &choice);
        } while (choice < 1 || choice > 2);

        switch (choice)
        {
        case 1:
            chooseNewClass(user);
            break;
        case 2:
            main_menu(user);
            break;
        }
    }
}
