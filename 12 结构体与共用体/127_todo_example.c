#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char task[100];
    struct Node* next;
} Node;
void insert_at_head(Node** head, char task[]) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("内存分配失败\n");
        return;
    }
    strcpy(new_node->task, task);   
    new_node->next = *head; 
    *head = new_node;
}
void insert_at_tail(Node** head, char task[]) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("内存分配失败\n");
        return;
    }
    strcpy(new_node->task, task);
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}
void insert_at_position(Node** head, char task[], unsigned int pos) {
    if (pos == 0) {
        insert_at_head(head, task);
        return;
    }
    Node* current = *head;
    int count = 0;
    while(current != NULL && count < pos - 1) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        printf("插入位置无效！\n");
        return;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("内存分配失败\n");
        return;
    }
    strcpy(new_node->task, task);
    new_node->next = current->next;
    current->next = new_node;
}
void traverse_list(Node* head) {
    Node* current = head;
    while (current!= NULL) {
        printf("待办：%s\n", current->task);
        current = current->next;
    }
    printf("\n");
}
void delete_first(Node** head) {
    if (*head == NULL) {
        printf("未找到目标结点\n");
        return;   
    } 
    Node* temp = *head;
    *head = temp->next;
    free(temp); 
}
void delete_last(Node** head) {
    if (*head == NULL) {
        printf("未找到目标结点\n");
        return;   
    } 
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    Node* temp = current->next;
    current->next = NULL;
    free(temp);
}
void delete_node(Node** head, char target[]) {
    if (*head == NULL) {
        printf("未找到目标结点\n");
        return;   
    } 
    if (strcmp((*head)->task, target) == 0) {
        delete_first(head);
        return;
    }
    Node* current = *head;
    while (current->next != NULL && strcmp(current->next->task, target) != 0) {
        current = current->next;
    }
    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);   
    }
    else {
        printf("未找到目标结点\n");
    }
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
    Node* head = NULL;
    insert_at_head(&head, "学1小时C语言");
    traverse_list(head);
    insert_at_tail(&head, "学1小时Python");
    traverse_list(head);
    insert_at_position(&head, "学1小时数据分析", 1);
    traverse_list(head);
    insert_at_tail(&head, "学1小时C语言");
    insert_at_tail(&head, "学1小时Python");
    insert_at_tail(&head, "学1小时数据分析");
    traverse_list(head);
    delete_first(&head);
    traverse_list(head);
    delete_last(&head);
    traverse_list(head);
    delete_node(&head, "学1小时数据分析");
    traverse_list(head);
    
    free_list(head);
}