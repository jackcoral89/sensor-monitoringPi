using System.Device.I2c;
using Iot.Device.Bmxx80;
using Iot.Device.Bmxx80.ReadResult;

class Program
{
	static async Task Main()
	{
		const int busId = 1;
		var i2cSettings = new I2cConnectionSettings(busId, Bme680.DefaultI2cAddress);
		using I2cDevice i2cDevice = I2cDevice.Create(i2cSettings);
		using var bme = new Bme680(i2cDevice);

		while (true)
		{
			Bme680ReadResult results = await bme.ReadAsync();

			Console.WriteLine($"Temp: {results.Temperature}");
			Console.WriteLine($"Hum: {results.Humidity}");
			Console.WriteLine($"Press: {results.Pressure}");
			Console.WriteLine($"Gas: {results.GasResistance}");
			Thread.Sleep(2000);
		}

	}
}

