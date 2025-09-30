# Blink LED

Blinking LED.  
LED_Blink.x directory is MPLAB X IDE project.  
LED_Blink_KiCad directory is KiCad project. 

Circuit diagram:  

| Symbol | Parts | Value | Description |
| --- | --- | --- | --- |
| C1 | Capacitor | 0.1μ | Bypass Capacitor for noise reduction. |
| C2 | Capacitor | 220μ | Bypass Capacitor for power  supply stabilization. |
| R1 | Resistor | 330Ω | Resistor for LED protection. |
| R2 | Resistor | 10K | Pull-up resistor |
| D1 | LED | - | Blink LED. |
| U1 | PIC | - | PIC12F683 |

![CircuitDiagram](CircuitDiagram.png)

## Which resistor should I choose for an LED?

Assume the power supply voltage is 5.0V, the LED forward voltage (VF) is 3.1V, and the LED rated current is 20mA.  
Since the LED consumes 3.1V, the voltage across the resistor is 5.0 - 3.1 = 1.9V.  
Therefore, the required resistance value is R = V / I = 1.9 / 0.02 = 95Ω.  
And required power is P = I × V = 0.02 × 1.9 = 0.038W.  
Therefore, a 1/4W resistor rated at 95Ω or higher is sufficient.  
※ If the resistor is too large, the voltage across it becomes excessively high, preventing the LED from lighting up.  

Digikey's calculator is useful for calculations.  
[LED Series Resistor Calculator](https://www.digikey.jp/ja/resources/conversion-calculators/conversion-calculator-led-series-resistor "LED Series Resistor Calculator")  

## Input Pin Handling

When an input pin is not connected to anything, it is referred to as "floating" or "open." It is neither Hi nor Low, but enters a high-impedance state (also called Hi-Z).  
In the high-impedance state, the voltage becomes unstable due to various noise influences.  
To avoid the high-impedance state, a voltage that is always interpreted as Hi (V<sub>IH</sub>) or a voltage that is always interpreted as Low (V<sub>IL</sub>) must be applied to the input pin.  
These voltages may differ depending on the pin, the pin's intended use, and the specific IC.  

The following shows an example of using the PIC12F683 as an I/O port:  
(Quoted from the PIC12F683 datasheet)

| Sym | Min | Typ | Max | Units | Conditions |
| :---: | :---: | :---: | :---: | :---: | :---: |
| V<sub>IL</sub> | V<sub>ss</sub> | - | 0.8 | V | 4.5V <= V<sub>DD</sub> <= 5.5V |
| | V<sub>ss</sub> | - | 0.15V<sub>DD</sub> | V | 2.0V <= V<sub>DD</sub> <= 4.5V |
| V<sub>IH</sub> | 2.0 | - | V<sub>DD</sub> | V | 4.5V <= V<sub>DD</sub> <= 5.5V |
| | 0.25V<sub>DD</sub> + 0.8 | - | V<sub>DD</sub> | V | 2.0V <= V<sub>DD</sub> <= 4.5V |

Table 1. Input Voltage for the PIC12F683  

### Pull-up

Connecting an input pin to V<sub>DD</sub> via a resistor and stabilizing its voltage with V<sub>IH</sub> is called pull-up.  
The resistor used for pull-up is called a pull-up resistor.  

### Required pull-up resistor value

* Generally 1K to 100K
* If resistance values are specified in the datasheet, use those.
* If not specified in the datasheet, you must determine the resistance value yourself.
* Some ICs have built-in pull-up functionality, so you may use that instead.

#### Example of 12F683

The 12F683 has an internal pull-up function on each GPIO pin except the GP3 pin. Here, we calculate the required resistor value when not using the internal pull-up function.  

When V<sub>DD</sub> = 5V, according to Table 1, V<sub>IH</sub> ranges from 2.0V to V<sub>DD</sub>.  
The maximum input leakage current is 1μA (per the PIC12F683 datasheet).  

When 5.0V is applied to the input pin, 0V is applied to the resistor, so R = 0.
This represents the minimum resistance value. However, it should be avoided because connecting it to GND via components like switches in the future would result in a short-circuit condition.  

Since the minimum value of V<sub>IH</sub> is 2.0V, R = V / I = 2.0 / 0.000001 = 2000000 (2M).
This represents the maximum resistance value; however, considering noise effects, values near the boundary should not be used.  

When 4.9V is applied to the input pin, 0.1V is applied to the resistor, so R = 0.1 / 0.000001 = 100,000 (100K).  

Generally:

* When the resistance value is high:  
  * Power consumption decreases  
  * If current flows due to noise, the induced voltage increases, potentially causing IC malfunction  
  * If too high, it becomes equivalent to an open circuit  
* When the resistance value is low:  
  * Power consumption increases  
  * If too low, it becomes equivalent to a short circuit

For the reasons above, resistors in the 1K-100KΩ range (especially 10KΩ) are commonly used in practice.  
