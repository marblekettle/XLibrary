#ifndef XS_MIDI_HPP
# define XS_MIDI_HPP
# include <windows.h>
# include <string>

class XS_Midi
{
private:
	HMIDIOUT		_dev;
	bool			_ready;
	unsigned char	_msg[4];
public:
	XS_Midi();
	~XS_Midi();
	XS_Midi(UINT id);
	XS_Midi(const char *name);
	XS_Midi(const std::string &name);
	XS_Midi(const XS_Midi &copy);
	XS_Midi	&operator=(const XS_Midi &from);

	bool	closeDevice();
	bool	changeDevice(UINT id);
	bool	changeDevice(const char *name);
	bool	changeDevice(const std::string &name);
	bool	sendMidi(UINT msg);
	bool	playNote(char pitch, char vel = 64);
	bool	setChannel(char chan);


	class XS_MidiDevNotFoundException : public std::exception
	{
		virtual const char	*what() const throw();
	};
	class XS_MidiDevErrorException : public std::exception
	{
		virtual const char	*what() const throw();
	};
};

#endif