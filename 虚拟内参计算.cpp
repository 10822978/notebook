#include <iostream>
#include <Eigen/Dense>

int main() {
    // 输入数据
    double fx = 1526.84843;
    double fy = 1526.563871;
    double cx = 960;
    double cy = 540;

    double pad_left = 560;
    double pad_top = 410;
    double raw_u = 800;
    double raw_v = 256;
    double new_u = 800;
    double new_v = 256;

    bool is_far = true;

    // 计算缩放比例
    double scale_u = new_u / raw_u;
    double scale_v = new_v / raw_v;

    // 定义矩阵A和B
    Eigen::Matrix3d A;
    A << scale_u, 0, -pad_left * scale_u,
         0, scale_v, -pad_top * scale_v,
         0, 0, 1;

    Eigen::Matrix3d B;
    B << fx, 0, cx,
         0, fy, cy,
         0, 0, 1;

    // 计算矩阵乘法
    Eigen::Matrix3d C = A*B;

    // 如果is_far为true，调整C矩阵的特定元素
    if (is_far) {
        C(1, 2) -= 96;
    }

    // 输出结果
    std::cout << "Resulting matrix C:" << std::endl;
    std::cout << C << std::endl;

    std::cout << "        \"focal_length_x\": " << C(0, 0) << "," << std::endl;
    std::cout << "        \"focal_length_y\": " << C(1, 1) << "," << std::endl;
    std::cout << "        \"optical_center_x\": " << C(0, 2) << "," << std::endl;
    std::cout << "        \"optical_center_y\": " << C(1, 2) << "," << std::endl;

    return 0;
}
