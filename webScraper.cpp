#include <string>
#include <vector>
#include "webScraper.h"
#include "globalConsts.h"
#include <iostream>
#include <fstream>
#include "Node.h"
using namespace std;

vector<Node>webScraper(int index)
{
    int nodeCounter = 0;
    vector<string> document;
    vector<Node> extract;
    ifstream infile;
    infile.open(to_string(index) + ".txt");
    //Check for Error
    if (infile.fail())
    {
        cerr << "Error Opening File" << endl;
        exit(1);
    }
    string item;
    //Read a file until you've reached the end
    while (!infile.eof())
    {
        infile >> item;
        document.push_back(item);
    }
    for(int i = 0; i < document.size()-1; i++)
    {
        if(document[i] == "rel=" + quote + "noopener" && document[i+1] == "nofollow" + quote)
            nodeCounter++;
    }
    for(int i = 0; i < nodeCounter; i++)
    {
        extract.push_back(Node("tempP", "tempO"));
    }
    
    int indexP = 0;
    int indexO = 0;
    //position
    for(int i = 0; i < document.size()-1; i++)
    {
        string p;
        if(document[i] == "rel=" + quote + "noopener" && document[i+1] == "nofollow" + quote) //landmark within text
        {
            if(document[i-1] != "target=" + quote + "_blank" + quote) //accounting for two occurrences of the position
            {
                int j = i;
                while(document[j].substr(0,7) != "title=" + quote)
                {
                    j--;
                }
                string temp;
                for(int k = j+1; k <= i-2; k++)
                {
                    temp += document[k] + " ";
                }
                p = document[j].substr(7, document[j].length()-7) + " " + temp + document[i-1].substr(0, document[i-1].length()-1);
                extract[indexP].m_position = p;
                indexP++;
            }
            else //accounting for two occurrences of the position
            {
                int tracker1 = i;
                int tracker2 = i;
                while(document[tracker1].substr(0,7) != "title=" + quote)
                {
                    tracker1++;
                }
                while(document[tracker2].substr(0,7) != "class=" + quote)
                {
                    tracker2++;
                }
                string temp2 ="";
                for(int m = tracker1+1; m <= tracker2-2; m++)
                {
                    temp2 += document[m] + " ";
                }
                p = document[tracker1].substr(7, document[tracker1].length()-7) + " " + temp2 + document[tracker2-1].substr(0, document[tracker2-1].length()-1);
                extract[indexP].m_position = p;
                indexP++;
            }
        }
    }
    //organization
    for(int i = 0; i < document.size()-1; i++)
    {
        string o;
        if(document[i] == "<span" && document[i+1] == "class=" + quote + "company" + quote + ">")
        {
            int j = i;
            for(;;)
            {
                if(document[j].length() < 7)
                    j++;
                else if(document[j].length() >= 7 && document[j].length() < 11)
                {
                    if(document[j].substr(document[j].length()-7, 7) != "</span>")
                        j++;
                    else
                        break;
                }
                else if(document[j].length() >= 11)
                {
                    if(document[j].substr(document[j].length()-11, 11) != "</a></span>" && document[j].substr(document[j].length()-7, 7) != "</span>")
                        j++;
                    else
                        break;
                }
            }
            if(document[j].length() >= 11 && document[j].substr(document[j].length()-11, 11) == "</a></span>")
            {
                int target = j;
                while(document[target] != ">")
                {
                    target--;
                }
                string temp2 = "";
                for(int l = target+1; l <= j-1; l++)
                {
                    temp2 += document[l] + " ";
                }
                o = temp2 + document[j].substr(0, document[j].length()-11);
                extract[indexO].m_organization = o;
                indexO++;
            }
            
            else if(document[j].substr(document[j].length()-7, 7) == "</span>")
            {
                string temp1 = "";
                for(int k = i+2; k <= j-1; k++)
                {
                    temp1 += document[k] + " ";
                }
                o = temp1 + document[j].substr(0, document[j].length()-7);
                extract[indexO].m_organization = o;
                indexO++;
            }
        }
    }
    return extract;
}
