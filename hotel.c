#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "Hotel_Management.h"


void finish_with_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

void Rooms(MYSQL *conn);
void booking(MYSQL *conn);
void Customer_Details(MYSQL *conn);

void MainMenu(MYSQL *conn);

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "0", "hotel", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }
    else {
	    printf("Connected SuccessFully...");
    }
	MainMenu(conn);
	return 0;
}

void MainMenu(MYSQL *conn ){ 
	printf("Welcome to Our Hotel :- \n\n");
	printf("\t1. Customer Details\n");
	printf("\t2. Room Details\n");
	printf("\t3. Booking of Room\n");
	printf("\t4. Exit\n\n");
	printf("Enter your Choice :- ");
	int choice;
	scanf("%d",&choice);
	int temp = 1;
		switch (choice) {
			case 1:
				Customer_Details(conn);
				break;
			case 2:
				Rooms(conn);
				break;
			case 3:
				booking(conn);
				break;
			case 4:
				temp = 0;
				printf("Thank You For Visiting....");
				exit(0);
				break;
			default:
				printf("Enter Valid Choice :- ");
				scanf("%d",&choice);
		}
	return;
}

void Customer_Details(MYSQL *conn) {
	while(true) {
	int choice;
	printf("Customer details :-\n\n");
	printf("\t1. Show Visitor\n");
	printf("\t2. Add Visitor\n");
	printf("\t3. Update Visitor\n");
	printf("\t4. Remove Visitor\n");
	printf("\t5. Search for Visitor\n");
	printf("\t6. Back to ManiMenu(<<)\n\n");
	printf("Enter any option from the above :- ");
	scanf("%d",&choice);
	switch (choice) {
		case 1:
			ShowVisitor(conn);
			break;
		case 2:
			AddVisitor(conn);
			break;
		case 3:
			UpdateVisitor(conn);
			break;
		case 4:
			RemoveVisitor(conn);
			break;
		case 5:
			SearchVisitor(conn);
			break;
		case 6:
			MainMenu(conn);
			break;
		default:
			//Customer_Details(conn);
			printf("Invalid Input...");
	}
	}
	return;
}

void Rooms(MYSQL *conn) {
        while(true) {
        int choice;
        printf("Room details :-\n\n");
        printf("\t1. Show Rooms\n");
        printf("\t2. Add Rooms\n");
        printf("\t3. Update Rooms\n");
        printf("\t4. Remove Rooms\n");
        printf("\t5. Search for Room\n");
        printf("\t6. Back to ManiMenu(<<)\n\n");
        printf("Enter any option from the above :- ");
        scanf("%d",&choice);
        switch (choice) {
                case 1:
                        ShowRoom(conn);
                        break;
                case 2:
                        AddRoom(conn);
                        break;
                case 3:
                        UpdateRoom(conn);
                        break;
                case 4:
                        RemoveRoom(conn);
                        break;
                case 5:
                        //SearchRoom(conn);
                        break;
                case 6:
                        MainMenu(conn);
                        break;
                default:
                        //Customer_Details(conn);
                        printf("Invalid Input...");
        }
        }
        return;
}

void booking(MYSQL *conn) {
    while(true) {
    	int choice;
	printf("Booking Options are :-\n\n");
	printf("\t1. Show current booking\n");
	printf("\t2. Show previous booking\n");
	printf("\t3. Booking of a Room\n");
	printf("\t4. Generate Bill\n");
	printf("\t5. Back to Mainmenu<<\n\n");
	printf("Enter your choice :- ");
	scanf("%d",&choice);
	switch (choice) {
	    case 1:
		    ShowCurrentBooking(conn);
		    break;
	    case 2:
		    ShowPreviousBooking(conn);
		    break;
	    case 3:
		    BookRoom(conn);
		    break;
	    case 4:
		    Bill(conn);
		    printf("Thank you for Visiting...\n");
		    exit(0);
		    break;
	    case 5:
		    MainMenu(conn);
		    break;
	    default:
		    printf("Invalid Input...\n");
	}
    }
}


































