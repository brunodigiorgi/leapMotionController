from setuptools import find_packages
from setuptools import setup, Extension
from Cython.Build import cythonize
import numpy

extensions = [
    Extension(
        name="leapMotionController.pyLMController",
        sources=[
            "leapMotionController/pyLMController.pyx",
            "leapMotionController/cLMController/src/LMController.cpp",
        ],
        include_dirs=[
            'leapMotionController/cLMController/include',
            'leapMotionController/cLMController/third_party',
            numpy.get_include()
        ],
        libraries=['Leap'],
        library_dirs=['leapMotionController/cLMController/third_party'],
        extra_compile_args=['-std=gnu++11', '-stdlib=libc++', '-mmacosx-version-min=10.7'],
        language='c++',
    )
]

setup(
    name='leapMotionController',
    version='0.1',
    description='Minimal Leap Motion Controller with Cython',
    author='Bruno Di Giorgi',
    author_email='bruno@brunodigiorgi.it',
    url='https://github.com/brunodigiorgi/leapMotionController',
    license="GPLv2",
    packages=find_packages(),
    include_package_data=False,
    zip_safe=False,
    install_requires=[],
    extras_require={},
    ext_modules=cythonize(extensions)
)
