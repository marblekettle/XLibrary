#ifndef XS_CORE_HPP
# define XS_CORE_HPP
# include "XS_Canvas.hpp"
# include "XS_Keymap.hpp"

class XS_Core : public XS_Canvas, public XS_Clock, public XS_Keymap
{
public:
				~XS_Core();
				XS_Core(const char *title, int width = DEF_WIDTH, \
					int height = DEF_HEIGHT, int frame_time = 40);
				XS_Core(const XS_Core &copy);
	XS_Core		&operator=(const XS_Core &assign);
private:
				XS_Core();
};

#endif