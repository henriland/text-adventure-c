#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char file_content[1024][1024];
int file_rows = 0;
int chapter_number = 1;
int count_chapters = 1;
int chapter_locations[5];
int chapter_location_now = 0;
char answer[1] = "";


/*********************************************************************************/
/* READ THE FILE WHERE IS THE STORY AND SAVE IT TO A MULTIDIMENSIONAL CHAR ARRAY */
/*********************************************************************************/
int read_file(char *filename) 
{
    FILE* file = fopen(filename, "r");
    if(!file) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    while(fgets(file_content[file_rows], sizeof(file_content[file_rows]), file) != NULL) {
        file_content[file_rows][strcspn(file_content[file_rows], "\n")] = 0; // Remove empty lines from char
        file_rows++;
    }

    if (ferror(file)) { puts("I/O error when reading"); }
    else if (feof(file)) { /* Reading file was succesful */ }

    fclose(file);
}

/*********************/
/* CLEAR THE CONSOLE */
/*********************/
void clear_console() {
    puts("\x1B[2J");
}

/***********************************/
/* PRINT MESSAGE TO CONSOLE SCREEN */
/***********************************/
void print_message_to_console(char *message) {
    if(message == "error") {
        printf(ANSI_COLOR_RED "Wrong answer. Please try again.\n" ANSI_COLOR_RESET);
    } else {
        puts(message);
    }
}

/*****************/
/* TYPING READER */
/*****************/
void typing_reader() {
    answer[0] = 0;
    scanf("%s",answer);
}

/***********************/
/* PLAY A CHAPTER TEXT */
/***********************/
void play_chapter_text(char *chapter_text) {
    printf("%s\n\n",chapter_text);
}

/**************************/
/* GO TO THE NEXT CHAPTER */
/**************************/
void go_to_next_chapter() {
    chapter_number++;
    chapter_location_now++;
}

/*************************************************************************/
/* FIND THE CHAPTER LOCATIONS FROM THE TEXT FILE AND SAVE IT TO AN ARRAY */
/*************************************************************************/
void find_chapter_locations()
{
    int j = 0;
    for(int i = 0; i < file_rows; i++)
    {
        if(strcmp(file_content[i],"#") == 0)
        {
            chapter_locations[j] = i;
            j++;
        }
    }
}

/********************/
/* CONTROL THE GAME */
/********************/
void controller()
{
    if(chapter_number == 1) 
    {
        play_chapter_text(file_content[chapter_locations[chapter_location_now]+1]);
        play_chapter_text(file_content[chapter_locations[chapter_location_now]+2]);
        typing_reader();

        if(strcmp(answer,"a") == 0)
        {
            clear_console();
            play_chapter_text(file_content[chapter_locations[chapter_location_now]+3]);
            go_to_next_chapter();
            controller();
        }
        else if(strcmp(answer,"b") == 0)
        {
            clear_console();
            play_chapter_text(file_content[chapter_locations[chapter_location_now]+4]);
            go_to_next_chapter();
            controller();
        }
        else {
            clear_console();
            print_message_to_console("error");
            controller();
        }
    }
    else if(chapter_number == 2) 
    {
        play_chapter_text(file_content[chapter_locations[chapter_location_now]+1]);
        typing_reader();

        if(strcmp(answer,"222") == 0)
        {
            clear_console();
            play_chapter_text(file_content[chapter_locations[chapter_location_now]+2]);
            go_to_next_chapter();
            controller();
        }
        else {
            clear_console();
            print_message_to_console("error");
            controller();
        }
    }
    else if(chapter_number == 3)
    {
        play_chapter_text(file_content[chapter_locations[chapter_location_now]+1]);
        play_chapter_text(file_content[chapter_locations[chapter_location_now]+2]);
        typing_reader();

        if(strcmp(answer,"a") == 0)
        {
            clear_console();
            go_to_next_chapter();
            controller();
        }
        else {
            clear_console();
            print_message_to_console("error");
            controller();
        }       
    }
    else if(chapter_number == 4)
    {
        play_chapter_text(file_content[chapter_locations[chapter_location_now]+1]);
        typing_reader();

        if(strcmp(answer,"sun") == 0)
        {
            clear_console();
            play_chapter_text(file_content[chapter_locations[chapter_location_now]+2]);
            go_to_next_chapter();
            controller();
        }
        else {
            clear_console();
            print_message_to_console("error");
            controller();
        }
    }
    else if(chapter_number == 5)
    {
        play_chapter_text(file_content[chapter_locations[chapter_location_now]+1]);
        play_chapter_text(file_content[chapter_locations[chapter_location_now]+2]);
        play_chapter_text(file_content[chapter_locations[chapter_location_now]+3]);
        typing_reader();

        if(strcmp(answer,"a") == 0 || strcmp(answer,"b") == 0 || strcmp(answer,"c") == 0)
        {
            clear_console();
            puts("---------------------------------------------------");
            puts("---------------------------------------------------");            
            puts("YOU DID IT! YOU ENTERED THE TOWER AND WON THE GAME!");
            puts("---------------------------------------------------");
            puts("---------------------------------------------------");
        }
        else {
            clear_console();
            print_message_to_console("error");
            controller();
        }    
    }    
    else 
    {
        puts("ERROR! NO CHAPTER FOUND!");
    }
}

/*********************/
/* START THE PROGRAM */
/*********************/
int main(void)
{
    read_file("story.txt");
    clear_console();
    find_chapter_locations();
    controller();
}
