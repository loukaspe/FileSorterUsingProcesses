cmake_minimum_required(VERSION 3.15)
project(LoukasPeteinaris_Prj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(LoukasPeteinaris_Prj2 main.cpp QuickSorter.cpp QuickSorter.h RecordReader.cpp RecordReader.h Helper.cpp Helper.h Record.cpp Record.h PipeReader.cpp PipeReader.h PipeWriter.cpp PipeWriter.h CoachFactory.cpp CoachFactory.h Coordinator.cpp Coordinator.h HeapSorter.cpp HeapSorter.h)