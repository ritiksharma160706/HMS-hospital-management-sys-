# Hospital Management System (C Language)

### **📘 Overview**

This Hospital Management System is a console-based project developed in C language.
It efficiently manages hospital records such as patient details, doctor information, and appointment scheduling — all through a clean file-handling approach (no database required).

The project demonstrates strong fundamentals of C programming, including:

File handling (binary .dat files)

Structs and data organization

Modular coding structure

Input validation and formatted output




### **⚙️ Features**

### **👨‍⚕️ Patient Management**

Add, view, update, and delete patient records

Stores name, age, gender, phone number, address, and disease details

Automatically assigns unique patient IDs




### **🩺 Doctor Management**

Add and list doctors with name, specialization, and ID

Easily assign doctors to patients or appointments



### **📅 Appointment Scheduling**

Book new appointments between patients and doctors

Displays existing appointments in a styled HTML table

Delete or modify appointments dynamically



### **💵 Billing System**

Automatically generate hospital bills for patients

Includes breakdown of consultation, tests, medicines, and tax

Displays a styled HTML bill with modern UI formatting



### **🧠 Technologies Used**

Language: C

Concepts: File Handling, Structs, Pointers, CGI (Common Gateway Interface)

Output: Dynamic HTML pages via C programs

Files Used:

patients.dat

doctors.dat

appointments.dat



### **🖥️ How It Works**

All CGI programs are placed inside the /cgi-bin/ folder.

Data files (.dat) are stored inside /data/ directory.

HTML pages (Dashboard, Forms, Lists) call corresponding .cgi programs for dynamic functionality.

Each module (Add, List, Delete) interacts with binary data files to display updated information.



### **📁 Project Structure**
hospital-management/
│
├── cgi-bin/
│   ├── add_patient.c
│   ├── list_patients.c
│   ├── delete_patient.c
│   ├── add_doctor.c
│   ├── list_doctors.c
│   ├── add_appointment.c
│   ├── list_appointments.c
│   └── delete_appointment.c
│
├── data/
│   ├── patients.dat
│   ├── doctors.dat
│   └── appointments.dat
│
├── hospital/
│   ├── dashboard.html
│   ├── billing.html
│   └── forms/
│
└── README.md



### **🚀 Future Enhancements**

Add login/authentication for admin & staff

Integrate database (MySQL) for scalability

Add report generation (PDF/Excel)

Improve UI using modern web frameworks


### **🧑‍💻 Author**

Ritik Sharma
🎓 Computer Science Student
💡 Passionate about C programming, system design, and building impactful software solutions.

🔗 Connect on LinkedIn:(https://www.linkedin.com/in/ritik-sharma-91465b2a8/)

⭐ If you like this project, don’t forget to star the repo!
