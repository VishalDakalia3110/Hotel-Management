#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>


void finish_with_error(MYSQL *conn);

void ShowCurrentBooking(MYSQL *conn) {
   printf("Current Bookings are :-\n");
   char query[256] = "SELECT * from Booking";
   if(mysql_query(conn, query)) finish_with_error(conn);
   MYSQL_RES *result;
   result = mysql_store_result(conn);
   if(result == NULL) finish_with_error(conn);
   int num_rows = mysql_num_rows(result);
   if(num_rows == 0) printf("No Bookings are present...\n");
   else {
   	int num_fields = mysql_num_fields(result);                                                                                                            MYSQL_FIELD *field;
	MYSQL_ROW row;
	while ((field = mysql_fetch_field(result))) {                                                                                                             printf("%-15s", field->name);
	}
	printf("\n");
	 while ((row = mysql_fetch_row(result))) {                                                                                                                 for (int i = 0; i < num_fields; i++) {                                                                                                                    printf("%-15s", row[i] ? row[i] : "NULL");  
	 }                                                                                                                                                     printf("\n");                                                                                                                                     }
	
   }
    
}
void ShowPreviousBooking(MYSQL *conn) {
   printf("Previous Bookings are :-\n");
   char query[256] = "SELECT * from Billing";
   if(mysql_query(conn, query)) finish_with_error(conn);
   MYSQL_RES *result;
   result = mysql_store_result(conn);
   if(result == NULL) finish_with_error(conn);
   int num_rows = mysql_num_rows(result);
   if(num_rows == 0) printf("No Bookings are present...\n");
   else {
        int num_fields = mysql_num_fields(result);                                                                                                            MYSQL_FIELD *field;
        MYSQL_ROW row;
        while ((field = mysql_fetch_field(result))) {                                                                                                             printf("%-15s", field->name);
        }                                                                                                                                                     printf("\n");
         while ((row = mysql_fetch_row(result))) {                                                                                                                 for (int i = 0; i < num_fields; i++) {                                                                                                                    printf("%-15s", row[i] ? row[i] : "NULL");
         }                                                                                                                                                     printf("\n");                                                                                                                                     }
                                                                                                                                                         }
}


void BookRoom(MYSQL *conn) {
    printf("Booking Room...\n");
    int BID, R_no, ID;
    char Enroll_Date[20];

    printf("Enter Booking ID :- ");
    scanf("%d", &BID);

    // Check if Booking ID exists
    while (1) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT * FROM Booking WHERE BID=%d", BID);

        if (mysql_query(conn, query)) {
            finish_with_error(conn);
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            finish_with_error(conn);
        }

        int cnt = mysql_num_rows(result);
        mysql_free_result(result);

        if (cnt >= 1) {
            printf("Booking ID %d already exists...\n", BID);
            printf("Again Enter Booking ID > ");
            scanf("%d", &BID);
        } else {
            break;
        }
    }
    printf("Checking for Availablity of Rooms...\n");
    if (mysql_query(conn, "SELECT R_no, R_type FROM Room_Details WHERE Vacancy LIKE '%Vacant%' ORDER BY R_no")) {
        finish_with_error(conn);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        finish_with_error(conn);
    }

    int cnt = mysql_num_rows(result);
    if (cnt == 0) {
        printf("No Rooms are Available...\n");
    } else {
        printf("Available Rooms are :-\n");

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            printf("Room No: %s, Room Type: %s\n", row[0], row[1]);
        }
        printf("\n");
    }
    mysql_free_result(result);
    printf("Enter Room Number :- ");
    scanf("%d", &R_no);
    while (true) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT * FROM Room_Details WHERE R_no=%d", R_no);
        mysql_query(conn, query);

        result = mysql_store_result(conn);
        cnt = mysql_num_rows(result);
        mysql_free_result(result);

        if (cnt == 0) {
            printf("Room No. %d does not exist...\n", R_no);
            printf("Again Enter Room No :- ");
            scanf("%d", &R_no);
        }
	else {
            snprintf(query, sizeof(query), "SELECT * FROM Room_Details WHERE Vacancy LIKE '%%Booked%%' AND R_no=%d", R_no);
            mysql_query(conn, query);

            result = mysql_store_result(conn);
            cnt = mysql_num_rows(result);
            mysql_free_result(result);

            if (cnt >= 1) {
                printf("Room No. %d is already booked...\n", R_no);
                printf("Again Enter Room No :- ");
                scanf("%d", &R_no);
            } 
	    else {
                break;
            }
        }
    }
    printf("Guest ID :- ");
    scanf("%d", &ID);

    while (true) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT * FROM Hotel_Visitors WHERE ID=%d", ID);
        mysql_query(conn, query);

        result = mysql_store_result(conn);
        cnt = mysql_num_rows(result);
        mysql_free_result(result);

        if (cnt == 0) {
            printf("Guest ID %d does not exist...\n", ID);
            printf("Again Enter Guest ID :- ");
            scanf("%d", &ID);
        }
	else {
            break;
        }
    }
     // Enter Check-in Date
    printf("Check-in Date (YYYY-MM-DD) > ");
    scanf("%s", Enroll_Date);

    // Insert into Booking
    char query[512];
    snprintf(query, sizeof(query),"INSERT INTO Booking (BID, ID, R_no, Enroll_Date) VALUES (%d, %d, %d, '%s')",BID, ID, R_no, Enroll_Date);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    // Insert into Billing
    snprintf(query, sizeof(query),
             "INSERT INTO Billing (BID, ID, R_no, Enroll_Date) VALUES (%d, %d, %d, '%s')",
             BID, ID, R_no, Enroll_Date);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    // Update Room Vacancy to Booked
    snprintf(query, sizeof(query), "UPDATE Room_Details SET Vacancy='Booked' WHERE R_no=%d", R_no);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    // Fetch and display guest name
    snprintf(query, sizeof(query), "SELECT Name FROM Hotel_Visitors WHERE ID=%d", ID);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    result = mysql_store_result(conn);
    if (result == NULL) {
        finish_with_error(conn);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    printf("Room No. %d booked successfully for Guest %s...\n", R_no, row[0]);
    mysql_free_result(result);

}

void Bill(MYSQL *conn) {
    printf("Generating Bill...\n");
    int BID, Stay = 0, Room_No = 0, GID;
    float Charges = 0, Amount = 0, GST = 0, Discount = 0, Net_Amount = 0;
    char Check_out_Date[20], Room_Type[50], GName[100], Check_In_Date[20], Check_Out_Date[20];

    printf("Enter Booking ID :- ");
    scanf("%d", &BID);
    // Check if Booking ID exists
    while (true) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT * FROM Booking WHERE BID=%d", BID);

        if (mysql_query(conn, query)) {
            finish_with_error(conn);
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            finish_with_error(conn);
        }

        int cnt = mysql_num_rows(result);
        mysql_free_result(result);

        if (cnt == 0) {
            printf("Booking ID %d does not exist...\n", BID);
            printf("Again Enter Booking ID :- ");
            scanf("%d", &BID);
        }
	else {
            break;
        }
    }
    // Fetch booking details
    char query[256];
    snprintf(query, sizeof(query), "SELECT BID, ID, R_no, Enroll_Date FROM Booking WHERE BID=%d", BID);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }
    printf("Siuu");
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row) {
        printf("Booking ID: %s, Guest ID: %s, Room No: %s, Check-in Date: %s\n", row[0], row[1], row[2], row[3]);
        GID = atoi(row[1]);
        Room_No = atoi(row[2]);
        strcpy(Check_In_Date, row[3]);
    }
    mysql_free_result(result);
    // Enter Check-out Date
    printf("Check-out Date (YYYY-MM-DD) :- ");
    scanf("%s", Check_out_Date);

    // Update Check-out Date
    snprintf(query, sizeof(query), "UPDATE Billing SET DisEnroll_Date='%s' WHERE BID=%d", Check_out_Date, BID);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    // Calculate Stay Duration
    while (true) {
        snprintf(query, sizeof(query), "SELECT DATEDIFF(DisEnroll_Date, Enroll_Date) FROM Billing WHERE BID=%d", BID);
        if (mysql_query(conn, query)) {
            finish_with_error(conn);
        }

        result = mysql_store_result(conn);
        row = mysql_fetch_row(result);
        if (row) {
            Stay = atoi(row[0]);
        }
        mysql_free_result(result);

        if (Stay < 0) {
            printf("Invalid Check-out date, it can't be less than Check-in date...\n");
            printf("Again Check-out Date (YYYY-MM-DD) > ");
            scanf("%s", Check_out_Date);
            snprintf(query, sizeof(query), "UPDATE Billing SET DisEnroll_Date='%s' WHERE BID=%d", Check_out_Date, BID);
            if (mysql_query(conn, query)) {
                finish_with_error(conn);
            }
        }
	else {
            Stay += 1;
            break;
        }
    }

    // Fetch room charges
    snprintf(query, sizeof(query), "SELECT rd.Charges FROM Room_Details rd, Booking b WHERE rd.R_no=b.R_no AND BID=%d", BID);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    if (row) {
        Charges = atof(row[0]);
    }
    mysql_free_result(result);

      // Calculate Bill
    Amount = Stay * Charges;
    GST = Amount * 0.12;
    Discount = (Amount + GST) * 0.05;
    Net_Amount = Amount + GST - Discount;
    
    // Update Billing information
    snprintf(query, sizeof(query),
             "UPDATE Billing SET Stay=%d, Amount=%.2f, GST=%.2f, Net_Amount=%.2f WHERE BID=%d",
             Stay, Amount, GST, Net_Amount, BID);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    // Update Room to Vacant
    snprintf(query, sizeof(query), "UPDATE Room_Details SET Vacancy='Vacant' WHERE R_no=(SELECT R_no FROM Booking WHERE BID=%d)", BID);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    // Remove the booking from Room_Booking
    snprintf(query, sizeof(query), "DELETE FROM Booking WHERE BID=%d", BID);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }
     // Fetch additional details for billing
    snprintf(query, sizeof(query), "SELECT R_type FROM Room_Details WHERE R_no=%d", Room_No);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    if (row) {
        strcpy(Room_Type, row[0]);
    }
    mysql_free_result(result);

    snprintf(query, sizeof(query), "SELECT Name FROM Hotel_Visitors WHERE ID=%d", GID);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    if (row) {
        strcpy(GName, row[0]);
    }
    mysql_free_result(result);

    snprintf(query, sizeof(query), "SELECT DisEnroll_Date FROM Billing WHERE BID=%d", BID);
    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    if (row) {
        strcpy(Check_Out_Date, row[0]);
    }
    mysql_free_result(result);
    
    // Print Bill
    printf("\n\n");
    printf("**************************************************\n");
    printf("                   HOTEL MAHARAJA\n");
    printf("            (Opp. Bikaner Railway Station)\n");
    printf("__________________________________________________\n");
    printf("__________________________________________________\n\n");
    printf("                 Billing Receipt :-\n");
    printf("              _______________________\n\n");
    printf("          Booking ID           :           %d\n", BID);
    printf("          Room No              :           %d\n", Room_No);
    printf("          Room Type            :           %s\n", Room_Type);
    printf("          Guest ID             :           %d\n", GID);
    printf("          Guest Name           :           %s\n", GName);
    printf("          Check-in Date        :           %s\n", Check_In_Date);
    printf("          Check-out Date       :           %s\n", Check_Out_Date);
    printf("          No. of Stay          :           %d\n", Stay);
    printf("          Charges (per Room)   :           %.2f\n", Charges);
    printf("          Amount               :           %.2f\n", Amount);
    printf("          GST (@ 12%%)         :           %.2f\n", GST);
    printf("          Discount (@ 5%%)     :           %.2f\n", Discount);
    printf("\n                                 Net Amount          :        Rs. %.2f\n\n", Net_Amount);
    printf("          ___________________________________________\n\n");
    printf("                Thanks for staying in our hotel &\n");
    printf("              Enjoy the Feeling of 'MAHARAJAS' !\n");
    printf("          ___________________________________________\n\n");
    printf("**********************************************************\n\n");

}

