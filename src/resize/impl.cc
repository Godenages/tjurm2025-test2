#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    // IMPLEMENT YOUR CODE HERE


    // 创建一个新的（空的）Mat对象，用于存储缩放后的图像
    cv::Mat output=cv::Mat::zeros(new_rows, new_cols, input.type());

    // 遍历新的图像
    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            // 计算对应的原始图像坐标
            float x = j / scale;
            float y = i / scale;

            // 计算四个最近邻像素的坐标
            //(x1,y1),(x2,y1)
            //(x1,y2),(x2,y2)
            // int x1 = static_cast<int>(x-1);
            // int y1 = static_cast<int>(y-1);
            // int x2 = static_cast<int>(x+1);
            // int y2 = static_cast<int>(y+1);

            int x1 = static_cast<int>(x);
            int y1 = static_cast<int>(y);
            int x2 = std::min(x1 + 1, input.cols - 1);
            int y2 = std::min(y1 + 1, input.rows - 1);


            // 确保坐标在原始图像范围内
            x1 = std::max(0, std::min(x1, input.cols - 1));
            y1 = std::max(0, std::min(y1, input.rows - 1));
            x2 = std::max(0, std::min(x2, input.cols - 1));
            y2 = std::max(0, std::min(y2, input.rows - 1));

            // 获取四个最近邻像素的值
            cv::Vec3b zuoshang = input.at<cv::Vec3b>(y1, x1);
            cv::Vec3b youshang = input.at<cv::Vec3b>(y1, x2);
            cv::Vec3b zuoxia = input.at<cv::Vec3b>(y2, x1);
            cv::Vec3b youxia = input.at<cv::Vec3b>(y2, x2);

            // 计算插值权重
            float wx1 = x - x1;
            float wx2 = x2 - x;
            float wy1 = y - y1;
            float wy2 = y2 - y;

            // 双线性插值
            cv::Vec3b pixel;
            for (int k = 0; k < 3; ++k) {
                pixel[k] = static_cast<uchar>(
                    zuoshang[k] * (1 - wx1) * (1 - wy1) +
                    youshang[k] * wx1 * (1 - wy1) +
                    zuoxia[k] * (1 - wx1) * wy1 +
                    youxia[k] * wx1 * wy2
                );
            }

            // 将计算得到的像素值赋给目标像素
            output.at<cv::Vec3b>(i, j) = pixel;
        }
    }
    

    return output;
    //return cv::Mat::zeros(new_rows, new_cols, input.type());
}

// zuoshang[k] * (1 - wx1) * (1 - wy1) +
//                     youshang[k] * wx1 * (1 - wy1) +
//                     zuoxia[k] * (1 - wx1) * wy1 +
//                     youxia[k] * wx1 * wy2