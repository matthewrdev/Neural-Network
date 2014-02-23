----------------------------------------------------------------------------
                                 FMOD 3.70
              Copyright (c) Firelight Technologies Pty, Ltd,    
                                1994 - 2003
----------------------------------------------------------------------------

                             http://www.fmod.org


----------------------------------------------------------------------------
WIN32 specific issues.
----------------------------------------------------------------------------

Remember to use the correct import library!

MSVC Users                   - use FMODVC.LIB
METROWERKS/CODEWARRIOR Users - use FMODVC.LIB
WATCOM Users                 - use FMODWC.LIB
BORLAND Users                - use FMODBC.LIB
LCC-WIN32 Users              - use FMODLCC.LIB
MINGW AND CYGWIN Users       - use LIBFMOD.A

Linux users        - link with libfmod-3-70.so (i.e. gcc file.c -lfmod-3.70)
Delphi Users       - use FMOD.PAS
Visual Basic Users - use FMOD.BAS

----------------------------------------------------------------------------
Linux specific issues.
----------------------------------------------------------------------------

Linux users link against libfmod-3.70.so.  This file must also be present
with your executable for distribution.


----------------------------------------------------------------------------
ASIO Config
----------------------------------------------------------------------------
FMOD ignores FSOUND_SetBufferSize in ASIO mode.  It relies on settings 
provided by the ASIO control panel supplied with the driver.  In the tools
directory of the FMOD api, you will find an asioconfig.exe tool which allows
you to configure the ASIO driver by doubleclicking on the appropriate driver.

----------------------------------------------------------------------------
FMOD End User License Agreement
----------------------------------------------------------------------------

FMOD's names, sources, documentation and binaries contained within the 
distributed archive are copyright © Firelight Technologies, Pty, Ltd. 
1994-2002.

The contents of the FMOD distribution archive may not be redistributed, 
reproduced, modified, transmitted, broadcast, published or adapted in any 
way, shape or form, without the prior written consent of the owner, 
Firelight Technologies, be it by tangible or non tangible media.

The FMOD.DLL file may be redistributed without the authors prior permission, 
and must remain unmodified.  The use of dll 'static linking' tools is 
discouraged.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------
Ogg Vorbis License
----------------------------------------------------------------------------
Portions Copyright (c) 2001, Xiphophorus

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
- Neither the name of the Xiphophorus nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
