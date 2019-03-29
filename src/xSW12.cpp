#include <xSW12.h>
#include <inttypes.h>

/*					public					*/

xSW12::xSW12()
{
	addr = HTS221_I2C_ADDR;
	temperature = 0.0;
	humidity = 0.0;
}

bool xSW12::begin(void)
{
	uint8_t device_id = xCore.read8(addr, HTS221_WHO_AM_I);
	if (device_id != HTS221_DEVICE_ID) return false;

	uint8_t data = HTS221_CTRL_REG1_PD | HTS221_CTRL_REG1_1Hz;
	xCore.write8(addr, HTS221_CTRL_REG1, data);
	readCalibrationData();

	return true;
}

float xSW12::getTempC(void)
{
	readTemp();
	return temperature;
}

float xSW12::getTempF(void)
{

}

float xSW12::getHumidity(void)
{
	readHum();
	return humidity;
}

/*					private					*/

bool xSW12::readCalibrationData(void)
{
	uint8_t data8;
	uint16_t data16;
	for (int i = HTS221_CALIB_START; i <= HTS221_CALIB_END; i++) {
		if (i==0x34 | i==0x38 | i==0x39) continue;
		data8 = xCore.read8(addr, i);
		switch (i) {
			case HTS221_CALIB_START:
			H0_rH = data8;
			break;
			case HTS221_CALIB_START + 1:
			H1_rH = data8;
			break;
			case HTS221_CALIB_START + 2:
			T0_degC = data8;
			break;
			case HTS221_CALIB_START + 3:
			T1_degC = data8;
			break;
			case HTS221_CALIB_START + 5:
			data16 = T0_degC;
			T0_degC = (data8 & 0x03) << 8;
			T0_degC |= data16;
            data16 = T1_degC;
            T1_degC = ((data8 & 0x0C) >> 2) << 8;
            T1_degC |= data16;
            case HTS221_CALIB_START + 6:
            H0_T0_OUT = data8;
            break;
            case HTS221_CALIB_START + 7:
            H0_T0_OUT |= data8 << 8; 
            break;
            case HTS221_CALIB_START + 10:
            H1_T0_OUT = data8;
            break;
            case HTS221_CALIB_START + 11:
            H1_T0_OUT |= data8 << 8;
            break;
            case HTS221_CALIB_START + 12:
            T0_OUT = data8;
            break;
            case HTS221_CALIB_START + 13:
            T0_OUT |= data8 << 8;
            break;
            case HTS221_CALIB_START + 14:
            T1_OUT = data8;
            break;
            case HTS221_CALIB_START + 15:
            T1_OUT |= data8 << 8;
            break;
            default: return false; break;
		}
	}
	return true;
}

void xSW12::readTemp(void)
{
	if (xCore.read8(addr, HTS221_STATUS_REG) & 0x01) {

		uint16_t t_degC = ((int16_t)T1_degC - (int16_t)T0_degC)/8.0;
		int16_t t_out = (int16_t)T1_OUT - (int16_t)T0_OUT;

		int16_t temp_raw = ((uint8_t)xCore.read8(addr, HTS221_TEMP_OUT_H) << 8);
		temp_raw |= (uint8_t)xCore.read8(addr, HTS221_TEMP_OUT_L);

		temperature = (float)(((float)(t_degC)*((float)temp_raw - (float)T0_OUT))/(float)t_out) + (float)T0_degC/8.0;
	}
}

void xSW12::readHum(void)
{
	if (xCore.read8(addr, HTS221_STATUS_REG) & 0x02) {

		uint16_t hum_rh = ((int16_t)H1_rH - (int16_t)H0_rH)/2.0;
		int16_t hum_out = H1_T0_OUT - H0_T0_OUT;

		int16_t hum_raw = ((uint8_t)xCore.read8(addr, HTS221_HUMIDITY_OUT_H) << 8);
		hum_raw |= (uint8_t)xCore.read8(addr, HTS221_HUMIDITY_OUT_L);

		humidity = (float)(((float)(hum_rh)*((float)hum_raw - (float)H0_T0_OUT))/(float)hum_out) + (float)H0_rH/2.0;
	}
}
