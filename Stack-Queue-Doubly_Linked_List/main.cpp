
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

// The size of the arrays for queues and stacks.
int s;

// defining the output files.
ofstream out1("task1.out");
ofstream out2("task2.out");
ofstream out3("task3.out");

                                                         /* Stack implementation */
//function to add an element into the stack
void push(int n, int *top,int *sto,int s) 
{ 
  if(*top==s-1) {out1<<"overflow"<<endl;return;}
  else
  {
    *top = *top +1;
    sto[*top]=n;
    out1<<"pushed "<<n<<endl;
  }
}
// function to pop out an element from the stack
void pop(int *top, int st[]) 
{
  if(*top==-1){out1<<"underflow"<<endl;return;}
  else
  {
    out1<<"popped "<<st[*top]<<endl;
    *top=*top-1;
  }
}
// function to search a given element in the stack.
void fid(int n,int top,int sto[]) 
{
  for(int h=0;h<=top;h++){if(sto[h]==n){out1<<"found "<<n<<endl;return;}}
  out1<<"not found "<<n<<endl;return;
}
// function to print the elements present in the stack.
void print(int top, int sto[]) 
{
  if(top==-1){out1<<endl;return;} // if there are no elements in the stack..then it prints a blank line.
  for(int h=top;h>=0;h--){out1<<sto[h]<<" ";}
  out1<<endl;
  return;
}
                                                         /* Queue implementation */
// we'll need to modify the array and the member size...so taking by reference.
void enqueue(int *que, int head, int &mem, int n)
{
  if(mem==s){out2<<"overflow"<<endl;}
  else
  {
    que[(head + mem)%s]=n;
    out2<<"enqueued "<<n<<endl; // we'll add it at the head plus mem poosition. mem can be max (s-1).
    mem++; // head will be the same.
  }
}

void dequeue(int *que, int &head, int &mem)
{
  if(mem == 0){out2<<"underflow"<<endl;}
  else
  {
    out2<<"dequeued "<<que[head]<<endl;
    head = (head + 1)%s;
    mem--;
  }
}

void printque(int *que,int head, int mem)
{
  if(mem==0){out2<<endl;}
  else
  {
    for(int i=0;i<mem;i++)
    {
      out2<<que[(head + i)%s]<<" ";
    }
    out2<<endl;
  }
}

void findque(int *que, int head, int mem, int n)
{
 for(int i=0;i<mem;i++)
 { //out3<<que[(head + i)%s]<<endl;
  if(que[(head + i)%s]==n){out2<<"found "<<n<<endl;return;}
 }
out2<<"not found "<<n<<endl;return;
}

                                                     /* Doubly linked list implementation */

class node
{
 public:
  int data;
  node *prev;
  node *next;

  node() {
    prev = NULL;
    next = NULL;
  }
};

node *root = NULL; // the pointer which is the head of the list. ... defining it as a global variable.

void insertdll(node **root, int n) // note that it is by reference.
{
  node *temp1 = *root;
  node *temp = new node;
  temp->prev = NULL;
  temp->next = *root;
  temp->data = n;
  if(*root!=NULL){temp1->prev=temp;}
  *root=temp;
  out3<<"inserted "<<n<<endl;
}

void removedll(node **root, int n) // pointer by reference.
{
  if(*root==NULL){out3<<"cannot delete "<<n<<endl;return;}

  node *temp = *root;
  if(temp->data == n)
  {
    if(temp->next==NULL){
      delete temp;
      *root = NULL;
      out3<<"deleted "<<n<<endl;
      return;
    }
    temp->next->prev = NULL;
    *root = temp->next;
    delete temp;
    out3<<"deleted "<<n<<endl;
    return;
  }

  node *temp1 = temp->next;
  while(temp1!=NULL)
  {
    if(temp1->data == n)
    {
      temp1->prev->next = temp1->next;
      if(temp1->next!=NULL) temp1->next->prev = temp1->prev; // if the deleted element was the last one!
      delete temp1;
      out3<<"deleted "<<n<<endl;
      return;
    }
    temp1=temp1->next;
  }
  out3<<"cannot delete "<<n<<endl;
}

void printdll(node *root) // here it is pointer passing by value.
{
  //if(root==NULL){out3<<endl;return;}
  node *temp = root;
  while(temp!=NULL)
  {
    out3<<temp->data<<" ";
    temp=temp->next;
  }
  out3<<endl;
  return;
}

void finddll(node *root, int n)
{
  node *temp = root;
  while (temp!=NULL)
  {
    if(temp->data==n){out3<<"found "<<n<<endl;return;}
    temp=temp->next;
  }
  out3<<"not found "<<n<<endl;
}

int main(int argc, char * argv[]) // should include command line arguements.
{

                                                        /*stack variables.*/
 int top=-1;
 string si = argv[2];
 s = stoi(si);

 int sto[s];

 //defining functions...
 void push(int n, int *top,int *sto,int s);
 void pop(int *top, int sto[]);
 void fid(int n,int top,int sto[]);
 void print(int top, int sto[]);

                                                        /*queue variable.*/
 int que[s]; // for the queue.
 int head =0;
 int mem=0;

 void enqueue(int *que, int head, int &mem, int n); // to add an element.
 void dequeue(int *que, int &head, int &mem); // to remove and element.
 void printque(int *que, int head, int mem); // to print out the queue.
 void findque(int *que, int head, int mem, int n); // to find the given element.


 //string line; // not needed

 ifstream myfile (argv[1]);
 if (myfile.is_open())
  {
    char ch;
    int n;

	  while(myfile>>ch) // this is better than myfile.eof() ...this one is not suggested to use.
    {
      if(ch=='!')
      { 
        //Stack implementation
        print(top,sto);//place this continue at the end of the block.
        //Queue implementation
        printque(que,head,mem);
        // Double linked list implementation
        printdll(root);
        continue;
      }
      myfile>>n;

      if(ch=='+')
      { 
        //Stack implementation
        push(n,&top,sto,s);
        //Queue implementation
        enqueue(que,head,mem,n);
        //Double linked list implementation
        insertdll(&root,n); //here we are passing the pointer by reference...we can change the pointer as well as the variable stored in its address.
      }
      else if(ch=='-')
      { //Stack implementation
        pop(&top, sto);
        //Queue implementation
        dequeue(que, head, mem);
        //Double linked list inplementation
        removedll(&root,n);
      }

      else
      {
        //Stack implementation.
        fid(n,top,sto);
        //Queue implementation.
        findque(que, head, mem, n);
        //Double linked list implementation
        finddll(root, n); // here we will be able to change only the variable stored in the address not the pointer.
      }
    }
  }
}
