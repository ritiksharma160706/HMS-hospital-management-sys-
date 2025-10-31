#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APPT_FILE "../data/appointments.dat"

typedef struct {
    int id, patient_id, doctor_id;
    char patient_name[100];
    char doctor_name[100];
    char date[20];
    char time_slot[20];
    char status[30];
    char notes[200];
} Appointment;

int main() {
    FILE *f = fopen(APPT_FILE, "rb");
    printf("Content-Type:text/html\n\n");

    if (!f) {
        printf("<html><body style='background:#0d0d0d;color:#ff3333;text-align:center;font-family:Segoe UI;'>");
        printf("<h2>No Appointments Found!</h2><p>File: %s</p></body></html>", APPT_FILE);
        return 0;
    }

    Appointment a;
    printf("<html><head><title>Appointment List - CityCare</title>");
    printf("<style>"
           "body{background:#0d0d0d;color:#f5f5f5;font-family:'Segoe UI';margin:0;}"
           ".container{width:90%%;margin:40px auto;background:rgba(255,255,255,0.05);padding:30px;"
           "border-radius:12px;box-shadow:0 0 20px rgba(255,0,0,0.2);}"
           "h2{text-align:center;color:#ff3333;font-size:36px;margin-bottom:30px;text-shadow:0 0 10px #ff0000;}"
           "table{width:100%%;border-collapse:collapse;margin-top:20px;}"
           "th,td{border:1px solid rgba(255,255,255,0.1);padding:12px;text-align:left;}"
           "th{background:#1a0000;color:#ff4d4d;font-size:18px;}"
           "td{background:rgba(255,255,255,0.03);font-size:16px;}"
           "tr:hover{background:rgba(255,0,0,0.1);}"
           ".btn{background:linear-gradient(90deg,#ff3333,#990000);color:white;padding:8px 16px;border-radius:6px;"
           "text-decoration:none;font-weight:bold;transition:0.3s;}"
           ".btn:hover{background:linear-gradient(90deg,#ff0000,#660000);box-shadow:0 0 10px #ff3333;}"
           "</style></head><body>");
    printf("<div class='container'><h2>Appointment List</h2>");
    printf("<table><tr>"
           "<th>ID</th><th>Patient</th><th>Doctor</th><th>Date</th><th>Time</th>"
           "<th>Status</th><th>Notes</th><th>Action</th></tr>");

    while (fread(&a, sizeof(Appointment), 1, f) == 1) {
        printf("<tr>");
        printf("<td>%d</td>", a.id);
        printf("<td>%s (ID %d)</td>", a.patient_name, a.patient_id);
        printf("<td>%s (ID %d)</td>", a.doctor_name, a.doctor_id);
        printf("<td>%s</td>", a.date);
        printf("<td>%s</td>", a.time_slot);
        printf("<td>%s</td>", a.status);
        printf("<td>%s</td>", strlen(a.notes) > 0 ? a.notes : "-");
        printf("<td><a class='btn' href='/cgi-bin/delete_appointment.cgi?id=%d'>Delete</a></td>", a.id);
        printf("</tr>");
    }

    printf("</table><div style='text-align:center;'><br>"
           "<a href='/hospital/dashboard.html' class='btn'>Back</a></div></div></body></html>");

    fclose(f);
    return 0;
}
