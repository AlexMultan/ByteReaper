#
# Internal file for GetGitRevisionDescription.cmake
#
# Requires CMake 2.6 or newer (uses the 'function' command)
#
# Original Author:
# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com
# Iowa State University HCI Graduate Program/VRAC
#
# Copyright 2009-2012, Iowa State University
# Copyright 2011-2015, Contributors
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
# SPDX-License-Identifier: BSL-1.0

set(HEAD_HASH)

file(READ "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/cmake-build-debug/engine/vendor/SDL/CMakeFiles/git-data/HEAD" HEAD_CONTENTS LIMIT 1024)

string(STRIP "${HEAD_CONTENTS}" HEAD_CONTENTS)
if(HEAD_CONTENTS MATCHES "ref")
	# named branch
	string(REPLACE "ref: " "" HEAD_REF "${HEAD_CONTENTS}")
	if(EXISTS "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/.git/modules/engine/vendor/SDL/${HEAD_REF}")
		configure_file("/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/.git/modules/engine/vendor/SDL/${HEAD_REF}" "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/cmake-build-debug/engine/vendor/SDL/CMakeFiles/git-data/head-ref" COPYONLY)
	elseif(EXISTS "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/.git/modules/engine/vendor/SDL/packed-refs")
		configure_file("/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/.git/modules/engine/vendor/SDL/packed-refs" "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/cmake-build-debug/engine/vendor/SDL/CMakeFiles/git-data/packed-refs" COPYONLY)
		file(READ "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/cmake-build-debug/engine/vendor/SDL/CMakeFiles/git-data/packed-refs" PACKED_REFS)
		if(${PACKED_REFS} MATCHES "([0-9a-z]*) ${HEAD_REF}")
			set(HEAD_HASH "${CMAKE_MATCH_1}")
		endif()
	elseif(EXISTS "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/.git/modules/engine/vendor/SDL/reftable/tables.list")
		configure_file("/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/.git/modules/engine/vendor/SDL/reftable/tables.list" "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/cmake-build-debug/engine/vendor/SDL/CMakeFiles/git-data/reftable-tables.list" COPYONLY)
	endif()
else()
	# detached HEAD
	configure_file("/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/.git/modules/engine/vendor/SDL/HEAD" "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/cmake-build-debug/engine/vendor/SDL/CMakeFiles/git-data/head-ref" COPYONLY)
endif()

if(NOT HEAD_HASH AND EXISTS "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/cmake-build-debug/engine/vendor/SDL/CMakeFiles/git-data/head-ref")
	file(READ "/run/media/alex/57016d74-ac9c-46d4-bb38-da9f9a681708/ByteReaper/cmake-build-debug/engine/vendor/SDL/CMakeFiles/git-data/head-ref" HEAD_HASH LIMIT 1024)
	string(STRIP "${HEAD_HASH}" HEAD_HASH)
endif()
