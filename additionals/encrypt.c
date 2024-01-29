#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Function to encrypt a password using Caesar cipher
void encrypt_password(char* password) {
    for (int i = 0; password[i] != '\0'; i++) {
        char c = password[i];
        if (c >= 'a' && c <= 'z') {
            password[i] = (c - 'a' + 3) % 26 + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            password[i] = (c - 'A' + 3) % 26 + 'A';
        }
    }
}

void encrypt_username(char* username){
    for (int j = 0; username[j] != '\0'; j++) {
        char c = username[j];
        if (c >= 'a' && c <= 'z') {
            username[j] = (c - 'a' + 3) % 26 + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            username[j] = (c - 'A' + 3) % 26 + 'A';
        } 
    }
}

void decrypt_username(char* username){
    for (int j = 0; username[j] != '\0'; j++) {
        char c = username[j];
        if (c >= 'a' && c <= 'z') {
            username[j] = (c - 'a' - 3 + 26) % 26 + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            username[j] = (c - 'A' - 3 + 26) % 26 + 'A';
        } 
    }
}

char* login(char* entered_username, char* entered_password) {
    FILE* file = fopen("D:/GitHub/Hostal-Register/data/Users_Encrypt.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return NULL;
    }

    // Encrypt the entered password
    encrypt_password(entered_password);

    // Encrypt the entered username
    encrypt_username(entered_username);
    

    char line[MAX_SIZE];
    while (fgets(line, sizeof(line), file)) {
        char username[MAX_SIZE], password[MAX_SIZE], role[MAX_SIZE];
        sscanf(line, "%s %s %s", username, password, role);

        if (strcmp(username, entered_username) == 0 && strcmp(password, entered_password) == 0) {
            fclose(file);
            return strdup(role);
        }
    }

    fclose(file);
    printf("Invalid username or password\n");
    return NULL;
}

int main() {
    char username[MAX_SIZE];
    char password[MAX_SIZE];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    char* role = login(username, password);
    if (role != NULL) {
        decrypt_username(username);
        printf("Logged in as role: %s\n", role);
        printf("Decrypted username: %s\n", username);
        free(role);
    }
    return 0;
}