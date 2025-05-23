#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// ѧ����
class Student {
private:
    string id;      // ѧ��
    string name;    // ����
    int age;        // ����
    string gender;  // �Ա�
    double score;   // �ɼ�

public:
    // ���캯��
    Student(string id, string name, int age, string gender, double score)
        : id(id), name(name), age(age), gender(gender), score(score) {}

    // ��ȡѧ��
    string getId() const { return id; }

    // ��ȡ����
    string getName() const { return name; }

    // ��ȡ����
    int getAge() const { return age; }

    // ��ȡ�Ա�
    string getGender() const { return gender; }

    // ��ȡ�ɼ�
    double getScore() const { return score; }

    // ��ʾѧ����Ϣ
    void display() const {
        cout << left << setw(12) << id
            << setw(12) << name
            << setw(6) << age
            << setw(8) << gender
            << setw(8) << fixed << setprecision(2) << score << endl;
    }
};

// ѧ������ϵͳ��
class StudentManagementSystem {
private:
    vector<Student> students;

public:
    // ���ѧ��
    void addStudent() {
        string id, name, gender;
        int age;
        double score;

        cout << "������ѧ��: ";
        cin >> id;

        // ���ѧ���Ƿ��Ѵ���
        for (const auto& student : students) {
            if (student.getId() == id) {
                cout << "��ѧ���Ѵ���!" << endl;
                return;
            }
        }

        cout << "����������: ";
        cin >> name;
        cout << "����������: ";
        cin >> age;
        cout << "�������Ա�: ";
        cin >> gender;
        cout << "������ɼ�: ";
        cin >> score;

        students.emplace_back(id, name, age, gender, score);
        cout << "��ӳɹ�!" << endl;
    }

    // ɾ��ѧ��
    void deleteStudent() {
        string id;
        cout << "������Ҫɾ����ѧ��ѧ��: ";
        cin >> id;

        auto it = find_if(students.begin(), students.end(),
            [&id](const Student& s) { return s.getId() == id; });

        if (it != students.end()) {
            students.erase(it);
            cout << "ɾ���ɹ�!" << endl;
        }
        else {
            cout << "δ�ҵ���ѧ�ŵ�ѧ��!" << endl;
        }
    }

    // �޸�ѧ����Ϣ
    void modifyStudent() {
        string id;
        cout << "������Ҫ�޸ĵ�ѧ��ѧ��: ";
        cin >> id;

        auto it = find_if(students.begin(), students.end(),
            [&id](const Student& s) { return s.getId() == id; });

        if (it != students.end()) {
            string name, gender;
            int age;
            double score;

            cout << "������������: ";
            cin >> name;
            cout << "������������: ";
            cin >> age;
            cout << "���������Ա�: ";
            cin >> gender;
            cout << "�������³ɼ�: ";
            cin >> score;

            *it = Student(id, name, age, gender, score);
            cout << "�޸ĳɹ�!" << endl;
        }
        else {
            cout << "δ�ҵ���ѧ�ŵ�ѧ��!" << endl;
        }
    }

    // ��ѯѧ��
    void queryStudent() {
        string id;
        cout << "������Ҫ��ѯ��ѧ��ѧ��: ";
        cin >> id;

        auto it = find_if(students.begin(), students.end(),
            [&id](const Student& s) { return s.getId() == id; });

        if (it != students.end()) {
            displayHeader();
            it->display();
        }
        else {
            cout << "δ�ҵ���ѧ�ŵ�ѧ��!" << endl;
        }
    }

    // ��ʾ����ѧ��
    void displayAllStudents() {
        if (students.empty()) {
            cout << "��ǰû��ѧ����¼!" << endl;
            return;
        }

        displayHeader();
        for (const auto& student : students) {
            student.display();
        }
    }

    // ��ʾ��ͷ
    void displayHeader() const {
        cout << left << setw(12) << "ѧ��"
            << setw(12) << "����"
            << setw(6) << "����"
            << setw(8) << "�Ա�"
            << setw(8) << "�ɼ�" << endl;
        cout << string(46, '-') << endl;
    }

    // ���ɼ�����
    void sortByScore() {
        sort(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.getScore() > b.getScore();
            });
        cout << "���ɼ��������!" << endl;
    }

    // ͳ����Ϣ
    void showStatistics() {
        if (students.empty()) {
            cout << "��ǰû��ѧ����¼!" << endl;
            return;
        }

        double total = 0;
        double maxScore = students[0].getScore();
        double minScore = students[0].getScore();

        for (const auto& student : students) {
            double score = student.getScore();
            total += score;
            if (score > maxScore) maxScore = score;
            if (score < minScore) minScore = score;
        }

        double average = total / students.size();

        cout << "ѧ������: " << students.size() << endl;
        cout << "ƽ���ɼ�: " << fixed << setprecision(2) << average << endl;
        cout << "��߳ɼ�: " << fixed << setprecision(2) << maxScore << endl;
        cout << "��ͳɼ�: " << fixed << setprecision(2) << minScore << endl;
    }
};

// ��ʾ�˵�
void displayMenu() {
    cout << "\n========== ѧ������ϵͳ ==========" << endl;
    cout << "1. ���ѧ��" << endl;
    cout << "2. ɾ��ѧ��" << endl;
    cout << "3. �޸�ѧ����Ϣ" << endl;
    cout << "4. ��ѯѧ��" << endl;
    cout << "5. ��ʾ����ѧ��" << endl;
    cout << "6. ���ɼ�����" << endl;
    cout << "7. ͳ����Ϣ" << endl;
    cout << "0. �˳�ϵͳ" << endl;
    cout << "=================================" << endl;
    cout << "��ѡ�����: ";
}

int main() {
    StudentManagementSystem sms;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            sms.addStudent();
            break;
        case 2:
            sms.deleteStudent();
            break;
        case 3:
            sms.modifyStudent();
            break;
        case 4:
            sms.queryStudent();
            break;
        case 5:
            sms.displayAllStudents();
            break;
        case 6:
            sms.sortByScore();
            break;
        case 7:
            sms.showStatistics();
            break;
        case 0:
            cout << "��лʹ��ѧ������ϵͳ���ټ�!" << endl;
            break;
        default:
            cout << "��Ч��ѡ������������!" << endl;
        }
    } while (choice != 0);

    return 0;
}