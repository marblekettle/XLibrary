#include "XS_Midi.hpp"

int		main(void)
{
	XS_Midi midi(1);

	midi.setChannel(1);
	for (int i = 0; i < 10; i++)
	{
		midi.playNote(64, 64);
		Sleep(2000);
	}
	return (0);
}