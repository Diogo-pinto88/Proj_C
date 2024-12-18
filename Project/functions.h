#ifndef functions_h
#define functions_h


#define BUFFERSIZE 8192

#define FALSE 0
#define TRUE 1

#define MAT 9
#define DATE 11 
#define TIME 6
#define NEW_MAT 7
#define NUM_MAX_PARK 20
#define MEMO_ERR_MSG "memory allocation error."
#define PARK_EXISTS "%s: parking already exists.\n"
#define CAP_INVALID "%d: invalid capacity.\n"
#define COST_INVALID "invalid cost.\n"
#define LIMIT_PARKS "too many parks.\n"
#define PARK_NOT_EXISTS "%s: no such parking.\n"
#define PARK_FULL "%s: parking is full.\n"
#define INVALID_MAT "%s: invalid licence plate.\n"
#define CAR_ERROR "%s: invalid vehicle entry.\n"
#define CARR_ERROR "%s: invalid vehicle exit.\n"
#define TIME_ERROR "invalid date.\n"
#define NOT_REG "%s: no entries found in any parking.\n"
#define NUM_ARGUMENTS "invalid number of arguments.\n"

typedef struct Info_park
{
    char *name;
    int capacity;
    int ocupation;
    float x;
    float y;
    float z;
    struct List_entries *cars;
} park;


typedef struct Time_format
{
    int day;
    int month;
    int year;
    int minute;
    int hour;
} time;


typedef struct Info_entries
{
    char reg[NEW_MAT];
    struct Time_format *in;
    struct Time_format *out;
    float cost;
} entry;


typedef struct List_park 
{
    struct Info_park *info;
    struct List_park *next;
    struct List_park *prev;
} park_list;


typedef struct List_entries
{
    struct Info_entries *info;
    struct List_entries *next;
    struct List_entries *prev;
} entries_list;

typedef struct Ordered_entries_list
{
    struct Ordered_entries_list *prev;
    struct Ordered_entries_list *next;
    struct Info_entries *info;
    struct Info_park *park;

} ordered;

#endif


/*
These functions allocate and initialise new structs or elements of a list
*/

park* Init_park();
entry* Init_entry();
entries_list* Init_entries_list();
park_list* Init_park_list();
time * Init_time();
ordered* Init_ordered();

/*
This Function adds a new park to the list of parks
*/

void Add_park_to_list(park *p,  park_list* l);


/*
This Function adds a new entry to the list of entries
*/

void Add_entry_to_list(entry *e, park* p);


/*
This function prints a park
*/

void Print_park(park_list* p);


/*
This function removes a park from the list of parks
*/

park_list* Remove_park(park* p, park_list* l);


/*
This function calculates the cost that a car has to pay, based on the time that it was parked
*/

void Calculate_cost(entry* e, park* p);


/*
These functions free's the structs
*/

void Free_park(park* p);
void Free_entry(entry* e);


/*
These functions free's an element of a list
*/

void Free_park_list_cell(park_list* c);
void Free_entries_list_cell(entries_list* c);


/*
These functions free's all the elements of a list
*/

void Free_all_entries(entries_list* h);
void Free_all_parks(park_list* h);


/*
* 	Function: Find_park_in_lis
* 
*	Description: This function searches for a park in a list of parks.
* 
*	Arguments: 
*		- char* name: The name of the park to be searched.
*       - park_list* l: The list of parks where the park will be searched.
*
*	Return Value:
*		- park*: The park that was found in the list.
*		- NULL, in case the park was not found.
*/
park* Find_park_in_lis(char* name, park_list* l);


/*
* 	Function: Find_entry
* 
*	Description: This function verifies if a car was parked in a park.
* 
*	Arguments: 
*		- park* p: The park where the car may have been parked.
*       - char* new: The matriculation of the car.

*	Return Value:
*		- entry*: The entry associated with the car.
*		- NULL, in case the car was not found.
*/
entry* Find_entry(park* p, char* new);


/*
* 	Function: Find_open_entry
* 
*	Description: This function will check if a car is parked in a park
* 
*	Arguments: 
*		- park* p: The park where the car can be parked.
*       - char* new: The matriculation of the car.

*	Return Value:
*		- entry*: The entry associated with the car.
*		- NULL, in case the car was not found.
*/
entry* Find_open_entry(park* p, char* new);


/*
* 	Function: Find_last_entry
* 
*	Description: This function compares the hour of entry and exit of a car and returns the bigger one
* 
*	Arguments: 
*		- park* p: The park where the car is parked.
*      
*	Return Value:
*		- max_in, in case the hour of entry is bigger than the hour of exit.
*		- max_out, in case the hour of exit is bigger than the hour of entry.
*/
time* Find_last_entry(park* p);


/*
* 	Function: Count_Args
* 
*	Description: This Function Returns the number of arguments in the input read
* 
*	Arguments: 
*		- char* str: The input that will be analyzed, a string.
*      
*	Return Value:
*		- integer args, the number of arguments in the input.
*/
int Count_Args(char* str);


/*
* 	Function: Check_full
* 
*	Description: This Function verify if a park is full
* 
*	Arguments: 
*		- park* p: The park that will be analyzed.
*      
*	Return Value:
*		- TRUE if the park is full.
*		- FALSE if the park is not full.
*/
int Check_full(park* p);


/*
* 	Function: Get_park_number
* 
*	Description: This Function returns the number of parks in a list of parks
* 
*	Arguments: 
*		- park_list* l: The list of parks that will be analyzed.
*      
*	Return Value:
*		- integer count, the number of parks in the list.
*/
int Get_park_number(park_list* l);


/*
* 	Function: Check_num_and_let
* 
*	Description: This Function checks if there is always a pair of letters and digits in the license plate and if doesn´t exists letter and digit in the same pair.
* 
*	Arguments: 
*		- char* num: The license plate that will be analyzed.
*      
*	Return Value:
*		- TRUE, if the license plate is valid in the format.
*		- FALSE if the license plate is not valid in the format.
*/
int Check_num_and_let(char *new);


/*
* 	Function: Check_num_and_let
* 
*	Description: This function verify that exists the caracter '-' in the middle of the pairs of digits or letters
* 
*	Arguments: 
*		- char* reg: The license plate that will be analyzed.
*      
*	Return Value:
*		- TRUE, if the license plate is valid in the format.
*		- FALSE if the license plate is not valid in the format.
*/
int Check_dash(char* reg);


/*
* 	Function: Check_equal
* 
*	Description: This function verify if the first two characters of a given string are either both letters or both digits.
* 
*	Arguments: 
*		- char* num: string with size 2 that will be analyzed.
*      
*	Return Value:
*		- TRUE, if the first two characters are both letters (A-Z) or both digits (0-9)
*		- FALSE, if the first two characters are not both letters or both digits.
*/
int Check_equal(char* num);


/*
* 	Function: Build_new_mat
* 
*	Description: This function builds a new matriculation withou the '-' for a easier use
* 
*	Arguments: 
*		- char* reg: The old license plate that will be reformulated.
*      
*	Return Value:
*		- new, the new license plate.
*/
char* Build_new_mat(char* reg);


/*
* 	Function: Build_new_mat
* 
*	Description: This function rebuilds the old license plate with the '-'.
* 
*	Arguments: 
*		- char* reg: The old license plate that will be reformulated.
*      
*	Return Value:
*		- old, the old license plate.
*/
char* Build_old_mat(char* reg);


/*
* 	Function: Time_to_int   
* 
*	Description: This function converts a 2 position string with the time to an integer.
* 
*	Arguments: 
*		- char* m: The string that will be converted.
*      
*	Return Value:
*		- integer, the time converted to an integer.
*/
int Time_to_int(char * m);


/*
* 	Function: Year_to_int   
* 
*	Description: This function converts a 4 position string with the year to an integer.
* 
*	Arguments: 
*		- char* Year: The string that will be converted.
*      
*	Return Value:
*		- integer, the time converted to an integer.
*/
int Year_to_int(char * Year);



/*
* 	Function: Day_in_month   
* 
*	Description: This function returns the number of days in a month
* 
*	Arguments: 
*		- int m: The month that will be analyzed.
*      
*	Return Value:
*		- integer, the number of days in the month.
*/
int Day_in_month(int m);


/*
* 	Function: Day_in_month_before 
* 
*	Description: This function returns the number of days in the months before the month that is being analyzed
* 
*	Arguments: 
*		- int m: The month that will be analyzed.
*      
*	Return Value:
*		- integer days, the number of days in the months before the month.
*/
int Days_in_months_before(int m);


/*
* 	Function: Time_diference
* 
*	Description: This function compares the time of entry and exit of a car returning the difference, important to calculate the cost.
* 
*	Arguments: 
*		- time* t1: The time of entry of the car.
*		- time* t2: The time of exit of the car.
*      
*	Return Value:
*		- integer, the difference between the two times, in minutes.
*/
int Time_diference(time *t1, time* t2);


/*
* 	Function: Create_Park
* 
*	Description: This function creates a new park, updating the information of the park. 
* 
*	Arguments: 
*		- char* name: The name of the park.
*		- int capacity: The capacity of the park.
*		- float x: The value to be charged for the first 4 periods of 15 minutes.
*		- float y: The value for each additional period of 15 minutes, since the 1st hour.
*		- float z: The daily value of the park.
*      
*	Return Value:
*		- park*, the new park created.
*/
park* Create_Park(char *name, int capacity, float x, float y, float z);


/*
* 	Function: Create_entry
* 
*	Description: This function creates a new entry, updating the information of the entry.
* 
*	Arguments: 
*		- char* new: The license plate of the car.
*		- time* in: The time of entry of the car.
*      
*	Return Value:
*		- entry*, the new entry created.
*/
entry* Create_entry(char* new, time* in);


/*
* 	Function: Is_Text
* 
*	Description: This function verifys the content of a string.
* 
*	Arguments: 
*		- char c: The character that will be analyzed.
*      
*	Return Value:
*		- TRUE, if the content is valid in the format.
*		- FALSE, if the content is not valid in the format.
*/
int Is_Text(char c);


/*
* 	Function: verify_date
* 
*	Description: This function verifys if the date has the correct format, and the values are valid.
* 
*	Arguments: 
*		- char* s: The string that will be analyzed.
*      
*	Return Value:
*		- TRUE, if the content is valid in the format.
*		- FALSE, if the content is not valid in the format.
*/
int verify_date(char* s);


/*
* 	Function: verify_hour
* 
*	Description: This function verifys if the hour has the correct format, and the values are valid.
* 
*	Arguments: 
*		- char* s: The string that will be analyzed.
*      
*	Return Value:
*		- TRUE, if the content is valid in the format.
*		- FALSE, if the content is not valid in the format.
*/
int verify_hour(char* s);


/*
* 	Function: date_and_hour_to_int
* 
*	Description: This function converts the date and hour to an integer, saving the content in a time struct.
* 
*	Arguments: 
*		- char* date: The date that will be analyzed.
*		- char* hour: The hour that will be analyzed.
*      
*	Return Value:
*		- time*, the time converted to an integer.
*/
time* date_and_hour_to_int(char* date, char* hour);


/*
* 	Function: Print_Date_and_Time
* 
*	Description: This function prints the date and the hour.
* 
*	Arguments: 
*		- time* t: The time that will be printed.
*      
*	Return Value:
*		- char*, the date and the hour printed.
*/
char* Print_Date_and_Time(time* t);


/*
* 	Function: Get_Name
* 
*	Description: Retrieves a name from a string:
*		- If it is delimited by '"', the name retrieved is everythin inside;
*		- If it isn't, the name retrieved is a string delimited by spaces; 
* 
*	Arguments: 
*		- char* str: The string that will be analyzed.
*      
*	Return Value:
*		- An array of size 2 with 2 pointers to char:
*			- In the first position, a pointer to a string with
*				the name of the park read.
*			- In the second position, a pointer to the position in the original
*				string immediatly after the name read.
*/
char** Get_Name(char* str);


/*
* 	Function: Search_in_Parks
* 
*	Description: This function checks if a car is parked in a park, without the exit time.
* 
*	Arguments: 
*		- park_list* l: The list of parks that will be analyzed.
*		- char* new: The license plate of the car.
*      
*	Return Value:
*		- entry*, the entry associated with the car.
        - NULL, if the car is not parked.
*/
entry* Search_in_Parks(park_list* l, char* new);


/*
* 	Function: Search_in_Parks_out
* 
*	Description: This function checks if a car has been parked in a park, there may be an exit time. 
* 
*	Arguments: 
*		- park_list* l: The list of parks that will be analyzed.
*		- char* new: The license plate of the car.
*      
*	Return Value:
*		- entry*, the entry associated with the car.
        - NULL, if the car is not parked.
*/
entry* Search_in_Parks_out(park_list* l, char* new);


/*
* 	Function: Order_parks_by_name
* 
*	Description: This function orders the parks by name. 
* 
*	Arguments: 
*		- park_list* l: The list of parks that will be analyzed.
*      
*	Return Value:
*		- park_list*, park list copy that has the parks ordered by name.
*/
park_list* Order_parks_by_name(park_list* l);


/*
* 	Function: Order_list_by_out_date
* 
*	Description: This function orders the parks by out date and hour. 
* 
*	Arguments: 
*		- entries_list* l: The list of entries that will be analyzed.
*      
*	Return Value:
*		- entries_list*, entries list copy that has the entries ordered by out date and hour.
*/
entries_list* Order_list_by_out_date(entries_list* l);


/*
* 	Function: Add_to_list_in_order_name
* 
*	Description: Inserts a new park into the park list while maintaining alphabetical order by the names of the parks.
* 
*	Arguments: 
*		- park_list* head: The list of parks that will be analyzed.
*		- park* p: The park that will be inserted.
*		
*	Return Value:
*		- park_list*, returns the pointer to the head of the list after insertion.
*/
park_list* Add_to_list_in_order_name(park_list* head, park* p);


/*
* 	Function: Add_to_list_in_order_out
* 
*	Description: Inserts a new entry into the entries list while maintaining order based on the 'out' timestamp.
* 
*	Arguments: 
*		- entries_list* head: The list of entries that will be analyzed.
*		- entry* e: The entry that will be inserted.
*      
*	Return Value:
*		- entries_list* - returns the pointer to the head of the list after insertion.
*/
entries_list* Add_to_list_in_order_out(entries_list* head, entry* e);


/*
*   Function: Add_to_list_in_order_v
* 
*   Description: Adds an element to the list in an ordered manner, first by the park name in alphabetical order, and then by entry 'in' time within the same park.
* 
*	Arguments: 
*		- ordered* head: The ordered list of entries that will be analyzed.
*		- entry* e: The entry that will be inserted.
*		- park* p: The park associated with the entry.
*      
*	Return Value:
*		- ordered* - returns the pointer to the head of the list after insertion.
*/
ordered* Add_to_list_in_order_v(ordered* head, entry* e, park* p);


/*
* 	Function: List_ordered_v
* 
*	Description: This function generates a new ordered list of entries from a given park list where the entries match a specific matriculation.
* 
*	Arguments: 
*		- park_list* l: The list of parks that will be analyzed.
*		- char* new: The license plate of the car.
*      
*	Return Value:
*		- ordered*, the ordered list of entries.
*/
ordered* List_ordered_v(park_list* l, char* new);




