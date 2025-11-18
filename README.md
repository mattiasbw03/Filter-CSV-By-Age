Filter CSV by Age
Denne opgave går ud på at skrive et C-program, der kan filtrere personer ud fra en CSV-fil baseret på en maksimal alder, som brugeren angiver i terminalen. En CSV-fil består af linjer med navne og aldersværdier adskilt af et komma, f.eks.:
Anna, 12.
Programmet skal læse filen linje for linje, tjekke at hver linje er gyldig, udskrive fejl for ugyldige linjer, og kun sende de gyldige linjer videre, hvor alderen er mindre end eller lig med den grænse, brugeren har angivet. Programmet skal samtidig kunne læse input enten fra en fil eller fra standard input (stdin), og det skal kunne skrive output både til en fil og til terminalen.
I koden bliver maks-alderen hentet som et kommandolinje-argument via argv[1]. Hvis brugeren f.eks. skriver:
./filter-csv-by-age.exe 15 people.csv out.csv

så bliver 15 den maksimale alder, som programmet filtrerer efter. Herefter åbner programmet inputfilen, eller bruger stdin hvis ingen fil er angivet. Programmet læser én linje ad gangen med fgets, opdeler den med strtok i navn og alder, og kontrollerer om linjen er korrekt formateret. Hvis der mangler alder, hvis linjen er tom, eller hvis alderen ikke kan konverteres til et tal, udskrives en fejlmeddelelse til stderr, og linjen springes over.
Når programmet møder en gyldig linje og alderen er mindre end eller lig med grænsen, skrives linjen videre til output – enten til en fil eller til stdout. På den måde bliver kun de personer, der opfylder filteret, gemt i den endelige outputfil. Programmet afsluttes ved at lukke eventuelle åbne filer og returnere succes.
