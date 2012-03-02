: Set paths for the "include" and "lib" directories of the toolchain and the
: Windows SDK. Note that "link" has a dependency on "common7\ide\mspdb*.dll".
set PATH=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\bin;C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE;%PATH%
set INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include;%INCLUDE%
set LIB=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib;%LIB%
