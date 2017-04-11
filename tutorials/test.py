import leapMotionController as lmc
import time

for i in range(10):
    print("frame:", i)
    c = lmc.LMController()
    hands = c.frame()
    for h in hands:
        print(h.detected)
        print(h.fingers[2].bones[3].nextJoint.array)
    time.sleep(1)
