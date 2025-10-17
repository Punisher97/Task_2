#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *link;
typedef struct Node {
    char *word;
    link next;
} node;
typedef link list;

// Создание звена 
link create_node(char *word) {
    link p = (link)malloc(sizeof(node));
    p->word = (char*)malloc(strlen(word) + 1);
    strcpy(p->word, word);
    p->next = NULL;
    return p;
}

// Добавление звена в конец 
void append(list *lp, char *word) {
    link p = create_node(word);
    if (*lp == NULL) {
        *lp = p;
    } else {
        link cur = *lp;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = p;
    }
}

// Освобождение памяти 
void destruct(list ls) {
    link q;
    while (ls != NULL) {
        q = ls;
        ls = ls->next;
        free(q);
    }
}

// Печать списка слов через пробел 
void print(list ls) {
    while (ls != NULL) {
        printf("%s", ls->word);
        if (ls->next != NULL)
            printf(" ");
        ls = ls->next;
    }
    printf("\n");
}

// Удаление
void remove_duplicates_of_last(list *lp) {
    if (*lp == NULL) return;

    // Найдём последнее слово
    link last = *lp;
    while (last->next != NULL)
        last = last->next;

    char *target = last->word;

    // Удаляем совпадения, кроме последнего
    link cur = *lp, prev = NULL;
    while (cur != NULL) {
        if (cur != last && strcmp(cur->word, target) == 0) {
            link temp = cur;
            if (prev == NULL)
                *lp = cur->next;
            else
                prev->next = cur->next;
            cur = cur->next;
            free(temp);
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
}

int main(void) {
    list lst = NULL;
    char word[256];

    while (scanf("%255s", word) == 1) {
        append(&lst, word);
    }

    remove_duplicates_of_last(&lst);
    print(lst);
    destruct(lst);
    return 0;
}
