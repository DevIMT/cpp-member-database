#include "member.h"
#include <iostream>
#include <fstream>
#include <vector>

Member::Member(int id, std::string fn, std::string ln, std::string em){
    memberID = id;   
    f_name = fn;
    l_name = ln;
    email = em;
}

Member::Member(int id, std::string fn, std::string ln, std::string em, int ag, std::string sts){
    memberID = id;
    f_name = fn;
    l_name = ln;
    email = em;
    age = ag;
    status = sts;
}

// TODO: Store members into text file
// TODO: 

void Member::info() {
    std::string a;
    if (age != 0) {
        a = std::to_string(age);
    } else {
        a = "N/A";
    }


    std::cout << "Member: " << memberID << "\n"
              << "First name : " << f_name << "\n"
              << "Last name: " << l_name << "\n"
              << "Email: " << email << "\n"
              << "Age: " << a << "\n"
              << "Status: " << status << "\n\n";
              
}

bool Member::findMember(int id, std::vector<Member> dir)
{
    if (memberID == id)
        return true;

    return false;
}

bool Member::findMember(std::string fn, std::vector<Member> dir)
{
    if (f_name == fn)
        return true;

    return false;
}

void Member::update(){
    char input = '\0';
    std::cout << "Member: " << memberID << "\n" 
              << f_name << " " << l_name << "\n"
              << "What would you like to update?" << "\n"
              << "   F. First name" << "\n"
              << "   L. Last name" << "\n"
              << "   E. Email" << "\n"
              << "   A. Age" << "\n"
              << "   S. Status" << "\n";
    
    std::cin >> input;
    input = toupper(input);

    if (input == 'F'){
        std::string f;
        std::cout << "First name: " << f_name << "\n"
                    << "Please enter new name: ";
        std::cin >> f;
        std::cout << "Changed first name to: " << f << "\n";
        f_name = f;
    } else if (input == 'L'){
            std::string l;
            std::cout << "Last name: " << l_name << "\n"
                      << "Please enter new name: ";
            std::cin >> l;
            std::cout << "Changed last name to: " << l << "\n";
            l_name = l;
    } else if (input == 'E'){
            std::cout << "Feature is unavailable" << "\n";
    } else if (input == 'A'){
            std::string a;
            std::cout << "Age: " << age << "\n"
                      << "Please enter new age: ";
            std::cin >> a;
            std::cout << "Changed age to: " << a << "\n";
            age = stoi(a);
    } else if (input == 'S'){
            std::string s;
            std::cout << "Status: " << status << "\n"
                      << "Please enter new status: ";
            std::cin >> s;
            std::cout << "Updated status: " << s << "\n";
            status = s;
    } else {
        std::cout << "Invalid input" << "\n";
    }
}

Member addMember(int memberID, char quickadd)
{
    std::string fn;
    std::string ln;
    std::string em;
    
    std::cout << "First name: ";
    std::cin >> fn;

    std::cout << "Last name: ";
    std::cin >> ln;

    std::cout << "Email: ";
    std::cin >> em;
    std::cout << "\n";

    if (quickadd == 'Y'){
        Member m(memberID, fn, ln, em);
        return m;
    } else {
        int age_input;
        std::string sts;
        char s;
        
        std::cout << "Age: ";
        std::cin >> age_input;
        std::cout << "Status (A/E/P): ";
        std::cin >> s;
        s = toupper(s);

        if (s == 'A') sts = "Active";
        else if (s == 'P') sts = "Pending";        
        else sts = "Expired";

        Member m(memberID, fn, ln, em, age_input, sts);
        return m;
    }
}

void importDirectory(std::vector<Member> &members)
{
    std::ifstream member_dir;
    member_dir.open("./dir/directory.txt");

    if (!member_dir){
        std::cerr << "File not found.";
        return;
    }

    std::string mmbr[6];

    // Read member vector into file from line 2
    std::string line;
    int i = 0;
    while (std::getline(member_dir, line)){
        // Gather member information
        if (line ==  ""){
            // Create member object
            Member a(stoi(mmbr[0]),mmbr[1],mmbr[2],mmbr[3],stoi(mmbr[4]),mmbr[5]);
            members.push_back(a);
            i = 0;
        } else {
            mmbr[i++] = line;
        }
    }
    
    Member a(stoi(mmbr[0]),mmbr[1],mmbr[2],mmbr[3],stoi(mmbr[4]),mmbr[5]);
    members.push_back(a);

    member_dir.close();
}

void Member::exportDirectory(std::ofstream &outfile)
{
    outfile << memberID << "\n" << f_name << "\n" << l_name << "\n"
            << email << "\n" << age << "\n" << status;
}

int lastMemberID(const std::vector<Member> &dir)
{
    int maxID = 0;
    for (auto e : dir){
        if (e.memberID > maxID){
            maxID = e.memberID;
        }
    }

    return maxID;
}