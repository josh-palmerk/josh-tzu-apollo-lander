/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 09: Pointer Arithmetic
 * 3. Assignment Description:
 *      Traverse a string using pointer notation
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/


/**************************************
 * COUNT - ARRAY
 **************************************/
int countArray(char *str, char target) {
	int count = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == target) count++;

	};

	return count;
}


/**************************************
 * COUNT - POINTER
 **************************************/

int countPointer(char *str, char target) {
	int count = 0;
	while (*str != '\0') {
		if (*str == target) count++;
		str++;
	}
	return count;
}
