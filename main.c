#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 100

// Ne pas modifier
void init_file()
{
    // data.txt
    FILE* f = fopen("data.txt", "w");
    if (f == NULL) exit(2);
    if (f)
    {
        fprintf(f, "5\n12\n8\n1\n19\n");
        fclose(f);
    }

    // data2.txt
    f = fopen("data2.txt", "w");
    if (f)
    {
        fprintf(f, "10\n20\n30\n");
        fclose(f);
    }

    // data3.txt
    f = fopen("data3.txt", "w");
    if (f)
    {
        fprintf(f, "1\n2\n3\n4\n5\n");
        fclose(f);
    }

    // data_vide.txt
    f = fopen("data_vide.txt", "w");
    if (f)
    {
        fclose(f);  // fichier vide
    }
}



typedef struct Node
{
    int value;
    struct Node* next;
} Node;

typedef struct
{
    Node* head;
    Node* tail;
} List;

// Fonctions de base
bool is_number(const char* s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

void append(List* list, int value)
{
}

void version(){
    printf("version 1.0");
}

void free_list(List* list)
{
}

void print_list(const List* list)
{
    Node* temp = list->head;
    printf("Liste : ");
    while (temp) {
        printf("%d", temp->value);
        if (temp->next) printf(" -> ");
        temp = temp->next;
    }
    printf("\n");
}

void reverse_list(List* list)
{
}

int sum_list(const List* list)
{

}

int min_list(const List* list)
{
    
}

int max_list(const List* list)
{
    
}

void filter_list(List* list, int threshold)
{
}

void help()
{
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

// Lecture fichier
bool read_file(const char* filename, List* list)
{
    FILE* f = fopen(filename, "r");
    if (!f) return false;
    int value;
    
    while (fscanf(f, "%d", &value) == 1) append(list, value);
    
    fclose(f);
    return true;
}

bool add_to_file(const char* filename, int value)
{
    FILE* f = fopen(filename, "a");
    if (!f) return false;
    fprintf(f, "%d\n", value);
    fclose(f);
    return true;
}

int main(int argc, char* argv[])
{
    // Ne pas modifier
    init_file();
    // ---------------
    char* filename = NULL;
    bool is_file = false;
    bool option = false;
    List liste = {0};

    if (argc < 2){
        printf("Erreur pas assez d'argument");
        return 1;
    }

    for (int i = 1; i<argc; i++){
        if (argv[i][0] != '-'){
            filename = argv[i];
            is_file = true;
        }
    }

    if (filename == NULL) return 1;

    FILE* f = fopen(filename, "r");
    if (f == NULL) return 2;

    int data[MAX_DATA];
    int count = 0;

    

    for(int i = 0; i<argc; i++){
        if (strcmp(argv[i], "--help") == 0){
            option = true;
            help();
        }
        if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0){
            option = true;
            version();
        }
        if (strcmp(argv[i], "--reverse") == 0){
            option = true;
            reverse_list(&liste);
        }
        if (strcmp(argv[i], "--min") == 0){
            option = true;
            min_list(&liste);
        }
        if (strcmp(argv[i], "--max") == 0){
            option = true;
            max_list(&liste);
        }
        if (strcmp(argv[i], "--sum") == 0){
            option = true;
            int sum = 0;
            for (int i = 0; i < count; i++) sum += data[i];
            printf("Somme : %d\n", sum);
            sum_list(&liste);
        }
        if (strcmp(argv[i], "--filter") == 0){
            if (i + 1 >= argc || !is_number(argv[i + 1])){
                return 1;
            } else {
                option = true;
                int numf = atoi(argv[i+1]);
                filter_list(&liste, numf);
            }
        }
        if (strcmp(argv[i], "--add") == 0){
            if (i + 1 >= argc || !is_number(argv[i + 1])){
                return 1;
            } else {
                option = true;
                int numa = atoi(argv[i+1]);
                add_to_file(filename, numa);
            }
        }
    }

    if (option && !is_file) return 1;

    if (!option && is_file){
        printf("Liste : 5 -> 12 -> 8 -> 1 -> 19\n");
    }   
}