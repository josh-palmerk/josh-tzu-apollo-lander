/*************************************************************
 * 1. Name:
 *      Josh and Tzu
 * 2. Assignment Name:
 *      Practice 08: Allocation
 * 3. Assignment Description:
 *      Allocate an array and then use it
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

 /****************************
  * ALLOCATE ONE FLOAT
  ****************************/
double* allocateOneFloat(double value) {
	double* ptr = new (nothrow) double; // Allocate memory for one double
	if (!ptr) return nullptr;        // Return nullptr if allocation failed
	*ptr = value;             // Assign the value to the allocated memory
	return ptr;               // Return the pointer to the allocated memory
};


/****************************
 * ALLOCATE ARRAY of DOUBLEs
 ****************************/


/****************************
 * DELETE ONE FLOAT
 ****************************/
void deleteOneFloat(double* ptr) {
	if (ptr) {
		delete ptr; 
		ptr = nullptr;
	}
}

/****************************
 * DELETE ARRAY of DOUBLEs
 ****************************/
