#!/bin/bash
ADDRESS=192.168.178.49
while : 
do
R=$(($RANDOM%256))
G=$(($RANDOM%256))
B=$(($RANDOM%256))
COLOR="?r=${R}&g=${G}&b=${B}"
URL=http://${ADDRESS}/rgb${COLOR}
echo $URL
curl ${URL}
echo "\n"
sleep 2
done
