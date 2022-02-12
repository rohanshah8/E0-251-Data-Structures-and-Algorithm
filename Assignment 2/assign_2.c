/*
 main() is drive function 
 other functions:
 add -> add 2 Linkedlist
 mul -> multiply 2 Linkedlist
 input_LL -> take input number and convert to Linkedlist
 print_LL -> print Linkedlist in proper format
 dynamic_input -> take input as expression and evalute it in Left to right then prints the result 
 extra_dynamic_input -> same as above function but consider priority of operator

 for output check screenshot of running code

*/

#include<stdio.h>
#include<stdlib.h>
#define MAX_LIMIT 1000

// A linked list node
struct Node {
    int data;
    struct Node* next;
};
//returns new node address
struct Node* newNode(int data)
{
    struct Node* new_node =
        (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

//add 2 linkedlist and return linkedlist first node address
struct Node* add(struct Node* a,struct Node* b){
    struct Node* fhead=NULL;
    struct Node* shead=NULL;
    int carry=0;
    while(a || b){
        int sum=0;
        if(a){
            sum=a->data;
            a=a->next;
        }
        if(b){
            sum+=b->data+carry;
            carry=sum/1000;
            sum=sum%1000;
            b=b->next;
        }
        if(!fhead){
            fhead=newNode(sum);
            shead=fhead;
        }
        else{
            shead->next=newNode(sum);
            shead=shead->next;
        }
    }
    if(carry)
        shead->next=newNode(carry);
    return fhead;
}

//mul 2 linkedlist and return linkedlist first node address
struct Node* mul(struct Node* a,struct Node* b){
    struct Node* fhead=NULL;
    struct Node* chead=NULL;
    struct Node* shead=NULL;
    int carry=0;
    // if one number is zero so mul is zero
    if((a->data==0 && a->next==NULL) || (b->data==0 && b->next==NULL))
        return newNode(0);
    // if b is single digit single node then swap(a,b)
    if(b->data/10==0 && b->next==NULL){
        struct Node* t=a;
        a=b;b=t;
    }
    
    while(a){
        struct Node* temp=b;
        int k=a->data;
        int carry=0;
        // multiply one node of a to b
        while(temp){
            int m=k*temp->data+carry;
            carry=m/1000;
            if(!fhead){
                fhead=newNode(m%1000);
                shead=fhead;chead=fhead;
            }
            else if(shead->next==NULL){
                shead->next=newNode(m%1000);
                shead=shead->next;
            }
            else{
                m=shead->next->data+m;
                carry=m/1000;
                shead->next->data=m%1000;
                shead=shead->next;
            }
            temp=temp->next;
        }
        if(carry){
            if(shead->next){
                shead=shead->next;
                shead->data+=carry;
                carry=shead->data/1000;
                shead->data%=1000;
                if(carry)
                    shead->next=newNode(carry);

            }
            else{
                shead->next=newNode(carry);
            }
        }
        a=a->next;
        
        shead=chead;
        chead=chead->next;
    }
    
    return fhead;
}

//convert string into linklist of our number
struct Node* input_LL(char *str){
   
   struct Node* prev=NULL,*curr=NULL;
   int i=0;
   while(str[i]!='$'){
       // 48 is ascii code for 0 digit
       int temp=(str[i]-48)*100 + (str[i+1]-48)*10 + (str[i+2]-48)*1;
       curr=newNode(temp);
       curr->next=prev;
       prev=curr;

       if(str[i+3]==',')
        i=i+4;
       else if(str[i+3]=='$')
        i=i+3; 
   }
   return curr;
    
}

//stdout output the linkedlist as number , using recursive approach 
// taking 2 nodes as input in function which are both same and for purpose of putting ',' between  digit
void print_LL(struct Node* a,struct Node* b){
    if(a==NULL)
        return;
    print_LL(a->next,b);
    //checking if number is not like this 000,...,XXX,XXX$  starting with zeros
    if(a!=b && a->data==0 && a->next==NULL)
        return;
    //putting 00X
    if(a->data/10==0)
        printf("00");
    //putting 0XX
    else if(a->data/100==0)
        printf("0");
    
    printf("%d",a->data);
    if(a != b)
        printf(",");    
}

// for expression this consider priority of operator also ( expression evalution tree using 2 stack )
int extra_dynamic_input(int count){
    char expression[MAX_LIMIT];
    printf("\nEnter Expression No. %d\n",count);
    fgets(expression, MAX_LIMIT, stdin);
    int i=0;
    struct Node* stack[20];int top=-1;
    char op_stack[20];int op_top=-1;
    while(expression[i]!='='){
        char operand[MAX_LIMIT];int j=0;
        //operand
        while(expression[i]!='$'){
            operand[j++]=expression[i++];
        }
        operand[j++]=expression[i++];
        // convert operand to linked list
        stack[++top]=input_LL(operand);
        //putting + operator by looking top of stack becasue of priority of *
        if(expression[i]=='+'){
            while(op_top!=-1 && op_stack[op_top]=='*'){
                struct Node* head1=stack[top--];
                struct Node* head2=stack[top--];
                stack[++top]=mul(head1,head2);
                op_top--;
            }
            //printf("OP_TOP == %d ",op_top);
            op_stack[++op_top]=expression[i++];
        }
        // * has higher priority
        else if(expression[i]=='*')
            op_stack[++op_top]=expression[i++];
    }
    while(op_top!=-1){
        if(op_stack[op_top--]=='+'){
                struct Node* head1=stack[top--];
                struct Node* head2=stack[top--];
                stack[++top]=add(head1,head2);
        }
        else{
                struct Node* head1=stack[top--];
                struct Node* head2=stack[top--];
                stack[++top]=mul(head1,head2);
        }
    }
    if(top!=-1)
        print_LL(stack[top],stack[top]);
    else
        return 0;
    return 1;
}

int valid_input(char exp[MAX_LIMIT]){
    int i=0;
    while(exp[i]!='='){
        if(exp[i]>='0' && exp[i]<='9' && exp[i+1]>='0' && exp[i+1]<='9' && exp[2+i]>='0' && exp[i+2]<='9' )
            i=i+3;
        else
            return 0;
        if(exp[i]==','){
            i++;continue;
        }
        else if(exp[i]=='$'){
            i++;
            if(exp[i]=='+' || exp[i]=='*')
                i++;
            else if(exp[i]=='=')
                continue;
            else
                return 0;
        }
    }
    if(exp[i+1]!='\n')
        return 0;
    return 1;
}
//take expression , solves and print answer
int dynamic_input(int count){
    char expression[MAX_LIMIT];
    printf("\nEnter Expression No. %d\n",count); 
    fgets(expression, MAX_LIMIT, stdin);
    int i=0;
    // i have used stack but it's just like array and size of it only 2 for operands  or think of 2 node pointer
    struct Node* stack[20];int top=-1;
    char op_stack=' ';
    //input is valid input or not
    if(!valid_input(expression)){
        printf("Invalid Input");
        return 1;
    }
    while(expression[i]!='='){
        char operand[MAX_LIMIT];int j=0;
        //single operand
        while(expression[i]!='$'){
            operand[j++]=expression[i++];
        }
        operand[j++]=expression[i++];
        // convert operand to linked list and store in stack
        stack[++top]=input_LL(operand);
        //doing operation + or *
        if(op_stack!=' '){
            if(op_stack=='*')
                stack[0]=mul(stack[0],stack[1]);
            else
                stack[0]=add(stack[0],stack[1]);
            stack[1]=NULL;
            op_stack=' ';
            top=0;
        }
        //store next operator
        if(expression[i]=='*' || expression[i]=='+')
            op_stack=expression[i++];
    }
    if(op_stack!=' '){
            if(op_stack=='+'){
                stack[0]=add(stack[0],stack[1]);
            }
            else{
                stack[0]=mul(stack[0],stack[1]);
            }
            top=0;
        }
    if(top!=-1){
        printf("Result : ");
        print_LL(stack[0],stack[0]);
        printf("$\n");
    }
    else
        return 0;
    return 1;
}


int main(){
    
    printf("Rules : \n(1) 1000 base-Number (eg. xxx,xxx) \t(2) Ends with '$' (eg. xxx$) \t(3) Expression end with '=' \n");
    //getchar();
    
/*
    (a) addition and multiplication of 2 number demo
    printf("\nEnter first Number : ");
    char str[MAX_LIMIT];
    fgets(str, MAX_LIMIT, stdin);
    struct Node* head1=input_LL(str);

    printf("Enter second Number : ");
    fgets(str, MAX_LIMIT, stdin);
    struct Node* head2=input_LL(str);

    printf("Multiplication :  ");
    struct Node* m=mul(head1,head2);
    print_LL(m,m);

    printf("\nSum :  ");
    struct Node* sum=add(head1,head2);
    print_LL(sum,sum);

    (b) taking input in desired format
    printf("\nEnter first Number : ");
    char str[MAX_LIMIT];
    fgets(str, MAX_LIMIT, stdin);
    struct Node* head1=input_LL(str);

    (c) showing output in desired format
    print_LL(head1,head1);
*/

    printf("\n---------------------------------------------------------------------------------\n");

//  (d) Expression evalution
    int count=1;
    while(dynamic_input(count++)){
        printf("\n---------------------------------------------------------------------------------\n");
    }
    return 0;
}