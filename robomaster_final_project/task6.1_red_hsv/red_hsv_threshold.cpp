#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    // 检查命令行参数
    if (argc != 2) {
        cout << "使用方法: " << argv[0] << " <图片路径>" << endl;
        return -1;
    }

    // 读取图像
    Mat image = imread(argv[1]);//读取指定路径的图像文件
    if (image.empty()) {
        cout << "无法加载图像: " << argv[1] << endl;
        return -1;
    }

    // 转换为HSV颜色空间
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    // 定义红色的HSV阈值范围（红色在HSV中有两个范围）
    Scalar lower_red1(0, 100, 100);    // 红色范围1的下限
    Scalar upper_red1(10, 255, 255);   // 红色范围1的上限
    Scalar lower_red2(160, 100, 100);  // 红色范围2的下限
    Scalar upper_red2(180, 255, 255);  // 红色范围2的上限

    // 创建两个掩码
    Mat mask1, mask2;
    inRange(hsvImage, lower_red1, upper_red1, mask1);//inRange函数根据阈值范围创建二值掩码
    inRange(hsvImage, lower_red2, upper_red2, mask2);

    // 合并两个掩码
    Mat redMask;
    bitwise_or(mask1, mask2, redMask);

    // 显示原始图像和掩码
    namedWindow("原始图像", WINDOW_AUTOSIZE);
    namedWindow("红色掩码", WINDOW_AUTOSIZE);
    
    imshow("原始图像", image);
    imshow("红色掩码", redMask);

    // 等待按键
    cout << "按任意键退出..." << endl;
    waitKey(0);

    // 销毁所有窗口
    destroyAllWindows();

    return 0;
}
