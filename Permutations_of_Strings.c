int lexicographically_precedes(char *a, char *b) {
    for (int i = 0; i < 12; i++) {
        if (a[i] < b[i])
            return 1;
        if (a[i] > b[i])
            return 0;
    }
    return 0;
}

int next_permutation(int n, char** s) {
    int k = -1, l = -1;
    char *x;
    for (int i = 0; i < n - 1; i++) {
        if (lexicographically_precedes(s[i], s[i + 1])) {
            k = i;
        }
    }
    if (k < 0)
        return 0;
    for (int i = k + 1; i < n; i++) {
        if (lexicographically_precedes(s[k], s[i])) {
            l = i;
        }
    }
    if (l > 0) {
        x = s[k];
        s[k] = s[l];
        s[l] = x;
    }
    for (int i = k + 1; i < (k + n + 1) / 2; i++) {
        x = s[i];
        s[i] = s[n - i + k];
        s[n - i + k] = x;
    }
    return 1;
}

int main()
{
    char **s;
    int n;
    scanf("%d", &n);
    s = calloc(n, sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        s[i] = calloc(11, sizeof(char));
        scanf("%s", s[i]);
    }
    do
    {
        for (int i = 0; i < n; i++)
            printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
    } while (next_permutation(n, s));
    for (int i = 0; i < n; i++)
        free(s[i]);
    free(s);
    return 0;
}