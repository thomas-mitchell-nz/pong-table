# Pong Table

This repository contains the code I developed for a light-up pong table that I designed and built. The table features cup-detecting RGB pods on each side, with each pod comprising three RGB LEDs and a pair of infrared emitters and receivers. The system is controlled using an Arduino, and all electronics are concealed beneath a sheet of opal perspex.

## Powering Up the System

The system is powered by a 5V wall adapter connected to the DC plug on the Arduino shield. Upon powering on, the system will enter the calibration sequence.

**Note:** For accurate calibration, cover each LED pod with a cup before powering on the system. Once the LED pods turn green, remove all the cups from the table and wait a few seconds until the pods display solid colors.

## Recalibrating the Cup Detection System

To recalibrate the sensors and ensure accurate cup detection, follow these steps:

1. Place a cup over each LED pod on the table.  
2. Press and hold the push-button for at least 3 seconds, then release it. The LED pods will briefly flash green, signaling the start of the calibration process.  
3. Once the LED pods turn green again, remove all cups from the table. This allows the system to capture the background values.  
4. After a few seconds, the LED pods will display solid colours to confirm that the calibration is complete and no cups are currently detected.

**Important:** Ensure that no objects are obstructing the sensors during the second half of the calibration to capture accurate background values.

## Enabling and Disabling Sensors

The push-button also allows for temporarily disabling or enabling the sensors. Here’s how it works:  

- **Short press**: Deactivates the sensors.  
- **Another short press**: Reactivates the sensors.  

This feature is particularly useful for troubleshooting or when you want to disable sensors that may be malfunctioning or interfering with gameplay.

## Future Improvements

Several enhancements could be implemented to improve the system’s performance and reliability:

1. **Reducing Noise in Long Cables:** Replace the centralized Arduino with two smaller Arduino boards, one under each side of the table, communicating serially. This setup would minimize interference and improve data transmission.
2. **Improving Sensor Consistency:** The homemade sensors have variable characteristics that affect the reliability of the digital filters. Future versions could incorporate standardized sensors or advanced calibration techniques to address this issue.
3. **Adapting to Ambient Light:** The system performs best in darker environments due to its sensitivity to ambient light levels. Future iterations could include light sensors or adaptive algorithms to optimize performance under varying lighting conditions.

