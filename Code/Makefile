EXEC_NAME = RTSC.exe
STATIC_LIB_NAME=RTSC.a

IDIR=Include
SDIR=Source
ODIR=Objects
EXECDIR=Application
STATICDIR=StaticLibrary

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
     RtscTiming.o\
     ThreadBase.o\
     ThreadManager.o\
     UdpReceiver.o\
     UdpSender.o\

_MAIN_OBJ=Main.o\

_ALL_OBJ:=$(_OBJ)$(_MAIN_OBJ)

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
ALL_OBJ = $(patsubst %,$(ODIR)/%,$(_ALL_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	g++ -c -o $@ $< $(CFLAGS)
	
$(EXEC_NAME): $(ALL_OBJ)
	g++ -o $(EXECDIR)/$@ $^ $(CFLAGS)

staticlib:
	@mkdir -p $(STATICDIR)
	ar rcs $(STATICDIR)/$(STATIC_LIB_NAME) $(OBJ)

clean:
	rm -f $(ODIR)/*.o $(RDIR)/$(EXEC_NAME)
