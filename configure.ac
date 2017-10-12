AC_INIT([Game Pencil Engine], [1.13], [help@pawbyte.com])
AM_INIT_AUTOMAKE([subdir-objects])
AC_PROG_CC
dnl Check for SDL
SDL_VERSION=2.0.6
AM_PATH_SDL2($SDL_VERSION,
          :,
          AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)
CFLAGS="$CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"
AC_CONFIG_FILES(Makefile)
AC_OUTPUT
