#include "member.h"
#include <iostream> 
#include <string>
#include <vector>
#include <fstream>

void importDirectory(std::vector<Member> &members);
Member addMember(int memberID, char quickadd);
int lastMemberID(const std::vector<Member> &dir);

int main()
{
    char input = '\0';
    std::vector<Member> members;
    std::vector<std::string> updates;
    
    // Imports current member directory from a text file "directory.txt"
    importDirectory(members);
    int num_member = lastMemberID(members);
    
    std::cout << "*** Welcome to the SPH Database (beta) ***" << "\n"
              << "  A. Add member" << "\n"
              << "  U. Update member" << "\n"
              << "  P. Print Directory" << "\n"
              << "  R. Remove member" << "\n"
              << "  Q. Quit" << "\n";

    do {
        std::cout << "What would you like to do? ";
        std::cin >> input;
        input = toupper(input);

        if (input == 'A'){
            char qa;
            std::cout << "Would you like to quick-add? (Y/N) ";
            std::cin >> qa;
            qa = toupper(qa);
            members.push_back(addMember(++num_member,qa));
            updates.push_back("*Added a new member*");
        } else if (input == 'U'){
            char ans;
            std::cout << "Which member would you like to update?\n"
                      << "Search by ID (I) or First name (F)? ";
            std::cin >> ans;
            ans = toupper(ans);
            if (ans == 'I'){
                int id;
                std::cout << "Enter the member's ID number: ";
                std::cin >> id;
                for (auto &e : members){
                    if (e.findMember(id,members)){
                        e.update();
                    } 
                }
            } else {
                std::string fn;
                std::cout << "Enter the member's first name: ";
                std::cin.ignore();
                std::getline(std::cin, fn);
                for (auto &e : members){
                    if (e.findMember(fn,members)){
                        e.update();
                    } 
                }
            }

            updates.push_back("*Updated member information*");
        } else if (input == 'P'){
            for (auto e : members){
                e.info();
            }
            updates.push_back("*Printed directory*");
        } else if (input == 'R'){
            std::cout << "Feature is coming" << "\n";
        }

    } while (input != 'Q');


    // Update Directory text file
    std::ofstream outfile;
    outfile.open("./dir/directory.txt");

    for (unsigned int i = 0; i < members.size(); ++i){
        if (i < members.size()-1){
            members[i].exportDirectory(outfile);
            outfile << "\n\n";
        } else {
            members[i].exportDirectory(outfile);           
        }
    }

    outfile.close();
    
    std::cout << "\n    Session Updates    " << "\n"
              << "------------------------\n";
    for (auto e : updates){
        std::cout << e << "\n";
    }

    return 0;

}
