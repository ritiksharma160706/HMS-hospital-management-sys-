#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define APPT_FILE "../data/appointments.dat"
#define PATIENT_FILE "../data/patients.dat"
#define DOCTOR_FILE "../data/doctors.dat"

typedef struct {
    int id;
    char name[100];
    char phone[20];
} Patient;

typedef struct {
    int id;
    char name[100];
    char specialty[100];
} Doctor;

typedef struct {
    int id, patient_id, doctor_id;
    char patient_name[100];
    char doctor_name[100];
    char date[20];
    char time_slot[20];
    char status[30];
    char notes[200];
} Appointment;

// Replace + with space
void decode_spaces(char *str) {
    for (int i = 0; str[i]; i++)
        if (str[i] == '+') str[i] = ' ';
}

// Decode URL encoding like %3A -> :
void urldecode(char *dst, const char *src) {
    char a, b;
    while (*src) {
        if ((*src == '%') &&
            ((a = src[1]) && (b = src[2])) &&
            (isxdigit(a) && isxdigit(b))) {
            if (a >= 'a') a -= 'a' - 'A';
            if (a >= 'A') a -= ('A' - 10);
            else a -= '0';
            if (b >= 'a') b -= 'a' - 'A';
            if (b >= 'A') b -= ('A' - 10);
            else b -= '0';
            *dst++ = 16 * a + b;
            src += 3;
        } else if (*src == '+') {
            *dst++ = ' ';
            src++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}

char *getPatientName(int pid) {
    static char name[100] = "Unknown";
    FILE *f = fopen(PATIENT_FILE, "rb");
    if (!f) return name;
    Patient p;
    while (fread(&p, sizeof(Patient), 1, f))
        if (p.id == pid) { strcpy(name, p.name); break; }
    fclose(f);
    return name;
}

char *getDoctorName(int did) {
    static char name[100] = "Unknown";
    FILE *f = fopen(DOCTOR_FILE, "rb");
    if (!f) return name;
    Doctor d;
    while (fread(&d, sizeof(Doctor), 1, f))
        if (d.id == did) { strcpy(name, d.name); break; }
    fclose(f);
    return name;
}

int next_id() {
    FILE *f = fopen(APPT_FILE, "rb");
    if (!f) return 1;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return (size / sizeof(Appointment)) + 1;
}

int main() {
    printf("Content-Type:text/html\n\n");

    char *query = getenv("QUERY_STRING");
    if (!query) {
        printf("<html><body><h3 style='color:red;'>Invalid Request</h3></body></html>");
        return 0;
    }

    Appointment a;
    char pid_str[10], did_str[10], date_raw[100], time_raw[100], notes_raw[300];

    // handle both possible naming styles: pid/did OR patient_id/doctor_id
    sscanf(query,
           "pid=%9[^&]&did=%9[^&]&date=%99[^&]&time=%99[^&]&notes=%299[^\n]",
           pid_str, did_str, date_raw, time_raw, notes_raw);

    if (strlen(pid_str) == 0 || strlen(did_str) == 0) {
        // fallback to patient_id/doctor_id pattern
        sscanf(query,
               "patient_id=%9[^&]&doctor_id=%9[^&]&date=%99[^&]&time_slot=%99[^&]&status=%29[^&]&notes=%299[^\n]",
               pid_str, did_str, date_raw, time_raw, a.status, notes_raw);
    } else {
        strcpy(a.status, "Scheduled");
    }

    urldecode(a.date, date_raw);
    urldecode(a.time_slot, time_raw);
    urldecode(a.notes, notes_raw);

    a.id = next_id();
    a.patient_id = atoi(pid_str);
    a.doctor_id = atoi(did_str);

    strcpy(a.patient_name, getPatientName(a.patient_id));
    strcpy(a.doctor_name, getDoctorName(a.doctor_id));

    FILE *f = fopen(APPT_FILE, "ab");
    if (f) {
        fwrite(&a, sizeof(Appointment), 1, f);
        fclose(f);
    }

    // ✅ Stylish Success Page
    printf("<html><head><title>Appointment Added</title>");
    printf("<style>"
           "body{background:#0d0d0d;color:#f5f5f5;font-family:'Segoe UI';margin:0;text-align:center;}"
           ".container{margin:120px auto;width:60%%;background:rgba(255,255,255,0.05);padding:50px;"
           "border-radius:16px;box-shadow:0 0 25px rgba(255,0,0,0.3);}"
           "h1{color:#00ff99;font-size:40px;text-shadow:0 0 15px #00ff99;animation:fadeIn 2s ease-in-out;}"
           "p{font-size:20px;margin:15px 0;color:#e0e0e0;}"
           ".btn{background:linear-gradient(90deg,#ff3333,#990000);color:white;padding:12px 20px;"
           "border-radius:6px;text-decoration:none;font-weight:bold;transition:0.3s;margin:10px;display:inline-block;}"
           ".btn:hover{background:linear-gradient(90deg,#ff0000,#660000);box-shadow:0 0 10px #ff3333;}"
           "@keyframes fadeIn{from{opacity:0;transform:translateY(-20px);}to{opacity:1;transform:translateY(0);}}"
           "</style></head><body>");
    printf("<div class='container'>");
    printf("<h1>Appointment Added Successfully!</h1>");
    printf("<p><strong>ID:</strong> %d</p>", a.id);
    printf("<p><strong>Patient:</strong> %s</p>", a.patient_name);
    printf("<p><strong>Doctor:</strong> %s</p>", a.doctor_name);
    printf("<p><strong>Date:</strong> %s | <strong>Time:</strong> %s</p>", a.date, a.time_slot);
    printf("<p><strong>Notes:</strong> %s</p>", a.notes);
    printf("<br><a class='btn' href='/cgi-bin/list_appointments.cgi'>View Appointments</a>");
    printf("<a class='btn' href='/hospital/dashboard.html'>Back to Dashboard</a>");
    printf("</div></body></html>");

    return 0;
}
