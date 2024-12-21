# Pong Table

This repository contains the code I developed for a light-up pong table that I designed and built. The table features cup-detecting RGB pods on each side, with each pod comprising three RGB LEDs and a pair of infrared emitters and receivers. The system is controlled using an Arduino, and all electronics are concealed beneath a sheet of opal perspex, ensuring a seamless and polished look.

## Power Supply
To power the LED strips, use a 5V wall adapter connected to the 5V terminal on the Arduino shield. The Arduino itself can be powered using any supply with an output voltage range of 7-12V, such as a 6x AA battery pack.

## Re-Calibrating the Sensors
The table includes a push-button for recalibrating the cup detection system. To recalibrate:
1. Place a cup over each LED pod.
2. Press and hold the push-button for more than three seconds. The software will record sensor values for each cup.
3. Once calibration is complete, the LED pods will briefly turn green to indicate success.
4. Remove all cups from the table to allow the system to capture background values.
5. After a few seconds, the LED pods will return to normal operation.

**Important:** Ensure that no objects obstruct the sensors during calibration to guarantee accurate background value capture.

## Disabling and Enabling Sensors
The push-button also allows for temporarily disabling or enabling the sensors:
- A short press deactivates the sensors.
- Another short press reactivates them.

This feature is useful for troubleshooting and disabling malfunctioning sensors that might disrupt gameplay.

## Future Improvements
Several enhancements could be implemented to improve the system’s performance and reliability:
1. **Reducing Noise in Long Cables:** Replace the centralized Arduino with two smaller Arduino boards, one under each side of the table, communicating serially. This setup would minimize interference and improve data transmission.
2. **Improving Sensor Consistency:** The homemade sensors have variable characteristics that affect the reliability of the digital filters. Future versions could incorporate standardized sensors or advanced calibration techniques to address this issue.
3. **Adapting to Ambient Light:** The system performs best in darker environments due to its sensitivity to ambient light levels. Future iterations could include light sensors or adaptive algorithms to optimize performance under varying lighting conditions.

