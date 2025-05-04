#include<iostream>
#include<string.h>
using namespace std;

struct node
{
int data,prior;
char pnm[10],name[10];
struct node *next;
}*front,*rear;
class Queue
{
public:
int isempty();
void pq_insert(int prior,char name[10]);
void display();
void p_delete();
};
int Queue::isempty()
{
if((rear=front)==NULL)
{
return 1;
}
return 0;
}
struct node *createnode(int prior,char name[10])
{
struct node *temp;
temp=new node;
strcpy(temp->pnm,name);
temp->prior=prior;
temp->next=NULL;
return temp;
}
void Queue::pq_insert(int prior,char name[10])
{
int i;
struct node *temp;
temp=createnode(prior,name);
if(isempty())
{
front=rear=temp;
}
else if(front->prior > temp->prior)
{
temp->next=front;
front=temp;
}
else
{
rear=front;
while(rear->next!=NULL && temp->prior >= rear->next->prior)
{
rear=rear->next;
}
temp->next=rear->next;
rear->next=temp;
}
}
void Queue::display()
{
struct node *temp;
cout<<"priority \t name \t\t patient name"<<endl;
for(temp=front;temp!=NULL;temp=temp->next)
{
if(temp->prior==1)
cout<<temp->prior<<"\t \t serious\t\t"<<temp->pnm<<endl;
if(temp->prior==2)
cout<<temp->prior<<"\t \t medium \t \t"<<temp->pnm<<endl;
if(temp->prior==3)
cout<<temp->prior<<"\t \t normal \t \t"<<temp->pnm<<endl;
}
}
void Queue::p_delete()
{
struct node *temp;
temp=front;
front=front->next;
temp->next=NULL;
cout<<"\n"<<temp->pnm<<" patient checked successfully \n "<<endl;
delete temp;
display();
}
int main()
{
int priority,i,ch,n;
int ans,patient_no;
char name[10];
Queue q;
do
{
cout<<"\n hospital history";
cout<<"\n 1.enter the record u want";
cout<<"\n 2.display";
cout<<"\n 3.delete";
cout<<"\n enter ur choice";
cin>>ch;
switch(ch)
{
case 1:
cout<<"\n 1.serious";
cout<<"\n 2.medium";
cout<<"\n 3.normal";
cout<<"\n enter no of patient";
cin>>n;
for(i=0;i<n;i++)
{
cout<<"\n enter severity=";
cin>>priority;
cout<<"\n enter patient name=";
cin>>name;
q.pq_insert(priority,name);
}
break;
case 2:
q.display();
break;
case 3:
q.p_delete();
break;
case 4:
cout<<"\n wrong choice";
cin>>ch;
break;
}
cout<<"\n Do u want to continue?";
cin>>ans;
}while(ans==1);
return 0;
}

