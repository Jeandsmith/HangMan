#include <iostream>
#include <fstream>

void log(const char *msg); //To log messages to the screen
void reset_buffer();
const char *pick_word();
const uint32_t word_length(const char *c);

int main() {
	srand(static_cast<uint32_t>(time(nullptr)));
	log("HANGMAN \n");

	const uint32_t LENGTH {word_length(pick_word())};
	printf("%d \n", LENGTH);

	char word_mask [LENGTH];
	for (int i = 0; i < LENGTH; i++){
		word_mask[i] = '-';
	}

	printf("Word:  %s \n", word_mask);
//
//	uint32_t player_lives = 3, guess = 0;
//	const char * chosen_word = pick_word();
//	while (player_lives != 0){
//		++guess;
//		printf("Enter guess: %d \n", guess);
//		const char ch {static_cast<char>(toupper(getc(stdin)))};
//		std::cin.ignore();
//		for (int c = 0; chosen_word[c]; c++){
//			if ( ch != chosen_word[c]
//			    && c == word_length(chosen_word) - 1){
//				puts("Not found");
//				player_lives--;
//				printf("Lives: %d \n", player_lives);
//				reset_buffer();
//				break;
//			}
//
//			if (ch == chosen_word[c]){
//				if (chosen_word[c] == word_mask[c]){
//					continue;
//				}
//				word_mask[c] = chosen_word[c];
//				printf("Word:  %s \n", word_mask);
//				reset_buffer();
//				break;
//			}
//		}
//	}
	return 0;
}

void log(const char *msg) {
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
			const uint32_t MAX_BUFFER = 100;
			char ss[MAX_BUFFER];
			if (fgets(ss, MAX_BUFFER, file) == nullptr) break;
			fputs(ss, stdout);
		}
		fclose(file);
	}

}

void reset_buffer() {
	fflush(stdout);
}

const char *pick_word() {
	uint32_t arr_size = 0;
	const char * word_bank[] = {"BREAD", "PENGUINS", "SAUSAGE", "WORLD", "CAR"};
	for (const char *word: word_bank){
		if (word == 0) break;
		arr_size++;
	}

	const char * word = word_bank[rand() % arr_size];
	return word;
}

const uint32_t word_length(const char *c){
	uint32_t size {0};
	for (; *c; c++){
		size++;
	}

	return size;
}