# Blink LED

Blinking LED.  
LED_Blink.x directory is MPLAB X IDE project.  
LED_Blink_KiCad directory is KiCad project. 

Circuit diagram:  

| Symbol | Parts | Value | Description |
| --- | --- | --- | --- |
| C1 | Capacitor | 0.1μ | Bypass Capacitor for noise reduction. |
| C2 | Capacitor | 220μ | Bypass Capacitor for power  supply stabilization. |
| D1 | LED | - | Blink LED. |
| R1 | Resistor | 330Ω | Resistor for LED protection. |
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