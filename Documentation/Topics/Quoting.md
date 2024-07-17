# Quoting

## Examples
```bash
bash-3.2$ VAR=2
bash-3.2$ echo VAR
VAR
bash-3.2$ echo $VAR
2
bash-3.2$ echo "$VAR"
2
bash-3.2$ echo '$VAR'
$VAR
bash-3.2$ echo "'$VAR'"
'2'
bash-3.2$ echo '"$VAR"'
"$VAR"
bash-3.2$ echo "'"$VAR"'"
'2'
bash-3.2$ echo ""'"$VAR"'""
"$VAR"
bash-3.2$ echo """'"$VAR"'"""
'2'
bash-3.2$ echo """"'"$VAR"'""""
"$VAR"
bash-3.2$ echo '"""'"$VAR"'"""'
"""2"""
bash-3.2$ echo '""''"$VAR'""'"'
"""$VAR"
bash-3.2$ echo '"'"'"'"$VAR'""'"'"'"
"'"$VAR"'
```

- Manual decomposition:
```bash
bash-3.2$ echo "'$VAR'"
'2'
```
=> Between double quotes, so parameter expanded

```bash
bash-3.2$ echo '"$VAR"'
"$VAR"
```
=> Between double quotes, so should be expanded, but all this is between single quotes, thus literal value of each character, including the double quotes

```bash
bash-3.2$ echo "'"$VAR"'"
'2'
```
=> From left to right:
1. `"'"` => `'`
2. `$VAR` => `2`
3. `"'"` => `'`

```bash
bash-3.2$ echo ""'"$VAR"'""
"$VAR"
```
=> From left to right:
1. `""` => {}
2. `'"$VAR"'` => `"$VAR"`
3. `""` => {}

```bash
bash-3.2$ echo '"'"'"'"$VAR'""'"'"'"
"'"$VAR"'
```
=> From left to right:
1. `'"'` => `"`
2. `"'"` => `'`
3. `'"$VAR'` => `"$VAR`
4. `""` => {}
5. `'"'` => `"`
6. `"'"` => `'`