#ifndef NODE_H
#define NODE_H
using namespace std;
#include <string>

struct Node
{
    Node(string position, string organization);
    string m_position;
    string m_organization;
};

#endif
