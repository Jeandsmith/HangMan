#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdint>
#include <memory>
#include <typeinfo>

const void log(const char *msg); //To log messages to the screen
void reset_buffer();
const char *pick_word();
const int32_t word_length(const char *c);
const void display_hanged_man();
void display_game_title();

int main() {

	display_game_title();

	srand(static_cast<uint32_t>(time(nullptr)));

	start:
	log("HANGMAN \n");

	const char * word{pick_word()};
	const int32_t CHAR_BUFFER{word_length(word) + 1};
	char word_mask[CHAR_BUFFER];
	word_mask[CHAR_BUFFER] = '\0';
	for (int i = 0; i < CHAR_BUFFER; i++) {
		word_mask[i] = '-';
	}

	printf("\n");
	printf("Word\' Length:  %d \n", CHAR_BUFFER);
	printf("%s \n", word_mask);

	uint32_t player_lives = 3, guess = 0;
	while (player_lives != 0) {
		reset_buffer();
		++guess;
		printf("Enter guess: %d \n", guess);
		char ch{static_cast<char>(toupper(getc(stdin)))};
		std::cin.ignore();

		for (int c = 0; word[c]; c++) {
			if (ch != word[c]
			    && c == word_length(word)) {
				puts("Not found");
				player_lives--;
				printf("Lives: %d \n", player_lives);
				reset_buffer();
				break;
			}

			if (ch == word[c]) {
				if (word[c] == word_mask[c]) {
					continue;
				}
				word_mask[c] = word[c];
				// printf("Word:  %s \n", word_mask);
				reset_buffer();
				break;
			}
		}

		if (std::string(word_mask) == std::string(word)) {
			puts("You have won the game!!");
		}

		if (player_lives == 0) {
			puts("You have lost the game. ");
			printf("The word was %s \n", word);
			display_hanged_man();
		}

		if (std::string(word_mask) == std::string(word)
		    || player_lives == 0){
			puts("Play again?");
			char ans = getc(stdin);
			std::cin.ignore();
			if (tolower(ans) == 'y') {
				goto start;
			} else break;
		}
	}

	return 0;
}

const void log(const char *msg) {
	puts(msg);
	fflush(stdout);
}

void display_game_title() {
	FILE *file;
	file = fopen(R"(../TextFiles/title_screen.txt)", "r");
	if (file == nullptr) {
		puts("Error opening file");
	} else {
		while (!feof(file)) {
			const int32_t MAX_BUFFER = 100;
			char ss[MAX_BUFFER];
			if (fgets(ss, MAX_BUFFER, file) == nullptr) break;
			fputs(ss, stdout);
		}
		fclose(file);
	}

	printf("Press Any Key To Continue\n");
	std::cin.get();

}

void reset_buffer() {
	fflush(stdout);
}

const char *pick_word() {
	int32_t arr_size = 0;
	const char *word_bank[] = {
			const_cast<char *>("BREAD"),
			const_cast<char *>("PENGUINS"),
			const_cast<char *>("SAUSAGE"),
			const_cast<char *>("WORLD"),
			const_cast<char *>("CAR"),
			"\0"
	};

	for (const char *word: word_bank) {
		if (word == "\0") break;
		arr_size++;
	}

	const char *word = word_bank[rand() % arr_size];
	return word;
}

const int32_t word_length(const char *c) {
	int32_t size{0};
	while (*c) {
		size++;
		c++;
	}

	return size - 1;
}

const void display_hanged_man(){
	FILE *file;
	file = fopen(R"(../TextFiles/hanged_man.txt)", "r");
	if (file == nullptr) {
		puts("Error opening file");
	} else {
		while (!feof(file)) {
			const int32_t MAX_BUFFER = 50;
			char ss[MAX_BUFFER];
			if (fgets(ss, MAX_BUFFER, file) == nullptr) break;
			fputs(ss, stdout);
		}
		fclose(file);
	}
}