#ifndef ANSWERS

#define ANSWERS

#define YES 1
#define NO 0

#endif


#define OK 0
#define MAX_LINE_LEN 256
#define MAX_LETTERS 16
#define MAX_WORDS 128
#define LEN_LINE_ERR -1
#define NO_WORDS_ERR -2
#define CANNOT_READ_ERR -3
#define EMPTY_ERR -4
#define WORD_LEN_ERR -5

#define LEN_LINE_MSG "Line must have less then 256 symbols"
#define NO_WORDS_MSG "Only separators in line"
#define FIND_EOF_MSG "Finded EOF"
#define EMPTY_LINE_MSG "Line is empty"
#define LEN_WORD_MSG "Word must be less then 16 symbols"

int my_split();
int my_strstr();
int is_separator();
int repeat_check();
int str_equality();
void my_strcpy();
int errors_check();
void form_answers();