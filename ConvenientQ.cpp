#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <conio.h>
#include <cstdlib>
using namespace std;
// graphics class for text formatting and user interface
class graphics
{
public:
    // function to display text in a formatted box with specified width
    void txtSpace(int textboxWidth, list<string> lines)
    {
        cout << "." << string(textboxWidth, '-') << "." << endl;
        for (string line : lines)
        {
            int padding = textboxWidth - line.length();
            if (padding < 0)
            {
                padding = 0;
            }
            int leftPad = padding / 2;
            int rightPad = padding - leftPad;
            cout << "|" << string(leftPad, ' ') << line << string(rightPad, ' ') << "|" << endl;
        }
        cout << "`" << string(textboxWidth, '-') << "`" << endl;
    }

    // same as txtSpace but top and bottom lines are separated for more flexibility
    void txtSpaceup(int textboxWidth)
    {
        cout << "." << string(textboxWidth, '-') << "." << endl;
    }
    void txtSpacemd(int textboxWidth, list<string> lines)
    {
        for (string line : lines)
        {
            int padding = textboxWidth - line.length();
            if (padding < 0)
            {
                padding = 0;
            }
            int leftPad = padding / 2;
            int rightPad = padding - leftPad;
            cout << "|" << string(leftPad, ' ') << line << string(rightPad, ' ') << "|" << endl;
        }
    }
    void txtSpacedn(int textboxWidth)
    {
        cout << "`" << string(textboxWidth, '-') << "`" << endl;
    }

    // function to convert a string to uppercase
    string upperConv(string fromConversion)
    {
        for (auto &toBeConverted : fromConversion)
        {
            toBeConverted = toupper(toBeConverted);
        }
        return fromConversion;
    }

    // function to convert a string to lowercase
    string lowerConv(string fromConversion)
    {
        for (auto &toBeConverted : fromConversion)
        {
            toBeConverted = tolower(toBeConverted);
        }
        return fromConversion;
    }

    // bool decision box for user input
    // bool decision box for user input (now clears the input buffer)
    bool inputBool()
    {
        bool userDecision;
        string userInput;
        txtSpace(30, {"(Y) Yes / (N) No"});
        cout << "->";
        cin >> userInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears the leftover newline

        userInput = upperConv(userInput);
        if (userInput == "Y" || userInput == "YES")
        {
            userDecision = true;
        }
        else if (userInput == "N" || userInput == "NO")
        {
            userDecision = false;
        }
        else
        {
            txtSpace(30, {"Invalid Input", "Please enter Y or N"});
            userDecision = inputBool();
        }
        return userDecision;
    }

    // input handling for string/charStreams
    string inputTxt()
    {
        string userInput;
        while (true)
        {
            cout << "->";
            getline(cin, userInput);

            if (userInput.empty())
            {
                txtSpace(30, {"Invalid Input", "Please enter a valid text"});
                continue;
            }

            bool isValid = true;
            for (char c : userInput)
            {
                // Allowing alphabetic characters and spaces for names/positions
                if (!isalpha(c) && c != ' ')
                {
                    isValid = false;
                    break;
                }
            }

            if (!isValid)
            {
                txtSpace(30, {"Invalid Input", "Please enter a valid text"});
            }
            else
            {
                break;
            }
        }
        return userInput;
    }

    // input handling for a full line of text (including spaces)
    string inputLine(int maxLength)
    {
        string userInput;

        while (true)
        {
            cout << "->";
            getline(cin, userInput);
            if (!userInput.empty() && userInput.length() <= maxLength)
            {
                break;
            }
            txtSpace(30, {"Invalid Input", "Enter 1-" + to_string(maxLength) + " characters"});
        }
        return userInput;
    }

    // input handling for integers
    int inputNum()
    {
        int userInput;
        cout << "->";
        while (true)
        {
            cin >> userInput;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                txtSpace(30, {"Invalid Input", "Please enter a valid number"});
                cout << "->";
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
        return userInput;
    }
};

// profile related tasks and handling
class profile
{
    graphics grp;
    queue<pair<string, int>> taskQueue;
    bool taskSorted = false;

public:
    string profileName;
    int profileAge;
    string profilePosition;
    vector<pair<string, int>> profileTaskList;

    void menuProfile()
    {
        bool running = true;
        while (running)
        {
            grp.txtSpace(40, {"Task Menu: " + profileName,
                            "1. Profile Details",
                            "2. Add tasks",
                            "3. View tasks (sorted)",
                            "4. Search task",
                            "5. Complete next task",
                            "6. Back"});
            int choice = grp.inputNum();
            switch (choice)
            {
            case 1:
                profileDisplay();
                break;
            case 2:
                profileTaskAddition();
                break;
            case 3:
                profileDisplayTasks();
                break;
            case 4:
                profileSearchTask();
                break;
            case 5:
                profileComplete();
                break;
            case 6:
                running = false;
                break;
            default:
                grp.txtSpace(30, {"Invalid Input", "Please choose 1-5"});
            }
        }
    }
    // adding new profile initialization
    void profileNaming()
    {
        grp.txtSpace(30, {"Enter Profile Name:"});
        profileName = grp.inputTxt();
        grp.txtSpace(30, {"Enter Profile Age:"});
        profileAge = grp.inputNum();
        grp.txtSpace(30, {"Enter Profile Position:"});
        profilePosition = grp.inputTxt();
    }
    // Priority input handling for profile tasks
    int profilePriority()
    {
        int priority = grp.inputNum();
        while (priority < 1 || priority > 10)
        {
            grp.txtSpace(30, {"Invalid Input", "Priority must be 1-10"});
            priority = grp.inputNum();
        }
        return priority;
    }
    // adding profile tasks
    void profileTaskAddition()
    {
        grp.txtSpace(30, {"Do you want to add a task?"});
        bool addTask = grp.inputBool();
        while (addTask)
        {
            int taskPriority;
            string taskName;
            grp.txtSpace(36, {"Enter task priority (1-10): ", "1 = most important"});
            taskPriority = profilePriority();
            grp.txtSpace(30, {"Enter task name: "});
            taskName = grp.inputLine(20);
            profileTaskList.push_back({taskName, taskPriority});
            taskSorted = false;
            grp.txtSpace(30, {"Add another task? "});
            if (!grp.inputBool())
            {
                break;
            }
        }
        profileDisplayTasks();
    }

    // sorting algorithm
    void profileQuickSort(vector<pair<string, int>> &vec, int low, int high)
    {
        if (low >= high)
        {
            return;
        }

        int pivot = vec[high].second;
        int i = low;

        for (int j = low; j < high; j++)
        {
            if (vec[j].second < pivot)
            {
                pair<string, int> temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
                i++;
            }
        }

        pair<string, int> temp = vec[i];
        vec[i] = vec[high];
        vec[high] = temp;

        profileQuickSort(vec, low, i - 1);
        profileQuickSort(vec, i + 1, high);
    }

    void profileQuickSortName(vector<pair<string, int>> &vec, int low, int high)
    {
        if (low >= high)
        {
            return;
        }

        string pivot = grp.lowerConv(vec[high].first);
        int i = low;

        for (int j = low; j < high; j++)
        {
            if (grp.lowerConv(vec[j].first) < pivot)
            {
                swap(vec[i], vec[j]);
                i++;
            }
        }
        swap(vec[i], vec[high]);

        profileQuickSortName(vec, low, i - 1);
        profileQuickSortName(vec, i + 1, high);
    }

    // Binary search algorithm for searching tasks by name
    int profileSearchTName(const vector<pair<string, int>> &vec, const string &target)
    {
        string key = grp.lowerConv(target);
        int low = 0;
        int high = (int)vec.size() - 1;
        int found = -1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            string midName = grp.lowerConv(vec[mid].first);
            if (midName == key)
            {
                found = mid;
                high = mid - 1;
            }
            else if (midName < key)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return found;
    }

    void profileSortTasks()
    {
        profileQuickSort(profileTaskList, 0, (int)profileTaskList.size() - 1);
        taskQueue = queue<pair<string, int>>();
        for (const auto &task : profileTaskList)
        {
            taskQueue.push(task);
        }
        taskSorted = true;
    }

    // ask for task name and show every task with that name
    void profileSearchTask()
    {
        if (profileTaskList.empty())
        {
            grp.txtSpace(30, {"No tasks to search."});
            return;
        }
        // binary search needs names in alphabetical order, so search a sorted copy
        // and leave profileTaskList (priority order) untouched
        vector<pair<string, int>> byName = profileTaskList;
        profileQuickSortName(byName, 0, (int)byName.size() - 1);

        grp.txtSpace(30, {"Enter task name to search:"});
        string target = grp.inputLine(20);
        int index = profileSearchTName(byName, target);
        if (index == -1)
        {
            grp.txtSpace(44, {"No task named " + target});
            return;
        }
        grp.txtSpaceup(44);
        grp.txtSpacemd(44, {"Task found:"});
        // sorted data keeps equal names next to each other
        for (int i = index; i < (int)byName.size() && grp.lowerConv(byName[i].first) == grp.lowerConv(target); i++)
        {
            grp.txtSpacemd(44, {byName[i].first + " | Priority: " + to_string(byName[i].second)});
        }
        grp.txtSpacedn(44);
    }

    // task completion
    void profileComplete()
    {
        if (profileTaskList.empty())
        {
            grp.txtSpace(30, {"No task in queue."});
            return;
        }
        if (!taskSorted)
        {
            profileSortTasks();
        }
        list<string> lines = {"Which task did you complete?"};
        for (int i = 0; i < (int)profileTaskList.size(); i++)
        {
            lines.push_back(to_string(i + 1) + ". " + profileTaskList[i].first + " | Priority: " + to_string(profileTaskList[i].second));
        }
        lines.push_back("0. Cancel");
        grp.txtSpace(44, lines);
        int choice = grp.inputNum();
        while (choice < 0 || choice > (int)profileTaskList.size())
        {
            grp.txtSpace(30, {"Invalid Input", "Choose a listed number"});
            choice = grp.inputNum();
        }
        if (choice == 0)
        {
            return;
        }

        pair<string, int> done = profileTaskList[choice - 1];
        profileTaskList.erase(profileTaskList.begin() + (choice - 1));
        profileSortTasks();
        grp.txtSpace(44, {"Completed: " + done.first, "Priority: " + to_string(done.second)});
        if (!taskQueue.empty())
        {
            grp.txtSpace(44, {"Next up: " + taskQueue.front().first});
        }
    }

    // show task sorted by priority
    void profileDisplayTasks()
    {
        if (profileTaskList.empty())
        {
            grp.txtSpace(30, {"No tasks added."});
            return;
        }
        if (!taskSorted)
        {
            profileSortTasks();
        }
        grp.txtSpaceup(44);
        grp.txtSpacemd(44, {"Profile Tasks: "});
        for (const auto &task : profileTaskList)
        {
            grp.txtSpacemd(44, {task.first + " | Priority: " + to_string(task.second)});
        }
        grp.txtSpacedn(44);
    }

    void profileDisplay()
    {
        grp.txtSpaceup(30);
        grp.txtSpacemd(30, {"Profile Name: " + profileName, "Profile Age: " + to_string(profileAge), "Profile Position: " + profilePosition});
        grp.txtSpacedn(30);
    }
};

// main class for the profile management system
class convenientQ
{
    vector<profile> Accounts;
    graphics grp;

public:
    // returns true only if the correct password was entered within 3 tries
    bool loginSetup()
    {
        string passwordCheck = "password";

        for (int passwordTries = 3; passwordTries > 0; passwordTries--)
        {
            string loginInput;
            grp.txtSpace(30, {"Input password: "});

            // Password Censoring using asterisk
            char passCen;

            while ((passCen = _getch()) != 13)
            {
                if (passCen == 8)
                {
                    if (!loginInput.empty())
                    {
                        loginInput.pop_back();
                        cout << "\b \b";
                    }
                }
                else
                {
                    loginInput += passCen;
                    cout << '*';
                }
            }
            cout << endl;

            if (loginInput == passwordCheck)
            { // Info Checking
                grp.txtSpace(30, {"Correct Password"});
                return true;
            }
            if (passwordTries > 1)
            {
                grp.txtSpace(30, {"Wrong password,", "Try again?"});
                if (!grp.inputBool())
                {
                    exit(EXIT_FAILURE);
                }
            }
        }
        grp.txtSpace(30, {"Too many attempts."});
        exit(EXIT_FAILURE);
    }
    void systemInitialization()
    {
        grp.txtSpace(30, {"Welcome to the", "Profile Management System,", "User"});
    }
    void profileCreation()
    {
        while (true)
        {
            grp.txtSpace(50, {"Do you want to create a new profile?"});
            if (grp.inputBool())
            {
                profile newProfile;
                newProfile.profileNaming();
                Accounts.push_back(newProfile);
            }
            else
            {
                break;
            }
        }
    }
    // pick a profile and open its task menu
    void manageProfiles()
    {
        if (Accounts.empty())
        {
            grp.txtSpace(30, {"No profiles created."});
            return;
        }
        while (true)
        {
            list<string> lines = {"Select a profile:"};
            for (int i = 0; i < (int)Accounts.size(); i++)
            {
                lines.push_back(to_string(i + 1) + ". " + Accounts[i].profileName);
            }
            lines.push_back("0. Exit");
            grp.txtSpace(30, lines);
            int choice = grp.inputNum();
            if (choice == 0)
            {
                break;
            }
            if (choice >= 1 && choice <= (int)Accounts.size())
            {
                Accounts[choice - 1].menuProfile();
            }
            else
            {
                grp.txtSpace(30, {"Invalid Input", "Choose a listed number"});
            }
        }
    }
    void mainMenu()
    {
        while (true)
        {
            grp.txtSpace(30, {"Main Menu:", "1. Create Profile", "2. Manage Profiles", "3. Exit"});
            int choice = grp.inputNum();
            switch (choice)
            {
            case 1:
                profileCreation();
                break;
            case 2:
                manageProfiles();
                break;
            case 3:
                return;
            default:
                grp.txtSpace(30, {"Invalid Input", "Choose 1-3"});
            }
        }
    }
};

int main()
{
    convenientQ sys;
    profile prf;
    graphics grp;

    sys.loginSetup();
    sys.systemInitialization();
    sys.mainMenu();

    return 0;
}
