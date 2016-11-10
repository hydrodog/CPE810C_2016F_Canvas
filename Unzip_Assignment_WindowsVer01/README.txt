We use an external library to uncompress ZIP files within our Qt application.

The best library that implements this feature is QuaZIP:

QuaZIP is a simple C++ wrapper that can be used to access ZIP archives. It uses the Qt toolkit, which means that it is a cross-platform (Windows/Linux/BSD/UNIX/Mac/Others) library.

It depends on zlib library, so we need to download them from their official websites. We use the latest versions of both for this example:

QuaZIP v0.7
zlib v1.2.8

First of all, uncompress the file zlib128.zip in your computer wherever you want. I have chosen the path G:\Qt\zlib-1.2.8 because in the G:\Qt folder I have my original installation of Qt.

After that, open a Windows Command Prompt and write the next commands:

$ cd G:\Qt\zlib-1.2.8
$ mingw32-make -f win32/Makefile.gcc

Make sure that the installation folder of both, Qt and MinGW, is accessible through the PATH system variable.

The next step is uncompress the file quazip-0.7.zip. For this library I have chosen the folder G:\Qt\quazip-0.7.

Again, open a Windows Command Prompt and write the next commands:

$ cd G:\Qt\quazip-0.7
$ qmake "CONFIG+=release" "INCLUDEPATH+=G:/Qt/zlib-1.2.8" "LIBS+=-LG:/Qt/zlib-1.2.8 -lz"
$ mingw32-make
$ qmake "CONFIG+=debug" "INCLUDEPATH+=G:/Qt/zlib-1.2.8" "LIBS+=-LG:/Qt/zlib-1.2.8 -lz"
$ mingw32-make

Take into account that if the folder in which you have uncompressed zlib is different, you need to modify the commands above to write the correct path.

If you do not get any error, it means that you have build QuaZIP (and zlib) correctly!

Finally, after creating a Qt project to unzip file, add following code to the *.pro file:

INCLUDEPATH += G:/Qt/zlib-1.2.8
LIBS += -LG:/Qt/zlib-1.2.8 -lz
INCLUDEPATH += G:/Qt/quazip-0.7/quazip
LIBS += -LG:/Qt/quazip-0.7/quazip/release -lquazip
(Don't forget to change the path!)