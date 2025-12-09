cmake_minimum_required(VERSION 3.10)
project(libucd VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 配置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

# 添加调试选项
option(DEBUG "Enable debug mode" OFF)
if(DEBUG)
    add_definitions(-DDEBUG=1)
endif()

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 公共头文件
set(PUBLIC_HEADERS
    include/libucd.h
)

# 私有头文件
set(PRIVATE_HEADERS
    src/CharDistribution.h
    src/nsCodingStateMachine.h
    src/nsGB2312Prober.h
    src/nsSBCSGroupProber.h
    src/JpCntx.h
    src/nsEUCJPProber.h
    src/nsHebrewProber.h
    src/nsSBCharSetProber.h
    src/nsEUCKRProber.h
    src/nsLatin1Prober.h
    src/nsSJISProber.h
    src/nsBig5Prober.h
    src/nsEUCTWProber.h
    src/nsMBCSGroupProber.h
    src/nsUTF8Prober.h
    src/nsCharSetProber.h
    src/nsEscCharsetProber.h
    src/nsPkgInt.h
    src/nsUniversalDetector.h
    src/nsDebug.h
    src/prmem.h
    src/nscore.h
    src/Big5Freq.tab
    src/EUCKRFreq.tab
    src/EUCTWFreq.tab
    src/GB2312Freq.tab
    src/JISFreq.tab
)

# 源文件
set(SOURCES
    src/ucdapi.cpp
    src/CharDistribution.cpp
    src/JpCntx.cpp
    src/LangBulgarianModel.cpp
    src/LangCyrillicModel.cpp
    src/LangGreekModel.cpp
    src/LangHebrewModel.cpp
    src/LangHungarianModel.cpp
    src/LangThaiModel.cpp
    src/LangCzechModel.cpp
    src/LangFinnishModel.cpp
    src/LangFrenchModel.cpp
    src/LangGermanModel.cpp
    src/LangPolishModel.cpp
    src/LangSpanishModel.cpp
    src/LangSwedishModel.cpp
    src/LangTurkishModel.cpp
    src/nsBig5Prober.cpp
    src/nsCharSetProber.cpp
    src/nsEUCJPProber.cpp
    src/nsEUCKRProber.cpp
    src/nsEUCTWProber.cpp
    src/nsEscCharsetProber.cpp
    src/nsEscSM.cpp
    src/nsGB2312Prober.cpp
    src/nsHebrewProber.cpp
    src/nsLatin1Prober.cpp
    src/nsMBCSGroupProber.cpp
    src/nsMBCSSM.cpp
    src/nsSBCSGroupProber.cpp
    src/nsSBCharSetProber.cpp
    src/nsSJISProber.cpp
    src/nsUTF8Prober.cpp
    src/nsUniversalDetector.cpp
)

# 创建共享库
add_library(libucd_static STATIC ${SOURCES} ${PRIVATE_HEADERS})
target_include_directories(libucd_static PUBLIC     
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

# message(STATUS "---- libucd_static created -----")
# # 打印 ${CMAKE_SOURCE_DIR}/include
# message(STATUS "Include dir: ${CMAKE_CURRENT_SOURCE_DIR}/include")

# # 创建共享库
# add_library(libucd SHARED ${SOURCES} ${PRIVATE_HEADERS})
# target_include_directories(libucd PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 设置库的版本信息
set_target_properties(libucd_static PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# set_target_properties(libucd PROPERTIES
#     VERSION ${PROJECT_VERSION}
#     SOVERSION 1
# )