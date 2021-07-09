#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BITS 65535
typedef struct {
    char op;
    int index;
} Node;
Node* stack[BITS];
int top = 0;
int stack_push(Node* stack[], Node* node){
    if(top < BITS - 1)
        stack[top++] = node;
    else{
        printf("Stack overflown\n");
        exit(1);
    }
}
Node* stack_pop(Node* stack[]){
    if(top > 0)
        return stack[--top];
    else{
        printf("Stack size is negative\n");
        exit(1);
    }
}
int parser(char*);
int interpreter(FILE* fp, char*);
int main(int argc, char* argv[]) {
    if(argc == 2){
        char* filename = argv[1];
        parser(filename);
    }else{
        printf("Usage: bfc INPUT.bf or bfc OUTPUT.b\n");
        exit(1);
    }
}
int parser(char* filename){
    FILE* fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error: Cannot open %s, please check whether the file exists.\n", filename);
        exit(1);
    }
    char ptr[BITS];
    int i;
    for(i=0;i<BITS;i++){
        ptr[i] = '\0';
    }
    interpreter(fp, ptr);
}
int interpreter(FILE *fp, char *ptr){
    char op;
    Node *loop_start, *loop_end;
    int comment = 0;
    while(fscanf(fp, "%c", &op) != EOF){
        // printf("code = %c\n", op);
        switch(op){
            case '>':
                ptr++;
                break;
            case '<':
                ptr--;
                break;
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
            case '.':
                printf("%d\n", *ptr);
                break;
            case ',':
                *ptr = getchar();
                break;
            case '[':
                loop_start = malloc(sizeof(Node));
                loop_start->op = '[';
                loop_start->index = ftell(fp) - 1;
                stack_push(stack, loop_start);
                break;
            case ']':
                loop_end = stack_pop(stack);
                if(*ptr != 0){
                    // printf("stack pos: %d\n", loop_end->index);
                    fseek(fp, loop_end->index, SEEK_SET);
                }
                break;
            case '/':
                comment++;
                if(comment == 2){
                    comment = 0;
                    while(op != '\n' && fscanf(fp, "%c", &op) != EOF);
                }
        }
    }
}