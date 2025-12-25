//============ Copyright (c) Valve Corporation, All rights reserved.
//============
#include "device_provider.h"

#include "driverlog.h"

vr::EVRInitError MyDeviceProvider::Init(vr::IVRDriverContext *pDriverContext) {

  VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
  vr::VRDriverLog()->Log("asdfghjkl");

  const unsigned int number_of_trackers = 1;
  for (unsigned int i = 0; i < number_of_trackers; i++) {

    std::unique_ptr<MyTrackerDeviceDriver> tracker_device =
        std::make_unique<MyTrackerDeviceDriver>(i);

    if (!vr::VRServerDriverHost()->TrackedDeviceAdded(
            tracker_device->MyGetSerialNumber().c_str(),
            vr::TrackedDeviceClass_GenericTracker, tracker_device.get())) {
      DriverLog("Failed to create left controller device!");

      return vr::VRInitError_Driver_Unknown;
    }

    my_tracker_devices_.emplace_back(std::move(tracker_device));
  }

  return vr::VRInitError_None;
}

const char *const *MyDeviceProvider::GetInterfaceVersions() {
  return vr::k_InterfaceVersions;
}

bool MyDeviceProvider::ShouldBlockStandbyMode() { return false; }

void MyDeviceProvider::RunFrame() {

  for (const auto &tracker : my_tracker_devices_) {
    tracker->MyRunFrame();
  }

  vr::VREvent_t vrevent{};
  while (vr::VRServerDriverHost()->PollNextEvent(&vrevent,
                                                 sizeof(vr::VREvent_t))) {
    for (const auto &tracker : my_tracker_devices_) {
      tracker->MyProcessEvent(vrevent);
    }
  }
}

void MyDeviceProvider::EnterStandby() {}

void MyDeviceProvider::LeaveStandby() {}

void MyDeviceProvider::Cleanup() {

  for (auto &tracker : my_tracker_devices_) {
    tracker = nullptr;
  }
}
