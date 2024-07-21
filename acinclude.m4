## adapted from libdbi-drivers acinclude.m4

AC_DEFUN(AC_FIND_FILE,
[
$3=NO
for i in $2; do
	for j in $1; do
		if test -r "$i/$j"; then
			$3=$i
			break 2
		fi
	done
done
])

AC_DEFUN(AC_CHECK_INTSIZES,
[
AC_CHECK_SIZEOF(short)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)

case 2 in
	$ac_cv_sizeof_short)
		UINT16='unsigned short'; INT16='short'; break
		;;
	$ac_cv_sizeof_int)
		UINT16='unsigned int'; INT16='int'; break
		;;
	$ac_cv_sizeof_long)
		UINT16='unsigned long'; INT16='long'; break
		;;
	$ac_cv_sizeof_long_long)
		UINT16='unsigned long long'; INT16='long long'; break
		;;
	*)
		AC_ERROR('Cannot find type for int16')
		;;
esac
case 4 in
	$ac_cv_sizeof_short)
		UINT32='unsigned short'; INT32='short'; break
		;;
	$ac_cv_sizeof_int)
		UINT32='unsigned int'; INT32='int'; break
		;;
	$ac_cv_sizeof_long)
		UINT32='unsigned long'; INT32='long'; break
		;;
	$ac_cv_sizeof_long_long)
		UINT32='unsigned long long'; INT32='long long'; break
		;;
	*)
		AC_ERROR('Cannot find type for int32')
		;;
esac
case 8 in
	$ac_cv_sizeof_short)
		UINT64='unsigned short'; INT64='short'; break
		;;
	$ac_cv_sizeof_int)
		UINT64='unsigned int'; INT64='int'; break
		;;
	$ac_cv_sizeof_long)
		UINT64='unsigned long'; INT64='long'; break
		;;
	$ac_cv_sizeof_long_long)
		UINT64='unsigned long long'; INT64='long long'; break
		;;
	*)
		AC_ERROR('Cannot find type for int64')
		;;
esac

AC_SUBST(INT16)
AC_SUBST(UINT16)
AC_SUBST(INT32)
AC_SUBST(UINT32)
AC_SUBST(INT64)
AC_SUBST(UINT64)
])

## SYBASE

AC_DEFUN(AC_CHECK_SYBASE,
[
AM_CONDITIONAL(HAVE_SYBASE, false)
ac_sybase="NO"
ac_sybase_incdir="NO"
ac_sybase_libdir="NO"

# exported variables
SYBASE_LIBS=""
SYBASE_LDFLAGS=""
SYBASE_INCLUDE=""

AC_MSG_CHECKING(for Sybase support)

AC_ARG_WITH(sybase,
	[  --with-sybase		  Include Sybase support.],
	[  ac_sybase="YES" ])
AC_ARG_WITH(sybase-dir,
	[  --with-sybase-dir	  Specifies the Sybase root directory.],
	[  ac_sybase_incdir="$withval"/include
	   ac_sybase_libdir="$withval"/lib ])
AC_ARG_WITH(sybase-incdir,
	[  --with-sybase-incdir	  Specifies where the Sybase include files are.],
	[  ac_sybase_incdir="$withval" ])
AC_ARG_WITH(sybase-libdir,
	[  --with-sybase-libdir	  Specifies where the Sybase libraries are.],
	[  ac_sybase_libdir="$withval" ])

if test "$ac_sybase" = "YES"; then
	if test "$ac_sybase_incdir" = "NO" || test "$ac_sybase_libs" = "NO"; then
		sybase_incdirs="/usr/include /usr/local/include /usr/include/sybase /usr/local/include/sybase /usr/local/sybase/include /opt/sybase/include"
		AC_FIND_FILE(ctpublic.h, $sybase_incdirs, ac_sybase_incdir)
		sybase_libdirs="/usr/lib /usr/local/lib /usr/lib/sybase /usr/local/lib/sybase /usr/local/sybase/lib /opt/sybase/lib"
		sybase_libs="libct.so libct.a"
		AC_FIND_FILE($sybase_libs, $sybase_libdirs, ac_sybase_libdir)
		if test "$ac_sybase_incdir" = "NO"; then
			AC_MSG_RESULT(no)
			AC_MSG_ERROR([Invalid Sybase directory - include files not found.])
		fi
		if test "$ac_sybase_libdir" = "NO"; then
			AC_MSG_RESULT(no)
			AC_MSG_ERROR([Invalid Sybase directory - libraries not found.])
		fi
	fi
	AC_MSG_RESULT([yes: libs in $ac_sybase_libdir, headers in $ac_sybase_incdir])
	AM_CONDITIONAL(HAVE_SYBASE, true)
	
	SYBASE_LIBS="-lct -lcs -lsybdb -lsybtcl -ldl"
	SYBASE_INCLUDE="-I$ac_sybase_incdir"
	SYBASE_LDFLAGS="-L$ac_sybase_libdir"
	
	AC_SUBST(SYBASE_LIBS)
	AC_SUBST(SYBASE_INCLUDE)
	AC_SUBST(SYBASE_LDFLAGS)
else
	AC_MSG_RESULT(no)
fi
])
