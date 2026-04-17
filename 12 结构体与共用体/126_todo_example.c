#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char task[100];
    struct Node* next;
} Node;

void insert_at_head(Node* head, char task[]) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("内存分配失败\n");
        return;
    }

    strcpy(new_node->task, task);
    new_node->next = head->next;
    head->next = new_node;
}

void insert_at_tail(Node* head, char task[]) {
    Node* new_node  = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("内存分配失败\n");
        return;
    }

    strcpy(new_node->task, task);
    new_node->next = NULL;

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void insert_at_position(Node* head, char task[], unsigned int pos) {
    Node* current = head; 
    int count = 0;
    while(current != NULL && count < pos) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        printf("插入位置无效！\n");
        return;
    }

    Node* new_node  = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("内存分配失败\n");
        return;
    }
    strcpy(new_node->task, task);
    new_node->next = current->next;
    current->next = new_node ;
}

void traverse_list(Node* head) {
    Node* current = head->next;
    while (current!= NULL) {
        printf("待办：%s\n", current->task);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node* head = (Node*)malloc(sizeof(Node)); 
    if (head == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    strcpy(head->task, "");
    head->next = NULL;

    insert_at_head(head, "学1小时C语言");
    traverse_list(head);
    insert_at_tail(head, "学1小时Python");
    traverse_list(head);
    insert_at_position(head, "学1小时数据分析", 1);
    traverse_list(head);

    free_list(head);
}