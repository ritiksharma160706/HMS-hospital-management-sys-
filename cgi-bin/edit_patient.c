#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PATIENT_FILE "../data/patients.dat"

typedef struct {
    int id;
    char name[100];
    int age;
    char gender[10];
    char address[200];
    char phone[20];
    char disease[150];
    time_t created_at;
} Patient;

int main() {
    char *data = getenv("QUERY_STRING");
    int id;
    char name[100], age_str[10], gender[10], address[200], phone[20], disease[150];
    
    sscanf(data, "id=%d&name=%99[^&]&age=%9[^&]&gender=%9[^&]&address=%199[^&]&phone=%19[^&]&disease=%149s",
           &id, name, age_str, gender, address, phone, disease);

    FILE *f = fopen(PATIENT_FILE, "rb+");
    Patient p;
    int found = 0;

    if (!f) {
        printf("Content-Type:text/html\n\n");
        printf("<html><body><h3 style='color:red;'>Error opening file!</h3></body></html>");
        return 0;
    }

    while (fread(&p, sizeof(Patient), 1, f) == 1) {
        if (p.id == id) {
            strcpy(p.name, name);
            p.age = atoi(age_str);
            strcpy(p.gender, gender);
            strcpy(p.address, address);
            strcpy(p.phone, phone);
            strcpy(p.disease, disease);
            fseek(f, -(long)sizeof(Patient), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, f);
            found = 1;
            break;
        }
    }
    fclose(f);

    // ✅ HTML + CSS for feedback
    printf("Content-Type:text/html\n\n");
    printf("<html><head>");
    printf("<style>"
           "body { background-color:#111; color:white; font-family:Arial; text-align:center; padding-top:80px; }"
           ".card { background-color:#1b1b1b; padding:40px; width:400px; margin:auto; border-radius:15px; "
           "box-shadow:0 0 15px red; }"
           "h2 { color:#ff3333; margin-bottom:20px; }"
           ".btn { display:inline-block; padding:10px 20px; background-color:red; color:white; text-decoration:none; "
           "border-radius:6px; transition:0.3s; }"
           ".btn:hover { background-color:#b30000; }"
           "</style>");
    printf("</head><body>");

    printf("<div class='card'>");
    if (found)
        printf("<h2>Patient Updated Successfully</h2>");
    else
        printf("<h2>Patient Not Found</h2>");
    
    printf("<a href='/hospital/patients.html' class='btn'>⬅ Back to Patients</a>");
    printf("</div></body></html>");
    
    return 0;
}
