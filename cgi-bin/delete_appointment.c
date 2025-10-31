#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APPT_FILE "../data/appointments.dat"
#define TEMP_FILE "../data/temp.dat"

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
    printf("Content-Type:text/html\n\n");

    char *data = getenv("QUERY_STRING");
    if (!data || strlen(data) == 0) {
        printf("<html><body style='background:#0d0d0d;color:#ff3333;text-align:center;'>");
        printf("<h2>Invalid Request! No ID provided.</h2></body></html>");
        return 0;
    }

    int delete_id = 0;
    sscanf(data, "id=%d", &delete_id);

    FILE *f = fopen(APPT_FILE, "rb");
    FILE *temp = fopen(TEMP_FILE, "wb");

    if (!f || !temp) {
        printf("<html><body style='background:#0d0d0d;color:#ff3333;text-align:center;'>");
        printf("<h2>Error: Unable to open appointment files!</h2></body></html>");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return 0;
    }

    Appointment a;
    int found = 0;

    while (fread(&a, sizeof(Appointment), 1, f) == 1) {
        if (a.id == delete_id) {
            found = 1;
            continue;
        }
        fwrite(&a, sizeof(Appointment), 1, temp);
    }

    fclose(f);
    fclose(temp);

    remove(APPT_FILE);
    rename(TEMP_FILE, APPT_FILE);

    printf("<html><head><title>Delete Appointment</title>");
    printf("<style>"
           "body{background:#0d0d0d;color:#f5f5f5;font-family:'Segoe UI';text-align:center;margin:0;}"
           ".container{margin:100px auto;width:60%%;background:rgba(255,255,255,0.05);padding:40px;"
           "border-radius:12px;box-shadow:0 0 20px rgba(255,0,0,0.2);}"
           "h2{color:#ff3333;text-shadow:0 0 10px #ff0000;}"
           ".btn{background:linear-gradient(90deg,#ff3333,#990000);color:white;padding:10px 18px;"
           "border-radius:6px;text-decoration:none;font-weight:bold;transition:0.3s;}"
           ".btn:hover{background:linear-gradient(90deg,#ff0000,#660000);box-shadow:0 0 10px #ff3333;}"
           "</style></head><body>");
    printf("<div class='container'>");

    if (found)
        printf("<h2>Appointment ID %d Deleted Successfully!</h2>", delete_id);
    else
        printf("<h2>No Appointment Found with ID %d!</h2>", delete_id);

    printf("<br><a class='btn' href='/cgi-bin/list_appointments.cgi'>Back to Appointments</a>");
    printf("</div></body></html>");

    return 0;
}
