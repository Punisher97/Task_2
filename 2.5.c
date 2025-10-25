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

void expand_buffer(char **buf, int *size) {
    int new_size = (*size == 0) ? 16 : *size * 2;
    char *new_buf = realloc(*buf, new_size);
    *buf = new_buf;
    *size = new_size;
}

// Проверка на пробельный символ
int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// Чтение слова с динамическим выделением памяти
char* read_word_dynamic(const char **input) {
    const char *p = *input;

    // Пропускаем пробелы
    while (*p != '\0' && is_space(*p)) {
        p++;
    }

    if (*p == '\0') return NULL;

    // Читаем слово
    char *word = NULL;
    int size = 0, len = 0;

    while (*p != '\0' && !is_space(*p)) {
        if (len + 1 >= size)
            expand_buffer(&word, &size);
        word[len++] = *p;
        p++;
    }

    if (word) {
        if (len + 1 >= size)
            expand_buffer(&word, &size);
        word[len] = '\0';
    }

    *input = p; // Обновляем позицию в строке
    return word;
}

int main(void) {
    printf("Введите строку: ");

    // Читаем всю строку
    char *input = NULL;
    int size = 0, len = 0;
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= size)
            expand_buffer(&input, &size);
        input[len++] = (char)c;
    }

    if (input) {
        if (len + 1 >= size)
            expand_buffer(&input, &size);
        input[len] = '\0';
    } else {
        input = strdup("");
    }

    // Разбираем строку на слова и строим список
    list lst = NULL;
    const char *pos = input;

    while (1) {
        char *word = read_word_dynamic(&pos);
        if (word == NULL) break;

        append(&lst, word);
        free(word);
    }

    if (lst != NULL) {
        remove_duplicates_of_last(&lst);
    }

    print(lst);
    destruct(lst);
    free(input);

    return 0;
}

