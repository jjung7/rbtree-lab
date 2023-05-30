// #include <stdio.h>
// #include <stdlib.h>
// int push(int data);
// int pop();
// struct node{
//     int data;
//     struct node *next;
// } node;
// struct node *head = NULL;
// struct node *tail = NULL;
// struct node *end = NULL;
// int main(){
//     int *input;
//     int a;
//     int userinput;
//     while(1){
//         printf("Exit: 0 | push: 1 | pop: 2 \n");
//         scanf("%d", &a);
//         input = &a;
//         if (*input == 0){
//             break;
//         }
//         if(*input == 1)
//         {
//             printf("what do you want to put? \n");
//             scanf("%d", &userinput);
//             push(userinput);
//         }
//         if(*input == 2){
//             pop();
//         }
//     }
//     return 0;
// }
// int push(int data1){
//     struct node *cur = (struct node*)malloc(sizeof(node));
//     cur -> data = data1;
//     struct node *lk = head;
//     while(lk->next != NULL)
//         lk = lk->next;
//     lk -> next = cur;
// }
// int pop(){
//     struct node *lk = head;
//     while(lk ->next->next != NULL)
//         lk = lk -> next;
//     lk -> next = NULL;
// }

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

int stack_push(int data);
int stack_pop();

int main() {
    int input;
    int userinput;
    while(1) {
        printf("Exit: 0 | push: 1 | pop: 2 \n");
        scanf("%d", &input);
        if (input == 0) {
            break;
        }
        if (input == 1) {
            printf("what do you want to put? \n");
            scanf("%d", &userinput);
            push(userinput);
        }
        if (input == 2) {
            pop();
        }
    }
    return 0;
}

int stack_push(int data1) {
    struct node *cur = (struct node*)malloc(sizeof(struct node));
    cur->data = data1;
    cur->next = NULL;
    if (head == NULL) {
        head = cur;
        tail = cur;
    } else {
        tail->next = cur;
        tail = cur;
    }
    return data1;
}

// int stack_pop() {
//     if (head == NULL) {
//         printf("Stack is empty\n");
//         return 0;
//     }
//     int data = tail->data;
//     if (head == tail) {
//         head = NULL;
//         tail = NULL;
//     } else {
//         struct node *cur = head;
//         while (cur->next != tail) {
//             cur = cur->next;
//         }
//         cur->next = NULL;
//         tail = cur;
//     }
//     printf("%d\n", data);
//     return data;
// }
