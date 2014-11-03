#include <stdio.h>
#include <string.h>

enum Orientation {
    up,
    down
};

struct word {
    char text[20];
    int row;
    int column;
    enum Orientation word_orientation;
};
    

void load_word_into_array(char word[], struct word words_array[]);
void sort_word_array_into_descending_order(struct word words_array[]);
int next_empty_row(struct word words_array[15]);
void print_playing_board(char board_array[]);
void print_solution_board(char board_array[]);
//void place_word_into_board(
//        char *word_to_place,
//        char board_array[15][15]
//        );

int main () {
    char board_array[15][15];
    struct word words_array[15] = {{ 0 }};

    //#########################TESTING PURPOSES#################
    char word1[] = "Bananas";
    char word2[] = "are";
    char word3[] = "the";
    char word4[] = "greatest";
    char word5[] = "fruit";



    //TODO load words into array from stdin
    // Init test array
    load_word_into_array(word1, words_array);
    load_word_into_array(word2, words_array);
    load_word_into_array(word3, words_array);
    load_word_into_array(word4, words_array);
    load_word_into_array(word5, words_array);

    //##########################################################

    printf("%s", words_array[0].text);

    return 0;
}

void load_word_into_array(char word[], struct word words_array[]) {
    //TODO Write function
    /*
       Loads given word into words array
    */

    strcpy(words_array[next_empty_row(words_array)].text, word);

}

//void place_word_into_board() {
//    /*
//       Takes word and places it into 

int next_empty_row(struct word words_array[15]) {
    /*
       Takes zeroed structure array as argument,finds
       the first row that is "empty" and returns that index
       (which also happens to be the total number of stored words)
    */

    //TODO Possibly determine size of array without hard-coding?
    int len_array = 15;
    int i;

    for (i = 0; i < 15; i++) {
        if (!words_array[i].text[0] && !words_array[i].row) {
            return i;
        }
    }

}
void print_playing_board(char board_array[]) {
    /*
       Prints board with pound signs and blank spaces
       where words are located
    */
}

void print_solution_board(char board_array[]) {
    /*
       Prints board with pound signs
       and words are displayed in their appropriate spaces
    */
}
