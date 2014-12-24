#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;


//Base Student
class Student
{
//these classes will remain the same within each child of student
protected:
    char Name[21];
    char SSN[10];
    float gpa;
    int credits;

public:
    //virtual functions that will need to be manipulated within each child of student
    virtual float tuition() const=0;
    Student(const string &name, const string &ssn, int&credits, float &gpa)
    {
        //creating the char array
        size_t length = name.copy(Name, 21,0);
        Name[length] = '\0';

        size_t length2 = ssn.copy(SSN,10,0);
        SSN[length2] = '\0';

        this->credits = credits;
        this->gpa= gpa;
    }

    char* getName()
    {
        return Name;
    }

    char* getSSN()
    {
        return SSN;
    }


    int getCredit()
    {
        return credits;
    }

    float getGpa()
    {
        return gpa;
    }

    //the print function for a basic student
    virtual void print()const
    {
        cout<<"Name:\t\t\t"<<Name<<endl;
        cout<<"Social Security #:\t"<<SSN<<endl;
        cout<<"Credits:\t\t"<<credits<<endl;
        cout<<"Grade Point Average:\t"<<gpa<<endl;
    }

};

//undergraduate inheriting from student
class jsjohn23_Undergrad : public Student
{

private:
//this are specific to an undergraduate student.
    float undergraduate_rate,undergrad_rate;
    char *year;

public:
    //undergrad constructor
    jsjohn23_Undergrad(const string &name, const string &ssn, string Year,
                       int credits,float gpa):Student(name, ssn, credits, gpa)
    {
        //storing string as char*
        year = new char[Year.size() + 1];
        year[Year.size()] ='\0';
        copy(Year.begin(), Year.end(), year);
    }

    void setRate(float undergrad_rate)
    {
        this->undergraduate_rate = undergrad_rate;
    }

    float getRate() const
    {
        return undergraduate_rate;
    }

    char* getYear()
    {
        return year;
    }

    float tuition()const
    {
        return undergraduate_rate * credits;
    }

    //print function including manipulations needed to include undergraduate parameters
    void  print()
    {
        //this prints the 4 student parameters
        Student::print();
        cout<<"Year:\t\t\t"<<year<<endl;
        cout<<"Tuition:\t\t"<<tuition()<<endl<<endl<<endl;
    }

};


//graduate class inheriting from student
class Grad:public Student
{
private:
//these are specific to a graduate student
    float graduate_rate;
    char* thesis;
    char* status;

public:
    //constructor for graduate class
    Grad(string name, string ssn, string Status, int credits, float gpa, string Thesis):
        Student(name, ssn, credits, gpa)
    {
        status = new char[Status.size() + 1];
        status[Status.size()] ='\0';
        copy(Status.begin(), Status.end(), status);


        thesis = new char[Thesis.size() + 1];
        thesis[Thesis.size()] ='\0';
        copy(Thesis.begin(), Thesis.end(), thesis);
    }

    float tuition()const
    {
        return graduate_rate * credits;
    }

    char* getThesis()
    {
        return thesis;
    }

    void setThesis(string Thesis)
    {
        thesis = &Thesis[0];
    }

    void setRate(float grad_rate)
    {
        this->graduate_rate = grad_rate;
    }

    //print function including student attributes and graduate student attributes
    void print()const
    {

        Student::print();
        cout<<"Status:\t\t\t"<<status<<endl;
        cout<<"Tuition:\t\t"<<tuition()<<endl;
        cout<<"Thesis:\t\t\t"<<thesis<<endl;
    }

};

//graduate assistant that inherits from a graduate
class GradAsst:public Grad
{
private:
//these are specific to the graduate assistant
    float hourPay;
    char* task;
    char* supervisor;

public:
//Graduate assistant Constructor
    GradAsst(string name,string ssn,string Status,int credits, float gpa,
             string thesis,string Task,float hourPay, string Supervisor):Grad(name,ssn,Status,credits,gpa,thesis)
    {
        //converting string to type char*
        task = new char[Task.size() + 1];
        task[Task.size()] ='\0';
        copy(Task.begin(), Task.end(), task);


        supervisor = new char[Supervisor.size() + 1];
        supervisor[Supervisor.size()] ='\0';
        copy(Supervisor.begin(), Supervisor.end(), supervisor);

        this->hourPay = hourPay;
    }

    //print function to print parameters from graduate student as well as what is needed for an graduate assistant
    void print()const
    {
        cout<<endl<<endl;
        Grad::print();
        cout<<setw(7)<<"Task:\t\t\t"<<task<<endl;
        cout<<setw(10)<<"Hourly Pay:\t\t$"<<hourPay<<endl;
        cout<<setw(10)<<"Supervisor:\t\t"<<supervisor<<endl<<endl<<endl;
    }

    char* getSupervisor()
    {
        return supervisor;
    }

    float getHourPay()
    {
        return hourPay;
    }

    void setSupervisor(string s)
    {
        supervisor = &s[0];
    }

    void setHourPay(float pay)
    {
        hourPay = pay;
    }

    char* getTask()
    {
        return task;
    }

    void setTask(char* Task)
    {
        task = &Task[0];
    }
};


//sort undergrads by GPA in the list
bool sortByGpa(jsjohn23_Undergrad student1, jsjohn23_Undergrad student2)
{
    return student1.getGpa() > student2.getGpa();
}



int main()

{
//this will stop dialog box from closing early
    char ch;
//Dynamic calling
    Student *ptr;
    float const undergrad_rate = 380.0;
    float const grad_rate = 500.0;

    //create your different types of students
    jsjohn23_Undergrad undergrad("Mary","000111222","Junior",12,4.0 );

    Grad grad("David","111222333","Graduate",9,3.7,
              "How to learn data structures using C++/STL?");

    GradAsst gradAssist("Jason","222333444","Graduate Assistant",9,3.9,
                        "Design of efficient algorithms",
                        "Grading 330 projects and implementing a data mining algorithm",20,
                        "Lixen Fu");
    undergrad.setRate(undergrad_rate);
    grad.setRate(grad_rate);
    gradAssist.setRate(grad_rate);


//static call
    cout<<"Part One: Static and Dynamic calling to print and tuition"<<endl<<endl;
    cout<<"Calling print through static"<<endl<<endl;
    undergrad.print();
    grad.print();
    gradAssist.print();


    cout<<endl<<endl<<"Dynamic Call to print"<<endl<<endl;
    ptr = &undergrad;
//dynamic call
    ptr->print();
    cout<<endl<<endl;
    ptr = &grad;
    ptr->print();
    cout<<endl<<endl;
    ptr = &gradAssist;
    ptr->print();

//static call to tuition
    cout<<endl<<endl<<"Static Call of tuition"<<endl<<endl;
    cout<<undergrad.getName()<<" pays $"<<undergrad.tuition()<<endl;
    cout<<grad.getName()<<" pays $"<<grad.tuition()<<endl;
    cout<<gradAssist.getName()<<" pays $"<<gradAssist.tuition()<<endl;

//dynamic call to tuition
    cout<<endl<<endl<<"Dynamic Call of tuition"<<endl<<endl;
    ptr = &undergrad;
    cout<<undergrad.getName()<<" pays $"<<ptr->tuition()<<endl;
    ptr = &grad;
    cout<<grad.getName()<<" pays $"<<ptr->tuition()<<endl;
    ptr = &gradAssist;
    cout<<gradAssist.getName()<<" pays $"<<ptr->tuition()<<endl;


//creating file reader
    ifstream fin;
    fin.open("students.txt", ios::in);
    if(!fin)
    {
//in case the file cannot be located
        cout<<endl<<endl;
        cerr<<"Unable to locate student roster. Press enter to terminate program."<<endl;
        cin.get(ch);
        return 0;
    }
    string name;
    string ssn;
    string year;
    int credits;
    float gpa;
//creating list
    list<jsjohn23_Undergrad> undergraduate;

//while file not empty push onto list
    while(fin >> name >> ssn >> year >> credits >> gpa)
    {
        jsjohn23_Undergrad student(name,ssn,year,credits,gpa);
        undergraduate.push_back(student);
    }

//create an iterator to move through the list
    list<jsjohn23_Undergrad>::const_iterator i;
    cout<<endl<<endl<<"Part Two"<<endl<<endl;
    cout<<endl<<endl<<setw(50)<<"Undergraduate Roster"<<endl<<endl;

//formatting the output
    cout<<setiosflags(ios::left)
        << setw(20) << "Name"
        << setw(10) << "SSN"
        << setw(10) << "Year"
        << setw(10) << "Credits"
        << resetiosflags(ios::left)
        << setiosflags(ios::right)
        << setw(10) << "Tuition" << setw(10) << "GPA" << endl << endl;

//output Student information from list also formatted based on above parameters for formatting
    for( i = undergraduate.begin(); i != undergraduate.end(); i++)
    {
        jsjohn23_Undergrad student = *i;
        student.setRate(undergrad_rate);
        cout<<resetiosflags(ios::right)<<setiosflags(ios::left)<<setw(20)
            <<student.getName()<<setw(10)<<student.getSSN()<<setw(10)<<student.getYear()<<setw(10)
            <<student.getCredit()<<resetiosflags(ios::left)<<setiosflags(ios::right)
            <<setiosflags(ios::fixed)<<setprecision(2)<<setw(10)
            <<student.tuition()<<setw(10)<<student.getGpa()<<endl;

    }

//find last student
    i = undergraduate.end();
    i--;
//push last student to front of list
    undergraduate.push_front(*i);
    undergraduate.pop_back();
    cout<<endl<<endl<<setw(60)
        <<"Last student pushed to front of list"<<endl<<endl;

    cout<<resetiosflags(ios::right)<<setiosflags(ios::left)<<setw(20)<<"Name"<<setw(10)
        <<"SSN"<<setw(10)<<"Year"<<setw(10)<<"Credits"<<resetiosflags(ios::left)
        <<setiosflags(ios::right)<<setw(10)<<"Tuition"<<setw(10)<<"GPA"<<endl<<endl;

//output updated roster
    for( i = undergraduate.begin(); i != undergraduate.end(); i++)
    {
        jsjohn23_Undergrad student = *i;
        student.setRate(undergrad_rate);
        cout<<resetiosflags(ios::right)<<setiosflags(ios::left)<<setw(20)
            <<student.getName()<<setw(10)<<student.getSSN()<<setw(10)<<student.getYear()<<setw(10)
            <<student.getCredit()<<resetiosflags(ios::left)<<setiosflags(ios::right)
            <<setw(10)<<student.tuition()<<setw(10)<<student.getGpa()<<endl;
    }

    //create a vector and new iterator
    cout<<endl<<endl<<endl;

    vector<jsjohn23_Undergrad> vec;

    vector<jsjohn23_Undergrad>:: iterator i2;

    for( i = undergraduate.begin(); i != undergraduate.end(); i++)
    {
        vec.push_back(*i);
    }

    sort(vec.begin(),vec.end(),sortByGpa);
    cout<<setw(50)
        <<"Roster by GPA"<<endl<<endl;
    cout<<resetiosflags(ios::right)<<setiosflags(ios::left)<<setw(20)<<"Name"<<setw(10)
        <<"SSN"<<setw(10)<<"Year"<<setw(10)<<"Credits"<<resetiosflags(ios::left)
        <<setiosflags(ios::right)<<setw(10)<<"Tuition"<<setw(10)<<"GPA"<<endl<<endl;

    for(i2 = vec.begin(); i2 != vec.end(); i2++)
    {
        jsjohn23_Undergrad student = *i2;
        student.setRate(undergrad_rate);
        cout<<resetiosflags(ios::right)<<setiosflags(ios::left)<<setw(20)
            <<student.getName()<<setw(10)<<student.getSSN()<<setw(10)<<student.getYear()<<setw(10)
            <<student.getCredit()<<resetiosflags(ios::left)<<setiosflags(ios::right)
            <<setw(10)<<student.tuition()<<setw(10)<<student.getGpa()<<endl;
    }


    cout<<endl<<endl;
    return 0;
}

