#!/bin/bash
export LC_ALL=C
remain_rules=`cat "$1" | grep -o '^[^#]*'`

remain_packets=`(tee) | grep -o '^[^#]*'`
echo "$remain_rules" > rules_input_after.txt


> packets_output.txt

packets_to_print=""
while IFS=, read -r first second third fourth; do
   surviving_packets=`echo "$remain_packets" | ./firewall.exe "$first"`
   surviving_packets=`echo "$surviving_packets" | ./firewall.exe "$second"`
   surviving_packets=`echo "$surviving_packets" | ./firewall.exe "$third"`
   surviving_packets=`echo "$surviving_packets" | ./firewall.exe "$fourth"`
   packets_to_print+=`echo -e "$surviving_packets"`
   packets_to_print+="\n"
done <<< "$remain_rules"
packets_to_print=`echo -e "$packets_to_print" | sort | uniq`
echo -e "$packets_to_print" > beS_packets_output.txt
packets_to_print=`echo -e "$packets_to_print" | sort | uniq |tr -d "[:blank:]" | grep -o '^[^#]*'`
echo -e "$packets_to_print"
echo -e "$packets_to_print" > packets_output.txt
