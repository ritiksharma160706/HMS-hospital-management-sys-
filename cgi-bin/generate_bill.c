#include <stdio.h>
#include <stdlib.h>
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
    int pid;
    sscanf(data, "pid=%d", &pid);

    FILE *f = fopen(PATIENT_FILE, "rb");
    Patient p;
    int found = 0;

    if (f) {
        while (fread(&p, sizeof(Patient), 1, f) == 1) {
            if (p.id == pid) {
                found = 1;
                break;
            }
        }
        fclose(f);
    }

    printf("Content-Type:text/html\n\n");
    printf("<html><head><title>Patient Bill</title>");
    printf("<style>"
           "body{background:#0d0d0d;color:#f5f5f5;font-family:'Segoe UI';margin:0;text-align:center;}"
           ".container{margin:120px auto;width:70%%;background:rgba(255,255,255,0.05);padding:50px;"
           "border-radius:16px;box-shadow:0 0 25px rgba(255,0,0,0.3);animation:fadeIn 1.5s ease-in-out;}"
           "h1{color:#00ff99;font-size:42px;text-shadow:0 0 15px #00ff99;margin-bottom:30px;}"
           "table{width:80%%;margin:0 auto;border-collapse:collapse;}"
           "th,td{padding:12px;border-bottom:1px solid rgba(255,255,255,0.2);}"
           "th{color:#00ff99;font-size:18px;}"
           "td{font-size:17px;color:#f0f0f0;}"
           ".total{font-weight:bold;color:#ff5555;text-shadow:0 0 10px #ff5555;}"
           ".btn{background:linear-gradient(90deg,#ff3333,#990000);color:white;padding:12px 24px;"
           "border-radius:8px;text-decoration:none;font-weight:bold;transition:0.3s;margin:20px;display:inline-block;}"
           ".btn:hover{background:linear-gradient(90deg,#ff0000,#660000);box-shadow:0 0 10px #ff3333;}"
           "@keyframes fadeIn{from{opacity:0;transform:translateY(-20px);}to{opacity:1;transform:translateY(0);}}"
           "</style></head><body>");

    if (found) {
        double consultation = 500, tests = 200, meds = 300, other = 100;
        double subtotal = consultation + tests + meds + other;
        double tax = subtotal * 0.05;
        double total = subtotal + tax;

        printf("<div class='container'>");
        printf("<h1>Hospital Billing System</h1>");
        printf("<h2 style='color:#00ffff;text-shadow:0 0 10px #00ffff;'>Patient Bill Details</h2>");
        printf("<p><strong>Name:</strong> %s<br><strong>Age:</strong> %d<br><strong>Gender:</strong> %s<br>"
               "<strong>Phone:</strong> %s<br><strong>Disease:</strong> %s</p>",
               p.name, p.age, p.gender, p.phone, p.disease);

        printf("<table>"
               "<tr><th>Particulars</th><th>Amount (₹)</th></tr>"
               "<tr><td>Consultation</td><td>%.2f</td></tr>"
               "<tr><td>Tests</td><td>%.2f</td></tr>"
               "<tr><td>Medicines</td><td>%.2f</td></tr>"
               "<tr><td>Other Charges</td><td>%.2f</td></tr>"
               "<tr><td><strong>Subtotal</strong></td><td>%.2f</td></tr>"
               "<tr><td><strong>Tax (5%%)</strong></td><td>%.2f</td></tr>"
               "<tr><td class='total'><strong>Total</strong></td><td class='total'>%.2f</td></tr>"
               "</table>",
               consultation, tests, meds, other, subtotal, tax, total);

        printf("<br><a class='btn' href='/hospital/dashboard.html'>Back to Dashboard</a>");
        printf("<a class='btn' href='/hospital/billing.html'>New Bill</a>");
        printf("</div>");
    } else {
        printf("<div class='container'>");
        printf("<h1 style='color:#ff5555;text-shadow:0 0 15px #ff5555;'>Patient Not Found!</h1>");
        printf("<a class='btn' href='/hospital/billing.html'>Try Again</a>");
        printf("</div>");
    }

    printf("</body></html>");
    return 0;
}
