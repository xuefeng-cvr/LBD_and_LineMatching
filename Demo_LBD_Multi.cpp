#include "LineMatchingAlgorithm.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
using namespace std;

void usage(int argc, char **argv)
{
    cout << "Usage: " << argv[0] << "  ImgDirPath"
         << "  OurDirPath" << endl;
}

int main(int argc, char **argv)
{

    int ret = -1;
    if (argc < 3)
    {
        usage(argc, argv);
        return ret;
    }

    struct dirent *ptr;
    DIR *dir;
    string PATH(argv[1]);
    string OUT(argv[2]);

    dir = opendir(PATH.c_str());
    vector<string> files;
    fstream _file;

    //读取图片
    while ((ptr = readdir(dir)) != NULL)
    {
        //跳过'.'和'..'两个目录
        if (ptr->d_name[0] == '.')
            continue;
        files.push_back(ptr->d_name);
    }

    sort(files.begin(), files.end()); //排序

    for (int i = 0; i < files.size() - 1; ++i)
    {
        string img1 = PATH;
        string img2 = PATH;
        string out = OUT;
        img1 = img1 + files[i];
        img2 = img2 + files[i + 1];
        out = out + files[i] + "_" + files[i + 1];
        
        _file.open(out, ios::in);
        if(!_file)
        {
            image_process(img1.c_str(), img2.c_str(), out.c_str(),false);
            cout << files[i] << ">>>" << files[i + 1] << endl;
        }
        else
        {
            cout<<out<<"已经存在!"<<endl;
            _file.close();
        }
        

    }

    closedir(dir);
    return 0;
}