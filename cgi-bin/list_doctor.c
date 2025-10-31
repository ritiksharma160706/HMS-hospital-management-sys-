#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOCTOR_FILE "../data/doctors.dat"

typedef struct {
    int id;
    char name[100];
    char specialization[60];
    char phone[20];
    float fee;
} Doctor;

void decode_spaces(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '+') str[i] = ' ';
    }
}

int main() {
    FILE *f = fopen(DOCTOR_FILE, "rb");
    if (!f) {
        printf("Content-Type:text/html\n\n");
        printf("<html><body><h3 style='text-align:center; color:#ff3333;'>No Doctors Found!</h3></body></html>");
        return 0;
    }

    Doctor d;
    printf("Content-Type:text/html\n\n");
    printf("<html><head>");
    printf("<title>Doctor List - CityCare</title>");
    printf("<style>");
    printf("body { background-color:#0d0d0d; color:#f5f5f5; font-family:'Segoe UI',sans-serif; margin:0; }");
    printf(".container { width:90%%; margin:40px auto; background:rgba(255,255,255,0.05); padding:30px; border-radius:12px; box-shadow:0 0 20px rgba(255,0,0,0.2); }");
    printf("h2 { text-align:center; color:#ff3333; font-size:36px; margin-bottom:30px; text-shadow:0 0 10px #ff0000; }");
    printf("table { width:100%%; border-collapse:collapse; margin-top:20px; }");
    printf("th, td { border:1px solid rgba(255,255,255,0.1); padding:12px; text-align:left; }");
    printf("th { background:#1a0000; color:#ff4d4d; font-size:18px; }");
    printf("td { background:rgba(255,255,255,0.03); font-size:16px; }");
    printf("tr:hover { background:rgba(255,0,0,0.1); }");
    printf(".btn { background:linear-gradient(90deg,#ff3333,#990000); color:white; padding:8px 16px; border-radius:6px; text-decoration:none; font-weight:bold; transition:0.3s; }");
    printf(".btn:hover { background:linear-gradient(90deg,#ff0000,#660000); box-shadow:0 0 10px #ff3333; }");
    printf("</style></head><body>");

    printf("<div class='container'>");
    printf("<h2>Doctor List</h2>");
    printf("<table>");
    printf("<tr><th>ID</th><th>Name</th><th>Specialization</th><th>Phone</th><th>Consultation Fee (₹)</th><th>Actions</th></tr>");

    while (fread(&d, sizeof(Doctor), 1, f) == 1) {
        decode_spaces(d.name);
        decode_spaces(d.specialization);
        decode_spaces(d.phone);

        printf("<tr>");
        printf("<td>%d</td>", d.id);
        printf("<td>%s</td>", d.name);
        printf("<td>%s</td>", d.specialization);
        printf("<td>%s</td>", d.phone);
        printf("<td>%.2f</td>", d.fee);
        printf("<td><a class='btn' href='/cgi-bin/delete_doctor.cgi?id=%d'>Delete</a></td>", d.id);
        printf("</tr>");
    }

    printf("</table>");
    printf("<div style='text-align:center;'><br>");
    printf("<a href='/hospital/dashboard.html' class='btn'>Back to Dashboard</a>");
    printf("</div></div></body></html>");

    fclose(f);
    return 0;
}
