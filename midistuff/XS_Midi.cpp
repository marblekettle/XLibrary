#include "XS_Midi.hpp"
#include <cstring>

XS_Midi::XS_Midi(): _ready(false)
{
	for (int i = 0; i < 4; i++)
		_msg[i] = 0;
}

XS_Midi::~XS_Midi()
{
	closeDevice();
}

XS_Midi::XS_Midi(UINT id): XS_Midi()
{
	changeDevice(id);
}

XS_Midi::XS_Midi(const char *name): XS_Midi()
{
	changeDevice(name);
}

XS_Midi::XS_Midi(const std::string &name): XS_Midi()
{
	changeDevice(name);
}

XS_Midi::XS_Midi(const XS_Midi &copy): _ready(false)
{
	*this = copy;
}

XS_Midi	&XS_Midi::operator=(const XS_Midi &from)
{
	this->_dev = from._dev;
	this->_ready = from._ready;
	for (int i = 0; i < 4; i++)
		this->_msg[i] = from._msg[i];
	return (*this);
}

bool	XS_Midi::closeDevice()
{
	if (_ready)
	{
		midiOutClose(_dev);
		return (true);
	}
	return (false);
}

bool	XS_Midi::changeDevice(UINT id)
{
	closeDevice();
	try
	{
		MMRESULT res = midiOutOpen(&_dev, id, 0, 0, CALLBACK_NULL);
		if (res)
			throw (XS_MidiDevErrorException());
	}
	catch (std::exception &e)
	{
		_ready = false;
		throw ;
	}
	_ready = true;
	return (true);
}

bool	XS_Midi::changeDevice(const char *name)
{
	std::string	devname(name);
	return (changeDevice(devname));
}

bool	XS_Midi::changeDevice(const std::string &name)
{
	closeDevice();
	UINT devcount = midiOutGetNumDevs();
	for (int i = 0; i < devcount; i++)
	{
		MIDIOUTCAPS	i_dev;
		MMRESULT is_ok = midiOutGetDevCaps(i, &i_dev, sizeof(MIDIOUTCAPS));
		std::string	devname(reinterpret_cast<char *>(i_dev.szPname));
		if (!is_ok && name == devname)
		{
			MMRESULT	res = midiOutOpen(&_dev, i, 0, 0, CALLBACK_NULL);
			if (res)
				throw (XS_MidiDevErrorException());
			_ready = true;
			break ;
		}
		if (i == devcount - 1)
		{
			_ready = false;
			throw (XS_MidiDevNotFoundException());
		}
	}
	return (true);
}

bool	XS_Midi::sendMidi(UINT msg)
{
	midiOutShortMsg(_dev, msg);
	return (true);
}

bool	XS_Midi::playNote(char pitch, char vel)
{
	_msg[0] = vel;
	_msg[1] = pitch;
	midiOutShortMsg(_dev, *(reinterpret_cast<UINT *>(_msg)));
	return (true);
}

bool	XS_Midi::setChannel(char chan)
{
	_msg[2] = 144 + chan;
	return (true);
}

const char	*XS_Midi::XS_MidiDevNotFoundException::what() const throw()
{
	return ("MIDI Device not found");
}

const char	*XS_Midi::XS_MidiDevErrorException::what() const throw()
{
	return ("MIDI Device Error");
}
