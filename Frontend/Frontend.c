#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
//#include "curl/include/curl/curl.h"
//#include <curl/curl.h>
#include <windows.h>
#include <unistd.h>

// Function to check if the enrollment number exists in the database
int check_enrollment(char *enroll_no) {
    // Open the file that contains student data
    FILE *s_data = fopen("//DESKTOP-QE6QOLV/data/Students.txt", "r");
    if (s_data == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    char line[256];
    // Read each line from the file
    while (fgets(line, sizeof(line), s_data) != NULL) {
        // Assuming the line is in the format "enrollment_number,name,hostel"
        char *temp_enroll_no = strtok(line, "`");
        // If the read enrollment number matches the input enrollment number
        if (temp_enroll_no != NULL && strcmp(temp_enroll_no, enroll_no) == 0) {
            // Close the file and return 1 (true)
            fclose(s_data);
            return 1;
        }
    }

    // Close the file and return 0 (false) if no match was found
    fclose(s_data);
    return 0;
} 

// Function to add a record to the database
void add_record(char *enroll_no, char *destination, time_t t){
    // Open the file where records are stored
    FILE *fp=fopen("//DESKTOP-QE6QOLV/data/Records.txt","a");
    if (fp == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    // Write the enrollment number, destination, and current time to the file
    // Use commas as separators
    fprintf(fp,"%s`",enroll_no);
    fprintf(fp,"%s`",destination);
    fprintf(fp, "%ld\n", (long)t);
    //printf("\tStudent records saved successfully\n");
    // Close the file
    fclose(fp);
    }

/*void add_record(char *enroll_no, char *destination, time_t t){
    CURL *curl;
    CURLcode res;
    FILE *fp;

    if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) {
        fprintf(stderr, "curl_global_init() failed\n");
        return;
    }

    curl = curl_easy_init();

    if(curl) {
        fp = fopen("D:/GitHub/Hostal-Register/data/Records.txt","w+");
        if (fp == NULL) {
            printf("Failed to open the file.\n");
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return;
        }

        fprintf(fp,"%s`",enroll_no);
        fprintf(fp,"%s`",destination);
        fprintf(fp, "%ld\n", (long)t);
        fclose(fp);

        curl_easy_setopt(curl, CURLOPT_URL, "ftp://ftp.eecosl.com:21/home/eecoslco/hostel/Records.txt");
        curl_easy_setopt(curl, CURLOPT_USERNAME, "hostel@eecosl.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "v$A3AUOECb)W");
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        fp = fopen("Records.txt", "rb");
        if (fp == NULL) {
            printf("Failed to open the file.\n");
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return;
        }

        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        fclose(fp);
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "curl_easy_init() failed\n");
    }

    curl_global_cleanup();
}*/

int frontf() {
    char enroll_input[8];
    char enroll_no[15];
    char destination[50];
    time_t t;

    while(1) {
        system("cls");
        printf("\n\n");
        printc("Enter student's details");

        printf("\n\n\n\n\n\n\n\n\n\n");

        printf("\n\tEnter student's enrollment number: ");
        scanf("%s", enroll_input);

        // Convert the input enrollment number to uppercase
        for(int i = 0; enroll_input[i]; i++){
            enroll_input[i] = toupper(enroll_input[i]);
        }

        // Split the input enrollment number into degree, year, and number
        char degree[4], year[3], number[4];
        sscanf(enroll_input, "%3s%2s%3s", degree, year, number);
        // Format the enrollment number
        printf("\t");
        sprintf(enroll_no, "UWU/%s/%s/%s", degree, year, number);
        //printf("%s\n", enroll_no); 

        // If the enrollment number exists in the database
        if(check_enrollment(enroll_no)) {
            printf("\n\tEnter destination: ");
            scanf("%s", destination);

            // Get the current time
            t = time(NULL);

            // Add a record to the database
            add_record(enroll_no, destination, t);
            system("cls");
            printcm("Successfully updated\n");
            sleep(2);
        } else {
            system("cls");
            printcm("Invalid Enrollment number\n");
            sleep(2);
        }
    }

    return 0;
}
