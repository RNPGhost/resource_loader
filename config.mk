CXX = clang++

CXXFLAGS += -std=c++14 -Wall
opt: CXXFLAGS += -ffunction-sections -fdata-sections -flto -O3

LDFLAGS += -fuse-ld=gold
opt: LDFLAGS += -s -Wl,--gc-sections
