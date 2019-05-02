#ifndef _SIGNAL_H_
#define _SIGNAL_H_

const char NOSTYLE[]= "\033[0m", ERROR[]= "\033[41m", SIG[]= "\033[42m",
           INFO[]= "\033[44m";

#define error(a) printf(ERROR),printf(a),printf(NOSTYLE),puts("")
#define sig(a) printf(SIG),printf(a),printf(NOSTYLE),puts("")
#define log(a) printf(a),puts("")
#define info(a) printf(INFO),printf(a),printf(NOSTYLE),puts("")

#endif
