## Dictionary

I finished writing the list of words a few hours ago but I realize now that I just made a dictionary program you could
use to look up the words.

#### Esperanto grammar abridged

Nouns end with -o for the subject and anything adverbial and -on for the direct object.
Adjectives end with -a or -an depending on the noun it's tied to.
Adverbs normally end with -e and rarely with -en to indicate movement.

Adjectives may be in front of the noun, like in English, or behind the noun, like in French.
There's no strict rule to it, it goes wherever you want it to.

Plurals end with -oj instead of -o.
In Esperanto “j” is pronounced like “y“ in “yes”, the way it is in most European languages.
I'll omit how all the other letters are pronounced as for my code you'll only need to be able to read.

Infinitives end with -i, present tense with -as, future with -os, past with -is.
In my code you will almost always see verbs in the imperative mood which ends with -u.

#### Interrogatives

| epo | eng |
|-----|-----|
|ĉu   |introduces a yes/no question|
|kio  |what |
|kiu  |who, which|
|kial |why  |
|kiam |when |
|kie  |where|

#### Suffixes I frequently use

| epo | eng |
|-----|-----|
|-ega |large |
|-eta |small |
|-ujo |container |
|-aro |collection |
|-ilo |tool |
|-ejo |a place for something, e.g. “lernejo” is a place to learn: a school|
|-anta|actively doing something, e.g. “la parolanta viro” means “the speaking man”|
|-anto|someone or something actively doing something|
|-ata |having something done to them, e.g. “la ĵetata viro” means “the man being thrown”|
|-ato |someone or something having something done to them|

-anta etc. have variants for future and past tense: -onta and -inta. Out of those I only use -ita often.

#### Prefixes I frequently use

| epo | eng  |
|-----|------|
|mal- |the opposite, e.g. “malbona” means “bad” (“bona” means “good”)|
|ĉef- |main  |
|cel- |target|
|font-|source|

#### Prepositions I frequently use

| epo | eng |
|-----|-----|
|en   |in   |
|el   |from |
|de   |of   |
|al   |to   |
|dum  |while|

#### Words I frequently use

I've omitted all words whose meaning is easy to guess.

| epo       | eng        | note  |
|-----------|------------|-------|
|donu       |give        | _Used for “get” methods. I think “give” makes more sense because I write method names from the perspective of their class._ |
|agordu     |set         ||
|agordo     |setting     ||
|havi       |to have     ||
|enhavi     |to contain  ||
|prenu      |take        ||
|forprenu   |remove      ||
|elprenu    |take out of | _I usually use this when a function removes and returns something._ |
|provu      |try         | _I usually use this to indicate that a function can fail without throwing._ |
|dosierujo  |folder      | _dosiero (file) + ujo (container)_ |
|klako      |click       ||
|klavo      |keyboard key||
|klavligo   |hotkey      | _Ligo means “link”._ |
|granda     |large       ||
|nova       |new         ||
|plena      |full        ||
|plenigi    |to fill     ||
|komencu    |start       ||
|haltu      |stop        ||
|uzi        |to use      ||
|trakti     |to handle   ||
|montri     |to show     ||
|desegni    |to draw     ||
|aranĝi     |to arrange  ||
|koni       |to know     ||
|rekoni     |to recognize||
|ŝarĝi      |to load     ||
|konservi   |to save     ||
|ludi       |to play     | _Both in the sense of “play with a ball” and “play a video”._ |
|ekrano     |screen, monitor ||
|bildo      |picture     ||
|legi       |to read     ||
|wortaro    |dictionary  | _worto (word) + aro (collection)_ |
|difino     |definition  ||
|linguo     |language    ||
|supra      |upper       ||
|suba       |lower       ||
|dextra     |right       ||
|liva       |left        | _Others almost always use “maldekstra”._ |
|io         |something   ||
|ie         |somewhere   ||
|iam        |sometime    ||
|iom        |somewhat    ||
|tio        |that        ||
|tie        |there       ||
|tiam       |then        ||
|tiom       |that much   | _I included this for completeness but I don't think I ever used it in my code_ |
|kaj        |and         ||
|aŭ         |or          ||
|verŝajne   |probably    ||
|qŭankam    |however     ||
|ankaŭ      |also        ||
|ankoraŭ    |still       ||
|jam        |already     ||
|se, te     |if, then    ||

Please mention in an issue if there's any other word you can't figure out.

If you need to translate a word into Esperanto I recommend reta-vortaro.de. Reta Vortaro provides the actual definitions
in Esperanto however, which will be difficult to follow with little experience. Nonetheless it's important to look at
the definitions and not just the translations to ensure you get the right semantic. After all, if a word has multiple
definitions in English, other languages may use different words for specific definitions. I myself learned the hard
way that anglophones are less inclined to sit on a bank than the Dutch.

#### Differences from normal Esperanto

The Esperanto I use in my code differs a bit from normal Esperanto because I was going to make a formally defined
Esperantido (Esperanto-derived constructed language) but never got around to actually making the formal definition.
Reason for the Esperantido is that Esperanto's grammar is a bit minimal. Formally it's sixteen rules that vaguely
describes the language by describing how it differs from other European languages, but it doesn't scratch the surface of
Esperanto's actual grammar. I was thinking of making a formally defined Esperantido, which would be almost entirely like
Esperanto but with a full formal definition, to the point where it would be possible to make an algorithm that could
completely consistently check whether a sentence is grammatically cohesive, of course neglecting semantics. I got plenty
of ideas over time but spent little time actually working on this large undertaking. As such I've more or less left it
by the wayside, but not without applying my vague grammatical ideas to my codebases.

Here's a pretty much exhaustive list of differences from normal Esperanto:
 - “kv” is “qŭ” because it's more recognizable. E.g. “freqŭenco” instead of “frekvenco”.
 - I use “w” and “x”, which are “v” and “ks” in normal Esperanto.
 - I use “se ... te ...” instead of the usual “se ... tiam ...”.
 - I use “-es” for the genitive case, and use “mies” etc. instead of “mia” for consistency.
 - Since recently I use “-ora” as comparative and “-ima” as superlative suffix, e.g. “bonoran” instead of “pli bonan”
 - I write “ĝi estas bela**n**” instead of “ĝi estas bela”.

My code isn't always perfectly consistent in this because I come up with these things as I go, and some of the code is
from earlier projects.