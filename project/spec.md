# Kiln Controller Specifications
## States
1. IDLE
2. RAMP
    - Will heat to 95.0
3. SOAK
    - Holds 95.0 (elements on below 94.0 ) for 180 ticks
4. COOL
    - Lasts until the reading is below 10.0 then moves to IDLE
5. FAULT
    - Caused when reading exceeds 98.0

## 