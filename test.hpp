#ifndef TEST_HPP
#define TEST_HPP
#include "LineDescriptor.hh"
#include <iostream>
using namespace std;
void svScaleLines(ScaleLines &sl,string filename,string subname)
{
    int j;
    int i;
    int k;
    ofstream savefile(filename + subname + ".txt");
    for(i = 0;i<sl.size();i++)
    {
        for(j = 0;j<sl[i].size();j++)
        {
            savefile<<sl[i][j].startPointX<<" "
                   <<sl[i][j].startPointY<<" "
                  <<sl[i][j].endPointX<<" "
                 <<sl[i][j].endPointY<<" "
                <<sl[i][j].sPointInOctaveX
               <<" "<<sl[i][j].sPointInOctaveY
              <<" "<<sl[i][j].ePointInOctaveX
             <<" "<<sl[i][j].ePointInOctaveY
            <<" "<<sl[i][j].direction
            <<" "<<sl[i][j].salience
            <<" "<<sl[i][j].lineLength
            <<" "<<sl[i][j].numOfPixels
            <<" "<<sl[i][j].octaveCount;
            for(k = 0;k<sl[i][j].descriptor.size();k++)
            {
                savefile<<" "<<sl[i][j].descriptor[k];
            }
            savefile<<endl;
        }
    }
    savefile.close();
}

void svMatchResult(vector<unsigned int> matchresult, string filename, string subname)
{
    int i;
    ofstream savefile(filename + subname + ".txt");
    for(i = 0;i<matchresult.size();i = i+2)
    {
        savefile<<matchresult[i]<<" "<<matchresult[i+1]<<endl;
    }
    savefile.close();
}


#endif // TEST_HPP

