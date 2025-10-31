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

// Replace '+' with space (for CGI form data)
void decode_spaces(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '+') str[i] = ' ';
    }
}

// Generate next patient ID
int next_id() {
    FILE *f = fopen(PATIENT_FILE, "rb");
    if (!f) return 1;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return (size <= 0) ? 1 : (int)(size / sizeof(Patient)) + 1;
}

int main() {
    printf("Content-Type:text/html\n\n");

    char *data = getenv("QUERY_STRING");
    if (!data) {
        printf("<html><body><h3 style='color:red;'>Error: No data received.</h3></body></html>");
        return 0;
    }

    char name[100] = "", age_str[10] = "", gender[10] = "", address[200] = "", phone[20] = "", disease[150] = "";

    // Parse form data safely
    sscanf(data, "name=%99[^&]&age=%9[^&]&gender=%9[^&]&phone=%19[^&]&address=%199[^&]&disease=%149[^\n]",
       name, age_str, gender, phone, address, disease);


    // Decode '+' to ' '
    decode_spaces(name);
    decode_spaces(gender);
    decode_spaces(address);
    decode_spaces(phone);
    decode_spaces(disease);

    Patient p;
    p.id = next_id();
    strncpy(p.name, name, sizeof(p.name) - 1);
    p.name[sizeof(p.name) - 1] = '\0';
    p.age = atoi(age_str);
    strncpy(p.gender, gender, sizeof(p.gender) - 1);
    p.gender[sizeof(p.gender) - 1] = '\0';
    strncpy(p.address, address, sizeof(p.address) - 1);
    p.address[sizeof(p.address) - 1] = '\0';
    strncpy(p.phone, phone, sizeof(p.phone) - 1);
    p.phone[sizeof(p.phone) - 1] = '\0';
    strncpy(p.disease, disease, sizeof(p.disease) - 1);
    p.disease[sizeof(p.disease) - 1] = '\0';
    p.created_at = time(NULL);

    // Save record
    FILE *f = fopen(PATIENT_FILE, "ab");
    if (f) {
        fwrite(&p, sizeof(Patient), 1, f);
        fclose(f);
    } else {
        printf("<html><body><h3 style='color:red;'>Error: Cannot open file to save patient.</h3></body></html>");
        return 0;
    }

    // Success Page
    printf("<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Patient Added</title>");
    printf("<style>");
    printf("body{font-family:Poppins,Arial;background:#0b0b0b;color:#eee;display:flex;align-items:center;justify-content:center;height:100vh;margin:0;}");
    printf(".box{background:#1a1a1a;border:1px solid rgba(255,255,255,0.1);border-radius:15px;padding:40px 60px;text-align:center;box-shadow:0 0 20px rgba(255,0,0,0.2);}");
    printf("h2{color:#ff4d4d;margin-bottom:10px;}");
    printf("p{color:#bbb;font-size:16px;margin-bottom:25px;}");
    printf(".btn{background:linear-gradient(90deg,#ff0000,#cc0000);color:#fff;padding:10px 20px;border:none;border-radius:8px;font-weight:600;text-decoration:none;transition:0.3s;}");
    printf(".btn:hover{background:#e60000;transform:scale(1.05);}");
    printf("</style></head><body>");
    printf("<div class='box'>");
    printf("<h2>Patient Added Successfully</h2>");
    printf("<p><strong>Name:</strong> %s</p>", p.name);
    printf("<p><strong>Gender:</strong> %s</p>", p.gender);
    printf("<p><strong>Age:</strong> %d</p>", p.age);
    printf("<p><strong>Address:</strong> %s</p>", p.address);
    printf("<p><strong>Phone:</strong> %s</p>", p.phone);
    printf("<p><strong>Disease:</strong> %s</p>", p.disease);
    printf("<a href='/cgi-bin/list_patients.cgi' class='btn'>View Patients</a>");
    printf("</div></body></html>");
    return 0;
}
