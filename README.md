# HeartWave Project

## Introduction:
This is a Team Project for Developing and testing a software-based prototype of a Heart Rate Variability(HRV) device. HeartWave is able to measure, analyze and display HRV patterns through the use of an advanced heart rate monitor and provide users with real-time biofeedback on their coherence levels. The goal of this device is to help users reduce stress and achieve a high state of coherence, an optimal psychophysiological state that reflects well being and health. HeartWave is based on technology produced by the HeartMath institute, including their Inner Balance and emWave2 line of products.

## File Organization:
- DesignDocumentation
    - SequenceDiagrams
        - StartNewSession.pdf
        - ExtensionCases.pdf
        - ChangeSettings.pdf
        - PowerOnOff.pdf
        - ViewHistory.pdf
    - ActivityDiagram.pdf
    - UseCases.pdf
    - UML.pdf
    - TraceabilityMatrix.pdf
    - DesignPatterns.pdf
- README.md
- heartwave.pro
- mainwindow.ui
- src
    - main.cpp
    - mainwindow.cpp
    - mainwindow.h
    - menu.cpp
    - menu.h
    - dbController.cpp
    - dbController.h
    - record.cpp
    - record.h
    - session.cpp
    - session.h
    - setting.cpp
    - setting.h
- res
    - img
        - back.png
        - change.png
        - check.png
        - down.png
        - left.png
        - menu.png
        - power.png
        - right.png
        - select.png
        - sensor.png
        - up.png
    - lib
        - qcustomplot.cpp
        - qcustomplot.h
    - res.qrc

## Execution instruction:
- Clone this project and open .pro file in Qt Creator. Run the application and interact with HeartWave device.
