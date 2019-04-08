#ifndef xSW12_h
#define xSW12_h

#include <xCore.h>


#define HTS221_DEVICE_ID		0xBC

#define HTS221_WHO_AM_I 		0x0F
#define HTS221_AV_CONF 			0x10

/* control register 1 */
#define HTS221_CTRL_REG1		 0x20
#define HTS221_CTRL_REG1_PD		 0x80
#define HTS221_CTRL_REG1_ONESHOT 0x00
#define HTS221_CTRL_REG1_1Hz	 0x01			
#define HTS221_CTRL_REG1_7Hz	 0x02
#define HTS221_CTRL_REG1_125Hz	 0x03


#define HTS221_CTRL_REG2		0x21
#define HTS221_CTRL_REG3		0x22
#define HTS221_STATUS_REG		0x27
#define HTS221_HUMIDITY_OUT_L	0x28
#define HTS221_HUMIDITY_OUT_H	0x29
#define HTS221_TEMP_OUT_L		0x2A
#define HTS221_TEMP_OUT_H		0x2B

#define HTS221_CALIB_START      0x30
/*
#define HTS221_CALIB_0		0x30
#define HTS221_CALIB_1			0x31
#define HTS221_CALIB_2			0x32
#define HTS221_CALIB_3			0x33
#define HTS221_CALIB_4			0x34
#define HTS221_CALIB_5			0x35
#define HTS221_CALIB_6			0x36
#define HTS221_CALIB_7			0x37
#define HTS221_CALIB_8			0x38
#define HTS221_CALIB_9			0x39
#define HTS221_CALIB_10			0x3A
#define HTS221_CALIB_11			0x3B
#define HTS221_CALIB_12			0x3C
#define HTS221_CALIB_13			0x3D
#define HTS221_CALIB_14			0x3E
#define HTS221_CALIB_15			0x3F
*/
#define HTS221_CALIB_END		0x3F

#define HTS221_AVGT_2   		0x00
#define HTS221_AVGT_4 			0x10
#define HTS221_AVGT_8 			0x20
#define HTS221_AVGT_16 			0x30
#define HTS221_AVGT_32 			0x40
#define HTS221_AVGT_64 			0x50
#define HTS221_AVGT_128 		0x60
#define HTS221_AVGT_256 		0x70

#define HTS221_AVGH_4   		0x00
#define HTS221_AVGH_8 			0x10
#define HTS221_AVGH_16 			0x20
#define HTS221_AVGH_32 			0x30
#define HTS221_AVGH_64 			0x40
#define HTS221_AVGH_128 		0x50
#define HTS221_AVGH_256 		0x60
#define HTS221_AVGH_512 		0x70


class xSW12: public xCoreClass
{
	public:
		xSW12(); 
		bool begin(void);
		bool getHumidity(float &val);
		bool getTempC(float &val);
		bool getTempF(float &val);
		void wakeup(void);
		void sleep(void);
		void enableAlert(void);

	private:
		bool readCalibrationData(void);
		bool readTemp(float &val);
		bool readHum(float &val);
		uint8_t H0_rH, H1_rH;
		uint16_t T0_degC, T1_degC;
		uint16_t H0_T0_OUT, H1_T0_OUT, T0_OUT, T1_OUT;

		uint8_t SW12_I2C_ADDR;

};

#endif
