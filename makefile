# $Id: makefile,v 1.8 2010/03/24 13:17:06 stoecker Exp $
# probably works not with all compilers. Thought this should be easy
# fixable. There is nothing special at this source.

ifdef windir
CC   = gcc
OPTS = -Wall -W -O3 -DWINDOWSVERSION 
LIBS = -lwsock32
else
#OPTS = -Wall -W -O3 -I../libj2735v2016/src
OPTS = -DCAMP_DENSO_WSU -Wall -W -I../libj2735v2016/src
endif

SRC=rsu_send.c j2735_encode.c udp_socket.c

ntripclient: ntripclient.c $(SRC)
	$(CC) $(OPTS) ntripclient.c $(SRC) -I../libj2735v2016/src -o $@ ../libj2735v2016/libj2735v2016.a $(LIBS)

test_encode: test_encode.c $(SRC)
	$(CC) $(OPTS) test_encode.c $(SRC) -I../libj2735v2016/src -o $@ ../libj2735v2016/libj2735v2016.a $(LIBS)

clean:
	$(RM) ntripclient core*

archive:
	zip -9 ntripclient.zip ntripclient.c makefile README serial.c

tgzarchive:
	tar -czf ntripclient.tgz ntripclient.c makefile README serial.c
