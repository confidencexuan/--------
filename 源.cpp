#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// 学生类
class Student {
private:
    string id;      // 学号
    string name;    // 姓名
    int age;        // 年龄
    string gender;  // 性别
    double score;   // 成绩

public:
    // 构造函数
    Student(string id, string name, int age, string gender, double score)
        : id(id), name(name), age(age), gender(gender), score(score) {}

    // 获取学号
    string getId() const { return id; }

    // 获取姓名
    string getName() const { return name; }

    // 获取年龄
    int getAge() const { return age; }

    // 获取性别
    string getGender() const { return gender; }

    // 获取成绩
    double getScore() const { return score; }

    // 显示学生信息
    void display() const {
        cout << left << setw(12) << id
            << setw(12) << name
            << setw(6) << age
            << setw(8) << gender
            << setw(8) << fixed << setprecision(2) << score << endl;
    }
};

// 学生管理系统类
class StudentManagementSystem {
private:
    vector<Student> students;

public:
    // 添加学生
    void addStudent() {
        string id, name, gender;
        int age;
        double score;

        cout << "请输入学号: ";
        cin >> id;

        // 检查学号是否已存在
        for (const auto& student : students) {
            if (student.getId() == id) {
                cout << "该学号已存在!" << endl;
                return;
            }
        }

        cout << "请输入姓名: ";
        cin >> name;
        cout << "请输入年龄: ";
        cin >> age;
        cout << "请输入性别: ";
        cin >> gender;
        cout << "请输入成绩: ";
        cin >> score;

        students.emplace_back(id, name, age, gender, score);
        cout << "添加成功!" << endl;
    }

    // 删除学生
    void deleteStudent() {
        string id;
        cout << "请输入要删除的学生学号: ";
        cin >> id;

        auto it = find_if(students.begin(), students.end(),
            [&id](const Student& s) { return s.getId() == id; });

        if (it != students.end()) {
            students.erase(it);
            cout << "删除成功!" << endl;
        }
        else {
            cout << "未找到该学号的学生!" << endl;
        }
    }

    // 修改学生信息
    void modifyStudent() {
        string id;
        cout << "请输入要修改的学生学号: ";
        cin >> id;

        auto it = find_if(students.begin(), students.end(),
            [&id](const Student& s) { return s.getId() == id; });

        if (it != students.end()) {
            string name, gender;
            int age;
            double score;

            cout << "请输入新姓名: ";
            cin >> name;
            cout << "请输入新年龄: ";
            cin >> age;
            cout << "请输入新性别: ";
            cin >> gender;
            cout << "请输入新成绩: ";
            cin >> score;

            *it = Student(id, name, age, gender, score);
            cout << "修改成功!" << endl;
        }
        else {
            cout << "未找到该学号的学生!" << endl;
        }
    }

    // 查询学生
    void queryStudent() {
        string id;
        cout << "请输入要查询的学生学号: ";
        cin >> id;

        auto it = find_if(students.begin(), students.end(),
            [&id](const Student& s) { return s.getId() == id; });

        if (it != students.end()) {
            displayHeader();
            it->display();
        }
        else {
            cout << "未找到该学号的学生!" << endl;
        }
    }

    // 显示所有学生
    void displayAllStudents() {
        if (students.empty()) {
            cout << "当前没有学生记录!" << endl;
            return;
        }

        displayHeader();
        for (const auto& student : students) {
            student.display();
        }
    }

    // 显示表头
    void displayHeader() const {
        cout << left << setw(12) << "学号"
            << setw(12) << "姓名"
            << setw(6) << "年龄"
            << setw(8) << "性别"
            << setw(8) << "成绩" << endl;
        cout << string(46, '-') << endl;
    }

    // 按成绩排序
    void sortByScore() {
        sort(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.getScore() > b.getScore();
            });
        cout << "按成绩排序完成!" << endl;
    }

    // 统计信息
    void showStatistics() {
        if (students.empty()) {
            cout << "当前没有学生记录!" << endl;
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

        cout << "学生总数: " << students.size() << endl;
        cout << "平均成绩: " << fixed << setprecision(2) << average << endl;
        cout << "最高成绩: " << fixed << setprecision(2) << maxScore << endl;
        cout << "最低成绩: " << fixed << setprecision(2) << minScore << endl;
    }
};

// 显示菜单
void displayMenu() {
    cout << "\n========== 学生管理系统 ==========" << endl;
    cout << "1. 添加学生" << endl;
    cout << "2. 删除学生" << endl;
    cout << "3. 修改学生信息" << endl;
    cout << "4. 查询学生" << endl;
    cout << "5. 显示所有学生" << endl;
    cout << "6. 按成绩排序" << endl;
    cout << "7. 统计信息" << endl;
    cout << "0. 退出系统" << endl;
    cout << "=================================" << endl;
    cout << "请选择操作: ";
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
            cout << "感谢使用学生管理系统，再见!" << endl;
            break;
        default:
            cout << "无效的选择，请重新输入!" << endl;
        }
    } while (choice != 0);

    return 0;
}