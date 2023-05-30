#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

int queue_push(int data1);
int queue_pop();

int main(){
    int input;
    int num;
    
    while(1){
        printf("EXIT: 0 | PUSH: 1 | POP: 2 \n");
        scanf("%d", &input);
        if (input==0){
            break;
        }
        else if(input == 1){
            printf("What dou you want to put? \n");
            scanf("%d",&num);
            queue_push(num);
        }
        else if(input == 2){
            queue_pop();
        }
    }
}
int queue_push(int data1){
    struct node *cur = (struct node*)malloc(sizeof(struct node));
    cur-> data = data1;
    cur-> next = NULL;
    if(head == NULL){
        head = cur;
        tail = cur;
    }
    else{
        tail->next = cur;
        tail = cur;
    }
    return data1;
}
int queue_pop(){
    if (head == NULL){
        printf("queue is empty \n");
        return 0;
    }
    int data = head -> data;
    if(head == tail){
        head = NULL;
        tail = NULL;
    }
    else{
        head = head -> next;
    }
    printf("%d \n", data);
    return data;
}