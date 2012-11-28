/******************************************/
/* SIGMA RUN DEFAULTS FOR TRANSLATED MODEL */
/*******************************************/
/*

         MODEL DEFAULTS
         --------------

Model Name:         SigCake2
Model Description:  
Output File:        UNTITLED.OUT
Output Plot Style:  NOAUTO_FIT
Run Mode:           HI_SPEED
Trace Vars:         TOTAL[1]
Random Number Seed: 12346
Initial Values:     8,4,4,4,120,360,30,30,30,30,.4,.4,.2,.1,.3,.3,.3,.1,.3,.3,.3,.1,.3,.3,.3
Ending Condition:   STOP_ON_TIME
Ending Time:        20000.000
Trace Events:       RUN,GET_PUT,INPUT_D
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
void   INPUT_D(void);	/***  ***/
void   AVAIL_W(void);	/***  ***/
void   CLOSING(void);	/***  ***/

/*   STATE VARIABLE DELARATIONS   */
double R[6];	/***  array of random numbers  ***/
long   I[7];	/***  array of customer order details  ***/
long   ID;	/***  customer ID number  ***/
long   TOTAL[6];	/***    ***/
long   Q[15627];	/***    ***/
long   INDEX;	/***  index for checking stations  ***/
long   SUPPLY[5][4];	/***  Resources for station i and type j  ***/
long   TYPE;	/***    ***/
double RESTOCK[5][4];	/***  0-1 array if ingregient in restock process  ***/
double RES[4];	/***  array of resources  ***/
long   QTYPE;	/***  Denotes which queue the customer is in  ***/
long   AVAIL;	/***  # servers at time of finshr  ***/
long   OPTIME[5];	/***    ***/
long   WAITQ[2][7812];	/***    ***/
long   INPUT[15627];	/***  Various inputs from the client  ***/
long   INVT[8][13];	/***  Inventory array for day i  ***/
double RESTOCKT[5][4];	/***  Restock distribution times  ***/
double SERVICET[5][4];	/***  Service distribution times  ***/
double PREPT;	/***  Time to prepare cupcake batter for oven  ***/
long   IND[2];	/***    ***/
double CUSTPREF[5][4];	/***    ***/
long   CLOSE;	/***    ***/
double REMAIN;	/***    ***/
long   CLOSESTK[5][4];	/***    ***/
long   THRESH[5];	/***    ***/
double MISC[15627];	/***    ***/

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
   INPUT_D_event,
   AVAIL_W_event,
   CLOSING_event,
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

  /* Schedule end of simulation */
  event_time = stop_time;
  event_type = run_end_event;
  event_priority = 9999;
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
               event_trace("RUN",event_count[next_event]);
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
               event_trace("GET_PUT",event_count[next_event]);
               break;

      case INPUT_D_event:  INPUT_D();
               event_trace("INPUT_D",event_count[next_event]);
               break;

      case AVAIL_W_event:  AVAIL_W();
               break;

      case CLOSING_event:  CLOSING();
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
  c_timest(TOTAL[1], 1, 0);
  c_sampst(TOTAL[1], 1, 0);
  if(trace_flag) fprintf(output_fp, "%9.3f\t %6s\t%6d ",current_time,name_of_event,count);
  if(trace_flag) fprintf(output_fp, "	%7.3g \n"
,(double)TOTAL[1]);
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
  if (fscanf(input_fp,"%s %1s %ld %lf %d", output_file_name, &y_n, &rndsd, &stop_time, &trace_flag)<4
     || fscanf(input_fp,"%ld", &INPUT[0])<1
     || fscanf(input_fp,"%ld", &INPUT[1])<1
     || fscanf(input_fp,"%ld", &INPUT[2])<1
     || fscanf(input_fp,"%ld", &INPUT[3])<1
     || fscanf(input_fp,"%ld", &OPTIME[0])<1
     || fscanf(input_fp,"%ld", &OPTIME[1])<1
     || fscanf(input_fp,"%ld", &THRESH[1])<1
     || fscanf(input_fp,"%ld", &THRESH[2])<1
     || fscanf(input_fp,"%ld", &THRESH[3])<1
     || fscanf(input_fp,"%ld", &THRESH[4])<1
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

  if (stop_time <= 0.0) {
     fprintf(stderr,"\nINPUT ERROR: Stopping time %lf is negative!\n",stop_time);
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

     /* Read in run stopping time */
     printf("\nSTOPPING TIME (Enter number of time units until run termination):\n");
     scanf("%lf", &stop_time);
     fflush(stdin);

     /* Read in trace_flag */
     printf("\n\nTRACE (1 = Event Trace, 0 = Summary Only):\n");
     scanf("%d", &trace_flag);
     fflush(stdin);

     /* Parameters for the initial event */;
     printf ( "\nEnter initial value for INPUT[0]: \n");
     scanf  ( "%ld", &INPUT[0]);
     printf ( "\nEnter initial value for INPUT[1]: \n");
     scanf  ( "%ld", &INPUT[1]);
     printf ( "\nEnter initial value for INPUT[2]: \n");
     scanf  ( "%ld", &INPUT[2]);
     printf ( "\nEnter initial value for INPUT[3]: \n");
     scanf  ( "%ld", &INPUT[3]);
     printf ( "\nEnter initial value for OPTIME[0]: \n");
     scanf  ( "%ld", &OPTIME[0]);
     printf ( "\nEnter initial value for OPTIME[1]: \n");
     scanf  ( "%ld", &OPTIME[1]);
     printf ( "\nEnter initial value for THRESH[1]: \n");
     scanf  ( "%ld", &THRESH[1]);
     printf ( "\nEnter initial value for THRESH[2]: \n");
     scanf  ( "%ld", &THRESH[2]);
     printf ( "\nEnter initial value for THRESH[3]: \n");
     scanf  ( "%ld", &THRESH[3]);
     printf ( "\nEnter initial value for THRESH[4]: \n");
     scanf  ( "%ld", &THRESH[4]);
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
   }

 else {
    /* this is not the first time and there is no .exp file */
    return 0;
    }
  
   /* PLACE CUSTOMIZED INITIALIZATIONS HERE */

if (trace_flag)
   {
   fprintf(output_fp,"    Time\t  Event\t Count");
   fprintf(output_fp,"	          TOTAL[1] ");
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
  c_timest(TOTAL[1], 1, 1);
   fprintf(output_fp, "TOTAL[1]:\n Time Ave. = \t%7.4g Time Sample Var. =\t%7.4g\n", transfer[4], transfer[7]);
   printf("TOTAL[1]:\n Time Ave. = 	%7.4g Time Sample Var. = 	%7.4g\n", transfer[4], transfer[7]);
  c_sampst(TOTAL[1], 1, 1);
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
  MISC[2]=(OPTIME[0]/60)*((MISC[0]*MISC[1]*2*RES[3])+(MISC[0]*(1-MISC[1])*RES[2])+((1-MISC[0])*MISC[1]*2*RES[3])+((1-MISC[0])*(1-MISC[1])*RES[0]));

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
    event_type = INPUT_D_event;
    event_priority = 5;
    schedule_event();
    }

}


/***  ***/
void
CHECK_S()
{
int  _edge_condition[3];

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
    event_time = current_time + 0;
    event_type = SUP_event;
    event_priority = 5;
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
    event_priority = 5;
    schedule_event();
    }

}


/***  ***/
void
LEAVE()
{
int  _edge_condition[1];

  /* Attribute Value(s) Passed to this Event */
  I[5] = (long) transfer[3];
  I[6] = (long) transfer[4];
  ID = (long) transfer[5];

  /* state changes */
  WAITQ[1][ID]=CLK-I[6];
  TOTAL[1]=TOTAL[1]+I[5];
  TOTAL[5]=TOTAL[5]+1;

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( (RES[0]==INPUT[0])&&(Q[2]==0)&&(CLK>OPTIME[2])&&(OPTIME[3]<7)&&(RESTOCK[4][1]==0)&&(RESTOCK[4][2]==0)&&(RESTOCK[1][1]==0)&&(RESTOCK[1][2]==0)&&(RESTOCK[2][1]==0)&&(RESTOCK[2][2]==0)&&(RESTOCK[3][1]==0)&&(RESTOCK[3][2]==0) );

  /* schedule future events */
  if (_edge_condition[0])
    /***  How will we know when the last customer leaves the system for the day?  1) when the number of available servers = number of total servers, 2) when the number in Q and ORDERQ equals 0,  3) when CLK > OPEN  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = CLK;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = WARMUP_event;
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
  TYPE=I[INDEX];
  I[INDEX]=0;
  WAITQ[0][ID]=(CLK-I[6])*(INDEX==0)+(WAITQ[0][ID]*(INDEX>0));
  I[6]=CLK*(INDEX==0)+(I[6]*(INDEX>0));

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( INDEX<4 );
  _edge_condition[1] = ( INDEX==4 );
  _edge_condition[2] = ( (INDEX==4)&&(RES[0]>0)&&(Q[2]>0) );
  _edge_condition[3] = ( (SUPPLY[INDEX][TYPE]<THRESH[INDEX])&&(RES[0]>0)&&(RESTOCK[INDEX][TYPE]==0)&&(INDEX==1)&&(CLOSESTK[INDEX][TYPE]==0)&&(RES[3]>0)&&(RES[2]>0)&&(CLK<(OPTIME[2]-60)) );
  _edge_condition[4] = ( (SUPPLY[INDEX][TYPE]<THRESH[INDEX])&&(RES[0]>0)&&(RESTOCK[INDEX][TYPE]==0)&&(INDEX>1)&&(CLOSESTK[INDEX][TYPE]==0)&&(RES[2]>0) );

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
    event_priority = 5;
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
    event_priority = 5;
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
    transfer[4] = TYPE;
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = RESTK_event;
    event_priority = 8;
    schedule_event();
    }

  if (_edge_condition[4])
    /***  For other supply restock  ***/
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = INDEX;
    transfer[4] = TYPE;
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = RESTK_event;
    event_priority = 8;
    schedule_event();
    }

}


/***  ***/
void
SUP()
{
int  _edge_condition[8];

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
  AVAIL=0;

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( ((SUPPLY[INDEX][I[INDEX]]-1*I[5])>=0)&&(RES[0]>0)&&(INDEX>0) );
  _edge_condition[1] = ( (RES[0]>0)&&(RES[1]>0)&&(INDEX==0) );
  _edge_condition[2] = ( (INDEX>0)&&(RES[0]<=0)&&((SUPPLY[INDEX][I[INDEX]]-1*I[5])>=0) );
  _edge_condition[3] = ( ((INDEX==0)&&(RES[0]<=0))||((INDEX==0)&&(RES[1]<=0)) );
  _edge_condition[4] = ( (INDEX>0)&&((SUPPLY[INDEX][I[INDEX]]-1*I[5])<0) );
  _edge_condition[5] = ( ((SUPPLY[INDEX][I[INDEX]]-1*I[5])<0)&&(INDEX==1)&&(RESTOCK[INDEX][I[INDEX]]==0)&&RES[0]>0&&RES[3]>0&&RES[2]>0 );
  _edge_condition[6] = ( ((SUPPLY[INDEX][I[INDEX]]-1*I[5])<0)&&(INDEX>1)&&(RESTOCK[INDEX][I[INDEX]]==0)&&RES[0]>0&&RES[2]>0 );
  _edge_condition[7] = ( (CLK>OPTIME[2])&&(CLOSE==0) );

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
    event_priority = 3;
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
    event_priority = 3;
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
    event_priority = 5;
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
    event_priority = 5;
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

  if (_edge_condition[7])
    {
    for ( t_index=3; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = CLOSING_event;
    event_priority = 5;
    schedule_event();
    }

}


/*** Customer arrives but doesn't get a chance to place an order. (We need to add a non order queue variable) ***/
void
ARRIVE()
{
int  _edge_condition[3];


  /* state changes */
  TOTAL[0]=TOTAL[0]+1;
  I[0]=1;
  R[1]=RND;
  R[2]=RND;
  R[3]=RND;
  R[4]=RND;
  R[5]=RND;
  I[5]=1+(10-1)*R[5];
  I[6]=CLK;
  I[1]=(R[1]<CUSTPREF[1][1])+2*((R[1]>CUSTPREF[1][1])&&(R[1]<(CUSTPREF[1][1]+CUSTPREF[1][2])))+3*((R[1]>(CUSTPREF[1][1]+CUSTPREF[1][2]))&&(R[1]<(CUSTPREF[1][1]+CUSTPREF[1][2]+CUSTPREF[1][3])));
  I[2]=(R[2]<CUSTPREF[2][1])+2*((R[2]>CUSTPREF[2][1])&&(R[2]<(CUSTPREF[2][1]+CUSTPREF[2][2])))+3*((R[2]>(CUSTPREF[2][1]+CUSTPREF[2][2]))&&(R[2]<(CUSTPREF[2][1]+CUSTPREF[2][2]+CUSTPREF[2][3])));
  I[3]=(R[3]<CUSTPREF[3][1])+2*((R[3]>CUSTPREF[3][1])&&(R[3]<(CUSTPREF[3][1]+CUSTPREF[3][2])))+3*((R[3]>(CUSTPREF[3][1]+CUSTPREF[3][2]))&&(R[3]<(CUSTPREF[3][1]+CUSTPREF[3][2]+CUSTPREF[3][3])));
  I[4]=(R[4]<CUSTPREF[4][1])+2*((R[4]>CUSTPREF[4][1])&&(R[4]<(CUSTPREF[4][1]+CUSTPREF[4][2])))+3*((R[4]>(CUSTPREF[4][1]+CUSTPREF[4][2]))&&(R[4]<(CUSTPREF[4][1]+CUSTPREF[4][2]+CUSTPREF[4][3])));
  TOTAL[4]=TOTAL[4]+(CLK<OPTIME[2]);
  TOTAL[2]=TOTAL[2]+I[5];

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( CLK<OPTIME[2] );
  _edge_condition[1] = ( (CLK<OPTIME[2])&&((RES[0]<=0)||(RES[1]<=0)) );
  _edge_condition[2] = ( (RES[0]>0)&&(RES[1]>0)&&(CLK<OPTIME[2]) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    for ( t_index=3; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 1+(10-1)*RND;
    event_type = ARRIVE_event;
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
    transfer[10] = TOTAL[0];
    transfer[11] = 0;
    transfer[12] = 0;
    for ( t_index=13; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = JOINQ_event;
    event_priority = 5;
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
    transfer[10] = TOTAL[0];
    transfer[11] = 0;
    for ( t_index=12; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = SUP_event;
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
  TYPE = (long) transfer[12];

  /* state changes */
  QTYPE=(INDEX+5*TYPE)*TYPE+2;
  Q[QTYPE]=Q[QTYPE]+(PUT(INC,QTYPE));
}


/*** "2" is the location of the customers who have already ordered and their cupcakes are going through the process of being completed ***/
void
NEXTQ()
{
int  _edge_condition[2];

  /* Attribute Value(s) Passed to this Event */
  AVAIL = (long) transfer[3];

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
  _edge_condition[1] = ( (AVAIL>1)&&(Q[2]>0)&&(AVAIL<99) );

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
    event_priority = 4;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = AVAIL-1;
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
  TYPE = (long) transfer[4];

  /* state changes */
  RES[0]=RES[0]-1;
  RESTOCK[INDEX][TYPE]=1;
  PREPT=13+(17-13)*RND;

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
    transfer[4] = TYPE;
    transfer[5] = 0;
    for ( t_index=6; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + RESTOCKT[INDEX][0]+(RESTOCKT[INDEX][1]-RESTOCKT[INDEX][0])*RND;
    event_type = FINISHR_event;
    event_priority = 4;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = INDEX;
    transfer[4] = TYPE;
    transfer[5] = PREPT;
    for ( t_index=6; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + (RESTOCKT[INDEX][0]+(RESTOCKT[INDEX][1]-RESTOCKT[INDEX][0])*RND)+PREPT;
    event_type = FINISHR_event;
    event_priority = 4;
    schedule_event();
    }

  if (_edge_condition[2])
    {
    for ( t_index=3; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + PREPT;
    event_type = AVAIL_W_event;
    event_priority = 5;
    schedule_event();
    }

}


/*** 20 is the extra amount that was made when a restock event was executed ***/
void
FINISHR()
{
int  _edge_condition[2];

  /* Attribute Value(s) Passed to this Event */
  INDEX = (long) transfer[3];
  TYPE = (long) transfer[4];
  PREPT = transfer[5];

  /* state changes */
  SUPPLY[INDEX][TYPE]=SUPPLY[INDEX][TYPE]+24+24*(INDEX==1);
  RESTOCK[INDEX][TYPE]=0;
  QTYPE=((INDEX+5*TYPE)*TYPE+2);
  RES[0]=RES[0]+1*(INDEX>1);
  RES[3]=RES[3]+1*(INDEX==1);
  RES[2]=RES[2]+1*(INDEX>1);

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( (RES[0]==INPUT[0])&&(Q[2]==0)&&(CLK>OPTIME[2])&&(Q[TYPE]<=0)&&(OPTIME[3]<7)&&(RESTOCK[4][1]==0)&&(RESTOCK[4][2]==0)&&(RESTOCK[1][1]==0)&&(RESTOCK[1][2]==0)&&(RESTOCK[2][1]==0)&&(RESTOCK[2][2]==0)&&(RESTOCK[3][1]==0)&&(RESTOCK[3][2]==0) );
  _edge_condition[1] = ( Q[QTYPE]>0 );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = CLK;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = WARMUP_event;
    event_priority = 10;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = QTYPE;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = GET_PUT_event;
    event_priority = 3;
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
    event_time = current_time + (SERVICET[INDEX][0]+(SERVICET[INDEX][1]-SERVICET[INDEX][0])*RND)*I[5];
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
    event_time = current_time + (SERVICET[INDEX][0]+(SERVICET[INDEX][1]-SERVICET[INDEX][0])*RND);
    event_type = FINISH_event;
    event_priority = 5;
    schedule_event();
    }

}


/***  ***/
void
WARMUP()
{
int  _edge_condition[1];

  /* Attribute Value(s) Passed to this Event */
  OPTIME[4] = (long) transfer[3];

  /* state changes */
  INVT[OPTIME[3]][1]=SUPPLY[1][1];
  INVT[OPTIME[3]][2]=SUPPLY[1][2];
  INVT[OPTIME[3]][3]=SUPPLY[1][3];
  INVT[OPTIME[3]][4]=SUPPLY[2][1];
  INVT[OPTIME[3]][5]=SUPPLY[2][2];
  INVT[OPTIME[3]][6]=SUPPLY[2][3];
  INVT[OPTIME[3]][7]=SUPPLY[3][1];
  INVT[OPTIME[3]][8]=SUPPLY[3][2];
  INVT[OPTIME[3]][9]=SUPPLY[3][3];
  INVT[OPTIME[3]][10]=SUPPLY[4][1];
  INVT[OPTIME[3]][11]=SUPPLY[4][2];
  INVT[OPTIME[3]][12]=SUPPLY[4][3];
  OPTIME[2]=OPTIME[1]+(OPTIME[0]+OPTIME[4]);
  OPTIME[3]=OPTIME[3]+1;
  CLOSE=0;
  CLOSESTK[1][1]=0;
  CLOSESTK[1][2]=0;
  CLOSESTK[1][3]=0;
  CLOSESTK[2][1]=0;
  CLOSESTK[2][2]=0;
  CLOSESTK[2][3]=0;
  CLOSESTK[3][1]=0;
  CLOSESTK[3][2]=0;
  CLOSESTK[3][3]=0;
  CLOSESTK[4][1]=0;
  CLOSESTK[4][2]=0;
  CLOSESTK[4][3]=0;
  TOTAL[2]=0;
  TOTAL[3]=0;
  TOTAL[4]=0;
  TOTAL[5]=0;
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
    event_time = current_time + OPTIME[0];
    event_type = ARRIVE_event;
    event_priority = 5;
    schedule_event();
    }

}


/***  ***/
void
GET_PUT()
{
int  _edge_condition[2];

  /* Attribute Value(s) Passed to this Event */
  QTYPE = (long) transfer[3];

  /* state changes */
  Q[QTYPE]=Q[QTYPE]-GET(FST,QTYPE);
  Q[2]=Q[2]+PUT(INC,2);

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( Q[QTYPE]>0 );
  _edge_condition[1] = ( (Q[QTYPE]==0)&&(Q[2]>0) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = QTYPE;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = GET_PUT_event;
    event_priority = 3;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = RES[0];
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = NEXTQ_event;
    event_priority = 5;
    schedule_event();
    }

}


/***  ***/
void
INPUT_D()
{
int  _edge_condition[3];

  /* Attribute Value(s) Passed to this Event */
  IND[0] = (long) transfer[3];
  IND[1] = (long) transfer[4];

  /* state changes */
  RESTOCK[IND[0]][IND[1]]=DISK(RESTOCK.DAT,(IND[0]*4+IND[1]+1));
  RESTOCKT[IND[0]][IND[1]]=DISK(RESTOCKT.DAT,(IND[0]*4+IND[1]+1));
  SERVICET[IND[0]][IND[1]]=DISK(SERVICET.DAT,(IND[0]*4+IND[1]+1));

  /* Evaluate edge conditions now so that they will*/
  /* not be changed by preemptive event execution  */
  _edge_condition[0] = ( IND[0]==4&&IND[1]==3 );
  _edge_condition[1] = ( (IND[0]<=4)&&(IND[1]<3) );
  _edge_condition[2] = ( (IND[0]<4)&&(IND[1]==3) );

  /* schedule future events */
  if (_edge_condition[0])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = 0;
    for ( t_index=4; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = WARMUP_event;
    event_priority = 5;
    schedule_event();
    }

  if (_edge_condition[1])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = IND[0];
    transfer[4] = IND[1]+1;
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = INPUT_D_event;
    event_priority = 5;
    schedule_event();
    }

  if (_edge_condition[2])
    {
    /*** attribute value(s) to be transferred to event ***/
    transfer[3] = IND[0]+1;
    transfer[4] = 0;
    for ( t_index=5; t_index<maxatr; t_index++) transfer[t_index] = 0.0;
    event_time = current_time + 0;
    event_type = INPUT_D_event;
    event_priority = 5;
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
CLOSING()
{

  /* state changes */
  CLOSE=1;
  REMAIN=TOTAL[2]-TOTAL[3];
  CLOSESTK[1][1]=(SUPPLY[1][1]>(CUSTPREF[1][1]*REMAIN));
  CLOSESTK[1][2]=(SUPPLY[1][2]>(CUSTPREF[1][2]*REMAIN));
  CLOSESTK[1][3]=(SUPPLY[1][3]>(CUSTPREF[1][3]*REMAIN));
  CLOSESTK[2][1]=(SUPPLY[2][1]>(CUSTPREF[2][1]*REMAIN));
  CLOSESTK[2][2]=(SUPPLY[2][2]>(CUSTPREF[2][2]*REMAIN));
  CLOSESTK[2][3]=(SUPPLY[2][3]>(CUSTPREF[2][3]*REMAIN));
  CLOSESTK[3][1]=(SUPPLY[3][1]>(CUSTPREF[3][1]*REMAIN));
  CLOSESTK[3][2]=(SUPPLY[3][2]>(CUSTPREF[3][2]*REMAIN));
  CLOSESTK[3][3]=(SUPPLY[3][3]>(CUSTPREF[3][3]*REMAIN));
  CLOSESTK[4][1]=(SUPPLY[4][1]>(CUSTPREF[4][1]*REMAIN));
  CLOSESTK[4][2]=(SUPPLY[4][2]>(CUSTPREF[4][2]*REMAIN));
  CLOSESTK[4][3]=(SUPPLY[4][3]>(CUSTPREF[4][3]*REMAIN));
}

