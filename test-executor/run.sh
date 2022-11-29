#/bin/bash
./test
strace -e trace=clone -o /dev/null -e fault=clone:when=2:error=EAGAIN ./test_sysfail test_2C_2nd_fork_fail
strace -e trace=pipe -o /dev/null -e fault=pipe:when=1:error=ENFILE ./test_sysfail test_2C_pipe_fail
strace -e trace=getcwd -o /dev/null -e fault=getcwd:when=1:error=ENOENT ./test_sysfail test_builtin_pwd_fail
