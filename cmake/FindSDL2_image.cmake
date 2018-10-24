# Verder verneukt door mij
# SDL2_image_INCLUDE_DIR
# SDL2_image_LIBRARY
# SDL2_image_FOUND
# De rest wil je waarschijnlijk niet

# Modified by Eric Wing.

#=============================================================================
# Copyright 2003-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

SET(SDL2_image_SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
)

FIND_PATH(SDL2_image_INCLUDE_DIR SDL_ttf.h
	HINTS
	$ENV{SDL2_imageDIR}
	PATH_SUFFIXES include/SDL2 include
	PATHS ${SDL2_image_SEARCH_PATHS}
)

FIND_LIBRARY(SDL2_image_LIBRARY_TEMP
	NAMES SDL2_image
	HINTS
	$ENV{SDL2_imageDIR}
	PATH_SUFFIXES lib64 lib
	PATHS ${SDL2_image_SEARCH_PATHS}
)

IF(NOT SDL2_image_BUILDING_LIBRARY)
	IF(NOT ${SDL2_image_INCLUDE_DIR} MATCHES ".framework")
		# Non-OS X framework versions expect you to also dynamically link to
		# SDL2_imagemain. This is mainly for Windows and OS X. Other (Unix) platforms
		# seem to provide SDL2_imagemain for compatibility even though they don't
		# necessarily need it.
		FIND_LIBRARY(SDL2_imageMAIN_LIBRARY
			NAMES SDL2_image
			HINTS
			$ENV{SDL2_imageDIR}
			PATH_SUFFIXES lib64 lib
			PATHS ${SDL2_image_SEARCH_PATHS}
		)
	ENDIF(NOT ${SDL2_image_INCLUDE_DIR} MATCHES ".framework")
ENDIF(NOT SDL2_image_BUILDING_LIBRARY)

# SDL2_image may require threads on your system.
# The Apple build may not need an explicit flag because one of the
# frameworks may already provide it.
# But for non-OSX systems, I will use the CMake Threads package.
IF(NOT APPLE)
	FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)

# MinGW needs an additional library, mwindows
# It's total link flags should look like -lmingw32 -lSDL2_imagemain -lSDL2_image -lmwindows
# (Actually on second look, I think it only needs one of the m* libraries.)
IF(MINGW)
	SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
ENDIF(MINGW)

IF(SDL2_image_LIBRARY_TEMP)
	# For SDL2_imagemain
	IF(NOT SDL2_image_BUILDING_LIBRARY)
		IF(SDL2_imageMAIN_LIBRARY)
			SET(SDL2_image_LIBRARY_TEMP ${SDL2_imageMAIN_LIBRARY} ${SDL2_image_LIBRARY_TEMP})
		ENDIF(SDL2_imageMAIN_LIBRARY)
	ENDIF(NOT SDL2_image_BUILDING_LIBRARY)

	# For OS X, SDL2_image uses Cocoa as a backend so it must link to Cocoa.
	# CMake doesn't display the -framework Cocoa string in the UI even
	# though it actually is there if I modify a pre-used variable.
	# I think it has something to do with the CACHE STRING.
	# So I use a temporary variable until the end so I can set the
	# "real" variable in one-shot.
	IF(APPLE)
		SET(SDL2_image_LIBRARY_TEMP ${SDL2_image_LIBRARY_TEMP} "-framework Cocoa")
	ENDIF(APPLE)

	# For threads, as mentioned Apple doesn't need this.
	# In fact, there seems to be a problem if I used the Threads package
	# and try using this line, so I'm just skipping it entirely for OS X.
	IF(NOT APPLE)
		SET(SDL2_image_LIBRARY_TEMP ${SDL2_image_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
	ENDIF(NOT APPLE)

	# For MinGW library
	IF(MINGW)
		SET(SDL2_image_LIBRARY_TEMP ${MINGW32_LIBRARY} ${SDL2_image_LIBRARY_TEMP})
	ENDIF(MINGW)

	# Set the final string here so the GUI reflects the final state.
	SET(SDL2_image_LIBRARY ${SDL2_image_LIBRARY_TEMP} CACHE STRING "Where the SDL2_image Library can be found")
	# Set the temp variable to INTERNAL so it is not seen in the CMake GUI
	SET(SDL2_image_LIBRARY_TEMP "${SDL2_image_LIBRARY_TEMP}" CACHE INTERNAL "")
ENDIF(SDL2_image_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_image REQUIRED_VARS SDL2_image_LIBRARY SDL2_image_INCLUDE_DIR)
