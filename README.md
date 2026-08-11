# 🏥 Medical Information Management System

> A role-based **Patient & Medical Information Management System** developed in C for managing patient records, prescriptions, medical reports, nurses, doctors, and pharmacy information.

---

## 🌐 Project Overview

The **Medical Information Management System** is a console-based application designed to simulate a basic hospital information management environment.

The system provides four independent user roles:

```text
Doctor
Patient
Nurse
Pharmacist
```

Each role receives access to different features according to its responsibilities.

The project is implemented entirely in **C** using structures, arrays, functions, string handling, authentication logic, and file handling.

---

## 🎯 Objectives

The main objectives of this project are to:

* Manage patient information
* Maintain medical records
* Manage prescriptions
* Assign doctors and nurses
* Track patient departments and beds
* Provide role-based access
* Search patient records
* Generate medical reports
* Demonstrate practical C programming concepts

---

## 👥 User Management

```text
                         ┌─────────────┐
                         │    SYSTEM   │
                         └──────┬──────┘
                                │
       ┌────────────┬──────────┼──────────┬────────────┐
       │            │          │          │            │
       ▼            ▼          ▼          ▼            │
    Doctor       Patient     Nurse    Pharmacist       │
       │            │          │          │            │
       ▼            ▼          ▼          ▼            │
   Manage       View Own   Assigned    Medicine       │
   Records      Records    Patients     Records       │
       │                                                │
       └────────────────────────────────────────────────┘
```

---

# 🩺 Doctor Module

The Doctor module is responsible for managing patient records.

### Capabilities

```text
✓ Register new patients
✓ Search patients
✓ View all patients
✓ View complete medical records
✓ Edit patient information
✓ Update diagnosis
✓ Update medical reports
✓ Add medicines
✓ Remove medicines
✓ Generate patient reports
```

The doctor menu contains options for registering, searching, viewing patients, and logging out.

---

# 👤 Patient Module

Patients have a simplified portal focused on viewing their own medical information.

### Patient Authentication

```text
Username → Patient Name
Password → Date of Birth
```

### Patient Features

```text
✓ View personal information
✓ View diagnosis
✓ View medical report
✓ View prescription
✓ View doctor
✓ View assigned nurses
✓ View department
✓ View bed number
✓ Generate personal report
```

The patient portal intentionally provides viewing functionality rather than editing medical records.

---

# 👩‍⚕️ Nurse Module

Nurses can access patients assigned to them.

### Features

```text
✓ View assigned patients
✓ Search patient
✓ View disease
✓ View medicines
✓ View dosage
✓ View medicine schedule
✓ View assigned bed
✓ Generate patient report
```

The system checks the patient's assigned nurse fields when determining which patients appear in a nurse's list.

---

# 💊 Pharmacist Module

The pharmacist module focuses specifically on prescription information.

### Features

```text
✓ Search patient by ID
✓ View patient information
✓ View medicine list
✓ View dosage
✓ View duration
✓ View medicine schedule
✓ Generate medicine report
```

---

# 🧬 Patient Record

Each patient contains a complete medical profile.

```text
┌─────────────────────────────────┐
│          PATIENT RECORD         │
├─────────────────────────────────┤
│ Patient ID                      │
│ Name                            │
│ Date of Birth                   │
│ Gender                          │
│ Contact                         │
│ Department                      │
│                                 │
│ Symptoms                        │
│ Medical Tests                   │
│ Disease                         │
│ Medical Report                  │
│                                 │
│ Prescription                    │
│ ├── Medicine                    │
│ ├── Dosage                      │
│ ├── Time                        │
│ └── Duration                    │
│                                 │
│ Doctor                          │
│ Nurse(s)                        │
│ Bed Number                      │
└─────────────────────────────────┘
```

The `Patient` structure contains these fields, including an array of `Medicine` records.

---

# 💊 Medicine Structure

Each prescription stores four pieces of information:

```text
Medicine
│
├── Name
├── Dosage
├── Time
└── Duration
```

Example:

```text
Napa 500 mg
├── Dosage   : 1 Tablet
├── Time     : Morning, Afternoon, Night
└── Duration : 5 Days
```

---

# 🔑 Authentication System

The project contains separate login functions for every role.

```text
main()
 │
 ├── Doctor Login
 │
 ├── Patient Login
 │
 ├── Nurse Login
 │
 └── Pharmacist Login
```

The main program routes the selected login option to the appropriate authentication module.

---

# 📄 Report System

One of the key features is automatic report generation.

### Reports

| User       | Report                  |
| ---------- | ----------------------- |
| Doctor     | Complete Patient Report |
| Patient    | Personal Medical Report |
| Nurse      | Assigned Patient Report |
| Pharmacist | Medicine Report         |

Reports are generated as plain-text `.txt` files using C file handling.

---

# 🗂️ Data Organization

The application uses an in-memory array:

```c
Patient patients[MAX_PATIENTS];
```

Current limits:

```text
Maximum Patients       : 100
Maximum Medicines      : 10 / patient
```

---

# 🧪 Built-in Test Data

The application starts with sample patient records.

### P1001

```text
Name       : Obidul
Disease    : Dengue Fever
Department : Medicine Ward
Bed        : M-101
```

### P1002

```text
Name       : Shahedul
Disease    : Pneumonia
Department : Medicine Ward
Bed        : M-102
```

### P1003

```text
Name       : Sabbir
Disease    : Typhoid
Department : General Ward
Bed        : G-103
```

These records are initialized by the `seedPatients()` function.

---

# ⚙️ Technology Stack

```text
Language       C
Compiler       GCC / MinGW / Clang
Interface      Command Line
Storage        Runtime Memory
Reports        TXT Files
Architecture   Role-Based Menu System
```

### Standard Libraries

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
```

---

# 🚀 Getting Started

## Requirements

Install any C compiler such as:

* GCC
* MinGW
* Clang

---

## Clone

```bash
git clone https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git
cd YOUR-REPOSITORY
```

---

## Compile

```bash
gcc patient-and-medical-information-management-system3.c -o medical_system
```

---

## Run

### Windows

```bash
medical_system.exe
```

### Linux / macOS

```bash
./medical_system
```

---

# 🖥️ Application Flow

```text
START
  │
  ▼
MAIN MENU
  │
  ├──── Doctor ────► Doctor Portal
  │
  ├──── Patient ───► Patient Portal
  │
  ├──── Nurse ─────► Nurse Portal
  │
  ├──── Pharmacist ► Pharmacist Portal
  │
  └──── Exit
          │
          ▼
         END
```

---

# 📌 Project Structure

```text
📦 Medical-Information-Management-System
│
├── 📄 patient-and-medical-information-management-system3.c
│
├── 📄 README.md
│
└── 📁 reports/
    └── Generated .txt reports
```

---

# 🔐 Demo Credentials

> These credentials are part of the current source implementation and are intended only for demonstration.

| Role       | Username       | Password         |
| ---------- | -------------- | ---------------- |
| Doctor     | `Dr. Mohammad` | `mohammad123`    |
| Nurse A    | `Nurse A`      | `nursea123`      |
| Nurse B    | `Nurse B`      | `nurseb123`      |
| Pharmacist | `Pharmacist A` | `pharmacista123` |
| Patient    | Patient Name   | Date of Birth    |

---

# ⚠️ Disclaimer

This project is intended for **educational purposes only**.

It is **not a production-ready healthcare application**.

The current implementation does not provide:

* Database persistence
* Password encryption
* Secure authentication
* Data encryption
* User session management
* Audit logging
* Medical-data compliance
* Network security

Therefore, **do not use real patient information** with this application.

---

# 🔮 Future Development

```text
                         CURRENT
                            │
                            ▼
                   Console Application
                            │
             ┌──────────────┼──────────────┐
             ▼              ▼              ▼
          Database        Security         UI
             │              │              │
             ▼              ▼              ▼
          SQLite/        Password        GUI/Web
          MySQL          Hashing         Interface
             │              │              │
             └──────────────┼──────────────┘
                            ▼
                   Advanced Hospital
                   Management System
```

### Planned Features

* [ ] Database integration
* [ ] Persistent patient records
* [ ] Secure password hashing
* [ ] Advanced role permissions
* [ ] Appointment system
* [ ] Bed management
* [ ] Medicine inventory
* [ ] Billing system
* [ ] Patient history
* [ ] PDF reports
* [ ] GUI application
* [ ] Web application
* [ ] Data backup and recovery

---

# 📚 Concepts Demonstrated

This project is particularly useful for practicing:

```text
C Programming
│
├── Structures
├── Nested Structures
├── Arrays
├── Functions
├── Pointers
├── Strings
├── Loops
├── Conditions
├── File Handling
├── Searching
├── Authentication
└── Menu-Driven Programming
```

---

# 🎓 Academic Use

This project can be used as a demonstration of:

* Structured programming
* Data organization
* Function-based modular design
* Basic information management
* File operations
* Role-based application design

---

# 👨‍💻 Author

**Obidul Haque**

> C Programming Project — Patient & Medical Information Management System

---

# ⭐ Support

If you found this project useful, feel free to ⭐ **Star** the repository.

---

<p align="center">

**Built with C ❤️**

</p>
