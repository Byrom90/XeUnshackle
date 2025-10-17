#include "stdafx.h"

// IMPORTANT NOTE!!!
// The standard font used by this app DOES NOT support the characters required for some languages.
// Unfortunately I have no idea how to create a new font that does.

// Localised language support - Credit FreeMyXe, this is how it's handled there.
LocalisationMessages_t english = {
    // Error Messagebox
    L"Unfortunately an error occurred while running Stage %i\n\nApp will now exit",
    L"Understood",
    // Dashlaunch load status
    L"Dashlaunch: Loaded! %ls",
    L"[HDD mode]",
    L"[USB mode] DO NOT UNPLUG THE USB!",
    L"Dashlaunch: FAILED! - Failed to write lhelper.xex. Section data error!",
    L"Dashlaunch: FAILED! - Failed to write lhelper.xex. Mount error!",
    L"Dashlaunch: FAILED! - Failed to write lhelper.xex to storage device.",
    L"Dashlaunch: FAILED! - Failed to load launch.xex. Section data error!",
    L"Dashlaunch: FAILED! - Status: %X",
    // Dump 1BL Notify
    L"[Dump1blRomToFile] FAILED! Non-zero result from Hvx...",
    L"Saved to %S-1bl.bin",
    L"[Dump1blRomToFile] FAILED! Failed to write file...",
    // Save Console Info Notify
    L"Saved to ConsoleInfo.txt",
    L"Saving Failed!",
    // Save Orig MAC
    L"Original MAC dumped to OriginalMACAddress.bin",
    L"Failed to dump original MAC!",
    // Main Screen Text
    L"All patches have now been applied!\nRegular JTAG/RGH functionality should now be possible on your system.\n\nTHIS IS NOT PERSISTENT!\nYour console will return to a completely stock unmodified state once shut down.\nIt is HIGHLY recommended that you now go dump a copy of your nand!",
    L"Any plugins set in launch.ini will load when you exit this app.\nLiveBlock should be working now if enabled in the launch.ini.\nPlug in your ethernet cable before exiting to allow stealths to authenticate correctly.",
    GLYPH_X_BUTTON L" Save info to file",
    GLYPH_Y_BUTTON L" Dump 1BL to file",
    L"Press " GLYPH_BACK_BUTTON L" to exit"
};

LocalisationMessages_t spanish = {
    L"Lamentablemente ocurrió un error al ejecutar Stage %i\n\nLa aplicación ahora se cerrará",
    L"Comprendido",
    // Dashlaunch load status
    L"Dashlaunch: ¡Cargado! %ls",
    L"[Modo HDD]",
    L"[Modo USB] ¡NO DESCONECTE EL USB!",
    L"Dashlaunch: ¡FALLÓ! - No se pudo escribir lhelper.xex. ¡Error en los datos de la sección!",
    L"Dashlaunch: ¡FALLÓ! - No se pudo escribir lhelper.xex. ¡Error de montaje!",
    L"Dashlaunch: ¡FALLÓ! - No se pudo escribir lhelper.xex en el dispositivo de almacenamiento.",
    L"Dashlaunch: ¡FALLÓ! - No se pudo cargar launch.xex. ¡Error en los datos de la sección!",
    L"Dashlaunch: ¡FALLÓ! - Estado: %X",
    // Dump 1BL Notify
    L"[Dump1blRomToFile] ¡FALLÓ! Resultado distinto de cero de Hvx...",
    L"Guardado en %S-1bl.bin",
    L"[Dump1blRomToFile] ¡FALLÓ! No se pudo escribir el archivo...",
    // Save Console Info Notify
    L"Guardado en ConsoleInfo.txt",
    L"¡Error al guardar!",
    // Save Orig MAC
    L"MAC original volcada a OriginalMACAddress.bin",
    L"No se pudo volcar el original MAC!",
    // Main Screen Text
    L"¡Todos los parches han sido aplicados!\nLa funcionalidad JTAG/RGH regular ahora debería ser posible en tu sistema\n\nESTO NO ES PERMANENTE!\nTu consola volverá a un estado completamente original y sin modificaciones\nuna vez que se apague la consola\nSe recomienda altamente que ahora hagas una copia de seguridad de tu NAND!",
    L"Cualquier complemento configurado en launch.ini se cargará cuando salgas de esta aplicación\nLiveBlock debería estar funcionando ahora si está habilitado en launch.ini.\nConecta tu cable de Internet antes de salir para permitir que los servicios\nque necesiten autenticación lo hagan correctamente",
    GLYPH_X_BUTTON L" Guardar información",
    GLYPH_Y_BUTTON L" Volcar 1BL",
    L"Presionar " GLYPH_BACK_BUTTON L" para salir"
};

LocalisationMessages_t canadian_french = {
// Error Messagebox
L"Malheureusement, une erreur est survenue pendant l'exécution de l'étape %i\n\nL'application va maintenant se fermer",
L"D'accord",
// Dashlaunch load status
L"Dashlaunch : Chargé ! %ls",
L"[Mode disque dur]",
L"[Mode USB] NE PAS DÉBRANCHER LA CLÉ USB !",
L"Dashlaunch : ÉCHEC ! - Impossible d’écrire lhelper.xex. Erreur de données de section !",
L"Dashlaunch : ÉCHEC ! - Impossible d’écrire lhelper.xex. Erreur de montage !",
L"Dashlaunch : ÉCHEC ! - Impossible d’écrire lhelper.xex sur le périphérique de stockage.",
L"Dashlaunch : ÉCHEC ! - Impossible de charger launch.xex. Erreur de données de section !",
L"Dashlaunch : ÉCHEC ! - Statut : %X",
// Dump 1BL Notify
L"[Dump1blRomToFile] ÉCHEC ! Résultat non nul retourné par Hvx...",
L"Enregistré sous %S-1bl.bin",
L"[Dump1blRomToFile] ÉCHEC ! Impossible d’écrire le fichier...",
// Save Console Info Notify
L"Enregistré sous ConsoleInfo.txt",
L"Échec de l’enregistrement !",
// Save Orig MAC
L"Adresse MAC originale sauvegardée dans OriginalMACAddress.bin",
L"Échec de la sauvegarde de l'adresse MAC originale !",
// Main Screen Text
L"Tous les patchs ont été appliqués !\nLes fonctions JTAG/RGH normales devraient maintenant être actives sur votre console.\n\nCET ÉTAT N’EST PAS PERMANENT !\nVotre console retournera à son état d’origine une fois éteinte.\nIl est FORTEMENT recommandé de faire une copie de votre NAND maintenant !",
L"Tous les plugins définis dans launch.ini seront chargés quand vous quitterez l'application.\nLiveBlock devrait fonctionner maintenant s’il est activé dans launch.ini.\nBranchez votre câble réseau avant de quitter pour permettre l’authentification des services stealth.",
GLYPH_X_BUTTON L" Sauvegarder les infos dans un fichier",
GLYPH_Y_BUTTON L" Extraire 1BL dans un fichier",
L"Appuie sur " GLYPH_BACK_BUTTON L" pour quitter"
};

LocalisationMessages_t brazilian_portuguese = {
    // Error Messagebox
    L"Infelizmente ocorreu um erro ao executar o Stage %i\n\nO Aplicativo será encerrado",
    L"Entendido",
    // Dashlaunch load status
    L"Dashlaunch: Carregado! %ls",
    L"[HDD mode]",
    L"[USB mode] NÃO DESCONECTE O USB!",
    L"Dashlaunch: FALHA! - Falha ao escrever lhelper.xex. Erro de dados da seção!",
    L"Dashlaunch: FALHA! - Falha ao escrever lhelper.xex. Erro de montagem!",
    L"Dashlaunch: FALHA! - Falha ao escrever lhelper.xex para dispositivo de armazenamento.",
    L"Dashlaunch: FALHA! - Falha ao carregar launch.xex. Erro de dados da seção!",
    L"Dashlaunch: FALHA! - Status: %X",
    // Dump 1BL Notify
    L"[Dump1blRomToFile] FALHA! Resultado diferente de zero de Hvx...",
    L"Salvo em %S-1bl.bin",
    L"[Dump1blRomToFile] FALHA! Falha ao gravar o arquivo...",
    // Save Console Info Notify
    L"Salvo em ConsoleInfo.txt",
    L"Falha ao salvar!",
    // Save Orig MAC
    L"MAC original despejado em OriginalMACAddress.bin",
    L"Não foi possível despejar o MAC original!",
    // Main Screen Text

    L"Todos os patches foram aplicados!\nAgora a funcionalidade JTAG/RGH regular deve ser possível no seu sistema.\n\nISSO NÃO É PERSISTENTE!\nSeu console retornará a um estado completamente original e não modificado assim que for desligado.\nÉ ALTAMENTE recomendado que você faça agora o dump de uma cópia do seu nand!",
    L"Todos os plugins definidos em launch.ini serão carregados quando você sair deste aplicativo.\nO LiveBlock deve estar funcionando agora se estiver habilitado em launch.ini.\nConecte seu cabo de rede antes de sair para permitir que os stealths sejam autenticados corretamente.",
    GLYPH_X_BUTTON L" Salvar informações",
    GLYPH_Y_BUTTON L" Despejar 1BL",
    L"Pressione " GLYPH_BACK_BUTTON L" para sair"    
};

LocalisationMessages_t portuguese = {
// Error Messagebox
L"Infelizmente, ocorreu um erro durante a execução da etapa %i\n\nO aplicativo será encerrado agora",
L"Entendido",
// Dashlaunch load status
L"Dashlaunch: Carregado! %ls",
L"[Modo HDD]",
L"[Modo USB] NÃO REMOVA O USB!",
L"Dashlaunch: FALHA! - Falha ao gravar lhelper.xex. Erro nos dados da seção!",
L"Dashlaunch: FALHA! - Falha ao gravar lhelper.xex. Erro de montagem!",
L"Dashlaunch: FALHA! - Falha ao gravar lhelper.xex no dispositivo de armazenamento.",
L"Dashlaunch: FALHA! - Falha ao carregar launch.xex. Erro nos dados da seção!",
L"Dashlaunch: FALHA! - Status: %X",
// Dump 1BL Notify
L"[Dump1blRomToFile] FALHA! Resultado diferente de zero retornado pelo Hvx...",
L"Salvo como %S-1bl.bin",
L"[Dump1blRomToFile] FALHA! Não foi possível gravar o arquivo...",
// Save Console Info Notify
L"Salvo como ConsoleInfo.txt",
L"Falha ao salvar!",
L"Endereço MAC original salvo como OriginalMACAddress.bin",
L"Falha ao salvar o endereço MAC original!",
// Main Screen Text
L"Todos os patches foram aplicados!\nAs funcionalidades padrão de JTAG/RGH agora devem estar disponíveis no seu console.\n\nISSO NÃO É PERMANENTE!\nSeu console voltará ao estado original e sem modificações após ser desligado.\nÉ ALTAMENTE recomendável que você faça agora um backup da sua NAND!",
L"Todos os plugins definidos no launch.ini serão carregados quando você sair deste aplicativo.\nO LiveBlock deve estar funcionando agora, se estiver ativado no launch.ini.\nConecte seu cabo de rede antes de sair para permitir que os serviços stealth se autentiquem corretamente.",
GLYPH_X_BUTTON L" Salvar informações em arquivo",
GLYPH_Y_BUTTON L" Fazer dump do 1BL para arquivo",
L"Pressione " GLYPH_BACK_BUTTON L" para sair"

};

LocalisationMessages_t german = {
// Error Messagebox
L"Leider ist während Schritt %i ein Fehler aufgetreten\n\nDie Anwendung wird jetzt beendet",
L"Verstanden",
// Dashlaunch load status
L"Dashlaunch: Geladen! %ls",
L"[HDD-Modus]",
L"[USB-Modus] USB NICHT ENTFERNEN!",
L"Dashlaunch: FEHLGESCHLAGEN! - Konnte lhelper.xex nicht schreiben. Abschnittsdatenfehler!",
L"Dashlaunch: FEHLGESCHLAGEN! - Konnte lhelper.xex nicht schreiben. Einbindungsfehler!",
L"Dashlaunch: FEHLGESCHLAGEN! - Konnte lhelper.xex nicht auf das Speichermedium schreiben.",
L"Dashlaunch: FEHLGESCHLAGEN! - Konnte launch.xex nicht laden. Abschnittsdatenfehler!",
L"Dashlaunch: FEHLGESCHLAGEN! - Status: %X",
// Dump 1BL Notify
L"[Dump1blRomToFile] FEHLGESCHLAGEN! Nicht-null Ergebnis von Hvx...",
L"Gespeichert als %S-1bl.bin",
L"[Dump1blRomToFile] FEHLGESCHLAGEN! Konnte Datei nicht schreiben...",
// Save Console Info Notify
L"Gespeichert als ConsoleInfo.txt",
L"Speichern fehlgeschlagen!",
L"Original-MAC-Adresse gespeichert in OriginalMACAddress.bin",
L"Originale MAC-Adresse konnte nicht gespeichert werden!",
// Main Screen Text
L"Alle Patches wurden angewendet!\nNormale JTAG/RGH-Funktionalität sollte jetzt möglich sein.\n\nDIES IST NICHT PERMANENT!\nDie Konsole kehrt nach dem Ausschalten in den Originalzustand zurück.\nEs wird DRINGEND empfohlen, jetzt ein NAND-Backup zu erstellen!",
L"Alle in launch.ini festgelegten Plugins werden beim Verlassen der App geladen.\nLiveBlock sollte nun funktionieren, wenn es in der launch.ini aktiviert wurde.\nBitte Netzwerkkabel einstecken, bevor du die App verlässt, um eine erfolgreiche Stealth-Authentifizierung zu ermöglichen.",
GLYPH_X_BUTTON L" Informationen in Datei speichern",
GLYPH_Y_BUTTON L" 1BL in Datei speichern",
L"Drücke " GLYPH_BACK_BUTTON L" zum Beenden"
    
};

LocalisationMessages_t swedish = {
// Error Messagebox
L"Ett fel inträffade tyvärr under steg %i\n\nAppen kommer nu att avslutas",
L"Förstått",
// Dashlaunch load status
L"Dashlaunch: Laddad! %ls",
L"[HDD-läge]",
L"[USB-läge] DRA INTE UT USB!",
L"Dashlaunch: MISSLYCKADES! - Kunde inte skriva lhelper.xex. Sektionsdatafel!",
L"Dashlaunch: MISSLYCKADES! - Kunde inte skriva lhelper.xex. Monteringsfel!",
L"Dashlaunch: MISSLYCKADES! - Kunde inte skriva lhelper.xex till lagringsenheten.",
L"Dashlaunch: MISSLYCKADES! - Kunde inte läsa in launch.xex. Sektionsdatafel!",
L"Dashlaunch: MISSLYCKADES! - Status: %X",
// Dump 1BL Notify
L"[Dump1blRomToFile] MISSLYCKADES! Hvx returnerade ett icke-noll resultat...",
L"Sparad som %S-1bl.bin",
L"[Dump1blRomToFile] MISSLYCKADES! Kunde inte skriva filen...",
// Save Console Info Notify
L"Sparad som ConsoleInfo.txt",
L"Misslyckades med att spara!",
L"Original-MAC sparad som OriginalMACAddress.bin",
L"Misslyckades med att spara original-MAC!",
L"Alla patchar har nu applicerats!\nVanlig JTAG/RGH-funktionalitet bör nu fungera på din konsol.\n\nDETTA ÄR INTE PERMANENT!\nDin konsol återgår till originalskick när den stängs av.\nDet rekommenderas STARKT att du nu gör en säkerhetskopia av din NAND!",
L"Alla plugins angivna i launch.ini laddas när du avslutar appen.\nLiveBlock bör fungera nu om det är aktiverat i launch.ini.\nAnslut nätverkskabeln innan du avslutar för korrekt autentisering med stealth.",
GLYPH_X_BUTTON L" Spara information till fil",
GLYPH_Y_BUTTON L" Dumpa 1BL till fil",
L"Tryck på " GLYPH_BACK_BUTTON L" för att avsluta"
    
};

LocalisationMessages_t italian = {
// Error Messagebox
L"Purtroppo si è verificato un errore durante la fase %i\n\nL'app verrà ora chiusa",
L"Capito",
// Dashlaunch load status
L"Dashlaunch: Caricato! %ls",
L"[Modalità HDD]",
L"[Modalità USB] NON SCOLLEGARE LA USB!",
L"Dashlaunch: FALLITO! - Impossibile scrivere lhelper.xex. Errore nei dati della sezione!",
L"Dashlaunch: FALLITO! - Impossibile scrivere lhelper.xex. Errore di montaggio!",
L"Dashlaunch: FALLITO! - Impossibile scrivere lhelper.xex sul dispositivo di archiviazione.",
L"Dashlaunch: FALLITO! - Impossibile caricare launch.xex. Errore nei dati della sezione!",
L"Dashlaunch: FALLITO! - Stato: %X",
// Dump 1BL Notify
L"[Dump1blRomToFile] FALLITO! Risultato non nullo da Hvx...",
L"Salvato come %S-1bl.bin",
L"[Dump1blRomToFile] FALLITO! Impossibile scrivere il file...",
// Save Console Info Notify
L"Salvato come ConsoleInfo.txt",
L"Salvataggio fallito!",
L"MAC originale salvato in OriginalMACAddress.bin",
L"Impossibile salvare il MAC originale!",
// Main Screen Text
L"Tutte le patch sono state applicate!\nLa funzionalità JTAG/RGH standard dovrebbe ora essere disponibile sul tuo sistema.\n\nQUESTO NON È PERMANENTE!\nLa console tornerà allo stato originale dopo lo spegnimento.\nÈ FORTEMENTE consigliato eseguire subito un backup della NAND!",
L"Tutti i plugin definiti in launch.ini verranno caricati quando esci dall'app.\nLiveBlock dovrebbe essere attivo ora se abilitato nel file launch.ini.\nCollega il cavo Ethernet prima di uscire per consentire l'autenticazione corretta dei servizi stealth.",
GLYPH_X_BUTTON L" Salva informazioni su file",
GLYPH_Y_BUTTON L" Esegui dump del 1BL su file",
L"Premi " GLYPH_BACK_BUTTON L" per uscire"
    
};



//Use Romanized or Latin Approximations (Temporary)


//No romanization needed — just stripped accents where needed for maximum compatibility.
LocalisationMessages_t polish = {
 // Error Messagebox
    L"Niestety, wystapil blad podczas etapu %i\n\nAplikacja zostanie teraz zamknieta",
    L"Rozumiem",
    // Dashlaunch load status
    L"Dashlaunch: Zaladowano! %ls",
    L"[Tryb HDD]",
    L"[Tryb USB] NIE ODLACZAJ USB!",
    L"Dashlaunch: NIEUDANE! - Nie mozna zapisac lhelper.xex. Blad danych sekcji!",
    L"Dashlaunch: NIEUDANE! - Nie mozna zapisac lhelper.xex. Blad montazu!",
    L"Dashlaunch: NIEUDANE! - Nie mozna zapisac lhelper.xex na urzadzeniu pamieci.",
    L"Dashlaunch: NIEUDANE! - Nie mozna zaladowac launch.xex. Blad danych sekcji!",
    L"Dashlaunch: NIEUDANE! - Status: %X",
    // Dump 1BL Notify
    L"[Dump1blRomToFile] NIEUDANE! Zwracany wynik Hvx nie jest zerem...",
    L"Zapisano jako %S-1bl.bin",
    L"[Dump1blRomToFile] NIEUDANE! Nie udalo sie zapisac pliku...",
    // Save Console Info Notify
    L"Zapisano jako ConsoleInfo.txt",
    L"Zapis nie powiodl sie!",
    // Save Orig MAC
    L"Oryginalny MAC zapisany jako OriginalMACAddress.bin",
    L"Nie udalo sie zapisac oryginalnego MAC!",
    // Main Screen Text
    L"Wszystkie latki zostaly zastosowane!\nStandardowe funkcje JTAG/RGH powinny dzialac.\n\nTO NIE JEST TRWALE!\nPo wylaczeniu konsola wroci do stanu fabrycznego.\nZalecane jest zrobienie kopii NAND!",
    L"Wszystkie pluginy z launch.ini zostana zaladowane po wyjsciu.\nLiveBlock powinien dzialac, jesli aktywowany.\nPodlacz kabel sieciowy przed wyjsciem.",
    GLYPH_X_BUTTON L" Zapisz info do pliku",
    GLYPH_Y_BUTTON L" Zrzuc 1BL do pliku",
    L"Wcisnij " GLYPH_BACK_BUTTON L" aby wyjsc"    
};

//Romanized Cyrillic russian
LocalisationMessages_t russian = {
    // Error Messagebox
    L"K sozhaleniyu, proizoshla oshibka vo vremya etapa %i\n\nPrilozhenie seychas zakroetsya",
    L"Ponimat’",
    // Dashlaunch load status
    L"Dashlaunch: Zagruzheno! %ls",
    L"[Rezhim HDD]",
    L"[Rezhim USB] NE OTKLYUCHAY USB!",
    L"Dashlaunch: OShIBKA! - Ne udalos’ zapisat’ lhelper.xex. Oshibka dannykh sektsii!",
    L"Dashlaunch: OShIBKA! - Ne udalos’ zapisat’ lhelper.xex. Oshibka montazha!",
    L"Dashlaunch: OShIBKA! - Ne udalos’ zapisat’ lhelper.xex na ustroystvo khraneniya.",
    L"Dashlaunch: OShIBKA! - Ne udalos’ zagruzit’ launch.xex. Oshibka dannykh sektsii!",
    L"Dashlaunch: OShIBKA! - Status: %X",
    // Dump 1BL Notify
    L"[Dump1blRomToFile] OShIBKA! Hvx vernul ne-nulevyy rezultat...",
    L"Fayl sokhranen kak %S-1bl.bin",
    L"[Dump1blRomToFile] OShIBKA! Ne udalos’ zapisat’ fayl...",
    // Save Console Info Notify
    L"Fayl sokhranen kak ConsoleInfo.txt",
    L"Ne udalos’ sokhranit’!",
    // Save Orig MAC
    L"Original’nyy MAC sokhranen kak OriginalMACAddress.bin",
    L"Ne udalos’ sokhranit’ MAC!",
    // Main Screen Text
    L"Vse patchi byli primeneni!\nFunktsii JTAG/RGH teper' dolzhny rabotat’.\n\nETO NE POSTOYANNO!\nKonsol’ vernetsya v zavodskoye sostoyaniye posle vyklyucheniya.\nNastoyatel’no rekomenduetsya sdelat’ rezervnuyu kopiyu NAND!",
    L"Vse plaginy iz launch.ini budut zagruzheny pri vykhode.\nLiveBlock dolzhen rabotat’, esli vklyuchen.\nPodklyuchite Ethernet kabel pered vykhodom.",
    GLYPH_X_BUTTON L" Sokhranit’ informatsiyu v fayl",
    GLYPH_Y_BUTTON L" Sdelat’ dump 1BL v fayl",
    L"Nazhmi " GLYPH_BACK_BUTTON L" dlya vykhoda"
   
};

//Romanized
LocalisationMessages_t korean = {
    // Error Messagebox
    L"Yuchihage, %i beonjjae stage jung erroga balseonghaessseubnida\n\nAppi jigeum jonglyohabnida",
    L"Araessseubnida",
    // Dashlaunch load status
    L"Dashlaunch: Load wanryo! %ls",
    L"[HDD mode]",
    L"[USB mode] USB-reul ppajji maseyo!",
    L"Dashlaunch: SILPAE! - lhelper.xex-eul ssujil su eopseubnida. Section data error!",
    L"Dashlaunch: SILPAE! - lhelper.xex ssugi SILPAE. Mount error!",
    L"Dashlaunch: SILPAE! - lhelper.xex-reul jejangjangchi-e ssujil su eopseubnida.",
    L"Dashlaunch: SILPAE! - launch.xex load SILPAE. Section data error!",
    L"Dashlaunch: SILPAE! - Status: %X",
    // Dump 1BL Notify
    L"[Dump1blRomToFile] SILPAE! Hvxga 0 anin gyeolgwa-reul naetam...",
    L"%S-1bl.bin-e jeojanghaessseubnida",
    L"[Dump1blRomToFile] SILPAE! Fail-leul ssujil su eopseubnida...",
    // Save Console Info Notify
    L"ConsoleInfo.txt-ro jeojanghaessseubnida",
    L"Jeojang SILPAE!",
    // Save Orig MAC
    L"Original MAC, OriginalMACAddress.bin-e jeojanghaessseubnida",
    L"Original MAC jeojang SILPAE!",
    // Main Screen Text
    L"Modeun paechiga jeoyong dwaessseubnida!\nJTAG/RGH gineung-i hyeonjaehwa dwaessseubnida.\n\nI geos-eun yeonggujeog-i anibnida!\nKonsol-eul kkeumyeon chobonsangtaelo dol-a-gabnida.\nNAND-reul backuphaneun geos-eul ganglyohan-gamnida!",
    L"launch.ini-e jeong-ui doen modeun peullagin-eun app-reul naomyeon load doebnida.\nlaunch.ini-e seonghwadoen LiveBlockdo jigeum hwalseong jung-il su issseubnida.\nJonglyohagi jeon-e Ethernet kaebeurul yeolchyeojuseyo.",
    GLYPH_X_BUTTON L" Jeongbo-leul failro jeojang",
    GLYPH_Y_BUTTON L" 1BL-eul failro dump",
    L"BACK beuteun-eul nulleo jonglyohae juseyo"
    
};

//Pinyin Romanized
LocalisationMessages_t chinese_simplified = {
    // Error Messagebox
    L"Henshang, zai zhixing di %i bu shihou fasheng cuowu\n\nYingyong jiang guanbi",
    L"Mingbai",
    // Dashlaunch load status
    L"Dashlaunch: Yijia zai! %ls",
    L"[Yingpan moshi]",
    L"[USB moshi] QING BUYAO BAXIA USB!",
    L"Dashlaunch: SHIBAI! - Wu fa xieru lhelper.xex. qumu shuju cuowu!",
    L"Dashlaunch: SHIBAI! - Wu fa xieru lhelper.xex. guazai cuowu!",
    L"Dashlaunch: SHIBAI! - Wu fa xieru lhelper.xex dao cunchushebei.",
    L"Dashlaunch: SHIBAI! - Wu fa jiazai launch.xex. qumu shuju cuowu!",
    L"Dashlaunch: SHIBAI! - Zhuangtai: %X",
    // Dump 1BL Notify
    L"[Dump1blRomToFile] SHIBAI! Hvx fanhui fei ling jieguo...",
    L"Baocun dao %S-1bl.bin",
    L"[Dump1blRomToFile] SHIBAI! Wu fa xieru wenjian...",
    // Save Console Info Notify
    L"Baocun dao ConsoleInfo.txt",
    L"Baocun shibai!",
    // Save Orig MAC
    L"Yuanshi MAC baocun dao OriginalMACAddress.bin",
    L"Wufa baocun yuanshi MAC!",
    // Main Screen Text
    L"Suo you patch yi jia zai!\nXitong yinggai keyi zhengchang shiyong JTAG/RGH gongneng.\n\nZHE BUSHI YONGJIU DE!\nGuanji hou, xitong jiang fuyuan chuchang zhuangtai.\nQianglie tuijian xianzai beifen NAND!",
    L"Tuichu chengxu shi, launch.ini zhong de plugin jiang bei jiazai.\nRuguo launch.ini zhong qidong le LiveBlock, xianzai yinggai keyi yunyong.\nTuichu qian qing lianjie wangluo yinxian.",
    GLYPH_X_BUTTON L" Baocun xinxi dao wenjian",
    GLYPH_Y_BUTTON L" Daochu 1BL dao wenjian",
    L"An " GLYPH_BACK_BUTTON L" tuichu"
    
};

LocalisationMessages_t* currentLocalisation = &english; // &spanish;


VOID SetLocale()
{
    switch (XGetLanguage())
    {
    case XC_LANGUAGE_ENGLISH:
        currentLocalisation = &english;
        break;
    case XC_LANGUAGE_SPANISH:
        currentLocalisation = &spanish;
        break;
    case XC_LANGUAGE_GERMAN:
        currentLocalisation = &german;
        break;
    case XC_LANGUAGE_FRENCH:
        currentLocalisation = &canadian_french;
        break;
    case XC_LANGUAGE_SWEDISH:
        currentLocalisation = &swedish;
        break;
    case XC_LANGUAGE_ITALIAN:
        currentLocalisation = &italian;
        break;
    case XC_LANGUAGE_PORTUGUESE:
        currentLocalisation = &brazilian_portuguese;
        
        if (XGetLocale() == XC_LOCALE_BRAZIL)
            currentLocalisation = &brazilian_portuguese;
        else
            currentLocalisation = &portuguese;
        break;
    
    // === UNSUPPORTED NATIVE FONT WITHOUT NEW FONT METHOD ===
    case XC_LANGUAGE_POLISH:
        currentLocalisation = &polish;
        break;
    case XC_LANGUAGE_RUSSIAN:
        currentLocalisation = &russian;
        break;
    case XC_LANGUAGE_KOREAN:
        currentLocalisation = &korean;
        break;
    case XC_LANGUAGE_SCHINESE:
        currentLocalisation = &chinese_simplified;
        break;
    default:
        currentLocalisation = &english;
        break;
    }
}
