#include "allFunctions.h"

struct user userDataArray[100];
int userDataLength = 0;
struct user user1;

void loadUserData()
{
    FILE *fp = fopen("userData.txt", "r");
    char line[200];
    int row = 0;
    while(fgets(line,200,fp))
    {
        char *tok = strtok(line, ",");
        int col = 0;
        while(tok)
        {
            if(col == 0)
                strcpy(userDataArray[row].name, tok);
            if(col == 1)
                strcpy(userDataArray[row].email, tok);
            if(col == 2)
                strcpy(userDataArray[row].password, tok);
            
            int lastIndex = (int) strlen(userDataArray[row].password);
            lastIndex = lastIndex - 1;
            userDataArray[row].password[lastIndex] = '\0';
                
            col = col + 1;
            tok = strtok(NULL, ",");
        }
        row = row + 1;
        userDataLength = userDataLength + 1;
    }
    fclose(fp);
    return;
}

int registerFunc()
{
    printf("\tEnter User Name\n\t\t: ");
    scanf(" %s", user1.name);
    
    printf("\tEnter User Email\n\t\t: ");
    scanf(" %s", user1.email);
    
    printf("\tEnter Password\n\t\t: ");
    scanf(" %s", user1.password);
    char reCheckPassword[40];
    int whileIsTrue = 1;
    while(whileIsTrue)
    {    
        printf("\tRe-Enter Password\n\t\t: ");
        scanf(" %s", reCheckPassword);
        whileIsTrue = strcmp(reCheckPassword, user1.password);
        if( whileIsTrue != 0)
        {   
            printf("\t! Password Didn't Matched To The Previously Entered Password\n");
            int yesorno;
            printf("\tEnter 0 - Exit\n\t\t1 - Retry\n\tChoice : ");
            scanf("%d", &yesorno);
            if(yesorno == 0)
                return 0;
        }
    }
    
    printf("\n\t--------------------------------------------\n\tUser Name : %s\n\tUser Email : %s\n\tUser Password : %c**%c**", user1.name, user1.email, user1.password[0], user1.password[3]);
    
    // Saving/Storing Data into userData.txt file.
    FILE *fp = fopen("userData.txt", "a");
    fputs(user1.name, fp);
    fputc(',', fp);
    fputs(user1.email, fp);
    fputc(',', fp);
    fputs(user1.password, fp);
    fputc('\n', fp);
    fclose(fp);
    
    return 1;
}

int loginFunc(char *userId)
{
    loadUserData(); // This will load the the Previously stored data into the userDataArray 
    
    int whileIsTrue = 1;
    char email[80], password[40];
    int row = 0; // row will be password to checkpassword() to avoid looping through userDataArray elements
    printf("\tEnter Email\n\t\t: ");
    while(whileIsTrue)
    {
        scanf(" %s", email);
        row = checkemail(email);  //(checkemail(email) == -1) // If User Email Not Valid
        if( row == -1) 
        {
            printf("\t! Invalid User Email\n");
            char yn;
            printf("\tWant to retry ?[Y,y/N,n] : ");
            int internalWhileIsTrue = 1;
            while(internalWhileIsTrue)
            {
                scanf(" %c", &yn);
                if(yn == 'n' || yn == 'N')
                {
                    return 1;
                }
                else if(yn == 'y' || yn == 'Y')
                {
                    printf("\n\tRe-Enter Email\n\t\t: ");
                    internalWhileIsTrue = 0;
                }
                else
                {
                    printf("\n\tEnter Valid Choice [Y,y/N,n] : ");
                }
            }
            continue;
        }
        break;
    }
    printf("\tEnter Password\n\t\t: ");
    while(whileIsTrue)
    {
        scanf(" %s", password);
        if(checkpassword(password, row) != 0) // If User Password Not Valid
        {
            printf("\n\t! Invalid Password\n");
            char yn;
            printf("\tWant to retry ?[Y,y/N,n] : ");
            int internalWhileIsTrue = 1;
            while(internalWhileIsTrue)
            {
                scanf(" %c", &yn);
                if(yn == 'n' || yn == 'N')
                {
                    return 1;
                }
                else if(yn == 'y' || yn == 'Y')
                {
                    printf("\n\tRe-Enter Password\n\t\t: ");
                    internalWhileIsTrue = 0;
                }
                else
                {
                    printf("\n\tEnter Valid Choice [Y,y/N,n] : ");
                }
            }
            continue;
        }
        printf("\n\tLogin Successful \n");
        strcpy(userId, email);
        return 1;
    }
    return 1;
}

int checkemail(char *email)
{
    int row = 0;
    while(row < userDataLength)
    {
        if(strcmp(userDataArray[row].email, email) == 0)
        {
            return row; // return row index for next password checking
        }
        row = row + 1;
    }
    return -1;
}

int checkpassword(char *password, int row)
{
    // int lastIndex = (int) strlen(userDataArray[row].password);
    // lastIndex = lastIndex - 1;
    // userDataArray[row].password[lastIndex] = '\0';
    // printf("\n[%s != %s]\n", password, userDataArray[row].password);
    if(strcmp(userDataArray[row].password, password) == 0)
    {
        return 0;
    }
    return 1;
}

int showWelcomePage(char *userId)
{
    printf("\n\tWelcome to Bharat Bus pvt.ltd\n\t");
    int choiceLogOrRegis = 1;
    while(choiceLogOrRegis)
    {   
        printf("\n\t\tEnter 1 For Login\n\t");
        printf("\tEnter 2 For Registration\n\t");
        printf("\tEnter 0 For Save and Exit\n\tChoice : ");
        scanf("%d", &choiceLogOrRegis);
        if(choiceLogOrRegis == 1)
        {
            choiceLogOrRegis = loginFunc(userId);
            printf("-------------------------------\n");
            if(choiceLogOrRegis == 1)
                return 2;
        }
        else if(choiceLogOrRegis == 2)
        {
            choiceLogOrRegis = registerFunc();
            if(choiceLogOrRegis != 0)
                printf("\n\tRegistration Successful\n");
            else
            {   
                printf("\n\tRegistration UnSuccessful");
                choiceLogOrRegis = 1;
            }
        }
        else if (choiceLogOrRegis > 2 || choiceLogOrRegis < 0)
        {
            printf("\tInvalid Input Please Re-Enter Choice :");
            choiceLogOrRegis = 1;
        }
        else if( choiceLogOrRegis == 0)
            return 0;
    }
    return EXIT_SUCCESS;
}
