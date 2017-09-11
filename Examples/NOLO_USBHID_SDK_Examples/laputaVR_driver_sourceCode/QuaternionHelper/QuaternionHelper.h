#ifndef _QUATERNION_HELPER_H_
#define _QUATERNION_HELPER_H_

#include <openvr_driver.h>
using namespace vr;

namespace QuaternionHelper
{
#define PI 3.141592f

	HmdQuaternion_t QuaternionMulti(HmdQuaternion_t q1, HmdQuaternion_t q2);

	float QuaternionMod(HmdQuaternion_t q1);

	HmdQuaternion_t GetQuaternionCorr(const HmdQuaternion_t q);

	// Convert LaputaVR coordinates to OpenVR's.
	void ConvertCoordinateToOpenVR(HmdQuaternion_t& qcorr);

	// Recenter Yaw
	HmdQuaternion_t QuaternionRecenter(HmdQuaternion_t& q, const HmdQuaternion_t qcorr);
}
#endif