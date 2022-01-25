#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

struct inventory
{
    char ID[50];
    char name[50];
    char description[50];
    float price;
    int quantity;
}inv;

void login()
{
    int a=0,i=0;
    char uname[10],c = ' '; 
    char pword[10],code[10];
    char user[10]="manager";
    char pass[10]="lkrs";
    do
    {
        system("cls");
	
        printf("\n===================== LOGIN FORM =====================  ");
        printf(" \n\tENTER USERNAME: ");
	    scanf("%s", &uname); 
	    printf(" \n\tENTER PASSWORD: ");
	while(i < 10)
	{
	    pword[i] = getch();
	    c = pword[i];
	    if (c == 13) 
            break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
	i = 0; 
	if(strcmp(uname,user) == 0 && strcmp(pword,pass) == 0)
	{
	    printf("\n\n\n\t\tWELCOME !!!! LOGIN IS SUCCESSFUL");
        getch();
	    break;
	}
	else
	{
		printf("\n\tSORRY !!!!  PLEASE TRY AGAIN!!!");
		a++;
		getch();
	}
}
	while(a<=2);
	if (a>2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");
		getch();
	}
	system("cls");	
}
void billHeader(char name [50], char date[30])
{
    printf("\n\n");
    printf("\t      LONGKIM. Restaurant");
    printf("\n\t    --------------------");
    printf("\nDate:%s",date);
    printf("\nInvoice To: %s\n",name);
    printf("----------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n----------------------------------------");
    printf("\n\n");
}

void billBody(char item[30], int qty, float price)
{
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

void billFooter(float total)
{
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total - dis;
    printf("----------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\n----------------------------------------");
}

void add()
{
    system("cls");
    FILE *f;
    f = fopen("ListofInventory.dat","a+b");
    printf("\nPlease enter ID: ");
    scanf("%s",inv.ID);
    printf("\nPlease enter the name of item: ");
    scanf("%s",inv.name);
    printf("\nPlease enter the Description: ");
    scanf("%s",inv.description);
    printf("\nPlease enter the quantity: ");
    scanf("%d",&inv.quantity);
    printf("\nPlease enter the unit price: ");
    scanf("%f",&inv.price);
    fwrite(&inv,sizeof(struct inventory),1,f);
    printf("\nSuccessfully saved!");
    fclose(f);
}

void list()
{
    system("cls");
    FILE *f;
    f = fopen("ListofInventory.dat","rb");

    printf("\nID\t");
    printf("NAME\t");
    printf("DESCRIPTION\t");
    printf("PRICE\t\t");
    printf("QUANTITY\t");
    printf("VALUE\n");

    for(int i = 0; i < 100 ;i++)
        printf("=");
    while(fread(&inv,sizeof(struct inventory),1,f))
        printf("\n%s \t%s \t%s \t\t%.2f \t%d  \t\t%.2f", inv.ID, inv.name, inv.description, inv.price, inv.quantity, inv.price*inv.quantity);
    
    printf("\n");
    for(int i = 0; i < 100; i++)
        printf("=");
    getch();
    fclose(f);
}

void deletel()
{
    system("cls");
    char id[50];
    int i = 1;
    FILE *f, *t;
    t = fopen("temp.dat","wb");
    f = fopen("ListofInventory.dat","rb");

    printf("\n========================= DELETE ITEMS ========================");
    printf("Please enter ID to be deleted: ");
    scanf("%s",id);

    while(fread(&inv,sizeof(struct inventory),1,f))
    {
        if(strcmp(inv.ID,id) == 0)
        {
            i = 0;
            continue;
        }
        else
            fwrite(&inv,sizeof(struct inventory),1,t);
    }
    if (i == 1)
    {
        printf("ID is not found!");
        getch();
        fclose(f);
        fclose(t);
    }
    fclose(f);
    fclose(t);
    remove("ListofInventory.dat");
    rename("temp.dat","ListofInventory.dat");
    printf("\n\tThe item is successfully removed...");
}

void search()
{
    system("cls");
    char id[50];
    int flag = 1;
    FILE *f;
    f = fopen("ListofInventory.dat","rb");

    printf("\n========================= SEARCH ITEMS ========================");
    printf("Enter the ID of item to search: ");
    scanf("%s",id);

    while(fread(&inv,sizeof(struct inventory),1,f))
    {
        if (strcmp(inv.ID,id) == 0)
        {
            flag = 0;
            printf("\n======================== RECORD FOUND! ========================\n");
            printf("ID: \t%s",inv.ID);
            printf("\nName: \t%s",inv.name);
            printf("\nDescription: \t%s",inv.description);
            printf("\nPrice: \t%.2f",inv.price);
            printf("\nQuantity: \t%d",inv.quantity);
            printf("\nValue: \t%.2f", inv.price*inv.quantity);
        }
    }

    if (flag == 1)
        printf("The item can not be found...");

    getch();
    fclose(f);
}

int main()
{
    login();
    system("cls");
    int key, x, choice;
    int n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',conFlag = 'y';
    char name[50];
    FILE *fp;
    FILE *fi = fopen("D:/Code/Restaurant 2/Menu.txt", "r");
    fscanf(fi, "%d", &n);
    fgets(name, 255, fi);
    while(conFlag == 'y')
    {
        float total = 0;
        int invoiceFound = 0;
        system("cls");
        printf("\n\t\tLONGKIM RESTAURANT");
        printf("\n\n====================== OPERATION =======================");
        printf("\n1. Menu");
        printf("\n2. Order");
        printf("\n3. Bill");
        printf("\n4. Search");
        printf("\n==================== INVENTORY ====================");
        printf("\n5. Add items");
        printf("\n6. List of inventory");
        printf("\n7. Delete items");
        printf("\n8. Search items");
        printf("\n0. Exit\n");
        printf("===================================================\n");
        printf("\nYour choice:\t ");
        scanf("%d",&key);
        fgetc(stdin);
        switch(key)
        {
            case 1:
                printf("\n==================== MENU ==================\n");
                for(int i = 0; i < n; i++)
                    {
                        fgets(name, 50, fi);
                        printf("%d.%s", (i+1), name);
                    }
                printf("\n============================================\n");
                printf("\nPress any key to continue...");
                getch();
                break;
            case 2:
                system("cls");
                printf("\n===================== ORDER =====================\n");
                printf("\n Please enter the name of the customer:\t");
                fgets(ord.customer,50,stdin);
                ord.customer[strlen(ord.customer)-1] = 0;
                strcpy(ord.date,__DATE__);
                printf("\nPlease enter the number of item: \t");
                scanf("%d",&x);
                ord.numOfItems = x;

                for(int i = 0; i < x;i++)
                {
                    fgetc(stdin);
                    printf("\n\n");
                    printf("Please enter the item %d:\t", i+1);
                    fgets(ord.itm[i].item,20,stdin);
                    ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
                    printf("\nPlease enter the quantity:\t");
                    scanf("%d",&ord.itm[i].qty);
                    printf("\nPlease enter the unit price:\t");
                    scanf("%f",&ord.itm[i].price);
                    total += ord.itm[i].qty * ord.itm[i].price;
                }

                billHeader(ord.customer,ord.date);
                for(int i=0; i < ord.numOfItems;i++)
                {
                    billBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                }
                billFooter(total);

                printf("\n\nDo you want to save the invoice [y/n]:\t");
                scanf("%s",&saveBill);

                if(saveBill == 'y')
                {
                    fp = fopen("RestaurantBill.dat","ab");
                    fwrite(&ord,sizeof(struct orders),1,fp);
                    if(fwrite != 0)
                        printf("\n Successfully saved");
                    else
                        printf("\nError saving");
                    fclose(fp);
                }
                printf("\nPress any key to continue...");
                getch();
                break;
            case 3:
                printf("\nBill");
                system("cls");
                fp = fopen("RestaurantBill.dat","rb");
                printf("\n  ===================== PREVIOUS INVOICES ======================\n");
                while(fread(&order,sizeof(struct orders),1,fp))
                {
                    float tot = 0;
                    billHeader(order.customer,order.date);
                    for(int i = 0; i < order.numOfItems;i++)
                    {
                        billBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    billFooter(tot);
                }
                fclose(fp);   
                printf("\nPress any key to continue...");
                getch();
                break;
            case 4:
                printf("\n  ======================= SEARCH INVOICES =======================");
                printf("\nEnter the name of the customer: ");
                //fgetc(stdin);
                fgets(name,50,stdin);
                name[strlen(name)-1]=0;
                system("cls");
                fp = fopen("RestaurantBill.dat","rb");
                printf("\n===================== Invoices of %s ========================\n",name);
                while(fread(&order,sizeof(struct orders),1,fp))
                {
                    float tot = 0;
                    if(strcmp(order.customer,name) == 0)
                    {
                        invoiceFound = 1;
                        billHeader(order.customer,order.date);
                        for(int i = 0; i < order.numOfItems;i++)
                        {
                            billBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                            tot += order.itm[i].qty * order.itm[i].price;
                        }
                        billFooter(tot);
                    }
                    if(invoiceFound == 0)
                    {
                        printf("\nSorry the invoice for %s doesn't exists",name);
                    }
                }
                fclose(fp); 
                printf("\nPress any key to continue...");
                getch();
                break;
            case 5:
                add();
                break;
            case 6:
                list();
                break;
            case 7:
                deletel();
                break;
            case 8:
                search();
                break;
            case 0:
                printf("\nGOOD BYE! SEE YOU AGAIN!");
                getch();
                return 0;
            default:
                printf("\nSorry invalid option");
                printf("\nPress any key to continue...");
                getch();
                break;
        }
        printf("\n\nDo you want to perform another operation? [y/n]:\t");
        scanf("%s",&conFlag);
    }
    printf("\nGOOD BYE!!!");
    fclose(fi);
}
