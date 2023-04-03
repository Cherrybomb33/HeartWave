# comp3004_project

Team members: Jing Wang, Maddie Liu, Hao Li, Daohu Wang.

Team Project: Developing and testing a software-based prototype of a Heart Rate Variability device 


Overview:

We designed a computer software for a standalone device called HeartWave. HeartWave will be able 
to measure, analyze and display HRV (Heart RateVariability) patterns through the use of an advanced 
heart rate monitor and provide users with real-time biofeedback on their coherence levels. The goal 
of this device is to help users reduce stress and achieve a high state of coherence, an optimal 
psychophysiological state that reflects well being and health. HeartWave is based on technology 
produced by the HeartMath institute, including their Inner Balance and emWave2 line of products.

Background:

Heart rate variability (HRV) is not heart rate as measured in BPM. One’s heart rate is not
constant, rather it fluctuates. HRV is a measure of the variation in time intervals between
heartbeats.
It is a marker of the balance between the sympathetic and parasympathetic branches of the
autonomic nervous system. High HRV is generally associated with good physical and mental
health, and low HRV is associated with stress, poor health, and an increased risk of certain
diseases. HRV is a non-invasive measurement that reflects heart-brain interaction and
autonomic nervous system dynamics, which are particularly sensitive to changes in your
emotional state.
HRV can be measured using a variety of techniques, including electrocardiography (ECG),
photoplethysmography (PPG), and impedance cardiography (ICG). HRV is often used as a tool
1 This project has been specified by Igor Radonjić, with minor changes by Vojislav Radonjić.
to assess the effects of stress, exercise, and other factors on the body and to monitor changes
in physical and mental health over time.
HeartWave utilizes HRV to analyze the entire heart rhythm pattern in order to indicate and train
cardiac coherence. The goal is to achieve a continuous, high level of coherence. Coherence is a
state of synchronization between your heart, brain and autonomic nervous system that has
been proven to have numerous mental, emotional and physical benefits.
HeartWave displays your heart rhythm in real time providing ongoing biofeedback. A coherent
heart rhythm is defined as a relatively harmonic, sine-wavelike signal. The goal for the user is to
change the displayed erratic incoherent heart rhythm below into a smooth, regular wave. The
device will indicate the level of heart coherence, from low coherence to medium and high
coherence.
HRV naturally varies with breathing. As you breathe in HR (heart rate) speeds up, as you
breathe out it slows down. This is because inhalation is associated with the signal from the
sympathetic nervous system (flight and fight), whereas exhalation signals the parasympathetic
nervous system (rest and relaxation). These signals are mediated by the vagus nerve which
controls HRV. A high range in HRV is evidenced in the undulating coherent wave pattern that is
in-sync with a slow and steady respiratory rate. This is why the HeartWave includes an optional
breath pacer for the user to help achieve a high state of coherence.
So, in short, the HeartWave will display the heart rhythm signals in real time for the user, along
with a variety of key indicators to help facilitate and measure coherence levels. The device will
have a history or log that records data about individual sessions and progress over time. There
will also be a settings tab. The features will be listed in the next section. The student is free to
design and implement the user interface as they see fit, as long as the key features are
included.
For more information, visit the HeartMath institute at www.heartmath.com

Requirements:

Figure 1: Example User Interface
The HeartWave includes the following features:
● A light on the machine and/or a symbol on the screen that indicates an active pulse
reading
● A suggested user interface consists of the following main components: A screen and
buttons. The screen contains the menu options and the display graph. There are eight
buttons: an off/on button for the device, a menu button, a standard back button which will
return the user to the menu, four arrow buttons (up/down,left/right) and a selector in the
center of the arrow buttons which also functions as a start/stop button in session mode.
● In addition, the device has an led light that changes to red, blue or green to indicate
coherence level
● Press selector to initiate and end a session. The menu options are displayed as default
on the session screen. There is an option at the top to start a new session. The menu
could consist of the following options: start new session, settings, log/history.
● Session screen must display the main HRV graph (HR vs time) with key metrics
● On the device there should be a light that changes to red, blue or green indicating low,
medium or high coherence, depending on the challenge level
● The metrics on the screen include the current coherence score (numerical value), length
(duration of session), achievement (total sum of coherence scores sampled every 5
seconds)
● A breath pacer in the form of a strip of lights on the machine itself or a ball going back
and forth on the session screen, default set at one breath every 10 seconds, adjustable
in settings
● The settings tab includes challenge level and breath pacer settings
● There are 4 challenge levels for coherence, from beginner to advanced, for the user to
choose
● The breath pacer, 1-30 seconds, increases time interval between each breath, default at
10 seconds
● When the user ends a session a summary view will appear that includes the following
information: challenge level, percentage of time in different coherence levels (low
medium and high), average coherence, length of session, achievement score, entire
HRV graph
● The menu contains a log or history tab of all sessions, with dates, when selected show
the summary view, as well as the ability to delete a session
● An option to reset, wipe all data and restore the device to the initial install condition
● There is a battery charge indicator on the session screen
● A beep goes off when a new coherence level is reached

Technical Information:

Achievement Score: The sum of your individual Coherence Scores during the length of a
session. It can be improved by achieving higher Coherence Scores and the length of time spent
in Coherence during the session. It is the total of all Coherence. The scoring algorithm updates
your Coherence Score every 5 seconds during an active session and adds them together giving
you a sum which is called Achievement on the app displays.
Heart Coherence: Coherence refers to your internal order or harmony. Increased Coherence
enables better balance, greater health, and new levels of creativity, resilience and productivity.
Coherence Indicator: The light or coloured circle at the top of the Session View. Reflective of
your state of Coherence over the last 64 seconds, it indicates your current state of Coherence.
Green for High, Blue for Medium and Red for Low.
Coherence Score: A measure of the degree of Coherence in the heart rhythm pattern. A
Coherent heart rhythm is a stable regular repeating rhythm resembling a sine wave at a single
frequency between 0.04-0.24 Hz (3-15 cycles per minute). The scoring algorithm continuously
monitors the most current 64 seconds of heart rhythm data and updates the score every 5
seconds. The more stable and regular the heart rhythm frequency is, the higher the Coherence
Score. Scores range from 0-16. The score range is the guide to setting the Challenge Levell.

Coherence Score Guide
0.5 Basic – good beginner level
1.0 Good
2.0 Very good
3.0+ Excellent

Challenge Level: 

These settings are thresholds for the levels of Coherence that determine if you
are in low (red), medium (blue) or high (green) Coherence. There are four different Challenge
Levels; 1, 2, 3, and 4. As your Coherence Score rises you shift from one range (low, med or
high) to the next. The Coherence Score threshold between the three ranges is gradually
increased at a rate of 15% for each higher Challenge Level 1 ‐ 3 and 30% between 3 ‐ 4.
The challenge thresholds for the medium level are at level 1, med 0.5-0.9, level 2, med 0.6-2.1,
level 3, med 1.8-4.0, level 4, med 4.0-6.0. Below and above these medium ranges are low and
high Coherence levels for each challenge level.
Coherence and Achievement Scores are not affected by the Challenge Level Setting.
Heart Rate Variability (HRV): The normally occurring beat-to-beat changes in heart rate.
Analysis of HRV is an important tool used to assess heart-brain interactions and autonomic
nervous system dynamics (function, synchronization and balance). HRV is considered a key
indicator of aging, cardiac health, resilience and overall well-being.

Further Information:

Visit the HearthMath website for more information at www.heartmath.com.
The algorithms and coherence scoring system is based on HeartMath technology, including the
Inner Balance and emWave2 line of products.
The following is a link to the user manual for the Inner Balance:
https://cdn.heartmath.com/manuals/inner_balance_ios_android.pdf
The following is a link to a more detailed background on the science of HRV:
https://www.heartmath.org/research/science-of-the-heart/heart-brain-communication/
The following is a link to a presentation “Engaging The Intelligence of the Heart” by Howard
Martin that includes a demo:
https://www.youtube.com/watch?v=A9kQBAH1nK4
