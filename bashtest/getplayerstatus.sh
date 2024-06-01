#!/bin/bash

#use plyerctl -l to find name
PLAYER="spotify"
STATUS="$(playerctl --player=$PLAYER status 2>/dev/null)"
#OUTCOMES: "Playing", "Paused", "Stopped", "Error[exit1]"
#EXIT=$? #exit code of prev

#if [ $EXIT -eq 0 ]; then
  #STATUS=$STATUS
#else
  #STATUS=" "
#fi

if [ "$STATUS" == "Stopped" ]; then
  echo "NO MUSIC"
  exit 1
elif [ "$STATUS" == "Paused" ]; then
  echo "$(playerctl --player=$PLAYER metadata title)"
  exit 0
elif [ "$STATUS" == "Playing" ]; then
  echo "$(playerctl --player=$PLAYER metadata title)"
  exit 0
else
  echo ""
  exit 1
fi

