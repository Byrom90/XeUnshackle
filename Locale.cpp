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

//LocalisationMessages_t canadian_french = {
//    
//};

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

//LocalisationMessages_t portuguese = {
//    
//};

//LocalisationMessages_t german = {
//    
//};

//LocalisationMessages_t swedish = {
//    
//};

//LocalisationMessages_t italian = {
//    
//};


// Launguages below here won't work without a new font to support the characters???

//LocalisationMessages_t polish = {
//    
//};

LocalisationMessages_t russian = {
    // Error Messagebox - Ошибка при каком-либо этапе
    L"\u041A \u0441\u043E\u0436\u0430\u043B\u0435\u043D\u0438\u044E \u043F\u0440\u043E\u0438\u0437\u043E\u0448\u043B\u0430 \u043E\u0448\u0438\u0431\u043A\u0430 \u043F\u0440\u0438 %i \u044D\u0442\u0430\u043F\u0435.\n\n\u041F\u0440\u0438\u043B\u043E\u0436\u0435\u043D\u0438\u0435 \u0441\u0435\u0439\u0447\u0430\u0441 \u0437\u0430\u043A\u0440\u043E\u0435\u0442\u0441\u044F.",
    L"\u041E\u041A :(",
    // Dashlaunch load status - статус DashLaunch
    L"\u0421\u0442\u0430\u0442\u0443\u0441 Dashlaunch: \u0417\u0430\u0433\u0440\u0443\u0436\u0435\u043D! %ls",
    L"[\u0420\u0435\u0436\u0438\u043C \u0436\u0435\u0441\u0442\u043A\u043E\u0433\u043E \u0434\u0438\u0441\u043A\u0430]",
    L"[\u0420\u0435\u0436\u0438\u043C \u0444\u043B\u0435\u0448\u043A\u0438] \u041D\u0415 \u041E\u0422\u041A\u041B\u042E\u0427\u0410\u0419\u0422\u0415 \u0424\u041B\u0415\u0428\u041A\u0423!",
    L"\u0421\u0442\u0430\u0442\u0443\u0441 Dashlaunch: \u041E\u0448\u0438\u0431\u043A\u0430! - \u041D\u0435 \u043F\u043E\u043B\u0443\u0447\u0438\u043B\u043E\u0441\u044C \u0437\u0430\u043F\u0438\u0441\u0430\u0442\u044C lhelper.xex. \u041E\u0448\u0438\u0431\u043A\u0430 \u0434\u0430\u043D\u043D\u044B\u0445 \u0440\u0430\u0437\u0434\u0435\u043B\u0430!",
    L"\u0421\u0442\u0430\u0442\u0443\u0441 Dashlaunch: \u041E\u0448\u0438\u0431\u043A\u0430! - \u041D\u0435 \u043F\u043E\u043B\u0443\u0447\u0438\u043B\u043E\u0441\u044C \u0437\u0430\u043F\u0438\u0441\u0430\u0442\u044C lhelper.xex. \u041E\u0448\u0438\u0431\u043A\u0430 \u043C\u043E\u043D\u0442\u0438\u0440\u043E\u0432\u0430\u043D\u0438\u044F!",
    L"\u0421\u0442\u0430\u0442\u0443\u0441 Dashlaunch: \u041E\u0448\u0438\u0431\u043A\u0430! - \u041D\u0435 \u043F\u043E\u043B\u0443\u0447\u0438\u043B\u043E\u0441\u044C \u0437\u0430\u043F\u0438\u0441\u0430\u0442\u044C lhelper.xex \u0432 \u0445\u0440\u0430\u043D\u0438\u043B\u0438\u0449\u0435.",
    L"\u0421\u0442\u0430\u0442\u0443\u0441 Dashlaunch: \u041E\u0448\u0438\u0431\u043A\u0430! - \u041D\u0435 \u043F\u043E\u043B\u0443\u0447\u0438\u043B\u043E\u0441\u044C \u0437\u0430\u0433\u0440\u0443\u0437\u0438\u0442\u044C launch.xex. \u041E\u0448\u0438\u0431\u043A\u0430 \u0434\u0430\u043D\u043D\u044B\u0445 \u0440\u0430\u0437\u0434\u0435\u043B\u0430!",
    L"\u0421\u0442\u0430\u0442\u0443\u0441 Dashlaunch: \u041E\u0448\u0438\u0431\u043A\u0430! - \u0421\u0442\u0430\u0442\u0443\u0441: %X",
    // Dump 1BL Notify - Уведомление о сохранении первого загрузчика
    L"[Dump1blRomToFile] \u041E\u0448\u0438\u0431\u043A\u0430! \u041D\u0435-\u043D\u0443\u043B\u0435\u0432\u043E\u0439 \u0440\u0435\u0437\u0443\u043B\u044C\u0442\u0430\u0442 \u043E\u0442 \u0433\u0438\u043F\u0435\u0440\u0432\u0438\u0437\u043E\u0440\u0430...",
    L"\u0421\u043E\u0445\u0440\u0430\u043D\u0438\u043B \u0432 %S-1bl.bin",
    L"[Dump1blRomToFile] \u041E\u0448\u0438\u0431\u043A\u0430! \u041D\u0435 \u0443\u0434\u0430\u043B\u043E\u0441\u044C \u0437\u0430\u043F\u0438\u0441\u0430\u0442\u044C \u0444\u0430\u0439\u043B...",
    // Save Console Info Notify - Уведомления о сохранении информации консоли
    L"\u0421\u043E\u0445\u0440\u0430\u043D\u0438\u043B \u0432 ConsoleInfo.txt",
    L"\u041D\u0435 \u0443\u0434\u0430\u043B\u043E\u0441\u044C \u0441\u043E\u0445\u0440\u0430\u043D\u0438\u0442\u044C \u0438\u043D\u0444\u043E\u0440\u043C\u0430\u0446\u0438\u044E \u043E \u043A\u043E\u043D\u0441\u043E\u043B\u0438!",
    // Save Orig MAC - сохранение оригинального MAC-адреса
    L"\u041E\u0440\u0438\u0433\u0438\u043D\u0430\u043B\u044C\u043D\u044B\u0439 MAC-\u0430\u0434\u0440\u0435\u0441 \u0441\u043E\u0445\u0440\u0430\u043D\u0435\u043D \u0432 OriginalMACAddress.bin",
    L"\u041D\u0435 \u0443\u0434\u0430\u043B\u043E\u0441\u044C \u0441\u043E\u0445\u0440\u0430\u043D\u0438\u0442\u044C MAC-\u0430\u0434\u0440\u0435\u0441!",
    // Main Screen Text - текст главного экрана
    L"\u0412\u0441\u0435 \u043F\u0430\u0442\u0447\u0438 \u043F\u0440\u0438\u043C\u0435\u043D\u0435\u043D\u044B!\n\u0424\u0443\u043D\u043A\u0446\u0438\u043E\u043D\u0430\u043B RGH/JTAG \u0434\u043E\u043B\u0436\u0435\u043D \u0440\u0430\u0431\u043E\u0442\u0430\u0442\u044C \u043D\u0430 \u0432\u0430\u0448\u0435\u0439 \u043A\u043E\u043D\u0441\u043E\u043B\u0438, \u041D\u041E \u041D\u0415 \u041F\u041E\u0421\u0422\u041E\u042F\u041D\u041D\u041E!\n\u0412\u0430\u0448\u0430 \u043A\u043E\u043D\u0441\u043E\u043B\u044C \u0432\u0435\u0440\u043D\u0435\u0442\u0441\u044F \u0432 \u0441\u0442\u043E\u043A\u043E\u0432\u043E\u0435 \u0441\u043E\u0441\u0442\u043E\u044F\u043D\u0438\u0435 \u043F\u043E\u0441\u043B\u0435 \u043F\u0435\u0440\u0435\u0437\u0430\u0433\u0440\u0443\u0437\u043A\u0438.\n\u041E\u0427\u0415\u041D\u042C \u0436\u0435\u043B\u0430\u0442\u0435\u043B\u044C\u043D\u043E \u0441\u043E\u0445\u0440\u0430\u043D\u0438\u0442\u044C \u0444\u043B\u0435\u0448-\u043F\u0430\u043C\u044F\u0442\u044C!",
    L"\u0412\u0441\u0435 \u043F\u043B\u0430\u0433\u0438\u043D\u044B \u0443\u043A\u0430\u0437\u0430\u043D\u044B\u0435 \u0432 launch.ini \u0437\u0430\u0433\u0440\u0443\u0437\u044F\u0442\u0441\u044F \u043F\u043E\u0441\u043B\u0435 \u0432\u044B\u0445\u043E\u0434\u0430 \u0438\u0437 \u043F\u0440\u0438\u043B\u043E\u0436\u0435\u043D\u0438\u044F.\nLiveBlock \u0434\u043E\u043B\u0436\u0435\u043D \u0440\u0430\u0431\u043E\u0442\u0430\u0442\u044C \u0435\u0441\u043B\u0438 \u0443\u043A\u0430\u0437\u0430\u043D \u0432 launch.ini.\n\u041F\u043E\u0434\u043A\u043B\u044E\u0447\u0438\u0442\u0435 \u0438\u043D\u0442\u0435\u0440\u043D\u0435\u0442-\u043A\u0430\u0431\u0435\u043B\u044C \u0438\u043B\u0438 WiFi \u0441\u0435\u0439\u0447\u0430\u0441 \u0447\u0442\u043E\u0431\u044B \u0434\u0430\u0442\u044C \u0441\u0442\u0435\u043B\u0441-\u0441\u0435\u0440\u0432\u0435\u0440\u0430\u043C \u0430\u0443\u0442\u0435\u043D\u0442\u0438\u0444\u0438\u0446\u0438\u0440\u043E\u0432\u0430\u0442\u044C\u0441\u044F.",
    GLYPH_X_BUTTON L" \u0421\u043E\u0445\u0440\u0430\u043D\u0438\u0442\u044C \u0438\u043D\u0444\u043E\u0440\u043C\u0430\u0446\u0438\u044E \u043E \u043A\u043E\u043D\u0441\u043E\u043B\u0438 \u0432 \u0444\u0430\u0439\u043B",
    GLYPH_Y_BUTTON L" \u0421\u043E\u0445\u0440\u0430\u043D\u0438\u0442\u044C \u043F\u0435\u0440\u0432\u044B\u0439 \u0437\u0430\u0433\u0440\u0443\u0437\u0447\u0438\u043A \u0432 \u0444\u0430\u0439\u043B",
    L"\u041D\u0430\u0436\u043C\u0438\u0442\u0435 " GLYPH_BACK_BUTTON L" \u0447\u0442\u043E\u0431\u044B \u0432\u044B\u0439\u0442\u0438"
};

//LocalisationMessages_t korean = {
//    
//};

//LocalisationMessages_t chinese_simplified = {
//    
//};

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
    //case XC_LANGUAGE_GERMAN:
    //    currentLocalisation = &german;
    //    break;
    //case XC_LANGUAGE_FRENCH:
    //    currentLocalisation = &canadian_french;
    //    break;
    //case XC_LANGUAGE_SWEDISH:
    //    currentLocalisation = &swedish;
    //    break;
    //case XC_LANGUAGE_ITALIAN:
    //    currentLocalisation = &italian;
    //    break;
    case XC_LANGUAGE_PORTUGUESE:
        currentLocalisation = &brazilian_portuguese;
        //waiting for the translation in Portuguese
        //if (XGetLocale() == XC_LOCALE_BRAZIL)
        //    currentLocalisation = &brazilian_portuguese;
        //else
        //    currentLocalisation = &portuguese;
        break;
    
    // === UNSUPPORTED WITHOUT NEW FONT ===
    //case XC_LANGUAGE_POLISH:
    //    currentLocalisation = &polish;
    //    break;
    //case XC_LANGUAGE_RUSSIAN:
    //    currentLocalisation = &russian;
    //    break;
    //case XC_LANGUAGE_KOREAN:
    //    currentLocalisation = &korean;
    //    break;
    //case XC_LANGUAGE_SCHINESE:
    //    currentLocalisation = &chinese_simplified;
    //    break;
    default:
        currentLocalisation = &english;
        break;
    }
}
