# Hotel Management System

## Overview

The **Hotel Management System** is a console-based application developed in C with MySQL as the backend database. This system allows hotel management to efficiently handle operations such as visitor registration, room management, booking processes, and billing.

## Features

- **Visitor Management**: Register new visitors with their details such as name, contact information, ID proof, and nationality.
- **Room Management**: Manage room details, including room types, charges, and vacancy status.
- **Booking Management**: Book rooms for visitors and manage current and previous bookings.
- **Billing System**: Generate bills based on the duration of stay, including calculation of GST and net amount.

## Technologies Used

- **Programming Language**: C
- **Database**: MySQL
- **Host**: localhost
- **MySQL User**: root
- **Database Name**: Hotel

## Database Structure

### 1. **Hotel_Visitors Table**
   - **Columns**:
     - `ID` (int, Primary Key)
     - `Name` (char(30))
     - `Mobile_no` (bigint)
     - `ID_Proof` (char(20))
     - `ID_no` (int)
     - `Nationality` (char(30))
     - `City` (char(20))

### 2. **Room_Details Table**
   - **Columns**:
     - `R_no` (int, Primary Key)
     - `R_type` (char(40))
     - `Charges` (int)
     - `Vacancy` (char(8), Default: "Vacant")

### 3. **Booking Table**
   - **Columns**:
     - `BID` (char(8), Primary Key)
     - `ID` (int, Foreign Key references Hotel_Visitors(ID))
     - `R_no` (int, Foreign Key references Room_Details(R_no))
     - `Enroll_Date` (date)

### 4. **Billing Table**
   - **Columns**:
     - `BID` (int, Primary Key)
     - `ID` (int, Foreign Key references Hotel_Visitors(ID))
     - `R_no` (int, Foreign Key references Room_Details(R_no))
     - `Enroll_Date` (date)
     - `DisEnroll_Date` (date)
     - `Stay` (int)
     - `Amount` (int)
     - `GST` (char(10))
     - `Net_Amount` (int)

## Installation and Setup

### Prerequisites

- GCC compiler
- MySQL Server

### Step-by-Step Guide

1. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   ```
### Compile the C Code:

```bash
gcc -o hotel_management hotel_management.c -lmysqlclient
```
## MySQL Database Setup

- Create the database and tables as specified in the Database Structure.
- Insert initial room details and visitor records as needed.

### Secure MySQL Installation (Optional)

- Run `sudo mysql_secure_installation` to secure your MySQL server.

## Usage

### Visitor Management:
- Add, update, search, or remove visitor details.

### Room Management:
- Add, update, search, or remove room details.

### Booking:
- Book rooms for visitors and manage booking records.

### Billing:
- Generate bills for the visitor's stay, calculate GST, and display the net amount.

## Use Cases

### 1. Check-in Process

**Description**: When a visitor arrives at the hotel, their details are registered in the system. Based on the room availability, a room is assigned, and the booking details are stored in the database.

**Steps**:
1. Register the visitor in the `Hotel_Visitors` table.
2. Check room availability in the `Room_Details` table.
3. Book the room by inserting a record in the `Booking` table.
4. Update the room status to "Occupied" in the `Room_Details` table.

### 2. Room Upgrade

**Description**: If a guest requests a room upgrade during their stay, the system checks for availability and processes the upgrade.

**Steps**:
1. Search for the current booking in the `Booking` table.
2. Check for the availability of the desired room type in the `Room_Details` table.
3. Update the booking details with the new room number.
4. Update the status of the old room to "Vacant" and the new room to "Occupied".

### 3. Check-out Process

**Description**: When a visitor checks out, their booking record is updated with the check-out date, and the final bill is generated.

**Steps**:
1. Update the `DisEnroll_Date` in the `Billing` table.
2. Calculate the total stay, amount due, GST, and net amount.
3. Mark the room as "Vacant" in the `Room_Details` table.

### 4. Generate Bill

**Description**: After a guest checks out, the system calculates the total amount for the stay, applies GST, and generates the final bill.

**Steps**:
1. Retrieve the booking and stay details from the `Booking` and `Billing` tables.
2. Calculate the total amount based on the room charges and stay duration.
3. Apply GST and generate the net amount.
4. Display or print the bill for the guest.

### 5. Room Availability Search

**Description**: Hotel staff can search for available rooms based on room type or other criteria to assist with booking inquiries.

**Steps**:
1. Query the `Room_Details` table for rooms marked as "Vacant".
2. Display the available rooms with their details for selection.
