CC=g++

EXEC_NAME = RTSC

IDIR=Include
SDIR=Source
ODIR=Objects
EXECDIR=Application

#CFLAGS=-lm -lpthread -I$(IDIR) -Lrelease -lstdc++ -Wl,-rpath=.
CFLAGS= -I$(IDIR) -lpthread

_DEPS=Base.h\
      CharPtrQueue.h\
      Global.h\
      Logger.h\
      LogMSG.h\
      Platform.h\
      RtscConfig.h\
      RtscTiming.h\
      ThreadBase.h\
      ThreadManager.h\
      UDPHeader.h\
      UDPReceiver.h\
      UDPSender.h\

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=Base.o\
     CharPtrQueue.o\
     Logger.o\
     main.o\
     RtscTiming.o\
     ThreadBase.o\
     ThreadManager.o\
     UDPReceiver.o\
     UDPSender.o\

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(EXEC_NAME): $(OBJ)
	$(CC) -o $(RDIR)/$@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o $(RDIR)/$(EXEC_NAME)
