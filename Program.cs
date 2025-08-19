using System.Device.Gpio;
using System.Device.I2c;
using Iot.Device.Bmxx80;
using Iot.Device.GrovePiDevice;
using Iot.Device.GrovePiDevice.Models;
using Iot.Device.GrovePiDevice.Sensors;
using UnitsNet;

class Program
{
	static void Main()
	{
		Console.WriteLine("Hello!");
		// const int busId = 1;
		// var i2cSettings = new I2cConnectionSettings(busId, Bme280.DefaultI2cAddress);
		// using I2cDevice i2cDevice = I2cDevice.Create(i2cSettings);
		// using var bme80 = new Bme280(i2cDevice)
		// {
		// 	// set higher sampling
		// 	TemperatureSampling = Sampling.LowPower,
		// 	PressureSampling = Sampling.UltraHighResolution,
		// 	HumiditySampling = Sampling.Standard,

		// };

	}
}

