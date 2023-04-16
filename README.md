# COMP3004 Team 43: HeartWave Project

## Team Members:
- Jing Wang
- Maddie Liu
- Hao Li
- Daohu Wang

## Responsibilities:
- Jing Wang:
  - Use Cases
  - MainWindow class, DBController class, Menu class, Setting class
  - UI
  - Testing and debugging
  - Traceability matrix
  - UML class diagram

- Maddie Liu:
  - Use Cases
  - Record class
  - Sequence diagrams
  - Traceability matrix

- Hao Li:
  - Use Cases
  - MainWindow class, Session class
  - UI
  - Testing and debugging
  - Sequence diagrams
  - Video

- Daohu Wang:
  - Use Cases
  - Use case diagram
  - Session class
  - Activity diagram

## Demo video:
- YouTube link: https://youtu.be/i2RBg_o1sh8

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
    - UseCaseDiagram.pdf
    - UML.pdf
    - TraceabilityMatrix.pdf
    - DesignPattern.pdf
- README.md
- comp3004_project.pro
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

## Excution instruction:
- After clone (or unzip project zip file if you choose to download the zip file) this project into Qt Creator in course VM, open this project by open comp3004_project.pro file in the root directory. After that, you can run this application.
- If it takes too long to build the project, you may need to expand the size of memory allocated for your VM. You can do this by following this instruction: Open VirtualBox -> Choose the course VM -> Click <Setting> -> Select <System> tab -> Change size of <Base Memory> -> Press <OK> -> Start VM

## Other notes:
- You can find all design related documents in /DesignDocumentation directory. /src directory keeps all our source code, and /res directory keeps images used for buttons in UI and library code for generating HRV graph.
