all: schedule_fcfs schedule_sjf schedule_srtf schedule_pr schedule_rr
.PHONY : all

schedule_fcfs: schedule_fcfs.o schedule_proc.o
	gcc schedule_fcfs.o schedule_proc.o -o schedule_fcfs
schedule_sjf: schedule_sjf.o schedule_proc.o
	gcc schedule_sjf.o schedule_proc.o -o schedule_sjf
schedule_srtf: schedule_srtf.o schedule_proc.o
	gcc schedule_srtf.o schedule_proc.o -o schedule_srtf
schedule_pr: schedule_pr.o schedule_proc.o
	gcc schedule_pr.o schedule_proc.o -o schedule_pr
schedule_rr: schedule_rr.o schedule_proc.o
	gcc schedule_rr.o schedule_proc.o -o schedule_rr

schedule_fcfs.o: schedule_fcfs.c schedule_proc.h
	gcc schedule_fcfs.c schedule_proc.h -c
schedule_sjf.o: schedule_sjf.c schedule_proc.h
	gcc schedule_sjf.c schedule_proc.h -c
schedule_srtf.o: schedule_srtf.c schedule_proc.h
	gcc schedule_srtf.c schedule_proc.h -c
schedule_pr.o: schedule_pr.c schedule_proc.h
	gcc schedule_pr.c schedule_proc.h -c
schedule_rr.o: schedule_rr.c schedule_proc.h
	gcc schedule_rr.c schedule_proc.h -c
schedule_proc.o: schedule_proc.c schedule_proc.h
	gcc schedule_proc.c schedule_proc.h -c

clean:
	rm schedule_fcfs schedule_sjf schedule_srtf schedule_pr schedule_rr *.o
