#include <fstream>

class Settings
{
private:
	int Width = 800;
	int Height = 600;
	int Volume = 100;
	bool Fullscreen = false;
public:

	/*
	Settings()
	{
		std::ifstream SettingsFile("settings.ini");
		if (myfile.is_open())
		{
			int Width = 800;
			int Height = 600;
			int Volume = 100;
			bool Fullscreen = false;
		}
	};
	*/

	void SetResolution(short NewWidth, short NewHeight)
	{
		Width = NewWidth;
		Height = NewHeight;
	};

	void SetVolume(short NewVolume)
	{
		Volume = NewVolume;
	};

	void SetFullscreen(bool NewFullscreen)
	{
		Fullscreen = NewFullscreen;
	};

	short GetWidth()
	{
		return Width;
	};

	short GetHeight()
	{
		return Height;
	};

	short GetVolume()
	{
		return Volume;
	};

	bool GetFullscreenMode()
	{
		return Fullscreen;
	};
};