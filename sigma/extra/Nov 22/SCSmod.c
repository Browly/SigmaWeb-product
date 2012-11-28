/******************************************/
/* SIGMA RUN DEFAULTS FOR TRANSLATED MODEL */
/*******************************************/
/*

         MODEL DEFAULTS
         --------------

Model Name:         SCSmod
Model Description:  
Output File:        untitled.out
Output Plot Style:  NOAUTO_FIT
Run Mode:           HI_SPEED
Trace Vars:         PROFIT
Random Number Seed: 12346
Initial Values:     10,3.5,7,4,4,4,4,120,360,1,10,10.26,10.26,5.13,2.025,2.025,2.025,1.35,1.35,1.35,.54,.54,.54,0.4,0.4,0.2,0.1,0.3,0.3,0.3,0.1,0.3,0.3,0.3,0.1,0.3,0.3,0.3,30,40,2,2,12,15,2,2,7,10,2,2,2,4,2,2,1,3,2,2,0.2,1,2,2,0.5,2,2,2,0.5,2,2,2,0.5,2,2,2,13,17,2,2,.51,.61,.50,.66,.50,.63,.30,.46,.50,.15,.15,.15
Ending Condition:   STOP_ON_EVENT
Event:              CALC   (1 iterations)
Trace Events:       CALC
Hide Edges:         

*/
/*******************************************/


#include "sigmafns.h"
#include "sigmalib.h"

/* EVENT FUNCTIONS USED IN THE SIMULATION MODEL */
void   RUN(void);	/*** rnk[1]=1 denotes that the orderq is sorted by ent[1], the time the ID customer arrived (in increasing order), rnk[2]=6 denotes that Q is sorted by ent[6], the ID of customer (in increasing order, so that customers that arrived first get their cupcakes worked on first) ***/
void   CHECK_S(void);	/***  ***/
void   LEAVE(void);	/***  ***/
void   FINISH(void);	/***  ***/
void   SUP(void);	/***  ***/
void   ARRIVE(void);	/*** Customer arrives but doesn't get a chance to place an order. (We need to add a non order queue variable) ***/
void   JOINQ(void);	/***  ***/
void   NEXTQ(void);	/*** "2" is the location of the customers who have already ordered and their cupcakes are going through the process of being completed ***/
void   RESTK(void);	/*** RESTOCK[INDEX;TYPE] is a boolean array that is initally set to 0 for product INDEX of type TYPE (ex, product=cake, type=vanilla) and becomes one when that type of product is in the process of being restocked (this functions to eliminate multiple RESTOCKS being scheduled for a particular type of product) ***/
void   FINISHR(void);	/*** 20 is the extra amount that was made when a restock event was executed ***/
void   START_S(void);	/***  ***/
void   WARMUP(void);	/***  ***/
void   GET_PUT(void);	/***  ***/
void   AVAIL_W(void);	/***  ***/
void   CALC(void);	/***  ***/

/*   STATE VARIABLE DELARATIONS   */
long   I[7];	/***  array of customer order details  ***/
long   ID;	/***  customer ID number  ***/
long   TOTAL[10][1562];	/***    ***/
long   Q[15627];	/***    ***/
long   INDEX;	/***  index for checking stations  ***/
long   SUPPLY[5][4];	/***  Resources for station i and type j  ***/
double RESTOCK[5][4];	/***  0-1 array if ingregient in restock process  ***/
double RES[4];	/***  array of resources  ***/
double INPUT[15627];	/***  Various inputs from the client  ***/
double RESTOCKT[5][4];	/***  Restock distribution times  ***/
double SERVICET[5][4];	/***  Service distribution times  ***/
double CUSTPREF[5][4];	/***    ***/
double MISC[15627];	/***    ***/
double ALPHA[15627];	/***    ***/
double BETA[15627];	/***    ***/
double PROFIT;	/***    ***/
long   TYPE[15627];	/***    ***/
double THRESH[5][4];	/***    ***/

/*   EVENT FUNCTIONS   */
enum
   {
   run_end_event,
   RUN_event,
   CHECK_S_event,
   LEAVE_event,
   FINISH_event,
   SUP_event,
   ARRIVE_event,
   JOINQ_event,
   NEXTQ_event,
   RESTK_event,
   FINISHR_event,
   START_S_event,
   WARMUP_event,
   GET_PUT_event,
   AVAIL_W_event,
   CALC_event,
   };

/*    MAIN PROGRAM     */
int main(int argc, char** argv)
{
  int  next_event;
  char keytoclose = 'p';

  if(!startup_check(0))
    return -1;

  /* Initialize csiglib and simulation */
  while (initialize(argc, (const char * *)argv)) {;

  /* Schedule beginning of simulation */
  event_time = current_time;
  event_type = RUN_event;
  schedule_event();

/*  EVENT EXECUTION CONTROL LOOP */
  while (!run_error && !done) {
    /* Pull next event from event list */
    next_event = c_timing();

    /* increment the event count for this event */
    event_count[next_event]++;

    /* Call appropriate event routine */
    switch ( next_event ) {
      case run_end_event:  run_end();
               break;

      case RUN_event:  RUN();
               break;

      case CHECK_S_event:  CHECK_S();
               break;

      case LEAVE_event:  LEAVE();
               break;

      case FINISH_event:  FINISH();
               break;

      case SUP_event:  SUP();
               break;

      case ARRIVE_event:  ARRIVE();
               break;

      case JOINQ_event:  JOINQ();
               break;

      case NEXTQ_event:  NEXTQ();
               break;

      case RESTK_event:  RESTK();
               break;

      case FINISHR_event:  FINISHR();
               break;

      case START_S_event:  START_S();
               break;

      case WARMUP_event:  WARMUP();
               break;

      case GET_PUT_event:  GET_PUT();
               break;

      case AVAIL_W_event:  AVAIL_W();
               break;

      case CALC_event:  CALC();
               event_trace("CALC",event_count[next_event]);
               evnt_count = evnt_count + 1;
               if ((long)evnt_count ==(long)stop_event_count) {
                  /* Schedule end of simulation */
                  evnt_count = 0;
                  event_time = current_time;
                  event_type = run_end_event;
                  schedule_event();
                  }
               break;

      }
    }
  }
// experiments terminated
printf("Experiments ended! If runs end early: \n\r1. check fields in *.exp file. \n\r2. check if output file was already open. \n\r");
return 0;
}

void
event_trace(const char * name_of_event,const long count)
{
  c_timest(PROFIT, 1, 0);
  c_sampst(PROFIT, 1, 0);
  if(trace_flag) fprintf(output_fp, "%9.3f\t %6s\t%6d ",current_time,name_of_event,count);
  if(trace_flag) fprintf(output_fp, "	%7.3g \n"
,(double)PROFIT);
}



int
initialize(int argc, const char** argv)
{
static int first_time = 1;     /* First time in initialize? */
static FILE *input_fp;     /* For reading from the input file */
char *exp_file_name;       /* For constructing input file name */
char y_n = 'p';            /* yes/no for file overwrite*/

       char dir[256];
       char fname[256];
       char ext[256];
       char simulation[1024];
       char experient_name[1024];
        _splitpath( argv[0], NULL, dir, fname, ext );
       strcpy(simulation, fname);
       strcat(simulation, ext);
       strcpy(experient_name, fname);
       strcat(experient_name, ".exp");
     printf("Running the simulation: %s\n", simulation);
    if(strlen(dir) !=0)
       printf("In Path: %s\n",dir);
  if (first_time) {
    exp_file_name = _strdup(argv[0]);
    exp_file_name[strlen(exp_file_name)-1] = 'p';
    printf("\nLooking for experiment file: %s\n",experient_name);
    }

  if ((first_time && (input_fp=fopen(exp_file_name,"r"))!=NULL)
                                           || input_fp!=NULL) {
  if (first_time) {
     first_time = 0; /* Reset for next time into initialize */
     printf("Found. Use [Control]-C to abort replications.\n");
     }

  /* We have run control file of type *.exp          */
  /* Read next set of data from run control file.    */
  if (fscanf(input_fp,"%s %1s %ld %ld %d", output_file_name, &y_n, &rndsd, &stop_event_count, &trace_flag)<4
     || fscanf(input_fp,"%lf", &INPUT[8])<1
     || fscanf(input_fp,"%lf", &INPUT[9])<1
     || fscanf(input_fp,"%lf", &INPUT[12])<1
     || fscanf(input_fp,"%lf", &INPUT[0])<1
     || fscanf(input_fp,"%lf", &INPUT[1])<1
     || fscanf(input_fp,"%lf", &INPUT[2])<1
     || fscanf(input_fp,"%lf", &INPUT[3])<1
     || fscanf(input_fp,"%lf", &INPUT[10])<1
     || fscanf(input_fp,"%lf", &INPUT[11])<1
     || fscanf(input_fp,"%lf", &INPUT[27])<1
     || fscanf(input_fp,"%lf", &INPUT[28])<1
     || fscanf(input_fp,"%lf", &THRESH[1][1])<1
     || fscanf(input_fp,"%lf", &THRESH[1][2])<1
     || fscanf(input_fp,"%lf", &THRESH[1][3])<1
     || fscanf(input_fp,"%lf", &THRESH[2][1])<1
     || fscanf(input_fp,"%lf", &THRESH[2][2])<1
     || fscanf(input_fp,"%lf", &THRESH[2][3])<1
     || fscanf(input_fp,"%lf", &THRESH[3][1])<1
     || fscanf(input_fp,"%lf", &THRESH[3][2])<1
     || fscanf(input_fp,"%lf", &THRESH[3][3])<1
     || fscanf(input_fp,"%lf", &THRESH[4][1])<1
     || fscanf(input_fp,"%lf", &THRESH[4][2])<1
     || fscanf(input_fp,"%lf", &THRESH[4][3])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[1][1])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[1][2])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[1][3])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[2][0])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[2][1])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[2][2])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[2][3])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[3][0])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[3][1])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[3][2])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[3][3])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[4][0])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[4][1])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[4][2])<1
     || fscanf(input_fp,"%lf", &CUSTPREF[4][3])<1
     || fscanf(input_fp,"%lf", &RESTOCKT[1][0])<1
     || fscanf(input_fp,"%lf", &RESTOCKT[1][1])<1
     || fscanf(input_fp,"%lf", &ALPHA[1])<1
     || fscanf(input_fp,"%lf", &BETA[1])<1
     || fscanf(input_fp,"%lf", &RESTOCKT[2][0])<1
     || fscanf(input_fp,"%lf", &RESTOCKT[2][1])<1
     || fscanf(input_fp,"%lf", &ALPHA[2])<1
     || fscanf(input_fp,"%lf", &BETA[2])<1
     || fscanf(input_fp,"%lf", &RESTOCKT[3][0])<1
     || fscanf(input_fp,"%lf", &RESTOCKT[3][1])<1
     || fscanf(input_fp,"%lf", &ALPHA[3])<1
     || fscanf(input_fp,"%lf", &BETA[3])<1
     || fscanf(input_fp,"%lf", &RESTOCKT[4][0])<1
     || fscanf(input_fp,"%lf", &RESTOCKT[4][1])<1
     || fscanf(input_fp,"%lf", &ALPHA[4])<1
     || fscanf(input_fp,"%lf", &BETA[4])<1
     || fscanf(input_fp,"%lf", &SERVICET[0][0])<1
     || fscanf(input_fp,"%lf", &SERVICET[0][1])<1
     || fscanf(input_fp,"%lf", &ALPHA[5])<1
     || fscanf(input_fp,"%lf", &BETA[5])<1
     || fscanf(input_fp,"%lf", &SERVICET[1][0])<1
     || fscanf(input_fp,"%lf", &SERVICET[1][1])<1
     || fscanf(input_fp,"%lf", &ALPHA[6])<1
     || fscanf(input_fp,"%lf", &BETA[6])<1
     || fscanf(input_fp,"%lf", &SERVICET[2][0])<1
     || fscanf(input_fp,"%lf", &SERVICET[2][1])<1
     || fscanf(input_fp,"%lf", &ALPHA[7])<1
     || fscanf(input_fp,"%lf", &BETA[7])<1
     || fscanf(input_fp,"%lf", &SERVICET[3][0])<1
     || fscanf(input_fp,"%lf", &SERVICET[3][1])<1
     || fscanf(input_fp,"%lf", &ALPHA[8])<1
     || fscanf(input_fp,"%lf", &BETA[8])<1
     || fscanf(input_fp,"%lf", &SERVICET[4][0])<1
     || fscanf(input_fp,"%lf", &SERVICET[4][1])<1
     || fscanf(input_fp,"%lf", &ALPHA[9])<1
     || fscanf(input_fp,"%lf", &BETA[9])<1
     || fscanf(input_fp,"%lf", &INPUT[25])<1
     || fscanf(input_fp,"%lf", &INPUT[26])<1
     || fscanf(input_fp,"%lf", &ALPHA[10])<1
     || fscanf(input_fp,"%lf", &BETA[10])<1
     || fscanf(input_fp,"%lf", &INPUT[13])<1
     || fscanf(input_fp,"%lf", &INPUT[14])<1
     || fscanf(input_fp,"%lf", &INPUT[15])<1
     || fscanf(input_fp,"%lf", &INPUT[16])<1
     || fscanf(input_fp,"%lf", &INPUT[17])<1
     || fscanf(input_fp,"%lf", &INPUT[18])<1
     || fscanf(input_fp,"%lf", &INPUT[19])<1
     || fscanf(input_fp,"%lf", &INPUT[20])<1
     || fscanf(input_fp,"%lf", &INPUT[21])<1
     || fscanf(input_fp,"%lf", &INPUT[22])<1
     || fscanf(input_fp,"%lf", &INPUT[23])<1
     || fscanf(input_fp,"%lf", &INPUT[24])<1
     ) {
     /* End of run control file */
     fclose(input_fp);
     return 0;
     }

  if (y_n != 'y' && y_n != 'Y' && y_n != 'n' && y_n != 'N') { 
  fprintf(stderr,"INPUT ERROR: Invalid append file flag in *.exp file: (y=append, n=overwrite old file)\n"); 
  return 0; 
  }

  if (y_n == 'y' || y_n == 'Y') {
     if ((output_fp = fopen(output_file_name,"a"))==NULL) { 
     /* Output file can't be opened. */
     fprintf(stderr,"\nINPUT ERROR: Cannot open output file %s in *.exp file\n",argv[1]);
  return 0; 
  }
  }
if (y_n == 'n' || y_n == 'N') {
     if ((output_fp = fopen(output_file_name,"w"))==NULL) { 
     /* Output file can't be opened. */
     fprintf(stderr,"\nINPUT ERROR: Cannot open output file %s in *.exp file\n",argv[1]);
     return 0;
     }
     }

  if (rndsd < 1 || rndsd > 65534) {
     fprintf(stderr,"\nINPUT ERROR: Random seed %ld is not between 0 and 65534\n",rndsd);
     return 0;
     }

  if (stop_event_count <= 0) { 
     fprintf(stderr,"\nINPUT ERROR: Stopping Event Count %lf is negative!\n",stop_event_count);
     return 0;
     }

  if (trace_flag != 0 && trace_flag != 1) {
     fprintf(stderr,"\nINPUT ERROR: Invalid trace_flag=%d: (1=full trace, 0=summary only)\n",trace_flag);
     return 0;
     }

  done = 0;
     }

 else if (first_time) { /* And open failed, implies data from stdin */
    first_time = 0; /* Reset for next time into initialize */
    printf("Not found, input data at the keyboard.\n");
     /* Give output file name */
     while(y_n != 'y' && y_n != 'Y' && y_n != 'n' && y_n != 'N')
         {
         printf("\nOUTPUT FILE (Enter File Name with Path):\n");
         scanf("%s", output_file_name);
         fflush(stdin);
         sprintf(filename,"%.20s", output_file_name);
         printf("WARNING:File %.20s must not be open!!\n If file does not exist it will be created.\n",filename);
         printf("Do you want the new output appended to this file? (yes/[no])\n");
         scanf("%1s",&y_n);
         fflush(stdin);
         }
     if(y_n == 'y' || y_n == 'Y') output_fp = fopen(filename,"a");
     if(y_n == 'n' || y_n == 'N') output_fp = fopen(filename,"w");

     /* Read in random number seed */
     printf("\n\nRANDOM NUMBER SEED (Enter Integer Between 0 and 65534):\n");
     scanf("%ld", &rndsd);
     fflush(stdin);

     /* Read in run number of stopping events */
     printf("\nEnter Number of CALC Events to Run:\n");
     scanf("%ld", &stop_event_count);
     fflush(stdin);

     /* Read in trace_flag */
     printf("\n\nTRACE (1 = Event Trace, 0 = Summary Only):\n");
     scanf("%d", &trace_flag);
     fflush(stdin);

     /* Parameters for the initial event */;
     printf ( "\nEnter initial value for INPUT[8]: \n");
     scanf  ( "%lf", &INPUT[8]);
     printf ( "\nEnter initial value for INPUT[9]: \n");
     scanf  ( "%lf", &INPUT[9]);
     printf ( "\nEnter initial value for INPUT[12]: \n");
     scanf  ( "%lf", &INPUT[12]);
     printf ( "\nEnter initial value for INPUT[0]: \n");
     scanf  ( "%lf", &INPUT[0]);
     printf ( "\nEnter initial value for INPUT[1]: \n");
     scanf  ( "%lf", &INPUT[1]);
     printf ( "\nEnter initial value for INPUT[2]: \n");
     scanf  ( "%lf", &INPUT[2]);
     printf ( "\nEnter initial value for INPUT[3]: \n");
     scanf  ( "%lf", &INPUT[3]);
     printf ( "\nEnter initial value for INPUT[10]: \n");
     scanf  ( "%lf", &INPUT[10]);
     printf ( "\nEnter initial value for INPUT[11]: \n");
     scanf  ( "%lf", &INPUT[11]);
     printf ( "\nEnter initial value for INPUT[27]: \n");
     scanf  ( "%lf", &INPUT[27]);
     printf ( "\nEnter initial value for INPUT[28]: \n");
     scanf  ( "%lf", &INPUT[28]);
     printf ( "\nEnter initial value for THRESH[1][1]: \n");
     scanf  ( "%lf", &THRESH[1][1]);
     printf ( "\nEnter initial value for THRESH[1][2]: \n");
     scanf  ( "%lf", &THRESH[1][2]);
     printf ( "\nEnter initial value for THRESH[1][3]: \n");
     scanf  ( "%lf", &THRESH[1][3]);
     printf ( "\nEnter initial value for THRESH[2][1]: \n");
     scanf  ( "%lf", &THRESH[2][1]);
     printf ( "\nEnter initial value for THRESH[2][2]: \n");
     scanf  ( "%lf", &THRESH[2][2]);
     printf ( "\nEnter initial value for THRESH[2][3]: \n");
     scanf  ( "%lf", &THRESH[2][3]);
     printf ( "\nEnter initial value for THRESH[3][1]: \n");
     scanf  ( "%lf", &THRESH[3][1]);
     printf ( "\nEnter initial value for THRESH[3][2]: \n");
     scanf  ( "%lf", &THRESH[3][2]);
     printf ( "\nEnter initial value for THRESH[3][3]: \n");
     scanf  ( "%lf", &THRESH[3][3]);
     printf ( "\nEnter initial value for THRESH[4][1]: \n");
     scanf  ( "%lf", &THRESH[4][1]);
     printf ( "\nEnter initial value for THRESH[4][2]: \n");
     scanf  ( "%lf", &THRESH[4][2]);
     printf ( "\nEnter initial value for THRESH[4][3]: \n");
     scanf  ( "%lf", &THRESH[4][3]);
     printf ( "\nEnter initial value for CUSTPREF[1][1]: \n");
     scanf  ( "%lf", &CUSTPREF[1][1]);
     printf ( "\nEnter initial value for CUSTPREF[1][2]: \n");
     scanf  ( "%lf", &CUSTPREF[1][2]);
     printf ( "\nEnter initial value for CUSTPREF[1][3]: \n");
     scanf  ( "%lf", &CUSTPREF[1][3]);
     printf ( "\nEnter initial value for CUSTPREF[2][0]: \n");
     scanf  ( "%lf", &CUSTPREF[2][0]);
     printf ( "\nEnter initial value for CUSTPREF[2][1]: \n");
     scanf  ( "%lf", &CUSTPREF[2][1]);
     printf ( "\nEnter initial value for CUSTPREF[2][2]: \n");
     scanf  ( "%lf", &CUSTPREF[2][2]);
     printf ( "\nEnter initial value for CUSTPREF[2][3]: \n");
     scanf  ( "%lf", &CUSTPREF[2][3]);
     printf ( "\nEnter initial value for CUSTPREF[3][0]: \n");
     scanf  ( "%lf", &CUSTPREF[3][0]);
     printf ( "\nEnter initial value for CUSTPREF[3][1]: \n");
     scanf  ( "%lf", &CUSTPREF[3][1]);
     printf ( "\nEnter initial value for CUSTPREF[3][2]: \n");
     scanf  ( "%lf", &CUSTPREF[3][2]);
     printf ( "\nEnter initial value for CUSTPREF[3][3]: \n");
     scanf  ( "%lf", &CUSTPREF[3][3]);
     printf ( "\nEnter initial value for CUSTPREF[4][0]: \n");
     scanf  ( "%lf", &CUSTPREF[4][0]);
     printf ( "\nEnter initial value for CUSTPREF[4][1]: \n");
     scanf  ( "%lf", &CUSTPREF[4][1]);
     printf ( "\nEnter initial value for CUSTPREF[4][2]: \n");
     scanf  ( "%lf", &CUSTPREF[4][2]);
     printf ( "\nEnter initial value for CUSTPREF[4][3]: \n");
     scanf  ( "%lf", &CUSTPREF[4][3]);
     printf ( "\nEnter initial value for RESTOCKT[1][0]: \n");
     scanf  ( "%lf", &RESTOCKT[1][0]);
     printf ( "\nEnter initial value for RESTOCKT[1][1]: \n");
     scanf  ( "%lf", &RESTOCKT[1][1]);
     printf ( "\nEnter initial value for ALPHA[1]: \n");
     scanf  ( "%lf", &ALPHA[1]);
     printf ( "\nEnter initial value for BETA[1]: \n");
     scanf  ( "%lf", &BETA[1]);
     printf ( "\nEnter initial value for RESTOCKT[2][0]: \n");
     scanf  ( "%lf", &RESTOCKT[2][0]);
     printf ( "\nEnter initial value for RESTOCKT[2][1]: \n");
     scanf  ( "%lf", &RESTOCKT[2][1]);
     printf ( "\nEnter initial value for ALPHA[2]: \n");
     scanf  ( "%lf", &ALPHA[2]);
     printf ( "\nEnter initial value for BETA[2]: \n");
     scanf  ( "%lf", &BETA[2]);
     printf ( "\nEnter initial value for RESTOCKT[3][0]: \n");
     scanf  ( "%lf", &RESTOCKT[3][0]);
     printf ( "\nEnter initial value for RESTOCKT[3][1]: \n");
     scanf  ( "%lf", &RESTOCKT[3][1]);
     printf ( "\nEnter initial value for ALPHA[3]: \n");
     scanf  ( "%lf", &ALPHA[3]);
     printf ( "\nEnter initial value for BETA[3]: \n");
     scanf  ( "%lf", &BETA[3]);
     printf ( "\nEnter initial value for RESTOCKT[4][0]: \n");
     scanf  ( "%lf", &RESTOCKT[4][0]);
     printf ( "\nEnter initial value for RESTOCKT[4][1]: \n");
     scanf  ( "%lf", &RESTOCKT[4][1]);
     printf ( "\nEnter initial value for ALPHA[4]: \n");
     scanf  ( "%lf", &ALPHA[4]);
     printf ( "\nEnter initial value for BETA[4]: \n");
     scanf  ( "%lf", &BETA[4]);
     printf ( "\nEnter initial value for SERVICET[0][0]: \n");
     scanf  ( "%lf", &SERVICET[0][0]);
     printf ( "\nEnter initial value for SERVICET[0][1]: \n");
     scanf  ( "%lf", &SERVICET[0][1]);
     printf ( "\nEnter initial value for ALPHA[5]: \n");
     scanf  ( "%lf", &ALPHA[5]);
     printf ( "\nEnter initial value for BETA[5]: \n");
     scanf  ( "%lf", &BETA[5]);
     printf ( "\nEnter initial value for SERVICET[1][0]: \n");
     scanf  ( "%lf", &SERVICET[1][0]);
     printf ( "\nEnter initial value for SERVICET[1][1]: \n");
     scanf  ( "%lf", &SERVICET[1][1]);
     printf ( "\nEnter initial value for ALPHA[6]: \n");
     scanf  ( "%lf", &ALPHA[6]);
     printf ( "\nEnter initial value for BETA[6]: \n");
     scanf  ( "%lf", &BETA[6]);
     printf ( "\nEnter initial value for SERVICET[2][0]: \n");
     scanf  ( "%lf", &SERVICET[2][0]);
     printf ( "\nEnter initial value for SERVICET[2][1]: \n");
     scanf  ( "%lf", &SERVICET[2][1]);
     printf ( "\nEnter initial value for ALPHA[7]: \n");
     scanf  ( "%lf", &ALPHA[7]);
     printf ( "\nEnter initial value for BETA[7]: \n");
     scanf  ( "%lf", &BETA[7]);
     printf ( "\nEnter initial value for SERVICET[3][0]: \n");
     scanf  ( "%lf", &SERVICET[3][0]);
     printf ( "\nEnter initial value for SERVICET[3][1]: \n");
     scanf  ( "%lf", &SERVICET[3][1]);
     printf ( "\nEnter initial value for ALPHA[8]: \n");
     scanf  ( "%lf", &ALPHA[8]);
     printf ( "\nEnter initial value for BETA[8]: \n");
     scanf  ( "%lf", &BETA[8]);
     printf ( "\nEnter initial value for SERVICET[4][0]: \n");
     scanf  ( "%lf", &SERVICET[4][0]);
     printf ( "\nEnter initial value for SERVICET[4][1]: \n");
     scanf  ( "%lf", &SERVICET[4][1]);
     printf ( "\nEnter initial value for ALPHA[9]: \n");
     scanf  ( "%lf", &ALPHA[9]);
     printf ( "\nEnter initial value for BETA[9]: \n");
     scanf  ( "%lf", &BETA[9]);
     printf ( "\nEnter initial value for INPUT[25]: \n");
     scanf  ( "%lf", &INPUT[25]);
     printf ( "\nEnter initial value for INPUT[26]: \n");
     scanf  ( "%lf", &INPUT[26]);
     printf ( "\nEnter initial value for ALPHA[10]: \n");
     scanf  ( "%lf", &ALPHA[10]);
     printf ( "\nEnter initial value for BETA[10]: \n");
     scanf  ( "%lf", &BETA[10]);
     printf ( "\nEnter initial value for INPUT[13]: \n");
     scanf  ( "%lf", &INPUT[13]);
     printf ( "\nEnter initial value for INPUT[14]: \n");
     scanf  ( "%lf", &INPUT[14]);
     printf ( "\nEnter initial value for INPUT[15]: \n");
     scanf  ( "%lf", &INPUT[15]);
     printf ( "\nEnter initial value for INPUT[16]: \n");
     scanf  ( "%lf", &INPUT[16]);
     printf ( "\nEnter initial value for INPUT[17]: \n");
     scanf  ( "%lf", &INPUT[17]);
     printf ( "\nEnter initial value for INPUT[18]: \n");
     scanf  ( "%lf", &INPUT[18]);
     printf ( "\nEnter initial value for INPUT[19]: \n");
     scanf  ( "%lf", &INPUT[19]);
     printf ( "\nEnter initial value for INPUT[20]: \n");
     scanf  ( "%lf", &INPUT[20]);
     printf ( "\nEnter initial value for INPUT[21]: \n");
     scanf  ( "%lf", &INPUT[21]);
     printf ( "\nEnter initial value for INPUT[22]: \n");
     scanf  ( "%lf", &INPUT[22]);
     printf ( "\nEnter initial value for INPUT[23]: \n");
     scanf  ( "%lf", &INPUT[23]);
     printf ( "\nEnter initial value for INPUT[24]: \n");
     scanf  ( "%lf", &INPUT[24]);
   }

 else {
    /* this is not the first time and there is no .exp file */
    return 0;
    }
  
   /* PLACE CUSTOMIZED INITIALIZATIONS HERE */

if (trace_flag)
   {
   fprintf(output_fp,"    Time\t  Event\t Count");
   fprintf(output_fp,"	            PROFIT ");
   fprintf(output_fp,"\n");
   }
  /* Initialize CSIGLIB variables and files */
  c_initlk(rndsd);
  c_initfiles();

  return(1);
}



void
run_end()
{
  printf("\r\nNormal completion after %f time units\n",current_time);
  printf("The Next Seed In the Random Input Stream is %ld\n",rndsd);

  ///  Summary statistics ///
  fprintf(output_fp,"SUMMARY STATISTICS\n");
  printf("SUMMARY STATISTICS\n");
  c_timest(PROFIT, 1, 1);
   fprintf(output_fp, "PROFIT:\n Time Ave. = \t%7.4g Time Sample Var. =\t%7.4g\n", transfer[4], transfer[7]);
   printf("PROFIT:\n Time Ave. = 	%7.4g Time Sample Var. = 	%7.4g\n", transfer[4], transfer[7]);
  c_sampst(PROFIT, 1, 1);
   fprintf(output_fp, " Event Ave. =\t%7.4g Event Sample Var. =\t%7.4g\n", transfer[4], transfer[8]);
   fprintf(output_fp, " Minimum =\t%7.4g\n", transfer[7]);
   fprintf(output_fp, " Maximum =\t%7.4g\n", transfer[6]);
   printf(" Event Ave.  = 	%7.4g Event Sample Var.= 	%7.4g\n", transfer[4], transfer[8]);
   printf(" Minimum  = 	%7.4g\n", transfer[7]);
   printf(" Maximum  = 	%7.4g\n", transfer[6]);
  printf("Output written to, %s\n",output_file_name);
  fclose(output_fp);
  c_closedisk();
  done = 1;
}



/****************************/
/*     EVENT FUNCTIONS      */
/****************************/

/*** rnk[1]=1 denotes that the orderq is sorted by ent[1], the time the ID customer arrived (in increasing order), rnk[2]=6 denotes that Q is sorted by ent[6], the ID of customer (in increasing order, so that customers that arrived first get their cupcakes worked on first) ***/
void
RUN()
{
int  _edge_condition[1];

  /* Attribute Value(s) Passed to this Event */

  /* state changes */
  RNK[2]=7;
  RNK[8]=7;
  RNK[9]=7;
  RNK[10]=7;
  RNK[11]=7;
  RNK[24]=7;
  RNK[26]=7;
  RNK[28]=7;
  RNK[30]=7;
  RNK[50]=7;
  RNK[53]=7;
  RNK[56]=7;
  RNK[59]=7;
  RES[0]=INPUT[0];
  RES[1]=INPUT[1];
  RES[2]=INPUT[2];
  RES[3]=INPUT[3];
  MISC[0]=(RES[0]>RES[2]);
  MISC[1]=((RES[2]/2)>RES[3]);
  MISC[2]=(INPUT[10]/60)*((MISC[0]*MISC[1]*2*RES[3])+(MISC[0]*(1-MISC[1])*RES[2])+((1-MISC[0])*MISC[1]*2*RES[3])+((1-MISC[0])*(1-MISC[1])*RES[0]));
  RESTOCK[1][1]=0;
  RESTOCK[1][2]=0;
  RESTOCK[2][1]=0;
  RESTOCK[2][2]=0;
  RESTOCK[3][1]=0;
  RESTOCK[3][2]=0;
  RESTOCK[4][1]=0;
  RESTOCK[4][2]=0;

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( 1==1 );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = 0;
    transfer[4] = 0;
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = WARMUP_event;
    event_priority = 10;
    schedule_event();
    }

}


/***  ***/
void
CHECK_S()
{
int  _edge_condition[4];

  /* Attribute Value(s) Passed to this Event */
  I[0] = (long) transfer[3];
  I[1] = (long) transfer[4];
  I[2] = (long) transfer[5];
  I[3] = (long) transfer[6];
  I[4] = (long) transfer[7];
  I[5] = (long) transfer[8];
  I[6] = (long) transfer[9];
  ID = (long) transfer[10];
  INDEX = (long) transfer[11];

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( (INDEX==4)&&(I[INDEX]==0) );
  _edge_condition[1] = ( (I[INDEX]>0) );
  _edge_condition[2] = ( I[INDEX]==0&&INDEX<4 );
  _edge_condition[3] = ( (INDEX==4)&&(I[INDEX]==0)&&(RES[0]>0)&&(Q[2]>0) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[5];
    transfer[4] = I[6];
    transfer[5] = ID;
    for ( t_index=6; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = LEAVE_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = SUP_event;
    event_priority = 6;
    schedule_event();
    }

  if (_edge_condition[2])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX+1;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = CHECK_S_event;
    event_priority = 6;
    schedule_event();
    }

  if (_edge_condition[3])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = 0;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = NEXTQ_event;
    event_priority = 5;
    schedule_event();
    }

}


/***  ***/
void
LEAVE()
{
int  _edge_condition[2];

  /* Attribute Value(s) Passed to this Event */
  I[5] = (long) transfer[3];
  I[6] = (long) transfer[4];
  ID = (long) transfer[5];

  /* state changes */
  TOTAL[4][ID]=CLK-I[6];
  TOTAL[5][ID]=TOTAL[3][ID]+TOTAL[4][ID];
  TOTAL[6][1]=TOTAL[6][1]+I[5];

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( (RES[0]==INPUT[0])&&(RES[1]==INPUT[1])&&(RES[2]==INPUT[2])&&(RES[3]==INPUT[3])&&(Q[2]==0)&&(CLK>MISC[7])&&(MISC[8]<INPUT[12])&&(RESTOCK[4][1]==0)&&(RESTOCK[4][2]==0)&&(RESTOCK[1][1]==0)&&(RESTOCK[1][2]==0)&&(RESTOCK[2][1]==0)&&(RESTOCK[2][2]==0)&&(RESTOCK[3][1]==0)&&(RESTOCK[3][2]==0) );
  _edge_condition[1] = ( (RES[0]==INPUT[0])&&(RES[1]==INPUT[1])&&(RES[2]==INPUT[2])&&(RES[3]==INPUT[3])&&(Q[2]==0)&&(CLK>MISC[7])&&(MISC[8]==INPUT[12])&&(RESTOCK[4][1]==0)&&(RESTOCK[4][2]==0)&&(RESTOCK[1][1]==0)&&(RESTOCK[1][2]==0)&&(RESTOCK[2][1]==0)&&(RESTOCK[2][2]==0)&&(RESTOCK[3][1]==0)&&(RESTOCK[3][2]==0) );

  /* schedule future events */
  if (_edge_condition[0])
    /***  How will we know when the last customer leaves the system for the day?  1) when the number of available servers = number of total servers, 2) when the number in Q and ORDERQ equals 0,  3) when CLK > OPEN  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = CLK;
    transfer[4] = 0;
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = WARMUP_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    for ( t_index=3; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = CALC_event;
    event_priority = 10;
    schedule_event();
    }

}


/***  ***/
void
FINISH()
{
int  _edge_condition[5];

  /* Attribute Value(s) Passed to this Event */
  I[0] = (long) transfer[3];
  I[1] = (long) transfer[4];
  I[2] = (long) transfer[5];
  I[3] = (long) transfer[6];
  I[4] = (long) transfer[7];
  I[5] = (long) transfer[8];
  I[6] = (long) transfer[9];
  ID = (long) transfer[10];
  INDEX = (long) transfer[11];

  /* state changes */
  RES[0]=RES[0]+1;
  RES[1]=RES[1]+1*(INDEX==0);
  TYPE[1]=I[INDEX];
  I[INDEX]=0;
  TOTAL[3][ID]=(CLK-I[6])*(INDEX==0)+(TOTAL[3][ID]*(INDEX>0));
  I[6]=CLK*(INDEX==0)+(I[6]*(INDEX>0));

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( INDEX<4 );
  _edge_condition[1] = ( INDEX==4 );
  _edge_condition[2] = ( (INDEX==4)&&(RES[0]>0)&&(Q[2]>0) );
  _edge_condition[3] = ( (SUPPLY[INDEX][TYPE[1]]<THRESH[INDEX][TYPE[1]])&&(RES[0]>0)&&(RESTOCK[INDEX][TYPE[1]]==0)&&(INDEX==1)&&(RES[3]>0)&&(RES[2]>0)&&(CLK<MISC[7]) );
  _edge_condition[4] = ( (SUPPLY[INDEX][TYPE[1]]<THRESH[INDEX][TYPE[1]])&&(RES[0]>0)&&(RESTOCK[INDEX][TYPE[1]]==0)&&(INDEX>1)&&(RES[2]>0)&&(CLK<MISC[7]) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX+1;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = CHECK_S_event;
    event_priority = 6;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[5];
    transfer[4] = I[6];
    transfer[5] = ID;
    for ( t_index=6; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = LEAVE_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[2])
    /***  If there are still orders to be fulfilled/cupcakes to be made, the available server will start service on the customer with the lowest ID's cupcake order  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = 0;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = NEXTQ_event;
    event_priority = 5;
    schedule_event();
    }

  if (_edge_condition[3])
    /***  For cupcake restock  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = INDEX;
    transfer[4] = TYPE[1];
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = RESTK_event;
    event_priority = 1;
    schedule_event();
    }

  if (_edge_condition[4])
    /***  For other supply restock  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = INDEX;
    transfer[4] = TYPE[1];
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = RESTK_event;
    event_priority = 1;
    schedule_event();
    }

}


/***  ***/
void
SUP()
{
int  _edge_condition[7];

  /* Attribute Value(s) Passed to this Event */
  I[0] = (long) transfer[3];
  I[1] = (long) transfer[4];
  I[2] = (long) transfer[5];
  I[3] = (long) transfer[6];
  I[4] = (long) transfer[7];
  I[5] = (long) transfer[8];
  I[6] = (long) transfer[9];
  ID = (long) transfer[10];
  INDEX = (long) transfer[11];

  /* state changes */
  MISC[3]=0;

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( ((SUPPLY[INDEX][I[INDEX]]-1*I[5])>=0)&&(RES[0]>0)&&(INDEX>0) );
  _edge_condition[1] = ( (RES[0]>0)&&(RES[1]>0)&&(INDEX==0) );
  _edge_condition[2] = ( (INDEX>0)&&(RES[0]<=0)&&((SUPPLY[INDEX][I[INDEX]]-1*I[5])>=0) );
  _edge_condition[3] = ( ((INDEX==0)&&(RES[0]<=0))||((INDEX==0)&&(RES[1]<=0)) );
  _edge_condition[4] = ( (INDEX>0)&&((SUPPLY[INDEX][I[INDEX]]-1*I[5])<0) );
  _edge_condition[5] = ( ((SUPPLY[INDEX][I[INDEX]]-1*I[5])<0)&&(INDEX==1)&&(RESTOCK[INDEX][I[INDEX]]==0)&&RES[0]>0&&RES[3]>0&&RES[2]>0 );
  _edge_condition[6] = ( ((SUPPLY[INDEX][I[INDEX]]-1*I[5])<0)&&(INDEX>1)&&(RESTOCK[INDEX][I[INDEX]]==0)&&RES[0]>0&&RES[2]>0 );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = START_S_event;
    event_priority = 4;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = START_S_event;
    event_priority = 4;
    schedule_event();
    }

  if (_edge_condition[2])
    /***  If customer has already ordered and there are no available workers (but there are enough supplies)  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX;
    transfer[12] = 0;
    for ( t_index=13; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = JOINQ_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[3])
    /***  If customer has not ordered yet and there are no available workers or cash registers  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX;
    transfer[12] = 0;
    for ( t_index=13; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = JOINQ_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[4])
    /***  If the customer has already ordered and there are not enough supplies to satisfy order  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX;
    transfer[12] = I[INDEX];
    for ( t_index=13; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = JOINQ_event;
    event_priority = 5;
    schedule_event();
    }

  if (_edge_condition[5])
    /***  For cupcake restock  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = INDEX;
    transfer[4] = I[INDEX];
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = RESTK_event;
    event_priority = 4;
    schedule_event();
    }

  if (_edge_condition[6])
    /***  For other supply restock  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = INDEX;
    transfer[4] = I[INDEX];
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = RESTK_event;
    event_priority = 5;
    schedule_event();
    }

}


/*** Customer arrives but doesn't get a chance to place an order. (We need to add a non order queue variable) ***/
void
ARRIVE()
{
int  _edge_condition[6];


  /* state changes */
  TOTAL[6][0]=TOTAL[6][0]+1;
  I[0]=1;
  MISC[11]=RND;
  MISC[12]=RND;
  MISC[13]=RND;
  MISC[14]=RND;
  MISC[15]=RND;
  I[5]=INPUT[27]+(INPUT[28]-INPUT[27])*MISC[15];
  I[6]=CLK;
  I[1]=(MISC[11]<CUSTPREF[1][1])+2*((MISC[11]>CUSTPREF[1][1])&&(MISC[11]<(CUSTPREF[1][1]+CUSTPREF[1][2])))+3*((MISC[11]>(CUSTPREF[1][1]+CUSTPREF[1][2]))&&(MISC[11]<(CUSTPREF[1][1]+CUSTPREF[1][2]+CUSTPREF[1][3])));
  I[2]=(MISC[12]<CUSTPREF[2][1])+2*((MISC[12]>CUSTPREF[2][1])&&(MISC[12]<(CUSTPREF[2][1]+CUSTPREF[2][2])))+3*((MISC[12]>(CUSTPREF[2][1]+CUSTPREF[2][2]))&&(MISC[12]<(CUSTPREF[2][1]+CUSTPREF[2][2]+CUSTPREF[2][3])));
  I[3]=(MISC[13]<CUSTPREF[3][1])+2*((MISC[13]>CUSTPREF[3][1])&&(MISC[13]<(CUSTPREF[3][1]+CUSTPREF[3][2])))+3*((MISC[13]>(CUSTPREF[3][1]+CUSTPREF[3][2]))&&(MISC[13]<(CUSTPREF[3][1]+CUSTPREF[3][2]+CUSTPREF[3][3])));
  I[4]=(MISC[14]<CUSTPREF[4][1])+2*((MISC[14]>CUSTPREF[4][1])&&(MISC[14]<(CUSTPREF[4][1]+CUSTPREF[4][2])))+3*((MISC[14]>(CUSTPREF[4][1]+CUSTPREF[4][2]))&&(MISC[14]<(CUSTPREF[4][1]+CUSTPREF[4][2]+CUSTPREF[4][3])));

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( CLK<MISC[7] );
  _edge_condition[1] = ( (RES[0]==INPUT[0])&&(RES[1]==INPUT[1])&&(RES[2]==INPUT[2])&&(RES[3]==INPUT[3])&&(Q[2]==0)&&(CLK>MISC[7])&&(MISC[8]<INPUT[12])&&(RESTOCK[4][1]==0)&&(RESTOCK[4][2]==0)&&(RESTOCK[1][1]==0)&&(RESTOCK[1][2]==0)&&(RESTOCK[2][1]==0)&&(RESTOCK[2][2]==0)&&(RESTOCK[3][1]==0)&&(RESTOCK[3][2]==0) );
  _edge_condition[2] = ( (CLK<MISC[7])&&((RES[0]<=0)||(RES[1]<=0)) );
  _edge_condition[3] = ( (RES[0]>0)&&(RES[1]>0)&&(CLK<MISC[7]) );
  _edge_condition[4] = ( (RES[0]==INPUT[0])&&(RES[1]==INPUT[1])&&(RES[2]==INPUT[2])&&(RES[3]==INPUT[3])&&(Q[2]==0)&&(CLK>MISC[7])&&(MISC[8]==INPUT[12])&&(RESTOCK[4][1]==0)&&(RESTOCK[4][2]==0)&&(RESTOCK[1][1]==0)&&(RESTOCK[1][2]==0)&&(RESTOCK[2][1]==0)&&(RESTOCK[2][2]==0)&&(RESTOCK[3][1]==0)&&(RESTOCK[3][2]==0) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    for ( t_index=3; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + INPUT[8]*ERL(1);
    event_type = ARRIVE_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = CLK;
    transfer[4] = 1;
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = WARMUP_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[2])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = TOTAL[6][0];
    transfer[11] = 0;
    transfer[12] = 0;
    for ( t_index=13; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = JOINQ_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[3])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = TOTAL[6][0];
    transfer[11] = 0;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = SUP_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[4])
    {
    for ( t_index=3; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = CALC_event;
    event_priority = 10;
    schedule_event();
    }

}


/***  ***/
void
JOINQ()
{
  /* Attribute Value(s) Passed to this Event */
  ENT[0] = (long) transfer[3];
  ENT[1] = (long) transfer[4];
  ENT[2] = (long) transfer[5];
  ENT[3] = (long) transfer[6];
  ENT[4] = (long) transfer[7];
  ENT[5] = (long) transfer[8];
  ENT[6] = (long) transfer[9];
  ENT[7] = (long) transfer[10];
  ENT[8] = (long) transfer[11];
  TYPE[1] = (long) transfer[12];

  /* state changes */
  TYPE[0]=(INDEX+5*TYPE[1])*TYPE[1]+2;
  Q[TYPE[0]]=Q[TYPE[0]]+(PUT(INC,TYPE[0]));
}


/*** "2" is the location of the customers who have already ordered and their cupcakes are going through the process of being completed ***/
void
NEXTQ()
{
int  _edge_condition[2];

  /* Attribute Value(s) Passed to this Event */
  MISC[3] = transfer[3];

  /* state changes */
  Q[2]=Q[2]-GET(FST,2);
  I[0]=ENT[0];
  I[1]=ENT[1];
  I[2]=ENT[2];
  I[3]=ENT[3];
  I[4]=ENT[4];
  I[5]=ENT[5];
  I[6]=ENT[6];
  ID=ENT[7];
  INDEX=ENT[8];

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( 1==1 );
  _edge_condition[1] = ( (MISC[3]>1)&&(Q[2]>0)&&(MISC[3]<99) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = SUP_event;
    event_priority = 3;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = MISC[3]-1;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = NEXTQ_event;
    event_priority = 5;
    schedule_event();
    }

}


/*** RESTOCK[INDEX;TYPE] is a boolean array that is initally set to 0 for product INDEX of type TYPE (ex, product=cake, type=vanilla) and becomes one when that type of product is in the process of being restocked (this functions to eliminate multiple RESTOCKS being scheduled for a particular type of product) ***/
void
RESTK()
{
int  _edge_condition[3];

  /* Attribute Value(s) Passed to this Event */
  INDEX = (long) transfer[3];
  TYPE[1] = (long) transfer[4];

  /* state changes */
  RES[0]=RES[0]-1;
  RESTOCK[INDEX][TYPE[1]]=1;
  MISC[4]=INPUT[25]+(INPUT[26]-INPUT[25])*BET(ALPHA[10],BETA[10]);
  RES[3]=RES[3]-1*(INDEX==1);
  RES[2]=RES[2]-1;

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( (INDEX>1) );
  _edge_condition[1] = ( (INDEX==1) );
  _edge_condition[2] = ( (INDEX==1) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = INDEX;
    transfer[4] = TYPE[1];
    transfer[5] = 0;
    for ( t_index=6; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + RESTOCKT[INDEX][0]+(RESTOCKT[INDEX][1]-RESTOCKT[INDEX][0])*BET(ALPHA[INDEX],BETA[INDEX]);
    event_type = FINISHR_event;
    event_priority = 4;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = INDEX;
    transfer[4] = TYPE[1];
    transfer[5] = MISC[4];
    for ( t_index=6; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + RESTOCKT[INDEX][0]+(RESTOCKT[INDEX][1]-RESTOCKT[INDEX][0])*BET(ALPHA[INDEX],BETA[INDEX])+MISC[4];
    event_type = FINISHR_event;
    event_priority = 4;
    schedule_event();
    }

  if (_edge_condition[2])
    {
    for ( t_index=3; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + MISC[4];
    event_type = AVAIL_W_event;
    event_priority = 5;
    schedule_event();
    }

}


/*** 20 is the extra amount that was made when a restock event was executed ***/
void
FINISHR()
{
int  _edge_condition[4];

  /* Attribute Value(s) Passed to this Event */
  INDEX = (long) transfer[3];
  TYPE[1] = (long) transfer[4];
  MISC[4] = transfer[5];

  /* state changes */
  SUPPLY[INDEX][TYPE[1]]=SUPPLY[INDEX][TYPE[1]]+24+24*(INDEX==1);
  RESTOCK[INDEX][TYPE[1]]=0;
  TYPE[0]=((INDEX+5*TYPE[1])*TYPE[1]+2);
  RES[0]=RES[0]+1*(INDEX>1);
  RES[3]=RES[3]+1*(INDEX==1);
  RES[2]=RES[2]+1*(INDEX>1);

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( (RES[0]==INPUT[0])&&(RES[1]==INPUT[1])&&(RES[2]==INPUT[2])&&(RES[3]==INPUT[3])&&(Q[2]==0)&&(CLK>MISC[7])&&(Q[TYPE[0]]<=0)&&(MISC[8]<INPUT[12])&&(RESTOCK[4][1]==0)&&(RESTOCK[4][2]==0)&&(RESTOCK[1][1]==0)&&(RESTOCK[1][2]==0)&&(RESTOCK[2][1]==0)&&(RESTOCK[2][2]==0)&&(RESTOCK[3][1]==0)&&(RESTOCK[3][2]==0) );
  _edge_condition[1] = ( Q[TYPE[0]]>0 );
  _edge_condition[2] = ( Q[TYPE[0]]<0&&(Q[2]>0)&&(RES[0]>0)&&(INDEX>1) );
  _edge_condition[3] = ( (RES[0]==INPUT[0])&&(RES[1]==INPUT[1])&&(RES[2]==INPUT[2])&&(RES[3]==INPUT[3])&&(Q[2]==0)&&(CLK>MISC[7])&&(Q[TYPE[0]]<=0)&&(MISC[8]==INPUT[12])&&(RESTOCK[4][1]==0)&&(RESTOCK[4][2]==0)&&(RESTOCK[1][1]==0)&&(RESTOCK[1][2]==0)&&(RESTOCK[2][1]==0)&&(RESTOCK[2][2]==0)&&(RESTOCK[3][1]==0)&&(RESTOCK[3][2]==0) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = CLK;
    transfer[4] = 0;
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = WARMUP_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = TYPE[0];
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = GET_PUT_event;
    event_priority = 2;
    schedule_event();
    }

  if (_edge_condition[2])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = 0;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = NEXTQ_event;
    event_priority = 5;
    schedule_event();
    }

  if (_edge_condition[3])
    {
    for ( t_index=3; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = CALC_event;
    event_priority = 10;
    schedule_event();
    }

}


/***  ***/
void
START_S()
{
int  _edge_condition[2];

  /* Attribute Value(s) Passed to this Event */
  I[0] = (long) transfer[3];
  I[1] = (long) transfer[4];
  I[2] = (long) transfer[5];
  I[3] = (long) transfer[6];
  I[4] = (long) transfer[7];
  I[5] = (long) transfer[8];
  I[6] = (long) transfer[9];
  ID = (long) transfer[10];
  INDEX = (long) transfer[11];

  /* state changes */
  RES[0]=RES[0]-1;
  RES[1]=RES[1]-1*(INDEX==0);
  SUPPLY[INDEX][I[INDEX]]=SUPPLY[INDEX][I[INDEX]]-I[5]*(INDEX>0);
  TYPE[2]=(INDEX>0);
  TYPE[3]=((INDEX>0)*(3*(INDEX-1)+I[INDEX]));
  TOTAL[TYPE[2]][TYPE[3]]=TOTAL[TYPE[2]][TYPE[3]]+I[5];

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( (INDEX>0) );
  _edge_condition[1] = ( (INDEX==0) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + SERVICET[INDEX][0]+(SERVICET[INDEX][1]-SERVICET[INDEX][0])*BET(ALPHA[INDEX+5],BETA[INDEX+5])*I[5];
    event_type = FINISH_event;
    event_priority = 5;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = I[0];
    transfer[4] = I[1];
    transfer[5] = I[2];
    transfer[6] = I[3];
    transfer[7] = I[4];
    transfer[8] = I[5];
    transfer[9] = I[6];
    transfer[10] = ID;
    transfer[11] = INDEX;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + SERVICET[INDEX][0]+(SERVICET[INDEX][1]-SERVICET[INDEX][0])*BET(ALPHA[5],BETA[5]);
    event_type = FINISH_event;
    event_priority = 5;
    schedule_event();
    }

}


/***  ***/
void
WARMUP()
{
int  _edge_condition[2];

  /* Attribute Value(s) Passed to this Event */
  MISC[9] = transfer[3];
  MISC[16] = transfer[4];

  /* state changes */
  MISC[7]=INPUT[11]+(INPUT[10]+MISC[9]);
  MISC[8]=MISC[8]+1;
  SUPPLY[1][1]=SUPPLY[1][1]+8*MISC[2];
  SUPPLY[1][2]=SUPPLY[1][2]+8*MISC[2];
  SUPPLY[1][3]=SUPPLY[1][3]+8*MISC[2];
  SUPPLY[2][1]=SUPPLY[2][1]+8*MISC[2];
  SUPPLY[2][2]=SUPPLY[2][2]+8*MISC[2];
  SUPPLY[2][3]=SUPPLY[2][3]+8*MISC[2];
  SUPPLY[3][1]=SUPPLY[3][1]+8*MISC[2];
  SUPPLY[3][2]=SUPPLY[3][2]+8*MISC[2];
  SUPPLY[3][3]=SUPPLY[3][3]+8*MISC[2];
  SUPPLY[4][1]=SUPPLY[4][1]+8*MISC[2];
  SUPPLY[4][2]=SUPPLY[4][2]+8*MISC[2];
  SUPPLY[4][3]=SUPPLY[4][3]+8*MISC[2];

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( 1==1 );

  /* schedule future events */
  if (_edge_condition[0])
    /***  The delay corresponds to the length of time spent preparing supplies before opening store to customers  ***/
    {
    for ( t_index=3; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + INPUT[10];
    event_type = ARRIVE_event;
    event_priority = 10;
    schedule_event();
    }

}


/***  ***/
void
GET_PUT()
{
int  _edge_condition[2];

  /* Attribute Value(s) Passed to this Event */
  TYPE[0] = (long) transfer[3];

  /* state changes */
  Q[TYPE[0]]=Q[TYPE[0]]-GET(FST,TYPE[0]);
  Q[2]=Q[2]+PUT(INC,2);

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( Q[TYPE[0]]>0 );
  _edge_condition[1] = ( (Q[TYPE[0]]==0)&&(Q[2]>0) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = TYPE[0];
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = GET_PUT_event;
    event_priority = 2;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = RES[0];
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = NEXTQ_event;
    event_priority = 2;
    schedule_event();
    }

}


/***  ***/
void
AVAIL_W()
{
int  _edge_condition[1];


  /* state changes */
  RES[0]=RES[0]+1;
  RES[2]=RES[2]+1;

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( Q[2]>0 );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = 100;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = NEXTQ_event;
    event_priority = 5;
    schedule_event();
    }

}


/***  ***/
void
CALC()
{

  /* state changes */
  PROFIT=(INPUT[9]*TOTAL[6][1])-(TOTAL[1][1]*INPUT[13]+TOTAL[1][2]*INPUT[14]+TOTAL[1][3]*INPUT[15]+TOTAL[1][4]*INPUT[16]+TOTAL[1][5]*INPUT[17]+TOTAL[1][6]*INPUT[18]+TOTAL[1][7]*INPUT[19]+TOTAL[1][8]*INPUT[20]+TOTAL[1][9]*INPUT[21]+TOTAL[1][10]*INPUT[22]+TOTAL[1][11]*INPUT[23]+TOTAL[1][12]*INPUT[24]);
}

