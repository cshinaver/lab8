#include <stdio.h>
#include <string.h>

enum Orientation {
    down,
    across
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
void print_playing_board(char board_array[][15]);
void print_solution_board(char board_array[][15]);
int place_word_into_board(struct word *word_to_place, char board_array[][15]);
int can_word_be_placed(int row, int column, int shared_letter_index, enum Orientation desired_orientation, char word[], char board_array[][15]);
void place_word(
        int row,
        int column,
        enum Orientation orientation,
        char word[],
        char board_array[][15]
        );
enum Orientation find_word_orientation(int row, int column, char board_array[][15]);

int main () {
    int i, number_of_words;
    char board_array[15][15] = { 0 };
    struct word words_array[15] = {{ 0 }};

    //#########################TESTING PURPOSES#################
    char word1[] = "Bananas";
    char word2[] = "are";
    char word3[] = "the";
    char word4[] = "greatest";
    char word5[] = "fruit";
    char word6[] = "fat";



    //TODO load words into array from stdin and keep track of words with number_of_words
    // Init test array
    load_word_into_array(word1, words_array);
    load_word_into_array(word2, words_array);
    load_word_into_array(word3, words_array);
    load_word_into_array(word4, words_array);
    load_word_into_array(word5, words_array);
    load_word_into_array(word6, words_array);


    //##########################################################

    // Sort array, place first word in center of array,
    // and store word properties 
    sort_word_array_into_descending_order(words_array);
    place_word(6, 3, across, words_array[0].text, board_array);
    words_array[0].row = 6;
    words_array[0].column = 3;
    words_array[0].word_orientation = across;

    // Place remaining words into board
    for (i = 1; i < 15; i++) {
        if (words_array[i].text[0]) {
            place_word_into_board(&words_array[i], board_array);
        }
    }

    // Print solution and playing board
    print_playing_board(board_array);
    printf("\n\n\n");
    print_solution_board(board_array);

    return 0;
}

void load_word_into_array(char word[], struct word words_array[]) {
    /*
       Loads given word into words array
    */

    strcpy(words_array[next_empty_row(words_array)].text, word);

}

int place_word_into_board(struct word *word_to_place, char board_array[][15]) {
    /*
       Checks board for common letters and places word appropriately
    */

    int letter_index, row_index, column_index, len_word, desired_row, desired_column;
    enum Orientation existing_word_orientation, desired_orientation;

    len_word = strlen((*word_to_place).text);

    // First loop, iterates through letters of given word
    for (letter_index = 0; letter_index < len_word; letter_index++) {
        // Second loop iterates through board rows
        for (row_index = 0; row_index < 15; row_index++) {
            // Third loop iterates through board columns
            for (column_index = 0; column_index < 15; column_index++) {
                // Check for letter in row
                // If letter is found, attempt to place word
                if (board_array[row_index][column_index] == (*word_to_place).text[letter_index]) {
                    // Find orientation of already existing word
                    existing_word_orientation = find_word_orientation(row_index, column_index,board_array);

                    if (existing_word_orientation == down) {
                        desired_orientation = across;
                    }
                    else if (existing_word_orientation == across) {
                        desired_orientation = down;
                    }

                    // Find desired starting location
                    if (desired_orientation == across) {
                        desired_row = row_index;
                        desired_column = column_index - letter_index;
                    }
                    else if (desired_orientation == down) {
                        desired_column = column_index;
                        desired_row = row_index - letter_index;
                    }


                    // for each letter, check for adjacent letters
                    if (can_word_be_placed(desired_row, desired_column, letter_index, desired_orientation, (*word_to_place).text, board_array)) {
                        place_word(desired_row, desired_column, desired_orientation, (*word_to_place).text, board_array);
                        (*word_to_place).word_orientation = desired_orientation;
                        (*word_to_place).row = desired_row;
                        (*word_to_place).column = desired_column;
                        return 0;
                    }


                }
            }
        }
    }


}



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


void sort_word_array_into_descending_order(struct word words_array[15])
{
	/*
	 * sort strings in word array in descending order by length of that string
	*/

	int numberOfWords,i,j,k = 0,flag;
	struct word a;


	numberOfWords = next_empty_row(words_array);

	for (i = 0; i < numberOfWords; i++)
	{
		for  (j = 0; j < numberOfWords; j++)
		{
			if (strlen(words_array[j].text) < strlen(words_array[j+1].text)) // check if next string is longer than previous 
			{
				// switch strings if one is longer than other
				a = words_array[j+1];
				words_array[j+1] = words_array[j];
				words_array[j] = a;
				flag++;
			}
			
		}
		if (flag == 0)
		{
			break;
		}

	}
}

void print_playing_board(char board_array[][15]) {
    /*
       Prints board with pound signs and blank spaces
       where words are located
    */

    int letter_index, row_index;

    for (row_index = 0; row_index < 15; row_index++) {
        for (letter_index = 0; letter_index < 15; letter_index++) {
            if (board_array[row_index][letter_index]) {
                printf("  ", board_array[row_index][letter_index]);
            }
            else {
                printf("# ");
            }
        }
        printf("\n");
    }
}

void print_solution_board(char board_array[][15]) {
    /*
       Prints board with pound signs
       and words are displayed in their appropriate spaces
    */
    
    int letter_index, row_index;

    for (row_index = 0; row_index < 15; row_index++) {
        for (letter_index = 0; letter_index < 15; letter_index++) {
            if (board_array[row_index][letter_index]) {
                printf("%c ", board_array[row_index][letter_index]);
            }
            else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

enum Orientation find_word_orientation(int row, int column, char board_array[][15]) {
    

    //TODO Doesn't deal with overlapping words
    enum Orientation word_orientation;

    // Not at edges of board
    if ((column > 0 && column < 15) && (row > 0 && row < 15)) {
        if (board_array[row][column + 1] != 0 || board_array[row][column - 1] != 0) {
            word_orientation = across;
        }
        else {
            word_orientation = down;
        }

    }
    
    // Edges of board
    if (column == 0 || column == 15) {
        word_orientation = across;
    }
    if (row == 0) {
        if (board_array[row + 1][column]) {
            word_orientation = down;
        }
        else {
            word_orientation = across;
        }
    }
    else if (row == 15) {
        if (board_array[row - 1][column]) {
            word_orientation = down;
        }
        else {
            word_orientation = across;
        }
    }

    if (column == 0) {
        if (board_array[row][column + 1]) {
            word_orientation = across;
        }
        else {
            word_orientation = down;
        }
    }
    else if (column == 15) {
        if (board_array[row][column - 1]) {
            word_orientation = across;
        }
        else {
            word_orientation = down;
        }
    }

    return word_orientation;
}

void place_word(
        int row,
        int column,
        enum Orientation orientation,
        char word[],
        char board_array[][15]
        ) {
    /* 
       Places word at passed locations 
    */

    int i;
    int len_str = strlen(word);

    if (orientation == down) {
        for (i = 0; i < len_str; i++) {
            board_array[row + i][column] = word[i];
        }
    }
    else if (orientation == across) {
        for (i = 0; i < len_str; i++) {
            board_array[row][column + i] = word[i];
        }
    }
}

int can_word_be_placed(int row, int column, int shared_letter_index, enum Orientation desired_orientation, char word[], char board_array[][15]) {
    /*
       Checks if word can be placed in desired row, column and orientation
       // TODO Possibly check the first letter behind position
    */

    int i, j, len_word;
    
    // Check if there are adjacent letters for every letter in word
    len_word = strlen(word);

    if (desired_orientation == down) {
        for (i = 0; i < len_word; i++) {
            // If shared word, allow flanking letters
            if (i == shared_letter_index && board_array[row + i + 1][column] == 0) {
                continue;
            }
            
            // Check for adjacent characters
            if (board_array[row + i][column + 1] == 0 && board_array[row + i][column - 1] == 0) {
                continue;
            }
            else {
                return 0;
            }
        }
    }
    else if (desired_orientation == across) {
        for (i = 0; i < len_word; i++) {
            // If shared word, allow flanking letters
            if (i == shared_letter_index && board_array[row][column + i + 1] == 0) {
                continue;
            }

            // Check for adjacent characters
            if (board_array[row + 1][column + i] == 0 && board_array[row - 1][column + i] == 0) {
                continue;
            }
            else {
                return 0;
            }
        }
    }


    return 1;
}
    
