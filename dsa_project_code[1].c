

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char mobilename[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *headc = NULL,*newnode,*tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

void adminmenu()
{
    printf("\n1. View total sales\n");
    printf("2. Add new mobile in the order menu\n");
    printf("3. Delete mobiles from the order menu\n");
    printf("4. Display order menu\n");
    printf("5. Back To Main Menu \n\n");
    printf("Enter Your Choice --->");
}

void customermenu()
{
    printf("\n1. Place your order\n");
    printf("2. View your ordered mobile\n");
    printf("3. Delete an mobiles from order\n");
    printf("4. Display final bill\n");
    printf("5. Back To Main Menu \n\n");
    printf("Enter Your Choice --->");
}

struct node* createadmin(struct node *head,int data, char mobilename[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->mobilename,mobilename);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        heada = taila = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}

struct node* createcustomer(struct node *head,int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;
    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;
        strcpy(newnode->mobilename,temp1->mobilename);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if(temp==NULL)
            headc = tailc = newnode;
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }


    }
    else
    {
        printf("\nThis mobile is not present in the menu!\n");
    }
    return headc;
}

void displayList(struct node *head)
{
    struct node *temp1 = head;
    if(temp1==NULL)
    {
        printf("\nList is empty!!\n\n");
    }
    else
    {
        printf("\n");
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)
                printf("%d\t%s\t%0.2f\n",temp1->data,temp1->mobilename,temp1->price);
            else
            {
                printf("%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->mobilename,temp1->quantity,temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }

}

struct node* totalsales(int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->mobilename,temp1->mobilename);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = headc;
    while(temp!=NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* delete(int data,struct node *head, struct node* tail)
{
    if(head==NULL)
    {
        printf("\n List is empty\n");
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteadmin()
{
    printf("\nEnter serial no. of the mobile name which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=heada;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            heada = delete(num, heada, taila);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

int deletecustomer()
{
    printf("\nEnter serial no. of the mobile name which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=headc;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            headc = delete(num, headc, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

void displaybill()
{
    displayList(headc);
    struct node *temp = headc;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }

    printf("\t\tTotal price: %0.02f\n",total_price);

}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin()
{
    printf("\n|-----------------------------------------------------------|\n");
    printf("|                    ADMIN SECTION                          |");
    printf("\n|-----------------------------------------------------------|\n");
    while(1)
    {
        adminmenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(head_s);
                break;
            case 2:

                printf("\nEnter serial no. of the mobile name: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);

                struct node *temp = heada;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        printf("\nmobile name with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)
                    break;

                printf("Enter mobile name: ");
                scanf("%s",name);
                printf("Enter price: ");
                scanf("%f",&price);
                heada = createadmin(heada, num, name, price);
                printf("\nNew mobile is added to the list!!\n\n");
                break;
            case 3:
                if(deleteadmin())
                {
                    printf("\n### Updated list of Mobiles menu ###\n");
                    displayList(heada);
                }
                else
                    printf("\nmobile name with given serial number doesn't exist!\n\n");

                break;
            case 4:
                printf("\n### Order menu ###\n");
                displayList(heada);
                break;

            default:
                printf("\nWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}

void customer()
{
    int flag=0,j=1;
    char ch;
    printf("\n|--------------------------------------------------------|\n");
    printf("|                 CUSTOMER SECTION                       |");
    printf("\n|--------------------------------------------------------|\n");
    while(1)
    {
        customermenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(heada);
                printf("\nEnter number corresponding to the mobile you want to order: ");
                int n;
                scanf("%d",&n);
                printf("Enter quantity: ");
                int quantity;
                scanf("%d",&quantity);
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                printf("\n### List of ordered mobiles ###\n");
                displayList(headc);
                break;
            case 3:
                if(deletecustomer())
                {
                    printf("\n### Updated list of your ordered mobiles name ###\n");
                    displayList(headc);
                }
                else
                    printf("\nmobile name with given serial number doesn't exist!!\n");
                break;
            case 4:
                calculatetotsales();
                printf("\n### Final Bill ###\n");
                displaybill();
                headc = deleteList(headc);
                printf("\nPress any key to return to main menu:\n");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                printf("\nWrong Input !! PLease choose valid option\n");
                break;
        }
        if(flag==1)
            break;
    }
}

void mainnenu()
{
    printf("\n|**************************************************************************|");
    printf("\n|                         WELCOME TO MOBILE STORE                          |");
    printf("\n|**************************************************************************|");
    printf("\n|                         1. ADMIN SECTION-->                              |");
    printf("\n|                         2. CUSTOMER SECTION-->                           |");
    printf("\n|                         3. Exit-->                                       |");
    printf("\n|**************************************************************************|\n\n");
    printf("Enter Your Choice --->");
}

int main()
{
    heada = createadmin(heada,1,"Apple",130000);
    heada = createadmin(heada,2,"Samsung",85000);
    heada = createadmin(heada,3,"One plus",50000);
    heada = createadmin(heada,4,"Redmi",25000);
    heada = createadmin(heada,5,"Oppo",20000);

    while(1)
    {
        mainnenu();
        int choice;
        scanf("%d",&choice);

        if(choice==3)
        {
            printf("\n\n**********Thank you!!**********\n");
            break;
        }

        switch (choice)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;

            default:
                printf("\nWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}
