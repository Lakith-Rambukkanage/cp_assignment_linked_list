LAB 1 - Linked List with concurrent access

The following folders are the "codeblocks" project folders of the different implementations of the linked list
	linked_list_serial
	linked_list_mutex
	linked_list_rw_lock

To run each implementation :
	1. install codeblocks and a c/c++ compiler
	2. open project file with the extention ".cbp"
		ex - "linked_list_serial.cbp"
	3. This should open the project workspace in Codeblocks
	4. Build and Run the program (Shortcut F9)

Configs can be set by modifying the following parameters:

	#define NUMBER_COUNT 1000
	#define METHOD_COUNT 10000
	int thread_count = 4;


	double m_frac = 0.99;
	double i_frac = 0.005;
	double d_frac = 0.005;

	int no_of_observations = 90;

In each project folder:
	-> main.c is the main program.
	-> linked_list_<implementation>_struct.h is the header 		file with linked list implementation. 
		ex - "linked_list_rw_struct.h"