#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
using namespace std;
// graphics class for text formatting and user interface
class graphics{
    public:
    // function to display text in a formatted box with specified width
    void txtSpace(int textboxWidth, list<string> lines){
        cout<<"."<<string(textboxWidth, '-')<<"."<<endl;
        for (string line : lines) {
            int padding=textboxWidth-line.length();
            if (padding<0){
                padding=0;
            }
            int leftPad=padding/2;
            int rightPad=padding-leftPad;
            cout<<"|"<<string(leftPad, ' ')<<line<<string(rightPad, ' ')<<"|"<<endl;
        }
        cout<<"`"<<string(textboxWidth, '-')<<"`"<<endl;
    }

    //same as txtSpace but top and bottom lines are separated for more flexibility
    void txtSpaceup(int textboxWidth){
            cout<<"."<<string(textboxWidth, '-')<<"."<<endl;
    }
    void txtSpacemd(int textboxWidth, list<string> lines){
        for (string line : lines) {
            int padding=textboxWidth-line.length();
            if (padding<0){
                padding=0;
            }
            int leftPad=padding/2;
            int rightPad=padding-leftPad;
            cout<<"|"<<string(leftPad, ' ')<<line<<string(rightPad, ' ')<<"|"<<endl;
        }
    }
    void txtSpacedn(int textboxWidth){
            cout<<"`"<<string(textboxWidth, '-')<<"`"<<endl;
    }

//function to convert a string to uppercase
    string upperConv(string fromConversion){
        for (auto &toBeConverted : fromConversion){
        toBeConverted = toupper(toBeConverted);
        }
        return fromConversion;
    }
//function to convert a string to lowercase
    string lowerConv(string fromConversion){
        for (auto &toBeConverted : fromConversion){
        toBeConverted = tolower(toBeConverted);
        }
        return fromConversion;
    }
//system boot message
    void systemBoot(){
        txtSpace(30, {"Welcome to the","Profile Management System,", "User"});
    }
//bool decision box for user input
    bool decisionBox(){
        bool userDecision;
        string userInput;
        txtSpace(30,{"Input Decision", "(Y) Yes / (N) No"});
        cout<<"->";
        cin>>userInput;
        userInput=upperConv(userInput);
        if(userInput=="Y"||userInput=="YES"){
            userDecision=true;
        } else if(userInput=="N"||userInput=="NO"){
            userDecision=false;
        }else{
            txtSpace(30, {"Invalid Input", "Please enter Y or N"});
            decisionBox();
        }
        return  userDecision;
    }
    string inputBox(){
        string userInput;
        txtSpaceup(30);
        cout<<"->";
        cin>>userInput;
        txtSpacedn(30);
        return userInput;
    }
};

class profile{
    graphics grp;
public:
    string profileName;
    int profileAge;
    string profilePosition;
    vector<pair<string, int>> profileTaskList;

    void menuProfile(){
     
    }
    void profileTaskhandling(){
        grp.txtSpace(30, {"Do you want to add a task?"});
        bool addTask = grp.decisionBox();
        while (addTask) {
                int taskPriority;
                string taskName;
                grp.txtSpace(40, {"Enter task priority (1-10):"});
                cout << "->";
                cin>>taskPriority;
                grp.txtSpace(30, {"Enter task name:"});
                cout << "->";
                cin >> taskName;
                profileTaskList.push_back({taskName, taskPriority});
                grp.txtSpace(30, {"Add another task?"});
                if(!grp.decisionBox()){
                    break;
                }
        }
        if (profileTaskList.empty()) {
            grp.txtSpace(30, {"No tasks added."});
        } else {
            grp.txtSpaceup(30);
            grp.txtSpacemd(30, {"Profile Tasks:"});
            grp.txtSpacemd(30,{""});
            for (const auto &task : profileTaskList){
                grp.txtSpacemd(30, {task.first + " (Priority: " + to_string(task.second) + ")"});
            }
            grp.txtSpacedn(30);
        }
    }
};


int main() {
    graphics grp;
    profile prf;

    prf.profileTaskhandling();
    grp.inputBox();
    return 0;
}   