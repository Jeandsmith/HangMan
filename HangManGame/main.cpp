#include <iostream>
#include <fstream>

void log(const char *msg); //To log messages to the screen
void display_game_title(); // Game title
void reset_buffer();
const char *pick_word();
const char get_user_input();

int main() {
	srand(static_cast<uint32_t>(time(nullptr)));
	return 0;
}

void log(const char *msg) {
	fputs(msg, stdout);
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
	const uint32_t ARR_SIZE = 2;
	const char * word_bank[] = {"BREAD", "PENGUINS"};
	const char * word = word_bank[rand() % ARR_SIZE];
	return word;
}

const char get_user_input(){
	puts("What is your guess? ");
	char input {};
	input = getc(stdin);
	return input;
}
