cmake_minimum_required(VERSION 3.4)
project(exp02 C)

set(CMAKE_C_STANDARD 99)

add_executable(process-fork fork/process-fork.c)
add_executable(process-exec fork/process-exec.c)
add_executable(schedule-fcfs schedule/schedule_fcfs.c schedule/schedule_proc.h schedule/schedule_proc.c)
add_executable(schedule-rr schedule/schedule_rr.c schedule/schedule_proc.h schedule/schedule_proc.c)
add_executable(schedule-pr schedule/schedule_pr.c schedule/schedule_proc.h schedule/schedule_proc.c)
add_executable(schedule-sjf schedule/schedule_sjf.c schedule/schedule_proc.h schedule/schedule_proc.c)
add_executable(schedule-srtf schedule/schedule_srtf.c schedule/schedule_proc.h schedule/schedule_proc.c)
#add_executable(test_proc test_proc.c schedule_proc.h schedule_proc.c)