#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>

static std::string INDEX_NAME;
static std::string SAMPLE_VIDEO_PATH;
static std::string SOURCE_VIDEO_PATH;

using namespace std;

 void readParameter(const char* filename)
{
    std::stringstream buffer;
    std::string line;
    std::string paramName;
    std::string paramValuestr;

    std::ifstream fin(filename);
    if (!fin.good())
    {
        std::string msg("parameters file not found");
        msg.append(filename);
        throw std::runtime_error(msg);
    }
    while (fin.good())
    {
        getline(fin,line);
        if(line[0] != '#')
        {
            buffer.clear();
            buffer << line;
            buffer >> paramName;

            if(paramName.compare("SAMPLE_VIDEO_PATH") == 0)
            {
                buffer >>paramValuestr;
                SAMPLE_VIDEO_PATH = paramValuestr;
                cout<<SAMPLE_VIDEO_PATH<<endl;
            }
            else if(paramName.compare("SOURCE_VIDEO_PATH") == 0)
            {
                buffer >>paramValuestr;
                SOURCE_VIDEO_PATH = paramValuestr;
                cout<<SOURCE_VIDEO_PATH<<endl;
            }
            else if(paramName.compare("INDEX_NAME") == 0)
            {
                buffer >>paramValuestr;
                INDEX_NAME = paramValuestr;
                cout<<INDEX_NAME<<endl;
            }
            else
                throw std::runtime_error(std::string("unknown parameter"));

        }

    }

    fin.close();
}
int main()
{
  readParameter("para.txt");
  return 0;
}
