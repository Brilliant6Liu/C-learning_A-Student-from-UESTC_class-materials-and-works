/*
题目：（用带头结点单链表实现）
1、定义一个单链表结点结构体，其标签为Node，同时使用typedef为该结构体定义别名为Node。
其中，数据域包含一个int类型的成员data，用于存储整数数据；指针域包含一个指向下一结点的指针成员next。
2、编写一个函数insert_at_head（没有返回值），该函数接收两个参数，一个是指向单链表头结点的头指针head，
另一个是要插入的int类型数据data。该函数用于在带头结点的单链表头部插入一个新结点，新结点的数据域为data。
3、编写一个函数traverse_list（没有返回值），该函数接收一个指向单链表头结点的头指针head作为参数，
用于遍历单链表，并且按顺序打印出单链表中每个结点数据域的值，每个值之间用 “-> ” 连接，链表末尾打印 “NULL”。
例：10 -> 20 -> 30 -> NULL
4、编写一个函数free_list（没有返回值），该函数接收一个指向单链表头结点的头指针head作为参数，
用于释放整个带头结点单链表所占用的内存空间。
5、编写一个函数delete_node（没有返回值），该函数接收两个参数，一个是指向单链表头结点的头指针head，
另一个是要删除的目标数据值target。该函数用于删除带头结点的单链表里数据域值为target的结点
（若存在多个，只删除第一个满足条件的）。
6、在main函数中：
1）创建并初始化一个空单链表。
2）调用insert_at_head函数，生成如下顺序的单链表：
30 -> 20 -> 10 -> NULL
3）调用traverse_list函数，打印出生成的单链表。
4）调用delete_node函数，删除数据域值为20的结点。
5）再次调用traverse_list函数，打印出最终的单链表。
6）调用free_list函数，释放链表的内存。
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void insert_at_head(Node* head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("内存分配失败\n");
        return;
    }
    new_node->data = data;
    new_node->next = head->next;
    head->next = new_node;
}

void traverse_list(Node* head) {
    Node* current = head->next;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void delete_node(Node* head, int target) {
    Node* current = head;
    while (current->next != NULL && current->next->data != target) {
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

int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    head->data = 0;
    head->next = NULL;

    insert_at_head(head, 10);
    insert_at_head(head, 20);
    insert_at_head(head, 30);
    traverse_list(head);
    delete_node(head, 20);
    traverse_list(head);
    free_list(head);
}
