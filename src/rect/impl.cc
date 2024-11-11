#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE

    //灰度
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::imshow("gray", gray);
    //二值化
    cv::Mat binary;
    cv::threshold(gray, binary,200,255,cv::THRESH_BINARY_INV);

    cv::imshow("binary", binary);

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    // 假设只处理最大的轮廓
    if (contours.empty()) 
    {
        return res; // 如果没有找到轮廓，返回默认值
    }

    // 计算最大轮廓的外接矩形
    cv::Rect boundingRect = cv::boundingRect(contours[0]);//[min_idx]);

    // 计算最大轮廓的最小面积外接矩形
    cv::RotatedRect minAreaRect = cv::minAreaRect(contours[0]);//[min_idx]);

    // 返回结果
    res.first = boundingRect;
    res.second = minAreaRect;

    return res;
}