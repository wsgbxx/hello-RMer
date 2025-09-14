#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>          //使用M-PI

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "用法: " << argv[0] << " <图片路径>" << endl;
        return -1;
    }

    Mat img = imread(argv[1]);
    if (img.empty()) {
        cout << "错误: 无法读取图片" << endl;
        return -1;
    }
    
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);     //灰度化
    
    Mat thresh;
    threshold(gray, thresh, 127, 255, THRESH_BINARY_INV);//二直化
    
    vector<vector<Point>> contours;
    findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
      //                            只检测最外层轮廓     压缩水平、垂直和对角方向的线段，只保留端点
    double best_circularity = 0;
    vector<Point> best_contour;
    
    for (const auto& contour : contours) {
        double area = contourArea(contour);
        double img_area = img.rows * img.cols;
        if (area < img_area * 0.01) continue;//过滤噪声（虽然没啥用）
        
        double perimeter = arcLength(contour, true);
        
        
        double circularity = 4 * M_PI * area / (perimeter * perimeter);
        
        if (circularity > best_circularity) {
            best_circularity = circularity;
            best_contour = contour;
        }//选最符合的，即只检测一个圆
    }
    
    if (!best_contour.empty()) {
        Rect bbox = boundingRect(best_contour);//计算最佳轮廓的最小外接矩形
        rectangle(img, bbox, Scalar(0, 255, 0), 2);//在原图上绘制绿色矩形框标记检测到的圆形，线长为2
        imshow("检测结果", img);
        waitKey(0);
    } else {
        cout << "未找到圆形轮廓" << endl;
    }

    return 0;
}
