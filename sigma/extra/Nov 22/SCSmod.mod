

         MODEL DEFAULTS
         --------------

Model Name:         SCSmod.mod
Model Description:  
Output File:        SCSmod.OUT
Output Plot Style:  NOAUTO_FIT
Run Mode:           HI_SPEED
Trace Vars:         PROFIT
Random Number Seed: 12346
Initial Values:     10,3.5,7,4,4,4,4,120,360,1,10,10.26,10.26,5.13,2.025,2.025,2.025,1.35,1.35,1.35,.54,.54,.54,0.4,0.4,0.2,0.1,0.3,0.3,0.3,0.1,0.3,0.3,0.3,0.1,0.3,0.3,0.3,30,40,2,2,12,15,2,2,7,10,2,2,2,4,2,2,1,3,2,2,0.2,1,2,2,0.5,2,2,2,0.5,2,2,2,0.5,2,2,2,13,17,2,2,.51,.61,.50,.66,.50,.63,.30,.46,.50,.15,.15,.15
Ending Condition:   STOP_ON_EVENT
Event:              CALC   (1 iterations)
Trace Events:       CALC
Hide Edges:         



         STATE VARIABLES
         ---------------

     State Variable #1
Name:          I
Description:   array of customer order details
Type:          INTEGER
Size:          7

     State Variable #2
Name:          ID
Description:   customer ID number
Type:          INTEGER
Size:          1

     State Variable #3
Name:          TOTAL
Description:   
Type:          INTEGER
Size:          10,1562

     State Variable #4
Name:          ENT
Description:   
Type:          INTEGER
Size:          15

     State Variable #5
Name:          RNK
Description:   array of random numbers
Type:          REAL
Size:          10000

     State Variable #6
Name:          Q
Description:   
Type:          INTEGER
Size:          15627

     State Variable #7
Name:          INDEX
Description:   index for checking stations
Type:          INTEGER
Size:          1

     State Variable #8
Name:          SUPPLY
Description:   Resources for station i and type j
Type:          INTEGER
Size:          5,4

     State Variable #9
Name:          RESTOCK
Description:   0-1 array if ingregient in restock process
Type:          REAL
Size:          5,4

     State Variable #10
Name:          RES
Description:   array of resources
Type:          REAL
Size:          4

     State Variable #11
Name:          INPUT
Description:   Various inputs from the client
Type:          REAL
Size:          15627

     State Variable #12
Name:          RESTOCKT
Description:   Restock distribution times
Type:          REAL
Size:          5,4

     State Variable #13
Name:          SERVICET
Description:   Service distribution times
Type:          REAL
Size:          5,4

     State Variable #14
Name:          CUSTPREF
Description:   
Type:          REAL
Size:          5,4

     State Variable #15
Name:          MISC
Description:   
Type:          REAL
Size:          15627

     State Variable #16
Name:          ALPHA
Description:   
Type:          REAL
Size:          15627

     State Variable #17
Name:          BETA
Description:   
Type:          REAL
Size:          15627

     State Variable #18
Name:          PROFIT
Description:   
Type:          REAL
Size:          1

     State Variable #19
Name:          TYPE
Description:   
Type:          INTEGER
Size:          15627

     State Variable #20
Name:          THRESH
Description:   
Type:          REAL
Size:          5,4



          VERTICES
          --------

     Vertex #1
Name:             RUN
Description:      rnk[1]=1 denotes that the orderq is sorted by ent[1], the time the ID customer arrived (in increasing order), rnk[2]=6 denotes that Q is sorted by ent[6], the ID of customer (in increasing order, so that customers that arrived first get their cupcakes worked on first)
State Changes:    RNK[2]=7,RNK[8]=7,RNK[9]=7,RNK[10]=7,RNK[11]=7,RNK[24]=7,RNK[26]=7,RNK[28]=7,RNK[30]=7,RNK[50]=7,RNK[53]=7,RNK[56]=7,RNK[59]=7,RES[0]=INPUT[0],RES[1]=INPUT[1],RES[2]=INPUT[2],RES[3]=INPUT[3],MISC[0]=(RES[0]>RES[2]),MISC[1]=((RES[2]/2)>RES[3]),MISC[2]=(INPUT[10]/60)*((MISC[0]*MISC[1]*2*RES[3])+(MISC[0]*(1-MISC[1])*RES[2])+((1-MISC[0])*MISC[1]*2*RES[3])+((1-MISC[0])*(1-MISC[1])*RES[0])),RESTOCK[1;1]=0,RESTOCK[1;2]=0,RESTOCK[2;1]=0,RESTOCK[2;2]=0,RESTOCK[3;1]=0,RESTOCK[3;2]=0,RESTOCK[4;1]=0,RESTOCK[4;2]=0
Parameter(s):     INPUT[8],INPUT[9],INPUT[12],INPUT[0],INPUT[1],INPUT[2],INPUT[3],INPUT[10],INPUT[11],INPUT[27],INPUT[28],THRESH[1;1],THRESH[1;2],THRESH[1;3],THRESH[2;1],THRESH[2;2],THRESH[2;3],THRESH[3;1],THRESH[3;2],THRESH[3;3],THRESH[4;1],THRESH[4;2],THRESH[4;3],CUSTPREF[1;1],CUSTPREF[1;2],CUSTPREF[1;3],CUSTPREF[2;0],CUSTPREF[2;1],CUSTPREF[2;2],CUSTPREF[2;3],CUSTPREF[3;0],CUSTPREF[3;1],CUSTPREF[3;2],CUSTPREF[3;3],CUSTPREF[4;0],CUSTPREF[4;1],CUSTPREF[4;2],CUSTPREF[4;3],RESTOCKT[1;0],RESTOCKT[1;1],ALPHA[1],BETA[1],RESTOCKT[2;0],RESTOCKT[2;1],ALPHA[2],BETA[2],RESTOCKT[3;0],RESTOCKT[3;1],ALPHA[3],BETA[3],RESTOCKT[4;0],RESTOCKT[4;1],ALPHA[4],BETA[4],SERVICET[0;0],SERVICET[0;1],ALPHA[5],BETA[5],SERVICET[1;0],SERVICET[1;1],ALPHA[6],BETA[6],SERVICET[2;0],SERVICET[2;1],ALPHA[7],BETA[7],SERVICET[3;0],SERVICET[3;1],ALPHA[8],BETA[8],SERVICET[4;0],SERVICET[4;1],ALPHA[9],BETA[9],INPUT[25],INPUT[26],ALPHA[10],BETA[10],INPUT[13],INPUT[14],INPUT[15],INPUT[16],INPUT[17],INPUT[18],INPUT[19],INPUT[20],INPUT[21],INPUT[22],INPUT[23],INPUT[24]
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X: -0.00;  Y:  2.72;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #2
Name:             CHECK_S
Description:      
State Changes:    
Parameter(s):     I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X:  1.46;  Y:  1.94;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #3
Name:             LEAVE
Description:      
State Changes:    TOTAL[4;ID]=CLK-I[6],TOTAL[5;ID]=TOTAL[3;ID]+TOTAL[4;ID],TOTAL[6;1]=TOTAL[6;1]+I[5]
Parameter(s):     I[5],I[6],ID
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X:  1.46;  Y:  2.33;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #4
Name:             FINISH
Description:      
State Changes:    RES[0]=RES[0]+1,RES[1]=RES[1]+1*(INDEX==0),TYPE[1]=I[INDEX],I[INDEX]=0,TOTAL[3;ID]=(CLK-I[6])*(INDEX==0)+(TOTAL[3;ID]*(INDEX>0)),I[6]=CLK*(INDEX==0)+(I[6]*(INDEX>0))
Parameter(s):     I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X:  0.06;  Y:  1.95;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #5
Name:             SUP
Description:      
State Changes:    MISC[3]=0
Parameter(s):     I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X:  1.46;  Y:  1.23;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #6
Name:             ARRIVE
Description:      Customer arrives but doesn't get a chance to place an order. (We need to add a non order queue variable)
State Changes:    TOTAL[6;0]=TOTAL[6;0]+1,I[0]=1,MISC[11]=RND,MISC[12]=RND,MISC[13]=RND,MISC[14]=RND,MISC[15]=RND,I[5]=INPUT[27]+(INPUT[28]-INPUT[27])*MISC[15],I[6]=CLK,I[1]=(MISC[11]<CUSTPREF[1;1])+2*((MISC[11]>CUSTPREF[1;1])&(MISC[11]<(CUSTPREF[1;1]+CUSTPREF[1;2])))+3*((MISC[11]>(CUSTPREF[1;1]+CUSTPREF[1;2]))&(MISC[11]<(CUSTPREF[1;1]+CUSTPREF[1;2]+CUSTPREF[1;3]))),I[2]=(MISC[12]<CUSTPREF[2;1])+2*((MISC[12]>CUSTPREF[2;1])&(MISC[12]<(CUSTPREF[2;1]+CUSTPREF[2;2])))+3*((MISC[12]>(CUSTPREF[2;1]+CUSTPREF[2;2]))&(MISC[12]<(CUSTPREF[2;1]+CUSTPREF[2;2]+CUSTPREF[2;3]))),I[3]=(MISC[13]<CUSTPREF[3;1])+2*((MISC[13]>CUSTPREF[3;1])&(MISC[13]<(CUSTPREF[3;1]+CUSTPREF[3;2])))+3*((MISC[13]>(CUSTPREF[3;1]+CUSTPREF[3;2]))&(MISC[13]<(CUSTPREF[3;1]+CUSTPREF[3;2]+CUSTPREF[3;3]))),I[4]=(MISC[14]<CUSTPREF[4;1])+2*((MISC[14]>CUSTPREF[4;1])&(MISC[14]<(CUSTPREF[4;1]+CUSTPREF[4;2])))+3*((MISC[14]>(CUSTPREF[4;1]+CUSTPREF[4;2]))&(MISC[14]<(CUSTPREF[4;1]+CUSTPREF[4;2]+CUSTPREF[4;3])))
Parameter(s):     
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X:  1.79;  Y:  2.71;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #7
Name:             JOINQ
Description:      
State Changes:    TYPE[0]=(INDEX+5*TYPE[1])*TYPE[1]+2,Q[TYPE[0]]=Q[TYPE[0]]+(PUT{INC;TYPE[0]})
Parameter(s):     ENT[0],ENT[1],ENT[2],ENT[3],ENT[4],ENT[5],ENT[6],ENT[7],ENT[8],TYPE[1]
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X:  2.38;  Y:  1.23;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #8
Name:             NEXTQ
Description:      "2" is the location of the customers who have already ordered and their cupcakes are going through the process of being completed
State Changes:    Q[2]=Q[2]-GET{FST;2},I[0]=ENT[0],I[1]=ENT[1],I[2]=ENT[2],I[3]=ENT[3],I[4]=ENT[4],I[5]=ENT[5],I[6]=ENT[6],ID=ENT[7],INDEX=ENT[8]
Parameter(s):     MISC[3]
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X: -0.00;  Y:  1.24;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #9
Name:             RESTK
Description:      RESTOCK[INDEX;TYPE] is a boolean array that is initally set to 0 for product INDEX of type TYPE (ex, product=cake, type=vanilla) and becomes one when that type of product is in the process of being restocked (this functions to eliminate multiple RESTOCKS being scheduled for a particular type of product)
State Changes:    RES[0]=RES[0]-1,RESTOCK[INDEX;TYPE[1]]=1,MISC[4]=INPUT[25]+(INPUT[26]-INPUT[25])*BET{ALPHA[10];BETA[10]},RES[3]=RES[3]-1*(INDEX==1),RES[2]=RES[2]-1
Parameter(s):     INDEX,TYPE[1]
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X: -0.47;  Y:  1.97;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #10
Name:             FINISHR
Description:      20 is the extra amount that was made when a restock event was executed
State Changes:    SUPPLY[INDEX;TYPE[1]]=SUPPLY[INDEX;TYPE[1]]+24+24*(INDEX==1),RESTOCK[INDEX;TYPE[1]]=0,TYPE[0]=((INDEX+5*TYPE[1])*TYPE[1]+2),RES[0]=RES[0]+1*(INDEX>1),RES[3]=RES[3]+1*(INDEX==1),RES[2]=RES[2]+1*(INDEX>1)
Parameter(s):     INDEX,TYPE[1],MISC[4]
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X: -1.06;  Y:  2.07;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #11
Name:             START_S
Description:      
State Changes:    RES[0]=RES[0]-1,RES[1]=RES[1]-1*(INDEX==0),SUPPLY[INDEX;I[INDEX]]=SUPPLY[INDEX;I[INDEX]]-I[5]*(INDEX>0),TYPE[2]=(INDEX>0),TYPE[3]=((INDEX>0)*(3*(INDEX-1)+I[INDEX])),TOTAL[TYPE[2];TYPE[3]]=TOTAL[TYPE[2];TYPE[3]]+I[5]
Parameter(s):     I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X:  1.08;  Y:  1.55;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #12
Name:             WARMUP
Description:      
State Changes:    MISC[7]=INPUT[11]+(INPUT[10]+MISC[9]),MISC[8]=MISC[8]+1,SUPPLY[1;1]=SUPPLY[1;1]+8*MISC[2],SUPPLY[1;2]=SUPPLY[1;2]+8*MISC[2],SUPPLY[1;3]=SUPPLY[1;3]+8*MISC[2],SUPPLY[2;1]=SUPPLY[2;1]+8*MISC[2],SUPPLY[2;2]=SUPPLY[2;2]+8*MISC[2],SUPPLY[2;3]=SUPPLY[2;3]+8*MISC[2],SUPPLY[3;1]=SUPPLY[3;1]+8*MISC[2],SUPPLY[3;2]=SUPPLY[3;2]+8*MISC[2],SUPPLY[3;3]=SUPPLY[3;3]+8*MISC[2],SUPPLY[4;1]=SUPPLY[4;1]+8*MISC[2],SUPPLY[4;2]=SUPPLY[4;2]+8*MISC[2],SUPPLY[4;3]=SUPPLY[4;3]+8*MISC[2]
Parameter(s):     MISC[9],MISC[16]
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X:  1.00;  Y:  2.72;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #13
Name:             GET_PUT
Description:      
State Changes:    Q[TYPE[0]]=Q[TYPE[0]]-GET{FST;TYPE[0]},Q[2]=Q[2]+PUT{INC;2}
Parameter(s):     TYPE[0]
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X: -1.07;  Y:  1.24;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #14
Name:             AVAIL_W
Description:      
State Changes:    RES[0]=RES[0]+1,RES[2]=RES[2]+1
Parameter(s):     
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X: -0.15;  Y:  1.61;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom

     Vertex #15
Name:             CALC
Description:      
State Changes:    PROFIT=(INPUT[9]*TOTAL[6;1])-(TOTAL[1;1]*INPUT[13]+TOTAL[1;2]*INPUT[14]+TOTAL[1;3]*INPUT[15]+TOTAL[1;4]*INPUT[16]+TOTAL[1;5]*INPUT[17]+TOTAL[1;6]*INPUT[18]+TOTAL[1;7]*INPUT[19]+TOTAL[1;8]*INPUT[20]+TOTAL[1;9]*INPUT[21]+TOTAL[1;10]*INPUT[22]+TOTAL[1;11]*INPUT[23]+TOTAL[1;12]*INPUT[24])
Parameter(s):     
Bitmap(Inactive): 
Bitmap(Active):   
Use Flowchart Shapes:   0
Use Opaque Bitmaps:   0
Location:         X:  0.24;  Y:  2.27;  Z: -1.00;
Local Trace:      
Trace Location:   Bottom



          EDGES
          -----


     Graphics Edge #1

  Sub-Edge #1
Description:   
Type:          Scheduling
Origin:        CHECK_S
Destination:   LEAVE
Condition:     (INDEX==4)&(I[INDEX]==0)
Delay:         0
Priority:      10
Attributes:    I[5],I[6],ID

     Graphics Edge #2

  Sub-Edge #2
Description:   
Type:          Scheduling
Origin:        CHECK_S
Destination:   SUP
Condition:     (I[INDEX]>0)
Delay:         0
Priority:      6
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX

     Graphics Edge #3

  Sub-Edge #3
Description:   
Type:          Scheduling
Origin:        CHECK_S
Destination:   CHECK_S
Condition:     I[INDEX]==0&INDEX<4
Delay:         0
Priority:      6
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX+1

     Graphics Edge #4

  Sub-Edge #4
Description:   
Type:          Scheduling
Origin:        FINISH
Destination:   CHECK_S
Condition:     INDEX<4
Delay:         0
Priority:      6
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX+1

     Graphics Edge #5

  Sub-Edge #5
Description:   
Type:          Scheduling
Origin:        ARRIVE
Destination:   ARRIVE
Condition:     CLK<MISC[7]
Delay:         INPUT[8]*ERL{1}
Priority:      10
Attributes:    

     Graphics Edge #6

  Sub-Edge #6
Description:   
Type:          Scheduling
Origin:        FINISH
Destination:   LEAVE
Condition:     INDEX==4
Delay:         0
Priority:      10
Attributes:    I[5],I[6],ID

     Graphics Edge #7

  Sub-Edge #7
Description:   If there are still orders to be fulfilled/cupcakes to be made, the available server will start service on the customer with the lowest ID's cupcake order
Type:          Scheduling
Origin:        FINISH
Destination:   NEXTQ
Condition:     (INDEX==4)&(RES[0]>0)&(Q[2]>0)
Delay:         0
Priority:      5
Attributes:    0

     Graphics Edge #8

  Sub-Edge #8
Description:   
Type:          Scheduling
Origin:        NEXTQ
Destination:   SUP
Condition:     1==1
Delay:         0
Priority:      3
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX

     Graphics Edge #9

  Sub-Edge #9
Description:   
Type:          Scheduling
Origin:        RESTK
Destination:   FINISHR
Condition:     (INDEX>1)
Delay:         RESTOCKT[INDEX;0]+(RESTOCKT[INDEX;1]-RESTOCKT[INDEX;0])*BET{ALPHA[INDEX];BETA[INDEX]}
Priority:      4
Attributes:    INDEX,TYPE[1],0

  Sub-Edge #10
Description:   
Type:          Scheduling
Origin:        RESTK
Destination:   FINISHR
Condition:     (INDEX==1)
Delay:         RESTOCKT[INDEX;0]+(RESTOCKT[INDEX;1]-RESTOCKT[INDEX;0])*BET{ALPHA[INDEX];BETA[INDEX]}+MISC[4]
Priority:      4
Attributes:    INDEX,TYPE[1],MISC[4]

     Graphics Edge #10

  Sub-Edge #11
Description:   
Type:          Scheduling
Origin:        SUP
Destination:   START_S
Condition:     ((SUPPLY[INDEX;I[INDEX]]-1*I[5])>=0)&(RES[0]>0)&(INDEX>0)
Delay:         0
Priority:      4
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX

  Sub-Edge #12
Description:   
Type:          Scheduling
Origin:        SUP
Destination:   START_S
Condition:     (RES[0]>0)&(RES[1]>0)&(INDEX==0)
Delay:         0
Priority:      4
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX

     Graphics Edge #11

  Sub-Edge #13
Description:   
Type:          Scheduling
Origin:        START_S
Destination:   FINISH
Condition:     (INDEX>0)
Delay:         SERVICET[INDEX;0]+(SERVICET[INDEX;1]-SERVICET[INDEX;0])*BET{ALPHA[INDEX+5];BETA[INDEX+5]}*I[5]
Priority:      5
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX

  Sub-Edge #14
Description:   
Type:          Scheduling
Origin:        START_S
Destination:   FINISH
Condition:     (INDEX==0)
Delay:         SERVICET[INDEX;0]+(SERVICET[INDEX;1]-SERVICET[INDEX;0])*BET{ALPHA[5];BETA[5]}
Priority:      5
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX

     Graphics Edge #12

  Sub-Edge #15
Description:   If customer has already ordered and there are no available workers (but there are enough supplies)
Type:          Scheduling
Origin:        SUP
Destination:   JOINQ
Condition:     (INDEX>0)&(RES[0]<=0)&((SUPPLY[INDEX;I[INDEX]]-1*I[5])>=0)
Delay:         0
Priority:      10
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX,0

  Sub-Edge #16
Description:   If customer has not ordered yet and there are no available workers or cash registers
Type:          Scheduling
Origin:        SUP
Destination:   JOINQ
Condition:     ((INDEX==0)&(RES[0]<=0))|((INDEX==0)&(RES[1]<=0))
Delay:         0
Priority:      10
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX,0

  Sub-Edge #17
Description:   If the customer has already ordered and there are not enough supplies to satisfy order
Type:          Scheduling
Origin:        SUP
Destination:   JOINQ
Condition:     (INDEX>0)&((SUPPLY[INDEX;I[INDEX]]-1*I[5])<0)
Delay:         0
Priority:      5
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],ID,INDEX,I[INDEX]

     Graphics Edge #13

  Sub-Edge #18
Description:   The delay corresponds to the length of time spent preparing supplies before opening store to customers
Type:          Scheduling
Origin:        WARMUP
Destination:   ARRIVE
Condition:     1==1
Delay:         INPUT[10]
Priority:      10
Attributes:    

  Sub-Edge #19
Description:   
Type:          Scheduling
Origin:        ARRIVE
Destination:   WARMUP
Condition:     (RES[0]==INPUT[0])&(RES[1]==INPUT[1])&(RES[2]==INPUT[2])&(RES[3]==INPUT[3])&(Q[2]==0)&(CLK>MISC[7])&(MISC[8]<INPUT[12])&(RESTOCK[4;1]==0)&(RESTOCK[4;2]==0)&(RESTOCK[1;1]==0)&(RESTOCK[1;2]==0)&(RESTOCK[2;1]==0)&(RESTOCK[2;2]==0)&(RESTOCK[3;1]==0)&(RESTOCK[3;2]==0)
Delay:         0
Priority:      10
Attributes:    CLK,1

     Graphics Edge #14

  Sub-Edge #20
Description:   How will we know when the last customer leaves the system for the day?  1) when the number of available servers = number of total servers, 2) when the number in Q and ORDERQ equals 0,  3) when CLK > OPEN
Type:          Scheduling
Origin:        LEAVE
Destination:   WARMUP
Condition:     (RES[0]==INPUT[0])&(RES[1]==INPUT[1])&(RES[2]==INPUT[2])&(RES[3]==INPUT[3])&(Q[2]==0)&(CLK>MISC[7])&(MISC[8]<INPUT[12])&(RESTOCK[4;1]==0)&(RESTOCK[4;2]==0)&(RESTOCK[1;1]==0)&(RESTOCK[1;2]==0)&(RESTOCK[2;1]==0)&(RESTOCK[2;2]==0)&(RESTOCK[3;1]==0)&(RESTOCK[3;2]==0)
Delay:         0
Priority:      10
Attributes:    CLK,0

     Graphics Edge #15

  Sub-Edge #21
Description:   
Type:          Scheduling
Origin:        FINISHR
Destination:   WARMUP
Condition:     (RES[0]==INPUT[0])&(RES[1]==INPUT[1])&(RES[2]==INPUT[2])&(RES[3]==INPUT[3])&(Q[2]==0)&(CLK>MISC[7])&(Q[TYPE[0]]<=0)&(MISC[8]<INPUT[12])&(RESTOCK[4;1]==0)&(RESTOCK[4;2]==0)&(RESTOCK[1;1]==0)&(RESTOCK[1;2]==0)&(RESTOCK[2;1]==0)&(RESTOCK[2;2]==0)&(RESTOCK[3;1]==0)&(RESTOCK[3;2]==0)
Delay:         0
Priority:      10
Attributes:    CLK,0

     Graphics Edge #16

  Sub-Edge #22
Description:   
Type:          Scheduling
Origin:        FINISHR
Destination:   GET_PUT
Condition:     Q[TYPE[0]]>0
Delay:         0
Priority:      2
Attributes:    TYPE[0]

     Graphics Edge #17

  Sub-Edge #23
Description:   
Type:          Scheduling
Origin:        GET_PUT
Destination:   GET_PUT
Condition:     Q[TYPE[0]]>0
Delay:         0
Priority:      2
Attributes:    TYPE[0]

     Graphics Edge #18

  Sub-Edge #24
Description:   For cupcake restock
Type:          Scheduling
Origin:        FINISH
Destination:   RESTK
Condition:     (SUPPLY[INDEX;TYPE[1]]<THRESH[INDEX;TYPE[1]])&(RES[0]>0)&(RESTOCK[INDEX;TYPE[1]]==0)&(INDEX==1)&(RES[3]>0)&(RES[2]>0)&(CLK<MISC[7])
Delay:         0
Priority:      1
Attributes:    INDEX,TYPE[1]

  Sub-Edge #25
Description:   For other supply restock
Type:          Scheduling
Origin:        FINISH
Destination:   RESTK
Condition:     (SUPPLY[INDEX;TYPE[1]]<THRESH[INDEX;TYPE[1]])&(RES[0]>0)&(RESTOCK[INDEX;TYPE[1]]==0)&(INDEX>1)&(RES[2]>0)&(CLK<MISC[7])
Delay:         0
Priority:      1
Attributes:    INDEX,TYPE[1]

     Graphics Edge #19

  Sub-Edge #26
Description:   For cupcake restock
Type:          Scheduling
Origin:        SUP
Destination:   RESTK
Condition:     ((SUPPLY[INDEX;I[INDEX]]-1*I[5])<0)&(INDEX==1)&(RESTOCK[INDEX;I[INDEX]]==0)&RES[0]>0&RES[3]>0&RES[2]>0
Delay:         0
Priority:      4
Attributes:    INDEX,I[INDEX]

  Sub-Edge #27
Description:   For other supply restock
Type:          Scheduling
Origin:        SUP
Destination:   RESTK
Condition:     ((SUPPLY[INDEX;I[INDEX]]-1*I[5])<0)&(INDEX>1)&(RESTOCK[INDEX;I[INDEX]]==0)&RES[0]>0&RES[2]>0
Delay:         0
Priority:      5
Attributes:    INDEX,I[INDEX]

     Graphics Edge #20

  Sub-Edge #28
Description:   
Type:          Scheduling
Origin:        GET_PUT
Destination:   NEXTQ
Condition:     (Q[TYPE[0]]==0)&(Q[2]>0)
Delay:         0
Priority:      2
Attributes:    RES[0]

     Graphics Edge #21

  Sub-Edge #29
Description:   
Type:          Scheduling
Origin:        ARRIVE
Destination:   JOINQ
Condition:     (CLK<MISC[7])&((RES[0]<=0)|(RES[1]<=0))
Delay:         0
Priority:      10
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],TOTAL[6;0],0,0

     Graphics Edge #22

  Sub-Edge #30
Description:   
Type:          Scheduling
Origin:        ARRIVE
Destination:   SUP
Condition:     (RES[0]>0)&(RES[1]>0)&(CLK<MISC[7])
Delay:         0
Priority:      10
Attributes:    I[0],I[1],I[2],I[3],I[4],I[5],I[6],TOTAL[6;0],0

     Graphics Edge #23

  Sub-Edge #31
Description:   
Type:          Scheduling
Origin:        NEXTQ
Destination:   NEXTQ
Condition:     (MISC[3]>1)&(Q[2]>0)&(MISC[3]<99)
Delay:         0
Priority:      5
Attributes:    MISC[3]-1

     Graphics Edge #24

  Sub-Edge #32
Description:   
Type:          Scheduling
Origin:        RESTK
Destination:   AVAIL_W
Condition:     (INDEX==1)
Delay:         MISC[4]
Priority:      5
Attributes:    

     Graphics Edge #25

  Sub-Edge #33
Description:   
Type:          Scheduling
Origin:        AVAIL_W
Destination:   NEXTQ
Condition:     Q[2]>0
Delay:         0
Priority:      5
Attributes:    100

     Graphics Edge #26

  Sub-Edge #34
Description:   
Type:          Scheduling
Origin:        CHECK_S
Destination:   NEXTQ
Condition:     (INDEX==4)&(I[INDEX]==0)&(RES[0]>0)&(Q[2]>0)
Delay:         0
Priority:      5
Attributes:    0

     Graphics Edge #27

  Sub-Edge #35
Description:   
Type:          Scheduling
Origin:        FINISHR
Destination:   NEXTQ
Condition:     Q[TYPE[0]]<0&(Q[2]>0)&(RES[0]>0)&(INDEX>1)
Delay:         0
Priority:      5
Attributes:    0

     Graphics Edge #28

  Sub-Edge #36
Description:   
Type:          Scheduling
Origin:        RUN
Destination:   WARMUP
Condition:     1==1
Delay:         0
Priority:      10
Attributes:    0,0

     Graphics Edge #29

  Sub-Edge #37
Description:   
Type:          Scheduling
Origin:        LEAVE
Destination:   CALC
Condition:     (RES[0]==INPUT[0])&(RES[1]==INPUT[1])&(RES[2]==INPUT[2])&(RES[3]==INPUT[3])&(Q[2]==0)&(CLK>MISC[7])&(MISC[8]==INPUT[12])&(RESTOCK[4;1]==0)&(RESTOCK[4;2]==0)&(RESTOCK[1;1]==0)&(RESTOCK[1;2]==0)&(RESTOCK[2;1]==0)&(RESTOCK[2;2]==0)&(RESTOCK[3;1]==0)&(RESTOCK[3;2]==0)
Delay:         0
Priority:      10
Attributes:    

     Graphics Edge #30

  Sub-Edge #38
Description:   
Type:          Scheduling
Origin:        ARRIVE
Destination:   CALC
Condition:     (RES[0]==INPUT[0])&(RES[1]==INPUT[1])&(RES[2]==INPUT[2])&(RES[3]==INPUT[3])&(Q[2]==0)&(CLK>MISC[7])&(MISC[8]==INPUT[12])&(RESTOCK[4;1]==0)&(RESTOCK[4;2]==0)&(RESTOCK[1;1]==0)&(RESTOCK[1;2]==0)&(RESTOCK[2;1]==0)&(RESTOCK[2;2]==0)&(RESTOCK[3;1]==0)&(RESTOCK[3;2]==0)
Delay:         0
Priority:      10
Attributes:    

     Graphics Edge #31

  Sub-Edge #39
Description:   
Type:          Scheduling
Origin:        FINISHR
Destination:   CALC
Condition:     (RES[0]==INPUT[0])&(RES[1]==INPUT[1])&(RES[2]==INPUT[2])&(RES[3]==INPUT[3])&(Q[2]==0)&(CLK>MISC[7])&(Q[TYPE[0]]<=0)&(MISC[8]==INPUT[12])&(RESTOCK[4;1]==0)&(RESTOCK[4;2]==0)&(RESTOCK[1;1]==0)&(RESTOCK[1;2]==0)&(RESTOCK[2;1]==0)&(RESTOCK[2;2]==0)&(RESTOCK[3;1]==0)&(RESTOCK[3;2]==0)
Delay:         0
Priority:      10
Attributes:    

