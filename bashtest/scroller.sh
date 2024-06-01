#!/bin/bash

COUNT=0
DELAY=0.3
LIMIT=30
LABEL=""

#gettext() {
#  echo ""
#}
TEXT=" "
LENGTH=1
EXIT=1

PREV_STATUS="$TEXT"
getinfo() {
  TEXT_="$($HOME/Codes/bashtest/getplayerstatus.sh)"
  EXIT=$?
  [ "$TEXT_" == "$PREV_STATUS" ] && return 0

  LENGTH_=${#TEXT_}
  [ $LENGTH_ -eq 0 ] && LENGTH_=1
  if [ $LENGTH_ -gt 30 ]; then
    PREV_STATUS=$TEXT_
    TEXT_="${TEXT_} || ${TEXT_}"
    LENGTH_=$((LENGTH_+2))
  fi
  
  COUNT=0
  TEXT=$TEXT_
  LENGTH=$LENGTH_
}

#INFO=($(getinfo))
#echo ${INFO[0]}


while true; do
  LABEL=""
  getinfo
  [ $EXIT -eq 0 ] && LABEL=" "
  OFF=$((COUNT%LENGTH))
  TOP=$((LIMIT+OFF))
  VALUE=$(echo "$TEXT" | head -c $TOP | tail -c $LIMIT )
  echo "${LABEL}${VALUE}"
  sleep "$DELAY"
  COUNT=$((COUNT+1))
done
