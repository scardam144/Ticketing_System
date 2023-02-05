#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma once


struct user
{
  char name[80];
  char email[80];
  char password[40];
};

struct busBookingData
{
    char userId[80];
    char seatNumbers[100];
};

// Login.c function
int loginFunc(char *userId);                                        // Complete
int checkemail(char *email);                            // Complete
int checkpassword(char *password, int row);             // Complete
int registerFunc();                                     // Complete
int showWelcomePage(char *userId);                                  // Complete
void loadUserData();                                    // Complete
                                                        
                                                        
// bookTicket.c function                                
int showRegistrationPage(char *userId);                             // Complete
void showBusStructure(int index);                       // Incomplete
void displayRoutes();                                   // Complete
void displayRoutePriceTable();                          // Complete
void displayNumberOfBookedTickets();                    // Complete
void loadBusBookingDataIntoGlobalVariables();           // Complete
int bookTicket(char se[],char *userId, char startPoint, char endPoint, int ch);  // Complete
int validate(char ch);
int validateticket(char c[]);
int validatechar(char startPoint, char endPoint);
int printTicket(char sp, char ep, char ticket[], int busFare,int ch);
void addSeatIntoBookingData(char seatNo[], char *userId,int ch);