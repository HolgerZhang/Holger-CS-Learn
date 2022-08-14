#!/bin/bash

calc_time=5  # 休眠时间
if [ "$1" ]; then
  if grep '^[[:digit:]]*$' <<<"$1" &>/dev/null; then
    calc_time=$1
  fi
fi

echo "Use time: ${calc_time}s"
#pgfault1=$(cat /proc/vmstat | grep pgfault | cut -d ' ' -f2)
pgfault1=$(awk '$1=="pgfault" {print $2}' /proc/vmstat)
echo "Now the number of page fault is $pgfault1"
sleep "$calc_time"
#pgfault2=$(cat /proc/vmstat | grep pgfault | cut -d ' ' -f2)
pgfault2=$(awk '$1=="pgfault" {print $2}' /proc/vmstat)
echo "Now the number of page fault is $pgfault2"
((page_fault=$pgfault2-$pgfault1))
echo "In $calc_time seconds, system calls $page_fault page fault!"
