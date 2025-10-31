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

// Decode '+' to space (simple)
void decode_spaces(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '+') str[i] = ' ';
    }
}

int main() {
    FILE *f = fopen(PATIENT_FILE, "rb");

    printf("Content-Type:text/html\n\n");
    printf("<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Patient List</title>");
    printf("<style>");
    printf("body{background:#0b0b0b;color:#f2f2f2;font-family:Poppins,Arial;margin:0;padding:0;}");
    printf(".container{width:95%%;margin:30px auto;background:rgba(255,255,255,0.04);padding:25px;border-radius:12px;box-shadow:0 0 20px rgba(255,0,0,0.18);}");
    printf("h2{text-align:center;color:#ff3333;font-size:36px;text-shadow:0 0 8px #ff0000;margin-bottom:18px;}");
    printf("table{width:100%%;border-collapse:collapse;margin-top:10px;}");
    printf("th,td{border:1px solid rgba(255,255,255,0.06);padding:12px;text-align:left;vertical-align:top;}");
    printf("th{background:#1a0000;color:#ff4d4d;font-size:15px;}");
    printf("td{background:rgba(255,255,255,0.03);font-size:15px;color:#eef;}");
    printf("tr:hover{background:rgba(255,0,0,0.06);transition:0.15s;}");
    printf(".btn{background:linear-gradient(90deg,#ff0000,#990000);color:white;padding:8px 14px;border-radius:6px;text-decoration:none;font-weight:600;}");
    printf(".btn:hover{box-shadow:0 0 10px #ff3333;transform:scale(1.03);}"); 
    printf(".small{font-size:13px;color:#cfcfcf;}"); 
    printf("</style></head><body>");
    printf("<div class='container'>");
    printf("<h2>Patient Records</h2>");

    if (!f) {
        printf("<p style='text-align:center;color:#ff6666;'>No patients found.</p>");
        printf("<div style='text-align:center;margin-top:18px;'><a href='/hospital/dashboard.html' class='btn'>⬅ Back to Dashboard</a></div>");
        printf("</div></body></html>");
        return 0;
    }

    Patient p;
    printf("<table>");
    printf("<tr>");
    printf("<th>ID</th>");
    printf("<th>Name</th>");
    printf("<th>Age</th>");
    printf("<th>Gender</th>");
    printf("<th>Address</th>");   // NEW column
    printf("<th>Phone</th>");
    printf("<th>Disease</th>");
    printf("<th>Actions</th>");
    printf("</tr>");

    while (fread(&p, sizeof(Patient), 1, f) == 1) {
        // decode simple '+' sentinel if present
        decode_spaces(p.name);
        decode_spaces(p.gender);
        decode_spaces(p.address);
        decode_spaces(p.phone);
        decode_spaces(p.disease);

        printf("<tr>");
        printf("<td>%d</td>", p.id);
        printf("<td>%s</td>", p.name);
        printf("<td>%d</td>", p.age);
        printf("<td>%s</td>", p.gender);

        // Address cell (wrap long text)
        printf("<td><div class='small'>%s</div></td>", p.address);

        printf("<td>%s</td>", p.phone);
        printf("<td>%s</td>", p.disease);

        // Delete action
        printf("<td><a class='btn' href='/cgi-bin/delete_patient.cgi?id=%d'>Delete</a></td>", p.id);


        printf("</tr>");
    }

    fclose(f);

    printf("</table>");
    printf("<div style='text-align:center;margin-top:18px;'><a href='/hospital/dashboard.html' class='btn'>⬅ Back to Dashboard</a></div>");
    printf("</div></body></html>");
    return 0;
}
