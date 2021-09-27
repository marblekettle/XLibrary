#include <windows.h>
#include <iostream>

void CALLBACK	midicb(HMIDIIN handle, UINT msg, DWORD inst, DWORD p1, DWORD p2)
{
	if (msg == MIM_DATA)
	{
		std::cout << "Type: " << (int)((p1 >> 4) & 7) << \
			" Channel: " << (int)(p1 & 15) << \
			"\nPitch: " << (int)((p1 >> 8) & 255) << \
			" Vel: " << (int)((p1 >> 16) & 255) << std::endl;
	}
	if (msg == MIM_CLOSE)
	{
		std::cout << "Device Closed" << std::endl;
	}
}

int		main(int ac, char **av)
{
	UINT devcount = midiOutGetNumDevs();

	std::cout << devcount << std::endl;
	for (UINT i = 0; i < devcount; i++)
	{
		MIDIOUTCAPS	dev;
		MMRESULT is_ok = midiOutGetDevCaps(i, &dev, sizeof(MIDIOUTCAPS));
		std::cout << dev.szPname << std::endl;
		HMIDIOUT	midi;
		midiOutOpen(&midi, i, 0, 0, CALLBACK_NULL);
		midiOutShortMsg(midi, 0x404090);
		Sleep(1000);
		midiOutShortMsg(midi, 0x404080);
		midiOutClose(midi);
	}

	UINT idevcount = midiInGetNumDevs();
	std::cout << idevcount << std::endl;
	for (UINT i = 0; i < idevcount; i++)
	{
		MIDIINCAPS	dev;
		MMRESULT is_ok = midiInGetDevCaps(i, &dev, sizeof(MIDIOUTCAPS));
		std::cout << dev.szPname << std::endl;
	}
	HMIDIIN	midi;
	MMRESULT is_ok = midiInOpen(&midi, 1, (DWORD_PTR)midicb, 0, CALLBACK_FUNCTION);
	if (is_ok)
		std::cout << is_ok << std::endl;
	midiInStart(midi);
	int d;
	std::cin >> d; 
	midiInClose(midi);
	return (0);
}