
#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *right;
    struct node *left;
};
struct node *root = NULL;

int insert(int data1);
int delete(int data1);
int find(int data1);

int main(){
    int input;
    int insert_input;
    int find_input;
    int delete_input;
    
    while(1){
        printf("EXIT: 0 | Insert: 1 | Find: 2 | Delete: 3 \n");
        scanf("%d", &input);
        if(input == 0){
            break;
        }
        else if(input == 1){
            printf("Enter number:");
            scanf("%d", &insert_input);
            insert(insert_input);
        }
        else if (input == 2){
            printf("Enter number:");
            scanf("%d", &find_input);
            find(find_input);
        }
        else if (input == 3){
            printf("Enter number:");
            scanf("%d", &delete_input);
            delete(delete_input);
        }
}
    return 0;
}
int insert(int data1){
    struct node *cur  = (struct node*)malloc(sizeof(struct node));
    struct node *lk = root;
    cur -> right = NULL;
    cur -> left = NULL;
    cur -> data = data1;
    if (root == NULL){
        root = cur;
        return data1;
    }
    else{
        while(1){
            if(lk->data > data1){
                if(lk->left == NULL){
                    lk -> left = cur;
                    return data1;
                }
                else{
                    lk = lk->left;
                }    
            }
            else if(lk -> data <data1){
                if(lk->right == NULL){
                    lk->right = cur;
                    return data1;
                }
                else{
                    lk = lk -> right;
                }
            }
            else{
                printf("data already exsits\n");
                return -1;
            }   
            }
    }
}
int find(int data1){
    struct node *lk = root;
    while(1){
        if (lk == NULL){
            printf("NO NUMBER\n");
            return -1;
        }
        else if(lk -> data == data1){
            printf("There is %d in the list \n", data1);
            return data1;
        }
        else if(lk ->data > data1){
            lk = lk -> left;
        }
        else if(lk -> data < data1){
            lk = lk -> right;
        }
    }
}
int delete(int data1){
    struct node *lk = root;
    struct node *pointer = NULL;
    struct node *parent = NULL;
    int data2;
    
    while(lk != NULL){
        if(lk->data == data1){
            data2 = lk->data;
            
            // Case 1: No child nodes
            if(lk->left == NULL && lk->right == NULL){
                if(parent == NULL){
                    root = NULL;
                }
                else if(parent->left == lk){
                    parent->left = NULL;
                }
                else{
                    parent->right = NULL;
                }
                printf("You deleted %d\n", data2);
                free(lk);
                return data2;
            }
            // Case 2: One child node
            else if(lk->left == NULL){
                if(parent == NULL){
                    root = lk->right;
                }
                else if(parent->left == lk){
                    parent->left = lk->right;
                }
                else{
                    parent->right = lk->right;
                }
                printf("You deleted %d\n", data2);
                free(lk);
                return data2;
            }
            else if(lk->right == NULL){
                if(parent == NULL){
                    root = lk->left;
                }
                else if(parent->left == lk){
                    parent->left = lk->left;
                }
                else{
                    parent->right = lk->left;
                }
                printf("You deleted %d\n", data2);
                free(lk);
                return data2;
            }
            // Case 3: Two child nodes
            else{
                pointer = lk->right;
                while(pointer->left != NULL){
                    pointer = pointer->left;
                }
                data2 = pointer->data;
                lk->data = data2;
                data2 = delete(data2);
                printf("You deleted %d\n", data2);
                return data2;
            }
        }
        else if(lk->data > data1){
            parent = lk;
            lk = lk->left;
        }
        else{
            parent = lk;
            lk = lk->right;
        }
    }
    printf("No number to delete\n");
    return -1;
}

// int delete(int data1){
//     struct node *lk = root;
//     struct node *pointer = root;
//     int data2;
//     while(1){
//     //     if (lk-> data == data1){
//     //         data2 = lk->data;
//     //         printf("you delete %d \n", data2);
//     //         lk = NULL;
//     //         return data2;
//     //     }
//             if(lk -> right-> data == data1){
//             if (lk->right-> left == NULL && lk -> right-> right == NULL){
//                 data2 = lk->right->data;
//                 lk -> right = NULL;
//                 printf("you delete %d \n", data2);
//                 return data2;
//             }
//             else if(lk->right-> left == NULL || lk -> right->right == NULL){
//                 data2 = lk->right->data;
//                 if(lk->right->left != NULL){
                    
//                     lk->right = lk->right->left;
//                 }
//                 else{
//                     lk->right = lk->right->right;
//                 }
//                 printf("you delete %d \n", data2);
//                 return data2;
//             }
//             else{
//                 data2 = lk->right->data;
//                 pointer = lk-> right;
//                 while (pointer->left->left != NULL){
//                     pointer = pointer->left;
//                 lk->right = pointer->left;
//                 pointer->left = NULL;
//                 printf("you delete %d \n", data2);
//                 return data2;
//                 }
//             }
//         }
//         else if(lk -> left -> data == data1){
//             data2 = lk->left->data;
//             if (lk->left-> left == NULL && lk -> left-> right == NULL){
//                 lk -> left = NULL;
//                 printf("you delete %d \n", data2);
//                 return data2;
//             }
//             else if(lk->left-> left == NULL || lk -> left->right == NULL){
//                 if(lk->left->left != NULL){
//                     lk->left = lk->left->left;
//                 }
//                 else{
//                     lk->left = lk->left->right;
//                 }
//                 printf("you delete %d \n", data2);
//                 return data2;
//             }
//             else{
//                 pointer = lk-> left;
//                 while (pointer->right->right != NULL){
//                     pointer = pointer->right;
//                 lk->left = pointer->right;
//                 pointer->right = NULL;
//                 }
//                 printf("you delete %d \n", data2);
//                 return data2;
//             }
//         }
//         else if(lk ->data > data1){
//             lk = lk -> left;
//         }
//         else if(lk -> data < data1){
//             lk = lk -> right;
//         }
//         else{
//             printf("No number to delete \n");
//             return -1;
//         }
//     }
// }
// int delete(int data1){
//     struct node *lk = root;
//     struct node *parent = NULL;
//     int data2;
//     while(1){
//         if (lk ==NULL){
//             printf("No number to delete \n");
//             return  -1;
//         else if(parent == NULL){
//             data2 = root-> data;
//             printf(data2);
//             root = NULL;
//             return data2
//         }
//         else if(lk -> data == data1){
//             if (lk-> left == NULL && lk -> right == NULL)
//                 data2 = lk -> data;
//                 printf(data2);

                
//             //자식이 없을때
//             else if(lk->left==NULL || lk->right == NULL)
//             //자식이 한개있을때
//             else if(lk->left !=NULL && lk->right != NULL){

//             }
//             //자식이 두개있을때
            
//         }
//         else if(lk -> data > data1){
//             parent = lk;
//             lk = lk->left;
//         }
//         else if(lk-> data < data1){
//             parent = lk;
//             lk = lk->right;
//         }
//         }
//     }

      
//     return data1;
// }
