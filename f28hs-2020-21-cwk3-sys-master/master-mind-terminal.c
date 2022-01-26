/*
 * MasterMind: a cut down version with just the master-mind game logic (purely C) and no external devices

Sample run:
Contents of the sequence (of length 3):  2 1 1
Input seq (len 3): 1 2 3
0 2
Input seq (len 3): 3 2 1
1 1
Input seq (len 3): 2 1 1
3 0
SUCCESS after 3 iterations; secret sequence is  2 1 1

 * Compile:    gcc -o cw3  master-mind-terminal.c
 * Run:        ./cw3

 */

/* --------------------------------------------------------------------------- */

/* Library headers from libc functions */


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Variable declarations +++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

/* Constants */
#define  COL  3
#define  LEN  3

/* Global variables */

static const int colors = COL;
static const int seqlen = LEN;

static char* color_names[] = { "red", "green", "blue" };
static int* theSeq = NULL;

int guess[LEN];
int my_array[LEN];

int almost, match;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Aux functions +++++++++++++++++++++++++++++++++++++++++++++++++++++

/* initialise the secret sequence; by default it should be a random sequence, with -s use that sequence */
void initSeq() {
    int i;
    time_t t;
    srand((unsigned) time(&t));
    // initialises random number generator

    for (i = 0; i < seqlen; i++) {
      my_array[i] = 1 + rand()%3;
    }

    // loops through my_array and adds a random number from 1 to 3 at each position of the array
}

void arrInit(int length, int arr[]){ 
  int i;
  for(i = 0; i < length; i++){
      arr[i] = 1;
    }
  // This method is used to set every value in an array to 1. I use this as a true or false array for my showMatches method
  // as C does not have boolean values.
}

/* display the sequence on the terminal window, using the format from the sample run above */
void showSeq(int *seq) {

  printf("\n Secret Code %i %i %i \n", seq[0], seq[1], seq[2]);
  // prints each value in the sequence one by one 
}

/* counts how many entries in seq2 match entries in seq1 */
/* returns exact and approximate matches  */
void countMatches(int *seq1, int *seq2) {
    int i,n,q; 
    int secretarr[LEN];
    int guessarr[LEN];
    arrInit(LEN, secretarr);
    arrInit(LEN, guessarr);
    // initialise variables for looping and keeping track of matches and approx. matches

    for( n=0; n<LEN; n++ ) {
      if (seq1[n] == seq2[n]){
        match++;
        secretarr[n] = 0;
        guessarr[n] = 0;
      }
    }
    // loops through both sequences and if the values are the same increments match by 1

    for (i= 0; i<LEN; i++){
      for(q =0 ; q<LEN; q++){
        if(secretarr[i] != 0 && guessarr[q] != 0 && seq1[i] == seq2[q]){
          almost++; 
          
        }
      }
    }
    // Loops through all of the first sequence and the second sequence. If the value that the user entered is found
    // anywhere in the second sequence then the value of almost is incremented by 1.
}
//int code, /* only for debugging */
void showMatches(int code, /* only for debugging */int *seq1, int *seq2) {
  countMatches(seq1, seq2);
  printf("%i exact matches\n%i approximate matches\n", match, almost);
  // calls countMatches function to increment the values of the gloabal variables almost and match
  // then prints them in the format of "matches  approx. matches" 
}

void readString(int *arr) {
  int i;
  printf("\nEnter your guess:");

  for(i = 0; i < LEN ;i++){
    scanf("%d", &arr[i]);
    }
  // This is used to scan the user imput and set that to the guess array
}

void convertSeq(int* arr2, char *arr) {
  int i; 
  for(i = 0; i < LEN ;i++){
    arr2[i] = (int)arr[i] - 48;
  }
  // This is used to convert a character array to an integer array. It accomplishes this by coverting the array strings 
  // to ASCII and then converts that to its original int value by subtracting 48 which was found using the ASCII table.
}



/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ main method +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int main(int argc, char **argv){
  /* DEFINE your variables here */
  int found = 0, attempts = 0;
  /* for getopts() command line processing */
  int verbose = 0, help = 0, unittest = 0, debug = 0;
  char *sseq = NULL;
  char *guessChar = NULL;

  // see: man 3 getopt for docu and an example of command line parsing
  // Use this template to process command line options and to store the input
  {
    int opt;
    while ((opt = getopt(argc, argv, "vuds:")) != -1) {
      switch (opt) {
      case 'v':
	verbose = 1;
	break;
      case 'u':
	unittest = 1;
	break;
      case 'd':
	debug = 1;
	break;
      case 's':
	sseq = (char *)malloc(LEN*sizeof(char));
	strcpy(sseq,optarg);
	break;
      default: /* '?' */
	fprintf(stderr, "Usage: %s [-v] [-d] [-s] <secret sequence> [-u] <secret sequence> <guess sequence> \n", argv[0]);
	exit(EXIT_FAILURE);
      }
    }
    if (unittest && optind >= argc) {
      fprintf(stderr, "Expected argument after options\n");
      exit(EXIT_FAILURE);
    }

    if (verbose && unittest) {
      printf("1st argument = %s\n", argv[optind]);
      printf("2nd argument = %s\n", argv[optind+1]);
    }
  }

  if (verbose) {
    fprintf(stdout, "Settings for running the program\n");
    fprintf(stdout, "Verbose is %s\n", (verbose ? "ON" : "OFF"));
    fprintf(stdout, "Debug is %s\n", (debug ? "ON" : "OFF"));
    fprintf(stdout, "Unittest is %s\n", (unittest ? "ON" : "OFF"));
    if (sseq)  fprintf(stdout, "Secret sequence set to %s\n", sseq);
  }

  if (sseq) {
      convertSeq(my_array,sseq);
  }
  if (unittest) {
    convertSeq(my_array,argv[optind]);
    convertSeq(guess, argv[optind + 1]);
    showMatches(1, guess, my_array);
    exit (EXIT_SUCCESS);
  }
  if (!sseq && !unittest){
    initSeq();
  }

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ main loop +++++++++++++++++++++++++++++++++++++++++++++++++++++
    printf("\nWelcome to the game Mastermind, where you will try and guess a secret code.");
    printf("\nYou have 9 attempts to guess the code. The sequence is always 3 values long. ");
    printf("\nWhen you type in your guess please space the numbers apart by 1 space.");
    printf("\n\nThe game has started and a code has been generated."); 
    while (!found) {
 
      readString(guess);
      
      showMatches(1, guess, my_array);
      attempts++;
      
      if(match == 3){
        found = 1;
        break;
      }
      else if (attempts > 9) {
        break;
      }
      else {
        match = 0;
        almost = 0;
      }
    }
    if (found) {
      printf("\nSUCCESS, total number of attempts = %d \n", attempts);
    } 
    else {
      printf("\nFAILURE, could not find answer in the specified number of attempts \n");
      showSeq(my_array);
    }
    return EXIT_SUCCESS;
  }


