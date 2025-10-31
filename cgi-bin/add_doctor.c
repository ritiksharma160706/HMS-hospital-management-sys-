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

int next_id() {
    FILE *f = fopen(DOCTOR_FILE, "rb");
    if (!f) return 1;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fclose(f);
    return (sz <= 0) ? 1 : (int)(sz / sizeof(Doctor)) + 1;
}

int main() {
    char *data = getenv("QUERY_STRING");
    char name[100] = "", spec[60] = "", phone[20] = "";
    float fee = 0.0;

    if (data)
        sscanf(data, "name=%99[^&]&spec=%59[^&]&phone=%19[^&]&fee=%f", name, spec, phone, &fee);

    Doctor d;
    d.id = next_id();
    strcpy(d.name, name);
    strcpy(d.specialization, spec);
    strcpy(d.phone, phone);
    d.fee = fee;

    FILE *f = fopen(DOCTOR_FILE, "ab");
    if (f) {
        fwrite(&d, sizeof(Doctor), 1, f);
        fclose(f);
    }

    printf("Content-Type:text/html\n\n");
    printf("<html><head>");
    printf("<title>Doctor Added - CuCare</title>");
    printf("<link rel='stylesheet' href='/hospital/style.css'>");
    printf("<style>");
    printf("body { background-color: #0d0d0d; color: #f5f5f5; font-family: 'Segoe UI', sans-serif; margin: 0; }");
    printf(".container { width: 70%%; margin: 80px auto; background: rgba(255,255,255,0.05); padding: 40px; border-radius: 12px; box-shadow: 0 0 25px rgba(255,0,0,0.25); text-align: center; }");
    printf("h2 { color: #ff3333; font-size: 38px; text-shadow: 0 0 10px #ff0000; margin-bottom: 20px; }");
    printf("p { font-size: 18px; margin: 15px 0; }");
    printf(".details { background: rgba(255,255,255,0.07); padding: 15px; border-radius: 10px; display: inline-block; margin-top: 10px; }");
    printf(".btn { display: inline-block; margin-top: 30px; background: linear-gradient(90deg,#ff3333,#990000); color: white; padding: 12px 24px; border-radius: 8px; text-decoration: none; font-weight: bold; transition: 0.3s; }");
    printf(".btn:hover { background: linear-gradient(90deg,#ff0000,#660000); box-shadow: 0 0 10px #ff3333; transform: scale(1.05); }");
    printf("</style>");
    printf("</head><body>");

    printf("<div class='container'>");
    printf("<h2>Doctor Added Successfully</h2>");
    printf("<a href='/hospital/doctors.html' class='btn'>Back to Doctors</a>");
    printf("</div>");

    printf("</body></html>");
    return 0;
}
