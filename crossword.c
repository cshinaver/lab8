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
void sort_word_array_into_ascending_order(struct word words_array[]);
int next_empty_row(struct word words_array[15]);
//void place_word_into_board(
//        char *word_to_place,
//        char board_array[15][15]
//        );

int main () {
    char board_array[15][15];
    struct word words_array[15] = {{ 0 }};
    char test_word[] = "hi";


    //TODO load words into array from stdin
    // Init test array
    load_word_into_array(test_word, words_array);

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
    */

    int len_array = 15;
    int i;

    for (i = 0; i < 15; i++) {
        if (!words_array[i].row) {
            return i;
        }
    }

}
