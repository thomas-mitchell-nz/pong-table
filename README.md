Pong Table
This is code I developed for a light-up pong table that I designed and built. The table itself consists of cup detecting RGB pods on each side of the table. Each pod contains 3 RGB LEDs and a pair of infra-red emitters and receivers. The electronics are interfaced with using an Arduino. All of the electronics are hidden from the players under a sheet of opal perspex.

Power Supply
Utilize the 5V wall adapter to supply power to the LED strips by connecting it to the 5V terminal on the Arduino shield. Meanwhile, you can provide power to the Arduino by using any power supply with an output voltage range of 7-12V, including the option of a 6x AA battery supply.

Re-calibrating with Button
Regarding button instructions, the system features a push-button designed to reset values associated with cup detection. To calibrate, one should place a cup over each LED puck, then press and hold the push-button for more than three seconds. During this time, the software captures sensor values for each cup. After a brief delay, the LED pucks will indicate completion by turning green. At this point, all cups should be removed to allow the system to capture background values effectively. After a few seconds, the LED pucks will return to normal operation. It is crucial to ensure that no objects obstruct the sensors during calibration to ensure accurate background value capture.

Disabling Sensors with Button
Furthermore, a short press of the push-button deactivates the sensors – another short press will reactivate the sensors. This functionality serves the purpose of enabling users to temporarily disable misbehaving sensors that might affect the overall gaming experience.

Future Improvements
In order to enhance the system's performance and reliability in the future, several improvements could be explored. Firstly, to address the issue of noise generated by long cables, two smaller Arduino boards under each side could be setup to communicate serially. This solution aims to reduce interference and improve data transmission. Secondly, there's a recognition of the challenges posed by homemade sensors with variable characteristics, which impact the digital filter's dependability. Future iterations may involve more standardized sensors or advanced calibration techniques to mitigate this variability. Additionally, the system's sensitivity to ambient light levels has been observed, and it has been found to perform optimally in darker environments. This could lead to the incorporation of light sensors or adaptive algorithms for better real-time adjustments in varying lighting conditions.