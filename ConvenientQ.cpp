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
//bool decision box for user input
    bool inputBool(){
        bool userDecision;
        string userInput;
        txtSpace(30,{"(Y) Yes / (N) No"});
        cout<<"->";
        cin>>userInput;
        userInput=upperConv(userInput);
        if(userInput=="Y"||userInput=="YES"){
            userDecision=true;
        } else if(userInput=="N"||userInput=="NO"){
            userDecision=false;
        }else{
            txtSpace(30, {"Invalid Input", "Please enter Y or N"});
            inputBool();
        }
        return  userDecision;
    }
    string inputTxt(){
        string userInput;
        cout<<"->";
        cin>>userInput;
        while (true) {
        bool isValid = true;
        for (char c : userInput){
            if (!isalpha(c)){
                isValid = false;
                break;
            }
        }
        if (!isValid){
            cin.clear();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            txtSpace(30, {"Invalid Input", "Please enter a valid text"});
            cout << "->";
        }else{
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
            }
        }
        return userInput;
    }
int inputNum() {
    int userInput;
    cout<<"->";
      while (true) {
        cin>>userInput;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            txtSpace(30, {"Invalid Input", "Please enter a valid number"});
            cout << "->";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
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
    void profileNaming(){
        grp.txtSpace(30, {"Enter Profile Name:"});
        profileName=grp.inputTxt();
        grp.txtSpace(30, {"Enter Profile Age:"});
        profileAge=grp.inputNum();
        grp.txtSpace(30, {"Enter Profile Position:"});
        profilePosition=grp.inputTxt();
    }
    void profileTaskhandling(){
        grp.txtSpace(30, {"Do you want to add a task?"});
        bool addTask = grp.inputBool();
        while (addTask) {
                int taskPriority;
                string taskName;
                grp.txtSpace(30, {"Enter task priority (1-10):"});
                taskPriority=grp.inputNum();
                grp.txtSpace(30, {"Enter task name:"});
                taskName=grp.inputTxt();
                profileTaskList.push_back({taskName, taskPriority});
                grp.txtSpace(30, {"Add another task?"});
                if(!grp.inputBool()){
                    break;
                }
        }
        if (profileTaskList.empty()) {
            grp.txtSpace(30, {"No tasks added."});
        } else {
            grp.txtSpaceup(30);
            grp.txtSpacemd(30, {"Profile Tasks:"});
            for (const auto &task : profileTaskList){
                grp.txtSpacemd(30, {task.first+"| Priority: "+to_string(task.second)});
            }
            grp.txtSpacedn(30);
        }
    }
    void profileDisplay(){
        grp.txtSpaceup(30);
        grp.txtSpacemd(30, {"Profile Name: "+profileName});
        grp.txtSpacemd(30, {"Profile Age: "+to_string(profileAge)});
        grp.txtSpacemd(30, {"Profile Position: "+profilePosition});
        grp.txtSpacedn(30);
    }
};

class convenientQ{
    vector<profile> Accounts;
    graphics grp;
public:
    void loginSetup(){
    int passwordTries=3;
    string passwordCheck="password";

    grp.txtSpace(30,{"Input password: "});
    string loginInput=grp.inputTxt();
    if(loginInput!=passwordCheck){
        grp.txtSpace(30,{"Wrong password,","Try again?"}); 
        if(!grp.inputBool()&&passwordTries==0){

        }else{
            loginSetup();
            passwordTries--;
        }
    }
    }
    void systemInitialization(){
        grp.txtSpace(30, {"Welcome to the", "Profile Management System,", "User"});


    }
    void profileCreation(){
        while (true){
            grp.txtSpace(50, {"Do you want to create a new profile?"});
            if (grp.inputBool()){
                profile newProfile;
                Accounts.push_back(newProfile);
                cout<<Accounts.size()<<endl;
            }else{
                break;
            }
        }
    }

};

int main() {
    convenientQ sys;
    profile prf;
    sys.loginSetup();

    return 0;
}
