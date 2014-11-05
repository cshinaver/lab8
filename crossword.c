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
void place_word_into_board(struct word *word_to_place, char board_array[][15]);
void place_word(
        int row,
        int column,
        enum Orientation orientation,
        char word[],
        char board_array[][15]
        );

int main () {
    char board_array[15][15] = { 0 };
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

    sort_word_array_into_descending_order(words_array);

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

void place_word_into_board(struct word *word_to_place, char board_array[][15]) {
    /*
       Checks board for common letters and places word appropriately
    */

    int letter_index, row_index, column_index, len_word;

    len_word = strlen((*word_to_place).text);

    // First loop, iterates through letters of given word
    for (letter_index = 0; letter_index < len_word; letter_index++) {
        // Second loop iterates through board rows
        for (row_index = 0; row_index < 15; row_index++) {
            // Third loop iterates through board columns
            for (column_index = 0; column_index < 15; column_index++) {
                // Check for letter in row
                if (board_array[row_index][column_index] == (*word_to_place).text[letter_index]) {
                    printf("%c is in row %i\n", (*word_to_place).text[letter_index], row_index);
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
                printf("# ");
            }
        }
        printf("\n");
    }
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

