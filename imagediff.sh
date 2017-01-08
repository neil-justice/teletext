#!/bin/bash
# This script requires ImageMagick to be installed.  To install it, run 
# 'apt-get install imagemagick'.  It compares 2 images, FILE and TESTFILE. 
# Depending on the mode, it either produces a PNG diff image, where the red 
# pixels indicate a difference between the two images and the white pixels 
# indicate the two files have the same colour pixel in that location, or it 
# returns a count of the number of different pixels.  The two files compared are
# 1) the most recent file in the screenshots directory, and
# 2) test_m7.gif
SHOTDIR='screenshots/'
TESTDIR='testfiles/'
DOCSDIR='docs/'
FILE=$(ls screenshots -rt1 | tail -1)
DATE=${FILE:6:17}
TESTFILE='test_m7.gif'
PNG='diff_'${DATE}'.png'
CMD='compare'
OPT='-compose src'
# Checks if CMD can be run
if ! type "$CMD" > /dev/null 2>&1; then
  echo "ERROR: This script requires ImageMagick to be installed."
else
  # Creates a timestamped .PNG file in DOCSDIR.  the PNG is a diff of the test image 
  # and the most recent file in the screenshot directory.  Red pixels mark
  # differences in the file, and white pixels mark matches.
  if [ ! -f "$DOCSDIR""$PNG" -a "$1" == "" ]; then
    eval $(echo "$CMD" "$SHOTDIR""$FILE" "$TESTDIR""$TESTFILE" "$OPT" "$DOCSDIR""$PNG")
    echo "New .PNG diff created between latest screenshot and "$TESTFILE""
  elif [ "$1" == "" ]; then 
    echo "A .PNG diff already exists between the latest screenshot and "$TESTFILE"."
    echo "It is: "$DOCSDIR""$PNG""
  fi
  # When the script is run with this argument, no PNG is created.  Instead the
  # number of different pixels between the two images is returned.
  if [ "$1" == "-p" ]; then
    WRONGPIXELS=$(eval $(echo "$CMD" '-metric AE' "$SHOTDIR""$FILE" "$TESTDIR""$TESTFILE" 'null: 2>&1'))
    echo "$WRONGPIXELS"
  fi
fi