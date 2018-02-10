+ ---------------------------------------------------------------------------- +

/* left */

- norminette
- check leaks, segfault
- implement pipe, redirections, here-document, and-if, or-if
- separateur `;`
- ajouter TOKEN_IO_NUMBER
- adapter l'environ par default en cas de `env -i sh` (ne quitte pas)
	-> check_tty() -> change getenv() call

- sur quel fd write le prompt (stderr?)? et l'input?
- check ctrl + c pdt le multi ligne quotes
- multiline a cause des quotes a revoir, pb compatibilite input_get()/tokenizer()
- ...

+ ---------------------------------------------------------------------------- +

/* doc */

	Analyse lexicale:
Convertir (découper) une chaîne de caractères en une liste de symboles (tokens).
Ces symboles sont ensuite consommés lors de l'analyse syntaxique.

	Analyseur lexical (lexer):
Un programme réalisant une analyse lexicale.
Un lexer est généralement combiné à un analyseur syntaxique (parser) pour analyser la syntaxe d'un texte.

	Analyse syntaxique:
Consiste à mettre en évidence la structure d'un texte.
Elle fait habituellement suite à une analyse lexicale, et sert à son tour de préalable à une analyse sémantique.

	Analyseur syntaxique (parser):
Un programme réalisant une analyse syntaxique.

	Analyse semantique:
La phase d'analyse de la chaine de caracteres qui en établit la signification en utilisant le sens des éléments du texte.

	Interprete (interpreter):
Outil ayant pour tâche d'analyser, de traduire et d'exécuter les programmes écrits dans un langage informatique.
Il se distingue d’un compilateur par le fait que, pour exécuter un programme, les opérations d’analyse et de traductions sont réalisées à chaque exécution du programme (par un interpréteur) plutôt qu’une fois pour toutes (par un compilateur).

	Arbre de syntaxe abstraite (abstract syntax tree / AST):
Un arbre dont les nœuds internes sont marqués par des opérateurs et dont les feuilles (ou nœuds externes) représentent les opérandes de ces opérateurs.

+ --- +

	Here-Document (`<<')
syntax: [fd]<<word        (si pas de fd, fd = stdin)
		  here-document
		delimiter

-> garde en memoire le premier mot apres `<<', puis boucle
jusqu'a obtenir ce mot exact, et uniquement lui
-> The here-document shall be treated as a single word
that begins after the next <newline> and continues until
there is a line containing only the delimiter and a <newline>,
with no <blank> characters in between.
Then the next here-document starts, if there is one.

+ ---------------------------------------------------------------------------- +
