#include "allFunctions.h"

char busStopNames[9][15] ={"Mumbai", "Vasai-East", "Vapi", "Valsad", "Navsari", "Surat", "Bharuch", "Vadodara", "Ahmedabad"};
int prices[9] = { 0, 125, 175, 200, 250, 300, 375, 400, 500};

char mumbaiToAhmedabadBus[10][200];
char ahmedabadToMumbaiBus[10][200];

struct busBookingData bookingData[100];
int bookingDataLength = 0;

// ---------------------------------------------------[ Data Loading Function ]
/*
    void loadBusBookingDataIntoGlobalVariables()
            Aim Of This Function Is To Load Data From Text Files Into Variables.
            Also To Avoid Constant File Interaction/Operation Due To Which We Can
            Attain Better Performance And Ease Of Coding.
    Arguments : No Arguments
    Returns : Void
*/
void loadBusBookingDataIntoGlobalVariables(){
    // Opening Files
    FILE *fpA = fopen("ahmedabadBus.txt", "r");
    FILE *fpM = fopen("mumbaiBus.txt", "r");
    char rowOfAhmedabadBus[50] = "";
    char rowOfMumbaiBus[50] = "";
    // Using Loop To Load Data One By One Into Matrix
    int index = 0;
    while(fgets(rowOfAhmedabadBus, 50, fpA) && fgets(rowOfMumbaiBus, 50, fpM)) // Using 'fgets' To Retrive Row Data 
    {
        // Performing -1 To Avaoid Last Character Which Is '\n'
        int ml = strlen(rowOfMumbaiBus)-1;
        int al = strlen(rowOfAhmedabadBus)-1;
        // Adding Row Data Into Character Matrix Variable Row
        strncat(mumbaiToAhmedabadBus[index], rowOfMumbaiBus, ml);
        strncat(ahmedabadToMumbaiBus[index], rowOfAhmedabadBus, al);
        index=1+index;
    }
    fclose(fpA);
    fclose(fpM);
    
    FILE *fpB = fopen("bookingData.txt", "r");
    char rowOfBookingData[180] = "";
    index = 0;
    while(fgets(rowOfBookingData, 180, fpB))
    {
        char *tok = strtok(rowOfBookingData, "|");
        strcpy(bookingData[index].userId, tok);
        tok = strtok(NULL, "|");
        int l = strlen(tok)-1;
        strncpy(bookingData[index].seatNumbers, tok, l);
        index = 1 + index;
    }
    bookingDataLength = index;
    fclose(fpB);
} // Complete

// ---------------------------------------------------[ Display Data Functions ]
/*
    void displayRoutes()
            Aim Of This Function Is To Display Routes Available Of Bus.
    Arguments : No Arguments
    Returns : Void
*/
void displayRoutes(){
    printf("\n\tWe Have Buses Available From Mumbai To Ahmedabad And Vice-Versa With Following Stops");
    printf("\n\t1 [ Mumbai -->");
    for(int i=1; i<8; i ++)
        printf(" %s-->", busStopNames[i]);
    printf("Ahmedabad ]\n");
    
    printf("\n\t2 [ Ahmedabad -->");
    for(int i=7; i>=1; i--)
        printf(" %s-->", busStopNames[i]);
    printf("Mumbai ]\n");
} // Complete

/*
    void displayRoutePriceTable()
            Aim Of This Function Is To Display Routes With Their Prices Available.
    Arguments : No Arguments
    Returns : Void
*/
void displayRoutePriceTable(){
    char line[200];
    int index = 1;
    printf("---------------------------------------------------------------------------------------------------------\n");
    FILE *fp = fopen("displayPriceTable.txt", "r");
    while(fgets(line, 200, fp))
    {
        printf("%d - %s", index, line);
        index = index + 1;
    }
    fclose(fp);
}   // Complete

/*
    void displayNumberOfBookedTickets()
            Aim Of This Function Is To Display Booked Seats And Vacant Seats Along Side.
    Arguments : No Arguments
    Returns : Void
*/
void displayNumberOfBookedTickets(){
    int indicator = 0;
    printf("\tEnter 0 For The Bus From Mumbai to Ahmedabad\n");
    printf("\tEnter 1 For The Bus From Ahmedabad to Mumbai\n\tEnter Choice : ");
    scanf("%d", &indicator);
    int seatBookedCounts[10][4] = {0};
    int totalSeatsBooked = 0;
    for(int i=0; i<10; i++)
    {
        char line[100] = {'\0'};
        if(indicator == 0)
            strcpy(line, mumbaiToAhmedabadBus[i]);
        else
            strcpy(line, ahmedabadToMumbaiBus[i]);
        int col=0;
        for(int j=0; j<strlen(line); j++)
        {
            if(line[j] == 'V')
            {
                seatBookedCounts[i][col] = 0;
            }
            else if(line[j] == '|')
            {
                ++col;
            }
            else if(line[j] >= 'A' && line[j] < 'V')
            {
                ++seatBookedCounts[i][col];
            }
        }
    }
    for(int row=0; row<10; row++)
    {
        char s0 = 'V', s1 = 'V', s2 = 'V', s3 = 'V';
        if(seatBookedCounts[row][0] != 0)
        {
            s0 = 'B';
            totalSeatsBooked++;
        }
        if(seatBookedCounts[row][1] != 0)
        {
            s1 = 'B';
            totalSeatsBooked++;
        }
        if(seatBookedCounts[row][2] != 0)
        {
            s2 = 'B';
            totalSeatsBooked++;
        }
        if(seatBookedCounts[row][3] != 0)
        {
            s3 = 'B';
            totalSeatsBooked++;
        }
        printf("\n\t|                           |");
        printf("\n\t| |   | |   |   |   | |   | |");
        printf("\n\t| | %c | | %c |   | %c | | %c | |", s0, s1, s2, s3);
        printf("\n\t| ----- -----   ----- ----- |");
    }
    printf("\n\tTotal Number of Booked Seats  = %d\n", totalSeatsBooked);
    printf("\n\tTotal Number of Vacant Seats  = %d\n", 40-totalSeatsBooked);
}  // Complete

/*
    void showBusStructure(int Index)
            Aim Of This Function Is To Display Booked And Vacant Seats With Seat Numbers.
    Arguments : One Integer Value
    Returns : Void
*/
void showBusStructure(int index){
    if(index < 0 && index > 2)
    {   
        printf("Invalid Input");
        return;
    }
    for(int i=0; i<10; i++)
    {   
        char dummyLine[50]="";
        if(index == 1)      // Mumbai to Ahmedabad
        {
            strcat(dummyLine, mumbaiToAhmedabadBus[i]);
        }
        else if(index == 2) // Ahmedabad to Mumbai
        {
            strcat(dummyLine, ahmedabadToMumbaiBus[i]);
        }
        char *tok = strtok(dummyLine, "|"); 
        printf("\t|                                                             |\n");
        printf("\t| |            ||            |   |            ||            | |\n\t| ");
        char ptok[10][20]={""};
        int ptokLen = 0;
        while(tok)
            {
                int tokLen = strlen(tok);
                
                if(tok[0] == 'V')
                {
                    char vacant[8] = "Vacant";
                    char seat[8]   = "Seat";
                    strcat(ptok[ptokLen], vacant);
                    ptokLen=ptokLen+1;
                    strcat(ptok[ptokLen], seat);
                    ptokLen=ptokLen+1;
                }
                else if(tokLen <= 8 && tokLen>=2)
                {
                    char vacant[10] = "     ";
                    char seat[10] = "";
                    for(int a=0; a<tokLen; a++)
                        //printf("**%c**",tok[i]);
                        seat[a] = tok[a];
                    strcat(ptok[ptokLen], vacant);
                    ptokLen=ptokLen+1;
                    strcat(ptok[ptokLen], seat);
                    ptokLen=ptokLen+1;
                }
                else if(tokLen > 8 && tokLen <= 16)
                {
                    char vacant[10] = "";
                    char set[10] = "";
                    for(int b=0; b<8; b++)
                    {
                        vacant[b] = tok[b];
                    }
                    for(int a=8; a<tokLen; a++)
                    {
                        set[a-8] = tok[a];
                    }
                    strcat(ptok[ptokLen], vacant);
                    ptokLen=ptokLen+1;
                    strcat(ptok[ptokLen], set);
                    ptokLen=ptokLen+1;
                }
                tok = strtok(NULL, "|");
            }
       
        for(int oddIndex=0; oddIndex < 8; oddIndex++)
        {   
            if(oddIndex%2 == 0)
                printf("| [%-8s] |", ptok[oddIndex]);
            if(oddIndex == 2) printf("   ");
        }
        printf(" |\n\t| ");
        for(int evenIndex=0; evenIndex < 8; evenIndex++)
        {
            if(evenIndex%2 == 1)
                printf("| [%-8s] |", ptok[evenIndex]);
            if(evenIndex == 3) printf("   ");
        }
        printf(" |\n\t| |---(S0R%d)---||---(S1R%d)---|   |---(S2R%d)---||---(S3R%d)---| |", i,i,i,i);
        printf(" \n");
    }
    printf("\tSelect Your Seats");
}  // Complete

void displayMyBooking(char *userId){
    int row = 0;
    int rowFound = -1;
    while(row < bookingDataLength)
    {
        if(strcmp(bookingData[row].userId, userId) == 0)
        {
            rowFound = row;
            char fromMumbai[100] = "";
            char fromAhmedabad[100] = "";
            int fromMumbaiIndex = 0;
            int fromAhmedabadIndex = 0;
            
            char line[100];
            strcpy(line, bookingData[row].seatNumbers);
            char *tok = strtok(line, ",");
            while(tok)
            {
                if(tok[0] == 'M')
                {
                    fromMumbai[fromMumbaiIndex] = tok[2];   ++fromMumbaiIndex;
                    fromMumbai[fromMumbaiIndex] = tok[3];   ++fromMumbaiIndex;
                    fromMumbai[fromMumbaiIndex] = tok[4];   ++fromMumbaiIndex;
                    fromMumbai[fromMumbaiIndex] = tok[5];   ++fromMumbaiIndex;
                    fromMumbai[fromMumbaiIndex] = ',';      ++fromMumbaiIndex;
                }
                else if(tok[0] == 'A')
                {
                    fromAhmedabad[fromAhmedabadIndex] = tok[2];   ++fromAhmedabadIndex;
                    fromAhmedabad[fromAhmedabadIndex] = tok[3];   ++fromAhmedabadIndex;
                    fromAhmedabad[fromAhmedabadIndex] = tok[4];   ++fromAhmedabadIndex;
                    fromAhmedabad[fromAhmedabadIndex] = tok[5];   ++fromAhmedabadIndex;
                    fromAhmedabad[fromAhmedabadIndex] = ',';      ++fromAhmedabadIndex;
                }
                tok = strtok(NULL, ",");
            }
            
            printf("\n\tUser Id : %s\n\tSeats Booked :", userId);
            printf("\n\tFrom Mumbai To Ahmedabad :\n\t%s", fromMumbai);
            printf("\n\tFrom Ahmedabad To Mumbai :\n\t%s", fromAhmedabad);
            return;
        }
        row = row + 1;
    }
    if(rowFound == -1)
    {
        printf("\n\tNo Booking");
        return;
    }
    
}

int printTicket(char sp, char ep, char ticket[], int busFare, int ch){
    char s[10]={'A','B','C','D','E','F','G','H','I'};
    char *e,*f;
    int index,index2;
    e = strchr(s, sp);
    index = (int)(e - s);
    f = strchr(s, ep);
    index2= (int)(f - s);
    printf("\n\t\t _________________________________________");
    printf("\n\t\t          Bharat Bus Pvt Ltd.            ");
    printf("\n\t\t*****************************************");    
    printf("\n\t\t                TICKET                   ");
    printf("\n\t\t*****************************************");
    if(ch==1)
    {
        printf("\n\t\t  Start Point :- %s                      ",busStopNames[index]);
        printf("\n\t\t  Stop Point  :- %s                       ",busStopNames[index2]);
    }
    else
    {
        printf("\n\t\t  Start Point :- %s                      ",busStopNames[8-index]);
        printf("\n\t\t  Stop Point  :- %s                       ",busStopNames[8-index2]);
    }
    printf("\n\t\t  Seat Number :- %s                      ",ticket);
    printf("\n\t\t  Fare Price  :- Rs.%d/-            ",busFare);
    printf("\n\t\t                                         ");
    printf("\n\t\t             Enjoy Your Ride!            ");
    printf("\n\t\t_________________________________________\n");
    return EXIT_SUCCESS;
} // Complete

/*
    void bookTicket(char seatNo[], char startPoint, char endPoint, int ch)
            This Function Does Following Operations In Their Respective Order.
                1. Look/Search For The Row Data In Which Seat Data Is Available.
                2. Copy That Row Data Into Dummy Variable.
                3. Use Tokenization On That Dummy Variable To Retrive Each Seat Data.
                4. Once Data Found Varify That Seat Is Vacan From Onboarding To Destination Point.
                5.1. If Vacant, The Update The Record.
                5.2. If Not, Then Tell User Seat is Booked.
    Arguments :
            1. String 'seatNo' - Contains Seat Number.
            2. Character 'startPoint' - Contains Onboarding Point.
            3. Character 'endPoint' - Contains Destination Point.
            4. Integer 'ch' - Stands For Choice And Contains Choice For Route.
    Returns : Void
*/
int bookTicket(char se[], char *userId, char startPoint, char endPoint, int ch){
    char s[10];
    strcpy(s,se);
    int asciiTable[130] = {0};
    char line[100];
    int row = se[3] - 48;
    int col = se[1] - 48;
    int choice=ch;
    
    char sp = startPoint;
    char ep = endPoint;
    
    if(ch == 1) // Mumbai to Ahmedabad
        strcpy(line, mumbaiToAhmedabadBus[row]);
    else
        strcpy(line, ahmedabadToMumbaiBus[row]);
        
    char *tok = strtok(line, "|");
    int index=0;
    char dummyLine[100];
    for(int i=0; i<100; i++)
        dummyLine[i] = '\0';
        
    while(tok)
    {
        if(index == col) // We Will Enter in If Block if index == column, means we are in the same column data of the seat
        {
            ++index;
            if(strlen(tok) == 1) // If length of tok == 1, then this means the seat is Vacant
            {
                // strncat(str, &ch, 1); 
                strncat(dummyLine, &startPoint, 1);
                strncat(dummyLine, &endPoint, 1);
                strcat(dummyLine, "|");
                tok = strtok(NULL, "|");
                continue;
            }
            /*
                Logic (from line 282 to 287): 
                    1.'asciiTable' represents Ascii Table.
                    2. Every Index Of 'asciiTable' Represent Character Value.
                    3. So Every Of 'tok' Character Will Take Us To Special Index.
                    4. In That Index We Store The Destination Point Value.
                    5. Therefore, Index Becomes Onboarding Value and Element 
                        At That Index Will Become Destination.
            */
            int i=0;
            while(i<strlen(tok))
            {
                asciiTable[(int) tok[i]] = tok[i+1];
                i=i+3;
            }
             /*
                Logic (from line 295 to 304) :
                    1. Checking Value Of Element(Destination) Of Specific Index(Onboarding) In Ascii Table.
                    2. If Element Value Is Greater Than 'startPoint' (Onboarding), 
                        Then That Means Seat is Booked.
                    3. If Not Then Seat Probably Is Vacant or Booked Till Our Onboarding Point.
            */
            i=(int)(sp-1);
            while(i>='A')
            {
                if(asciiTable[i] > sp)
                {
                  printf("\n\tSorry this Seat Is Already Booked\n");
                  return 1;
                }
                i=i-1;
            }
            /*
                Logic (from line 312 to 321) :
                    1. Checking Value Of Element(Destination) Of Specific Index(Onboarding) In Ascii Table.
                    2. If Element Value Is Smaller Than 'endPoint' (Destination), 
                        Then That Means Seat is Booked.
                    3. If Not Then Seat Probably Is Vacant or Booked After Our Destination Point.
            */
            i=(int)(sp);
            while(i<ep)
            {
                if(asciiTable[i] > 0)
                {
                  printf("\n\tSorry this Seat Is Already Booked\n");
                  return 1;
                }
                i=i+1;
            }
            
            
            strcat(dummyLine, tok);
            strcat(dummyLine, ",");
            
            // strncat(str, &ch, 1); 
            strncat(dummyLine, &startPoint, 1);
            strncat(dummyLine, &endPoint, 1);
            
            strcat(dummyLine, "|");
            tok = strtok(NULL, "|");
            continue;
        }
        ++index;
        strcat(dummyLine, tok);
        strcat(dummyLine, "|");
        tok = strtok(NULL, "|");
    }
    
    char a[12]={'A','B','C','D','E','F','G','H','I'};
    int startPrice = -1, endPrice = -1;
    for(int i=0; i < 9; i++)
    {
        if(a[i] == startPoint)
            startPrice = i;
        if(a[i] == endPoint)
            endPrice = i;
    }
    
    char d='\0';
    int busFare = prices[endPrice]-prices[startPrice];
    printf("\n\tSeat Found To Be Empty From Start Point to Destination :");
    printf("\n\tYour Fare For The Journey Is Rs%d \n", busFare);
    printf("\tDo You Want To Book The Seat([Y,y = yes] & [N,n = No])\n\tInput : ");
    scanf(" %c", &d);
    if(d == 'N' || d == 'n')
    {
        printf("\n\tBooking Cancelled...\n");
        return 0;
    }
    printf("\n\tSeat Is Successfully Booked %s", dummyLine);
     // From Line 361 to 375 We Update Data In Their Respective Files
    FILE *fp;
    if(ch == 1) // Mumbai to Ahmedabad
    {    
        strcpy(mumbaiToAhmedabadBus[row], dummyLine);
        fp = fopen("mumbaiBus.txt", "w");
        
        for(int i=0; i<10; i++)
        {
            fprintf(fp,"%s\n", mumbaiToAhmedabadBus[i]);
        }
    }
    else
    {    
        strcpy(ahmedabadToMumbaiBus[row], dummyLine);
        fp = fopen("ahmedabadBus.txt", "w");
        
        for(int i=0; i<10; i++)
        {
            fprintf(fp,"%s\n", ahmedabadToMumbaiBus[i]);
        }
    }
    fclose(fp);
    printTicket(sp, ep, s, busFare, choice);
    addSeatIntoBookingData(se, userId, ch);
    
    return 0;
}  // Complete

void addSeatIntoBookingData(char seatNo[], char *userId,int ch){
    int index = -1;
    for(int i=0; i < bookingDataLength; i++)
    {
        if(strcmp(bookingData[i].userId, userId) == 0)
        {
            index = i;
            break;
        }
    }
    if(index == -1) // If No Data Available Then Add
    {
        index = bookingDataLength;
        strcpy(bookingData[index].userId, userId);
        
        if(ch == 1) // Mumbai to Ahmedabad
        {
            strcat(bookingData[index].seatNumbers, "MA");
            strcat(bookingData[index].seatNumbers, seatNo);
        }
        else
        {
            strcat(bookingData[index].seatNumbers, "AM");
            strcat(bookingData[index].seatNumbers, seatNo);
        }
        strcat(bookingData[index].seatNumbers, ",");
        bookingDataLength++;
    }
    else
    {    if(ch == 1) // Mumbai to Ahmedabad
        {
            strcat(bookingData[index].seatNumbers, "MA");
            strcat(bookingData[index].seatNumbers, seatNo);
        }
        else
        {
            strcat(bookingData[index].seatNumbers, "AM");
            strcat(bookingData[index].seatNumbers, seatNo);
        }
        strcat(bookingData[index].seatNumbers, ",");
    }
    FILE *fp = fopen("bookingData.txt", "w");
    for(int i=0; i<bookingDataLength; i++)
    {   
        fputs(bookingData[i].userId, fp);
        fputc('|', fp);
        fputs(bookingData[i].seatNumbers, fp);
        fputc('\n', fp);
    }
    fclose(fp);
}

/*
    int ticketingInterface(void)
            This Function Shows Menu/Interface For Booking Ticket.
    Arguments : No Arguments
    Returns : Void
*/
int ticketingInterface(char *userId){
    int ch;
    displayRoutes();
    printf("\n\tChoose Where you want to travel?");
    printf("\n\tEnter :");
    printf("\n\t\t1- Mumbai to Ahmedabad");
    printf("\n\t\t2- Ahmedabad to Mumbai");
    printf("\n\t\t0- Exit");
    
    char a[12]={'A','B','C','D','E','F','G','H','I'};
    
    int whileIsTrue = 1;
    while(whileIsTrue)
    {    
        printf("\n\tChoice : ");
        scanf(" %d", &ch);
        if(ch==1) // Mumbai to Ahmedabad
        {
            for(int i=0; i< 9; i++)
                printf("\t %-13s(%c) -\n", busStopNames[i], a[i]);
            break;
        }
        else if(ch==2) // Ahmedabad to Mumbai
        {
            for(int i=0; i<9; i++)
                printf("\t %-13s(%c) -\n", busStopNames[8-i], a[i]);
            break;
        }
        else if(ch==0)
            return 0;
        else
            printf("\tInvalid Choise Entered : Please Re-Enter");
    }
    char startPoint = '\0';
    char endPoint = '\0';
    int temp=1, temp2=1, temp3=1,temp4=1;
    while(temp)
    {
        printf("\n\tEnter Start Point : ");
        scanf(" %c", &startPoint);
        temp = validate(startPoint);
    }
    while(temp2)
    {
        printf("\n\tEnter End Point : ");
        scanf(" %c", &endPoint);
        temp2 = validatechar(startPoint, endPoint);
    }
    char seatNo[5];
    // Displaying Bus Structure/Design which shows how many seats are 
    // booked and from what points they are booked.
    showBusStructure(ch);
    while(temp4)
    {
        printf("\n\tEnter Seat Number (e.g S0R1 or S3R3) : ");
        scanf(" %s", seatNo);
        temp3=validateticket(seatNo);
        if(temp3==0)
        {
            temp4= bookTicket(seatNo, userId, startPoint, endPoint, ch);
            
        }
    }
    
    //bookTicket(seatNo, userId, startPoint, endPoint, ch);
    return EXIT_SUCCESS;
} // Complete

// ----------------------------------------------------------------[ Menu Page ]
int showRegistrationPage(char *userId)
{
    int whileIsTrue = 1;
    while(whileIsTrue)
    {
        printf("\n\tEnter Following To :");
        printf("\n\t\t1. Display Routes");
        printf("\n\t\t2. Display Price Table");
        printf("\n\t\t3. Display Number Of Booked Tickets");
        printf("\n\t\t4. Book Ticket");
        printf("\n\t\t5. Show My Booking");
        printf("\n\t\t6. Go Back To Home Page");
        printf("\n\t\t0. Save And Exit\n\tChoice : ");
        scanf(" %d", &whileIsTrue);
        //-------------------------------
        if(whileIsTrue == 1)
        {
            displayRoutes(); // Complete
        }
        else if(whileIsTrue == 2)
        {
            displayRoutePriceTable(); // Complete
        }
        else if(whileIsTrue == 3)
        {
            displayNumberOfBookedTickets(); // Complete
        }
        else if(whileIsTrue == 4)
        {
            ticketingInterface(userId); // Complete
        }
        else if(whileIsTrue == 5) // Show Current User Booking
        {
            displayMyBooking(userId);
        }
        else if(whileIsTrue == 6) // Save And EXIT
        {
            return 1;
        }
    }
    return EXIT_SUCCESS;
}

// -----------------------------------------------------[ Validation Function  ]
int validate(char a)
{
    if(a>='A' && a<'I')
    {
        return 0;
    }
    else
    {
        printf("\n\tPlease choose your valid Start Point from 'A' to 'H'!\n");
        return 1;
    }
}

int validatechar(char a,char b)
{
    if(b>='B' && b<='I' && a<b)
        return 0;
    else
    {
        printf("\n\tPlease choose your valid Stop Point from '%c' to 'H'!\n", a+1);
        return 1;
    }
}

int validateticket(char d[])
{
    int c1=(int) d[1]-48;
    int c2=(int) d[3]-48;
    
    if((d[0]=='S') && (c1 >= 0 && c1<4) && (d[2]=='R') && (c2>=0 && c2<=9) && strlen(d)<=4)
    {
        return 0;
    }
    else
    {
        printf("\n\tPlease Enter valid Ticket Number!\n");
        return 1;
        
    }
}




