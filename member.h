#pragma once

#include <string>
#include <vector>

class Member {
    public:
        Member(int memberID, std::string f_name, std::string l_name, std::string email);
        Member(int memberID, std::string f_name, std::string l_name, std::string email, int age, std::string status);
        void info();
        void update();
        bool findMember(int id, std::vector<Member> dir);
        bool findMember(std::string fn, std::vector<Member> dir);
        void exportDirectory(std::ofstream &outfile);
        int memberID;
    private:
        std::string f_name;
        std::string l_name;
        std::string email;
        int age = 0;
        std::string status = "Inactive";
};