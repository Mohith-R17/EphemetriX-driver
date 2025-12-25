# Ephemetrix

**High-performance OpenVR driver for IMU-based Full Body Tracking (FBT).**

Ephemetrix bridges custom hardware—a single microcontroller with **five IMUs**—directly into the **SteamVR** ecosystem. The driver is designed for **low-latency data ingestion**, **robust coordinate transformations**, and **seamless integration** with the OpenVR runtime.

---

## 🚀 Key Features

- **Low-Latency UDP Ingestion**  
  Multi-threaded **Winsock2** implementation for high-frequency IMU data processing.

- **Advanced 3D Math**  
  Custom linear algebra utilities for quaternion-based orientation mapping between  
  **IMU (Z-up)** and **OpenVR (Y-up)** coordinate spaces.

- **Asynchronous Architecture**  
  Non-blocking `std::thread` receiver loop ensures tracking updates never stall the main driver frame.

- **Extensible Device Management**  
  Dynamic management of multiple trackers (waist, chest, limbs) via the  
  `IServerTrackedDeviceProvider` interface.

- **SteamVR Input Integration**  
  Full support for custom JSON input profiles and binding remapping.

---

## 🏗️ Technical Architecture

**Hardware Layer**  
- Microcontroller broadcasts 5-IMU data packets over UDP.

**Ingestion Layer**  
- Multi-threaded listener unmarshals `IMUPacket` data.

**Processing Layer**  
- Raw orientation data is converted into `DriverPose_t` using specialized linear algebra.

**Runtime Layer**  
- Trackers are registered as generic devices within SteamVR.

---

## 🛠️ Tech Stack

- **Language:** C++17  
- **SDK:** OpenVR (Valve Software)  
- **Networking:** Winsock2 (UDP)  
- **Build System:** CMake / MSBuild  

---

## 🔧 Setup

### Prerequisites

- Windows 10 / 11  
- Visual Studio 2019 or newer  
- SteamVR installed  

### Build Instructions

```bash
# Clone repository with submodules
git clone --recursive https://github.com/your-username/Ephemetrix.git

# Generate and build
mkdir build
cd build
cmake ..
