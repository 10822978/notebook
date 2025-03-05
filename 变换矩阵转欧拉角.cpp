#include <iostream>
#include <Eigen/Dense>
#include<Eigen/Geometry>

using namespace Eigen;

int main() {
    // 定义Tbc矩阵
    Matrix4d Tbc;
    // "angle_pitch": 89,
    // "angle_yaw": 88,
    // "angle_roll": 0.03,
    Tbc << -0.0008726623870565293,
        0.007854661202346475,
        0.9999687708912487,
        2.0,
        -0.9999992384582119,
        0.000865783458856995,
        -0.0008794896239086828,
        -0.235,
        -0.0008726645142379851,
        -0.9999687768707576,
        0.007853899684033858,
        1.4,
        0.0,
        0.0,
        0.0,
        1.0;

    // 提取旋转矩阵rotation_matrix
    Matrix3d rotation_matrix = Tbc.block<3, 3>(0, 0);
    // 计算Rcb（rotation_matrix的转置）
    // Matrix3d Rcb = rotation_matrix.transpose();

    // 提取相机平移量
    double camera_trans_x = Tbc(0, 3);
    double camera_trans_y = Tbc(1, 3);
    double camera_height = Tbc(2, 3);

    // 输出相机平移量
    std::cout << "        \"camera_trans_x\": " << camera_trans_x << "," << std::endl;
    std::cout << "        \"camera_trans_y\": " << camera_trans_y << "," << std::endl;
    std::cout << "        \"camera_height\": " << camera_height << "," << std::endl;

    Eigen::Vector3d euler_angles=rotation_matrix.eulerAngles(2,1,0);
    std::cout<<"Standard: euler_angles=\n"<<euler_angles*180/M_PI<<"\n"<<std::endl;

    double yaw = euler_angles(0);
    double pitch = euler_angles(1);
    double roll = euler_angles(2);
    yaw*=(180.0/3.1415927);
    pitch*=(180.0/3.1415927);
    roll*=(180.0/3.1415927);

    // nullmax独创坐标系定义
    double nullmax_pitch = 180.0-roll;
    double nullmax_yaw = 180.0-yaw;
    double nullmax_roll = 180.0+pitch;

    nullmax_pitch = std::fmod(nullmax_pitch + 180, 360) - 180;
    nullmax_yaw = std::fmod(nullmax_yaw + 180, 360) - 180;
    nullmax_roll = std::fmod(nullmax_roll + 180, 360) - 180;

    std::cout << "        \"angle_pitch\": " << nullmax_pitch << "," << std::endl;
    std::cout << "        \"angle_yaw\": " << nullmax_yaw << "," << std::endl;
    std::cout << "        \"angle_roll\": " << nullmax_roll << "," << std::endl;

    return 0;
}
