/*
练习：（用带头结点单链表实现）
1、定义一个单链表结点结构体，其标签为Node，同时使用typedef为该结构体定义别名为Node。
其中，数据域包含一个int类型的成员data，用于存储整数数据；指针域包含一个指向下一结点的指针成员next。
2、编写一个函数insert_at_head（没有返回值），该函数接收两个参数，一个是指向单链表头结点的头指针head，
另一个是要插入的int类型数据data。该函数用于在带头结点的单链表头部插入一个新结点，新结点的数据域为data。
3、编写一个函数traverse_list（没有返回值），该函数接收一个指向单链表头结点的头指针head作为参数，
用于遍历单链表，并且按顺序打印出单链表中每个结点数据域的值，每个值之间用 “-> ” 连接，链表末尾打印 “NULL”。
例：10 -> 20 -> 30 -> NULL
4、编写一个函数free_list（没有返回值），该函数接收一个指向单链表头结点的头指针head作为参数，
用于释放整个带头结点单链表所占用的内存空间。
5、编写一个函数reverse_list（没有返回值），该函数接收一个指向带头结点单链表的头结点的头指针head作为参数，
用于反转带头结点的单链表，即改变链表中结点的链接方向，使得原链表的最后一个结点变为第一个数据结点，
原第一个数据结点变为最后一个数据结点。
6、在main函数中：
1）创建并初始化一个空单链表，并且调用insert_at_head函数，生成如下顺序的单链表：
30 -> 20 -> 10 -> NULL
2）调用traverse_list函数，打印出生成的单链表。
3）调用reverse_list函数，反转现有的单链表。
4）调用traverse_list函数，打印出反转后的单链表。
5）创建并初始化另一个空单链表，并且调用 insert_at_head函数，生成如下顺序的单链表：
15 -> 35 -> 45 -> NULL
6）分别调用traverse_list函数，打印出上述两个单链表。
7）调用free_list函数，释放链表的内存。

打印格式：
原链表：...
反转后：...
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

void reverse_list(Node* head) {
    Node* current = head->next;
    Node* prev = NULL;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head->next = prev;
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
    printf("原链表：");
    traverse_list(head);
    reverse_list(head);
    printf("反转后：");
    traverse_list(head);
    free_list(head);
}


