#include "blynk.h"
//Blynk token kept in file listed in .gitignore
#include "AUTH_TOKEN.h"

const String event_prefix = "house/ivt/";

static const float tempLookup[1024] = {322.9453, 270.9837, 244.3900, 226.9534, 214.1624, 204.1503, 195.9738, 189.0937, 183.1740, 177.9923, 173.3940, 169.2675, 165.5300,
									   162.1182, 158.9827, 156.0845, 153.3919, 150.8793, 148.5253, 146.3121, 144.2246, 142.2500, 140.3774, 138.5972, 136.9012, 135.2822,
									   133.7338, 132.2504, 130.8270, 129.4592, 128.1430, 126.8748, 125.6513, 124.4698, 123.3274, 122.2219, 121.1510, 120.1126, 119.1050,
									   118.1265, 117.1754, 116.2504, 115.3501, 114.4732, 113.6187, 112.7854, 111.9724, 111.1787, 110.4034, 109.6458, 108.9051, 108.1805,
									   107.4714, 106.7772, 106.0973, 105.4311, 104.7780, 104.1377, 103.5095, 102.8932, 102.2881, 101.6941, 101.1105, 100.5372, 99.9737,
									   99.4198, 98.8751, 98.3393, 97.8121, 97.2933, 96.7826, 96.2798, 95.7846, 95.2968, 94.8161, 94.3425, 93.8756, 93.4153,
									   92.9615, 92.5138, 92.0722, 91.6366, 91.2066, 90.7823, 90.3634, 89.9498, 89.5414, 89.1381, 88.7397, 88.3461, 87.9571,
									   87.5728, 87.1929, 86.8174, 86.4462, 86.0791, 85.7161, 85.3571, 85.0020, 84.6507, 84.3032, 83.9593, 83.6189, 83.2821,
									   82.9487, 82.6186, 82.2918, 81.9683, 81.6479, 81.3305, 81.0163, 80.7049, 80.3965, 80.0910, 79.7883, 79.4883, 79.1910,
									   78.8963, 78.6043, 78.3148, 78.0278, 77.7433, 77.4612, 77.1815, 76.9041, 76.6290, 76.3561, 76.0855, 75.8171, 75.5507,
									   75.2865, 75.0244, 74.7643, 74.5062, 74.2501, 73.9959, 73.7436, 73.4932, 73.2446, 72.9979, 72.7529, 72.5097, 72.2683,
									   72.0285, 71.7905, 71.5541, 71.3193, 71.0861, 70.8546, 70.6245, 70.3961, 70.1691, 69.9436, 69.7196, 69.4971, 69.2760,
									   69.0563, 68.8380, 68.6210, 68.4055, 68.1912, 67.9783, 67.7667, 67.5563, 67.3473, 67.1394, 66.9328, 66.7274, 66.5233,
									   66.3203, 66.1184, 65.9177, 65.7182, 65.5198, 65.3225, 65.1263, 64.9311, 64.7371, 64.5441, 64.3521, 64.1612, 63.9713,
									   63.7824, 63.5945, 63.4075, 63.2216, 63.0366, 62.8525, 62.6694, 62.4872, 62.3059, 62.1255, 61.9460, 61.7674, 61.5897,
									   61.4128, 61.2368, 61.0616, 60.8872, 60.7137, 60.5410, 60.3691, 60.1980, 60.0277, 59.8581, 59.6894, 59.5214, 59.3541,
									   59.1876, 59.0218, 58.8568, 58.6925, 58.5289, 58.3660, 58.2038, 58.0423, 57.8815, 57.7214, 57.5619, 57.4031, 57.2450,
									   57.0875, 56.9306, 56.7744, 56.6189, 56.4639, 56.3096, 56.1559, 56.0028, 55.8503, 55.6983, 55.5470, 55.3963, 55.2461,
									   55.0965, 54.9475, 54.7990, 54.6511, 54.5037, 54.3569, 54.2106, 54.0649, 53.9197, 53.7750, 53.6308, 53.4872, 53.3440,
									   53.2014, 53.0593, 52.9176, 52.7765, 52.6358, 52.4956, 52.3559, 52.2167, 52.0779, 51.9396, 51.8018, 51.6644, 51.5275,
									   51.3910, 51.2550, 51.1194, 50.9842, 50.8495, 50.7152, 50.5813, 50.4479, 50.3148, 50.1822, 50.0500, 49.9182, 49.7868,
									   49.6558, 49.5252, 49.3950, 49.2652, 49.1357, 49.0067, 48.8780, 48.7497, 48.6218, 48.4943, 48.3671, 48.2403, 48.1138,
									   47.9877, 47.8620, 47.7366, 47.6115, 47.4868, 47.3625, 47.2385, 47.1148, 46.9914, 46.8684, 46.7458, 46.6234, 46.5014,
									   46.3797, 46.2583, 46.1372, 46.0164, 45.8960, 45.7758, 45.6560, 45.5365, 45.4172, 45.2983, 45.1797, 45.0613, 44.9433,
									   44.8255, 44.7080, 44.5908, 44.4739, 44.3573, 44.2410, 44.1249, 44.0091, 43.8936, 43.7783, 43.6633, 43.5486, 43.4341,
									   43.3199, 43.2059, 43.0923, 42.9788, 42.8656, 42.7527, 42.6400, 42.5276, 42.4154, 42.3034, 42.1917, 42.0803, 41.9690,
									   41.8580, 41.7473, 41.6367, 41.5264, 41.4164, 41.3065, 41.1969, 41.0875, 40.9783, 40.8694, 40.7606, 40.6521, 40.5438,
									   40.4357, 40.3278, 40.2202, 40.1127, 40.0054, 39.8984, 39.7915, 39.6849, 39.5784, 39.4722, 39.3661, 39.2603, 39.1546,
									   39.0491, 38.9438, 38.8387, 38.7338, 38.6291, 38.5246, 38.4202, 38.3161, 38.2121, 38.1083, 38.0047, 37.9012, 37.7979,
									   37.6948, 37.5919, 37.4892, 37.3866, 37.2842, 37.1819, 37.0798, 36.9779, 36.8762, 36.7746, 36.6731, 36.5719, 36.4707,
									   36.3698, 36.2690, 36.1683, 36.0679, 35.9675, 35.8673, 35.7673, 35.6674, 35.5677, 35.4681, 35.3686, 35.2693, 35.1702,
									   35.0711, 34.9723, 34.8735, 34.7749, 34.6765, 34.5781, 34.4799, 34.3819, 34.2840, 34.1862, 34.0885, 33.9910, 33.8936,
									   33.7963, 33.6992, 33.6021, 33.5052, 33.4085, 33.3118, 33.2153, 33.1189, 33.0226, 32.9264, 32.8304, 32.7344, 32.6386,
									   32.5429, 32.4473, 32.3518, 32.2564, 32.1612, 32.0660, 31.9710, 31.8761, 31.7812, 31.6865, 31.5919, 31.4974, 31.4030,
									   31.3087, 31.2145, 31.1204, 31.0264, 30.9325, 30.8387, 30.7449, 30.6513, 30.5578, 30.4644, 30.3711, 30.2778, 30.1847,
									   30.0916, 29.9986, 29.9058, 29.8130, 29.7203, 29.6277, 29.5351, 29.4427, 29.3503, 29.2580, 29.1658, 29.0737, 28.9817,
									   28.8897, 28.7979, 28.7061, 28.6143, 28.5227, 28.4311, 28.3396, 28.2482, 28.1569, 28.0656, 27.9744, 27.8833, 27.7922,
									   27.7012, 27.6103, 27.5195, 27.4287, 27.3379, 27.2473, 27.1567, 27.0662, 26.9757, 26.8853, 26.7950, 26.7047, 26.6145,
									   26.5243, 26.4342, 26.3442, 26.2542, 26.1643, 26.0744, 25.9846, 25.8948, 25.8051, 25.7155, 25.6259, 25.5363, 25.4468,
									   25.3574, 25.2680, 25.1786, 25.0893, 25.0000, 24.9108, 24.8217, 24.7325, 24.6435, 24.5544, 24.4654, 24.3765, 24.2876,
									   24.1987, 24.1099, 24.0211, 23.9323, 23.8436, 23.7550, 23.6663, 23.5777, 23.4891, 23.4006, 23.3121, 23.2236, 23.1352,
									   23.0468, 22.9584, 22.8701, 22.7818, 22.6935, 22.6052, 22.5170, 22.4288, 22.3406, 22.2525, 22.1643, 22.0762, 21.9882,
									   21.9001, 21.8121, 21.7241, 21.6361, 21.5481, 21.4601, 21.3722, 21.2843, 21.1964, 21.1085, 21.0206, 20.9328, 20.8449,
									   20.7571, 20.6693, 20.5815, 20.4937, 20.4059, 20.3181, 20.2304, 20.1426, 20.0549, 19.9672, 19.8794, 19.7917, 19.7040,
									   19.6163, 19.5286, 19.4409, 19.3532, 19.2655, 19.1778, 19.0901, 19.0024, 18.9147, 18.8270, 18.7392, 18.6515, 18.5638,
									   18.4761, 18.3884, 18.3007, 18.2129, 18.1252, 18.0375, 17.9497, 17.8619, 17.7742, 17.6864, 17.5986, 17.5108, 17.4229,
									   17.3351, 17.2473, 17.1594, 17.0715, 16.9836, 16.8957, 16.8078, 16.7198, 16.6318, 16.5439, 16.4558, 16.3678, 16.2798,
									   16.1917, 16.1036, 16.0155, 15.9273, 15.8391, 15.7509, 15.6627, 15.5744, 15.4861, 15.3978, 15.3095, 15.2211, 15.1327,
									   15.0443, 14.9558, 14.8673, 14.7787, 14.6901, 14.6015, 14.5129, 14.4242, 14.3354, 14.2467, 14.1579, 14.0690, 13.9801,
									   13.8912, 13.8022, 13.7132, 13.6241, 13.5350, 13.4458, 13.3566, 13.2673, 13.1780, 13.0887, 12.9992, 12.9098, 12.8203,
									   12.7307, 12.6411, 12.5514, 12.4617, 12.3719, 12.2820, 12.1921, 12.1021, 12.0121, 11.9220, 11.8319, 11.7417, 11.6514,
									   11.5610, 11.4706, 11.3801, 11.2896, 11.1990, 11.1083, 11.0176, 10.9267, 10.8358, 10.7449, 10.6538, 10.5627, 10.4715,
									   10.3803, 10.2889, 10.1975, 10.1060, 10.0144, 9.9227, 9.8310, 9.7391, 9.6472, 9.5552, 9.4631, 9.3709, 9.2787,
									   9.1863, 9.0939, 9.0013, 8.9087, 8.8160, 8.7231, 8.6302, 8.5372, 8.4441, 8.3509, 8.2575, 8.1641, 8.0706,
									   7.9770, 7.8832, 7.7894, 7.6955, 7.6014, 7.5073, 7.4130, 7.3186, 7.2241, 7.1295, 7.0348, 6.9399, 6.8449,
									   6.7499, 6.6547, 6.5593, 6.4639, 6.3683, 6.2726, 6.1768, 6.0808, 5.9847, 5.8885, 5.7922, 5.6957, 5.5991,
									   5.5023, 5.4054, 5.3084, 5.2112, 5.1139, 5.0164, 4.9188, 4.8211, 4.7232, 4.6251, 4.5269, 4.4286, 4.3301,
									   4.2314, 4.1326, 4.0336, 3.9345, 3.8352, 3.7357, 3.6361, 3.5363, 3.4363, 3.3362, 3.2359, 3.1354, 3.0348,
									   2.9339, 2.8329, 2.7317, 2.6304, 2.5288, 2.4271, 2.3251, 2.2230, 2.1207, 2.0182, 1.9155, 1.8126, 1.7095,
									   1.6062, 1.5027, 1.3990, 1.2951, 1.1910, 1.0867, 0.9821, 0.8774, 0.7724, 0.6672, 0.5618, 0.4561, 0.3503,
									   0.2442, 0.1378, 0.0313, -0.0755, -0.1826, -0.2898, -0.3974, -0.5051, -0.6131, -0.7214, -0.8299, -0.9387, -1.0477,
									   -1.1570, -1.2665, -1.3764, -1.4865, -1.5968, -1.7074, -1.8183, -1.9295, -2.0410, -2.1528, -2.2648, -2.3771, -2.4898,
									   -2.6027, -2.7159, -2.8295, -2.9433, -3.0575, -3.1719, -3.2867, -3.4018, -3.5172, -3.6330, -3.7491, -3.8655, -3.9823,
									   -4.0994, -4.2168, -4.3346, -4.4527, -4.5712, -4.6901, -4.8093, -4.9289, -5.0489, -5.1692, -5.2900, -5.4111, -5.5326,
									   -5.6545, -5.7768, -5.8995, -6.0226, -6.1461, -6.2700, -6.3944, -6.5192, -6.6444, -6.7700, -6.8961, -7.0226, -7.1496,
									   -7.2771, -7.4050, -7.5334, -7.6622, -7.7916, -7.9214, -8.0517, -8.1825, -8.3138, -8.4456, -8.5780, -8.7108, -8.8442,
									   -8.9781, -9.1126, -9.2476, -9.3832, -9.5193, -9.6560, -9.7933, -9.9311, -10.0696, -10.2087, -10.3483, -10.4886, -10.6295,
									   -10.7711, -10.9132, -11.0561, -11.1996, -11.3437, -11.4886, -11.6341, -11.7803, -11.9272, -12.0749, -12.2232, -12.3723, -12.5222,
									   -12.6728, -12.8242, -12.9763, -13.1293, -13.2830, -13.4376, -13.5930, -13.7492, -13.9063, -14.0642, -14.2231, -14.3828, -14.5434,
									   -14.7050, -14.8675, -15.0309, -15.1953, -15.3607, -15.5270, -15.6944, -15.8628, -16.0323, -16.2028, -16.3745, -16.5472, -16.7210,
									   -16.8960, -17.0721, -17.2494, -17.4279, -17.6077, -17.7887, -17.9709, -18.1545, -18.3393, -18.5255, -18.7131, -18.9020, -19.0924,
									   -19.2842, -19.4775, -19.6723, -19.8686, -20.0665, -20.2659, -20.4671, -20.6698, -20.8743, -21.0805, -21.2885, -21.4982, -21.7099,
									   -21.9234, -22.1388, -22.3562, -22.5757, -22.7972, -23.0208, -23.2466, -23.4746, -23.7049, -23.9375, -24.1725, -24.4100, -24.6499,
									   -24.8924, -25.1376, -25.3855, -25.6361, -25.8897, -26.1461, -26.4056, -26.6682, -26.9340, -27.2030, -27.4755, -27.7515, -28.0310,
									   -28.3143, -28.6014, -28.8925, -29.1876, -29.4870, -29.7907, -30.0989, -30.4118, -30.7296, -31.0523, -31.3803, -31.7136, -32.0526,
									   -32.3974, -32.7482, -33.1054, -33.4691, -33.8397, -34.2175, -34.6027, -34.9958, -35.3971, -35.8069, -36.2258, -36.6542, -37.0925,
									   -37.5413, -38.0012, -38.4729, -38.9569, -39.4541, -39.9653, -40.4914, -41.0334, -41.5923, -42.1695, -42.7662, -43.3839, -44.0245,
									   -44.6898, -45.3820, -46.1036, -46.8575, -47.6470, -48.4760, -49.3490, -50.2714, -51.2498, -52.2920, -53.4077, -54.6091, -55.9118,
									   -57.3360, -58.9090, -60.6685, -62.6693, -64.9950, -67.7838, -71.2897, -76.0689, -83.8330, -273.1500};

const int TEMP_RELAY_OUTPUT_PIN = D4;
const int SPI_CS_PIN = A2;
const byte SPI_ADDRESS = 0x11;

enum HeaterState
{
	HEATERSTATE_DISABLED = -1,
	HEATERSTATE_STANDARD = 0,
	HEATERSTATE_HEATING = 1,
	HEATERSTATE_FORCED_HEATING = 2,
	HEATERSTATE_UNKNOWN = 99
};

static inline char *stringFromHeaterState(enum HeaterState heaterState)
{
	switch (heaterState)
	{
	case HEATERSTATE_STANDARD:
		return (char *)"standard";
	case HEATERSTATE_DISABLED:
		return (char *)"disabled";
	case HEATERSTATE_HEATING:
		return (char *)"heating";
	case HEATERSTATE_FORCED_HEATING:
		return (char *)"forced heating";
	case HEATERSTATE_UNKNOWN:
		return (char *)"unknown";
	default:
		return (char *)"unknown";
	}
}

// Can bus on pins D1 & D2
CANChannel can(CAN_D1_D2);
BlynkTimer timer;
enum HeaterState heaterState = HEATERSTATE_UNKNOWN;
String heaterStateString = stringFromHeaterState(HEATERSTATE_UNKNOWN);

float t1_temp = 0.0;
float t2_temp = 0.0;
float t3_temp = 0.0;
float t8_temp = 0.0;
float t9_temp = 0.0;
int heater_fan = 0;
int compressor = 0;
int immersionHeater = 0;
float current_outdoor_temp;
float current_indoor_temp;
float desired_indoor_temp;
float desired_low_temp_offset; // = 0.40;
float desired_high_temp_offset; // = 0.20;
float forced_heating_offset; //= 0.80;
String current_indoor_temp_string;

//Event consumer, consuming temp events from another particle device (IndoorClimate)
void updateTemperature(const char *event, const char *data)
{
	String tempEvent = String(event).trim();
	String tempData = String(data).trim();

	if (tempEvent.indexOf("temperature") > -1)
	{
		float _temp = tempData.toFloat();
		if (_temp > 0)
		{
			current_indoor_temp = _temp;
			current_indoor_temp_string = tempData;
		}
	}
}

BLYNK_CONNECTED()
{
	//After a disconnect, make sure blynk and photon are in sync
	Blynk.syncVirtual(V95);
	Blynk.syncVirtual(V96);
	Blynk.syncVirtual(V97);
	Blynk.syncVirtual(V98);
}

BLYNK_WRITE(V95)
{
	if (forced_heating_offset == param.asFloat())
	{
		//No change, just a reconnect event
		return;
	}

	forced_heating_offset = param.asFloat();
	Particle.publish(event_prefix + "indoor/forced_heating_offset", param.asString(), PRIVATE);
}

BLYNK_WRITE(V96)
{
	if (desired_low_temp_offset == param.asFloat())
	{
		//No change, just a reconnect event
		return;
	}

	desired_low_temp_offset = param.asFloat();
	Particle.publish(event_prefix + "indoor/desired_low_offset", param.asString(), PRIVATE);
}

BLYNK_WRITE(V97)
{
	if (desired_high_temp_offset == param.asFloat())
	{
		//No change, just a reconnect event
		return;
	}

	desired_high_temp_offset = param.asFloat();
	Particle.publish(event_prefix + "indoor/desired_high_offset", param.asString(), PRIVATE);
}

BLYNK_WRITE(V98)
{
	if (desired_indoor_temp == param.asFloat())
	{
		//No change, just a reconnect event
		return;
	}

	desired_indoor_temp = param.asFloat();
	Particle.publish(event_prefix + "indoor/desired_temperature", param.asString(), PRIVATE);
}

void setup()
{
	Particle.publish(event_prefix + "setup", "starting", PRIVATE);
	Particle.function("standardHeating", standardHeating);
	Particle.function("disableHeating", disableHeating);
	Particle.function("setOutdoorTemp", setOutdoorTemp);
	Particle.variable("heatingState", heaterStateString);
	Particle.variable("indoor_temp", current_indoor_temp_string);

	delay(5000);   // Allow board to settle
	Time.zone(+1); // Set to correct time zone

	can.begin(125000);
	if (can.errorStatus() == CAN_BUS_OFF)
	{
		Particle.publish(event_prefix + "error", "Not properly connected to CAN bus", PRIVATE);
	}

	Particle.subscribe("house/climate", updateTemperature, MY_DEVICES);

	Blynk.begin(BLYNK_AUTH_TOKEN);
	timer.setInterval(20000L, publishSensors); //20 seconds
	timer.setInterval(120000L, operateHeater); //2 mins

	//Initialize the relay pin and make sure it is low
	pinMode(TEMP_RELAY_OUTPUT_PIN, OUTPUT);
	pinMode(SPI_CS_PIN, OUTPUT);
	// Initiate SPI
	SPI.begin();
	heaterStandard(true);
}

void digitalPotWrite(int value)
{
	digitalWrite(SPI_CS_PIN, LOW);
	SPI.transfer(SPI_ADDRESS);
	SPI.transfer(value);
	digitalWrite(SPI_CS_PIN, HIGH);
}

void operateHeater()
{
	if (forcedHeatingRequired())
	{
		//Lets heat that house with force
		heaterOnForce();
	}
	else if (!isHeatingDisabled() && isHeaterSupposedToBeOn())
	{
		//Lets heat that house
		heaterOn();
	}
	else if (!isHeatingDisabled())
	{
		//Heating is not disabled, lets use standard heating
		heaterStandard(true);
	}
}

bool forcedHeatingRequired()
{
	if (current_indoor_temp < (desired_indoor_temp - forced_heating_offset))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isHeaterSupposedToBeOn()
{
	//If heater is not on, only start after temp is less than desired offset
	if (!isHeaterOn() && current_indoor_temp < (desired_indoor_temp - desired_low_temp_offset))
	{
		return true;
		
	}
	//If heater is on, run it until indoor temp reaches desired offset
	else if (isHeaterOn() && current_indoor_temp < (desired_indoor_temp - desired_high_temp_offset))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isHeaterOn()
{
	return heaterState == HEATERSTATE_HEATING;
}
bool isHeaterStandard()
{
	return heaterState == HEATERSTATE_STANDARD;
}
bool isHeatingDisabled()
{
	return heaterState == HEATERSTATE_DISABLED;
}
bool isHeatingForced()
{
	return heaterState == HEATERSTATE_FORCED_HEATING;
}

void heaterOnForce()
{
	//If heater already is forced, then skip
	if (!isHeatingForced())
	{
		//turnOnHeater (HEATING) = -10 grader
		digitalWrite(TEMP_RELAY_OUTPUT_PIN, HIGH);
		digitalPotWrite(10);
		heaterState = HEATERSTATE_FORCED_HEATING;
		heaterStateString = stringFromHeaterState(HEATERSTATE_FORCED_HEATING);
		String eventString = "Heater forced, current temp: " + floatToString(current_indoor_temp) +
							 ", desired temp: " + floatToString(desired_indoor_temp);
		Particle.publish(event_prefix + "info", eventString, PRIVATE);
	}
}

void heaterOn()
{
	//If heater already is on, then skip
	if (!isHeaterOn())
	{
		//turnOnHeater (HEATING) = -10 grader
		digitalWrite(TEMP_RELAY_OUTPUT_PIN, HIGH);
		digitalPotWrite(10);
		heaterState = HEATERSTATE_HEATING;
		heaterStateString = stringFromHeaterState(HEATERSTATE_HEATING);
		String eventString = "Heater on, current temp: " + floatToString(current_indoor_temp) +
							 ", desired temp: " + floatToString(desired_indoor_temp);
		Particle.publish(event_prefix + "info", eventString, PRIVATE);
	}
}

void heaterStandard(bool force)
{
	//If heater already is standard, or heater is on - then ignore command
	//unless force is used
	if (!isHeaterStandard() && (!isHeaterOn() || force))
	{
		//standardHeating (STANDARD) = +6 grader
		digitalWrite(TEMP_RELAY_OUTPUT_PIN, HIGH);
		digitalPotWrite(0xFF);
		heaterState = HEATERSTATE_STANDARD;
		heaterStateString = stringFromHeaterState(HEATERSTATE_STANDARD);
		String eventString = "Heater standard, current temp: " + floatToString(current_indoor_temp) +
							 ", desired temp: " + floatToString(desired_indoor_temp);
		Particle.publish(event_prefix + "info", eventString, PRIVATE);
	}
}

void heaterDisabled()
{
	//If heating is forced, or already disabled - then don't disable
	if (!isHeatingForced() && !isHeatingDisabled())
	{
		//disableHeater (DISABLED) = +15 grader
		digitalWrite(TEMP_RELAY_OUTPUT_PIN, LOW);
		digitalPotWrite(120);
		heaterState = HEATERSTATE_DISABLED;
		heaterStateString = stringFromHeaterState(HEATERSTATE_DISABLED);
		String eventString = "Heater disabled, current temp: " + floatToString(current_indoor_temp) +
							 ", desired temp: " + floatToString(desired_indoor_temp);
		Particle.publish(event_prefix + "info", eventString, PRIVATE);
	}
}

//Particle functions
/////////////////////////////////////////////////////////
int standardHeating(String action)
{
	heaterStandard(false);
	return 1;
}

//Particle function
int disableHeating(String action)
{
	heaterDisabled();
	return 1;
}

int setOutdoorTemp(String temp)
{
	String _t = String(temp).trim();

	float _temp = _t.toFloat();
	if (_temp > 0)
	{
		current_outdoor_temp = _temp;
	}
	return 1;
}

String floatToString(float floatValue)
{
	char val[16];
	sprintf(val, "%.2f", floatValue);
	return String(val);
}
/////////////////////////////////////////////////////////

void publishSensors()
{
	//Floor heating water temp
	Blynk.virtualWrite(V99, t1_temp);
	//Outdoor temp
	Blynk.virtualWrite(V80, t2_temp);
	//Hot water
	Blynk.virtualWrite(V100, t3_temp);
	//Carrier Out
	Blynk.virtualWrite(V101, t8_temp);
	//Carrier In
	Blynk.virtualWrite(V102, t9_temp);
	//Fan or compressor
	//Blynk.virtualWrite(V103, (compressor == 1 || heater_fan == 1) ? 1 : 0);
	Blynk.virtualWrite(V103, compressor);
	//Immersion heater
	Blynk.virtualWrite(V104, immersionHeater);
	//Heater state
	Blynk.virtualWrite(V105, heaterState);
	//Heater state as string
	Blynk.virtualWrite(V108, heaterStateString);
	//Current outdoor temperature
	Blynk.virtualWrite(V109, current_outdoor_temp);

	String json = "{\"compressor_on\": " + String(compressor) + ", " +
					"\"immersion_heater_on\": " + String(immersionHeater) + ", " +
					"\"fan_on\": " + String(heater_fan) + ", " +
					"\"heater_state\": " + String(heaterState) + ", " +
					"\"floor_water_temp\": " + String(t1_temp) + ", " +
					"\"outdoor_temp\": " + String(current_outdoor_temp) + ", " +
					"\"indoor_temp\": " + String(current_indoor_temp) + " }";

	Particle.publish(event_prefix + "data", json, PRIVATE);
}

void loop()
{
	Blynk.run();
	timer.run();

	if (can.available() > 0)
	{
		float temp = 0.0;
		CANMessage message;
		if (can.receive(message))
		{
			switch (message.id)
			{
			case 268435472:
				//10000010, EP-Ai1, T1, Floor heating water temp
				temp = lookupTemp(message.data);
				if (temp < 100.0)
				{
					t1_temp = temp;
				}
				break;
			case 268451856:
				//10004010, EP-Ai2, T2, Outdoor
				t2_temp = lookupTemp(message.data);
				break;
			case 268468240:
				//10008010, EP-Ai3, T3, Hot water
				temp = lookupTemp(message.data);
				if (temp < 100.0)
				{
					t3_temp = temp;
				}
				break;
			case 268451841:
				//10004001, VP-Ai2, T8, Heat carrier out
				temp = lookupTemp(message.data);
				if (temp < 100.0)
				{
					t8_temp = temp;
				}
				break;
			case 268468225:
				//10008001, VP-Ai3, T9, Heat carrier in
				temp = lookupTemp(message.data);
				if (temp < 100.0)
				{
					t9_temp = temp;
				}
				break;
			case 134397953:
				//802C001, VP-Do2, heater fan
				heater_fan = (getDecimalValue(message.data[0], message.data[1]) == 0) ? 0 : 1;
				break;
			case 268943408:
				//1007C030, Immersion heater
				immersionHeater = (getDecimalValue(message.data[0], message.data[1]) == 0) ? 0 : 1;
				break;
			case 134447105:
				//8038001, VP-Do5, Compressor
				compressor = (getDecimalValue(message.data[0], message.data[1]) == 0) ? 0 : 1;
				break;
			}
		}
	}
}

float lookupTemp(uint8_t data[8])
{
	int adVal = getDecimalValue(data[0], data[1]);
	if (adVal > 1023)
	{
		adVal = 1023;
	}
	return tempLookup[adVal];
}

//Get frame and return Dec value
unsigned int getDecimalValue(uint8_t val1, uint8_t val2)
{
	String temp = String(val1, HEX) + String(val2, HEX);
	return hexToDec(temp);
}

unsigned int hexToDec(String hexString)
{
	unsigned int decValue = 0;
	int nextInt;
	for (unsigned int i = 0; i < hexString.length(); i++)
	{
		nextInt = int(hexString.charAt(i));
		if (nextInt >= 48 && nextInt <= 57)
			nextInt = map(nextInt, 48, 57, 0, 9);
		if (nextInt >= 65 && nextInt <= 70)
			nextInt = map(nextInt, 65, 70, 10, 15);
		if (nextInt >= 97 && nextInt <= 102)
			nextInt = map(nextInt, 97, 102, 10, 15);
		nextInt = constrain(nextInt, 0, 15);
		decValue = (decValue * 16) + nextInt;
	}
	return decValue;
}
