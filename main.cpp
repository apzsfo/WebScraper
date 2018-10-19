#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "webScraper.h"
#include "Node.h"

using namespace std;

int main()
{
    for(int j = 0; j < 3; j++)
    {
        ofstream package;
        package.open(to_string(j) + "output.txt");
        cout << endl << "Page" << " " << j << endl << endl;
       for(int i = 0; i < webScraper(j).size(); i++)
           cout << i+1 << "." << " " << webScraper(j)[i].m_position << "/" << webScraper(j)[i].m_organization << endl;
    }
}



