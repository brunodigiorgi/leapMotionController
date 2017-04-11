****************
*** Installation
****************

1. Download Leap Motion SDK

2. Move Leap.h, LeapMath.h plus libLeap.dylib (osx) or Leap.lib (msw) into leapMotionController/cLMController/third_party/

3. python3 setup.py install

4. (only msw) copy Leap.dll in the package installation directory. The installation directory is

	python -c "import leapMotionController; print(leapMotionController.__path__)"

