# ADC-interrupts-buttonDebounceAVRprogramming
Built in systems and Architecture

Labben går i stora drag ut på att dels använda ADC-enheten på Arduinon för att läsa av en potentiometer, en 
digitalingång för att läsa av en knapp, och dels använda timer/compare-enheter för att takta systemet. Interrupt ska 
användas, busy wait-loopar lämnar vi bakom oss!
Syftet med det är i första hand att bekanta dig med ADCn, interrupts, problematik som kan uppstå vid knappavläsning (knappstuds – fenomenet förekommer dock i fler elektromekaniska komponenter). Vi övar också 
elschemaläsning.
Du tillhandahålls en ’baseline’ med nödvändiga byggscript och källkodsfiler — utgå från den när du löser labben. 
Du får även ut en uppsättning nödvändiga elektronikkomponenter. Arduino UNO R3 samt kopplingsdäck och 
kablar tillhandahåller du själv. Du tillhandahålls också en uppsättning scheman och relevanta datablad.

1.4.1 DELUPPGIFT 1: KOPPLA UPP FÖLJANDE TRE KRETSAR PÅ DITT 
KOPPLINGSDÄCK
Labben är i grunden tänkt att kopplas upp enligt ovan ”av skäl”. Kan du lista ut varför?
Om du ändå tänker använda din egen shield till den här labben bör du tänka både en och två gången hur / 
varför det skulle / inte skulle funka. Du e smart. Du listar nog ut varför jag tar upp det här…
Om du till slut ändå bestämmer dig för att använda din sköld ”till vissa delar” av den här labben ska det 
framgå tydligt i readme.txt, kommentarer och commits hur och varför du gjort det. Det blir väldigt svårt 
för mig att rätta din uppgift annars…

1.4.2 DELUPPGIFT 2: LÄS AV DIGITALINGÅNG
1. Konfigurera upp pinne PD2 som ingång, som använder ett externt pulldown motstånd.
2. Skriv, och anropa periodiskt, en funktion som läser av pinnen och skriver ut ’pushed\r\n’ 
och ’released\r\n’ på UARTen när knappen trycks in, respektive släpps upp. Meddelandena 
ska baraskrivas ut en gång per knapptryck
3. Städa upp din kod och skapa en git-commit med ovanstående.
1.4.3 DELUPPGIFT 3: LÄS SPÄNNING MED HJÄLP AV ADCN
1. Konfigurera upp ADC-enheten mha kap 28 i databladet:
• Single conversion
• Bit-data, vänsterjusterat
• Prescaler = 8, referensspänning VCC
• Använd kanal ADC0
2. Skriv en avbrottshanterare för ’ADC conversion complete’, och i den, läs ut ADC-värdet och 
spara undan det i en global variabel
3. Konfigurera upp timer0 i Fast PWM-mod på samma sätt som i labb 2
• Fast PWM-mod, 255 som TOP, prescaler = 64
4. Konfigurera upp timer2 i CTC-mod på samma sätt som i labb 2, men slå på interrupts för 
compare match, och använd inte busy wait-loopar
• CTC-mod, 100 Hz, prescaler 1024, ’clear on match/set on bottom’
• Skriv en avbrottshanterare för compare match A, och i den, starta en ADComvandling, och skriv föregående ADC-värde (sparat i variabeln) till OCR0A
5. Städa upp din kod och skapa en git-commit med ovanstående.
Förväntat beteende: potentiometern kan användas för att styra ljusstyrkan på LEDen. Moturs 
bottenläge = helt släckt, medurs bottenläge = helt på
Fortsättning →

1.4.4 DELUPPGIFT 4 (VG-KRAV): ANVÄNDARSTYRT BETEENDE
1. Kombinera koden från de två föregående deluppgifterna, och ändra den så att följande beteende
uppnås:
• 10ms-timern används också för att periodiskt läsa av knappen
• När knappen tryckts in och sedan släppts upp helt, växlar LEDen beteende mellan 
följande moder, i den angivna sekvensen:
1. Pulserande, med hjälp av simple_ramp-funktionen från labb 2 (Utgångsläge vid
reset/uppstart)
2. Potentiometerstyrd, med hjälp av deluppgift 2
3. Blinkande av/på, i ca 1 Hz
4. Släckt
2. Beteendet implementeras med fördel med hjälp av en tillståndsmaskin
3. Delay-funktioner ska ej användas, ej heller busy-wait på flaggor för timers eller ADC
4. Tänk på att avbrottsrutinen ska exekvera minimalt med kod
5. Städa upp din kod och skapa en git-commit med ovanstående
