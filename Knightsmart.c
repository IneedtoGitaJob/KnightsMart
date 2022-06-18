/*
Andreas Hinsch
COP3502C
Feb, 15 2019
Spring: 0004
Knightsmart
*/

# include <stdio.h>
# include <stdlib.h>
#include <string.h>


 	typedef struct KnightsMartProduct {
 	 	int itemNum;
 	 	char itemName[21];
 	 	double unitPrice;
 	 	int stockQty;
 	 	int restockQty;
 	 	struct KnightsMartProduct *next;
 	    } KMProduct;

 	    typedef struct KnightsMartRestockProduct {
 	 	int itemNum;
 	 	struct KnightsMartRestockProduct *next;
 	} KMRestockProduct;

 	typedef struct KnightsMartSale {
 	    char firstName[21];
 	 	char lastName[21];
 	 	int numItemsOnList;
 	 	int *itemsPurchased;
 	 	int *item;
 	 	int total;
 	 	struct KnightsMartSale *next;
 	 	} KMSale;


//Restocks all products with quantity 0
void RESTOCK( KMRestockProduct *KMRestockhead, KMProduct *KMProducthead);

//Adds an item to the end of the Knightsmartproduct linked list
KMProduct * ADDITEM(FILE * ptr, KMProduct *KMProducthead);

//Prints the available inventory
void INVENTORY(KMProduct * KMProducthead);

//Facilitates the Customer command and stores the interaction in the KnightsmartSale Linked list
KMSale *CUSTOMER(FILE *ptr, KMSale *KMSalehead, KMProduct * KMProducthead);

//Prints all customer activity for that day
KMSale *PRINTDAYSUMMARY( KMSale *KMSalehead, KMProduct * KMProducthead);


int main(){

//Declares pointers to the heads of the linked lists
KMProduct *KMProductpoint = NULL;
KMRestockProduct *KMRestockpoint = NULL;
KMSale *KMSalepoint = NULL;

//pointer to input file
FILE *ptr;

//pointer to output file
FILE *actionpoint;

//opens both input and output files
ptr = fopen("Knightsmart.in", "r");
actionpoint = fopen("Knightsmart.out", "w+");

//a character array that takes in the commands of each action
char input[15];

//Creates a variable days of how many days of actions there are
int days = 0;
fscanf(ptr, "%d", &days);

int actions = 0;

//runs until the number of days is met
for(int q = 1; q <= days; q++){

printf("*************************\n UCF KnightsMart Day %d\n*************************\n", q);
    fscanf(ptr, "%d", &actions);

//runs until the number of actions is met
for(int c = 1; c <= actions; c++){
fprintf(ptr, "U");
fscanf(ptr, "%s", input);

//if the action is a particular command execute the command
if(strcmp(input, "ADDITEM") == 0){

KMProductpoint =  ADDITEM(ptr, KMProductpoint);

}

if(strcmp(input, "INVENTORY") == 0){

INVENTORY(KMProductpoint);

}

if(strcmp(input, "RESTOCK") == 0){

RESTOCK(KMRestockpoint, KMProductpoint);

}

if(strcmp(input, "CUSTOMER") == 0){

    KMSalepoint = CUSTOMER(ptr, KMSalepoint,KMProductpoint);

}

if(strcmp(input, "PRINTDAYSUMMARY") == 0){

    KMSalepoint = PRINTDAYSUMMARY(KMSalepoint, KMProductpoint);

}

}


}
free(KMProductpoint);
free(KMRestockpoint);
free(KMSalepoint);
return 0;
}
KMProduct * ADDITEM(FILE * ptr, KMProduct * KMProducthead){

//declares temporary pointers to head
KMProduct * temp = NULL;
KMProduct * KMPcurrent = NULL;

    //Creates new node
temp = (KMProduct*)malloc(sizeof(KMProduct));

//fills in the list with the information from the file
fscanf(ptr ,"%d", &temp->itemNum);
fscanf(ptr ,"%s", temp->itemName);
fscanf(ptr ,"%lf", &temp->unitPrice);
fscanf(ptr ,"%d", &temp->stockQty);
fscanf(ptr ,"%d", &temp->restockQty);
printf("Item %d, %s, with a cost of %.2lf and Initial stock of %d, has been added to the product database\n",temp->itemNum, temp->itemName, temp->unitPrice, temp->stockQty);

//connects the nodes
    temp->next = NULL;

    KMPcurrent = KMProducthead;

//if first item make temp head
    if (KMProducthead == NULL){
              return temp;

    }


    while (KMPcurrent ->next != NULL){
        KMPcurrent = KMPcurrent->next;
    }

    KMPcurrent->next = temp;


    return KMProducthead;

}


void INVENTORY(KMProduct * KMProducthead){
    //if the node is empty
if(KMProducthead != NULL){

//while KMPCurrent does not equal NULL print inventory
KMProduct * KMPCurrent = KMProducthead;
printf("INVENTORY: contains the following items:\n");
while(KMPCurrent != NULL){
printf("\t| Item %6d | %-20s | $%7.2lf | %4d unit(s) |\n", KMPCurrent->itemNum, KMPCurrent->itemName, KMPCurrent->unitPrice, KMPCurrent->stockQty);
KMPCurrent = KMPCurrent->next;
}

}
else{
printf("INVENTORY: contains no items\n");

}

}


void RESTOCK( KMRestockProduct *KMRestockhead, KMProduct *KMProducthead){
//If the node is empty
if(KMProducthead != NULL){

KMProduct *KMProductCurrent = KMProducthead;
int first = 1;

//traverse the linked list and for all items with no items in stock restock them with the restock amount
while(KMProductCurrent != NULL){

    if(KMProductCurrent->stockQty == 0){
if(first == 1){printf("RESTOCK:  the following items have been reordered and restocked:\n"); first = 0;}
printf("Item %d, %s, restocked to a quantity of %d \n", KMProductCurrent->itemNum, KMProductCurrent->itemName, KMProductCurrent->restockQty);

        KMProductCurrent->stockQty = KMProductCurrent->restockQty;
        KMProductCurrent =  KMProductCurrent->next;
    }
    else{

        KMProductCurrent =  KMProductCurrent->next;
    }
}

}

else{
printf("RESTOCK:  the Restock List contains no items.\n");

}

}


KMSale * CUSTOMER(FILE *ptr, KMSale *KMSalehead, KMProduct * KMProducthead){

//generates temporary nodes
KMSale * temp = NULL;
KMSale * KMScurrent = NULL;
KMProduct *KMProductCurrent = NULL;
KMProductCurrent = KMProducthead;

//control variables
int ItemNum = 0;

int NumOfitems = 0;

int difference = 0;

int bought = 0;

int escape = 0;

int control = 0;

int breaking = 0;

int arrcontrol = 0;

int totalnum = 0;

//Creates new node
temp = (KMSale*)malloc(sizeof(KMSale));
temp->next = NULL;
temp->itemsPurchased = malloc(sizeof(int));
temp->item = malloc(sizeof(int));

//fills in the list with the information from the file
fscanf(ptr ,"%s", temp->firstName);
fscanf(ptr ,"%s", temp->lastName);
fscanf(ptr ,"%d", &temp->numItemsOnList);

control = temp->numItemsOnList/2;
//for the items in the customers shopping list
for(int x = 1; x <= control; x++){

    fscanf(ptr, "%d", &ItemNum);
    fscanf(ptr, "%d", &NumOfitems);

escape = 0;
difference = 0;
breaking = 0;
KMProductCurrent = KMProducthead;
//traverse the list and find the item
    while(KMProductCurrent->itemNum != ItemNum){
if(breaking == 1 && KMProductCurrent->itemNum != ItemNum){escape = 1; break;}
                    KMProductCurrent = KMProductCurrent->next;
                    if(KMProductCurrent->next == NULL){breaking = 1;}
    }

    //If the item is present in the store
if(escape != 1){

if(KMProductCurrent->stockQty != 0){

//if there is not enough items for the customer to buy, buy what is remaining
if(KMProductCurrent->stockQty - NumOfitems  < 0){

difference = KMProductCurrent->stockQty - NumOfitems;
NumOfitems = NumOfitems + difference;

}

//fills in temp with modified variables
temp->numItemsOnList = NumOfitems;
KMProductCurrent->stockQty = KMProductCurrent->stockQty - NumOfitems;

bought++;
totalnum = totalnum + NumOfitems;
temp->itemsPurchased[bought] = KMProductCurrent->itemNum;
temp->item[arrcontrol] = NumOfitems;
arrcontrol++;
}
}

}
//if the customer made a purchase
if(bought > 0){printf("Customer %s %s came and made some purchases\n",temp->firstName,temp->lastName);}

//if the customer made no purchase
if(bought == 0){printf("Customer %s %s came and made no purchases\n",temp->firstName,temp->lastName);}

//traverses and links the Sale nodes together
temp->itemsPurchased[0] = bought;
temp->total = totalnum;
    KMScurrent = KMSalehead;


    if (KMSalehead == NULL){
              return temp;

    }


    while (KMScurrent ->next != NULL){
        KMScurrent = KMScurrent->next;
    }

    KMScurrent->next = temp;


return KMSalehead;
}


KMSale *PRINTDAYSUMMARY(KMSale *KMSalehead,  KMProduct *KMProducthead){

if(KMSalehead != NULL){

        //generates temporary nodes
    KMSale * KMSCurrent = NULL;
 KMSale * KMSnext = NULL;
KMSCurrent = KMSalehead;
KMSnext = (KMSale*)malloc(sizeof(KMSale));

KMProduct * KMProductCurrent = NULL;
KMProductCurrent = KMProducthead;

//sale number
int count = 0;

//grand total of the day
double income = 0;

//total for the customer
double custtotal = 0;

//traverses the Sale node and prints out the daily summary
printf("KnightsMart Daily Sales report:\n");

while(KMSCurrent != NULL){

//if the customer bought something print out what they bought and go to the next node
if(KMSCurrent->total != 0){
custtotal = 0;
    count++;
printf("SALE #%d, %s %s purchased %d item(s)\n", count, KMSCurrent->firstName, KMSCurrent->lastName, KMSCurrent->total);
for(int r = 1; r <= KMSCurrent->itemsPurchased[0]; r++){

while(KMProductCurrent->itemNum != KMSCurrent->itemsPurchased[r]){
    KMProductCurrent = KMProductCurrent->next;
}
printf("\t\t| Item %6d | %-20s | $%7.2lf (x%4d) |\n" , KMProductCurrent->itemNum, KMProductCurrent->itemName, KMProductCurrent->unitPrice, KMSCurrent->item[r -1]);

custtotal = custtotal+ (KMProductCurrent->unitPrice * KMSCurrent->item[r -1]);

income = income + (KMProductCurrent->unitPrice * KMSCurrent->item[r -1]);

KMProductCurrent = KMProducthead;

}

//prints the customers total
printf("Total: %.2lf\n", custtotal);
KMSCurrent = KMSCurrent->next;
}
else{KMSCurrent = KMSCurrent->next;}
}
//prints the days total
printf("Grand total = %.2lf\n", income);
KMSCurrent = KMSalehead;


KMSalehead = NULL;
return(KMSalehead);

}

else{
 printf("KnightsMart Daily Sales report: There were no sales today.\n");
return(KMSalehead);
}

}
