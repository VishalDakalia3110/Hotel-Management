#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *conn);


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
