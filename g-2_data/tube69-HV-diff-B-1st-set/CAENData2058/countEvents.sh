

 bcnt=`wc -c TR_0_0.dat | cut -f 1 -d ' ' `
 python -c "print $bcnt / 4096."
