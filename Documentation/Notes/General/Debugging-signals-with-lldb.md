make debug
lldb ./minishell
_regexp-display g_signal
_regexp-display rl_done

In different terminal:
ps to get PID (nb: we want "minishell" and not "lldb ./minishell")
kill -SIGINT <PID>

Then in LLDB terminal:
- n to step, c to continue (until breakpoints)