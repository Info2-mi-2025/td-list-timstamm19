#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 100

// Ne pas modifier
void init_file() {
    FILE* f = fopen("data.txt", "w");
    if (f == NULL) exit(2);
    fprintf(f, "5\n12\n8\n1\n19\n");
    fclose(f);

    f = fopen("data2.txt", "w");
    fprintf(f, "10\n20\n30\n");
    fclose(f);

    f = fopen("data3.txt", "w");
    fprintf(f, "1\n2\n3\n4\n5\n");
    fclose(f);

    f = fopen("data_vide.txt", "w");
    fclose(f);
}

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

// Vérifie si une chaîne représente un entier
bool is_number(const char* s) {
    if (s[0] == '-') s++; // autorise les nombres négatifs
    for (int i = 0; s[i]; i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

void append(List* list, int value) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) exit(2);
    new_node->value = value;
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void free_list(List* list) {
    Node* current = list->head;
    while (current) {
        Node* tmp = current;
        current = current->next;
        free(tmp);
    }
    list->head = list->tail = NULL;
}

void print_list(const List* list) {
    printf("Liste : ");
    Node* current = list->head;
    while (current) {
        printf("%d", current->value);
        if (current->next) printf(" -> ");
        current = current->next;
    }
    printf("\n");
}

void reverse_list(List* list) {
    Node* prev = NULL;
    Node* current = list->head;
    list->tail = current;
    while (current) {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

int sum_list(const List* list) {
    int sum = 0;
    Node* current = list->head;
    while (current) {
        sum += current->value;
        current = current->next;
    }
    return sum;
}

int min_list(const List* list) {
    if (!list->head) return 0;
    int min = list->head->value;
    Node* current = list->head->next;
    while (current) {
        if (current->value < min)
            min = current->value;
        current = current->next;
    }
    return min;
}

int max_list(const List* list) {
    if (!list->head) return 0;
    int max = list->head->value;
    Node* current = list->head->next;
    while (current) {
        if (current->value > max)
            max = current->value;
        current = current->next;
    }
    return max;
}

void filter_list(List* list, int threshold) {
    Node* current = list->head;
    Node* prev = NULL;
    while (current) {
        if (current->value < threshold) {
            Node* to_delete = current;
            if (prev == NULL) {
                list->head = current->next;
                current = list->head;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            free(to_delete);
        } else {
            prev = current;
            current = current->next;
        }
    }

    // Update tail
    list->tail = NULL;
    current = list->head;
    while (current) {
        if (!current->next)
            list->tail = current;
        current = current->next;
    }
}

bool read_file(const char* filename, List* list) {
    FILE* f = fopen(filename, "r");
    if (!f) return false;
    int value;
    while (fscanf(f, "%d", &value) == 1) {
        append(list, value);
    }
    fclose(f);
    return true;
}

bool add_to_file(const char* filename, int value) {
    FILE* f = fopen(filename, "a");
    if (!f) return false;
    fprintf(f, "%d\n", value);
    fclose(f);
    printf("Valeur %d ajoutée au fichier.\n", value);
    return true;
}

void help() {
    printf("Utilisation : ./app <fichier> [options]\n\n");
    printf("Options disponibles :\n");
    printf("  --reverse         Inverse l'ordre des éléments\n");
    printf("  --sum             Affiche la somme des éléments\n");
    printf("  --filter <val>    Filtre les éléments >= val\n");
    printf("  --add <val>       Ajoute une valeur à la fin du fichier\n");
    printf("  --help            Affiche ce message d'aide\n");
    printf("  --version, -v     Affiche la version du programme\n");
    printf("  --min             Affiche la valeur minimale de la liste\n");
    printf("  --max             Affiche la valeur maximale de la liste\n");
}

void version() {
    printf("version 1.0\n");
}

int main(int argc, char* argv[]) {
    init_file();

    if (argc < 2) {
        fprintf(stderr, "Erreur : pas assez d'arguments.\n");
        return 1;
    }

    char* filename = NULL;
    bool only_option = false;

    // Chercher le fichier (non --option)
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            filename = argv[i];
            break;
        }
    }

    if (!filename && !(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)) {
        return 1;
    }

    List list = {0};
    if (filename && !read_file(filename, &list)) return 2;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            help();
            return 0;
        }
        if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            version();
            return 0;
        }
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--add") == 0) {
            if (i + 1 >= argc || !is_number(argv[i + 1])) return 1;
            int val = atoi(argv[i + 1]);
            if (!add_to_file(filename, val)) return 2;
            return 0;
        }
    }

    bool option_used = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--reverse") == 0) {
            reverse_list(&list);
            print_list(&list);
            option_used = true;
        } else if (strcmp(argv[i], "--sum") == 0) {
            print_list(&list);
            printf("Somme : %d\n", sum_list(&list));
            option_used = true;
        } else if (strcmp(argv[i], "--min") == 0) {
            print_list(&list);
            printf("Minimum : %d\n", min_list(&list));
            option_used = true;
        } else if (strcmp(argv[i], "--max") == 0) {
            print_list(&list);
            printf("Maximum : %d\n", max_list(&list));
            option_used = true;
        } else if (strcmp(argv[i], "--filter") == 0) {
            if (i + 1 >= argc || !is_number(argv[i + 1])) return 1;
            int val = atoi(argv[i + 1]);
            filter_list(&list, val);
            print_list(&list);
            option_used = true;
        }
    }

    if (!option_used && filename) {
        print_list(&list);
    }

    free_list(&list);
    return 0;
}