#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATIENT_FILE "../data/patients.dat"

typedef struct {
    int id;
    char name[100];
    int age;
    char gender[10];
    char address[200];
    char phone[20];
    char disease[150];
} Patient;

int main() {
    char *data = getenv("QUERY_STRING");
    int id = 0;
    if (!data || sscanf(data, "id=%d", &id) != 1) {
        printf("Content-Type:text/html\n\n");
        printf("<html><body><h3>Invalid request!</h3></body></html>");
        return 0;
    }

    FILE *f = fopen(PATIENT_FILE, "rb");
    if (!f) {
        printf("Content-Type:text/html\n\n");
        printf("<html><body><h3>Could not open patient file!</h3></body></html>");
        return 0;
    }

    FILE *tmp = fopen("../data/tmp.dat", "wb");
    if (!tmp) {
        fclose(f);
        printf("Content-Type:text/html\n\n");
        printf("<html><body><h3>Could not create temp file!</h3></body></html>");
        return 0;
    }

    Patient p;
    int found = 0;
    while (fread(&p, sizeof(Patient), 1, f) == 1) {
        if (p.id != id) fwrite(&p, sizeof(Patient), 1, tmp);
        else found = 1;
    }

    fclose(f);
    fclose(tmp);
    remove(PATIENT_FILE);
    rename("../data/tmp.dat", PATIENT_FILE);

    // ✅ HTML + CSS Response
    printf("Content-Type:text/html\n\n");
    printf("<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Delete Patient</title>");
    printf("<style>");
    printf("body{font-family:Poppins,Arial;background:#0b0b0b;color:#eee;display:flex;align-items:center;justify-content:center;height:100vh;margin:0;}");
    printf(".box{background:#1a1a1a;border:1px solid rgba(255,255,255,0.1);border-radius:15px;padding:40px 60px;text-align:center;box-shadow:0 0 20px rgba(255,0,0,0.2);}");
    printf("h2{color:#ff4d4d;margin-bottom:10px;}");
    printf("p{color:#bbb;font-size:16px;margin-bottom:25px;}");
    printf(".btn{background:linear-gradient(90deg,#ff0000,#cc0000);color:#fff;padding:10px 20px;border:none;border-radius:8px;font-weight:600;text-decoration:none;transition:0.3s;}");
    printf(".btn:hover{background:#e60000;transform:scale(1.05);}");
    printf("</style></head><body>");

    printf("<div class='box'>");
    if (found) {
        printf("<h2>🗑️ Patient Deleted Successfully</h2>");
        printf("<p>The patient's record has been permanently removed.</p>");
    } else {
        printf("<h2>⚠️ Patient Not Found</h2>");
        printf("<p>No record exists with the given ID.</p>");
    }
    printf("<a href='/hospital/patients.html' class='btn'>⬅ Back to Patients</a>");
    printf("</div></body></html>");

    return 0;
}
