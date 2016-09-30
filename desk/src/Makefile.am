# these are the headers for your project

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = pfdevice

pfdevice_SOURCES= ./wizard/bluetoothwiz.cpp \
./wizard/EmanEz.cpp \
./wizard/serialwiz.cpp \
./wizard/usbwiz.cpp \
./wizard/hardwaredlg.cpp \
./controls/mcontrols.cpp \
./controls/managetext.cpp \
./controls/tableinfo.cpp \
./pfdevice.cpp \
./handlers/devicemanager.cpp \
./handlers/connectionthread.cpp \
./handlers/displaythread.cpp \
./handlers/scanfile.cpp \
./device/device.cpp \
./device/displayframe.cpp \
./device/mapdevice.cpp \
./acqpanel.cpp \
./acqreportdoc.cpp \
./acqreportview.cpp \
../lib/acqcom/virtualcom.cpp \
../lib/acqcom/serial/serialcom.cpp \
../lib/acqcom/network/tcpcom.cpp \
../lib/acqcom/usb/usbcom.cpp \
../lib/acqcom/bluetooth/bluetoothcom.cpp \
../lib/acqhelp/acqhelp.cpp \
../lib/acqreport/text/textreportgen.cpp \
../lib/acqreport/xls/xlsreportgen.cpp \
../lib/acqreport/reportgen.cpp \
../lib/acqvis/multiplexdisp.cpp \
../lib/acqvis/channelgrid.cpp \
../lib/acqconfig/sunshine/ssconfig.cpp \
../lib/acqconfig/acqconfig.cpp \
../lib/acqproto/sunshine/ssproto.cpp \
../lib/acqproto/protocolhandler.cpp 
# the application source, library search path, and link libraries
pfdevice_LDFLAGS = $(WX_LIBS)
pfdevice_CXXFLAGS = -DPREFIX=\"$(prefix)\" -DDATADIRS=\"$(datadir)\/\"
pfdevice_CFLAGS =  -DPREFIX=\"$(prefix)\" -DDATADIRS=\"$(datadir)\/\"
noinst_HEADERS = $(top_srcdir)/include/pfdevice.h $(top_srcdir)/include/acqhelp.h $(top_srcdir)/include/channelgrid.h $(top_srcdir)/include/acqconfig.h $(top_srcdir)/include/connectionthread.h  $(top_srcdir)/include/devicemanager.h  $(top_srcdir)/include/displayframe.h $(top_srcdir)/include/displaythread.h  $(top_srcdir)/include/hardwaredlg.h $(top_srcdir)/include/mapdevice.h $(top_srcdir)/include/multiplexdisp.h   $(top_srcdir)/include/acq/virtualcom.h $(top_srcdir)/include/tableinfo.h $(top_srcdir)/include/mcontrols.h $(top_srcdir)/include/managetext.h $(top_srcdir)/include/acq/protocolhandler.h

