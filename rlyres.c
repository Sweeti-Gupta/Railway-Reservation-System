#include<stdio.h>
#include "conio2.h"
#include<ctype.h>  //header file to call isDigit() to check mobile no.
#include<string.h>
#include "rlyres.h"
int enterchoice()
{
    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1;i<=80;i++)
    {
        printf("-");
    }
    printf("\nSelect an option");
    printf("\n1- View Trains");
    printf("\n2- Book Ticket");
    printf("\n3- View Ticket");
    printf("\n4- Search Ticket No");
    printf("\n5- View All Bookings");
    printf("\n6- View Train Bookings");
    printf("\n7- Cancel Ticket");
    printf("\n8-  Cancel Train");
    printf("\n9- Quit\n");
    printf("\n\nEnter choice:");
    scanf("%d",&choice);
    return choice;
}
void add_trains()
{
    Train alltrains[4]={
        {"123","BPL","GWA", 2100,1500},
        {"546","BPL","DEL",3500,2240},
        {"345","HBJ","AGR",1560,1135},
        {"896","HBJ","MUM",4500,3360},
    };
    FILE *fp=fopen("D:\\alltrains.dat","rb");
    if(fp==NULL)
    {
      fp=fopen("D:\\alltrains.dat","wb");
      fwrite(alltrains,4*sizeof(Train),1,fp);
      printf("File created and saved!\n");
      fclose(fp);
    }
    else
        printf("File already present\n");
    fclose(fp);
}
//Function to view the list of Trains available for travelling
void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    for(i=1;i<=80;i++)
    printf("-");
    FILE *fp=fopen("D:\\alltrains.dat","rb");
    Train tr;
     while(fread(&tr,sizeof(tr),1,fp)==1)
    {
          printf("\n%s\t\t%s\t%s\t%d\t\t%d ",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    printf("\n\n\n\n");
    fclose(fp);
}
//Function to validate train no input by user
int check_train_no(char *trainno)
{
    FILE *fp=fopen("D:\\alltrains.dat","rb");
     Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(tr.train_no,trainno)==0)
        {
            fclose(fp);
            return 1;
        }
    }
      fclose(fp);
      return 0;
}
//Function to validate mobile no. input by user
    int check_mob_no(char* p_mob)
    {
        if(strlen(p_mob)!=10)
            return 0;
        while(*p_mob!='\0')
        {
            if(isdigit(*p_mob)==0)
                return 0;
            p_mob++;
        }
        return 1;
}
//Function to input all the details of user for booking a ticket
Passenger* get_passenger_details()
{
    clrscr();
    gotoxy(65,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
//Taking Passenger name from user
    static Passenger psn;
    printf("Enter Passenger name:");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
        gotoxy(1,25);
        textcolor( LIGHTRED);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    //Taking Gender Input
    int valid;
    printf("Enter gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
           printf("\t\t\t\t\t\t\t");  //for clearing previous message
           gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
   if(psn.gender!='M' && psn.gender!='F')
    {
        gotoxy(1,25);
        textcolor(LIGHTRED);
        printf("Error! Gender should be M or F (in uppercase)");
        valid=0;
        getch();
        gotoxy(19,2);
        printf(" \b");
        textcolor(YELLOW);
    }

    }while(valid==0);

   gotoxy(1,25);
   printf("\t\t\t\t\t\t\t\t");  //For clearing previous message
   gotoxy(1,3);
   //Taking train no input
   printf("Enter train number:");
   do
   {
       fflush(stdin);
       scanf("%s",psn.train_no);
       if(strcmp(psn.train_no,"0")==0)
    {
        gotoxy(1,25);
        textcolor(LIGHTRED);
        printf("\t\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }
    valid=check_train_no(psn.train_no);
    if(valid==0)
    {
        gotoxy(1,25);
        textcolor(LIGHTRED);
        printf("Error! Invalid Train No");
        getch();
        gotoxy(20,3);
        printf("\t\t\t");
        gotoxy(20,3);
        textcolor(YELLOW);
    }

   }while(valid==0);
   gotoxy(1,25);
   printf("\t\t\t\t\t\t\t\t\t");

   gotoxy(1,4);
   //Taking travelling class input
   printf("Enter travelling class(First AC:F,Second AC:S):");
   do
   {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
           printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.p_class!='F' && psn.p_class!='S')
        {

            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Travelling class should be F or S (in uppercase)");
            valid=0;
            getch();
           gotoxy(48,4);
            printf(" \b");
            textcolor(YELLOW);
        }

   }while(valid==0);
   gotoxy(1,25);
   printf("\t\t\t\t\t\t\t");
   gotoxy(1,5);
//Taking address input
   printf("Enter address:");
   fflush(stdin);
   fgets(psn.address,30,stdin);
   pos=strchr(psn.address,'\n');
   *pos='\0';
   if(strcmp(psn.address,"0")==0)
   {
       gotoxy(1,25);
       textcolor(LIGHTRED);
       printf("\t\t\t\t\t\t\t");
       gotoxy(1,25);
       printf("Reservation Cancelled");
       getch();
       textcolor(YELLOW);
       clrscr();
       return NULL;
   }
//Taking age input
printf("Enter age:");
do
{
    valid=1;
    fflush(stdin);
    scanf("%d",&psn.age);
    if(psn.age==0)
    {
        gotoxy(1,25);
        textcolor(LIGHTRED);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
    }
    if(psn.age<0)
    {
        gotoxy(1,25);
        textcolor(LIGHTRED);
        printf("Error! Age should be positive");
        valid=0;
        getch();
        gotoxy(11,6);
        printf("\t\t\t");
        gotoxy(11,6);
        textcolor(YELLOW);
    }
}while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");

    gotoxy(1,7);
    //Taking mob no. input
    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
             gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Invalid Mobile No");
            getch();
            gotoxy(21,7);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(21,7);
            textcolor(YELLOW);
        }

    }while(valid==0);
    return &psn;
}
//Function to count the total no of booked tickets
int get_booked_ticket_count(char* train_no,char tc)
{
        FILE *fp=fopen("D:\\allbookings.dat","rb");;
        if(fp==NULL)
            return 0;
        Passenger pr;
        int count=0;
        while(fread(&pr,sizeof(pr),1,fp)==1)
            {
                if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
                     ++count;
            }
            fclose(fp);
            return count;
}
//Function to get last ticket no.
int last_ticket_no()
{
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
        Passenger pr;
        fseek(fp,-1L*sizeof(pr),SEEK_END);
        fread(&pr,sizeof(pr),1,fp);
        fclose(fp);
        return pr.ticketno;
}
//Function to generate ticket no. for new booking
int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==30)
    {
        textcolor(LIGHTRED);
        printf("All seats are full in train no %s in class %c!\n",p.train_no,p.p_class);
        getch();
        return -1;
    }
      int ticket_no=last_ticket_no()+1;
      p.ticketno=ticket_no;
      FILE *fp=fopen("D:\\allbookings.dat","ab");
      if(fp==NULL)
     {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        getch();
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}
//Function to input ticket no. from user
int accept_ticket_no()
{
    printf("Enter a valid ticket no: ");
    int valid;
    int ticket_no;
    do
    {
        valid=1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input....!");
            getch();
            textcolor(YELLOW);
           return 0;
        }
        if(ticket_no<0)
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Ticket number should be positive");
            getch();
            valid=0;
            gotoxy(26,1);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(26,1);
            textcolor(YELLOW);
        }

    }while(valid==0);
    return ticket_no;
}
//Function to display all the details of the ticket no. input by user
void view_ticket(int ticket_no)
{
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet");
        return;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            printf("\nNAME:%s\nGENDER:%c\nTRAIN No:%s\nCLASS:%c\nADDRESS:%s\nAGE:%d\nMOBILE NO:%s\nTICKET NO:%d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            found=1;
            break;
        }
    }
        if(!found)
        {
            textcolor(LIGHTRED);
            printf("\nNo details of the ticket no %d found!",ticket_no);
        }
        fclose(fp);
}
//Taking mob no. input
char* accept_mob_no()
{
    static char mob_no[12];
    char *pos;
    int valid;
    printf("Enter valid mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,12,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input!...");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Invalid mobile no");
            getch();
            gotoxy(27,1);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(27,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}
//Function to search a ticket no. booked with the mob no. input by user
int* get_ticket_no(char *p_mob_no)
{
    int count=0;
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
           {
               *(p+i)=pr.ticketno;
                i++;
            }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}
//To view list of ticket nos. booked with a particular mob no.
void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nSorry! No tickets booked against mobile number %s",pmob_no);
        textcolor(WHITE);
        printf("\nPress any key to go back to main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("\nFollowing tickets are booked for mobile number %s",pmob_no);
    int i;
    printf("\n\nTICKET NUMBERS\n");
    printf("-----------------------------------------------");
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
    textcolor(WHITE);
    printf("\nPress any key to go back to main screen");
    textcolor(YELLOW);
     getch();
     free(pticket_no);
}
//Function to accept train no. from user
char* accept_train_no()
{
    static char train_no[10];
    int valid;
    gotoxy(65,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",&train_no);
        if(strcmp(train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input!...");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Invalid train no");
            getch();
            gotoxy(20,1);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}
//Function to view the details of all tickets  booked in the train no. input by user
void view_booking(char* train_no)
{
    int found=0,i;
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nSorry! File cannot be opened");
        return;
    }
    Passenger pr;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=1;i<=80;i++)
        printf("-");
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
        }
    }
        if(!found)
        {
            clrscr();
            textcolor(LIGHTRED);
            printf("\nNo details of bookings in train no %s found!",train_no);
        }
        textcolor(WHITE);
        printf("\nPress any key to continue!");
        getch();
        fclose(fp);
}
//Function to view details of all the bookings in all trains
void view_all_bookings()
{
    int found=0,i;
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nSorry! File cannot be opened");
        return;
    }
    Passenger pr;
    printf("TICKET NO\tTRAIN NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOB NO\n");
    for(i=1;i<=80;i++)
        printf("-");
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
            printf("%d\t\t%s\t\t%c\t%s",pr.ticketno,pr.train_no,pr.p_class,pr.p_name);
            gotoxy(58,row);
            printf("%c\t%d   %s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
    }
        if(!found)
        {
            clrscr();
            textcolor(LIGHTRED);
            printf("\nNo bookings has been done yet in any trains");
        }
        textcolor(WHITE);
        printf("\nPress any key to continue!");
        getch();
        fclose(fp);
}
//Function to cancel a ticket no. input by user
int cancel_ticket(int ticket_no)
{
    int result;
    FILE *fp1=fopen("D:\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        printf("No bookings done yet");
        return -1;
    }
     FILE *fp2=fopen("D:\\temp.dat","ab");
     int found=0;
     Passenger pr;
     while(fread(&pr,sizeof(pr),1,fp1)==1)
     {
         if(pr.ticketno==ticket_no)
         {
             found=1;
         }
         else
         {
             fwrite(&pr,sizeof(pr),1,fp2);
         }
     }
     fclose(fp1);
     fclose(fp2);
     if(found==0)
     {
         result=remove("D:\\temp.dat");
     }
     else
     {
         result=remove("D:\\allbookings.dat");
         if(result!=0)
            return 2;
         rename("D:\\temp.dat","D:\\allbookings.dat");
     }
     return found;

}
//Function to cancel all the bookings in the train no. input by user
int cancel_train(char* trainno)
{
    int result;
    FILE *fp1=fopen("D:\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        printf("No bookings done yet");
        return -1;
    }
     FILE *fp2=fopen("D:\\temp.dat","ab");
     int found=0;
    Passenger pr;
     while(fread(&pr,sizeof(pr),1,fp1)==1)
     {
         if(strcmp(pr.train_no,trainno)==0)
         {
             found=1;
         }
         else
         {
             fwrite(&pr,sizeof(pr),1,fp2);
         }
     }
     fclose(fp1);
     fclose(fp2);
     if(found==0)
     {
         result=remove("D:\\temp.dat");
     }
     else
     {
         result=remove("D:\\allbookings.dat");
         if(result!=0)
            return 2;
         rename("D:\\temp.dat","D:\\allbookings.dat");
     }

     return found;
}
















