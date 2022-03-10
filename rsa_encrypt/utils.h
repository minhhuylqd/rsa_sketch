#include <math.h>

int power(int x, int y) {
    int tmp = 1;
    for (int i = 0; i < y; i++) {
        tmp *= x;
    }
    return tmp;
}

int to_int(String str) {
    int length = str.length();
    int res = 0;
    int is_zero = 1;

    for (int i = 0; i < length; i++) {
        if (str[i] != '0') {
            is_zero = 0;
            break;
        }
    }

    if (is_zero == 1) {
        return 0;
    }
    for (int i = 0; i < length; i++) {
        if (str[i] != '0') {
            res += power(10, length - i - 1) * (str[i] - '0');
        }
    }
    return res;

}

bool is_prime(int n) {
    if (n == 0 || n == 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// int* string_to_ascii_list(String str) {
//     int length = str.length();
//     int* ascii_list = new int[length];
//     for (int i = 0; i < length; i++) {
//         ascii_list[i] = (int)(str[i]);
//         Serial.println();
//     }
//     return ascii_list;
// }

// int[] string_to_ascii_list(String str) {
//     int length = str.length();
//     int[] ascii_list = new int[length];
//     for (int i = 0; i < length; i++) {
//         ascii_list[i] = (int)(str[i]);
//         Serial.println();
//     }
//     return ascii_list;
// }

int* string_to_ascii_list(char* str) {
    int length = strlen(str);
    int* ascii_list = new int[length];
    for (int i = 0; i < length; i++) {
        ascii_list[i] = (int)(str[i]);
        //Serial.println(ascii_list[i]);
    }
    return ascii_list;
}

// String ascii_list_to_string(int* ascii_list) {
//     String str = "";
//     int length = sizeof(ascii_list) / sizeof(ascii_list[0]);
//     for (int i = 0; i < length; i++) {
//         str += (char)(ascii_list[i]);
//     }
//     return str;
// }

char* ascii_list_to_string(int* ascii_list, int length) {
    //int length = sizeof(ascii_list) / sizeof(ascii_list[0]);
    char* str = new char[length];
    for (int i = 0; i < length; i++) {
        str[i] = (char)(ascii_list[i]);
    }
    return str;
}

int mod_func(int a, int b, int c) {
    int tmp = 1;
    for (int i = 0; i < b; i++) {
        tmp = (tmp * a) % c;
    }
    return tmp;
}

/*
String cipher(String message, int key, int n) {
    int length = message.length();
    int* message_ascii_list = string_to_ascii_list(message);
    int* cipher_ascii_list = new int[length];

    for (int i = 0; i < length; i++) {
        cipher_ascii_list[i] = mod_func(message_ascii_list[i], key, n);
    }

    return ascii_list_to_string(cipher_ascii_list);
}
*/
char* cipher(char* message, int key, int n) {
    int length = strlen(message);
    int* message_ascii_list = string_to_ascii_list(message);
    int* cipher_ascii_list = new int[length];

    for (int i = 0; i < length; i++) {
        cipher_ascii_list[i] = mod_func(message_ascii_list[i], key, n);
    }

    return ascii_list_to_string(cipher_ascii_list, length);
}

// Strategy:
//  - encrypt: string -> ascii list
//  - decrypt: acsii list -> string

int* encrypt(char* message, int key, int n) {
    int length = strlen(message);
    int* message_ascii_list = string_to_ascii_list(message);
    int* cipher_ascii_list = new int[length];
    // Serial.println("Encrypting:");
    for (int i = 0; i < length; i++) {
        cipher_ascii_list[i] = mod_func(message_ascii_list[i], key, n);
        // Serial.print("Origin ascii: ");
        // Serial.print(message_ascii_list[i]);
        // Serial.print(" - Ciphered ascii: ");
        // Serial.println(cipher_ascii_list[i]);
    }

    return cipher_ascii_list;
}

char* decrypt(int* message_ascii_list, int key, int n, int length) {
    int* cipher_ascii_list = new int[length];
    // Serial.println("Decrypting:");
    for (int i = 0; i < length; i++) {
        cipher_ascii_list[i] = mod_func(message_ascii_list[i], key, n);
        // Serial.print("Ciphered ascii: ");
        // Serial.print(message_ascii_list[i]);
        // Serial.print(" - Origin ascii: ");
        // Serial.println(cipher_ascii_list[i]);
    }
    return ascii_list_to_string(cipher_ascii_list, length);
}
