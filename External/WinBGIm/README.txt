[Jozko Mrkvicka, 3rd Oct 2020]

I have downloaded the WinBGIm library somewhere from Internet. I was not able to build it with MinGW G++ 9.2.0 and therefore I have done the following adjustments. Then I recompiled the libbgi.a file.

makefile:
- Added "SHELL = cmd".
- Added option "-std=gnu++98" to
	misc.o: misc.cxx winbgim.h winbgitypes.h
		g++ $(CPPFLAGS) misc.cxx

graphics.h:
- On line 302 second parameter changed from "right" to "top".

winbgim.h:
- On line 302 second parameter changed from "right" to "top".

