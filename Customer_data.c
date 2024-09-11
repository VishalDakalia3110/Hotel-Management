#include <mysql/mysql.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void finish_with_error(MYSQL *conn);

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
