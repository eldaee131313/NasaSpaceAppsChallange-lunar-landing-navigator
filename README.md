# Lunar Landing Site Navigator (NASA Space Apps Challenge 2026)

This is a C++ analysis tool and simple web visualizer built for the **Lunar Landing Site Navigator** challenge. The goal is to quickly evaluate solar illumination and Direct-to-Earth (DTE) communication windows for landing sites near the Moon's South Pole.

## What It Does
Tools like NASA's JPL Horizons give accurate astronomical tables, but reading raw text files manually takes too much time when comparing mission schedules. 

I wrote a C++ engine (`main.cpp`) that parses raw ephemeris data from JPL Horizons (`sun.txt` and `earth.txt`) and calculates key metrics for the **Shackleton Crater (-89.9°S, 0.0°E)** over a 30-day lunar cycle (721 hours):
- **Airless Horizon Calculation:** Accounts for the Moon's spherical horizon dip (`-0.0869 deg` for a 2m lander) with no atmospheric refraction.
- **Power Potential:** Calculates total sunlight hours, longest continuous daylight streak, and average solar flux (`W/m^2`).
- **Communication Windows:** Tracks when Earth is visible above the horizon for direct communication without relay satellites.
- **Countdowns:** Computes remaining hours until Sunset and Earthset at any given timestamp.

## Results (Nov 14 – Dec 14, 2026)
Running `main.cpp` on the Shackleton Crater dataset gives the following output:
- **Total Sunlight:** 721 hours (100.00% continuous daylight)
- **Average Solar Flux:** 37.39 W/m^2 (due to low grazing sun angles between 1.33° and 1.63°)
- **Direct-to-Earth Comm:** 301 hours (41.75% visibility due to lunar libration)
- **Optimal Operational Window:** 301 hours (simultaneous sunlight and direct Earth link)

## How to Run
1. Compile and run `main.cpp` (keep `sun.txt` and `earth.txt` in the same folder). It prints the summary in the console and exports `data.js`.
2. Open `nasa.html` in any browser to use the timeline slider and view the Sun/Earth elevation chart.
