#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    else if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    else if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    else return 0;
}

void remove_trailing_zeros(char *str) {
    char *dot = strchr(str, '.');
    if (dot != NULL) {
        char *end = str + strlen(str) - 1;
        while (end > dot && *end == '0') *end-- = '\0';
        if (end == dot) *end = '\0';
    }
}

void int_to_base(int num, int base, char *output) {
    char temp[50] = "";
    int index = 0;
    char digits[] = "0123456789ABCDEF";
    if (num == 0) {
        strcpy(output, "0");
        return;
    }
    while (num > 0) {
        temp[index++] = digits[num % base];
        num /= base;
    }
    for (int i = 0; i < index; i++) output[i] = temp[index - i - 1];
    output[index] = '\0';
}



float calculation(int pr, int pot) {
    char n[20], pre[10] = "", post[10] = "", octalpart[20], pre2[10] = "", post2[10] = "";
    int t = 0, dotPos = 0, postLen = 0;

    printf("\n============================================\n");
    printf("🔢 Base-%d to base-%d Converter\n⚠  Format: Include a '.' for fractions (e.g., 101.11)\n", pr, pot);
    printf("============================================\n");

    int valid = 0;
    while (!valid) {
        valid = 1;
        printf("👉 Enter number: ");
        scanf("%s", n);
        t = strlen(n);
        for (int i = 0; i < t; i++) {
            if (n[i] == '.') continue;
            int val = hexCharToInt(n[i]);
            if (val >= pr || val < 0) {
                printf("❌ Invalid input! Please enter a valid base-%d number.\n", pr);
                valid = 0;
                break;
            }
        }
    }

    int isFraction = 0;
    for (int i = 0; i < t; i++) if (n[i] == '.') { isFraction = 1; dotPos = i; break; }

    if (isFraction) {
        for (int j = 0; j < dotPos; j++) pre[j] = n[j];
        for (int k = dotPos + 1; k < t; k++) post[postLen++] = n[k];

        float sum = 0, sum2 = 0;
        for (int i = 0; i < dotPos; i++) sum += pow(pr, dotPos - 1 - i) * hexCharToInt(pre[i]);
        for (int i = 0, p = -1; i < postLen; i++, p--) sum2 += pow(pr, p) * hexCharToInt(post[i]);

        sprintf(octalpart, "%.10f", sum + sum2);
        remove_trailing_zeros(octalpart);

        int j = 0, k = 0, second3 = 0;
        while (octalpart[j] != '.' && octalpart[j]) pre2[j] = octalpart[j], j++;
        pre2[j] = '\0'; second3 = ++j;
        while (octalpart[second3]) post2[k++] = octalpart[second3++];

        int integerPart = atoi(pre2);
        char intResult[30] = "";
        int_to_base(integerPart, pot, intResult);

        float frac = atof(post2) / pow(10, strlen(post2));
        char fracResult[20] = ".";
        for (int i = 0; i < 5; i++) {
            frac *= pot;
            int digit = (int)frac;
            frac -= digit;
            sprintf(fracResult + strlen(fracResult), "%c", (digit < 10) ? digit + '0' : digit - 10 + 'A');
        }
        remove_trailing_zeros(fracResult);
        printf("\nReturned Answer = %s%s\n", intResult, fracResult);
        return atof(octalpart);
    } else {
        float sum = 0;
        for (int i = 0; i < t; i++) sum += pow(pr, t - 1 - i) * hexCharToInt(n[i]);
        int integerPart = (int)sum;
        char result2[30] = "";
        int_to_base(integerPart, pot, result2);
        printf("\nReturned Answer = %s\n", result2);
        return sum;
    }
}


float calculation2(int pr) {
    char n[20], pre[10] = "", post[10] = "";
    int t = 0, dotPos = 0, postLen = 0;

    printf("\n============================================\n");
    printf("🔢 Base-%d to Decimal Converter\n⚠  Format: Include a '.' for fractions (e.g., 101.11)\n", pr);
    printf("============================================\n");

    int valid = 0;
    while (!valid) {
        valid = 1;
        printf("👉 Enter number: ");
        scanf("%s", n);
        t = strlen(n);
        for (int i = 0; i < t; i++) {
            if (n[i] == '.') continue;
            int val = hexCharToInt(n[i]);
            if (val >= pr || val < 0) {
                printf("❌ Invalid input! Please enter a valid base-%d number.\n", pr);
                valid = 0;
                break;
            }
        }
    }

    int isFraction = 0;
    for (int i = 0; i < t; i++) if (n[i] == '.') { isFraction = 1; dotPos = i; break; }

    if (isFraction) {
        for (int j = 0; j < dotPos; j++) pre[j] = n[j];
        for (int k = dotPos + 1; k < t; k++) post[postLen++] = n[k];

        float sum = 0, sum2 = 0;
        for (int i = 0; i < dotPos; i++) sum += pow(pr, dotPos - 1 - i) * hexCharToInt(pre[i]);
        for (int i = 0, p = -1; i < postLen; i++, p--) sum2 += pow(pr, p) * hexCharToInt(post[i]);
        return sum + sum2;
    } else {
        float sum = 0;
        for (int i = 0; i < t; i++) sum += pow(pr, t - 1 - i) * hexCharToInt(n[i]);
        return sum;
    }
}


float calculation3(int sin) {
    char n[20], pre[10] = "", post[10] = "";
    int t = 0, dotPos = 0, postLen = 0;

    printf("\n============================================\n");
    printf("🔢 Decimal to Base-%d Converter\n⚠  Format: Include a '.' for fractions (e.g., 12.25)\n", sin);
    printf("============================================\n");

    int valid = 0;
    while (!valid) {
        valid = 1;
        printf("👉 Enter Decimal number: ");
        scanf("%s", n);
        t = strlen(n);
        for (int i = 0; i < t; i++) {
            if (n[i] == '.') continue;
            if (!isdigit(n[i])) {
                printf("❌ Invalid input! Please enter a valid decimal number.\n");
                valid = 0;
                break;
            }
        }
    }

    int isFraction = 0;
    for (int i = 0; i < t; i++) if (n[i] == '.') { isFraction = 1; dotPos = i; break; }

    if (isFraction) {
        for (int j = 0; j < dotPos; j++) pre[j] = n[j];
        for (int k = dotPos + 1; k < t; k++) post[postLen++] = n[k];

        float integerPart = atof(pre);
        float fractionalPart = atof(post) / pow(10, postLen);
        int arr[50], z2 = 0;

        while ((int)integerPart) { arr[z2++] = (int)integerPart % sin; integerPart = (int)integerPart / sin; }

        float finalAns = 0;
        for (int i = z2 - 1; i >= 0; i--) finalAns = finalAns * 10 + arr[i];
        for (int i = 0; i < 5; i++) {
            fractionalPart *= sin;
            finalAns += ((int)fractionalPart) / pow(10, i + 1);
            fractionalPart -= (int)fractionalPart;
        }
        return finalAns;
    } else {
        float decimal = atof(n);
        int arr[50], z2 = 0;
        while ((int)decimal) { arr[z2++] = (int)decimal % sin; decimal = (int)decimal / sin; }

        float finalAns = 0;
        for (int i = z2 - 1; i >= 0; i--) finalAns = finalAns * 10 + arr[i];
        return finalAns;
    }
}



int main() {
    int w, y;
    float result = 0;
    char again;
    do {
        // Main Menu Input Validation
        do {
            printf("Enter your choice:\n");
            printf("1. Binary\n2. Octal\n3. Decimal\n4. Hexadecimal\n👉 Enter: ");
            if (scanf("%d", &w) != 1 || w < 1 || w > 4) {
                while (getchar() != '\n');
                printf("❌ Invalid input! Please enter 1, 2, 3, or 4.\n");
                w = 0;
            }
        } while (w < 1 || w > 4);

        if (w == 1) {
            printf("1. Binary to Octal\n2. Binary to Decimal\n3. Binary to Hexadecimal\n");
            do {
                printf("👉 Enter: ");
                if (scanf("%d", &y) != 1 || y < 1 || y > 3) {
                    while (getchar() != '\n');
                    printf("❌ Invalid input! Please enter 1, 2, or 3.\n");
                    y = 0;
                }
            } while (y < 1 || y > 3);

            if (y == 1) { result = calculation(2, 8); printf("\nReturned Answer = %.2f\n", result); }
            else if (y == 2) { result = calculation2(2); printf("\nReturned Answer = %.2f\n", result); }
            else if (y == 3) { result = calculation(2, 16); printf("\nReturned Answer = %.2f\n", result); }
        } else if (w == 2) {
            printf("1. Octal to Binary\n2. Octal to Decimal\n3. Octal to Hexadecimal\n");
            do {
                printf("👉 Enter: ");
                if (scanf("%d", &y) != 1 || y < 1 || y > 3) {
                    while (getchar() != '\n');
                    printf("❌ Invalid input! Please enter 1, 2, or 3.\n");
                    y = 0;
                }
            } while (y < 1 || y > 3);

            if (y == 1) { result = calculation(8, 2); printf("\nReturned Answer = %.2f\n", result); }
            else if (y == 2) { result = calculation2(8); printf("\nReturned Answer = %.2f\n", result); }
            else if (y == 3) { result = calculation(8, 16); printf("\nReturned Answer = %.2f\n", result); }
        } else if (w == 3) {
            printf("1. Decimal to Binary\n2. Decimal to Octal\n3. Decimal to Hexadecimal\n");
            do {
                printf("👉 Enter: ");
                if (scanf("%d", &y) != 1 || y < 1 || y > 3) {
                    while (getchar() != '\n');
                    printf("❌ Invalid input! Please enter 1, 2, or 3.\n");
                    y = 0;
                }
            } while (y < 1 || y > 3);

            if (y == 1) { result = calculation3(2); printf("\nReturned Answer = %.2f\n", result); }
            else if (y == 2) { result = calculation3(8); printf("\nReturned Answer = %.2f\n", result); }
            else if (y == 3) { result = calculation3(16); printf("\nReturned Answer = %.2f\n", result); }
        } else if (w == 4) {
            printf("1. Hex to Binary\n2. Hex to Octal\n3. Hex to Decimal\n");
            do {
                printf("👉 Enter: ");
                if (scanf("%d", &y) != 1 || y < 1 || y > 3) {
                    while (getchar() != '\n');
                    printf("❌ Invalid input! Please enter 1, 2, or 3.\n");
                    y = 0;
                }
            } while (y < 1 || y > 3);

            if (y == 1) { result = calculation(16, 2); printf("\nReturned Answer = %.2f\n", result); }
            else if (y == 2) { result = calculation(16, 8); printf("\nReturned Answer = %.2f\n", result); }
            else if (y == 3) { result = calculation2(16); printf("\nReturned Answer = %.2f\n", result); }
        }

        printf("\nDo you want to perform another conversion? (y/n): ");
        scanf(" %c", &again);
    } while (again == 'y' || again == 'Y');

    return 0;
}