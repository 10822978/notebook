
#input
ldc =  {
            "x0": 560,
            "y0": 410,
            "width": 800,
            "height": 256,
            "target_width": 800,
            "target_height": 256
        }
cam_intrinsic =  {
            "fx": 1526.84843,
            "fy": 1526.563871,
            "cx": 960,
            "cy": 540
        }

is_far = True



def matrix_multiply(A, B):  
    # 假设A和B都是3x3的矩阵，表示为列表的列表  
    # 初始化结果矩阵C，所有元素为0  
    C = [[0 for _ in range(3)] for _ in range(3)]  
      
    # 计算矩阵乘法  
    for i in range(3):  
        for j in range(3):  
            for k in range(3):  
                C[i][j] += A[i][k] * B[k][j]  
                  
    return C  

fx=cam_intrinsic["fx"]
fy=cam_intrinsic["fy"]
cx=cam_intrinsic["cx"]
cy=cam_intrinsic["cy"]
pad_left=ldc["x0"]
pad_top=ldc["y0"]
raw_u=ldc["width"]
raw_v=ldc["height"]
new_u=ldc["target_width"]
new_v=ldc["target_height"]

# cal
scale_u=new_u/raw_u
scale_v=new_v/raw_v
A = [  
    [scale_u,         0,       -pad_left*scale_u],  
    [0,            scale_v,    -pad_top*scale_v],  
    [0,               0,             1         ]  
]  
  
B = [  
    [fx, 0, cx],  
    [0, fy, cy],  
    [0,  0,  1]  
]  
  
# 计算并打印结果  
C = matrix_multiply(A, B)  

if(is_far):
    C[1][2] -= 96
for row in C:  
    print(row)

print(f'        "focal_length_x": {str(C[0][0])},')
print(f'        "focal_length_y": {str(C[1][1])},')
print(f'        "optical_center_x": {str(C[0][2])},')
print(f'        "optical_center_y": {str(C[1][2])},')




"""
        #                    _oo8oo_
        #                   o8888888o
        #                   88" . "88
        #                   (| -_- |)
        #                   0\  =  /0
        #                 ___/'==='\___
        #               .' \\|     |// '.
        #              / \\|||  :  |||// \
        #             / _||||| -:- |||||_ \
        #            |   | \\\  -  /// |   |
        #            | \_|  ''\---/''  |_/ |
        #            \  .-\__  '-'  __/-.  /
        #        ___  '. .'  /--.--\  '. .'___
        #       ."" '<  '.___\_<|>_/___.'  >' "".
        #      | | :  `- \`.:`\ _ /`:.`/ -`  : | |
        #      \  \ `-.   \_ __\ /__ _/   .-` /  /
        #  =====`-.____`.___ \_____/ ___.`____.-`=====
        #                    `=---=`
        #                 佛  祖  保  佑！
"""
