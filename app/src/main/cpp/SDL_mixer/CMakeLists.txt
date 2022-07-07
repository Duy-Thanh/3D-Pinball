cmake_minimum_required(VERSION 2.8.12)
project(SDL_mixer C)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -O1 -O2 -O3 -flto=full")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O0 -O1 -O2 -O3 -flto=full")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -O1 -O2 -O3 -flto=full")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O0 -O1 -O2 -O3 -flto=full")


if (ANDROID)

    # FIXME: missing CMakeLists.txt for MPG123
    set(SUPPORT_MP3_MPG123 OFF CACHE BOOL "" FORCE)

    option(SUPPORT_FLAC "Support loading FLAC music with libFLAC" OFF)
    option(SUPPORT_OGG "Support loading OGG Vorbis music via Tremor" OFF)
    option(SUPPORT_MP3_MPG123 "Support loading MP3 music via MPG123" ON)
    option(SUPPORT_MOD_MODPLUG "Support loading MOD music via modplug" ON)
    option(SUPPORT_MID_TIMIDITY "Support TiMidity" OFF)

    include_directories(include src src/codecs)

    add_library(SDL2_mixer SHARED)

    target_sources(SDL2_mixer PRIVATE
            src/effect_position.c src/effects_internal.c src/effect_stereoreverse.c
            src/mixer.c src/music.c src/utils.c
            src/codecs/load_aiff.c src/codecs/load_voc.c
            src/codecs/music_cmd.c src/codecs/music_flac.c
            src/codecs/music_fluidsynth.c src/codecs/music_mad.c
            src/codecs/music_mikmod.c src/codecs/music_modplug.c
            src/codecs/music_mpg123.c src/codecs/music_nativemidi.c
            src/codecs/music_ogg.c src/codecs/music_opus.c
            src/codecs/music_timidity.c src/codecs/music_wav.c src/codecs/music_xmp.c)

    if (SUPPORT_FLAC)
        add_definitions(-DMUSIC_FLAC)
        add_subdirectory(external/flac)
        include_directories(external/flac/include)
        target_link_libraries(SDL2_mixer PRIVATE FLAC)
    endif()

    if (SUPPORT_OGG)
        add_definitions(-DMUSIC_OGG -DOGG_USE_TREMOR -DOGG_HEADER=<ivorbisfile.h>)
        add_subdirectory(external/ogg)
        add_subdirectory(external/vorbis)
        include_directories(external/vorbis)
        target_link_libraries(SDL2_mixer PRIVATE vorbis ogg)
    endif()

    if (SUPPORT_MP3_MPG123)
        add_definitions(-DMUSIC_MP3_MPG123)
        add_subdirectory(external/mpg123)
        target_link_libraries(SDL2_mixer PRIVATE mpg123)
    endif()

    if (SUPPORT_MOD_MODPLUG)
        add_definitions(-DMUSIC_MOD_MODPLUG -DMODPLUG_HEADER=<modplug.h>)
        add_subdirectory(external/libmodplug)
        include_directories(external/libmodplug/src)
        target_link_libraries(SDL2_mixer PRIVATE modplug)
    endif()

    if (SUPPORT_MID_TIMIDITY)
        add_definitions(-DMUSIC_MID_TIMIDITY)
        add_subdirectory(src/codecs/timidity)
        target_link_libraries(SDL2_mixer PRIVATE timidity)
    endif()

    target_include_directories(SDL2_mixer PUBLIC include)
    target_link_libraries(SDL2_mixer PRIVATE SDL2)
else()

endif()
