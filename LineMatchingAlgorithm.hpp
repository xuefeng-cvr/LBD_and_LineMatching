#include <math.h>
#include <time.h>
#include <fstream>

#include "LineDescriptor.hh"
#include <opencv2/imgproc/imgproc.hpp>
#include "PairwiseLineMatching.hh"
#include "test.hpp"

using namespace std;
int image_process(string img1path, string img2path, string outpath, string paramfilepath, bool saveLR = false)
{
    //load first image from file
    std::string imageName1 = img1path;
    std::string imageName2 = img2path;
    cout << "imgProcess: " << imageName1 << " + " << imageName2 << " = " << outpath << endl;
    cv::Mat leftImage;
    cv::Mat rightImage;

    leftImage = imread(imageName1, cv::IMREAD_GRAYSCALE);  // Read the file
    rightImage = imread(imageName2, cv::IMREAD_GRAYSCALE); // Read the file
    if (!leftImage.data || !rightImage.data)			   // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    unsigned int imageWidth = leftImage.cols; //图片的宽与高
    unsigned int imageHeight = leftImage.rows;

    srand((unsigned)time(0));
    int lowest = 100, highest = 255;
    int range = (highest - lowest) + 1;
    unsigned int r, g, b; //the color of lines

    //initial variables
    cv::Mat leftColorImage(leftImage.size(), CV_8UC3);
    cv::Mat rightColorImage(rightImage.size(), CV_8UC3);

    cvtColor(leftImage, leftColorImage, cv::COLOR_GRAY2RGB);
    cvtColor(rightImage, rightColorImage, cv::COLOR_GRAY2RGB);

    ///////////####################################################################
    ///////////####################################################################
    //extract lines, compute their descriptors and match lines
    //提取线段，计算descriptor并进行线段匹配
    LineDescriptor lineDesc;
    PairwiseLineMatching lineMatch;

    ScaleLines linesInLeft;
    ScaleLines linesInRight;
    std::vector<unsigned int> matchResult;

    lineDesc.GetLineDescriptor(leftImage, linesInLeft);
    lineDesc.GetLineDescriptor(rightImage, linesInRight);
    //TODO remove BIAS dependecies in PairwiseMatching
    lineMatch.LineMatching(linesInLeft, linesInRight, matchResult);
    //save the param of matching
    if(!paramfilepath.empty())
    {
        svScaleLines(linesInLeft,paramfilepath,"Llines");
        svScaleLines(linesInRight,paramfilepath,"Rlines");
        svMatchResult(matchResult,paramfilepath,"MatchRes");
    }
    ///////////####################################################################
    ///////////####################################################################
    //draw  extracted lines into images
    cv::Point startPoint;
    cv::Point endPoint;
    cv::Point point;

    for (unsigned int i = 0; i < linesInLeft.size(); i++)
    {
        r = lowest + int(rand() % range);
        g = lowest + int(rand() % range);
        b = lowest + int(rand() % range);
        startPoint = cv::Point(int(linesInLeft[i][0].startPointX), int(linesInLeft[i][0].startPointY));
        endPoint = cv::Point(int(linesInLeft[i][0].endPointX), int(linesInLeft[i][0].endPointY));
        cv::line(leftColorImage, startPoint, endPoint, cv::Scalar(r, g, b));
    }
    for (unsigned int i = 0; i < linesInRight.size(); i++)
    {
        r = lowest + int(rand() % range);
        g = lowest + int(rand() % range);
        b = lowest + int(rand() % range);
        startPoint = cv::Point(int(linesInRight[i][0].startPointX), int(linesInRight[i][0].startPointY));
        endPoint = cv::Point(int(linesInRight[i][0].endPointX), int(linesInRight[i][0].endPointY));
        cv::line(rightColorImage, startPoint, endPoint, cv::Scalar(r, g, b));
    }
    if (saveLR)
    {
        imwrite("LinesInImage1.png", leftColorImage);
        imwrite("LinesInImage2.png", rightColorImage);
    }
    //TODO enable after BIAS dependecies in PairwiseMatching have been removed
    //  ///////////####################################################################
    //  ///////////####################################################################
    //  //store the matching results of the first and second images into a single image
    double ww1, ww2;
    int lineIDLeft;
    int lineIDRight;
    int lowest1 = 0, highest1 = 255;
    int range1 = (highest1 - lowest1) + 1;
    std::vector<unsigned int> r1(matchResult.size() / 2), g1(matchResult.size() / 2), b1(matchResult.size() / 2); //the color of lines

    for (unsigned int pair = 0; pair < matchResult.size() / 2; pair++)
    {
        r1[pair] = lowest1 + int(rand() % range1);
        g1[pair] = lowest1 + int(rand() % range1);
        b1[pair] = 255 - r1[pair];
        ww1 = 0.2 * (rand() % 5);
        ww2 = 1 - ww1;
        char buf[10];
        sprintf(buf, "%d ", pair);
        lineIDLeft = matchResult[2 * pair];
        lineIDRight = matchResult[2 * pair + 1];
        startPoint = cv::Point(int(linesInLeft[lineIDLeft][0].startPointX), int(linesInLeft[lineIDLeft][0].startPointY));
        endPoint = cv::Point(int(linesInLeft[lineIDLeft][0].endPointX), int(linesInLeft[lineIDLeft][0].endPointY));
        cv::line(leftColorImage, startPoint, endPoint, CV_RGB(r1[pair], g1[pair], b1[pair]), 4, cv::LINE_AA, 0);
        startPoint = cvPoint(int(linesInRight[lineIDRight][0].startPointX), int(linesInRight[lineIDRight][0].startPointY));
        endPoint = cvPoint(int(linesInRight[lineIDRight][0].endPointX), int(linesInRight[lineIDRight][0].endPointY));
        cv::line(rightColorImage, startPoint, endPoint, CV_RGB(r1[pair], g1[pair], b1[pair]), 4, cv::LINE_AA, 0);
    }

    cv::Mat cvResultColorImage1 = cv::Mat(cv::Size(imageWidth * 2, imageHeight), leftColorImage.type(), 3);
    cv::Mat cvResultColorImage2 = cv::Mat(cv::Size(imageWidth * 2, imageHeight), leftColorImage.type(), 3);
    cv::Mat cvResultColorImage = cv::Mat(cv::Size(imageWidth * 2, imageHeight), leftColorImage.type(), 3);
    cv::Mat roi = cvResultColorImage1(cv::Rect(0, 0, imageWidth, imageHeight));
    cv::resize(leftColorImage, roi, roi.size(), 0, 0, 0);

    cv::Mat roi2 = cvResultColorImage1(cv::Rect(imageWidth, 0, imageWidth, imageHeight));
    cv::resize(rightColorImage, roi2, roi2.size(), 0, 0, 0);
    cvResultColorImage1.copyTo(cvResultColorImage2);

    for (unsigned int pair = 0; pair < matchResult.size() / 2; pair++)
    {
        lineIDLeft = matchResult[2 * pair];
        lineIDRight = matchResult[2 * pair + 1];
        startPoint = cv::Point(int(linesInLeft[lineIDLeft][0].startPointX), int(linesInLeft[lineIDLeft][0].startPointY));
        endPoint = cv::Point(int(linesInRight[lineIDRight][0].startPointX + imageWidth), int(linesInRight[lineIDRight][0].startPointY));
        cv::line(cvResultColorImage2, startPoint, endPoint, CV_RGB(r1[pair], g1[pair], b1[pair]), 1, cv::LINE_AA, 0);
    }
    cv::addWeighted(cvResultColorImage1, 0.5, cvResultColorImage2, 0.5, 0.0, cvResultColorImage, -1);

    cv::imwrite(outpath+".png", cvResultColorImage);
    cvResultColorImage.release();
    cvResultColorImage1.release();
    cvResultColorImage2.release();
    leftImage.release();
    rightImage.release();
    leftColorImage.release();
    rightColorImage.release();
    roi.release();
    roi2.release();

    cout << "number of total matches = " << matchResult.size() / 2 << endl;
    matchResult.clear();
    linesInLeft.clear();
    linesInRight.clear();

}
