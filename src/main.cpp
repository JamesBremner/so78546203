#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

class cRelation
{
public:
    int myA;
    int myB;
    int myR;
    cRelation(
        int A,
        int B,
        int rel);
};

class cInstance
{
public:

    void generate1();   // generate test case
    void solve();       // solve the problem
    void show();        // show the solution

private:

    std::vector<std::string> vPersons;
    std::vector<cRelation> vRelations;
    std::vector<int> vInvited;

    void clear();
    void add(
        const std::string &A,
        const std::string &B,
        int rel);
    int find(const std::string &name);
    void inviteOnValid(int ip);
    bool isValid1or2(int a, int b, const std::vector<int> &test);
    bool isValid3(int a, int b, const std::vector<int> &test);
};

    cRelation::cRelation(
        int A,
        int B,
        int rel)
        : myA(A), myB(B), myR(rel)
    {
        // relation 1 and 2 can be combined into
        // exclude one or both
        if (rel == 2)
            myR = 1;
    }

void cInstance::clear()
{
    vPersons.clear();
    vRelations.clear();
}
void cInstance::generate1()
{
    add("A", "B", 0); // invite one or both
    add("B", "C", 0);
    add("D", "E", 0);
    add("E", "F", 0);
    add("D", "E", 1); // include both or exclude both
    add("D", "E", 3); // exclude one or both
}
int cInstance::find(const std::string &name)
{
    for (int k = 0; k < vPersons.size(); k++)
        if (vPersons[k] == name)
            return k;
    vPersons.push_back(name);
    return vPersons.size() - 1;
}
void cInstance::add(
    const std::string &A,
    const std::string &B,
    int rel)
{
    vRelations.emplace_back(find(A), find(B), rel);
}
void cInstance::solve()
{
    for (auto &r : vRelations)
    {
        if (r.myR == 0)
        {
            inviteOnValid(r.myA);
            inviteOnValid(r.myB);
        }
    }
}

void cInstance::inviteOnValid(int ip)
{
    if (std::find(vInvited.begin(), vInvited.end(), ip) != vInvited.end())
        return;

    std::vector<int> test = vInvited;
    test.push_back(ip);
    for (auto &r : vRelations)
    {
        switch (r.myR)
        {
        case 0:
            break;
        case 1:
            if (!isValid1or2(r.myA, r.myB, test))
                return;
            break;
        case 3:
            if (!isValid3(r.myA, r.myB, test))
                return;
            break;
        default:
            throw std::runtime_error(
                "Bad relation");
        }
    }
    vInvited = test;
    return;
}

void cInstance::show()
{
    std::cout << "Invitees ";
    for (int v : vInvited)
    {
        std::cout << vPersons[v] << " ";
    }
    std::cout << "\n";
}

bool cInstance::isValid1or2(int a, int b, const std::vector<int> &test)
{
    if (std::find(test.begin(), test.end(), a) == test.end())
    {
        // a is excluded
        if (std::find(test.begin(), test.end(), a) != test.end())
        {
            // b is included

            // std::cout << "isValid1or2 failed " << vPersons[a] << " excluded " << vPersons[b] << " included\n";

            return false;
        }
    }
    return true;
}

bool cInstance::isValid3(int a, int b, const std::vector<int> &test)
{
    if (
        std::find(test.begin(), test.end(), a) != test.end() &&
        std::find(test.begin(), test.end(), b) != test.end())
        return false;
    return true;
}

main()
{
    cInstance I;
    I.generate1();
    I.solve();
    I.show();
    return 0;
}
