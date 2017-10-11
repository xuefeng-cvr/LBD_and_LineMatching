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
    string PARAM(argv[3]);

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

    for (int i = 0; i < files.size() - 1; i++)
    {
        string img1path = PATH;
        string img2path = PATH;
        string outpath = OUT;
        string parampath;
        if(!PARAM.empty())
        {
            parampath = PARAM + to_string(i) + "_" + to_string(i+1);
        }

        img1path = img1path + files[i];
        img2path = img2path + files[i + 1];
        outpath = outpath + to_string(i) + "_" + to_string(i+1);
        
        _file.open(outpath, ios::in);
        if(!_file)
        {
            image_process(img1path, img2path, outpath, parampath,false);
            cout << files[i] << "_" << files[i + 1] << endl << endl;
        }
        else
        {
            cout<<outpath<<"已经存在!"<<endl;
            _file.close();
        }
    }
    closedir(dir);
    return 0;
}
