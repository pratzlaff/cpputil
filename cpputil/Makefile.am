hh_sources = \
ansicolor.hh \
byte.hh \
cpputil.hh \
fmt.hh \
math.hh \
mem_data.hh \
re.hh \
singleton.hh \
str.hh \
fdstream.hh \
rand.hh \
rdb.hh \
sequence.hh \
ss_cast.hh \
thread.hh \
types.hh

cc_sources = \
byte.cc \
fmt.cc \
rand.cc \
rdb.cc \
str.cc

cpputilheaderdir = $(includedir)/cpputil
cpputilheader_HEADERS = $(hh_sources)

lib_LTLIBRARIES = libcpputil.la
libcpputil_la_SOURCES = $(hh_sources) $(cc_sources)
libcpputil_la_LDFLAGS= -version-info $(LIBRARY_VERSION) -release $(RELEASE)
