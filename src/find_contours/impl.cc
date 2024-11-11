#include "impls.h"


std::vector<std::vector<cv::Point>> find_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用cv::findContours函数，从输入图像（3个通道）中找出所有的最内层轮廓。
     * 将它们保存起来作为函数返回值就行。contours的中文意思就是轮廓。
     * 
     * 提示：
     * 1. 使用cv::imshow来查看输入图像。
     * 2. 使用cv::drawContours来在一张图上绘制轮廓。
     * 3. 直接使用原图一般而言不利于轮廓的寻找，可以做一些简单的处理。
     * 4. findContours函数可以返回轮廓的层次结构，理解层次结构的保存方式并使用它（重点）。
     * 
     * 通过条件：
     * 运行测试点，你找到的轮廓与答案的轮廓一样就行。
     */
    


    // IMPLEMENT YOUR CODE HERE

    //cv::imshow("input",input);


    //创建一个点集，用于存放找到的轮廓
    std::vector<std::vector<cv::Point>> res;

    //灰度
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    //二值
    cv::Mat binary;
    double yuzhi = 50; // 设置阈值
    double maxVal = 255;    // 设置最大值
    int type = cv::THRESH_BINARY; // 设置阈值类型
    cv::threshold(gray, binary, yuzhi, maxVal, type);

    //轮廓
    cv::findContours(binary, res, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    //cv::imshow("counters",res);

    cv::Mat contourImage;
    cv::cvtColor(input, contourImage, cv::COLOR_BGR2RGB);
    cv::drawContours(contourImage, res, 1, cv::Scalar(0, 255, 0),2);
    cv::imshow("Contours", contourImage);
    cv::waitKey(0);

    std::vector<std::vector<cv::Point>> ans;
    ans.push_back(res[0]);
    ans.push_back(res[1]);
    ans.push_back(res[2]);

    return ans;
}