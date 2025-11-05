# 🏥 **Hospital Management System (HMS)**  

## **📘 Overview**
The **Hospital Management System (HMS)** is a mini-project developed in **C language** using **File Handling**.  
It provides a simple, efficient way to manage **patients**, **doctors**, and **appointments** in a hospital setup.  
The system runs as a **CGI-based web application**, styled with a **modern black and red theme** for a clean interface.  

---

## **✨ Features**
- **🧑‍⚕️ Doctor Management:** Add, view, and manage doctor records (name, specialization, contact info).  
- **🧍 Patient Management:** Add, update, and display patient details like age, gender, disease, and phone number.  
- **📅 Appointment Scheduling:** Create, list, and delete appointments between patients and doctors.  
- **💰 Billing System:** Automatically generate bills with consultation fees, tests, medicines, and tax summary.  
- **🧾 Data Persistence:** All information is stored in **binary data files** using file handling.  

---

## **🛠️ Technologies Used**
- **Language:** C (CGI Programming)  
- **Backend:** File Handling (`.dat` files)  
- **Frontend:** HTML + Inline CSS  
- **Theme:** Black & Red (Dark Modern UI)  

---

## **📂 Project Structure**
/hospital
│
├── cgi-bin/
│ ├── add_patient.c
│ ├── list_patients.c
│ ├── add_doctor.c
│ ├── list_doctors.c
│ ├── add_appointment.c
│ ├── list_appointments.c
│ ├── delete_appointment.c
│ ├── bill_generate.c
│
├── data/
│ ├── patients.dat
│ ├── doctors.dat
│ ├── appointments.dat
│
├── html/
│ ├── dashboard.html
│ ├── patients.html
│ ├── doctors.html
│ ├── appointments.html
│ ├── billing.html
│
└── README.md



---

## **🚀 How to Run**
1. Install and configure **Apache** (with CGI enabled).  
2. Place all `.c` files inside your server’s **cgi-bin** directory.  
3. Compile using:
   ```bash
   gcc filename.c -o filename.cgi
   
4.Make sure the .dat files are inside the ../data/ directory.

5.Open your browser and run:

http://localhost/hospital/dashboard.html


## **💡 Future Enhancements**

Add login system for admin and doctors.

Include search filters for patients and appointments.

Generate downloadable PDF invoices for bills.

Add email/SMS notifications for appointments.

## **👨‍💻 Author**

## Ritik Sharma
🎓 Computer Science Student | 💻 Developer | 🚀 Passionate about C Programming

## **🖤 Theme Preview**

The project uses a black & red modern interface with gradients, hover effects, and glowing buttons for a futuristic hospital dashboard experience.
