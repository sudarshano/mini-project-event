#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Event {
    int id;
    char name[50];
    char category[20];
    char location[50];

    int day, month, year;
    int seats;
    int waitlist;
    int popularity;

    struct Event *prev;
    struct Event *next;
};

struct Event *head = NULL;
int autoID = 1000;


int compareDate(int d1,int m1,int y1,int d2,int m2,int y2){
    if(y1!=y2) return y1-y2;
    if(m1!=m2) return m1-m2;
    return d1-d2;
}


struct Event* createEvent(){
    struct Event *e = (struct Event*)malloc(sizeof(struct Event));

    e->id = ++autoID;

    printf("Event Name: ");
    scanf(" %[^\n]", e->name);

    printf("Category (Tech/Cultural/Sports/Workshop): ");
    scanf(" %[^\n]", e->category);

    printf("Location: ");
    scanf(" %[^\n]", e->location);

    printf("Date (DD MM YYYY): ");
    scanf("%d%d%d",&e->day,&e->month,&e->year);

    printf("Total Seats: ");
    scanf("%d",&e->seats);

    e->waitlist = 0;
    e->popularity = 0;
    e->prev = e->next = NULL;

    return e;
}


void insertEvent(){
    struct Event *n = createEvent();

    if(head == NULL){
        head = n;
        printf("Event Added Successfully!\n");
        return;
    }

    struct Event *t = head;

    while(t && compareDate(t->day,t->month,t->year,
                            n->day,n->month,n->year) < 0)
        t = t->next;

    if(t == head){
        n->next = head;
        head->prev = n;
        head = n;
    }
    else if(t == NULL){
        struct Event *last = head;
        while(last->next)
            last = last->next;

        last->next = n;
        n->prev = last;
    }
    else{
        n->next = t;
        n->prev = t->prev;
        t->prev->next = n;
        t->prev = n;
    }

    printf("Event Added Successfully!\n");
}


void displayChronological(struct Event *temp){
    if(temp == NULL)
        return;

    printf("\n-----------------------------");
    printf("\nID        : %d", temp->id);
    printf("\nName      : %s", temp->name);
    printf("\nCategory  : %s", temp->category);
    printf("\nLocation  : %s", temp->location);
    printf("\nDate      : %02d-%02d-%04d", temp->day, temp->month, temp->year);
    printf("\nSeats     : %d", temp->seats);
    printf("\nWaitlist  : %d", temp->waitlist);
    printf("\nPopularity: %d", temp->popularity);

    displayChronological(temp->next);
}


void displayReverse(struct Event *temp){
    if(temp == NULL)
        return;

    displayReverse(temp->next);

    printf("\n-----------------------------");
    printf("\nID        : %d", temp->id);
    printf("\nName      : %s", temp->name);
    printf("\nCategory  : %s", temp->category);
    printf("\nLocation  : %s", temp->location);
    printf("\nDate      : %02d-%02d-%04d", temp->day, temp->month, temp->year);
    printf("\nSeats     : %d", temp->seats);
    printf("\nWaitlist  : %d", temp->waitlist);
    printf("\nPopularity: %d", temp->popularity);
}


void bookSeat(){
    int id;
    printf("Enter Event ID: ");
    scanf("%d",&id);

    struct Event *t = head;
    while(t && t->id != id)
        t = t->next;

    if(!t){
        printf("Event Not Found!\n");
        return;
    }

    if(t->seats > 0){
        t->seats--;
        t->popularity++;
        printf("Seat Booked Successfully!\n");
    }
    else{
        t->waitlist++;
        printf("Event Full! Added to Waitlist.\n");
    }
}


void searchByID(){
    int id;
    printf("Enter Event ID: ");
    scanf("%d",&id);

    struct Event *t = head;
    while(t){
        if(t->id == id){
            printf("\nEvent Found!");
            printf("\nName: %s",t->name);
            printf("\nCategory: %s",t->category);
            printf("\nLocation: %s",t->location);
            printf("\nDate: %02d-%02d-%04d",t->day,t->month,t->year);
            return;
        }
        t = t->next;
    }
    printf("Event Not Found!\n");
}


void searchByCategory(){
    char cat[20];
    int found = 0;

    printf("Enter Category: ");
    scanf(" %[^\n]", cat);

    struct Event *t = head;
    while(t){
        if(strcmp(t->category, cat) == 0){
            printf("\n%s (%02d-%02d-%04d)",t->name,t->day,t->month,t->year);
            found = 1;
        }
        t = t->next;
    }

    if(!found)
        printf("No events in this category!\n");
}


void mostPopularEvent(){
    if(!head){
        printf("No Events Available!\n");
        return;
    }

    struct Event *t = head, *best = head;

    while(t){
        if(t->popularity > best->popularity)
            best = t;
        t = t->next;
    }

    printf("\n🔥 Most Popular Event 🔥");
    printf("\n%s (%d bookings)\n",best->name,best->popularity);
}


int main(){
    int choice;

    while(1){
        printf("\n\n===== EVENT SCHEDULING SYSTEM =====");
        printf("\n1. Add Event");
        printf("\n2. Display Events (Chronological)");
        printf("\n3. Display Events (Reverse)");
        printf("\n4. Book Seat");
        printf("\n5. Search by Event ID");
        printf("\n6. Search by Category");
        printf("\n7. Most Popular Event");
        printf("\n8. Exit");
        printf("\nEnter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1: insertEvent(); break;
            case 2: displayChronological(head); break;
            case 3: displayReverse(head); break;
            case 4: bookSeat(); break;
            case 5: searchByID(); break;
            case 6: searchByCategory(); break;
            case 7: mostPopularEvent(); break;
            case 8: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}
