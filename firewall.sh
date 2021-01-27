#!/bin/bash

# initializing parse of the rules and packets  
remain_rules=`cat "$1" | grep -o '^[^#]*'`
remain_packets=`(tee) | grep -o '^[^#]*'`

# initializing variable
packets_to_print=""

# loop over all of the rules and checking them column by column while
# checking only the remaining packets
while IFS=, read -r first second third fourth; do
   surviving_packets=`echo "$remain_packets" | ./firewall.exe "$first"`
   surviving_packets=`echo "$surviving_packets" | ./firewall.exe "$second"`
   surviving_packets=`echo "$surviving_packets" | ./firewall.exe "$third"`
   surviving_packets=`echo "$surviving_packets" | ./firewall.exe "$fourth"`
   packets_to_print+=`echo -e "$surviving_packets"`
   packets_to_print+="\n"
done <<< "$remain_rules"

# parsing the output packets
packets_to_print=`echo -e "$packets_to_print" | sort | uniq`
packets_to_print=`echo -e "$packets_to_print" | tr -d "[:blank:]"`
packets_to_print=`echo -e "$packets_to_print" | grep -o '^[^#]*'`

# print output
echo -e "$packets_to_print"
