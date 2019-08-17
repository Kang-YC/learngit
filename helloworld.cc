#include <iostream>
#include <cmath>

#include "ceres/ceres.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <vector>
#include <Eigen/Core>

#include <ceres/rotation.h>

using namespace ceres; 
using namespace std;
int main( )
{

    const float pi = 3.1415926;
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity( );
    Eigen::AngleAxisd rotation_vector( M_PI / 2, Eigen::Vector3d( 0, 0, 1 ) );
    cout << "rotation_matrix = \n" << rotation_vector.matrix( ) << endl;  // 转换成矩阵
    rotation_matrix = rotation_vector.toRotationMatrix( );  // 直接赋值
    cout << "rotation_matrix = \n" << rotation_matrix << endl;  // 转换成矩阵
 
    // 用AngleAxis进行坐标变换
    const Eigen::Vector3d v( 1, 0, 0 );
    cout<<" v = \n"<< v <<endl;
    Eigen::Vector3d v_rotated = rotation_vector * v;
    cout << "( 1, 0, 0 ) after rotation = \n" << v_rotated << endl;
 
    // 用旋转矩阵进行坐标变换
    v_rotated = rotation_matrix * v;
    cout << "( 1, 0, 0 ) after rotation = \n" << v_rotated << endl;
 
    // 将旋转矩阵转换成欧拉角
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles( 0, 1, 2 );  // x-y-z 顺序，即rpy
    cout << "roll pitch yaw = \n" << euler_angles << endl;
 
    // 用Eigen::Isometry表示欧氏变换矩阵
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity( );  // 三维变换矩阵
    T.rotate( rotation_vector );  // 旋转部分赋值
    T.pretranslate( Eigen::Vector3d( 1, 0, 0 ) );  // 设置平移向量
    cout << "Transform matrix = \n" << T.matrix( ) << endl;
 
    // 用欧氏变换矩阵进行坐标变换，此处的乘法运算符是重载意义上的
    Eigen::Vector3d v_transformed = T * v;  // 相当于R*v + t
    cout << "v transformed = \n" << v_transformed << endl;
 
    // 相应地，仿射变换和摄影变换，使用Eigen::Affine3d和Eigen::Projective3d
 
    // 直接将旋转向量赋值给四元数，反之亦然
    Eigen::Quaterniond q = Eigen::Quaterniond( rotation_vector );
    cout << "quaternion = \n" << q.coeffs( ) << endl;  // Eigen的存储顺序为(x,y,z,w)，实部为w
    // 直接将旋转矩阵赋值给四元数
    q = Eigen::Quaterniond( rotation_matrix );  
    cout << "quaternion = \n" << q.coeffs( ) << endl;
 
    // 用四元数旋转一个向量，使用重载过的乘法运算符
    v_rotated = q * v;  // 相当于qvq^{-1}
    cout << "( 1, 0, 0 ) after rotation = \n" << v_rotated << endl;

   //euler angle to quaterniond


//cout<<camera[2]<<endl;
float camera[3]={0,pi/2,pi/2};

Eigen::AngleAxisd rollAngle(camera[0], Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd pitchAngle(camera[1], Eigen::Vector3d::UnitY());
  Eigen::AngleAxisd yawAngle(camera[2], Eigen::Vector3d::UnitZ());
  q = rollAngle * pitchAngle * yawAngle;
   v_rotated = q * v;  // 相当于qvq^{-1}
    cout << "( 1, 0, 0 ) after rotation = \n" << v_rotated << endl;


    //const Eigen::Vector3d camera( 0, 0, pi/2 );

    ceres::Problem problem;

    float v_int[3] = {1, 0, 0};
// r p y
    //int v_int[3] = {int(v[0]), int(v[1]), int(v[2])};
    //int v_rotated_int[3] = {int(v_rotated[0]), int(v_rotated[1]), int(v_rotated[2])};
    //ceres::AngleAxisRotatePoint(camera,v,v_rotated);
    ceres::AngleAxisRotatePoint(camera,v_int,v_int);
cout << "( 1, 0, 0 ) after rotation = \n" << v_int[0]<<" "<< v_int[1]<<" "<< v_int[2]<< endl;

    //cout << "( 1, 0, 0 ) after rotation = \n" << v_rotated_int[0]<< v_rotated_int[1]<< v_rotated_int[2]<< endl;


 
    return 0;
}
