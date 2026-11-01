#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2

struct Room {
    int roomNumber;
    char type[20];
    float rate;
    int isOccupied;
};

struct Guest {
    int id;
    char name[30];
    char phone[15];
    int roomNumber;
    int nights;
    float billAmount;
    int isCheckedOut;
};

struct Room *rooms = NULL;
int roomCount = 0;
int roomCapacity = INITIAL_CAPACITY;

struct Guest *guests = NULL;
int guestCount = 0;
int guestCapacity = INITIAL_CAPACITY;

void clearBuffer(void);
void cleanupMemory(void);
int login(void);
void initSystem(void);
void displayRooms(void);
void addRoom(void);
void checkInGuest(void);
void checkOutGuest(void);
void displayGuests(void);
void showSummaryReport(void);

void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cleanupMemory(void) {
    if (rooms != NULL) {
        free(rooms);
        rooms = NULL;
    }
    if (guests != NULL) {
        free(guests);
        guests = NULL;
    }
}

int main(void) {
    initSystem();

    if (!login()) {
        printf("\n[!] 3 failed login attempts. Locking down system...\n");
        cleanupMemory();
        return 0;
    }

    int choice = -1;

    while (choice != 0) {
        printf("\n=====================================\n");
        printf("     HOTELIX OPERATIONS SYSTEM       \n");
        printf("=====================================\n");
        printf("1. View All Rooms\n");
        printf("2. Add New Room\n");
        printf("3. Guest Check-In\n");
        printf("4. Guest Check-Out & Billing\n");
        printf("5. View All Guest Records\n");
        printf("6. Hotel Summary Report\n");
        printf("0. Exit & Release Memory\n");
        printf("-------------------------------------\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[!] Invalid input! Please enter a valid number.\n");
            clearBuffer();
            choice = -1;
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: displayRooms(); break;
            case 2: addRoom(); break;
            case 3: checkInGuest(); break;
            case 4: checkOutGuest(); break;
            case 5: displayGuests(); break;
            case 6: showSummaryReport(); break;
            case 0: printf("\n[+] Exiting system cleanly...\n"); break;
            default: printf("\n[!] Option out of range. Try again.\n");
        }
    }

    cleanupMemory();
    printf("[+] Dynamic memory released successfully.\n");
    return 0;
}

int login(void) {
    char user[20];
    char pass[20];
    int attempts = 0;

    while (attempts < 3) {
        printf("\n=== LOGIN SCREEN (Attempt %d of 3) ===\n", attempts + 1);
        printf("Username: ");
        if (scanf("%19s", user) != 1) {
            clearBuffer();
            attempts++;
            continue;
        }
        printf("Password: ");
        if (scanf("%19s", pass) != 1) {
            clearBuffer();
            attempts++;
            continue;
        }
        clearBuffer();

        if (strcmp(user, "admin") == 0 && strcmp(pass, "1234") == 0) {
            printf("\n[+] Login Successful!\n");
            return 1;
        }

        printf("\n[!] Invalid credentials!\n");
        attempts++;
    }
    return 0;
}

void initSystem(void) {
    rooms  = (struct Room  *)calloc((size_t)roomCapacity, sizeof(struct Room));
    guests = (struct Guest *)calloc((size_t)guestCapacity, sizeof(struct Guest));

    if (rooms == NULL || guests == NULL) {
        printf("\n[!] Fatal Error: Initial dynamic allocation failed!\n");
        cleanupMemory();
        exit(1);
    }

    rooms[0].roomNumber = 101;
    strcpy(rooms[0].type, "Single");
    rooms[0].rate = 1000.0f;
    rooms[0].isOccupied = 0;

    rooms[1].roomNumber = 201;
    strcpy(rooms[1].type, "Double");
    rooms[1].rate = 1800.0f;
    rooms[1].isOccupied = 0;

    roomCount = 2;
}

void addRoom(void) {
    int roomNum;
    float roomRate;
    char typeBuf[20];

    printf("\nEnter Room Number: ");
    if (scanf("%d", &roomNum) != 1) {
        printf("\n[!] Error: Room number must be a positive integer.\n");
        clearBuffer();
        return;
    }
    if (roomNum <= 0) {
        printf("\n[!] Error: Room number must be a positive integer.\n");
        clearBuffer();
        return;
    }

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNum) {
            printf("\n[!] Error: Room Number %d already exists!\n", roomNum);
            return;
        }
    }

    printf("Enter Type (Single/Double/Suite): ");
    if (scanf("%19s", typeBuf) != 1) {
        printf("\n[!] Error: Invalid room type.\n");
        clearBuffer();
        return;
    }

    printf("Enter Rate per night (INR): ");
    if (scanf("%f", &roomRate) != 1) {
        printf("\n[!] Error: Room rate must be greater than zero.\n");
        clearBuffer();
        return;
    }
    if (roomRate <= 0.0f) {
        printf("\n[!] Error: Room rate must be greater than zero.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    if (roomCount >= roomCapacity) {
        int newCap = roomCapacity * 2;
        struct Room *temp = (struct Room *)realloc(rooms, (size_t)newCap * sizeof(struct Room));
        if (temp == NULL) {
            printf("\n[!] Memory expansion failed! Room data preserved.\n");
            return;
        }
        rooms = temp;
        roomCapacity = newCap;
        printf("\n[+] Room capacity expanded to %d.\n", roomCapacity);
    }

    rooms[roomCount].roomNumber = roomNum;
    strcpy(rooms[roomCount].type, typeBuf);
    rooms[roomCount].rate = roomRate;
    rooms[roomCount].isOccupied = 0;

    roomCount++;
    printf("[+] Room %d added successfully!\n", roomNum);
}

void displayRooms(void) {
    if (roomCount == 0) {
        printf("\n[!] No rooms registered in the system yet.\n");
        return;
    }

    printf("\n--- ROOM LIST (Total: %d | Capacity: %d) ---\n",
           roomCount, roomCapacity);
    printf("Room No | Type       | Rate (INR) | Status\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < roomCount; i++) {
        printf("%-7d | %-10s | %-10.2f | %s\n",
               rooms[i].roomNumber,
               rooms[i].type,
               rooms[i].rate,
               rooms[i].isOccupied ? "Occupied" : "Available");
    }
}

void checkInGuest(void) {
    int roomNum;
    int nights;

    printf("\nEnter Room Number for Check-In: ");
    if (scanf("%d", &roomNum) != 1) {
        printf("\n[!] Invalid room number format.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    int foundIndex = -1;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNum) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\n[!] Check-In Failed: Room %d does not exist!\n", roomNum);
        return;
    }
    if (rooms[foundIndex].isOccupied == 1) {
        printf("\n[!] Check-In Failed: Room %d is already occupied!\n", roomNum);
        return;
    }

    printf("Enter Duration of Stay (Nights): ");
    if (scanf("%d", &nights) != 1) {
        printf("\n[!] Check-In Failed: Duration must be a positive integer.\n");
        clearBuffer();
        return;
    }
    if (nights <= 0) {
        printf("\n[!] Check-In Failed: Duration must be a positive integer.\n");
        clearBuffer();
        return;
    }

    if (guestCount >= guestCapacity) {
        int newCap = guestCapacity * 2;
        struct Guest *temp = (struct Guest *)realloc(guests, (size_t)newCap * sizeof(struct Guest));
        if (temp == NULL) {
            printf("\n[!] Memory expansion failed! Check-in aborted.\n");
            return;
        }
        guests = temp;
        guestCapacity = newCap;
        printf("\n[+] Guest capacity expanded to %d.\n", guestCapacity);
    }

    guests[guestCount].id           = 1001 + guestCount;
    guests[guestCount].roomNumber   = roomNum;
    guests[guestCount].nights       = nights;
    guests[guestCount].billAmount   = (float)nights * rooms[foundIndex].rate;
    guests[guestCount].isCheckedOut = 0;

    printf("Enter Guest Name: ");
    /* FIXED: " %29[^\n]" reads the full line including spaces.
       The leading space skips any leftover newline in the buffer.
       [^\n] means: read everything until the newline character. */
    if (scanf(" %29[^\n]", guests[guestCount].name) != 1) {
        printf("\n[!] Invalid name input.\n");
        clearBuffer();
        return;
    }

    printf("Enter Phone Number: ");
    if (scanf("%14s", guests[guestCount].phone) != 1) {
        printf("\n[!] Invalid phone input.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    rooms[foundIndex].isOccupied = 1;

    printf("[+] Check-In successful! Guest ID: %d | Total: INR %.2f\n",
           guests[guestCount].id, guests[guestCount].billAmount);

    guestCount++;
}

void checkOutGuest(void) {
    int roomNum;
    printf("\nEnter Room Number for Check-Out: ");
    if (scanf("%d", &roomNum) != 1) {
        printf("\n[!] Invalid input for room number.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    int guestIndex = -1;
    for (int i = 0; i < guestCount; i++) {
        if (guests[i].roomNumber == roomNum && guests[i].isCheckedOut == 0) {
            guestIndex = i;
            break;
        }
    }

    if (guestIndex == -1) {
        printf("\n[!] Check-Out Failed: No active stay for Room %d.\n", roomNum);
        return;
    }

    printf("\n===================================\n");
    printf("        OFFICIAL HOTEL RECEIPT     \n");
    printf("===================================\n");
    printf("Guest ID     : %d\n", guests[guestIndex].id);
    printf("Guest Name   : %s\n", guests[guestIndex].name);
    printf("Phone        : %s\n", guests[guestIndex].phone);
    printf("Room Number  : %d\n", guests[guestIndex].roomNumber);
    printf("Nights Stayed: %d\n", guests[guestIndex].nights);
    printf("-----------------------------------\n");
    printf("TOTAL AMOUNT : INR %.2f\n", guests[guestIndex].billAmount);
    printf("===================================\n");

    guests[guestIndex].isCheckedOut = 1;

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNum) {
            rooms[i].isOccupied = 0;
            break;
        }
    }
    printf("[+] Check-out done! Room %d is now Available.\n", roomNum);
}

void displayGuests(void) {
    if (guestCount == 0) {
        printf("\n[!] No guest records found in the system.\n");
        return;
    }

    printf("\n--- GUEST DIRECTORY (Total: %d | Capacity: %d) ---\n",
           guestCount, guestCapacity);
    printf("ID   | Name       | Phone       | Room | Nights | Bill (INR) | Status\n");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < guestCount; i++) {
        printf("%-4d | %-10s | %-11s | %-4d | %-6d | %-10.2f | %s\n",
               guests[i].id,
               guests[i].name,
               guests[i].phone,
               guests[i].roomNumber,
               guests[i].nights,
               guests[i].billAmount,
               guests[i].isCheckedOut ? "Checked Out" : "Active Stay");
    }
}

void showSummaryReport(void) {
    int occupiedCount = 0;
    float realizedRevenue = 0.0f;
    float pendingReceivables = 0.0f;

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].isOccupied == 1) {
            occupiedCount++;
        }
    }

    for (int i = 0; i < guestCount; i++) {
        if (guests[i].isCheckedOut == 1) {
            realizedRevenue += guests[i].billAmount;
        } else {
            pendingReceivables += guests[i].billAmount;
        }
    }

    printf("\n=== HOTEL SUMMARY & REVENUE REPORT ===\n");
    printf("Total Registered Rooms  : %d\n", roomCount);
    printf("Occupied Rooms          : %d\n", occupiedCount);
    printf("Available Rooms         : %d\n", roomCount - occupiedCount);
    printf("--------------------------------------\n");
    printf("Realized Revenue (Paid) : INR %.2f\n", realizedRevenue);
    printf("Active Stay Receivables : INR %.2f\n", pendingReceivables);
    printf("======================================\n");
}