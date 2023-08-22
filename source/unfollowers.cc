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

void listLoad(list<string>& list, string filename, int padding) {
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
                string username = line.substr(18 + padding);
                username = username.substr(0, username.length() - 2);
                
                // Add the username to the list.
                list.insert(list.end(), username);
            }
        }
        list.sort();
        file.close(); 
    }
}

int main() {

    //Declare lists for each file.
    list<string> following;
    list<string> followers;

    // Load the files into the lists.
    listLoad(following, "following.json", 2);
    listLoad(followers, "followers_1.json", 0);

    // Declare a list for calculating unfollowers.
    list<string> unfollowers;

    // Compare the two lists.
    list<string>::iterator itFollowing = following.begin();
    list<string>::iterator itFollowers = followers.begin();

    //cout << *itFollowing << endl << *itFollowers << "\n";

    while (itFollowing != following.end() && itFollowers != followers.end()) {
        if (*itFollowing == *itFollowers) {
            itFollowing++;
            itFollowers++;
        } else if (*itFollowing < *itFollowers) {
            unfollowers.insert(unfollowers.end(), *itFollowing);
            itFollowing++;
        } else {
            itFollowers++;
        }
    }

    unfollowers.sort();
    printList(unfollowers);
}
