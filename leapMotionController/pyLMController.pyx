import cython
import numpy as np
cimport numpy as np
from libcpp cimport bool
from libcpp.vector cimport vector


cdef extern from "cLMController/include/LMController.h":
    cdef cppclass LMVector:
        float x, y, z

    cdef cppclass LMBone:
        int type
        LMVector prevJoint
        LMVector nextJoint

    cdef cppclass LMFinger:
        int type
        vector[LMBone] bones

    cdef cppclass LMHand:
        int type
        bool isValid
        bool detected
        LMVector palmPosition
        LMVector palmVelocity
        LMVector palmNormal
        LMVector palmPositionNormalized
        vector[LMFinger] fingers

    cdef cppclass LMController:
        LMController() except +
        bool isConnected()
        bool hasFocus()
        void frame()
        vector[LMHand] hands

NBONES = 4
NFINGERS = 5
NHANDS = 2

class PyLMVector:
    def __init__(self, x=0, y=0, z=0):
        self.assign(x, y, z)

    def assign(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        self.array = np.array([self.x, self.y, self.z], dtype=np.float)

    def __str__(self):
        return "%.2f, %.2f, %.2f" % (self.x, self.y, self.z)

class PyLMBone:
    def __init__(self, type):
        self.type = type
        self.prev_joint = PyLMVector()
        self.next_joint = PyLMVector()

class PyLMFinger:
    def __init__(self, type):
        self.type = type
        self.bones = [PyLMBone(i) for i in range(NBONES)]

class PyLMHand:
    def __init__(self, type):
        self.type = type
        self.isValid = False
        self.detected = False
        self.palm_position = PyLMVector()
        self.palm_velocity = PyLMVector()
        self.palm_normal = PyLMVector()
        self.palm_position_normalized = PyLMVector()
        self.fingers = [PyLMFinger(i) for i in range(NFINGERS)]


cdef class PyLMController:
    cdef LMController *thisptr      # hold a C++ instance which we're wrapping
    cdef public object hands

    def __cinit__(self):
        self.thisptr = new LMController()
        self.hands = [PyLMHand(i) for i in range(NHANDS)]

    def __dealloc__(self):
        del self.thisptr

    def isConnected(self):
        return self.thisptr.isConnected()

    def hasFocus(self):
        return self.thisptr.hasFocus()

    def frame(self):
        self.thisptr.frame()
        for ihand in range(NHANDS):
            pyh = self.hands[ihand]
            ch = self.thisptr.hands[ihand]
            self.copy_hand(pyh, ch)
        return self.hands

    cdef copy_hand(self, pyh, LMHand ch):
        pyh.isValid = ch.isValid
        pyh.detected = ch.detected
        self.copy_vector(pyh.palm_position, ch.palmPosition)
        self.copy_vector(pyh.palm_velocity, ch.palmVelocity)
        self.copy_vector(pyh.palm_normal, ch.palmNormal)
        self.copy_vector(pyh.palm_position_normalized, ch.palmPositionNormalized)
        for ifinger in range(NFINGERS):
            pyf = pyh.fingers[ifinger]
            cf = ch.fingers[ifinger]
            self.copy_finger(pyf, cf)

    cdef copy_finger(self, pyf, LMFinger cf):
        for ibone in range(NBONES):
            pyb = pyf.bones[ibone]
            cb = cf.bones[ibone]
            self.copy_bone(pyb, cb)

    cdef copy_bone(self, pyb, LMBone cb):
        self.copy_vector(pyb.prev_joint, cb.prevJoint)
        self.copy_vector(pyb.next_joint, cb.nextJoint)

    cdef copy_vector(self, pyv, LMVector cv):
        pyv.assign(cv.x, cv.y, cv.z)