#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOCTOR_FILE "../data/doctors.dat"

typedef struct {
    int id;
    char name[100];
    char specialization[60];
    char phone[20];
} Doctor;

int main() {
    char *data = getenv("QUERY_STRING");
    int id;
    if (!data || sscanf(data, "id=%d", &id) != 1) {
        printf("Content-Type:text/html\n\n<html><body><h3>Invalid Request!</h3></body></html>");
        return 0;
    }

    FILE *f = fopen(DOCTOR_FILE, "rb");
    if (!f) {
        printf("Content-Type:text/html\n\n<html><body><h3>Error opening doctor file!</h3></body></html>");
        return 0;
    }

    FILE *temp = fopen("../data/temp.dat", "wb");
    Doctor d;
    int found = 0;

    while (fread(&d, sizeof(Doctor), 1, f) == 1) {
        if (d.id != id)
            fwrite(&d, sizeof(Doctor), 1, temp);
        else
            found = 1;
    }

    fclose(f);
    fclose(temp);

    remove(DOCTOR_FILE);
    rename("../data/temp.dat", DOCTOR_FILE);

    printf("Content-Type:text/html\n\n");
    printf("<html><head><title>Doctor Deleted</title>");
    printf("<style>");
    printf("body { background-color:#0d0d0d; color:white; font-family:'Segoe UI'; text-align:center; }");
    printf(".box { margin-top:100px; background:rgba(255,255,255,0.05); padding:40px; border-radius:12px; display:inline-block; box-shadow:0 0 25px rgba(255,0,0,0.3); }");
    printf(".btn { display:inline-block; margin-top:20px; background:linear-gradient(90deg,#ff3333,#990000); color:white; padding:10px 20px; border-radius:8px; text-decoration:none; font-weight:bold; transition:0.3s; }");
    printf(".btn:hover { background:linear-gradient(90deg,#ff0000,#660000); box-shadow:0 0 10px #ff3333; }");
    printf("</style></head><body>");
    printf("<div class='box'>");
    if (found)
        printf("<h2>Doctor Deleted Successfully</h2>");
    else
        printf("<h2>Doctor Not Found</h2>");
    printf("<a href='/hospital/doctors.html' class='btn'>Back to Doctors</a>");
    printf("</div></body></html>");
    return 0;
}
