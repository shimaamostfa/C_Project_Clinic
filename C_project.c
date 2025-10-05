#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef unsigned char u8;
typedef unsigned int u32;

#define MAX_RESERVATIONS 5

const char *TimeSlots[MAX_RESERVATIONS] = {
    "2:00 - 2:30 PM",
    "2:30 - 3:00 PM",
    "3:00 - 3:30 PM",
    "4:00 - 4:30 PM",
    "4:30 - 5:00 PM"
};
u32 Reservations[MAX_RESERVATIONS] = {0}; // 0 = available, ID = reserved


typedef struct Node
{
    u32 ID;
    char Name[50];
    u32 Age;
    char Gender[10];
    struct Node *next; // Pointer to the next node in the linked list
}Node;
Node* Head ;
Node* Current ;


// Function prototype
int Check_ID(u32 Id);
void view_patient_information(void);
void view_today_reservations(void);
void Add_patient(void);
void Edit_patient(void);
void Exit(void);
void Reserve_slot(void);
void view_available_slots(void);
void Cancel_Reservation(void);
void Admin (void);
void User (void);

int Check_ID(u32 Id)
{
    
    Node* temp = Head;
    while(temp !=NULL)
    {
        if(temp->ID == Id)
        {
            printf("Welcome, your ID %d is found\n", Id);
            return 1;
            break;
        }
        temp = temp->next;
           
    }
    //printf("Your ID %d is not found, please contact the admin\n", new_node->ID);
    //free(new_node);
    return 0;

}

void view_patient_information(void)
{
    u32 Id;
    printf("Please enter your ID: ");
    scanf("%d", &Id);

    Node* patient = Head;
    while(patient != NULL)
    {
        if(patient->ID == Id)
        {
            printf("Name: %s\n", patient->Name);
            printf("Age: %d\n", patient->Age);
            printf("Gender: %s\n", patient->Gender);
            return;
        }
        patient = patient->next;
    }
    printf("ID not found.\n");


}

void Reserve_slot(void)
{
    u32 ID;
    printf("Enter your ID: ");
    scanf("%d", &ID);
    printf("Slots are: ");
    for(int i = 0; i < MAX_RESERVATIONS; i++)
    {
        printf("%d --> %s\n", i, TimeSlots[i]);
    }
    int slot;
    printf("Please enter your preferred slot: \n");
    scanf("%d", &slot);
    if(slot < 0 || slot >= MAX_RESERVATIONS)
    {
        printf("Invalid slot number. Please choose between 0 and %d\n", MAX_RESERVATIONS-1);
        return;
    }

    if(Check_ID(ID) == 0) // لازم المريض يكون متسجل
    {
        printf("ID not found. Please register patient first.\n");
        return;
    }

    if(Reservations[slot] == 0)
    {
        Reservations[slot] = ID;
        printf("Reservation confirmed for patient ID %d at %s\n", ID, TimeSlots[slot]);
    }
    else
    {
        printf("Slot %s is already reserved.\n", TimeSlots[slot]);
    }
}

void view_available_slots(void)
{
    printf("Available slots:\n");
    int found = 0;
    for(int i = 0; i < MAX_RESERVATIONS; i++)
    {
        if(Reservations[i] == 0)
        {
            printf("%d --> %s\n", i, TimeSlots[i]);
            found = 1;
        }
    }
    if(!found)
    {
        printf("No available slots today.\n");
    }
}

void view_today_reservations(void)
{
    printf("Today's Reservations:\n");
    for(int i = 0; i < MAX_RESERVATIONS; i++)
    {
        if(Reservations[i] == 0)
        {
            printf("%s --> Available\n", TimeSlots[i]);
        }
        else
        {
            printf("%s --> Reserved for patient ID %d\n", TimeSlots[i], Reservations[i]);
        }
    }
}

void Cancel_Reservation(void)
{
    u32 ID;
    int slot;

    printf("Enter your Patient ID: ");
    scanf("%u", &ID);

    printf("Enter the slot number to cancel (0 to %d): ", MAX_RESERVATIONS - 1);
    scanf("%d", &slot);
    if(slot < 0 || slot >= MAX_RESERVATIONS)
    {
        printf("Invalid slot number.\n");
        return;
    }

    if(Reservations[slot] != 0)
    {
        printf("Reservation for patient ID %d at %s is canceled.\n", Reservations[slot], TimeSlots[slot]);
        Reservations[slot] = 0;
    }
    else
    {
        printf("This slot is already available.\n");
    }
}

void Add_patient(void)
{
    printf("Enter your ID: ");
    u32 Id;
    scanf("%d", &Id);
    if(Check_ID(Id) == 0)
    {
        // Code for adding patient information
        printf("Enter patient name: ");
        char name[50];
        scanf("%s", name);
        printf("Enter patient age: ");
        u32 age;
        scanf("%d", &age);
        printf("Enter patient gender: ");
        char gender[10];
        scanf("%s", gender);

        // Create a new patient and add it to the list
        Node* new_patient = (Node*)malloc(sizeof(Node));
        new_patient->ID = Id;
        strcpy(new_patient->Name, name);
        new_patient->Age = age;
        strcpy(new_patient->Gender, gender);

        // Add the new patient to the linked list
        new_patient->next = Head;
        Head = new_patient;

        printf("Patient added successfully\n");
    }
    else
    {
        printf("Cannot add patient, ID was registered before\n");
    }
}

void Edit_patient(void)
{
    u32 Id;
    printf("Enter patient ID to edit: ");
    scanf("%d", &Id);

    Node* patient = Head;
    while(patient != NULL)
    {
        if(patient->ID == Id)
        {
            printf("Editing patient information...\n");
            printf("Enter new name: ");
            scanf("%s", patient->Name);
            printf("Enter new age: ");
            scanf("%d", &patient->Age);
            printf("Enter new gender: ");
            scanf("%s", patient->Gender);
            printf("Patient information updated successfully.\n");
            return;
        }
        patient = patient->next;
    }
    printf("Patient ID not found.\n");
}

void Admin (void)
{
    u32 password;
    printf("Welcome to the admin mode\n");
    int n = 0;
    while (n<3)
    {
        printf("Enter the password: ");
        scanf("%d",&password);
      if(password == 1234)
    {
        printf("Admin mode accessed\n");
        printf("Edit, Add patient information OR Reserve, Cancle slots (E/A/R/C): ");
        char choice;
        scanf(" %c",&choice);
        switch (choice)
        {
            case 'E':
                Edit_patient();
                break;
            case 'A':
                Add_patient();
                break;
            case 'R':
                Reserve_slot();
                break;
            case 'C':
                Cancel_Reservation();
                break;
        }
        break;

        
    }
    else
    {  
        printf("Wrong password, please try again\n");
    }
    n++;
    }

}

void User (void)
{
    u8 choice;
    printf("Welcome to the user mode\n");
    printf("view patient informaton -->'P' OR view Today's Reservations -->'R'\n");
    scanf(" %c", &choice);
    switch (choice)
    {
    case 'P':
        view_patient_information();
        break;
    case 'R':
        view_today_reservations();
        break;
    default:
        break;
    }
    

}

void Exit(void)
{
    printf("Exiting the program...\n");
    exit(0);
}

int main(void)
{
    while (1)
    {
    printf("Welcome to the clinic\n");
    printf("Please enter the mode (A --> Admin)/(U --> User)/(E --> Exit): ");
    char Mode;
    scanf(" %c",&Mode);
    switch (Mode)
    {
    case 'A':
        printf("Admin mode selected\n");
        Admin();
        break;
    case 'U':
        printf("User mode selected\n");
        User();
        break;
    case 'E':
        printf("Exit mode selected\n");
        Exit();
        break;
    default:
        printf("Invalid choice, try again.\n");
        break;
    }
}

    return 0;
}