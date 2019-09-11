#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char* a, const char* b) {
    return strcmp(b, a);
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return lexicographic_sort(b, a);
}

int number_of_distinct_characters(const char *a) {
    const size_t dict_size = 26;
    char found[dict_size];
    memset(&found, 0, sizeof(found));
    const size_t len = strlen(a);
    for (int i = 0; i < len; i++) {
        found[a[i] - 'a'] = 1;
    }
    int n = 0;
    for (int i = 0; i < dict_size; i++) {
        n += found[i];
    }
    return n;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int x = number_of_distinct_characters(b) - number_of_distinct_characters(a);
    return x ? x : lexicographic_sort(a, b);
}

int sort_by_length(const char* a, const char* b) {
    int x = strlen(b) - strlen(a);
    return x ? x : lexicographic_sort(a, b);
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)) {
    // bubble sort
    char* x;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (cmp_func(arr[i], arr[j]) < 0) {
                x = arr[i];
                arr[i] = arr[j];
                arr[j] = x;
            }
        }
    }
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
    arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}