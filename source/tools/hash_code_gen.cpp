#include <iostream>
#include <cstring>
using namespace std;

#define MAX_FULL_DIR 8
#define MAX_DIR 4

char str[100];

int main() {
    scanf("%s", str);
    printf("\n\n");
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] != '*') {
            continue;
        }
        int hash_len_low = i + 1;
        int hash_len_high = len - i;
        int hash_low = 0;
        int hash_high = 0;
        for (int j = i; j >= 0; j--) {
            if (str[j] == '*')
                hash_low += (1 << (2 * (i-j)));
            else if (str[j] == '?')
                hash_low += (3 << (2 * (i-j)));
        }
        for (int j = i; j < len; j++) {
            if (str[j] == '*')
                hash_high += (1 << (2 * (j-i)));
            else if (str[j] == '?')
                hash_high += (3 << (2 * (j-i)));
        }
        printf("    // ");
        for (int j = 0; j < len; j++) {
            if (j == i)
                printf("x");
            else 
                printf("%c", str[j]);
        }
        printf("\n");
        printf("    if (hash_low %% (1 << %d) == %d && hash_high %% (1 << %d) == %d) {\n",
            hash_len_low * 2, hash_low, hash_len_high * 2, hash_high);
        printf("        return 1;\n");
        printf("    }\n");
    }
    return 0;
}