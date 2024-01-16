import sys
if not '.' in sys.path:
    sys.path.append('.')

from build import pyikfast_el_mini_back as ik

if __name__ == "__main__":
    # print(ik.IKFast_trans3D([0, 0, 0], True))
    sols = []
    num = 20
    for i in range(num):
        sols.append(ik.IKFast_trans3D(
            [float(i/num), float(i/num), float(i/num), 0.3, 0, 0], True))
        print(sols[-1])
