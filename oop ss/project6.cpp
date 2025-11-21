#include <iostream>
#include <fstream>
using namespace std;

class Sem_results {
public:
    string name;
    int id;
    float marks[8];
    float credits[8];
    int total_course;
    double semesterFee;
    int waiverPercentage;
    float sgpa;
    float cgpa;
    float totalCredit;

    Sem_results() {
        total_course = 0;
        waiverPercentage = 0;
        sgpa = 0.0;
        cgpa = 0.0;
        totalCredit = 0.0;
        semesterFee = 0.0;
    }

    float GradePoint(float m) {
        if (m >= 80) return 4.0;
        else if (m >= 75) return 3.75;
        else if (m >= 70) return 3.5;
        else if (m >= 65) return 3.25;
        else if (m >= 60) return 3.0;
        else if (m >= 55) return 2.75;
        else if (m >= 50) return 2.5;
        else if (m >= 45) return 2.25;
        else if (m >= 40) return 2.0;
        else return 0.0;
    }

    float calcSGPA() {
        float Sum = 0, creditSum = 0;
        for (int i = 0; i < total_course; i++) {
            float gpa = GradePoint(marks[i]);
            Sum += gpa * credits[i];
            creditSum += credits[i];
        }
        if (creditSum > 0) {
            sgpa = Sum / creditSum;
        }
        totalCredit = creditSum;
        return sgpa;
    }

    float calcCGPA(float prevCGPA, float prevCredits) {
        if (prevCredits + totalCredit > 0) {
            cgpa = ((prevCGPA * prevCredits) + (sgpa * totalCredit)) / (prevCredits + totalCredit);
        } else {
            cgpa = sgpa;
        }
        return cgpa;
    }
};

int main() {
    ifstream fin("input.txt");   // input file
    ofstream fout("output.txt"); // output file

    if (!fin) {
        cout << "Error opening input file!" << endl;
        return 1;
    }
    if (!fout) {
        cout << "Error creating output file!" << endl;
        return 1;
    }

    Sem_results s;
    float prevCGPA, prevCredits;

    fout << "Student Results\n";
    fout << "=====================\n\n";

    // Loop until EOF (multiple students)
    while (fin >> s.name >> s.id >> s.total_course) {
        // Read marks & credits
        for (int i = 0; i < s.total_course; i++) {
            fin >> s.marks[i] >> s.credits[i];
        }

        // Read previous CGPA and credits
        fin >> prevCGPA >> prevCredits;

        // Calculate
        s.calcSGPA();
        s.calcCGPA(prevCGPA, prevCredits);

        // Print to console
        cout << "Name: " << s.name << endl;
        cout << "ID: " << s.id << endl;
        cout << "SGPA: " << s.sgpa << endl;
        cout << "CGPA: " << s.cgpa << endl;
        cout << "----------------------" << endl;

        // Write to file
        fout << "Name: " << s.name << "\n";
        fout << "ID: " << s.id << "\n";
        fout << "SGPA: " << s.sgpa << "\n";
        fout << "CGPA: " << s.cgpa << "\n";
        fout << "---------------------\n\n";
    }

    fin.close();
    fout.close();

    return 0;
}
