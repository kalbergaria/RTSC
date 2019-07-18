CC=g++

EXEC_NAME = RTSC.exe

IDIR=Include
SDIR=Source
ODIR=Objects
EXECDIR=Application

#CFLAGS=-lm -lpthread -I$(IDIR) -Lrelease -lstdc++ -Wl,-rpath=.
CFLAGS= -I$(IDIR) -lpthread

_DEPS=Base.h\
      Ptr32Queue.h\
      Global.h\
      Logger.h\
      LogMessage.h\
      Platform.h\
      RtscConfig.h\
      RtscTiming.h\
      ThreadBase.h\
      ThreadManager.h\
      UdpHeader.h\
      UdpReceiver.h\
      UdpSender.h\

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=Base.o\
     Ptr32Queue.o\
     Logger.o\
     Main.o\
     RtscTiming.o\
     ThreadBase.o\
     ThreadManager.o\
     UdpReceiver.o\
     UdpSender.o\

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(EXEC_NAME): $(OBJ)
	$(CC) -o $(EXECDIR)/$@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o $(RDIR)/$(EXEC_NAME)
