import pexpect
import subprocess
import unittest
import re
import sys

# ANSI color codes (macOS compatible)
GREEN = '\x1b[32m'
RED = '\x1b[31m'
RESET = '\x1b[0m'
CHECK = '✓'
CROSS = '✗'

def format_test_result(command, success):
    return f"{command:30} {GREEN if success else RED}{CHECK if success else CROSS}{RESET}"

class ShellTest(unittest.TestCase):
    PROMPT = 'minishell: '
    TIMEOUT = 3  # seconds

    def setUp(self):
        self.shell = pexpect.spawn('./minishell', encoding='utf-8')
        self.shell.expect(self.PROMPT, timeout=self.TIMEOUT)

    def tearDown(self):
        self.shell.sendline('exit')
        self.shell.close()

    def run_command(self, command):
        self.shell.sendline(command)
        self.shell.expect(self.PROMPT, timeout=self.TIMEOUT)
        raw_output = self.shell.before
        minishell_output = self.clean_output(raw_output, command)
        try:
            bash_output = subprocess.check_output(['bash', '-c', command], stderr=subprocess.STDOUT, text=True).strip()
        except subprocess.CalledProcessError as e:
            bash_output = e.output.strip()
            
        return minishell_output, bash_output

    def clean_output(self, output, command):
        output = re.sub(r'\x1b\[[?0-9;]*[A-Za-z]', '', output)  # Remove ANSI sequences
        output = output.replace(command + '\r\n', '').strip()  # Remove command echo
        return output

    def test_commands(self):
        with open('./test/commands_correction.txt', 'r') as file:
            commands = [line.strip() for line in file.readlines()]
        max_cmd_length = max(len(cmd) for cmd in commands)
        for cmd in commands:
            with self.subTest(cmd=cmd):
                minishell_output, bash_output = self.run_command(cmd)
                if minishell_output == bash_output:
                    print(f"command: {cmd:<{max_cmd_length*2}} {GREEN}OK{RESET}")
                else:
                    print(f"command: {cmd:<{max_cmd_length*2}} {RED}KO{RESET}\
                          \n\nBash:\n-----\n{bash_output}\n\nMinishell:\n----------\n{minishell_output}\n")

if __name__ == '__main__':
    with open('./test/test_output.txt', 'w') as f:
        sys.stdout = f # Redirect print statements to file
        runner = unittest.TextTestRunner(stream=f, verbosity=2)
        unittest.main(testRunner=runner, exit=False)