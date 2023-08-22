#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

void printList(list<string> list) {
    for (string username : list) {
        cout << username << "\n";
    }
}

void listLoad(list<string>& list, string filename) {
    fstream file;

    // Open a file to perform a write operation using a file object.
    file.open(filename, ios::in);
    
    // Checking whether the file is open.
    if (file.is_open()) { 
        string line;
        // Read data from the file object and put it into a string.
        while (getline(file, line)) { 
            
            if(line.find("value") != string::npos) {
                // Get the username only.
                string username = line.substr(20, line.length() - 22);

                // Add the username to the list.
                list.insert(list.end(), username);

                //cout << username << "\n";
            }
        }
        list.sort();
        file.close(); 

        //printList(list);
    }
}

int main() {

    //Declare lists for each file.
    list<string> following;
    list<string> followers;

    // Load the files into the lists.
    listLoad(following, "following.json");
    listLoad(following, "followers_1.json");

    // Declare a list for calculating unfollowers.
    list<string> unfollowers;

    // Compare the two lists.
    list<string>::iterator it;
    

    printList(unfollowers);
}
