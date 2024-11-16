import sys
import re

def clean_output(input_file, output_file):
    cleaned_lines = []
    ansi_escape = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')  # Regex to match ANSI escape codes

    try:
        with open(input_file, 'r') as infile:
            for line in infile:
                # Remove ANSI color codes
                line = ansi_escape.sub("", line).strip()
                # Remove the Minishell prompt
                if "Test_Minishell (Minishell)" in line:
                    line = line.replace("➜  Test_Minishell (Minishell) :", "").strip()
                # Ignore empty lines and lines with 'exit'
                if line and "exit" not in line:
                    cleaned_lines.append(line)
    except FileNotFoundError:
        print(f"Error: Input file '{input_file}' not found.")
        sys.exit(1)
    except PermissionError:
        print(f"Error: Permission denied for file '{input_file}'.")
        sys.exit(1)

    # Write the cleaned lines to the output file
    with open(output_file, 'w') as outfile:
        outfile.write("\n".join(cleaned_lines))

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 clean_output.py <input_file> <output_file>")
        sys.exit(1)
    clean_output(sys.argv[1], sys.argv[2])