# Lunar Landing Site Navigator (NASA Space Apps Challenge 2026)

This is a high-speed C++ ephemeris analysis engine and offline HTML5 web visualizer built for the **Lunar Landing Site Navigator** challenge. The goal is to quickly evaluate solar illumination, power density, and Direct-to-Earth (DTE) communication windows for landing sites near the Moon's South Pole.

## 1. Problem & Motivation
Missions targeting the Lunar South Pole (such as Artemis and CLPS landers) operate in one of the most challenging environments in the solar system:
- **Extreme Solar Geometry:** Near -89.9°S, the Sun circles just above the horizon (~1.5°), creating long crater shadows and severely reducing solar panel power output.
- **Communication Blackouts:** Without dedicated lunar relay satellites, landers rely on Direct-to-Earth (DTE) line-of-sight. Due to lunar libration (the Moon's slight wobble), Earth dips below the horizon for nearly 60% of the lunar cycle.
- **Data Bottleneck:** Tools like NASA's JPL Horizons give accurate astronomical tables, but reading raw text files manually takes too much time when launch delays force rapid schedule re-evaluation.

## 2. System Architecture & Files
The project is split into a fast backend calculation engine and a zero-dependency frontend visualizer:
- **`main.cpp`:** The core C++ analysis engine. It reads raw JPL Horizons datasets, filters out astronomical flags (`*`, `*i`, `*m`), runs physics and countdown algorithms, prints console telemetry, and exports `data.js`.
- **`sun.txt` & `earth.txt`:** Hourly topocentric ephemeris datasets exported from NASA JPL Horizons for Shackleton Crater (-89.9°S, 0.0°E).
- **`data.js`:** Automatically generated JavaScript array containing 721 hourly records of Sun/Earth azimuth, elevation, and Sunset countdowns.
- **`nasa.html`:** A standalone HTML5 Canvas dashboard that reads `data.js` and provides an interactive 721-hour timeline slider and elevation chart (works 100% offline with zero external libraries).

## 3. Physics & Mathematical Model
To accurately simulate conditions on the Moon, `main.cpp` uses the following equations:
- **Airless Spherical Horizon Dip:** Unlike Earth, the Moon has no atmosphere and zero optical refraction. For a mean lunar radius $R = 1737.4\text{ km}$ and lander sensor height $h = 2\text{ m}$ ($0.002\text{ km}$), the true geometric horizon dip angle is:
  $$\theta_{\text{dip}} = -\arccos\left(\frac{R}{R + h}\right) \approx -0.0869^\circ$$
- **Visibility Threshold:** Sunlight is active whenever $\theta_{\text{sun}} > \theta_{\text{dip}}$, and Direct-to-Earth communication is active whenever $\theta_{\text{earth}} > \theta_{\text{dip}}$.
- **Incident Solar Flux Density ($\text{W/m}^2$):** Using the cosmic solar constant $S_0 = 1361\text{ W/m}^2$, the average solar power density relative to the effective horizon is computed across all sunlit hours:
  $$P_{\text{flux}} = S_0 \cdot \sin(\theta_{\text{sun}} - \theta_{\text{dip}})$$

## 4. Algorithmic Efficiency (Time & Space Complexity)
- **Time Complexity — $O(N)$ Linear:** Finding the exact remaining hours until the next Sunset and Earthset for every timestamp using nested loops would take $O(N^2)$ operations. Instead, `main.cpp` uses a **single reverse-pass dynamic sweep** from $i = N - 1$ down to $0$, tracking the last seen horizon-crossing index. This processes 721 hourly records in **< 0.01 seconds**.
- **Space Complexity — $O(N)$:** Stores aligned time-series vectors for timestamps, solar/terrestrial azimuth, elevation, and precomputed countdown arrays (`sunset` and `earthset`).

## 5. Detailed Case Study Results: Shackleton Crater (-89.9°S, 0.0°E)
Running `main.cpp` on the 30-day lunar cycle dataset (**Nov 14 – Dec 14, 2026**, 721 hourly data points) produces the following engineering verdict:
- **Effective Lunar Horizon Angle:** `-0.0869 deg`
- **Solar Elevation Range:** `1.33 deg` (Min) to `1.63 deg` (Max)
- **Total Sunlight Duration:** `721 hours (100.00%)` — Confirms Shackleton's rim as a "Peak of Eternal Light" with zero sunset events during this period.
- **Longest Continuous Sunlight Streak:** `721 hours`
- **Average Solar Flux:** `37.39 W/m^2` (Indicates that landers require vertical or single-axis tracking solar arrays due to low grazing angles).
- **Direct-to-Earth (DTE) Comm Duration:** `301 hours (41.75%)` — Earth drops as low as `-4.55 deg` below the horizon for 420 hours due to lunar libration.
- **Optimal Operational Window:** `301 hours (41.75%)` — Hours where both solar charging and direct Earth telemetry are simultaneously active.

## 6. How to Run Locally
1. Keep `main.cpp`, `sun.txt`, and `earth.txt` in the same directory.
2. Compile and run `main.cpp` using any C++17 compiler (e.g., `g++ -O2 main.cpp -o navigator && ./navigator`). It will print the full engineering summary in the console and generate `data.js`.
3. Open `nasa.html` in any web browser to explore the interactive 721-hour slider and Sun/Earth elevation graph.

## 7. Future Roadmap
- **LOLA 3D Topography Integration:** Incorporating NASA Lunar Orbiter Laser Altimeter (LOLA) elevation maps to compute 360° azimuthal terrain masks for local crater walls and ridges.
- **Multi-Site Comparison Mode:** Allowing mission planners to rank multiple candidate landing sites side-by-side.
- **Live JPL Horizons API:** Automating direct ephemeris fetching for any custom lunar coordinate and date range.

---
*SI/AI Disclosure: AI tools were used to assist with HTML5 canvas chart rendering, code debugging, and text editing.*
