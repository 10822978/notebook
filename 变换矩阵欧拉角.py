from scipy.spatial.transform import Rotation
import numpy as np

#calibration_param.json文件里
#算出来写入        
# "angle_pitch": 88.85000092844395 , 
# "angle_yaw": 89.99999989716 ,
Tbc = np.array([
    [
      -0.0008726623870565293,
      0.007854661202346475,
      0.9999687708912487,
      2.0
    ],
    [
      -0.9999992384582119,
      0.000865783458856995,
      -0.0008794896239086828,
      -0.235
    ],
    [
      -0.0008726645142379851,
      -0.9999687768707576,
      0.007853899684033858,
      1.4
    ],
    [
      0.0,
      0.0,
      0.0,
      1.0
    ]
  ]
)
Rbc = Tbc[:3, :3]
Rcb = Rbc.T

camera_trans_x = Tbc[0, 3]
camera_trans_y = Tbc[1, 3]
camera_height = Tbc[2, 3]
print(f'        "camera_trans_x": {camera_trans_x},')
print(f'        "camera_trans_y": {camera_trans_y},')
print(f'        "camera_height": {camera_height},')

yaw, roll, pitch = Rotation.from_matrix(Rcb).as_euler("zyx", degrees=True)
print(f'        "angle_pitch": {str(pitch)},') # x
print(f'        "angle_yaw": {str(yaw)},')     # y
print(f'        "angle_roll": {str(roll)},')   # z
