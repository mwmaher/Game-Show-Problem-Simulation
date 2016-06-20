/* GameProb.C

   By Michael W. Maher

   Ver 1.0 5/28/92

   The following program is simulation of the game show problem.  The problem
   is as follows:

	You are a contestant on a popular game show.  At one point during the
	show you are given the opportunity to select one of three doors.
	Behind two of the doors is a sheep.  Behind the other door is car.
	You select a door and the show's host offers you the chance to trade
	your door for the chance to choose one of the remaining doors. What
	should you do?

   The program was written in Microsoft C 5.0 for full ANSI C compatibility.
   An ANSI C compiler should be able to compile the program. If you have any
   questions or comments I would love to here from you.  I can be reached at
   the address above.
*/
/* include files */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* define statements */
#define MAX_DOORS 3
#define PICKS 2
#define PRIZE 69
#define LOSE  96

/* function prototypes */
char main(char argc, char **argv);
void initialize(int *doors, int *picks);
int  pick_door(int *picks);

/* program */
char main(char argc, char **argv)
  {
  long int i,
	   j,
	   k,
	   wins[PICKS],
	   trials = 5000;              /* initial number of trials */
  int doors[MAX_DOORS],
      picks[PICKS];
  time_t bintime;

  if (argc > 1)
    trials = atol(argv[1]);
  printf("\ntrials = %-ld", trials);
  printf("\nsimulating...");

  /* randomize, based on clock */
  time(&bintime);
  srand((unsigned)bintime);

  /* initialize score array */
  for (i = 0; i < PICKS; i++)
    wins[i] = 0;

  /* simulate the random 1st selection of a door */
  j = 0;                               /* initialize pick counter */
  k = 0;                               /* test */
  for (i = 0; i < trials; i++)
    {
    initialize(doors, picks);          /* initialize the doors */
    picks[j] = pick_door(picks);       /* select a door */
    if (doors[picks[j]] == PRIZE)
      wins[k] = wins[k] + 1;           /* tally the selection of a car */
    }

  /* simulate the random 1st selection of a door with a goat, then a 2nd
     selection of one of the remaining doors */
  j = 0;                               /* initialize pick counter */
  k = 1;                               /* test */
  for (i = 0; i < trials; i++)
    {
    initialize(doors, picks);          /* initialize the doors */
    picks[j] = pick_door(picks);       /* select a door */
    if (doors[picks[j]] == LOSE)
      {
      /* printf("\n1st%d",i);*/
      if (doors[pick_door(picks)] == PRIZE)
	wins[k] = wins[k] + 1;         /* tally cars selected */
      }
    else
      {
      /*printf("\n2nd%d",i);*/
      picks[j] = pick_door(picks);     /* pick a losing door */
      if (doors[pick_door(picks)] == PRIZE)
	wins[k] = wins[k] + 1;         /* tally cars selected */
      }
    }

  /* output */
  for (k = 0; k < PICKS; k++)
    printf("\n%ld selection wins = %-9ld  %.2f%%",
	    k+1, wins[k], (float)100.0f*(((float)wins[k]) / ((float)trials)));
  return(0);
  }


void initialize(int *doors, int *picks)
  {
  int i,
      selection;

  for (i = 0; i < MAX_DOORS; i++)
    doors[i] = LOSE;
  for (i = 0; i < PICKS; i++)
    picks[i] = -1;
  selection = (int) ((float)(MAX_DOORS) * (float) rand() / (float) 32767);
  doors[selection] = PRIZE;
  return;
  }


/***************************************************************************
     function: pick_door

   parameters: picks : a ptr to an array of integers, the array contains a
	       list of selections or "picks".

      purpose: Randomly, chooses a door number between 0 and MAX_DOORS - 1
	       that has not been previously choosen (in picks array).

      returns: A selection between 0 and (MAX_DOORS - 1) that is not in the
	       picks array.
****************************************************************************/
int pick_door(int *picks)
  {
  int selection,
      i,
      j,
      k = 0,
      temp[MAX_DOORS];

  for (i = 0; i < MAX_DOORS; i++)
    {
    j = 0;
    do
      {
      j++;
      }
    while ((picks[j] != -1) && (picks[j] != i) && (j < PICKS));
    if (picks[j] != i)
      {
      temp[k] = i;
      k++;
      }
    }
  selection = (int)((float) k * (float) rand() / (float) 32767);
  return(temp[selection]);
  }
