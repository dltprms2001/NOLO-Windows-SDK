#include "QuaternionHelper.h"
#include <math.h>

namespace QuaternionHelper
{
    HmdQuaternion_t QuaternionMulti(HmdQuaternion_t q1, HmdQuaternion_t q2)
    {
        HmdQuaternion_t q;
		q.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
		q.x = q1.w * q2.x + q1.x * q2.w - q1.y * q2.z + q1.z * q2.y;
		q.y = q1.w * q2.y + q1.y * q2.w + q1.x * q2.z - q1.z * q2.x;
		q.z = q1.w * q2.z + q1.z * q2.w + q1.y * q2.x - q1.x * q2.y;
		return q;
    }

	float QuaternionMod(HmdQuaternion_t q1)
    {
        float mod;
		mod = (float)(q1.w * q1.w + q1.x * q1.x +
			q1.y * q1.y + q1.z * q1.z);
		mod = (float)sqrt(mod);
		return mod;
    }

    HmdQuaternion_t GetQuaternionCorr(const HmdQuaternion_t q)
    {
        HmdQuaternion_t qcorr;

		qcorr.w = q.w;
		qcorr.z = -q.z;
		qcorr.x = 0;
		qcorr.y = 0;

		double mod = QuaternionMod(qcorr);

		qcorr.w = q.w / mod;
		qcorr.z = -q.z / mod;

		ConvertCoordinateToOpenVR(qcorr);
		return qcorr;
    }

	void ConvertCoordinateToOpenVR(HmdQuaternion_t& qcorr)
	{
		HmdQuaternion_t t_qcorr = qcorr;
		qcorr.w = t_qcorr.w;
		qcorr.x = t_qcorr.y;
		qcorr.y = t_qcorr.z;
		qcorr.z = t_qcorr.x;
	}

	// Recenter Yaw
	HmdQuaternion_t QuaternionRecenter(HmdQuaternion_t& q, const HmdQuaternion_t qcorr)
    {
        return QuaternionMulti(q, qcorr);
    }
}