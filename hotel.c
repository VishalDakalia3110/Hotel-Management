#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *conn;
void finish_with_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}
void AddVisitor(MYSQL *conn);
void UpdateVisitor(MYSQL *conn);
void RemoveVisitor(MYSQL *conn);
void SearchVisitor(MYSQL *conn);
void ShowVisitor(MYSQL *conn);
void ShowRoom(MYSQL *conn);
void AddRoom(MYSQL *conn);
void UpdateRoom(MYSQL *conn);
void SearchRoom(MYSQL *conn);
void RemoveRoom(MYSQL *conn);

void Rooms(MYSQL *conn);
void Booking(MYSQL *conn);
void Customer_Details(MYSQL *conn);

void MainMenu(MYSQL *conn);
int main() {
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
			//	booking(conn);
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
void ShowVisitor(MYSQL *conn) {
    // Execute the query to retrieve all visitors
    if (mysql_query(conn, "SELECT * FROM Hotel_Visitors")) {
        finish_with_error(conn);
    }

    // Store the result of the query
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        finish_with_error(conn);
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    // Check if there are any rows in the result
    if ((row = mysql_fetch_row(result)) == NULL) {
        printf("No Records...\n");
        mysql_free_result(result); // Free result before returning
        return;
    }

    // Print the column names
    MYSQL_FIELD *field;
    mysql_field_seek(result, 0); // Ensure the field pointer is reset to the start
    while ((field = mysql_fetch_field(result))) {
        printf("%s\t", field->name); // Use tabs for better formatting
    }
    printf("\n");

    // Print the first row (already fetched above)
    do {
        for (int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    } while ((row = mysql_fetch_row(result))); // Fetch the remaining rows

    mysql_free_result(result);
}


void AddVisitor(MYSQL *conn) {
    printf("Adding Visitor...\n");
    int ID;
    
    while (1) {
        printf("Enter Visitor ID: ");
        scanf("%d", &ID);
        
        char query[256];
        snprintf(query, sizeof(query), "SELECT * FROM Hotel_Visitors WHERE ID=%d", ID);
        
        if (mysql_query(conn, query)) {
            finish_with_error(conn);
        }
        
        MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            finish_with_error(conn);
        }

        if (mysql_num_rows(result) > 0) {
            printf("ID Already exists..\n");
        } else {
            mysql_free_result(result);
            break;
        }
        
        mysql_free_result(result);
    }
    
    printf("ID %d is available. Proceeding...\n", ID);
    char name[100];
    long int mobile;
    printf("Please Enter Your Name --> ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  // Remove the newline character from the input

    printf("Enter your Mobile No. --> ");
    scanf("%ld", &mobile);
    printf("\nIdentification types are:\n");
    printf("     1. Aadhar Card\n");
    printf("     2. Passport\n");
    printf("     3. PAN Card\n");
    printf("     4. Driving Licence\n");
    char idtype[100];
    int ID_Proof;
    while (1) {
        printf("Please select an Identification type (1-4) --> ");
        scanf("%d", &ID_Proof);

        if (ID_Proof < 1 || ID_Proof > 4) {
            printf("Sorry, But enter a valid option -->\n");
        } else {
            if (ID_Proof == 1) {
                strcpy(idtype, "Aadhar Card");
            } else if (ID_Proof == 2) {
                strcpy(idtype, "Passport");
            } else if (ID_Proof == 3) {
                strcpy(idtype, "PAN Card");
            } else if (ID_Proof == 4) {
                strcpy(idtype, "Driving Licence");
            }
            break;
        }
    }
    int ID_no,Nationality;
    char ntype[100];
    char City[100];
    printf("Please Enter your ID Number --> ");
    scanf("%d", &ID_no);

    printf("\nWhich type of nationality do you have:\n");
    printf("     1. Indian\n");
    printf("     2. Foreigner\n");

    while (1) {
        printf("Please select Nationality (1 for Indian, 2 for Foreigner) --> ");
        scanf("%d", &Nationality);

        if (Nationality < 1 || Nationality > 2) {
            printf("Sorry, But Please enter a valid option!\n");
        } else {
            if (Nationality == 1) {
                strcpy(ntype, "Indian");
            } else if (Nationality == 2) {
                strcpy(ntype, "Foreigner");
            }
            break;
        }
    }
    printf("Please Enter your Belonging City Name --> ");
    scanf("%s", City);
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO Hotel_Visitors (ID,Name, Mobile_no, ID_Proof, ID_no, Nationality, City) "
                                   "VALUES ('%d','%s', '%ld', '%s', '%d', '%s', '%s')",
             ID,name, mobile, idtype, ID_no, ntype, City);

    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    mysql_commit(conn);
    printf("Guest Added Successfully...\n");
}

void UpdateVisitor(MYSQL *conn) {
	printf("Enter The id of the visitor You want to update :- ");
	int ID;
	while(true) {
		scanf("%d",&ID);
		char query[256];
        	snprintf(query, sizeof(query), "SELECT * FROM Hotel_Visitors WHERE ID=%d", ID);
		if (mysql_query(conn, query)) {
         	   finish_with_error(conn);
        	}
        	MYSQL_RES *result = mysql_store_result(conn);
        	if (result == NULL) {
			finish_with_error(conn);
        	}

       		if (mysql_num_rows(result) != 1) {
        	    printf("Invaild ID Enter Again :- ");
		    scanf("%d",&ID);
        	}
	       	else break;
	}
	char name[100];
    long int mobile;
    printf("Please Enter Your Name --> ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  // Remove the newline character from the input

    printf("Enter your Mobile No. --> ");
    scanf("%ld", &mobile);
    printf("\nIdentification types are:\n");
    printf("     1. Aadhar Card\n");
    printf("     2. Passport\n");
    printf("     3. PAN Card\n");
    printf("     4. Driving Licence\n");
    char idtype[100];
    int ID_Proof;
    while (1) {
        printf("Please select an Identification type (1-4) --> ");
        scanf("%d", &ID_Proof);

        if (ID_Proof < 1 || ID_Proof > 4) {
            printf("Sorry, But enter a valid option -->\n");
        } else {
            if (ID_Proof == 1) {
                strcpy(idtype, "Aadhar Card");
            } else if (ID_Proof == 2) {
                strcpy(idtype, "Passport");
            } else if (ID_Proof == 3) {
                strcpy(idtype, "PAN Card");
            } else if (ID_Proof == 4) {
                strcpy(idtype, "Driving Licence");
            }
            break;
        }
    }
     int ID_no,Nationality;
    char ntype[100];
    char City[100];
    printf("Please Enter your ID Number --> ");
    scanf("%d", &ID_no);

    printf("\nWhich type of nationality do you have:\n");
    printf("     1. Indian\n");
    printf("     2. Foreigner\n");

    while (1) {
        printf("Please select Nationality (1 for Indian, 2 for Foreigner) --> ");
        scanf("%d", &Nationality);

        if (Nationality < 1 || Nationality > 2) {
            printf("Sorry, But Please enter a valid option!\n");
        } else {
            if (Nationality == 1) {
                strcpy(ntype, "Indian");
            } else if (Nationality == 2) {
                strcpy(ntype, "Foreigner");
            }
            break;
        }
    }
    printf("Please Enter your Belonging City Name --> ");
    scanf("%s", City);
    char query[512];
snprintf(query, sizeof(query), "UPDATE Hotel_Visitors SET Name='%s', Mobile_no=%ld, ID_Proof='%s', ID_no=%d, Nationality='%s', City='%s' WHERE ID=%d",name, mobile, idtype, ID_no, ntype, City, ID);
    if(mysql_query(conn,query)) finish_with_error(conn);

    if(mysql_commit(conn)) finish_with_error(conn);

    printf("Updated Successfully...\n");

}

void RemoveVisitor(MYSQL *conn) {
	printf("Enter The id of the visitor You want to delete :- ");
        int ID;
	char query[256];
        while(true) {
                scanf("%d",&ID);
                snprintf(query, sizeof(query), "SELECT * FROM Hotel_Visitors WHERE ID=%d", ID);
                if (mysql_query(conn, query)) {
                   finish_with_error(conn);
                }
                MYSQL_RES *result = mysql_store_result(conn);
                if (result == NULL) {
                        printf("Siuuuu\n");
                        finish_with_error(conn);
                }

                if (mysql_num_rows(result) != 1) {
                    printf("Invaild ID Enter Again :- ");
                    scanf("%d",&ID);
                }
                else break;
        }
	snprintf(query, sizeof(query), "DELETE FROM Hotel_Visitors WHERE ID=%d", ID);
    	if(mysql_query(conn,query)) finish_with_error(conn);

    	if(mysql_commit(conn)) finish_with_error(conn);

    	printf("Guest Removed Successfully...\n");
	

}
void SearchVisitor(MYSQL *conn) {
	char query[256] = "SELECT * from Hotel_Visitors";
	if(mysql_query(conn,query)) finish_with_error(conn);
	MYSQL_RES *result;
	result = mysql_store_result(conn);
	if(result == NULL) finish_with_error(conn);
	MYSQL_ROW row;

    // Check if there are any rows in the result
    	if ((row = mysql_fetch_row(result)) == NULL) {
        	printf("No Records...\n");
        	mysql_free_result(result); // Free result before returning
        	return;
	}
	printf("Searching for Guest...\n");
	int ID;
	while(true) {
		printf("Enter ID of the Guest you want Search :- ");
		scanf("%d",&ID);
		snprintf(query, sizeof(query), "SELECT * FROM Hotel_Visitors WHERE ID=%d", ID);
		if (mysql_query(conn, query)) {
    		    finish_with_error(conn);
    		}
		result = mysql_store_result(conn);
    		if (result == NULL) {
        	    finish_with_error(conn);
    		}
		int num_rows = mysql_num_rows(result);
		if(num_rows >= 1) {
			int num_fields = mysql_num_fields(result);
        		MYSQL_FIELD *field;

        		// Print the column names
        		while ((field = mysql_fetch_field(result))) {
            			printf("%-15s", field->name);  // Adjust the width as necessary
        		}
        		printf("\n");

        		// Print the visitor details
        		while ((row = mysql_fetch_row(result))) {
            		for (int i = 0; i < num_fields; i++) {
                		printf("%-15s", row[i] ? row[i] : "NULL");  // Adjust the width as necessary
            		}
            		printf("\n");
			}
			break;	
		}
		else {
		    printf("No Guest Found...\n");
		    break;
		}
	}
	mysql_free_result(result);
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
                       // SearchRoom(conn);
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

void ShowRoom(MYSQL *conn) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[256];

    // Construct the query to fetch room details
    snprintf(query, sizeof(query), "SELECT * FROM Room_Details");

    // Execute the query
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    // Store the result
    result = mysql_store_result(conn);
    if (result == NULL) {
        finish_with_error(conn);
    }

    int num_rows = mysql_num_rows(result);
    printf("Room Details are...\n");
    if (num_rows == 0) {
        printf("No Guest Records Available.\n");
    }
    else {
        int num_fields = mysql_num_fields(result);
        MYSQL_FIELD *field;

        // Print the column names
        while ((field = mysql_fetch_field(result))) {
            printf("%-15s", field->name);  // Adjust the width as necessary
        }
        printf("\n");

        // Print the room details
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < num_fields; i++) {
                printf("%-15s", row[i] ? row[i] : "NULL");  // Adjust the width as necessary
            }
            printf("\n");
        }
    }


    // Free the result
    mysql_free_result(result);
}


void AddRoom(MYSQL *conn) {
    int R_no;
    int R_type;
    char rtype[50];
    int Charges;

    
    printf("Adding Room...\n");
    char query[256];
	
    while (1) {
        printf("Room No --> ");
        scanf("%d", &R_no);

        snprintf(query, sizeof(query), "SELECT * FROM Room_Details WHERE R_no=%d", R_no);

        if (mysql_query(conn, query)) {
            finish_with_error(conn);
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            finish_with_error(conn);
        }

        int cnt = mysql_num_rows(result);

        if (cnt >= 1) {
            printf("Room No. %d is already exist...\n", R_no);
            mysql_free_result(result);
        } else {
            mysql_free_result(result);
            break;
        }
    }

    printf("\nRoom types are:\n");
    printf("     1. Single Room (Charges(per day) = Rs. 1500)\n");
    printf("     2. Double Room (Charges(per day) = Rs. 2500)\n");
    printf("     3. Family Room (Charges(per day) = Rs. 3000)\n");
    printf("     4. Duplex Room (Charges(per day) = Rs. 5500)\n");
    printf("     5. Conference Room (Charges(per day) = Rs. 8500)\n");
    printf("     6. Inter-Connecting Room (Charges(per day) = Rs. 6000)\n");
    printf("\n");

    while (1) {
        printf("Choose any Room type: ");
        scanf("%d", &R_type);

        if (R_type <= 0 || R_type >= 7) {
            printf("Invalid input, Please select valid input...\n");
        } else {
            switch (R_type) {
                case 1:
                    strcpy(rtype, "Single Room");
                    Charges = 1500;
                    break;
                case 2:
                    strcpy(rtype, "Double Room");
                    Charges = 2500;
                    break;
                case 3:
                    strcpy(rtype, "Family Room");
                    Charges = 3000;
                    break;
                case 4:
                    strcpy(rtype, "Duplex Room");
                    Charges = 5500;
                    break;
                case 5:
                    strcpy(rtype, "Conference Room");
                    Charges = 8500;
                    break;
                case 6:
                    strcpy(rtype, "Inter-Connecting Room");
                    Charges = 6000;
                    break;
            }
            break;
        }
    }

    // Insert the new room into the database
    snprintf(query, sizeof(query), "INSERT INTO Room_Details (R_no, R_type, Charges, Vacancy) VALUES (%d, '%s', %d, 'Vacant')", R_no, rtype, Charges);

    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    printf("\nRoom Add Successfully...\n");
    
}
void UpdateRoom(MYSQL *conn) {
    char query[256] = "SELECT * from Room_Details";
    MYSQL_RES *result;
    if(mysql_query(conn, query)) finish_with_error(conn);
    result = mysql_store_result(conn);
    if(result == NULL) finish_with_error(conn);
    int row = mysql_num_rows(result);
    mysql_free_result(result);
    int R_no,Charges,R_type;
    char rtype[50];
    if(row == 0) {
	printf("No Room Available to update...\n");
	return;
    }
    else {
    	printf("Updating Room...\n");
	printf("Enter Room Number You want to update :- ");
	scanf("%d",&R_no);
	while(true) {
		snprintf(query, sizeof(query), "SELECT * from Room_Details where R_no=%d", R_no);
		if(mysql_query(conn, query)) finish_with_error(conn);
		result = mysql_store_result(conn);
		if(result == NULL) finish_with_error(conn);
		row = mysql_num_rows(result);
		mysql_free_result(result);
		if(row == 0) {
		    printf("Invalid Room Number Enter Again :- ");
		    scanf("%d",&R_no);
		}
		else break;
    	}
	
    }
    printf("\nRoom types are:\n");
    printf("     1. Single Room (Charges(per day) = Rs. 1500)\n");
    printf("     2. Double Room (Charges(per day) = Rs. 2500)\n");
    printf("     3. Family Room (Charges(per day) = Rs. 3000)\n");
    printf("     4. Duplex Room (Charges(per day) = Rs. 5500)\n");
    printf("     5. Conference Room (Charges(per day) = Rs. 8500)\n");
    printf("     6. Inter-Connecting Room (Charges(per day) = Rs. 6000)\n");
    while(true) {
        printf("Choose any Room Type :- ");
	scanf("%d",&R_type);
	if (R_type <= 0 || R_type >= 7) {
            printf("Invalid input, Please select valid input :- ");
        } else {
            if (R_type == 1) {
                strcpy(rtype, "Single Room");
                Charges = 1500;
            } else if (R_type == 2) {
                strcpy(rtype, "Double Room");
                Charges = 2500;
            } else if (R_type == 3) {
                strcpy(rtype, "Family Room");
                Charges = 3000;
            } else if (R_type == 4) {
                strcpy(rtype, "Duplex Room");
                Charges = 5500;
            } else if (R_type == 5) {
                strcpy(rtype, "Conference Room");
                Charges = 8500;
            } else if (R_type == 6) {
                strcpy(rtype, "Inter-Connecting Room");
                Charges = 6000;
            }
	    printf("Siuuu");
            break;
        }

    }
    snprintf(query, sizeof(query), "UPDATE Room_Details set R_type='%s', Charges=%d where R_no=%d", rtype, Charges, R_no);
    if(mysql_query(conn, query)) finish_with_error(conn);
    printf("Room Updated Successfully...\n");

}

void RemoveRoom(MYSQL *conn) {
    char query[256] = "SELECT * from Room_Details";
    if(mysql_query(conn, query)) finish_with_error(conn);
    MYSQL_RES *result;
    int row;
    result = mysql_store_result(conn);
    if(result == NULL) finish_with_error(conn);
    row = mysql_num_rows(result);
    mysql_free_result(result);
    if(row == 0) {
        printf("No Room is Available to Remove\n");
       return;	
    }
    int R_no;
    while(true) {
        printf("Enter Room Number you want to remove :- ");
	scanf("%d",&R_no);
	snprintf(query, sizeof(query), "SELECT * from Room_Details where R_no=%d", R_no);
	if(mysql_query(conn, query)) finish_with_error(conn);
	result = mysql_store_result(conn);
	if(result == NULL) finish_with_error(conn);
	row = mysql_num_rows(result);
	if(row == 0) {
	    printf("Enter Valid room number\n");
	}
	else {
	    snprintf(query, sizeof(query), "DELETE from Room_Details where R_no=%d", R_no);
	    if(mysql_query(conn, query)) finish_with_error(conn);
	    printf("Room Removed Successfully...\n");
	    break;
	}

    }
}

