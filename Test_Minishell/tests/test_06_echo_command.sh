#!/bin/bash
source ./test_structure.sh

# Définir des variables dynamiques
EXPECTED_HOME_PATH=$(echo ~)  # Récupère le chemin de l'utilisateur actuel
EXPECTED_HOME_WITH_WILDCARD=$(echo ~*)  # Récupère tous les chemins correspondants
EXPECTED_DYNAMIC_PATH=$(echo /Users/corentin*)  # Exemple pour les chemins dynamiques

# Tests liés aux quotes et espaces
run_test "echo \"hola\"\nexit\n" "hola" 0 "Double-quoted string"
run_test "echo 'hola'\nexit\n" "hola" 0 "Single-quoted string"
run_test "echo \"\"hola\nexit\n" "hola" 0 "Empty quotes followed by string"
run_test "echo ''hola''\nexit\n" "hola" 0 "Multiple single quotes"

# Tests liés aux commandes malformées
run_test "EechoE\nexit\n" "EechoE: command not found" 127 "Invalid command with extra E"
run_test ".echo.\nexit\n" ".echo.: command not found" 127 "Invalid command with dots"
run_test "e\"cho\" hola\nexit\n" "echo hola: command not found" 127 "Mixed quotes in command"

# Tests liés aux variables d'environnement
run_test "echo \$HOME\nexit\n" "$EXPECTED_HOME_PATH" 0 "Display HOME variable"
run_test "echo \$HOME*\nexit\n" "$EXPECTED_HOME_WITH_WILDCARD" 0 "HOME variable with wildcard"
run_test "echo /Users/corentin*\nexit\n" "$EXPECTED_DYNAMIC_PATH" 0 "Dynamic path with wildcard"

# Tests liés à `echo` et ses arguments
run_test "echo\nexit\n" "" 0 "Empty echo"
run_test "echo -n Hola\nexit\n" "Hola" 0 "Echo with -n"
run_test "echo -n -n -n\nexit\n" "" 0 "Echo with multiple -n"
run_test "echo hola \"bonjour\"\nexit\n" "hola bonjour" 0 "Echo with mixed quotes and arguments"

# Tests pour les métacaractères (non gérés)
run_test "echo > <\nexit\n" "syntax error near unexpected token '<'" 2 "Redirect metacharacters"
run_test "echo | |\nexit\n" "syntax error near unexpected token '|'" 2 "Pipe metacharacters"
run_test "echo -nnn \$hola\nexit\n" "" 0 "Echo with nonexistent variable"
run_test "echo \$*\nexit\n" "" 0 "Echo with variable substitution"

# Tests avancés avec quotes imbriquées
run_test "echo \"\\\"\nexit\n" "\\" 0 "Backslash in double quotes"
run_test "echo \"\\'\"\nexit\n" "'" 0 "Single quote escaped in double quotes"
run_test "echo \"\\\"\$DONTEXIST\"\nexit\n" "\"\"" 0 "Escaped quotes with nonexistent variable"

#===========================================================================#

run_test "ABC=hola\nexit\n" "" 0 "Variable assignment"
run_test "4ABC=hola\nexit\n" "4ABC=hola: command not found" 127 "Invalid variable assignment"
run_test "hola\nexit\n" "hola: command not found" 127 "Invalid command"
run_test "hola que tal\nexit\n" "bash: hola: command not found" 127 "Multiple commands"
run_test "Makefile\nexit\n" "bash: Makefile: command not found" 127 "Invalid command with Makefile"
run_test "echo\nexit\n" "" 0 "Empty echo"
run_test "echo -n\nexit\n" "-n" 0 "Echo with -n"
run_test "echo Hola\nexit\n" "Hola" 0 "Echo with argument"
run_test "echoHola\nexit\n" "echoHola: command not found" 127 "Invalid echo command"
run_test "echo-nHola\nexit\n" "echo-nHola: command not found" 127 "Invalid echo command with -n"
run_test "echo -n Hola\nexit\n" "-n Hola" 0 "Echo with -n and argument"
run_test "echo "-n" Hola\nexit\n" "-n Hola" 0 "Echo with -n and argument in quotes"
run_test "echo -nHola\nexit\n" "-nHola" 0 "Echo with -n and argument"
run_test "echo Hola -n\nexit\n" "Hola -n" 0 "Echo with argument and -n"
run_test "echo Hola Que Tal\nexit\n" "Hola Que Tal" 0 "Echo with multiple arguments"
run_test "echo         Hola\nexit\n" "Hola" 0 "Echo with multiple spaces"
run_test "echo    Hola     Que    Tal\nexit\n" "Hola Que Tal" 0 "Echo with multiple spaces"
run_test "echo      \n hola\nexit\n" "n hola" 0 "Echo with newline"
run_test "echo "         " | cat -e\nexit\n" "         $" 0 "Echo with spaces"
run_test "echo           | cat -e\nexit\n" "$" 0 "Echo with spaces and cat"
run_test """''echo hola""'''' que""'' tal""''\nexit\n" "hola que tal" 0 "Multiple quotes"
run_test "echo -n -n\nexit\n" "-n -n" 0 "Echo with multiple -n"
run_test "echo -n -n Hola Que\nexit\n" "-n -n Hola Que" 0 "Echo with multiple -n and arguments"
run_test "echo -p\nexit\n" "-p" 0 "Echo with -p"
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""
run_test "\nexit\n" "" 0 ""


		
$> echo -nnnnn				OK	OK	$>	0	
$> echo -n -nnn -nnnn				OK	OK	$>	0	
$> echo -n-nnn -nnnn				OK	OK	"-n-nnn -nnnn
$>"	0	
$> echo -n -nnn hola -nnnn				OK	OK	hola -nnnn$>	0	
$> echo -n -nnn-nnnn				OK	OK	-nnn-nnnn$>	0	
$> echo --------n				OK	OK	"--------n
$>"	0	
$> echo -nnn --------n				OK	OK	--------n$>	0	
$> echo -nnn -----nn---nnnn				OK	OK	-----nn---nnnn$>	0	
$> echo -nnn --------nnnn				OK	OK	--------nnnn$>	0	
$> echo $				OK	OK	"$
$>"	0	
$> echo $?				OK	OK	"0
$>"	0	Renvoie le code de retour du dernier pipeline exécuté à l'avant-plan
$> echo $?$				OK	OK	"0$
$>"	0	
$> echo $? | echo $? | echo $?				OK	OK	"0
$>"	0	
$> echo $:$= | cat -e				OK	OK	"$:$=$
$>"	0	
$> echo " $ " | cat -e				OK	OK	" $ $
$>"	0	
$> echo ' $ ' | cat -e				OK	OK	" $ $
$>"	0	
$> echo $HOME				OK	OK	"/home/vietdu91
$>"	0	
$> echo \$HOME				OK	OK	"$HOME
$>"	0	
$> echo my shit terminal is [$TERM]				OK	OK	"my shit terminal is [xterm-256color]
$>"	0	
$> echo my shit terminal is [$TERM4				OK	OK	"my shit terminal is [
$>"	0	
$> echo my shit terminal is [$TERM4]				OK	OK	"my shit terminal is []
$>"	0	
$> echo $UID				OK	OK	"1000
$>"	0	
$> echo $HOME9				OK	OK	"
$>"	0	Marche pour tous les caractères alphanumériques de l'ASCII
$> echo $9HOME				OK	OK	"HOME
$>"	0	
$> echo $HOME%				OK	OK	"/home/vietdu91%
$>"	0	Marche pour les autres caractères (ponctuation, caractères non-ASCII, etc.)
$> echo $UID$HOME				OK	OK	"1000/home/vietdu91%
$>"	0	
$> echo Le path de mon HOME est $HOME				OK	OK	"Le path de mon HOME est /home/vietdu91
$>"	0	
$> echo $USER$var\$USER$USER\$USERtest$USER				OK	OK	"vietdu91$USERvietdu91$USERtestvietdu91
$>"	0	"A ne pas gerer si '\' non gere :
Doit sortir : vietdu91vietdu91vietdu91vietdu91"
$> echo $hola*				OK	OK	"
$>"	0	Cas d'un variable inexistant
$> echo -nnnn $hola				OK	OK	$>	0	
$> echo > <				OK	OK	"bash: syntax error near unexpected token `<'
$>"	2	
$> echo | |				OK	OK	"bash: syntax error near unexpected token `|'
$>"	2	
$> EechoE				OK	OK	"bash: EechoE: command not found
$>"	127	
$> .echo.				OK	OK	"bash: .echo.: command not found
$>"	127	
$> >echo>				OK	OK	"bash: syntax error near unexpected token `newline'
$>"	2	
$> <echo<				OK	OK	"bash: syntax error near unexpected token `newline'
$>"	2	
$> >>echo>>				OK	OK	"bash: syntax error near unexpected token `newline'
$>"	2	
$> |echo|				OK	OK	"bash: syntax error near unexpected token `|'
$>"	2	
$> |echo -n hola				OK	OK	"bash: syntax error near unexpected token `|'
$>"	2	
$> echo *	NON GERE			OK	OK	"crashtest.c  Docs  Dockers  Drawings  Makefile  minishell  philosophers  srcs  test.c
$>"	0	[BONUS]
$> echo '*'	NON GERE			OK	OK	"*
$>"	0	Marche aussi pour les double quotes
$> echo D*	NON GERE			OK	OK	"Docs Dockers Drawings
$>"	0	[BONUS]
$> echo *Z	NON GERE			OK	OK	"*Z
$>"	0	[BONUS]
$> echo *t hola	NON GERE			OK	OK	"crashtest.c test.c hola
$>"	0	[BONUS]
$> echo *t	NON GERE			OK	OK	"crashtest.c test.c
$>"	0	[BONUS]
$> echo $*	NON GERE			OK	OK	"
$>"	0	[BONUS]
$> echo hola*hola *	NON GERE			OK	OK	"hola*hola crashtest.c  Docs  Dockers  Drawings  Makefile  minishell  philosophers  srcs  test.c
$>"	0	[BONUS]
$> echo $hola*	NON GERE			OK	OK	"crashtest.c  Docs  Dockers  Drawings  Makefile  minishell  philosophers  srcs  test.c
$>"	0	[BONUS]
$> echo $HOME*	NON GERE			OK	OK	"/home/vietdu91
$>"	0	[BONUS]
$> echo $""				OK	OK	"
$>"	0	
$> echo "$"""				OK	OK	"$
$>"	0	
$> echo '$'''				OK	OK	"$
$>"	0	
$> echo $"HOME"				OK	OK	"HOME
$>"	0	
$> echo $''HOME				OK	OK	"HOME
$>"	0	
$> echo $""HOME				OK	OK	"HOME
$>"	0	
$> echo "$HO"ME				OK	OK	"ME
$>"	0	
$> echo '$HO'ME				OK	OK	"$HOME
$>"	0	
$> echo "$HO""ME"				OK	OK	"ME
$>"	0	
$> echo '$HO''ME'				OK	OK	"$HOME
$>"	0	
$> echo "'$HO''ME'"				OK	OK	"''ME'
$>"	0	⚠️ Il y a bien 3 singles quotes avant le ME. Je ne sais pas pourquoi Excel tronque à l'affichage le 3e quote
$> echo ""$HOME				OK	OK	"/home/vietdu91
$>"	0	
$> echo "" $HOME				OK	OK	" /home/vietdu91
$>"		
$> echo ''$HOME				OK	OK	"/home/vietdu91
$>"	0	
$> echo '' $HOME				OK	OK	" /home/vietdu91
$>"		
$> echo $"HO""ME"				OK	OK	"HOME
$>"	0	
$> echo $'HO''ME'				OK	OK	"HOME
$>"	0	
$> echo $'HOME'				OK	OK	"HOME
$>"	0	
$> echo "$"HOME				OK	OK	"$HOME
$>"	0	
$> echo $=HOME				OK	OK	"$=HOME
$>"	0	
$> echo $"HOLA"				OK	OK	"HOLA
$>"	0	
$> echo $'HOLA'				OK	OK	"HOLA
$>"	0	
$> echo $DONTEXIST Hola				OK	OK	"Hola
$>"	0	Le cas ou la variable n'existe pas et n'est pas importee
$> echo "hola"				OK	OK	"hola
$>"	0	
$> echo 'hola'				OK	OK	"hola
$>"	0	
$> echo ''hola''				OK	OK	"hola
$>"	0	
$> echo ''h'o'la''				OK	OK	"hola
$>"	0	
$> echo "''h'o'la''"				OK	OK	"'h'o'la''
$>"	0	
$> echo "'"h'o'la"'"				OK	OK	"hola'
$>"	0	
$> echo"'hola'"				OK	OK	"bash: echo'hola': command not found
$>"	0	
$> echo "'hola'"				OK	OK	"'hola'
$>"	0	
$> echo '"hola"'				OK	OK	"""hola""
$>"	0	
$> echo '''ho"''''l"a'''				OK	OK	"ho""l""a
$>"	0	
$> echo hola""""""""""""				OK	OK	"hola
$>"	0	
$> echo hola"''''''''''"				OK	OK	"hola''''''''''
$>"	0	
$> echo hola''''''''''''				OK	OK	"hola
$>"	0	
$> echo hola'""""""""""'				OK	OK	"hola""""""""""""""""""""
$>"	0	
$> e"cho hola"				OK	OK	"bash: echo hola: command not found
$>"	127	
$> e'cho hola'				OK	OK	"bash: echo hola: command not found
$>"	127	
$> echo "hola     " | cat -e				OK	OK	"hola     $
$>"	0	
$> echo ""hola				OK	OK	"hola
$>"	0	
$> echo "" hola				OK	OK	" hola
$>"	0	
$> echo ""             hola				OK	OK	" hola
$>"	0	
$> echo ""hola				OK	OK	"hola
$>"	0	
$> echo "" hola				OK	OK	" hola
$>"	0	
$> echo hola""bonjour				OK	OK	"holabonjour
$>"	0	
$> "e"'c'ho 'b'"o"nj"o"'u'r				OK	OK	"bonjour
$>"	0	
$> ""e"'c'ho 'b'"o"nj"o"'u'r"				OK	OK	"bash: e'c'ho 'b'onjo'u'r: command not found
$>"	127	
$> echo "$DONTEXIST"Makefile				OK	OK	"Makefile
$>"	0	
$> echo "$DONTEXIST""Makefile"				OK	OK	"Makefile
$>"	0	
$> echo "$DONTEXIST" "Makefile"				OK	OK	" Makefile
$>"	0	Attention a l'espace avant