#!/bin/sh

DATE="$(date)"
AUTHOR="Marcel Guzik"
GROUP="środa parzysta"


# TODO: replace naive first line check with regex expression,
# fixing the command if invalid
FILENAME=$1
if [ "$FILENAME" = "" ]
then
    echo "gimme the name of the file ya meatbag"
    exit
fi

if [ "$(head -n1 $FILENAME)" != '/*' ]; then
    CREDS="\tAutor: $AUTHOR\n\tGrupa: $GROUP\n\tData: $DATE\n"
    COMMENT="/*\n$CREDS*/\n"
    printf "$COMMENT\n%s" "$(cat $FILENAME)" > $FILENAME
fi
