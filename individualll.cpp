#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>

#define MAX_WORD_LENGTH 100
#define MAX_WRONG_GUESSES 5
#define NUMBER_OF_STAGES 5
#define WORDS_PER_STAGE 3
#define EXIT_KEY 27

void outtextxy_int(int x, int y, int value) 
{
    char num_str[10];
    sprintf(num_str, "%d", value);
    outtextxy(x, y, num_str);
}
void drawHangman(int wrongGuesses) 
{ 
setcolor (LIGHTRED);
setlinestyle(SOLID_LINE,5,6);
    int headX = 250, headY = 100, headRadius = 30;
    int bodyStartY = headY + headRadius, bodyEndY = bodyStartY + 100;
    int armStartY = bodyStartY + 30, armEndY = armStartY + 50;
    int legStartY = bodyEndY, legEndY = legStartY + 50;

    line(150, 50, 150, 300); 
    line(150, 50, 250, 50); 
    line(250, 50, 250, 70); 

    if (wrongGuesses >= 1) {

        circle(headX, headY, headRadius);
    }
    if (wrongGuesses >= 2) {
        line(headX, bodyStartY, headX, bodyEndY);
    }
    if (wrongGuesses >= 3) {
        line(headX, armStartY, headX - 30, armEndY); 
        line(headX, armStartY, headX + 30, armEndY); 
    }
    if (wrongGuesses >= 4) {
        line(headX, legStartY, headX - 30, legEndY);
        line(headX, legStartY, headX + 30, legEndY); 
    }
    if (wrongGuesses >= 5) {
    	setlinestyle(SOLID_LINE,5,1);
        line(238, 92, 244, 88);
        line(244, 92, 238, 88);

        line(254, 92, 260, 88);
        line(260, 92, 254, 88);
    }
}

void initializeWord(const char *word, char *hiddenWord) 
{
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        hiddenWord[i] = '_';
    }
    hiddenWord[len] = '\0';
}
void getInputFromGraphicsWindow(char *input, int maxLen) 
{
    int index = 0;
    char str[2] = "\0"; 
    while (index < maxLen - 1) {
        char ch = getch();
        if (ch == 13) { 
            break; 
        } else if (ch == 8) { 
            if (index > 0) 
            { 
                index--; 
                input[index] = '\0'; 
                outtextxy(10 + textwidth(input), 100, "  ");
            }
        } else 
            { 
            input[index++] = ch; 
            input[index] = '\0'; 
            str[0] = ch; 
            outtextxy(10 + textwidth(input) - textwidth(str), 100, str); 
            }
    }
    input[index] = '\0'; 
}
void updateHiddenWord(const char *word, char *hiddenWord, char guess) 
{
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (word[i] == guess) {
            hiddenWord[i] = guess;
        }
    }
}

char toLowercase(char c) 
{ 
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}


void displayMenuAndGetChoice(int &choice) 
{
	setcolor (LIGHTRED);
    char menuText[10][1000] = {
        "1. Multiplayer",
        "2. Single Player",
        "3. Exit"
    };
    
    cleardevice();
    for (int i = 0; i < 5; i++) {
        outtextxy(250, 225 + i * 15, menuText[i]);
    }

    char strChoice[3] = {0};
    outtextxy(30, 105, menuText[5]);


    do {
        char ch = getch(); 
        if (ch >= '1' && ch <= '3') { 
            strChoice[0] = ch;
            strChoice[1] = '\0'; 
            outtextxy(220, 85, strChoice); 
            choice = ch - '0'; 
            break; 
        }
    } while (true);
}

int main() 
{
    const char *stageWords[NUMBER_OF_STAGES][WORDS_PER_STAGE] = {
        {"glock", "iarna", "mandarine"},
        {"ak", "draco", "ar"},
        {"slaughter", "nle", "ice"},
        {"gang", "rap", "savage"},
        { "boston", "new-york", "atlanta"}
    };
    int choice;
    char  word[MAX_WORD_LENGTH],hiddenWord[MAX_WORD_LENGTH],hiddenWordDisplay[100];
    int stage = 0;
    char guess;
    int wrongGuesses;
int gd = DETECT, gm;
initgraph(&gd, &gm, "path to the BGI folder");
    srand(time(NULL));

    do {
        displayMenuAndGetChoice(choice);
        switch (choice) {
            case 1:
                { cleardevice(); 
        outtextxy(10, 10, "Enter a word ");

        getInputFromGraphicsWindow(word, MAX_WORD_LENGTH);

        initializeWord(word, hiddenWord);
        wrongGuesses = 0;
        while (wrongGuesses < MAX_WRONG_GUESSES) {
            cleardevice();

            strcpy(hiddenWordDisplay, "Mistery Word: ");
            strcat(hiddenWordDisplay, hiddenWord);
            outtextxy(10, 30, hiddenWordDisplay);

            drawHangman(wrongGuesses);

            outtextxy(10, 50, "Enter your word ");
            guess = getch();
           
            guess = toLowercase(guess);

            if (strchr(word, guess) != NULL) {
                updateHiddenWord(word, hiddenWord, guess);
                if (strcmp(word, hiddenWord) == 0) 
                {
                    strcpy(hiddenWordDisplay, "Mistery word: ");
                    strcat(hiddenWordDisplay, hiddenWord);
                    outtextxy(10, 30, hiddenWordDisplay);
                    outtextxy(30, 70, "Congratulations!");
                    getch();
                    break;
                }
            } else {
                wrongGuesses++;
            }
        }

        if (wrongGuesses == MAX_WRONG_GUESSES) {
            drawHangman(wrongGuesses);
            outtextxy(50, 70, "You lost!");
            getch();

            wrongGuesses = 0;
        }
        break;
		}

            case 2:
{
	srand(time(NULL));
	stage=0;
	while (stage < NUMBER_OF_STAGES) {
    cleardevice();
    const char *word = stageWords[stage][rand() % WORDS_PER_STAGE];
    initializeWord(word, hiddenWord);
    wrongGuesses = 0;

    while (wrongGuesses < MAX_WRONG_GUESSES) {
        cleardevice();


        char stageDisplay[MAX_WORD_LENGTH];
        sprintf(stageDisplay, "Stage: %d", stage + 1);
        outtextxy(10, 10, stageDisplay);


        char hiddenWordDisplay[MAX_WORD_LENGTH * 2];
        strcpy(hiddenWordDisplay, "Mistery Word: ");
        strcat(hiddenWordDisplay, hiddenWord);
        outtextxy(10, 30, hiddenWordDisplay);

        drawHangman(wrongGuesses);

        outtextxy(30, 70, "Enter your word ");
        outtextxy(10, 450, "(Press ESC to go back) ");
        guess = getch();
         if (guess == EXIT_KEY) 
		 {
		 	  printf("Exiting the single player game.\n");
		 	   goto EXIT_SINGLE_PLAYER;
	     }
        guess = toLowercase(guess);

        if (strchr(word, guess) != NULL) {
            updateHiddenWord(word, hiddenWord, guess);
            if (strcmp(word, hiddenWord) == 0) {
              strcpy(hiddenWordDisplay, "Mistery word: ");
            strcat(hiddenWordDisplay, hiddenWord);
                  outtextxy(10, 30, hiddenWordDisplay);
                outtextxy(30, 120, "You won!");
                getch();
                break;
            }
        } else {
            wrongGuesses++;
        }
    }

    if (wrongGuesses == MAX_WRONG_GUESSES) {
        drawHangman(wrongGuesses);
        char gameOverMsg[MAX_WORD_LENGTH * 2];
        strcpy(gameOverMsg, "You lost! ");
     
        outtextxy(30, 110, gameOverMsg);
        getch();
        break;
    } else {
        stage++;
    }

    if (stage == NUMBER_OF_STAGES) {
        outtextxy(30, 90, "Congratulations!");
        outtextxy(30, 120, "You won!");
        getch();
        stage = 0;
    }
}
 EXIT_SINGLE_PLAYER: ;
  break;}
 case 3:
               {
				 printf("Exiting the game.\n");
                break;
}
            default:
                printf("Invalid choice. Enter a number between 1 and 2.\n");
}
    } while (choice != 3); 
 closegraph();
    return 0;
}