from math import pi
import sys

if not '.' in sys.path:
    sys.path.append('.')

from build import pyikfast_el_mini_back as ik
# from build import pyikfast_el_mini as ik_mirror
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

JOINT_STATE_NAME = ["LB_HAA", "LB_HFE", "LB_KFE",
                    "LF_HAA", "LF_HFE", "LF_KFE",
                    "LM_HAA", "LM_HFE", "LM_KFE",
                    "RB_HAA", "RB_HFE", "RB_KFE",
                    "RF_HAA", "RF_HFE", "RF_KFE",
                    "RM_HAA", "RM_HFE", "RM_KFE"]

FOOT_LINK_NAME = ["RF_FOOT", "RM_FOOT", "RB_FOOT",
                  "LF_FOOT", "LM_FOOT", "LB_FOOT"]

mirror_trans = [(np.array((1, 1, 1)), np.array((0, 0, 0))),
                (np.array((1, 1, 1)), np.array((0.3, 0.06, 0))),
                (np.array((1, -1, 1)), np.array((0, 0, 0))),
                (np.array((1, -1, 1)), np.array((0, 0, 0))),
                (np.array((1, -1, 1)), np.array((0.3, 0.06, 0))),
                (np.array((1, 1, 1)), np.array((0, 0, 0)))]


def get_sol(target, origin, approx=False):
    foot_index = 0
    target = target*mirror_trans[foot_index][0] + mirror_trans[foot_index][1]
    origin = origin*mirror_trans[foot_index][0] + mirror_trans[foot_index][1]
    if foot_index in [2, 5]:
        # Temporarily we only have pyikfast_el_mini_back
        # sol = ik_mirror.IKFast_trans3D(list(target)+list(origin), True)
        raise ValueError("Not implemented")
    else:
        if approx:
            sol = ik.IKFast_trans3D(list(target)+list(origin), True)
        else:
            sol = ik.IKFast_trans3D(list(target), False)
    return sol


if __name__ == "__main__":
    # Origin for IK approximation
    origin = np.array([0.35350208, -0.22998902, -0.1360558])
    
    # Calculate all solutions along a ray from origin
    sols = []
    num = 100
    dir = [1, 0, 0]
    for i in range(num):
        direction = float(i/num)*np.array(dir)
        sols.append(get_sol(direction+origin, origin, True))

    pts = []
    for i in range(num):
        for pt in sols[i]:
            pts.append(pt)

    # 3D scatter
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d',
                         xlim=(-pi, pi), ylim=(-pi, pi), zlim=(-pi, pi))

    ax.scatter([pt[0] for pt in pts], [pt[1]
               for pt in pts], [pt[2] for pt in pts], c=[0.1, 0.4, 0.0, 0.2])
    print("IK solutions along a ray from origin are drawn in Configuration Space.")
    plt.show()
