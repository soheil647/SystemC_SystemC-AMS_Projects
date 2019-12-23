// Example program
#include <iostream>
#include <string>
#include <vector> 
#include <iostream>
#include <fstream>
using namespace std; 
vector<string> department_names;
class Department{
    public:
    string name;
    int thesis_number;
    int scale_method;
};
class Thesis{
    public:
    string title;
    string writer_name;
    Department department;
    int grade;
};
class Library{
    public:
    vector<Thesis> thesis;
    void Add(Thesis add){
        thesis.push_back(add);
    }
    vector<int> thes_grades;
    vector<string> thes_name;
    void Display(){
    for (auto it = thesis.begin(); it != thesis.end(); it++){ 
        for (long long unsigned int j = 0 ; j < department_names.size(); j++) {
            if(it->department.name == department_names[j]){
                thes_grades.push_back(it->grade);
                thes_name.push_back(it->title);
            }
        }
        } 
        
        for(long long unsigned int i = 0 ; i < thes_grades.size();i++){
            for(long long unsigned int j = 0 ; j < thes_grades.size(); j++){
                if(thes_grades[i] > thes_grades[j]){
                    swap(thes_grades[i],thes_grades[j]);
                    swap(thes_name[i],thes_name[j]);
            }
        }
        }
		ofstream myfile;
		myfile.open ("data.txt");
        for(long long unsigned int i = 0 ; i < thes_grades.size();i++){
            cout << "name : " << thes_name[i] << " grade : " << thes_grades[i] << "\n";
			myfile << "name : " << thes_name[i] << " grade : " << thes_grades[i] << "\n";
        }
    }
    
    void Remove(Thesis r){
        Thesis trash = Thesis();
        thesis.push_back(trash);
        for (auto it = thesis.begin(); it != thesis.end(); it++) {
            if (it->title == r.title && it->writer_name == r.writer_name){
                thesis.erase(it);
                continue;
            }
        }
        thesis.pop_back();
                
    }
};
class student{
    public:
    string name;
    Department department;
    Thesis thesis;
};
int main()
{
    
    Thesis a = Thesis();
    Thesis b = Thesis();
    Thesis c = Thesis();
    c.title = "ar";
    a.title = "asdas";
    b.title = "vv";
    Department dp = Department();
    dp.name = "sdas";
    a.grade = 10;
    b.grade = 15;
    b.grade = 12;
    c.department = dp;
    b.department = dp;
    a.department = dp;
    department_names.push_back("sdas");
    Library lb = Library();
    lb.Add(a);
    lb.Add(b);
    lb.Add(c);
    lb.Display();
	system("pause");
}