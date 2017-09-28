#include "LineMatchingAlgorithm.hpp"

using namespace std;

void usage(int argc, char **argv)
{
	cout << "Usage: " << argv[0] << "  image1.png"
		 << "  image2.png" << " out.png" << endl;
}

int main(int argc, char **argv)
{
	int ret = -1;
	if (argc < 4)
	{
		usage(argc, argv);
		return ret;
	}
    //load first image from file
    image_process(argv[1],argv[2],argv[3],false);
    return 0;
}
