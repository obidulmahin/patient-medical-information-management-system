/* =========================================================
   PATIENT AND MEDICAL INFORMATION MANAGEMENT SYSTEM
   -----------------------------------------------------------
   Roles   : Doctor, Patient, Nurse, Pharmacist
   Features: Registration, search, view/edit records,
             prescriptions, role-based report file export
   ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATIENTS 100
#define MAX_MEDS     10

/* ---------------------------------------------------------
   DATA STRUCTURES
   --------------------------------------------------------- */
typedef struct {
    char name[60];
    char dosage[30];
    char time[60];
    char duration[30];
} Medicine;

typedef struct {
    char id[10];
    char name[60];
    char dob[15];
    char gender[10];
    char contact[20];
    char department[50];
    char symptoms[250];
    char medicalTests[250];
    char disease[120];
    char medicalReport[600];
    Medicine medicines[MAX_MEDS];
    int  medCount;
    char bed[10];
    char nurse1[30];
    char nurse2[30];
    char doctorName[30];
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;
int nextIdNumber = 1001;

/* ---------------------------------------------------------
   UTILITY FUNCTIONS
   --------------------------------------------------------- */

/* Reads a full line safely into buffer, strips trailing newline */
void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) != NULL) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n')
            buf[len - 1] = '\0';
    } else {
        buf[0] = '\0';
    }
}

int readInt() {
    char line[50];
    readLine(line, sizeof(line));
    return atoi(line);
}

/* Case-insensitive substring/exact compare helper */
int sameTextCI(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return (*a == '\0' && *b == '\0');
}

void printLine(char ch, int count) {
    for (int i = 0; i < count; i++) putchar(ch);
    putchar('\n');
}

/* Prints text centered horizontally in the terminal (assumes an
   80-column-wide console, the standard default terminal width) */
#define CONSOLE_WIDTH 80
void printCentered(const char *text) {
    int len = (int)strlen(text);
    int padding = (CONSOLE_WIDTH - len) / 2;
    if (padding < 0) padding = 0;
    for (int i = 0; i < padding; i++) putchar(' ');
    printf("%s\n", text);
}

void pauseEnter() {
    printf("\nPress Enter to continue...");
    char tmp[10];
    readLine(tmp, sizeof(tmp));
}

/* Removes spaces from a name for safe use in filenames */
void sanitizeForFilename(const char *src, char *dst) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        char c = src[i];
        if (c == ' ')
            dst[j++] = '_';
        else if (isalnum((unsigned char)c) || c == '_')
            dst[j++] = c;
    }
    dst[j] = '\0';
}

/* ---------------------------------------------------------
   SAMPLE / SEED DATA
   --------------------------------------------------------- */
void seedPatients() {
    /* Patient P1001 - Obidul */
    Patient *p = &patients[patientCount++];
    strcpy(p->id, "P1001");
    strcpy(p->name, "Obidul");
    strcpy(p->dob, "26-02-2005");
    strcpy(p->gender, "Male");
    strcpy(p->contact, "01711223344");
    strcpy(p->department, "Medicine Ward");
    strcpy(p->symptoms, "High Fever, Severe Headache, Body Pain");
    strcpy(p->medicalTests, "CBC, Platelet Count, Dengue NS1 Antigen Test");
    strcpy(p->disease, "Dengue Fever");
    strcpy(p->medicalReport, "The patient has been diagnosed with Dengue Fever. Platelet count is below the normal range.");
    p->medCount = 3;
    strcpy(p->medicines[0].name, "Napa 500 mg");
    strcpy(p->medicines[0].dosage, "1 Tablet");
    strcpy(p->medicines[0].time, "Morning, Afternoon, Night");
    strcpy(p->medicines[0].duration, "5 Days");
    strcpy(p->medicines[1].name, "Orsaline");
    strcpy(p->medicines[1].dosage, "As Needed");
    strcpy(p->medicines[1].time, "Throughout the Day");
    strcpy(p->medicines[1].duration, "5 Days");
    strcpy(p->medicines[2].name, "Ceevit 500 mg");
    strcpy(p->medicines[2].dosage, "1 Tablet");
    strcpy(p->medicines[2].time, "Morning");
    strcpy(p->medicines[2].duration, "7 Days");
    strcpy(p->bed, "M-101");
    strcpy(p->nurse1, "Nurse A Day");
    strcpy(p->nurse2, "Nurse B Evening");
    strcpy(p->doctorName, "Dr. Mohammad");

    /* Patient P1002 - Shahedul */
    p = &patients[patientCount++];
    strcpy(p->id, "P1002");
    strcpy(p->name, "Shahedul");
    strcpy(p->dob, "23-01-2005");
    strcpy(p->gender, "Female");
    strcpy(p->contact, "01822334455");
    strcpy(p->department, "Medicine Ward");
    strcpy(p->symptoms, "Cough, Chest Pain, Shortness of Breath, Fever");
    strcpy(p->medicalTests, "Chest X-ray, CBC, Oxygen Saturation Test");
    strcpy(p->disease, "Pneumonia");
    strcpy(p->medicalReport, "The patient has been diagnosed with Pneumonia. Chest X-ray confirms lung infection. Antibiotic treatment and oxygen monitoring are advised.");
    p->medCount = 3;
    strcpy(p->medicines[0].name, "Azithromycin 500 mg");
    strcpy(p->medicines[0].dosage, "1 Tablet");
    strcpy(p->medicines[0].time, "Morning");
    strcpy(p->medicines[0].duration, "5 Days");
    strcpy(p->medicines[1].name, "Napa 500 mg");
    strcpy(p->medicines[1].dosage, "1 Tablet");
    strcpy(p->medicines[1].time, "Morning, Afternoon, Night");
    strcpy(p->medicines[1].duration, "5 Days");
    strcpy(p->medicines[2].name, "Ambrox Syrup");
    strcpy(p->medicines[2].dosage, "10 ml");
    strcpy(p->medicines[2].time, "Morning and Night");
    strcpy(p->medicines[2].duration, "7 Days");
    strcpy(p->bed, "M-102");
    strcpy(p->nurse1, "Nurse A Day");
    strcpy(p->nurse2, "Nurse B Evening");
    strcpy(p->doctorName, "Dr. Mohammad");

    /* Patient P1003 - Sabbir */
    p = &patients[patientCount++];
    strcpy(p->id, "P1003");
    strcpy(p->name, "Sabbir");
    strcpy(p->dob, "15-11-2004");
    strcpy(p->gender, "Male");
    strcpy(p->contact, "01933445566");
    strcpy(p->department, "General Ward");
    strcpy(p->symptoms, "High Fever, Abdominal Pain, Weakness, Loss of Appetite");
    strcpy(p->medicalTests, "Widal Test, CBC, Blood Culture");
    strcpy(p->disease, "Typhoid");
    strcpy(p->medicalReport, "The patient has been diagnosed with Typhoid Fever. Laboratory reports confirm Salmonella Typhi infection. Complete antibiotic therapy, adequate hydration, and proper nutrition are recommended.");
    p->medCount = 3;
    strcpy(p->medicines[0].name, "Ciprofloxacin 500 mg");
    strcpy(p->medicines[0].dosage, "1 Tablet");
    strcpy(p->medicines[0].time, "Morning and Night");
    strcpy(p->medicines[0].duration, "7 Days");
    strcpy(p->medicines[1].name, "Napa 500 mg");
    strcpy(p->medicines[1].dosage, "1 Tablet");
    strcpy(p->medicines[1].time, "Morning, Afternoon, Night");
    strcpy(p->medicines[1].duration, "5 Days");
    strcpy(p->medicines[2].name, "Zinc 20 mg");
    strcpy(p->medicines[2].dosage, "1 Tablet");
    strcpy(p->medicines[2].time, "Morning");
    strcpy(p->medicines[2].duration, "10 Days");
    strcpy(p->bed, "G-103");
    strcpy(p->nurse1, "Nurse A Day");
    strcpy(p->nurse2, "Nurse B Evening");
    strcpy(p->doctorName, "Dr. Mohammad");

    nextIdNumber = 1004;
}

/* ---------------------------------------------------------
   PATIENT LOOKUP HELPERS
   --------------------------------------------------------- */
int findPatientIndexByIdOrName(const char *key) {
    for (int i = 0; i < patientCount; i++) {
        if (sameTextCI(patients[i].id, key) || sameTextCI(patients[i].name, key))
            return i;
    }
    return -1;
}

int findPatientIndexByName(const char *name) {
    for (int i = 0; i < patientCount; i++) {
        if (sameTextCI(patients[i].name, name))
            return i;
    }
    return -1;
}

int findPatientIndexByNameDob(const char *name, const char *dob) {
    for (int i = 0; i < patientCount; i++) {
        if (sameTextCI(patients[i].name, name) && strcmp(patients[i].dob, dob) == 0)
            return i;
    }
    return -1;
}

/* ---------------------------------------------------------
   DISPLAY HELPERS
   --------------------------------------------------------- */
void printFullPatientRecord(Patient *p) {
    printf("\nID: %s\n", p->id);
    printf("Name: %s\n", p->name);
    printf("DOB: %s\n", p->dob);
    printf("Gender: %s\n", p->gender);
    printf("Contact: %s\n", p->contact);
    printf("Doctor Name: %s\n", p->doctorName);
    printf("Symptoms: %s\n", p->symptoms);
    printf("Medical Tests: %s\n", p->medicalTests);
    printf("Disease: %s\n", p->disease);
    printf("Medical Report: %s\n", p->medicalReport);
    printf("Prescription:\n");
    for (int i = 0; i < p->medCount; i++) {
        printf(" - %s | %s | %s | %s\n",
               p->medicines[i].name, p->medicines[i].dosage,
               p->medicines[i].time, p->medicines[i].duration);
    }
    printf("Assigned Nurses: %s, %s\n", p->nurse1, p->nurse2);
    printf("Department: %s\n", p->department);
    printf("Bed Number: %s\n", p->bed);
}

void writeFullRecordToFile(Patient *p, FILE *f) {
    fprintf(f, "ID: %s\n", p->id);
    fprintf(f, "Name: %s\n", p->name);
    fprintf(f, "DOB: %s\n", p->dob);
    fprintf(f, "Gender: %s\n", p->gender);
    fprintf(f, "Contact: %s\n", p->contact);
    fprintf(f, "Doctor Name: %s\n", p->doctorName);
    fprintf(f, "Symptoms: %s\n", p->symptoms);
    fprintf(f, "Medical Tests: %s\n", p->medicalTests);
    fprintf(f, "Disease: %s\n", p->disease);
    fprintf(f, "Medical Report: %s\n", p->medicalReport);
    fprintf(f, "Prescription:\n");
    for (int i = 0; i < p->medCount; i++) {
        fprintf(f, " - %s | %s | %s | %s\n",
                p->medicines[i].name, p->medicines[i].dosage,
                p->medicines[i].time, p->medicines[i].duration);
    }
    fprintf(f, "Assigned Nurses: %s, %s\n", p->nurse1, p->nurse2);
    fprintf(f, "Department: %s\n", p->department);
    fprintf(f, "Bed Number: %s\n", p->bed);
}

/* ---------------------------------------------------------
   DOCTOR MODULE
   --------------------------------------------------------- */
void registerNewPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("\nPatient limit reached. Cannot register more patients.\n");
        return;
    }

    Patient *p = &patients[patientCount];
    memset(p, 0, sizeof(Patient));

    printf("\n--- REGISTER NEW PATIENT ---\n");
    printf("Patient Name: ");
    readLine(p->name, sizeof(p->name));
    printf("Birth Date (DD-MM-YYYY): ");
    readLine(p->dob, sizeof(p->dob));
    printf("Gender: ");
    readLine(p->gender, sizeof(p->gender));
    printf("Contact Number: ");
    readLine(p->contact, sizeof(p->contact));
    printf("Department: ");
    readLine(p->department, sizeof(p->department));
    printf("Symptoms: ");
    readLine(p->symptoms, sizeof(p->symptoms));
    printf("Medical Tests: ");
    readLine(p->medicalTests, sizeof(p->medicalTests));
    printf("Disease Diagnosis: ");
    readLine(p->disease, sizeof(p->disease));
    printf("Medical Report: ");
    readLine(p->medicalReport, sizeof(p->medicalReport));

    printf("How many medicines to prescribe? ");
    int n = readInt();
    if (n < 0) n = 0;
    if (n > MAX_MEDS) n = MAX_MEDS;
    p->medCount = n;
    for (int i = 0; i < n; i++) {
        printf("\nMedicine %d Name: ", i + 1);
        readLine(p->medicines[i].name, sizeof(p->medicines[i].name));
        printf("Dosage: ");
        readLine(p->medicines[i].dosage, sizeof(p->medicines[i].dosage));
        printf("Time: ");
        readLine(p->medicines[i].time, sizeof(p->medicines[i].time));
        printf("Duration: ");
        readLine(p->medicines[i].duration, sizeof(p->medicines[i].duration));
    }

    /* Auto-generated fields */
    sprintf(p->id, "P%d", nextIdNumber++);

    /* Simple bed numbering based on department first letter */
    char deptLetter = toupper((unsigned char)p->department[0]);
    static int bedCounter = 101; /* shared counter is fine for a student-level system */
    sprintf(p->bed, "%c-%d", deptLetter, bedCounter++);

    strcpy(p->nurse1, "Nurse A Day");
    strcpy(p->nurse2, "Nurse B Evening");
    strcpy(p->doctorName, "Dr. Mohammad");

    patientCount++;

    printf("\nPatient registered! System automatic add ID: %s, Bed: %s, Nurse by shift\n",
           p->id, p->bed);
}

void viewMedicalInfoDoctor(Patient *p) {
    printFullPatientRecord(p);

    char safeDoc[30], safeName[60], filename[130];
    sanitizeForFilename(p->doctorName, safeDoc);
    sanitizeForFilename(p->name, safeName);
    sprintf(filename, "%s_%s_PatientReport.txt", safeDoc, safeName);

    FILE *f = fopen(filename, "w");
    if (f) {
        writeFullRecordToFile(p, f);
        fclose(f);
        printf("\n[Report saved as: %s]\n", filename);
    } else {
        printf("\n[Could not save report file.]\n");
    }
}

void editPatientInfo(Patient *p) {
    char buf[600];
    printf("\n--- EDIT PATIENT INFORMATION ---\n");

    printf("Name [%s]: ", p->name);
    readLine(buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(p->name, buf);

    printf("Gender [%s]: ", p->gender);
    readLine(buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(p->gender, buf);

    printf("Contact Number [%s]: ", p->contact);
    readLine(buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(p->contact, buf);

    printf("Department [%s]: ", p->department);
    readLine(buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(p->department, buf);

    printf("Symptoms [%s]: ", p->symptoms);
    readLine(buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(p->symptoms, buf);

    printf("Medical Tests [%s]: ", p->medicalTests);
    readLine(buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(p->medicalTests, buf);

    printf("\nPatient information updated successfully.\n");
}

void updateMedicalReport(Patient *p) {
    printf("\n--- UPDATE MEDICAL REPORT ---\n");
    printf("Current Disease Diagnosis: %s\n", p->disease);
    printf("New Disease Diagnosis (leave blank to keep): ");
    char buf[600];
    readLine(buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(p->disease, buf);

    printf("\nCurrent Medical Report:\n%s\n", p->medicalReport);
    printf("New Medical Report (leave blank to keep): ");
    readLine(buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(p->medicalReport, buf);

    printf("\nMedical report updated successfully.\n");
}

void updatePrescription(Patient *p) {
    printf("\n--- UPDATE PRESCRIPTION ---\n");
    printf("1. Add new medicine\n");
    printf("2. Remove a medicine\n");
    printf("3. Back\n");
    printf("Select option: ");
    int choice = readInt();

    if (choice == 1) {
        if (p->medCount >= MAX_MEDS) {
            printf("\nMedicine list is full.\n");
            return;
        }
        Medicine *m = &p->medicines[p->medCount];
        printf("Medicine Name: ");
        readLine(m->name, sizeof(m->name));
        printf("Dosage: ");
        readLine(m->dosage, sizeof(m->dosage));
        printf("Time: ");
        readLine(m->time, sizeof(m->time));
        printf("Duration: ");
        readLine(m->duration, sizeof(m->duration));
        p->medCount++;
        printf("\nMedicine added.\n");
    } else if (choice == 2) {
        printf("\nCurrent medicines:\n");
        for (int i = 0; i < p->medCount; i++)
            printf(" %d. %s\n", i + 1, p->medicines[i].name);
        printf("Enter number to remove: ");
        int idx = readInt() - 1;
        if (idx >= 0 && idx < p->medCount) {
            for (int i = idx; i < p->medCount - 1; i++)
                p->medicines[i] = p->medicines[i + 1];
            p->medCount--;
            printf("\nMedicine removed.\n");
        } else {
            printf("\nInvalid selection.\n");
        }
    }
}

void patientActionSubmenu(Patient *p) {
    int running = 1;
    while (running) {
        printf("\n0. View Medical Information\n");
        printf("1. Edit Patient Information\n");
        printf("2. Update Medical Report\n");
        printf("3. Update Prescription\n");
        printf("4. Back to Doctor Menu\n");
        printf("Select option: ");
        int choice = readInt();

        switch (choice) {
            case 0: viewMedicalInfoDoctor(p); break;
            case 1: editPatientInfo(p); break;
            case 2: updateMedicalReport(p); break;
            case 3: updatePrescription(p); break;
            case 4: running = 0; break;
            default: printf("\nInvalid option.\n");
        }
    }
}

void viewAllPatients() {
    printf("\n--- ALL PATIENTS ---\n");
    for (int i = 0; i < patientCount; i++) {
        printf("ID: %s | Name: %s | Disease: %s | Bed: %s\n",
               patients[i].id, patients[i].name, patients[i].disease, patients[i].bed);
    }

    printf("\nEnter Patient ID to manage and view information (or '0' to cancel): ");
    char key[30];
    readLine(key, sizeof(key));
    if (strcmp(key, "0") == 0) return;

    int idx = findPatientIndexByIdOrName(key);
    if (idx == -1) {
        printf("\nPatient not found.\n");
        return;
    }
    patientActionSubmenu(&patients[idx]);
}

void searchPatientDoctor() {
    printf("\nEnter Patient Name or Patient ID (or '0' to cancel): ");
    char key[60];
    readLine(key, sizeof(key));
    if (strcmp(key, "0") == 0) return;

    int idx = findPatientIndexByIdOrName(key);
    if (idx == -1) {
        printf("\nPatient not found.\n");
        return;
    }

    printf("\nPatient found: %s (%s)\n", patients[idx].name, patients[idx].id);
    patientActionSubmenu(&patients[idx]);
}

void doctorMenu() {
    int running = 1;
    while (running) {
        printf("\n");
        printCentered("==============================");
        printCentered("DOCTOR PORTAL");
        printCentered("==============================");
        printf("1. New Patient\n");
        printf("2. Search Patient by Name or ID\n");
        printf("3. View All Patients\n");
        printf("4. Logout\n");
        printf("Select option: ");
        int choice = readInt();

        switch (choice) {
            case 1: registerNewPatient(); break;
            case 2: searchPatientDoctor(); break;
            case 3: viewAllPatients(); break;
            case 4: running = 0; break;
            default: printf("\nInvalid option.\n");
        }
    }
}

void doctorLogin() {
    printf("\n");
    printCentered("--- DOCTOR LOGIN ---");
    printf("Username: ");
    char name[30], pass[30];
    readLine(name, sizeof(name));
    printf("Password: ");
    readLine(pass, sizeof(pass));

    if (!sameTextCI(name, "Dr. Mohammad")) {
        printf("\nWrong username.\n");
    } else if (strcmp(pass, "mohammad123") != 0) {
        printf("\nWrong password.\n");
    } else {
        doctorMenu();
    }
}

/* ---------------------------------------------------------
   PATIENT MODULE
   --------------------------------------------------------- */
void patientMenu(Patient *p) {
    int running = 1;
    while (running) {
        printf("\n");
        printCentered("==============================");
        printCentered("PATIENT PORTAL");
        printCentered("==============================");
        printf("1. View Medical Information\n");
        printf("2. Logout\n");
        printf("Select option: ");
        int choice = readInt();

        if (choice == 1) {
            printFullPatientRecord(p);

            char safeName[60], filename[100];
            sanitizeForFilename(p->name, safeName);
            sprintf(filename, "%s_PatientReport.txt", safeName);

            FILE *f = fopen(filename, "w");
            if (f) {
                writeFullRecordToFile(p, f);
                fclose(f);
                printf("\n[Report saved as: %s]\n", filename);
            } else {
                printf("\n[Could not save report file.]\n");
            }
        } else if (choice == 2) {
            running = 0;
        } else {
            printf("\nInvalid option.\n");
        }
    }
}

void patientLogin() {
    printf("\n");
    printCentered("--- PATIENT LOGIN ---");
    printf("By, Patient Name as Username and Birth Date as Password (DD-MM-YYYY)\n");
    printf("Username: ");
    char name[60], dob[15];
    readLine(name, sizeof(name));
    printf("Password (DD-MM-YYYY): ");
    readLine(dob, sizeof(dob));

    int nameIdx = findPatientIndexByName(name);
    if (nameIdx == -1) {
        printf("\nWrong username.\n");
        return;
    }

    int idx = findPatientIndexByNameDob(name, dob);
    if (idx == -1) {
        printf("\nWrong password.\n");
        return;
    }
    patientMenu(&patients[idx]);
}

/* ---------------------------------------------------------
   NURSE MODULE
   --------------------------------------------------------- */
void nurseMenu(const char *nurseFullLabel, const char *nurseShortLabel) {
    int running = 1;
    while (running) {
        printf("\n");
        printCentered("==============================");
        printCentered("NURSE PORTAL");
        printCentered("==============================");
        printf("1. View Assigned Patients\n");
        printf("2. Logout\n");
        printf("Select option: ");
        int choice = readInt();

        if (choice == 1) {
            printf("\n--- ASSIGNED PATIENTS ---\n");
            for (int i = 0; i < patientCount; i++) {
                if (strstr(patients[i].nurse1, nurseShortLabel) || strstr(patients[i].nurse2, nurseShortLabel)) {
                    printf("ID: %s | Name: %s | Dept: %s | Bed: %s\n",
                           patients[i].id, patients[i].name, patients[i].department, patients[i].bed);
                }
            }

            printf("\nEnter Patient Name or Patient ID (or '0' to cancel): ");
            char key[60];
            readLine(key, sizeof(key));
            if (strcmp(key, "0") == 0) continue;

            int idx = findPatientIndexByIdOrName(key);
            if (idx == -1) {
                printf("\nPatient not found.\n");
                continue;
            }

            Patient *p = &patients[idx];
            printf("\nPatient Name: %s\n", p->name);
            printf("Patient ID: %s\n", p->id);
            printf("Disease: %s\n", p->disease);
            printf("Medicines:\n");
            for (int i = 0; i < p->medCount; i++) {
                printf(" - %s | %s | %s\n", p->medicines[i].name, p->medicines[i].dosage, p->medicines[i].time);
            }
            printf("Assigned Bed Number: %s\n", p->bed);

            char safeName[60], filename[100];
            sanitizeForFilename(p->name, safeName);
            sprintf(filename, "%s_%s_PatientReport.txt", nurseFullLabel, safeName);

            FILE *f = fopen(filename, "w");
            if (f) {
                fprintf(f, "Patient Name: %s\n", p->name);
                fprintf(f, "Patient ID: %s\n", p->id);
                fprintf(f, "Disease: %s\n", p->disease);
                fprintf(f, "Medicines:\n");
                for (int i = 0; i < p->medCount; i++) {
                    fprintf(f, " - %s | %s | %s\n", p->medicines[i].name, p->medicines[i].dosage, p->medicines[i].time);
                }
                fprintf(f, "Assigned Bed Number: %s\n", p->bed);
                fclose(f);
                printf("\n[Report saved as: %s]\n", filename);
            } else {
                printf("\n[Could not save report file.]\n");
            }
        } else if (choice == 2) {
            running = 0;
        } else {
            printf("\nInvalid option.\n");
        }
    }
}

void nurseLogin() {
    printf("\n");
    printCentered("--- NURSE LOGIN ---");
    printf("Username: ");
    char name[30], pass[30];
    readLine(name, sizeof(name));
    printf("Password: ");
    readLine(pass, sizeof(pass));

    if (sameTextCI(name, "Nurse A")) {
        if (strcmp(pass, "nursea123") == 0) {
            nurseMenu("NursA", "Nurse A");
        } else {
            printf("\nWrong password.\n");
        }
    } else if (sameTextCI(name, "Nurse B")) {
        if (strcmp(pass, "nurseb123") == 0) {
            nurseMenu("NursB", "Nurse B");
        } else {
            printf("\nWrong password.\n");
        }
    } else {
        printf("\nWrong username.\n");
    }
}

/* ---------------------------------------------------------
   PHARMACIST MODULE
   --------------------------------------------------------- */
void pharmacistMenu() {
    int running = 1;
    while (running) {
        printf("\n");
        printCentered("==============================");
        printCentered("PHARMACIST PORTAL");
        printCentered("==============================");
        printf("1. Search Patient by Patient ID\n");
        printf("2. Logout\n");
        printf("Select option: ");
        int choice = readInt();

        if (choice == 1) {
            printf("\nEnter Patient ID: ");
            char id[10];
            readLine(id, sizeof(id));

            int idx = findPatientIndexByIdOrName(id);
            if (idx == -1) {
                printf("\nPatient not found.\n");
                continue;
            }

            Patient *p = &patients[idx];
            printf("\nPatient Name: %s\n", p->name);
            printf("Patient ID: %s\n", p->id);
            printf("Medicine List:\n");
            for (int i = 0; i < p->medCount; i++) {
                printf(" - %s | %s | %s | %s\n",
                       p->medicines[i].name, p->medicines[i].dosage,
                       p->medicines[i].duration, p->medicines[i].time);
            }

            char safeName[60], filename[100];
            sanitizeForFilename(p->name, safeName);
            sprintf(filename, "%s_MedicineReport.txt", safeName);

            FILE *f = fopen(filename, "w");
            if (f) {
                fprintf(f, "Patient Name: %s\n", p->name);
                fprintf(f, "Patient ID: %s\n", p->id);
                fprintf(f, "Medicine List:\n");
                for (int i = 0; i < p->medCount; i++) {
                    fprintf(f, " - %s | %s | %s | %s\n",
                            p->medicines[i].name, p->medicines[i].dosage,
                            p->medicines[i].duration, p->medicines[i].time);
                }
                fclose(f);
                printf("\n[Report generated: %s]\n", filename);
            } else {
                printf("\n[Could not save report file.]\n");
            }
        } else if (choice == 2) {
            running = 0;
        } else {
            printf("\nInvalid option.\n");
        }
    }
}

void pharmacistLogin() {
    printf("\n");
    printCentered("--- PHARMACIST LOGIN ---");
    printf("Username: ");
    char name[30], pass[30];
    readLine(name, sizeof(name));
    printf("Password: ");
    readLine(pass, sizeof(pass));

    if (!sameTextCI(name, "Pharmacist A")) {
        printf("\nWrong username.\n");
    } else if (strcmp(pass, "pharmacista123") != 0) {
        printf("\nWrong password.\n");
    } else {
        pharmacistMenu();
    }
}

/* ---------------------------------------------------------
   MAIN
   --------------------------------------------------------- */
int main() {
    seedPatients();

    int running = 1;
    while (running) {
        printf("\n");
        printCentered("========================================");
        printCentered("PATIENT AND MEDICAL INFORMATION SYSTEM");
        printCentered("========================================");
        printf("1. Doctor Login\n");
        printf("2. Patient Login\n");
        printf("3. Nurse Login\n");
        printf("4. Pharmacist Login\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        int choice = readInt();

        switch (choice) {
            case 1: doctorLogin(); break;
            case 2: patientLogin(); break;
            case 3: nurseLogin(); break;
            case 4: pharmacistLogin(); break;
            case 5:
                printf("\nExiting system.\n");
                running = 0;
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}
