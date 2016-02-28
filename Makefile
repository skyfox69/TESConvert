MAKE=make
SHELL=/bin/sh

default: tesconvert

CC = g++

CFLAGS = -g -O0 -std=c++14 -I. -pipe -Wp,-fexceptions -fstack-protector --param=ssp-buffer-size=4  -m64 -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -fno-strict-aliasing -fwrapv -fPIC -static-libgcc -fno-omit-frame-pointer -fno-strict-aliasing -DMY_PTHREAD_FASTMUTEX=1

#CFLAGS = -g -O -std=c++11 -pipe -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=4  -m64 -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -fno-strict-aliasing -fwrapv -fPIC  -fPIC -static-libgcc -fno-omit-frame-pointer -fno-strict-aliasing -DMY_PTHREAD_FASTMUTEX=1

LIBS =

LDFLAGS = -g -lpthread -lz -lm -lrt -ldl -lpng

PRG = tesconvert
SRC = main.cpp \
      common/util/endian.cpp \
      common/util/tesoptions.cpp \
      common/util/bitmap.cpp \
      common/util/verbosity.cpp \
      common/util/compressor.cpp \
      common/util/tesmappingstorage.cpp \
      common/record/tesrecordbase.cpp \
      common/record/tesrecordmain.cpp \
      common/record/tesrecordsub.cpp \
      common/record/tesrecordgroup.cpp \
      common/tesparser.cpp \
      common/tesprocessor.cpp \
      tes3/tes3recordfactory.cpp \
      tes3/tes3processor.cpp \
      tes3/record/tes3recordgeneric.cpp \
      tes3/record/tes3recordignore.cpp \
      tes3/record/tes3recordgroup.cpp \
      tes3/subrecord/tes3subrecordhedr.cpp \
      tes3/subrecord/tes3subrecordweat.cpp \
      tes3/subrecord/tes3subrecordsnam.cpp \
      tes3/subrecord/tes3subrecordvnml.cpp \
      tes3/subrecord/tes3subrecordvhgt.cpp \
      tes3/subrecord/tes3subrecordwnam.cpp \
      tes3/subrecord/tes3subrecordvtex.cpp \
      tes3/subrecord/tes3subrecordambi.cpp \
      tes3/subrecord/tes3subrecordsinglestring.cpp \
      tes3/subrecord/tes3subrecordsinglefloat.cpp \
      tes3/subrecord/tes3subrecordsingleulong.cpp \
      tes3/subrecord/tes3subrecordcolorref.cpp \
      tes3/subrecord/tes3subrecordflags.cpp \
      tes3/subrecord/tes3subrecordignore.cpp \
      tes3/subrecord/tes3subrecorddatacell.cpp \
      tes3/subrecord/tes3subrecordintvland.cpp \
      tes3/subrecord/tes3subrecorddatafrmr.cpp \
      tes3/subrecord/tes3subrecorddatates3.cpp \
      tes4/tes4recordfactory.cpp \
      tes4/tes4processor.cpp \
      tes4/tes4converter.cpp \
      tes4/record/tes4recordgeneric.cpp \
      tes4/record/tes4recordgroup.cpp \
      tes4/record/tes4recordignore.cpp \
      tes4/subrecord/tes4subrecordhedr.cpp \
      tes4/subrecord/tes4subrecordmnam.cpp \
      tes4/subrecord/tes4subrecordvnml.cpp \
      tes4/subrecord/tes4subrecordvhgt.cpp \
      tes4/subrecord/tes4subrecordatxt.cpp \
      tes4/subrecord/tes4subrecordbtxt.cpp \
      tes4/subrecord/tes4subrecordvtxt.cpp \
      tes4/subrecord/tes4subrecordobnd.cpp \
      tes4/subrecord/tes4subrecorddodt.cpp \
      tes4/subrecord/tes4subrecordonam.cpp \
      tes4/subrecord/tes4subrecordxxxx.cpp \
      tes4/subrecord/tes4subrecordxclccell.cpp \
      tes4/subrecord/tes4subrecordsinglefloat.cpp \
      tes4/subrecord/tes4subrecordsinglestring.cpp \
      tes4/subrecord/tes4subrecordsingleulong.cpp \
      tes4/subrecord/tes4subrecordsingleushort.cpp \
      tes4/subrecord/tes4subrecordsingleuchar.cpp \
      tes4/subrecord/tes4subrecorddoublelong.cpp \
      tes4/subrecord/tes4subrecorddoubleuchar.cpp \
      tes4/subrecord/tes4subrecorddoublefloat.cpp \
      tes4/subrecord/tes4subrecorddoubleshort.cpp \
      tes4/subrecord/tes4subrecordtriplefloat.cpp \
      tes4/subrecord/tes4subrecordflags.cpp \
      tes4/subrecord/tes4subrecordignore.cpp \

OBJ = ${SRC:%.cpp=%.o}

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ ${@:.o=.cpp}

${PRG}: ${OBJ}
	$(CC) $(LDFLAGS) -o ${PRG} ${OBJ} $(LIBS)

clean:
	rm -f ${PRG}
	rm -f ${OBJ}

rebuild: clean tesconvert

rmimg:
	rm -f *.bmp
	rm -f *.png

