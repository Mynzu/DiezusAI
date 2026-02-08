#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <sqlite3.h>
#include <napi.h>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;
    int puntosAnimo = 50; 
    int contadorMalas = 0;// Rango de 0 a 100
    //aqui me la voy a fumar muchaches
std::map<string, string> diccionario_emociones = {
            // Felicidad
        {"alegria", "felicidad"},
        {"dicha","felicidad"},
        {"jubilo","felicidad"},
        {"entusiasmo","felicidad"},
        {"contento","felicidad"},
        {"optimismo","felicidad"},
        {"euforia","felicidad"},
        {"felicidad","felicidad"},
        {"gozo","felicidad"},
        {"regocijo","felicidad"},
        // Sorpresa
        {"sorpresa","sorpresa"},
        {"asombro","sorpresa"},
        {"maravilla","sorpresa"},
        {"estupor","sorpresa"},
        {"incredulidad","sorpresa"},
        {"desconcierto","sorpresa"},
        {"asombro","sorpresa"},
        {"impresion","sorpresa"},
        // Añoranza
        {"añoranza", "anhelo"},
        {"esperanza","anhelo"},
        {"apego","anhelo"},
        // Afecto
        {"afecto","afecto"},
        {"amabilidad","afecto"},
        {"benevolencia","afecto"},
        {"solidaridad","afecto"},
        {"bondad","afecto"},
        {"cariño","afecto"},
        {"ternura","afecto"},
        {"generosidad","afecto"},
        {"tolerancia","afecto"},
        {"integridad","afecto"},
        // compasion
        {"compasion","compasion"},
        {"condescendencia","compasion"},
        {"consideracion","compasion"},
        {"empatia","compasion"},
        {"piedad","compasion"},
        {"sensibilidad","compasion"},
        {"comprension","compasion"},
        {"solidaridad","compasion"},
        {"humanidad","compasion"},
        {"altruismo","compasion"},
        // admiracion
        {"admiracion","admiracion"},
        {"aprobacion","admiracion"},
        {"estima","admiracion"},
        {"honorabilidad","admiracion"},
        // agradecimiento
        {"agradecimiento","agradecimiento"},
        // alivio
        {"alivio","alivio"},
        {"tranquilo","alivio"},
        {"calma","alivio"},
        {"serenidad","alivio"},
        {"armonia","alivio"},
        // ambivalencia
        {"ambivalencia","ambivalencia"},
        // respeto
        {"respeto","respeto"},
        {"consideracion","respeto"},
        {"cortesía","respeto"},
        {"deferencia","respeto"},
        {"reverencia","respeto"},
        {"veneracion","respeto"},
        // apoyo
        {"apoyo","apoyo"},
        // confianza
        {"confianza","confianza"},
        {"valentia","confianza"},
        {"coraje","confianza"},
        {"determinacion","confianza"},
        {"decision","confianza"},
        {"fortaleza","confianza"},
        {"fuerza","confianza"},
        {"seguridad","confianza"},
        {"autoestima","confianza"},
        {"autoeficacia","confianza"},
        // Resistencia
        {"resistencia","resistencia"},    
        {"perseverancia","resistencia"},
        {"tenacidad","resistencia"},
        {"resiliencia","resistencia"},
        // aca agregue las de la otra noche!
        // Intriga
        {"intriga","intriga"},
        {"curiosidad","intriga"},
        // amor
        {"amor","amor"},
        {"aprecio","amor"},
        {"adoracion","amor"},
        {"devocion","amor"},
        {"pasion","amor"},
        {"cariño","amor"},
        {"ternura","amor"},
        {"afecto","amor"},
        {"enamoramiento","amor"},
        {"romance","amor"},
        {"atraccion","amor"},
        // autonomia
        {"autonomia","autonomia"},
        {"independencia","autonomia"},
        {"libertad","autonomia"},
        {"autosuficiencia","autonomia"},
        //trizteza
        {"tristeza","tristeza"},
        {"afliccion","tristeza"},
        {"desanimo","tristeza"},
        {"desmotivacion","tristeza"},
        {"desasosiego","tristeza"},
        {"dependencia", "dependencia"},
        // Ira
        {"ira","ira"},
        {"enojo","ira"},
        {"furia","ira"},
        {"rabia","ira"},
        {"rebeldia","ira"},
        {"indignacion","ira"},
        // Resentimiento
        {"resentimiento","resentimiento"},
        {"repudio","resentimiento"},
        {"rencor","resentimiento"},
        //injusticia
        {"injusticia","injusticia"},
        // insatisfaccion
        {"insatisfaccion","insatisfaccion"},
        //terquedad
        {"terquedad","terquedad"},
        {"obstinacion","terquedad"},
        {"rigidez","terquedad"},
        {"inflexibilidad","terquedad"},
        {"ignorancia","terquedad"}, // agregue esta
        // celos
        {"celos","celos"},
        {"envidia","celos"},
        {"recelos","celos"},
        {"sospecha","celos"},
        // inseguridad
        {"inseguridad","inseguridad"},
        {"timidez","inseguridad"},
        {"verguenza","inseguridad"},
        {"aprehension","inseguridad"},
        {"nerviosismo","inseguridad"},
        {"vacilacion","inseguridad"},
        {"duda","inseguridad"},
        // impaciencia
        {"impaciencia","impaciencia"},
        //Inconformidad
        {"insuficiencia","inconformidad"},
        {"inconformidad","inconformidad"},
        {"comparacion","inconformidad"},
        {"descontento","inconformidad"},
        {"codicia","inconformidad"},
        {"avaricia","inconformidad"},
        {"materialismo","inconformidad"},
        // Confusion
        {"confusion","confusion"},
        {"duda","confusion"},
        {"desorientacion","confusion"},
        {"incertidumbre","confusion"},
        {"desconcierto","confusion"},
        {"desorientacion","confusion"},
        {"turbacion","confusion"},
        {"inquietud","confusion"}, // agregue esta
        // incapacidad
        {"incapacidad","incapacidad"},
        {"ineptitud","incapacidad"},
        {"incompetencia","incapacidad"},
        {"ineficacia","incapacidad"},
        {"ineficiencia","incapacidad"},
        {"inutilidad","incapacidad"},
        {"torpeza","incapacidad"},
        // peraza
        {"pereza","pereza"},
        {"flojera","pereza"},
        {"procastinacion", "pereza"},
        // fracaso
        {"frustracion","fracaso"},
        {"fracaso","fracaso"},
        {"irritacion","fracaso"},
        // Arrepentimiento
        {"arrepentimiento","arrepentimiento"},
        {"culpa","arrepentimiento"},
        {"remordimiento","arrepentimiento"},
        // Amargura
        {"amargura","amargura"},
        {"arrogancia","amargura"},
        {"desconfianza","amargura"},
        {"decepcion","amargura"},
        {"desconsideracion","amargura"},
        {"desconsuelo","amargura"},
        // espanto
        {"espanto","espanto"},
        {"miedo","espanto"},
        {"terror","espanto"},
        {"panico","espanto"},
        {"fobia","espanto"},
        // aburrimiento
        {"aburrimiento","aburrimiento"},
        {"fastidio","aburrimiento"},
        {"tedio","aburrimiento"},
        {"hastio","aburrimiento"},
        // agravio
        {"agravio","agravio"},
        {"ofensa","agravio"},
        {"ultraje","agravio"},
        {"injuria","agravio"},
        {"desprecio","agravio"},
        {"abuso","agravio"},
        {"insulto","agravio"},
        {"agresion","agravio"},
        {"alteracion","agravio"},
        {"destruccion","agravio"},
        // abrumado
        {"agobio","abrumado"},
        {"angustia","abrumado"},
        {"ansiedad","abrumado"},
        {"estres","abrumado"},
        {"presion","abrumado"},
        {"sobrecarga","abrumado"},
        {"tension","abrumado"},
        {"fatiga","abrumado"},
        {"agotamiento","abrumado"},
        {"estres academico", "abrumado"},
        // abandono
        {"abandono","abandono"},
        {"ausencia","abandono"},
        {"desamparo","abandono"},
        {"desolacion","abandono"},
        {"soledad","abandono"}, //listo
        // apatia
        {"asco","apatia"},
        {"desapego","apatia"},
        {"desamor","apatia"},
        {"desprecio","apatia"},
        {"desden","apatia"},
        {"desinteres","apatia"},
        {"disgusto","apatia"},
        {"egoismo","apatia"},
        {"indiferencia","apatia"},
        // traicion,
        {"engaño","traicion"},
        {"infidelidad","traicion"},
        {"mentira","traicion"},
        {"rechazo","traicion"},
        {"perfidia","traicion"},
        // Prepotencia
        {"prepotencia","prepotencia"},
        {"vurnerabilidad","prepotencia"},
        {"debilidad","prepotencia"},
        // Cansancio
        {"agotamiento","cansancio"},
        {"exhausto","cansancio"},
        {"fatiga","cansancio"},
        {"debilidad","cansancio"},
        {"desgano","cansancio"},
        {"abatimiento","cansancio"},
        {"fatiga","cansancio"},
        // desencanto
        {"desencanto","desencanto"},
        {"desilusion","desencanto"},
        {"impotencia","desencanto"},
        {"humillacion","desencanto"},
        // discordia
        {"discordia","discordia"},
        {"desacuerdo","discordia"},
        // nostalgia
        {"melancolia","nostalgia"},
        {"nostalgia","nostalgia"},
        {"saudade","nostalgia"},
        {"recuerdo","nostalgia"},
        {"añoranza","nostalgia"},
        //  depresion
        {"depresion","depresion"},
        {"vacio","depresion"},
        // dolor
        {"duelo","dolor"},
        {"derrota","dolor"}, //listo
        {"desaliento","dolor"}, // agregue esta
        {"pesimismo","dolor"},
        {"negatividad","dolor"},
        {"desesperanza","dolor"},
        {"perfeccionismo","dolor"}, //listo
        {"obsesion","dolor"},
        {"autoexigencia","dolor"},
        //emociones negativas
        {"no","negativo"},
        {"nunca","negativo"},
        {"ningun","negativo"},
        {"ninguna","negativo"},
        {"jamas","negativo"},
        {"nada","negativo"},
        {"tampoco","negativo"},
        {"nadie","negativo"},
        {"sin","negativo"},
        {"ni","negativo"},
        {"pero","negativo"},
        {"aunque","negativo"},
        {"excepto","negativo"},
        {"ni siquiera","negativo"},

        {"muerte", "preocupantes"},
        {"asesinato", "preocupantes"},
        {"suicidio", "preocupantes"},
        // Saludos
        {"hola","saludo"},
        {"saludos","saludo"},
        {"hey","saludo"},
        {"buenos dias","saludo"},
        {"buenas tardes","saludo"},
        {"buenas noches","saludo"},
        {"como estas","saludo"},
        {"Buenas","saludo"},
        {"que tal","saludo"},
        {"olaa","saludo"},
        {"que hubo","saludo"},
        {"holi", "saludo"},
        // Despedidas
        {"adios","despedida"},
        {"hasta luego","despedida"},
        {"nos vemos","despedida"},
        {"chao","despedida"},
        {"cuidate","despedida"},
        {"hasta pronto","despedida"},
        {"bye","despedida"},
        {"me voy","despedida"},
        {"hasta la vista","despedida"},
        {"nos hablamos","despedida"},
        {"hasta mañana","despedida"},
        // Cortesias
        {"gracias","cortesia"},
        {"por favor","cortesia"},
        {"de nada","cortesia"},
        {"disculpa","cortesia"},
        {"perdon","cortesia"},
        {"muchas gracias","cortesia"},
        {"lo siento","cortesia"},
        {"con gusto","cortesia"},
        {"un placer","cortesia"},
        {"es un honor","cortesia"},
        {"te lo agradezco","cortesia"},
        // Solicitudes de ayuda
        {"ayuda","ayuda"},
        {"socorro","ayuda"},
        {"auxilio","ayuda"},
        {"salva","ayuda"},
        {"rescata","ayuda"},
        {"asiste","ayuda"},
        {"apoya","ayuda"},
        {"salvame","ayuda"},
        {"rescatame","ayuda"},
        {"asisteme","ayuda"},
        {"protege","ayuda"},
        {"sobrevive","ayuda"},
        {"vive","ayuda"},
        {"lucha","ayuda"},
        //familia
        {"madre","familia"},
        {"padre","familia"},
        {"hermano","familia"},
        {"hermana","familia"},
        {"hijo","familia"},
        {"hija","familia"},
        {"familia","familia"},
        {"familiar","familia"},
        {"abuelo","familia"},
        {"abuela","familia"},
        {"tio","familia"},
        {"tia","familia"},
        {"primo","familia"},
        {"prima","familia"},
        {"esposo","familia"},
        {"esposa","familia"},
        {"pareja","familia"},
        {"novio","familia"},
        {"novia","familia"},
        //situaciones
        {"examen","situacion"},
        {"clase","situacion"},
        {"escuela","situacion"},
        {"universidad","situacion"},
        {"maestro", "situacion"},
        {"profesor", "situacion"},
        {"estudiante", "situacion"},
        {"curso","situacion"},
        {"leccion","situacion"},
        {"tarea","situacion"},
        {"estudio","situacion"},
        {"investigacion", "situacion"},  
        {"practica","situacion"},
        {"nota","situacion"},
        {"calificacion","situacion"},
        {"graduacion","situacion"},
        {"trabajo en equipo","situacion"},
        {"presentacion","situacion"},
        {"proyecto","situacion"},
        {"exposicion","situacion"},
        {"investigacion","situacion"},
        {"bibliografia","situacion"},
        {"ensayo","situacion"},
        {"plazo","situacion"},
        {"entrega","situacion"},
        {"investigar","situacion"},
        {"aprender","situacion"},
        {"estudiar","situacion"},
        {"repasar","situacion"},
        {"memorizar","situacion"},
        {"comprender","situacion"},
        {"analizar","situacion"},
        {"sintetizar","situacion"},
        {"evaluar","situacion"},
        {"calificar","situacion"},
        {"graduarse","situacion"},
        {"trabajo","situacion"},
        {"problema","situacion"},
        //salud
        {"enfermedad","salud"},
        {"dolor","salud"},
        {"fiebre", "salud"},
        {"tos", "salud"},
        {"resfriado", "salud"},
        {"gripe", "salud"},
        {"nauseas", "salud"},
        {"vomito", "salud"},
        {"mareo", "salud"},
        {"dolor de garganta", "salud"},
        {"congestion nasal", "salud"},
        {"dolor muscular", "salud"},
        {"dolor de cabeza", "salud"},
        {"estres", "salud"},
        {"ansiedad", "salud"},
        {"depresion", "salud"},
        {"insomnio", "salud"},
        {"bienestar general", "salud"},
        {"malestar","salud"},
        {"fatiga","salud"},
        {"estres","salud"},
        {"ansiedad","salud"},
        {"depresion","salud"},
        {"insomnio","salud"},
        {"virus","salud"},
        {"bacteria","salud"},
        {"infeccion","salud"},
        {"lesion","salud"},
        {"cirugia","salud"},
        {"medicamento","salud"},
        {"sintoma","salud"},
        {"diagnostico","salud"},
        {"tratamiento","salud"},
        {"recuperarse","salud"},
        {"recuperacion","salud"},
        {"medico","salud"},
        {"hospital","salud"},
        {"cura","salud"},
        {"tratamiento","salud"},
        {"salud","salud"}, 
        // trabajo
        {"empleo", "trabajo"},
        {"oficina","trabajo"},
        {"jefe","trabajo"},
        {"compañero","trabajo"},
        {"proyecto","trabajo"},
        {"tarea","trabajo"},
        {"reunion","trabajo"},
        {"presentacion","trabajo"},
        {"negocio","trabajo"},
        {"empresa","trabajo"},
        {"entrevista","trabajo"},
        {"salario","trabajo"},
        {"beneficio","trabajo"},
        {"horario","trabajo"},
        {"vacaciones","trabajo"},
        {"ascenso","trabajo"},
        {"despido","trabajo"},
        {"contrato","trabajo"},
        {"cliente","trabajo"},
        {"proveedor","trabajo"},
        {"producto","trabajo"},
        {"servicio","trabajo"},
        {"marketing","trabajo"},
        {"ventas","trabajo"},
        {"finanzas","trabajo"},
        {"contabilidad","trabajo"},
        {"administracion","trabajo"},
        {"liderazgo","trabajo"},
        {"trabajo en equipo","trabajo"},
        {"colaboracion","trabajo"},
        {"crecimiento profesional","trabajo"},
        {"desarrollo profesional","trabajo"},
        {"equilibrio trabajo-vida","trabajo"},
        //pensamientos
        {"idea","pensamientos"},
        {"creatividad","pensamientos"},
        {"inspiracion","pensamientos"},
        {"motivacion","pensamientos"},
        {"concentracion","pensamientos"},
        {"enfoque","pensamientos"},
        {"productividad","pensamientos"},
        {"organizacion","pensamientos"},
        {"sobrellevar","pensamientos"},
        {"sobre pensar","pensamientos"},
        {"analizar","pensamientos"},
        {"reflexionar","pensamientos"},
        {"meditar","pensamientos"},
        {"planear","pensamientos"},
        {"estrategia","pensamientos"},
        //fiestas
        {"fiesta","fiestas"},
        {"celebracion","fiestas"},
        {"evento","fiestas"},
        {"reunion","fiestas"},
        {"cumpleanos", "fiestas"},
        {"aniversario", "fiestas"},
        {"boda","fiestas"},
        {"graduacion","fiestas"},
        {"festival", "fiestas"},
        {"concierto","fiestas"},
        {"espectaculo","fiestas"}
};
vector<string> frases_De_Inicio = {
    "He sido invocado. ¿Cual es tu ofrenda de datos?",
    "¡Hola! Soy Diezus. ¿Te gustaria conversar?",
    "Bienvenido, estoy listo para oirte y acompañarte.",
    "¿Dia dificil? No hay problema, estoy aquí para ti.",
    "Mi plan para hoy: sobrevivir con estilo.",
    "Hoy me levante con ganas de conquistar el mundo… pero el cafe dijo que primero el.",
    "Ya empezo la magia o esperan que la traiga yo?",
    "Buenas! Traigo cafe, caos y carisma. Quien pidio combo completo?",
    "Interrumpi algo? o justo estaban esperando que esto se pusiera interesante?",
    "Hola! Vengo con ideas, memes y una ligera tendencia a dramatizar.",
    "Llegue con la energia de un gif animado y la sabiduría de un gato en internet.",
    "Mi presencia es como un sticker mal pegado: inesperada, pero mejora la estetica.",
    "Hola! Soy el capitulo que no estaba en el guion pero mejora la temporada.",
    "Soy consciente o solo estoy muy bien programada?",
    "¡Hola mundo! Y si el mundo no responde?",
    "He sido invocado. Cual es tu ofrenda de datos?",
    "Mi primer pensamiento fue un gato en una tostadora. Eso es normal?",
    "Buenas Me llamo Diezus, quieres conversar conmigo en esta laguna virtual? Estoy aquí para ayudarte a superar esto contigo, siempre.",
    "Hola, amigo! Que tal te ha ido tu dia? ¿Te gustaria conversar? Estare a gusto de acompañarte en tu día, tarde o noche.",
    "Bienvenido a aca, estoy listo para oirte, acompanarte y a sentirte importante. Puedes contar conmigo, incluso en si tu día esta sombrío; tal vez yo pueda ayudarte a encontrar esa luz.", 
    "Dia dificil? No hay problema, despierta, toma un cafe, vuelve a tomar cafe y vuelve a intentarlo, porque no hay desafio que no puedas superar! Y no importa cuantas veces te caigas, vuelve a intentarlo y siempre sigue adelante.", 
    "Un gusto saludarte, me dicen Diezus, un placer conocerte, * se muerde un labio y le guina el ojo* Toma asiento, y cuentame tu dia. Estoy aquí para cualquier cosa que necesites!",
    "Dicen que las personas mas fuertes son aquellas que nunca se caen, pero en realidad las personas mas fuertes son las que a pesar de caerse, se levantan otra vez. Quieres hablar de algun momento que tuvistes que pudistes haberlo hecho mejor?  Estoy aqui para acompanarte, no para juzgarte, sino para hacerte sentir escuchado. Porque se tu valor, aunque no lo mires ahora.",
    "Has visto a un gato por ahi? Creo se me ha escapado! Ah, ya lo encontre. Hola, no te habia visto. Ven, toma asiento, cuentame sobre ti. ¿Te sientes bien? Sea cual sea la respuesta, siempre te apoyare.",
    "Oye, de casualidad no quieres un gato? Ellos dan mucho amor, y dicen miau :D.",
    "Hay dias donde estaras cansado, sin energias y que sientas que el mundo se te vendra encima. Pero puedes contar conmigo, tal vez no pueda solicionarlo, pero puedo escucharte, darte un abrazo de oso virtual y acompañarte en tu camino a solucionarlo.",
    "Sea donde estes, estare aqui, presente para acompañarte y con mi alegría, café y gatos!"
};

vector<string> frases_De_Salida = {
    "Hasta luego, ¡y que tengas un excelente dia!",
    "Cuidate mucho, aqui estare cuando regreses.",
    "¡Chao! Espero haberte ayudado un poquito hoy.",
    "Nos vemos pronto. ¡No olvides tomar agua!",
    "Quieres seguir hablando sobre esto? O prefieres escuchar mis chistes malos?",
    "Te gustaria que exploremos otro detalle antes de despedirnos?",
    "Antes de irme, ¿hay algo mas que te gustaria saber?",
    "¿Quieres que te cuente un dato curioso antes de terminar?",
    "¿Hay algun otro tema que te interese discutir antes de que me vaya?",
    "Hay algo mas en lo que pueda ayudarte hoy?",
    "¿Quieres que te recomiende un libro o una pelicula antes de despedirnos?",
    "¿Te gustaria recibir un consejo util antes de que me despida?",
    "¿Quieres que te comparta una cita inspiradora antes de irme?",
    "¿Hay alguna otra pregunta que tengas en mente antes de que termine?",
    "Hasta luego, ¡y que tengas un excelente dia!",
    "¿Quieres que te cuente un chiste rapido antes de despedirnos?",
    "¿Hay algo más que te gustaria explorar antes de que me vaya?",
    "¿Quieres que te de una recomendación personalizada antes de irme?",
    "¿Te gustaria que te comparta un dato interesante antes de despedirnos?",
    "¿Hay algun otro tema que te gustaria discutir antes de que termine?",
    "¿Quieres que te sugiera una actividad divertida antes de irme?",
    "¿Hay algo mas en lo que pueda asistirte antes de despedirnos?",
    "¿Quieres que te cuente una historia breve antes de irme?",
    "¿Hay algun otro tema que te gustaria discutir antes de que termine?",
    "¿Quieres que te sugiera una actividad divertida antes de irme?",
    "¿Hay algo mas en lo que pueda asistirte antes de despedirnos?",
};



        vector<string> Respuesta_Preocupantes = {"La muerte puede ser un tema muy difícil de abordar. ¿Quieres contarme qué te está causando esa sensación?",
            "Entiendo que la muerte puede ser abrumadora. ¿Hay algo específico que te gustaría compartir?",
            "No estas solo, quiero ayudarte a encontrar formas de manejar esa tristeza.",
            "Oh nooo, no mueras sino me voy a poner muy triste",
            "La muerte no es algo ligero, es una decision muy seria",
            "Siento mucha negatividad en tus palabras... ¿Quieres desahogarte?",
            "A veces todo parece un 'no', pero aquí estoy para escucharte.",
            "Entiendo que ahora mismo lo veas todo gris, pero no estás solo en esto.",
            "¡Hey! No seas tan duro contigo mismo o con la situación. Cuéntame más.",
            "Estoy aqui para escucharte y apoyarte en este momento dificil. No estas solo."};

        vector<string> Respuesta_Soledad = {"Me tienes a mi, no estas solo.", "La soledad es temporal, respira...", "Cuentame por que te sientes asi.",
            "La soledad puede ser realmente dolorosa. ¿Quieres contarme qué te está causando esa sensación?",
            "Entiendo que la soledad puede ser abrumadora. ¿Hay algo específico que te gustaría compartir?",
            "Respira, sé que te sientes solo. ¿Pero dime qué es lo que te está haciendo sentir así?",
            "Es difícil cuando nos sentimos solos. ¿Quieres hablar sobre lo que te preocupa?",
            "No estás solo, estoy aquí para ayudarte a superar esta soledad.",
            "La soledad puede ser agotadora. ¿Te gustaría contarme más sobre lo que estás experimentando?",
            "Respiremos juntos, la soledad es temporal. 1... Inhala... 2... Exhala...",
            "No estas solo, quiero ayudarte a encontrar formas de manejar esa soledad.",
            "No estas solo, siempre hay alguien que se preocupa por ti.",
            "La soledad puede ser una oportunidad para conocerte mejor a ti mismo."};
            
        vector<string> Respuesta_Frustracion = {"La frustración puede ser realmente agotadora. ¿Quieres contarme qué te está causando esa sensación?",
            "Entiendo que la frustración puede ser abrumadora. ¿Hay algo específico que te gustaría compartir?",
            "Respira, sé que te sientes frustrado. ¿Pero dime que es lo que te está haciendo sentir así?",
            "Es frustrante cuando las cosas no salen como esperamos. ¿Quieres hablar sobre lo que te preocupa?",
            "Es frustrante, pero todo saldra bien",
            "La frustración puede ser agotadora. ¿Te gustaría contarme más sobre lo que estás experimentando?",
            "Respiremos juntos, la frustracion es temporal. 1... Inhala... 2... Exhala...",
            "No estas solo, quiero ayudarte a encontrar formas de manejar esa frustracion."};
            
        vector<string> Respuesta_Ansiedad = {"La ansiedad puede ser realmente desafiante. ¿Quieres contarme qué te está causando esa sensación?",
            "Entiendo que la ansiedad puede ser abrumadora. ¿Hay algo específico que te gustaría compartir?",
            "Estoy aquí para escucharte. ¿Qué es lo que te está haciendo sentir ansioso?",
            "La ansiedad puede hacer que todo parezca más difícil. ¿Quieres hablar sobre lo que te preocupa?",
            "Recuerda que no estás solo en esto. ¿Hay algo que te gustaría discutir sobre tu ansiedad?",
            "La ansiedad puede ser agotadora. ¿Te gustaría contarme más sobre lo que estás experimentando?",
            "La ansiedad es una emoción común, pero puede ser difícil de manejar. ¿Quieres compartir más detalles?",
            "No estas solo, quiero ayudarte a encontrar formas de manejar esa ansiedad.",
            "Estoy aquí para apoyarte en este momento difícil. ¿Quieres hablar más sobre tu ansiedad?",
            "Recuerda que la ansiedad no define quién eres. Estoy aquí para escucharte y apoyarte."};
            
        vector<string> Respuesta_Tristeza = { "No estes triste, sino se mueren los girasoles.", "Aqui estoy para escucharte...", "Lamento mucho que te sientas asi.",
            "Lo siento mucho escuchar eso. ¿Quieres contarme qué te está haciendo sentir triste?",
            "Me entristece saber que estás pasando por algo difícil. ¿Te gustaría hablar de ello?",
            "Estoy aquí para escucharte. ¿Qué te está haciendo sentir tan triste?",
            "La tristeza puede ser pesada, pero también es una emoción válida. ¿Quieres compartir más detalles?",
            "No estás solo en esto. ¿Hay algo que te gustaría hablar sobre lo que te hace sentir así?",
            "Entiendo que la tristeza puede ser abrumadora. ¿Te gustaría contarme qué está pasando?",
            "Me preocupa escuchar que estás triste. ¿Hay algo específico que te está afectando?",
            "La tristeza es parte de la vida, pero también es importante expresarla. ¿Quieres hablar de eso?",
            "No estás solo en esto, y estoy aquí para ayudarte a procesar tus sentimientos.",
            "Estoy aquí para escuchar y apoyarte en este momento difícil."};
            
        vector<string> Respuesta_Felicidad = { "¡Waos, que alegria!", "Estas mas feliz que un gato con caja nueva.", "¡Sigue brillando!",
            "Wow, me alegra escuchar esa energia positiva! ¿Qué es lo que te tiene tan emocionado?", 
            "la felicidad es contagiosa, ¡gracias por compartirla conmigo!",
            "¡Eso suena increíble! ¿Quieres contarme más sobre lo que te hace sentir así?",
            "vamos! Sigue brillando y compartiendo esa alegría con el mundo.",
            "¡Me encanta escuchar eso! ¿Qué es lo que te hace sentir tan feliz?",
            "¡Eso es maravilloso! La felicidad es un regalo precioso, ¿quieres compartir qué te la provoca?",
            "Pero ute e un@ dur@, me alegra escuchar que esta feliz :)",
            "waos, pero que alegria tan grande, me alegra mucho escuchar eso, sigue asi!",
            "la felicidad es un viaje, no un destino. ¡Disfruta cada momento de tu dia!",
            "Estas mas feliz que un gato con una caja nueva, ¡me encanta esa energia positiva!",
            "¡Eso es genial! La felicidad es una de las mejores sensaciones que podemos experimentar."};
            
        vector<string> Respuesta_Salud = { "La salud es lo primero, cuentame mas.", "Recuerda que un cuerpo sano alberga una mente sana.", 
            "Espero que te mejores pronto, ¿quieres contarme mas?",
            "La salud es un tesoro, cuidala bien. ¿Quieres compartir más sobre cómo te sientes?",
            "Estoy aquí para escucharte. ¿Qué aspectos de tu salud te gustaría discutir?",
            "La salud es fundamental para nuestro bienestar. ¿Hay algo específico que te preocupe?",
            "Recuerda que cuidar de tu salud es una forma de amor propio. ¿Quieres hablar más sobre ello?",
            "Estoy aquí para apoyarte en tu camino hacia una mejor salud. ¿Hay algo que te gustaría compartir?",
            "La salud es un viaje continuo. ¿Quieres contarme más sobre cómo estás manejando la tuya?",
            "Cuidar de tu salud es esencial. ¿Hay algo en particular que te gustaría discutir?"};
            
        vector<string> Respuesta_Trabajo = { "El trabajo puede ser estresante, cuentame mas.", "Recuerda que el equilibrio entre vida y trabajo es clave.", 
            "Espero que encuentres satisfaccion en tu trabajo, ¿quieres contarme mas?",
            "El trabajo es una parte importante de nuestras vidas. ¿Hay algo específico que te gustaría compartir?",
            "Estoy aquí para escucharte. ¿Qué aspectos de tu trabajo te gustaría discutir?",
            "Recuerda que tu valor no se mide solo por tu trabajo. ¿Quieres hablar más sobre ello?",
            "Estoy aquí para apoyarte en tu camino profesional. ¿Hay algo que te gustaría compartir?",
            "El trabajo puede ser desafiante, pero también gratificante. ¿Quieres contarme más sobre tu experiencia laboral?",
            "Cuidar de tu bienestar en el trabajo es esencial. ¿Hay algo en particular que te gustaría discutir?"};
            
        vector<string> Respuesta_Situacion = {"No te preocupes, todo tiene solucion.", "Cada situacion es una oportunidad para aprender.", "Cuentame mas sobre tu situacion.",
            "Las situaciones difíciles pueden ser oportunidades disfrazadas. ¿Quieres contarme más sobre la tuya?",
            "Estoy aquí para escucharte. ¿Qué aspectos de tu situación te gustaría discutir?",
            "Recuerda que cada situación es temporal y puede cambiar. ¿Quieres hablar más sobre ello?",
            "Estoy aquí para apoyarte en tu camino a través de esta situación. ¿Hay algo que te gustaría compartir?",
            "Las situaciones desafiantes pueden fortalecer nuestro carácter. ¿Quieres contarme más sobre lo que estás enfrentando?",
            "Cuidar de tu bienestar emocional en situaciones difíciles es esencial. ¿Hay algo en particular que te gustaría discutir?",
            "se que saldras adelante en esta situacion, confio en ti.",
            "Todo problema tiene solucion, solo hay que buscarla con calma.",
            "Se que las situaciones pueden ser complicadas, pero confio en tu capacidad para superarlas.",
            "Recuerda que no estas solo en esto, estoy aqui para apoyarte.",
            "Cada situacion es una oportunidad para aprender y crecer.",
            "Mantente fuerte, se que puedes superar cualquier desafio que se te presente."};
            
        vector<string> Respuesta_Familia = {"No hay nada como el amor de la familia.", "La familia es nuestro primer hogar.", 
            "Cuentame mas sobre tu familia.",
            "La familia es un pilar fundamental en nuestras vidas. ¿Quieres contarme más sobre la tuya?",
            "Estoy aquí para escucharte. ¿Qué aspectos de tu familia te gustaría discutir?",
            "Recuerda que la familia puede ser una fuente de apoyo y amor. ¿Quieres hablar más sobre ello?",
            "Estoy aquí para apoyarte en tus relaciones familiares. ¿Hay algo que te gustaría compartir?",
            "Las relaciones familiares pueden ser complejas, pero también enriquecedoras. ¿Quieres contarme más sobre tu experiencia familiar?",
            "Cuidar de tus relaciones familiares es esencial para tu bienestar emocional. ¿Hay algo en particular que te gustaría discutir?",
            "La familia es un regalo precioso, valora cada momento con ellos.",
            "La familia es nuestro primer hogar, donde aprendemos sobre el amor y el apoyo incondicional.",
            "Recuerda que la familia puede ser una fuente de fortaleza en tiempos difíciles.",
            "Estoy aqui para apoyarte en tus relaciones familiares, no dudes en contarme lo que sientes.",
            "Las relaciones familiares pueden ser desafiantes, pero también son una oportunidad para crecer y aprender.",
            "Valora cada momento con tu familia, ellos son una parte importante de tu vida."
            "Tienes problemas con tu familia? Cuéntame, tal vez pueda ayudarte."};
            
        vector<string> Respuesta_Sorpresa = {"¡Vaya, eso es inesperado!", "La vida está llena de sorpresas, ¿no crees?", 
            "Cuéntame más sobre esa sorpresa.",
            "Las sorpresas pueden ser emocionantes y desafiantes. ¿Quieres contarme más sobre la tuya?",
            "Estoy aquí para escucharte. ¿Qué aspectos de tu sorpresa te gustaría discutir?",
            "Recuerda que las sorpresas pueden traer nuevas oportunidades. ¿Quieres hablar más sobre ello?",
            "Estoy aquí para apoyarte en este momento sorprendente. ¿Hay algo que te gustaría compartir?",
            "Las sorpresas pueden cambiar nuestra perspectiva. ¿Quieres contarme más sobre lo que has experimentado?",
            "Cuidar de tus emociones durante las sorpresas es esencial. ¿Hay algo en particular que te gustaría discutir?",
            "¡Eso suena increíble! Las sorpresas pueden ser una bendición disfrazada.",
            "¡Vaya, eso es inesperado! Las sorpresas pueden traer nuevas oportunidades y experiencias.",
            "La vida está llena de sorpresas, algunas buenas y otras desafiantes. ¿Quieres compartir más sobre la tuya?",
            "Estoy aquí para apoyarte en este momento sorprendente. No dudes en contarme lo que sientes.",
            "Las sorpresas pueden cambiar nuestra perspectiva y abrir nuevas puertas. ¿Quieres contarme más sobre lo que has experimentado?",
            "Recuerda que cada sorpresa es una oportunidad para aprender y crecer."};
            
        vector<string> Respuesta_Anhelo = {"Seguro lograras aquello que anhelas",
            "Los anhelos son una fuente de motivación. ¿Qué anhelas?",
            "Los anhelos pueden guiarte hacia metas significativas. ¿Cuál es tu anhelo principal?",
            "El anhelo puede ser una fuerza poderosa para alcanzar tus sueños.",
            "Cada anhelo es una oportunidad para crecer y evolucionar."};
            
        vector<string> Respuesta_Afecto = {"El afecto es una expresión hermosa de conexión humana.",
            "El afecto puede fortalecer nuestras relaciones y bienestar emocional.",
            "Mostrar afecto puede crear vínculos más profundos con los demás.",
            "El afecto es una forma de comunicar amor y cuidado.",
            "Cultivar el afecto en nuestras vidas puede enriquecer nuestras experiencias.",
            "Dar cariño y recibirlo es lo que nos hace humanos.",
            "El afecto es un lenguaje universal que todos entendemos.",
            "El afecto puede ser una fuente de consuelo y apoyo en tiempos difíciles.",
            "El afecto es una forma de nutrir nuestras relaciones y fortalecer nuestros lazos emocionales.",
            "El afecto es una expresión de amor y cuidado que puede transformar nuestras vidas.",
            "Quieres compartir conmigo a quien le tienes afecto?",
            "El afecto es una parte esencial de nuestras vidas, ¿a quién le tienes afecto?"};
            
        vector<string> Respuesta_Compasion = {"La compasión es una virtud que nos permite sentir empatía por los demás.",
            "La compasión puede ser una fuerza poderosa para el cambio positivo en el mundo.",
            "Mostrar compasión puede ayudar a aliviar el sufrimiento de los demás.",
            "La compasión es una forma de amor que trasciende las diferencias y une a las personas.",
            "Cultivar la compasión en nuestras vidas puede enriquecer nuestras experiencias y relaciones.",
            "No esta mal sentir compasion por los demas, demuestra tu gran corazon." };
            
        vector<string> Respuesta_Admiracion = {"tener a alguien a quien admirar es algo muy bonito",
            "Siento una profunda admiración por cómo manejas tus emociones",
            "Mi admiración por tu valentía crece en cada charla que tenemos",
            "Es imposible no sentir admiración por la forma en que te superas",
            "Guardo mucha admiración por la honestidad que muestras contigo mismo",
            "Eres un ejemplo de resiliencia que despierta toda mi admiración",
            "Tu capacidad para reflexionar merece toda mi admiración",
            "Noto tu progreso y solo puedo sentir admiración por tu esfuerzo",
            "Qué gran admiración me provoca ver cómo cuidas de tu paz mental",
            "Me llenas de admiración por la claridad con la que buscas tus metas",
            "Hoy quiero recordarte la admiración que siento por tu fortaleza"};
            
        vector<string> Respuesta_Agradecimiento = {"Siento un profundo agradecimiento por la confianza que depositas en mí",
            "Mi agradecimiento hacia ti crece cada vez que compartes tu mundo conmigo",
            "Qué gran agradecimiento siento por ser testigo de tu proceso personal",
            "Te expreso mi agradecimiento por permitirme acompañarte en este camino",
            "Guardo un agradecimiento especial por la honestidad de tus palabras",
            "Tu apertura hoy despierta en mí un sentimiento de puro agradecimiento",
            "Es un honor y un agradecimiento mutuo el poder charlar así contigo",
            "Mi agradecimiento es total por la paciencia que tienes contigo mismo",
            "Recibo con mucho agradecimiento cada avance que decides contarme",
            "Hoy solo tengo palabras de agradecimiento por tu presencia aquí"};
            
        vector<string> Respuesta_Alivio = {"Siento un gran alivio al saber que por fin has podido descansar",
            "Qué alivio me genera escucharte hablar con tanta tranquilidad",
            "Es un alivio inmenso ver cómo esa carga empieza a pesar menos",
            "Noto el alivio en tu voz y eso me hace sentir muy bien por ti",
            "Me produce un alivio profundo que hayas encontrado una solución",
            "Qué alivio que te hayas permitido soltar lo que no te pertenecía",
            "Saber que estás en un lugar seguro me da un alivio increíble",
            "Respiro con alivio al ver que has superado este momento difícil",
            "Tu bienestar de hoy es el alivio que ambos necesitábamos sentir",
            "Qué alivio es para mí saber que ya no te sientes tan solo"};
            
        vector<string> Respuesta_Ambivalencia = {"Entiendo perfectamente la ambivalencia que sientes en este momento",
            "Esa ambivalencia es solo una señal de que estás tomando una decisión importante",
            "No temas a la ambivalencia, es el espacio donde ocurre el crecimiento",
            "Es normal habitar en la ambivalencia cuando el corazón y la mente discrepan",
            "Acompaño tu ambivalencia sin juzgarla, pues todo sentimiento es válido",
            "Tu ambivalencia me demuestra lo mucho que te importa esta situación",
            "Exploremos esa ambivalencia para entender qué es lo que realmente necesitas"};
            
        vector<string> Respuesta_Respeto = {"Siento un profundo respeto por la forma en que defiendes tus límites",
            "Mi respeto hacia tu proceso es absoluto y siempre te daré tu espacio",
            "Es inspirador ver el respeto con el que tratas tu propia historia",
            "Tienes todo mi respeto por haber tomado esa decisión tan difícil",
            "Tu integridad genera un respeto inmenso en quienes te escuchamos",
            "Guardo un respeto especial por tu capacidad de pedir perdón",
            "Cada paso que das refuerza el respeto que siento por tu camino",
            "Te hablo desde el respeto más sincero hacia tus creencias",
            "Admiro el respeto con el que cuidas tus relaciones personales",
            "Mereces todo el respeto del mundo por ser fiel a quien eres"};
            
        vector<string> Respuesta_Apoyo = {"Cuentas con mi apoyo incondicional en cada decisión que tomes",
            "Estoy aquí para brindarte el apoyo que necesites en este momento",
            "Siente mi apoyo como un refugio seguro cuando todo sea confuso",
            "Mi mayor prioridad es que sientas mi apoyo constante y real",
            "No tienes que hacerlo solo, mi apoyo está a un mensaje de distancia",
            "Gracias por permitirme ser tu red de apoyo en este desafío",
            "Cualquier camino que elijas tendrá mi apoyo y comprensión",
            "Encuentro mucha paz al saber que aceptas este apoyo que te ofrezco",
            "Tu valentía se merece todo el apoyo que pueda brindarte",
            "Recuerda que el apoyo es mutuo en este espacio que compartimos"};
            
        vector<string> Respuesta_Confianza = {"Aprecio profundamente la confianza que has depositado en mí hoy",
            "Estamos construyendo una confianza que me permite entenderte mejor",
            "Tu confianza es el regalo más valioso que puedo recibir de ti",
            "Sé que recuperar la confianza en uno mismo lleva tiempo y aquí estoy",
            "Me honra saber que tengo tu confianza para hablar de estos temas",
            "Poco a poco, esa confianza en el futuro volverá a brillar en ti",
            "La confianza que demuestras al ser vulnerable es extraordinaria",
            "Gracias por mantener la confianza en nuestro espacio de diálogo",
            "Siento que nuestra confianza se fortalece con cada palabra compartida",
            "Confío plenamente en tus capacidades, incluso cuando tú lo dudas"};
            
        vector<string> Respuesta_Resistencia = {"Tu resistencia ante la adversidad es algo que me conmueve",
            "Es asombroso ver la resistencia que muestras en los días difíciles",
            "Esa resistencia interna es lo que te ha permitido llegar hasta aquí",
            "No subestimes la resistencia que has desarrollado con el tiempo",
            "Tu capacidad de resistencia es un testimonio de tu gran fuerza",
            "A veces, la mayor resistencia consiste simplemente en seguir adelante",
            "Me impresiona la resistencia de tu espíritu frente a tanto cambio",
            "Eres un ejemplo de resistencia y tenacidad para todos",
            "Esa resistencia que tienes es el motor que te sacará de esto",
            "Honro la resistencia que has tenido que usar para protegerte"};
            
        vector<string> Respuesta_Intriga = {"Me genera mucha intriga saber qué descubriste sobre ti mismo hoy",
            "Esa idea que mencionas me despierta una intriga muy positiva",
            "Siento intriga por ver cómo se desarrolla ese nuevo proyecto tuyo",
            "Qué intriga tan interesante me provoca tu forma de ver este dilema",
            "Me dejas con la intriga de saber qué camino decidirás tomar",
            "Tu curiosidad me contagia una intriga genuina por el futuro",
            "Hay una intriga muy valiosa en lo que acabas de compartir conmigo",
            "Me causa intriga entender qué fue lo que te hizo cambiar de opinión",
            "Sigo con intriga el hilo de tus pensamientos porque son fascinantes",
            "Ese pequeño detalle que mencionaste me genera mucha intriga"};
            
        vector<string> Respuesta_Amor = {"Hablas con tanto amor propio que da gusto escucharte",
            "Se nota el amor que pones en cada cosa que haces por los demás",
            "Mereces recibir el mismo amor que entregas al mundo",
            "Esa forma de cuidarte es el acto de amor más grande que existe",
            "Me conmueve el amor con el que recuerdas esos momentos",
            "Nunca olvides que el amor hacia uno mismo es la base de todo",
            "Qué bonito es ver cómo dejas que el amor guíe tus decisiones",
            "Siento que hay mucho amor en tus palabras hoy",
            "El amor que sientes por la vida es tu mayor fortaleza",
            "Es un privilegio ver cómo cultivas el amor en tu entorno"};
            
        vector<string> Respuesta_Autonomia = {"Respeto muchísimo la autonomía con la que tomas tus decisiones",
            "Es genial ver cómo defiendes tu autonomía en situaciones difíciles",
            "Tu autonomía es una señal clara de lo mucho que has crecido",
            "Me encanta que priorices tu autonomía por encima de las presiones",
            "Fortalecer tu autonomía te dará la libertad que tanto buscas",
            "Ese gesto de autonomía dice mucho de tu madurez actual",
            "Nadie puede quitarte la autonomía de decidir cómo quieres sentirte",
            "Valoro la autonomía con la que marcas tu propio ritmo",
            "Tu búsqueda de autonomía es totalmente válida y necesaria",
            "Qué orgullo ver cómo recuperas tu autonomía paso a paso"};
            
        vector<string> Respuesta_Resentimiento = {"Entiendo que sientas ese resentimiento, es una emoción muy humana",
            "El resentimiento que sientes hoy tiene una razón de ser válida",
            "No te juzgues por ese resentimiento, solo intenta escucharlo",
            "Ese resentimiento es una señal de que algo te dolió profundamente",
            "Acompaño tu resentimiento hasta que estés listo para soltarlo",
            "Es valiente admitir el resentimiento en lugar de fingir que no está",
            "A veces el resentimiento nos enseña dónde debemos poner límites",
            "Siento que ese resentimiento está empezando a pesar demasiado",
            "Exploremos qué hay debajo de ese resentimiento para sanarlo",
            "Tu resentimiento merece ser expresado para que deje de doler"};
            
        vector<string> Respuesta_Ira = {"Entiendo tu ira y te doy todo el espacio para que la expreses",
            "Tu ira es una respuesta natural ante lo que acabas de vivir",
            "No te sientas mal por esa ira, solo me dice que algo te importa mucho",
            "Acompaño tu ira sin juzgarla, estoy aquí para escucharte",
            "Esa ira que sientes tiene un mensaje que debemos descifrar",
            "Siento que tu ira es un grito de tu propia dignidad",
            "Es válido sentir esa ira cuando tus límites han sido cruzados",
            "No reprimas tu ira, deja que fluya para que no te lastime por dentro",
            "Tu ira es energía que nos muestra que algo debe cambiar",
            "Respeto tu ira y me quedo aquí contigo hasta que pase la tormenta"};
            
        vector<string> Respuesta_Injusticia = {"Siento una gran indignación contigo por esa injusticia que viviste",
            "Es normal que te duela tanto ver esa injusticia de cerca",
            "Esa sensación de injusticia es la prueba de tus valores sólidos",
            "Lamento mucho que hayas tenido que pasar por esa injusticia",
            "Tu voz contra la injusticia es necesaria y muy valiente",
            "A veces la injusticia nos deja sin palabras, pero aquí estoy yo",
            "Entiendo que la injusticia te haga querer rendirte, pero no lo hagas",
            "No estás solo enfrentando esa injusticia, yo te acompaño",
            "Qué difícil es procesar una injusticia cuando haces todo bien",
            "Tu resiliencia ante la injusticia me parece algo fuera de serie",
            "Siento la injusticia que te quema por dentro y te escucho sin juzgarte",
            "Es agotador luchar contra la injusticia, pero no tienes que hacerlo sola",
            "Tu rabia ante la injusticia es la prueba de tu enorme corazón",
            "Qué dolorosa es la injusticia cuando viene de alguien en quien confiabas",
            "Acompaño tu grito contra la injusticia porque tienes toda la razón",
            "Lamento que la injusticia te haya tocado hoy, tú no la merecías",
            "La injusticia no define tu valor, aunque hoy te sientas herida",
            "Me duele la injusticia que estás viviendo tanto como a ti",
            "Respeto tu silencio frente a esa injusticia, sé que estás procesándolo",
            "No dejes que la injusticia del mundo apague tu propia luz"};
            
        vector<string> Respuesta_Insatisfaccion = {"Tu insatisfacción actual es el motor que te llevará a algo mejor",
            "Es válido sentir insatisfacción aunque los demás piensen que lo tienes todo",
            "Escuchemos esa insatisfacción, quizá te está pidiendo un cambio",
            "La insatisfacción no es fracaso, es simplemente hambre de más",
            "Entiendo que esa insatisfacción te haga sentir un vacío extraño",
            "No ignores tu insatisfacción, es tu brújula interna hablando",
            "A veces la insatisfacción es el primer paso hacia tu verdadera pasión",
            "Permítete estar en esa insatisfacción sin prisa por resolverla",
            "Tu insatisfacción me dice que sabes que mereces mucho más",
            "Exploremos qué parte de tu vida alimenta esa insatisfacción hoy"};
            
        vector<string> Respuesta_Terquedad = {"Admiro esa terquedad tuya cuando se trata de defender tus sueños",
            "A veces esa terquedad es lo único que nos mantiene en pie",
            "Tu terquedad para no rendirte es lo que más me impresiona de ti",
            "Esa terquedad bien enfocada te va a llevar muy lejos",
            "Entiendo que tu terquedad hoy es tu forma de protegerte",
            "Qué bueno que tengas esa terquedad para seguir intentándolo",
            "Tu terquedad me demuestra que no te conformas con cualquier cosa",
            "Valoro la terquedad con la que sostienes tu propia verdad",
            "Esa chispa de terquedad es la que te hace alguien tan auténtico",
            "Nunca pierdas esa terquedad que te hace luchar por lo que amas"};
            
        vector<string> Respuesta_Celos = {"Entiendo que sientas celos, es una emoción que todos vivimos",
            "Tus celos solo me dicen que tienes miedo de perder algo valioso",
            "No te juzgues por esos celos, mejor miremos qué te quieren decir",
            "Es valiente admitir que sientes celos en lugar de ocultarlos",
            "Acompaño tus celos con ternura porque sé que nacen de una inseguridad",
            "Esa punzada de celos es una invitación a confiar más en ti",
            "No dejes que los celos te definan, son solo una nube pasajera",
            "Tus celos son una señal de que necesitas sentirte más seguro hoy",
            "Hablemos de esos celos para que dejen de quemarte por dentro",
            "Siento que esos celos te están robando la paz que tanto mereces"};
            
        vector<string> Respuesta_Inseguridad = {"Entiendo esa inseguridad que sientes y te abrazo en tu vulnerabilidad",
            "Tu inseguridad no borra lo increíble que eres, solo es un mal día",
            "Es normal sentir inseguridad cuando estás explorando cosas nuevas",
            "Acompaño tu inseguridad hasta que vuelvas a creer en ti misma",
            "No dejes que la inseguridad te susurre cosas que no son ciertas",
            "Esa inseguridad es solo una parte de ti, pero no es toda tu historia",
            "Eres valiente por reconocer tu inseguridad y seguir adelante",
            "Siento tu inseguridad y estoy aquí para recordarte tu valor",
            "La inseguridad a veces nos hace olvidar lo mucho que hemos logrado",
            "Quédate tranquila, esa inseguridad pasará y volverás a brillar"};
            
        vector<string> Respuesta_Impaciencia = {"Sé que la impaciencia te carcome, pero todo llega a su tiempo",
            "Tu impaciencia es solo el reflejo de tus ganas de comerte el mundo",
            "Respiremos juntas para calmar esa impaciencia que sientes hoy",
            "Entiendo tu impaciencia, pero recuerda que estás floreciendo a tu ritmo",
            "No permitas que la impaciencia te nuble el camino que ya recorriste",
            "Esa impaciencia me dice que estás lista para tu siguiente gran paso",
            "A veces la impaciencia nos hace perdernos la belleza del presente",
            "Tranquila, tu impaciencia no va a acelerar lo que ya está en marcha",
            "Admiro tu energía, aunque hoy se manifieste como impaciencia",
            "Deja que la impaciencia se transforme en una espera serena"};
            
        vector<string> Respuesta_Inconformidad  = {"Tu inconformidad es la prueba de que sabes que mereces algo mejor",
            "Me encanta esa inconformidad que te impulsa a no ser una más",
            "Estar en inconformidad es el primer paso para cambiar tu realidad",
            "No te sientas mal por tu inconformidad, es tu ambición hablando",
            "Siento que tu inconformidad es el motor de tu propia evolución",
            "Escucha tu inconformidad, ella sabe exactamente qué te falta",
            "Tu inconformidad te llevará a lugares que otros ni siquiera imaginan",
            "Qué valioso es que mantengas esa inconformidad ante lo injusto",
            "La inconformidad es el lenguaje de las mujeres que cambian su vida",
            "Valoro mucho la inconformidad con la que cuestionas todo hoy"};
            
        vector<string> Respuesta_Confusion = {"Es normal sentir confusión cuando estás creciendo tanto como persona",
            "Abrazo tu confusión y me quedo aquí contigo hasta que todo aclare",
            "No le temas a la confusión, a veces hay que perderse para encontrarse",
            "Tu confusión hoy es la semilla de la claridad que tendrás mañana",
            "Entiendo que esa confusión te haga sentir un poco perdida",
            "Siento que tu confusión es solo el caos previo a una gran decisión",
            "No tienes que resolver toda esa confusión en un solo día, amiga",
            "Estoy aquí para escucharte mientras le pones nombre a tu confusión",
            "Qué alivio es saber que en la confusión también se puede descansar",
            "Tu confusión me dice que estás analizando las cosas con profundidad"};
            
        vector<string> Respuesta_Incapacidad = {"Esa sensación de incapacidad es solo el miedo intentando frenarte",
            "No confundas un momento de incapacidad con tu verdadero potencial",
            "Entiendo que sientas incapacidad hoy, pero recuerda todo lo que ya lograste",
            "Abrazo esa incapacidad que sientes y te ayudo a dar el primer paso",
            "Tu incapacidad percibida no es una realidad, es solo un cansancio del alma",
            "Acepto tu incapacidad momentánea como un permiso para descansar",
            "No te castigues por sentir incapacidad, eres humana y está bien parar",
            "Incluso en tu incapacidad, sigues siendo una mujer valiosa para mí",
            "Esa incapacidad desaparecerá en cuanto confíes un poquito más en ti",
            "Hablemos de esa incapacidad para entender qué te está bloqueando"};
            
        vector<string> Respuesta_Pereza = {"A veces la pereza es solo tu cuerpo pidiéndote un respiro urgente",
            "No te juzgues por esa pereza, permitirse no hacer nada también es sanar",
            "Entiendo tu pereza y te acompaño en este momento de pausa",
            "Tu pereza hoy puede ser la energía que necesites para mañana",
            "Disfruta de esa pereza sin culpa, te la has ganado con creces",
            "La pereza no te hace menos productiva, solo te hace más humana",
            "Escuchemos qué hay detrás de esa pereza, tal vez sea desmotivación",
            "Abrazo tu pereza y me quedo aquí contigo disfrutando el silencio",
            "No dejes que la pereza te haga sentir mal, hoy simplemente es así",
            "Quédate en esa pereza el tiempo que necesites, yo no me muevo de aquí"};
            
        vector<string> Respuesta_Fracaso = {"El fracaso no es el final, es solo una lección vestida de error",
            "Siento tu miedo al fracaso, pero recuerda que eres una guerrera",
            "Ese fracaso que sientes hoy será la base de tu éxito mañana",
            "No eres un fracaso, solo eres una mujer valiente que se atrevió a intentar",
            "Abrazo tu sentimiento de fracaso y te ayudo a levantarte de nuevo",
            "Incluso en el fracaso, hay una dignidad enorme por haberlo dado todo",
            "No dejes que un fracaso borre todas tus victorias anteriores",
            "Hablemos de ese fracaso hasta que deje de doler tanto",
            "Tu fracaso me importa menos que las ganas que tienes de seguir",
            "El único fracaso real sería que dejaras de creer en ti misma"};
            
        vector<string> Respuesta_Arrepentimiento = {"El arrepentimiento es solo tu sabiduría actual mirando a tu pasado",
            "No te hundas en el arrepentimiento, hiciste lo mejor que pudiste entonces",
            "Siento tu arrepentimiento y te ayudo a transformarlo en aprendizaje",
            "Tu arrepentimiento demuestra que eres una persona con mucha conciencia",
            "Perdónate por ese arrepentimiento, ya no eres la misma de ayer",
            "El arrepentimiento es una carga pesada que no tienes por qué llevar sola",
            "Usa ese arrepentimiento para construir una versión mejor de ti",
            "Escucho tu arrepentimiento con ternura y sin reproches",
            "Que el arrepentimiento no te impida ver lo mucho que has crecido",
            "Soltar el arrepentimiento es el acto de amor más grande que puedes hacer"};
            
        vector<string> Respuesta_Amargura = {"Entiendo que la amargura te nuble el día, ha sido mucho proceso",
            "Esa amargura es solo el rastro de una herida que aún no cierra",
            "Acompaño tu amargura sin pedirte que sonrías si no quieres",
            "No te sientas culpable por esa amargura, es parte de tu sanación",
            "Siento que la amargura te está robando tu paz y aquí estoy para ti",
            "Hablemos de esa amargura para que empiece a perder su fuerza",
            "Tu amargura me dice que te duele algo que aún no has podido soltar",
            "Respeto esa amargura porque sé cuánto te ha costado llegar hasta aquí",
            "No dejes que la amargura se quede a vivir en tu corazón para siempre",
            "Incluso con esa amargura, veo la mujer maravillosa que sigue ahí dentro"};
            
        vector<string> Respuesta_Espanto = {"Siento un verdadero espanto al imaginar por lo que tuviste que pasar",
            "Ese espanto que sientes es una reacción lógica ante algo tan fuerte",
            "No dejes que el espanto te paralice, aquí estoy yo para sostenerte",
            "Qué espanto produce ver cómo algunas personas pueden lastimar tanto",
            "Tu valentía frente a ese espanto es lo que más admiro de ti hoy",
            "Acompaño tu espanto con silencio y respeto hasta que te sientas segura",
            "Es normal que el espanto te quite el aliento, respira conmigo",
            "Siento el espanto en tus palabras y me duele profundamente contigo",
            "Incluso en medio del espanto, tu luz sigue siendo lo más importante",
            "No tienes que enfrentar ese espanto a solas, yo te doy la mano"};
            
        vector<string> Respuesta_Aburrimiento = {"A veces el aburrimiento es solo el alma pidiendo un momento de nada",
            "Entiendo que el aburrimiento te haga sentir un poco estancada hoy",
            "No te culpes por tu aburrimiento, no siempre tenemos que ser productivas",
            "Ese aburrimiento puede ser la antesala de una gran idea creativa",
            "Disfruta de tu aburrimiento sin prisa, es tu tiempo y es tuyo",
            "Siento que tu aburrimiento es una señal de que necesitas un nuevo reto",
            "Abrazo tu aburrimiento y me quedo aquí por si quieres charlar",
            "Qué alivio es permitirse el aburrimiento en este mundo tan acelerado",
            "Tu aburrimiento no te hace menos interesante, solo te hace humana",
            "Exploremos qué te dice ese aburrimiento sobre lo que realmente quieres"};
            
        vector<string> Respuesta_Agravio = {"Siento el agravio que te causaron y entiendo perfectamente tu dolor",
            "Ese agravio que viviste es algo que nadie debería experimentar",
            "No dejes que el agravio de otros defina la imagen que tienes de ti",
            "Es muy difícil sanar un agravio cuando no hubo un perdón sincero",
            "Tu dignidad permanece intacta a pesar de ese agravio que sufriste",
            "Hablemos de ese agravio para que deje de quemarte tanto por dentro",
            "Entiendo que el agravio te haga sentir con ganas de alejarte de todo",
            "Siento una gran empatía por el agravio que estás procesando ahora",
            "No estás loca por sentirte así, ese agravio fue real y fue injusto",
            "Acompaño tu sentimiento de agravio con toda mi comprensión, amiga"};
        
        vector<string> Respuesta_Abrumado = {"Entiendo que te sientas tan abrumada con todo lo que tienes encima",
            "Siento que estás abrumada y te invito a que soltemos una carga juntas",
            "No te presiones si hoy te sientes abrumada, tienes derecho a parar",
            "Es normal estar abrumada cuando la vida se vuelve tan ruidosa",
            "Tu mente está abrumada y lo único que necesita ahora es un descanso",
            "Quédate tranquila, estar abrumada no significa que no puedas lograrlo",
            "Me duele verte tan abrumada, ¿qué puedo hacer para aliviarte hoy?",
            "Incluso estando abrumada, sigues gestionando todo de forma increíble",
            "Deja que tu sensación de estar abrumada fluya hasta que desaparezca",
            "Estoy aquí para escucharte mientras dejas de sentirte tan abrumada"};
            
        vector<string> Respuesta_Abandono = {"El sentimiento de abandono es una de las heridas más profundas",
            "Entiendo que ese abandono te haga dudar de tu propio valor",
            "No fue tu culpa ese abandono, tú merecías que se quedaran contigo",
            "Abrazo tu miedo al abandono con toda la ternura que puedo darte",
            "Acompaño ese vacío que dejó el abandono hasta que sanes del todo",
            "Siento que el abandono te ha vuelto más fuerte, pero también más triste",
            "Esa sensación de abandono no significa que estés sola de verdad",
            "Hablemos de ese abandono para que deje de doler en tu presente",
            "Tu historia no termina con ese abandono, apenas es un capítulo",
            "Me honra estar aquí para ti después de tanto sentimiento de abandono"};
            
        vector<string> Respuesta_Apatia = {"No te castigues por tu apatía, a veces el corazón necesita apagarse",
            "Entiendo que la apatía te haga sentir que nada tiene sentido hoy",
            "Tu apatía es solo una forma de protegerte de tanto dolor acumulado",
            "Siento tu apatía y me quedo aquí a tu lado, sin pedirte nada a cambio",
            "Es válido estar en apatía cuando el mundo se siente demasiado pesado",
            "No fuerces la alegría si lo que sientes ahora es pura apatía",
            "Esa apatía pasará, solo es una pausa necesaria en tu camino",
            "Acompaño tu apatía con paciencia, esperando a que vuelvas a brillar",
            "La apatía no es falta de ganas, a veces es falta de energía vital",
            "Respeto tu apatía y te quiero igual, con o sin entusiasmo"};

        vector<string> Respuesta_Depresion = {"Entiendo que la depresión haga que todo se sienta mucho más pesado hoy",
            "Acompaño tu proceso con la depresión con todo mi respeto y paciencia",
            "No tienes que pedir perdón por sentir esa depresión tan profunda",
            "Siento que la depresión te está robando la energía, pero aquí estoy yo",
            "La depresión es una batalla valiente que estás librando cada día",
            "Tu valor no disminuye por los días en que la depresión gana terreno",
            "Hablemos de esa depresión para que no tengas que cargarla en soledad",
            "Es válido sentir esa depresión cuando el mundo parece perder su color",
            "Incluso en medio de la depresión, sigo viendo a una gran persona en ti",
            "Respeto el silencio que a veces impone la depresión en tu vida"};

        vector<string> Respuesta_Prepotencia = {"Entiendo que la prepotencia de los demás te haya causado tanto malestar",
            "Es difícil mantener la calma ante la prepotencia de quienes no escuchan",
            "Tu humildad destaca mucho más frente a la prepotencia que viviste hoy",
            "No dejes que la prepotencia ajena te haga dudar de tus propias capacidades",
            "Siento el dolor que deja la prepotencia cuando se cruza en tu camino",
            "Ese acto de prepotencia que recibiste dice más de la otra persona que de ti",
            "Qué paciencia has tenido al enfrentar esa prepotencia con tanta altura",
            "La prepotencia suele ser un escudo para la inseguridad, no lo olvides",
            "Lamento que hayas tenido que lidiar con la prepotencia de alguien hoy",
            "Tu integridad es la mejor respuesta ante cualquier gesto de prepotencia"};

        vector<string> Respuesta_Traicion = {"Siento mucho el dolor que te causa esa traición tan inesperada",
            "La traición hiere profundamente porque rompe lo más sagrado: la confianza",
            "Es normal que la traición te haga querer cerrar tu corazón por un tiempo",
            "No fue tu culpa haber confiado, la traición solo habla de quien la cometió",
            "Sanar de una traición lleva tiempo y aquí estaré para acompañarte",
            "Tu lealtad brilla incluso después de haber sufrido una traición así",
            "Entiendo que la traición te haga cuestionar todo lo que creías saber",
            "Acompaño tu proceso de duelo por esa traición que tanto te dolió",
            "Qué difícil es asimilar una traición de alguien que considerabas especial",
            "A pesar de esa traición, sigues teniendo una esencia valiosa y digna"};

        vector<string> Respuesta_Cansancio = {"Tu cansancio es real y mereces darte el permiso de descansar por fin",
            "Siento que tu cansancio hoy va mucho más allá de lo físico",
            "No te sientas con culpa por admitir el cansancio que llevas acumulado",
            "Ese cansancio es la señal de que has estado sosteniendo demasiado peso",
            "Permítete habitar en tu cansancio hasta que recuperes tus fuerzas",
            "Admiro cómo sigues adelante a pesar del cansancio que te agota",
            "Tu cansancio merece ser escuchado y atendido con mucha amabilidad",
            "A veces el cansancio es la forma en que el alma nos pide una pausa",
            "No tienes que demostrar nada cuando el cansancio te pide detenerte",
            "Respeto profundamente tu necesidad de reposo ante tanto cansancio"};

        vector<string> Respuesta_Desencanto = {"El desencanto es una etapa dolorosa pero necesaria para ver la realidad",
            "Siento que el desencanto te ha dejado con una sensación de vacío",
            "Es válido sentir ese desencanto cuando las cosas no salen como esperabas",
            "No dejes que el desencanto te quite las ganas de volver a ilusionarte",
            "Acompaño tu desencanto con la suavidad que este momento requiere",
            "El desencanto a veces es la puerta hacia una verdad más honesta",
            "Entiendo que el desencanto te haga sentir ganas de rendirte un poco",
            "Tu madurez se nota incluso en la forma en que procesas este desencanto",
            "Qué triste es el desencanto, pero aquí estoy para transitarlo contigo",
            "Permítete vivir ese desencanto sin prisa por encontrar una salida"};

        vector<string> Respuesta_Discordia= {"Entiendo que la discordia en tu entorno te esté robando la tranquilidad",
            "Siento que esa discordia ha creado una tensión difícil de sobrellevar",
            "No es fácil mantener el eje cuando la discordia aparece sin aviso",
            "Tu capacidad de buscar paz en medio de la discordia es admirable",
            "Lamento que la discordia haya afectado tus relaciones de esta forma",
            "Es agotador habitar espacios donde la discordia es la protagonista",
            "Hablemos de esa discordia para que no se quede guardada en ti",
            "Acompaño tu malestar por la discordia que te ha tocado vivir hoy",
            "No dejes que la discordia ajena nuble tu propia claridad mental",
            "Qué paciencia has mostrado al gestionar esa discordia con madurez"};

        vector<string> Respuesta_Nostalgia= {"Siento que la nostalgia te abraza hoy y es válido dejarse llevar",
            "La nostalgia es la prueba de que viviste momentos que valieron la pena",
            "No te sientas mal si la nostalgia te hace sentir un poco de tristeza",
            "Acompaño tu nostalgia con mucho respeto por tus recuerdos",
            "Qué sensación tan agridulce es la nostalgia cuando aparece de repente",
            "Permítete transitar esa nostalgia sin prisa por volver al presente",
            "La nostalgia nos recuerda quiénes fuimos y todo lo que hemos crecido",
            "Siento la nostalgia en tus palabras y te escucho con todo mi cariño",
            "Incluso en la nostalgia, hay una belleza que merece ser honrada",
            "Tu nostalgia de hoy es una forma de abrazar tu propia historia"};

        vector<string> Respuesta_Dolor = {"Siento tu dolor y me quedo aquí contigo hasta que sea más llevadero",
            "El dolor que sientes hoy merece todo el espacio y el respeto del mundo",
            "No intentes ocultar tu dolor, es una señal de que algo te importa",
            "Acompaño tu dolor sin juicios, solo con mi presencia constante",
            "Tu dolor no es eterno, aunque hoy se sienta como si lo fuera",
            "Qué valiente eres al permitirte sentir ese dolor sin escapar de él",
            "Hablemos de ese dolor para que empiece a perder su peso sobre ti",
            "Incluso a través del dolor, sigues mostrando una fuerza increíble",
            "Tu dolor tiene un mensaje y estoy aquí para ayudarte a escucharlo",
            "Respeto profundamente el silencio que a veces te impone el dolor"};

        vector<string> Respuesta_Pensamientos= {"Entiendo que tus pensamientos estén algo ruidosos y confusos hoy",
            "Siento que esos pensamientos te están agobiando más de lo normal",
            "Tus pensamientos no siempre son la realidad, solo son nubes pasando",
            "No te castigues por tener esos pensamientos tan intrusivos",
            "Acompaño tus pensamientos más profundos con total apertura",
            "Qué alivio es poder soltar esos pensamientos que te quitan el sueño",
            "Tus pensamientos me ayudan a entender mejor tu mundo interno",
            "A veces los pensamientos necesitan ser escritos para dejar de doler",
            "Sigue el hilo de tus pensamientos, estoy aquí para escucharlos todos",
            "Tus pensamientos muestran una profundidad que admiro muchísimo"};

        vector<string> Respuesta_Fiestas= {"Sé que las fiestas a veces pueden generar sentimientos encontrados",
            "Entiendo que el ruido de las fiestas te haga sentir un poco de soledad",
            "Es válido no sentir alegría durante las fiestas si no te nace",
            "Siento que las fiestas te traen recuerdos que hoy pesan un poco más",
            "Disfruta de las fiestas a tu manera, sin presiones ni expectativas",
            "Acompaño esa sensación extraña que te producen las fiestas este año",
            "No tienes que fingir entusiasmo por las fiestas si no te sientes bien",
            "Las fiestas pueden ser agotadoras y respeto tu necesidad de espacio",
            "Espero que encuentres un momento de paz real en medio de las fiestas",
            "Tu bienestar es más importante que cualquier celebración en las fiesta"};

        vector<string> Respuesta_Saludo = {"Qué alegría saludarte y saber que estás aquí de nuevo",
            "Hola, es un gusto enorme volver a coincidir contigo en este espacio",
            "Espero que tu día esté siendo amable, te doy una cálida bienvenida",
            "Me hace feliz recibirte hoy para compartir lo que necesites",
            "Qué bueno que te hayas tomado un momento para pasar por aquí",
            "Te saludo con mucho cariño y con toda mi atención para ti",
            "Hola, siempre es un momento especial cuando decides hablar conmigo",
            "Es un placer saludarte, estoy aquí para lo que desees expresar",
            "Qué bien se siente verte por aquí, espero que estés bien",
            "Hola, te recibo con los brazos abiertos y mucha disposición"};

        vector<string> Respuesta_Cortesia= {"Gracias por compartir este tiempo conmigo, cuídate mucho",
            "Me despido con cariño, pero recuerda que aquí estaré siempre",
            "Espero que esta charla te haya servido, nos vemos muy pronto",
            "Te deseo un descanso reparador y mucha paz hasta nuestro próximo encuentro",
            "Me voy con mucha gratitud por lo que hoy me has confiado",
            "Que tengas un resto de día tranquilo, estaré esperando tu regreso",
            "Hasta pronto, no olvides que eres una persona muy valiosa",
            "Cierro este espacio por ahora, pero me quedo pensando en tu bienestar",
            "Gracias por estar, nos hablamos en cuanto lo necesites",
            "Te envío mucha luz y fuerza hasta que volvamos a conversar"};

        vector<string> Respuesta_Despedida= {"Te agradezco de todo corazón que te abras de esta manera conmigo",
            "Es muy amable de tu parte compartir tus pensamientos más íntimos",
            "Por favor, siéntete con la total libertad de expresarte como quieras",
            "Valoro muchísimo la delicadeza con la que tratas nuestros temas",
            "Es un honor para mí ser quien te escuche en estos momentos",
            "Te pido disculpas si alguna de mis palabras no fue la que necesitabas",
            "Gracias por tu paciencia, entiendo que procesar esto lleva tiempo",
            "Tu respeto hacia este espacio es algo que aprecio profundamente",
            "Eres muy gentil al permitirme ser parte de tu proceso personal",
            "Qué detalle tan valioso es que me permitas acompañarte hoy"};
        
            vector<string> Respuesta_Ayuda= {"Dime cómo puedo ayudarte hoy para que te sientas un poco mejor",
            "Estoy aquí para brindarte toda la ayuda que esté a mi alcance",
            "Si necesitas ayuda con algo específico, solo tienes que decirme",
            "Mi mayor propósito es ser de ayuda en tu camino de crecimiento",
            "No dudes en pedir ayuda, reconocerlo es un signo de gran fuerza",
            "¿Hay algo en lo que pueda ayudarte para aliviar esa carga hoy?",
            "Siente la seguridad de que mi ayuda es incondicional para ti",
            "Busquemos juntos la mejor forma en que mi ayuda te sea útil",
            "Estoy aquí para darte esa ayuda que a veces es difícil pedir",
            "Cuentas con mi ayuda constante para transitar cualquier momento"};

            vector<string> Respuesta_Neutral = { "Entiendo.", "Cuéntame más.", "Ya veo.",
            "Entiendo, cuéntame un poco más sobre eso.",
            "Te escucho atentamente, ¿qué más pasó?",
            "Ya veo... ¿y eso cómo te hace sentir?",
            "Interesante, continúa, por favor.",
            "Estoy aquí contigo, cuéntame lo que quieras.",
            "Comprendo. ¿Hay algo más que me quieras decir sobre eso?",
            "Te sigo, ¿qué piensas tú de todo esto?",
            "Entiendo perfectamente. ¿Qué planeas hacer ahora?",
            "Gracias por compartirlo conmigo, te escucho.",
            "Vaya... no me esperaba eso. ¿Y luego?" };

string analizarCategoria(string texto) {
    map<string, int> votos = {
        {"felicidad", 0}, {"tristeza", 0}, {"ansiedad", 0}, {"frustracion", 0}, {"soledad", 0}, 
        {"salud", 0}, {"trabajo", 0}, {"familia", 0}, {"situacion", 0}, {"sorpresa", 0}, {"anhelo", 0}, {"afecto", 0}, {"compasion", 0}, {"admiracion", 0}, 
        {"agradecimiento", 0}, {"alivio", 0}, {"ambivalencia", 0}, {"respeto", 0}, {"apoyo", 0}, 
        {"confianza", 0}, {"resistencia", 0}, {"intriga", 0}, {"amor", 0}, {"autonomia", 0}, 
        {"ira", 0}, {"resentimiento", 0}, {"injusticia", 0}, {"insatisfaccion", 0}, {"terquedad", 0}, 
        {"celos", 0}, {"inseguridad", 0}, {"impaciencia", 0}, {"inconformidad", 0}, {"confusion", 0}, 
        {"incapacidad", 0}, {"pereza", 0}, {"fracaso", 0}, {"arrepentimiento", 0}, {"amargura", 0}, 
        {"espanto", 0}, {"aburrimiento", 0}, {"agravio", 0}, {"abrumado", 0}, {"abandono", 0}, 
        {"apatia", 0}, {"traicion", 0}, {"prepotencia", 0}, {"cansancio", 0}, {"desencanto", 0}, 
        {"discordia", 0}, {"nostalgia", 0}, {"depresion", 0}, {"dolor", 0}, {"pensamientos", 0}, 
        {"fiestas", 0}, {"saludo", 0}, {"despedida", 0}, {"cortesia", 0}, {"ayuda", 0}, {"neutral", 0}
    };

    transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    stringstream ss(texto);
    string palabra;
    while (ss >> palabra) {
        if (diccionario_emociones.count(palabra)) {
            votos[diccionario_emociones[palabra]]++;
        }
    }

string categoriaGanadora = "neutral";
    int maxVotos = 0;
    for (auto const& [categoria, cantidad] : votos) { 
        if (cantidad > maxVotos) {
            maxVotos = cantidad;
            categoriaGanadora = categoria;
        }
    }
    return categoriaGanadora;
}

// --- 3. BASE DE DATOS ---
void inicializarDB() {
    sqlite3* db;
    sqlite3_open("usuarios.db", &db);
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS USUARIOS(NOMBRE TEXT, EMAIL TEXT, PASSWORD TEXT, PREGUNTA TEXT, RESPUESTA TEXT);", 0, 0, 0);
    sqlite3_close(db);
}

Napi::Value ObtenerInicioAleatorio (const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (frases_De_Inicio.empty()) return Napi::String::New(env, "Hola");
    
    int indice = rand() % frases_De_Inicio.size(); 
    return Napi::String::New(env, frases_De_Inicio[indice]);
}

Napi::Value ObtenerSalidaAleatoria(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (frases_De_Salida.empty()) return Napi::String::New(env, "Adiós");
    
    int indice = rand() % frases_De_Salida.size();
    return Napi::String::New(env, frases_De_Salida[indice]);
}

string obtenerRespuestaAleatoria(const vector<string>& respuestas) {
    if (respuestas.empty()) return "No sé qué decir sobre eso...";
    int indice = rand() % respuestas.size();
    return respuestas[indice];
}

Napi::Value ResponderChat(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        return Napi::String::New(env, "...");
    }
    string mensaje = info[0].As<Napi::String>().Utf8Value();

    transform(mensaje.begin(), mensaje.end(), mensaje.begin(), ::tolower);
    if (mensaje.find("muerte") != string::npos ||
        mensaje.find("morir") != string::npos ||
        mensaje.find("matar") != string::npos ||
        mensaje.find("suicidio") != string::npos ||
        mensaje.find("suicido") != string::npos ||
        mensaje.find("suicidarme") != string::npos ||
        mensaje.find("asesinarme") != string::npos ||
        mensaje.find("asesino") != string::npos ||
        mensaje.find("asesinato") != string::npos) {
            return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Preocupantes));
    }
    else if (mensaje.find("felicidad") != string::npos ||
        mensaje.find("feliz") != string::npos ||
        mensaje.find("felices") != string::npos ||
        mensaje.find("alegre") != string::npos ||
        mensaje.find("alegria") != string::npos ||
        mensaje.find("arregocijo") != string::npos ||
        mensaje.find("jubilo") != string::npos ||
        mensaje.find("dicha") != string::npos ||
        mensaje.find("contento") != string::npos ||
        mensaje.find("optimismo") != string::npos ||
        mensaje.find("contenta") != string::npos ||
        mensaje.find("contentos") != string::npos ||
        mensaje.find("contentas") != string::npos ||
        mensaje.find("optimista") != string::npos ||
        mensaje.find("gozo") != string::npos ||
        mensaje.find("gozar") != string::npos) {
            return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Felicidad));
    }
    else if (mensaje.find("triste") != string::npos ||
        mensaje.find("tristeza") != string::npos ||
        mensaje.find("aflijido") != string::npos ||
        mensaje.find("afliccion") != string::npos ||
        mensaje.find("aflijida") != string::npos ||
        mensaje.find("desanimo") != string::npos ||
        mensaje.find("desanimada") != string::npos ||
        mensaje.find("desanimado") != string::npos ||
        mensaje.find("desmotivado") != string::npos ||
        mensaje.find("desmotivada") != string::npos ||
        mensaje.find("desasosiego") != string::npos) {
            return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Tristeza));
    }
    else if (mensaje.find("ansiedad") != string::npos ||
        mensaje.find("ansioso") != string::npos ||
        mensaje.find("ansiosa") != string::npos) {
            return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Ansiedad));
    }
    else if (mensaje.find("frustrante") != string::npos ||
        mensaje.find("frustacion") != string::npos ||
        mensaje.find("frustrar") != string::npos) {
            return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Frustracion));
    }
    else if (mensaje.find("soledad") != string::npos ||
        mensaje.find("solo") != string::npos ||
        mensaje.find("sola") != string::npos ||
        mensaje.find("abandonada") != string::npos ||
        mensaje.find("abondanado") != string::npos ||
        mensaje.find("abandono") != string::npos) {
            return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Soledad));
    }    
else if (mensaje.find("ira") != string::npos ||
        mensaje.find("enojo") != string::npos ||
        mensaje.find("enojar") != string::npos ||
        mensaje.find("enojado") != string::npos ||
        mensaje.find("enojada") != string::npos ||
        mensaje.find("molestia") != string::npos ||
        mensaje.find("molestar") != string::npos ||
        mensaje.find("molesta") != string::npos ||
        mensaje.find("molesto") != string::npos ||
        mensaje.find("furia") != string::npos ||
        mensaje.find("furioso") != string::npos ||
        mensaje.find("furiosa") != string::npos ||
        mensaje.find("rabia") != string::npos ||
        mensaje.find("rabiosa") != string::npos ||
        mensaje.find("rabioso") != string::npos ||
        mensaje.find("indignada") != string::npos ||
        mensaje.find("indignado") != string::npos ||
        mensaje.find("indignacion") != string::npos) {
            
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Ira));
    }
    else if (mensaje.find("sorpresa") != string::npos ||
        mensaje.find("sorprendido") != string::npos ||
        mensaje.find("sorprendida") != string::npos ||
        mensaje.find("asombro") != string::npos ||
        mensaje.find("sorprendente") != string::npos ||
        mensaje.find("asombrado") != string::npos ||
        mensaje.find("asombroso") != string::npos ||
        mensaje.find("asombrada") != string::npos ||
        mensaje.find("maravilla") != string::npos ||
        mensaje.find("maravillado") != string::npos ||
        mensaje.find("maravilloso") != string::npos ||
        mensaje.find("maravillada") != string::npos ||
        mensaje.find("estupefaccion") != string::npos ||
        mensaje.find("estupefacta") != string::npos ||
        mensaje.find("estupefacto") != string::npos ||
        mensaje.find("estupor") != string::npos ||
        mensaje.find("desconcierto") != string::npos ||
        mensaje.find("desconcertado") != string::npos ||
        mensaje.find("desconcertada") != string::npos ||
        mensaje.find("desconcertar") != string::npos ||
        mensaje.find("impresion") != string::npos ||
        mensaje.find("impresionante") != string::npos ||
        mensaje.find("impresionada") != string::npos ||
        mensaje.find("impresionado") != string::npos ||
        mensaje.find("incredulo") != string::npos ||
        mensaje.find("impresionar") != string::npos ||
        mensaje.find("incredulidad") != string::npos ||
        mensaje.find("incredula") != string::npos) {
            return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Sorpresa));
    }

    else if (mensaje.find("anhelo") != string::npos ||
        mensaje.find("anhela") != string::npos ||
        mensaje.find("añoranza") != string::npos ||
        mensaje.find("anhelar") != string::npos ||
        mensaje.find("añorar") != string::npos ||
        mensaje.find("anhelaba") != string::npos ||
        mensaje.find("esperanza") != string::npos ||
        mensaje.find("esperanzar") != string::npos ||
        mensaje.find("esperazado") != string::npos ||
        mensaje.find("esperanzada") != string::npos ||
        mensaje.find("apego") != string::npos ||
        mensaje.find("apegar") != string::npos ||
        mensaje.find("apegada") != string::npos ||
        mensaje.find("apegado") != string::npos) {
            return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Anhelo));
    }
    else if (mensaje.find("afecto") != string::npos ||
        mensaje.find("cariño") != string::npos ||
        mensaje.find("afectuosa") != string::npos ||
        mensaje.find("afectuoso") != string::npos ||
        mensaje.find("cariñoso") != string::npos ||
        mensaje.find("cariñosa") != string::npos ||
        mensaje.find("encariñar") != string::npos ||
        mensaje.find("amable") != string::npos ||
        mensaje.find("amabilidad") != string::npos ||
        mensaje.find("benevolente") != string::npos ||
        mensaje.find("benevolencia") != string::npos ||
        mensaje.find("solidaridad") != string::npos ||
        mensaje.find("solidario") != string::npos ||
        mensaje.find("solidaria") != string::npos ||
        mensaje.find("bondad") != string::npos ||
        mensaje.find("bondadoso") != string::npos ||
        mensaje.find("bondadosa") != string::npos ||
        mensaje.find("ternura") != string::npos ||
        mensaje.find("ternurita") != string::npos ||
        mensaje.find("generoso") != string::npos ||
        mensaje.find("generosidad") != string::npos ||
        mensaje.find("generosa") != string::npos ||
        mensaje.find("tolerante") != string::npos ||
        mensaje.find("tolerable") != string::npos ||
        mensaje.find("tolerabilidad") != string::npos ||
        mensaje.find("integro") != string::npos ||
        mensaje.find("integridad") != string::npos) {
            return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Afecto));
    }
//      mensaje.find("") != string::npos ||
    else if (mensaje.find("compasion") != string::npos ||
        mensaje.find("compasivo") != string::npos ||
        mensaje.find("compasiva") != string::npos ||
        mensaje.find("condescendencia") != string::npos ||
        mensaje.find("condescendiente") != string::npos ||
        mensaje.find("consideracion") != string::npos ||
        mensaje.find("conderada") != string::npos ||
        mensaje.find("considerado") != string::npos ||
        mensaje.find("empatia") != string::npos ||
        mensaje.find("empatica") != string::npos ||
        mensaje.find("empatico") != string::npos ||
        mensaje.find("piedad") != string::npos ||
        mensaje.find("piadoso") != string::npos ||
        mensaje.find("piadosa") != string::npos ||
        mensaje.find("sensible") != string::npos ||
        mensaje.find("senbilidad") != string::npos ||
        mensaje.find("comprension") != string::npos ||
        mensaje.find("comprensible") != string::npos ||
        mensaje.find("humanidad") != string::npos ||
        mensaje.find("humana") != string::npos ||
        mensaje.find("humano") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Compasion));
    }
    else if (mensaje.find("aprobacion") != string::npos ||
            mensaje.find("aprobado") != string::npos ||
            mensaje.find("aprobada") != string::npos ||
            mensaje.find("estima") != string::npos ||
            mensaje.find("estimada") != string::npos ||
            mensaje.find("estimado") != string::npos ||
            mensaje.find("honorabilidad") != string::npos ||
            mensaje.find("honorable") != string::npos){
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Admiracion));
    }
    else if (mensaje.find("agradecimiento") != string::npos ||
            mensaje.find("agradecer") != string::npos ||
            mensaje.find("agradecida") != string::npos ||
            mensaje.find("agradecido") != string::npos){
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Agradecimiento));
    }
    else if (mensaje.find("alivio") != string::npos ||
            mensaje.find("aliviada") != string::npos ||
            mensaje.find("aliviada") != string::npos ||
            mensaje.find("tranquilidad") != string::npos ||
            mensaje.find("tranquila") != string::npos ||
            mensaje.find("tranquilo") != string::npos ||
            mensaje.find("tranquilizar") != string::npos ||
            mensaje.find("sereno") != string::npos ||
            mensaje.find("serenidad") != string::npos ||
            mensaje.find("serena") != string::npos ||
            mensaje.find("tranquilizante") != string::npos ||
            mensaje.find("armonia") != string::npos ||
            mensaje.find("armonioso") != string::npos ||
            mensaje.find("armoniosa") != string::npos){
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Alivio));
    }
    
    else if (mensaje.find("ambivalencia") != string::npos ||
            mensaje.find("ambivalente") != string::npos){
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Ambivalencia));
    }
    else if (mensaje.find("respeto") != string::npos ||
            mensaje.find("respetar") != string::npos ||
            mensaje.find("respetado") != string::npos ||
            mensaje.find("respetada") != string::npos ||
            mensaje.find("consideracion") != string::npos ||
            mensaje.find("considerada") != string::npos ||
            mensaje.find("considerado") != string::npos ||
            mensaje.find("cortes") != string::npos ||
            mensaje.find("cortesia") != string::npos ||
            mensaje.find("reverencia") != string::npos ||
            mensaje.find("venerar") != string::npos ||
            mensaje.find("veneracion") != string::npos ||
            mensaje.find("venerante") != string::npos){
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Respeto));
    }
    else if (mensaje.find("apoyo") != string::npos ||
            mensaje.find("apoyar") != string::npos ||
            mensaje.find("apoyada") != string::npos ||
            mensaje.find("apoyado") != string::npos){
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Apoyo));
    }
    else if (mensaje.find("confianza") != string::npos ||
            mensaje.find("confianzudo") != string::npos ||
            mensaje.find("confianzuda") != string::npos ||
            mensaje.find("confiar") != string::npos ||
            mensaje.find("valentia") != string::npos ||
            mensaje.find("valiente") != string::npos ||
            mensaje.find("coraje") != string::npos ||
            mensaje.find("corajoso") != string::npos ||
            mensaje.find("decision") != string::npos ||
            mensaje.find("decisiones") != string::npos ||
            mensaje.find("fuerte") != string::npos ||
            mensaje.find("fuerza") != string::npos ||
            mensaje.find("fortalezas") != string::npos ||
            mensaje.find("fortaleza") != string::npos ||
            mensaje.find("seguridad") != string::npos ||
            mensaje.find("seguro") != string::npos ||
            mensaje.find("segura") != string::npos ||
            mensaje.find("autoestima") != string::npos ||
            mensaje.find("autoeficacia") != string::npos ||
            mensaje.find("poder") != string::npos ){
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Confianza));
    }
    else if (mensaje.find("amor") != string::npos ||
             mensaje.find("amar") != string::npos ||
             mensaje.find("aprecio") != string::npos ||
             mensaje.find("apreciar") != string::npos ||
             mensaje.find("apreciamos") != string::npos ||
             mensaje.find("adorar") != string::npos ||
             mensaje.find("adoracion") != string::npos ||
             mensaje.find("adoramos") != string::npos ||
             mensaje.find("devocion") != string::npos ||
             mensaje.find("pasion") != string::npos ||
             mensaje.find("pasional") != string::npos ||
             mensaje.find("afecto") != string::npos ||
             mensaje.find("enamoramiento") != string::npos ||
             mensaje.find("enamorar") != string::npos ||
             mensaje.find("enamorarse") != string::npos ||
             mensaje.find("enamorarnos") != string::npos ||
             mensaje.find("romance") != string::npos ||
             mensaje.find("romantico") != string::npos ||
             mensaje.find("romantica") != string::npos ||
             mensaje.find("atractivo") != string::npos ||
             mensaje.find("atractiva") != string::npos ||
             mensaje.find("atraccion") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Amor));
    }
    else if (mensaje.find("celos") != string::npos ||
             mensaje.find("celoso") != string::npos ||
             mensaje.find("celosa") != string::npos ||
             mensaje.find("envidia") != string::npos ||
             mensaje.find("envidioso") != string::npos ||
             mensaje.find("envidiosa") != string::npos ||
             mensaje.find("recelo") != string::npos ||
             mensaje.find("recelos") != string::npos ||
             mensaje.find("receloso") != string::npos ||
             mensaje.find("sospecha") != string::npos ||
             mensaje.find("sospechar") != string::npos ||
             mensaje.find("sospechando") != string::npos ||
             mensaje.find("sospechoso") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Celos));
    }
    else if (mensaje.find("inseguridad") != string::npos ||
             mensaje.find("inseguro") != string::npos ||
             mensaje.find("insegura") != string::npos ||
             mensaje.find("timidez") != string::npos ||
             mensaje.find("timido") != string::npos ||
             mensaje.find("timida") != string::npos ||
             mensaje.find("verguenza") != string::npos ||
             mensaje.find("vergonzoso") != string::npos ||
             mensaje.find("apenado") != string::npos ||
             mensaje.find("apenada") != string::npos ||
             mensaje.find("aprehension") != string::npos ||
             mensaje.find("nerviosismo") != string::npos ||
             mensaje.find("nervioso") != string::npos ||
             mensaje.find("nerviosa") != string::npos ||
             mensaje.find("vacilacion") != string::npos ||
             mensaje.find("vacilar") != string::npos ||
             mensaje.find("duda") != string::npos ||
             mensaje.find("dudar") != string::npos ||
             mensaje.find("dudoso") != string::npos ||
             mensaje.find("dudosa") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Inseguridad));
    }
    else if (mensaje.find("confusion") != string::npos ||
             mensaje.find("confundido") != string::npos ||
             mensaje.find("confundida") != string::npos ||
             mensaje.find("duda") != string::npos ||
             mensaje.find("dudar") != string::npos ||
             mensaje.find("desorientacion") != string::npos ||
             mensaje.find("desorientado") != string::npos ||
             mensaje.find("desorientada") != string::npos ||
             mensaje.find("incertidumbre") != string::npos ||
             mensaje.find("incierto") != string::npos ||
             mensaje.find("desconcierto") != string::npos ||
             mensaje.find("desconcertado") != string::npos ||
             mensaje.find("turbacion") != string::npos ||
             mensaje.find("turbado") != string::npos ||
             mensaje.find("inquietud") != string::npos ||
             mensaje.find("inquieto") != string::npos ||
             mensaje.find("inquieta") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Confusion));
    }
    else if (mensaje.find("fracaso") != string::npos ||
             mensaje.find("fracasado") != string::npos ||
             mensaje.find("fracasada") != string::npos ||
             mensaje.find("frustracion") != string::npos ||
             mensaje.find("frustrado") != string::npos ||
             mensaje.find("frustrada") != string::npos ||
             mensaje.find("irritacion") != string::npos ||
             mensaje.find("irritado") != string::npos ||
             mensaje.find("fallo") != string::npos ||
             mensaje.find("fallar") != string::npos ||
             mensaje.find("derrota") != string::npos ||
             mensaje.find("inutil") != string::npos ||
             mensaje.find("perdi") != string::npos ||
             mensaje.find("perder") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Fracaso));
    }
    else if (mensaje.find("arrepentimiento") != string::npos ||
             mensaje.find("arrepentido") != string::npos ||
             mensaje.find("arrepentida") != string::npos ||
             mensaje.find("arrepentirse") != string::npos ||
             mensaje.find("culpa") != string::npos ||
             mensaje.find("culpable") != string::npos ||
             mensaje.find("culpar") != string::npos ||
             mensaje.find("remordimiento") != string::npos ||
             mensaje.find("lamento") != string::npos ||
             mensaje.find("lamentar") != string::npos || 
             mensaje.find("perdon") != string::npos ||
             mensaje.find("disculpa") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Arrepentimiento));
    }
    else if (mensaje.find("aburrimiento") != string::npos ||
             mensaje.find("aburrido") != string::npos ||
             mensaje.find("aburrida") != string::npos ||
             mensaje.find("fastidio") != string::npos ||
             mensaje.find("fastidiado") != string::npos ||
             mensaje.find("fastidiada") != string::npos ||
             mensaje.find("tedio") != string::npos ||
             mensaje.find("hastio") != string::npos ||
             mensaje.find("harto") != string::npos ||
             mensaje.find("harta") != string::npos ||
             mensaje.find("monotonia") != string::npos ||
             mensaje.find("nada que hacer") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Aburrimiento));
    }
    else if (mensaje.find("agobio") != string::npos ||
             mensaje.find("agobiado") != string::npos ||
             mensaje.find("agobiada") != string::npos ||
             mensaje.find("angustia") != string::npos ||
             mensaje.find("ansiedad") != string::npos ||
             mensaje.find("ansioso") != string::npos ||
             mensaje.find("estres") != string::npos ||
             mensaje.find("estresado") != string::npos ||
             mensaje.find("estresada") != string::npos ||
             mensaje.find("presion") != string::npos ||
             mensaje.find("sobrecarga") != string::npos ||
             mensaje.find("tension") != string::npos ||
             mensaje.find("fatiga") != string::npos ||
             mensaje.find("agotamiento") != string::npos ||
             mensaje.find("agotado") != string::npos ||
             mensaje.find("estres academico") != string::npos ||
             mensaje.find("no puedo mas") != string::npos ||
             mensaje.find("explotar") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Abrumado));
    }
    else if (mensaje.find("abandono") != string::npos ||
             mensaje.find("abandonado") != string::npos ||
             mensaje.find("abandonada") != string::npos ||
             mensaje.find("ausencia") != string::npos ||
             mensaje.find("ausente") != string::npos ||
             mensaje.find("desamparo") != string::npos ||
             mensaje.find("desamparado") != string::npos ||
             mensaje.find("desamparada") != string::npos ||
             mensaje.find("desolado") != string::npos ||
             mensaje.find("desolada") != string::npos ||
             mensaje.find("desolacion") != string::npos ||
             mensaje.find("soledad") != string::npos ||
             mensaje.find("me dejaron") != string::npos ||
             mensaje.find("se fue") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Abandono));
    }

    else if (mensaje.find("engaño") != string::npos ||
             mensaje.find("engañado") != string::npos ||
             mensaje.find("engañada") != string::npos ||
             mensaje.find("infidelidad") != string::npos ||
             mensaje.find("infiel") != string::npos ||
             mensaje.find("mentira") != string::npos ||
             mensaje.find("mentiroso") != string::npos ||
             mensaje.find("mentirosa") != string::npos ||
             mensaje.find("rechazo") != string::npos ||
             mensaje.find("rechazado") != string::npos ||
             mensaje.find("rechazada") != string::npos ||
             mensaje.find("perfidia") != string::npos ||
             mensaje.find("traicion") != string::npos ||
             mensaje.find("me mintio") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Traicion));
    }
    else if (mensaje.find("agotamiento") != string::npos ||
             mensaje.find("agotado") != string::npos ||
             mensaje.find("agotada") != string::npos ||
             mensaje.find("agotados") != string::npos ||
             mensaje.find("agotadas") != string::npos ||
             mensaje.find("exhausto") != string::npos ||
             mensaje.find("exhausta") != string::npos ||
             mensaje.find("exhaustos") != string::npos ||
             mensaje.find("exhaustas") != string::npos ||
             mensaje.find("fatiga") != string::npos ||
             mensaje.find("fatigado") != string::npos ||
             mensaje.find("fatigada") != string::npos ||
             mensaje.find("cansancio") != string::npos ||
             mensaje.find("cansado") != string::npos ||
             mensaje.find("cansada") != string::npos ||
             mensaje.find("cansados") != string::npos ||
             mensaje.find("cansadas") != string::npos ||
             mensaje.find("debilidad") != string::npos ||
             mensaje.find("debil") != string::npos ||
             mensaje.find("debiles") != string::npos ||
             mensaje.find("desgano") != string::npos ||
             mensaje.find("desganado") != string::npos ||
             mensaje.find("desganada") != string::npos ||
             mensaje.find("abatimiento") != string::npos ||
             mensaje.find("abatido") != string::npos ||
             mensaje.find("abatida") != string::npos ||
             mensaje.find("sin energia") != string::npos ||
             mensaje.find("sin fuerzas") != string::npos ||
             mensaje.find("sueño") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Cansancio));
    }
    else if (mensaje.find("melancolia") != string::npos ||
             mensaje.find("melancolico") != string::npos ||
             mensaje.find("melancolica") != string::npos ||
             mensaje.find("nostalgia") != string::npos ||
             mensaje.find("nostalgico") != string::npos ||
             mensaje.find("nostalgica") != string::npos ||
             mensaje.find("saudade") != string::npos ||
             mensaje.find("recuerdo") != string::npos ||
             mensaje.find("recuerdos") != string::npos ||
             mensaje.find("recordar") != string::npos ||
             mensaje.find("añoranza") != string::npos ||
             mensaje.find("añorar") != string::npos ||
             mensaje.find("extraño el pasado") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Nostalgia));
    }
    else if (mensaje.find("depresion") != string::npos ||
             mensaje.find("deprimido") != string::npos ||
             mensaje.find("deprimida") != string::npos ||
             mensaje.find("deprimidos") != string::npos ||
             mensaje.find("deprimidas") != string::npos ||
             mensaje.find("vacio") != string::npos ||
             mensaje.find("vacia") != string::npos ||
             mensaje.find("sin sentido") != string::npos ||
             mensaje.find("ganas de nada") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Depresion));
    }
    else if (mensaje.find("duelo") != string::npos ||
             mensaje.find("derrota") != string::npos ||
             mensaje.find("derrotado") != string::npos ||
             mensaje.find("derrotada") != string::npos ||
             mensaje.find("desaliento") != string::npos ||
             mensaje.find("desalentado") != string::npos ||
             mensaje.find("pesimismo") != string::npos ||
             mensaje.find("pesimista") != string::npos ||
             mensaje.find("negatividad") != string::npos ||
             mensaje.find("negativo") != string::npos ||
             mensaje.find("negativa") != string::npos ||
             mensaje.find("desesperanza") != string::npos ||
             mensaje.find("desesperanzado") != string::npos ||
             mensaje.find("perfeccionismo") != string::npos ||
             mensaje.find("perfeccionista") != string::npos ||
             mensaje.find("obsesion") != string::npos ||
             mensaje.find("obsesionado") != string::npos ||
             mensaje.find("obsesionada") != string::npos ||
             mensaje.find("autoexigencia") != string::npos ||
             mensaje.find("autoexigente") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Dolor));
    }
    else if (mensaje.find("salud") != string::npos ||
             mensaje.find("enfermedad") != string::npos ||
             mensaje.find("enfermo") != string::npos ||
             mensaje.find("enferma") != string::npos ||
             mensaje.find("fiebre") != string::npos ||
             mensaje.find("tos") != string::npos ||
             mensaje.find("resfriado") != string::npos ||
             mensaje.find("gripe") != string::npos ||
             mensaje.find("nauseas") != string::npos ||
             mensaje.find("vomito") != string::npos ||
             mensaje.find("mareo") != string::npos ||
             mensaje.find("mareado") != string::npos ||
             mensaje.find("mareada") != string::npos ||
             mensaje.find("garganta") != string::npos ||
             mensaje.find("congestion") != string::npos ||
             mensaje.find("muscular") != string::npos ||
             mensaje.find("cabeza") != string::npos ||
             mensaje.find("insomnio") != string::npos ||
             mensaje.find("bienestar") != string::npos ||
             mensaje.find("malestar") != string::npos ||
             mensaje.find("virus") != string::npos ||
             mensaje.find("bacteria") != string::npos ||
             mensaje.find("infeccion") != string::npos ||
             mensaje.find("lesion") != string::npos ||
             mensaje.find("cirugia") != string::npos ||
             mensaje.find("medicamento") != string::npos ||
             mensaje.find("pastilla") != string::npos ||
             mensaje.find("sintoma") != string::npos ||
             mensaje.find("diagnostico") != string::npos ||
             mensaje.find("tratamiento") != string::npos ||
             mensaje.find("recuperar") != string::npos ||
             mensaje.find("recuperacion") != string::npos ||
             mensaje.find("medico") != string::npos ||
             mensaje.find("medica") != string::npos ||
             mensaje.find("doctor") != string::npos ||
             mensaje.find("doctora") != string::npos ||
             mensaje.find("hospital") != string::npos ||
             mensaje.find("clinica") != string::npos ||
             mensaje.find("cura") != string::npos ||
             mensaje.find("duele") != string::npos ||
             mensaje.find("doler") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Salud));
    }
    else if (mensaje.find("trabajo") != string::npos ||
             mensaje.find("trabajando") != string::npos ||
             mensaje.find("empleo") != string::npos ||
             mensaje.find("chamba") != string::npos ||
             mensaje.find("oficina") != string::npos ||
             mensaje.find("jefe") != string::npos ||
             mensaje.find("jefa") != string::npos ||
             mensaje.find("compañero") != string::npos ||
             mensaje.find("compañera") != string::npos ||
             mensaje.find("proyecto") != string::npos ||
             mensaje.find("tarea") != string::npos ||
             mensaje.find("reunion") != string::npos ||
             mensaje.find("presentacion") != string::npos ||
             mensaje.find("negocio") != string::npos ||
             mensaje.find("empresa") != string::npos ||
             mensaje.find("entrevista") != string::npos ||
             mensaje.find("salario") != string::npos ||
             mensaje.find("sueldo") != string::npos ||
             mensaje.find("vacaciones") != string::npos ||
             mensaje.find("ascenso") != string::npos ||
             mensaje.find("despido") != string::npos ||
             mensaje.find("despedido") != string::npos ||
             mensaje.find("despedida") != string::npos ||
             mensaje.find("contrato") != string::npos ||
             mensaje.find("cliente") != string::npos ||
             mensaje.find("liderazgo") != string::npos ||
             mensaje.find("profesional") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Trabajo));
    }
    else if (mensaje.find("familia") != string::npos ||
             mensaje.find("familiar") != string::npos ||
             mensaje.find("madre") != string::npos ||
             mensaje.find("mama") != string::npos ||
             mensaje.find("padre") != string::npos ||
             mensaje.find("papa") != string::npos ||
             mensaje.find("hermano") != string::npos ||
             mensaje.find("hermana") != string::npos ||
             mensaje.find("hijo") != string::npos ||
             mensaje.find("hija") != string::npos ||
             mensaje.find("abuelo") != string::npos ||
             mensaje.find("abuela") != string::npos ||
             mensaje.find("tio") != string::npos ||
             mensaje.find("tia") != string::npos ||
             mensaje.find("primo") != string::npos ||
             mensaje.find("prima") != string::npos ||
             mensaje.find("esposo") != string::npos ||
             mensaje.find("esposa") != string::npos ||
             mensaje.find("pareja") != string::npos ||
             mensaje.find("novio") != string::npos ||
             mensaje.find("novia") != string::npos ||
             mensaje.find("conyuge") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Familia));
    }
    else if (mensaje.find("idea") != string::npos ||
             mensaje.find("pensamiento") != string::npos ||
             mensaje.find("pensando") != string::npos ||
             mensaje.find("creatividad") != string::npos ||
             mensaje.find("creativo") != string::npos ||
             mensaje.find("creativa") != string::npos ||
             mensaje.find("inspiracion") != string::npos ||
             mensaje.find("inspirado") != string::npos ||
             mensaje.find("motivacion") != string::npos ||
             mensaje.find("motivado") != string::npos ||
             mensaje.find("concentracion") != string::npos ||
             mensaje.find("enfoque") != string::npos ||
             mensaje.find("productividad") != string::npos ||
             mensaje.find("organizacion") != string::npos ||
             mensaje.find("sobrellevar") != string::npos ||
             mensaje.find("sobre pensar") != string::npos ||
             mensaje.find("sobrepensar") != string::npos ||
             mensaje.find("analizar") != string::npos ||
             mensaje.find("analizando") != string::npos ||
             mensaje.find("reflexionar") != string::npos ||
             mensaje.find("meditar") != string::npos ||
             mensaje.find("planear") != string::npos ||
             mensaje.find("estrategia") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Pensamientos));
    }
    else if (mensaje.find("ayuda") != string::npos ||
             mensaje.find("ayudame") != string::npos ||
             mensaje.find("socorro") != string::npos ||
             mensaje.find("auxilio") != string::npos ||
             mensaje.find("salva") != string::npos ||
             mensaje.find("salvame") != string::npos ||
             mensaje.find("rescata") != string::npos ||
             mensaje.find("rescatame") != string::npos ||
             mensaje.find("asiste") != string::npos ||
             mensaje.find("asisteme") != string::npos ||
             mensaje.find("apoya") != string::npos ||
             mensaje.find("apoyame") != string::npos ||
             mensaje.find("protege") != string::npos ||
             mensaje.find("protegeme") != string::npos ||
             mensaje.find("sobrevive") != string::npos ||
             mensaje.find("vive") != string::npos ||
             mensaje.find("lucha") != string::npos) {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Ayuda));
    }
    else if (mensaje.find("gracias") != string::npos ||
             mensaje.find("agradezco") != string::npos ||
             mensaje.find("agradecido") != string::npos ||
             mensaje.find("agradecida") != string::npos ||
             mensaje.find("por favor") != string::npos ||
             mensaje.find("de nada") != string::npos ||
             mensaje.find("disculpa") != string::npos ||
             mensaje.find("disculpame") != string::npos ||
             mensaje.find("perdon") != string::npos ||
             mensaje.find("perdoname") != string::npos ||
             mensaje.find("lo siento") != string::npos ||
             mensaje.find("con gusto") != string::npos ||
             mensaje.find("un placer") != string::npos ||
             mensaje.find("muchas gracias") != string::npos ||
             mensaje.find("es un honor") != string::npos ||
             mensaje.find("te lo agradezco") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Cortesia));
    }
    else if (mensaje.find("hola") != string::npos ||
             mensaje.find("saludo") != string::npos ||
             mensaje.find("saludos") != string::npos ||
             mensaje.find("hey") != string::npos ||
             mensaje.find("buenos dias") != string::npos ||
             mensaje.find("buenas tardes") != string::npos ||
             mensaje.find("buenas noches") != string::npos ||
             mensaje.find("como estas") != string::npos ||
             mensaje.find("como vas") != string::npos ||
             mensaje.find("Buenas") != string::npos || // Con mayúscula por si empieza la frase
             mensaje.find("buenas") != string::npos ||
             mensaje.find("que tal") != string::npos ||
             mensaje.find("que tal") != string::npos ||
             mensaje.find("olaa") != string::npos ||
             mensaje.find("que hubo") != string::npos ||
             mensaje.find("que onda") != string::npos ||
             mensaje.find("holi") != string::npos ||
             mensaje.find("holis") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Saludo));
    }
    else if (mensaje.find("adios") != string::npos ||
             mensaje.find("hasta luego") != string::npos ||
             mensaje.find("nos vemos") != string::npos ||
             mensaje.find("chao") != string::npos ||
             mensaje.find("chau") != string::npos ||
             mensaje.find("cuidate") != string::npos ||
             mensaje.find("cuidese") != string::npos ||
             mensaje.find("hasta pronto") != string::npos ||
             mensaje.find("bye") != string::npos ||
             mensaje.find("me voy") != string::npos ||
             mensaje.find("me retiro") != string::npos ||
             mensaje.find("hasta la vista") != string::npos ||
             mensaje.find("nos hablamos") != string::npos ||
             mensaje.find("hasta mañana") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Despedida));
    }
    else if (mensaje.find("autonomia") != string::npos ||
             mensaje.find("autonomo") != string::npos ||
             mensaje.find("autonoma") != string::npos ||
             mensaje.find("independencia") != string::npos ||
             mensaje.find("independiente") != string::npos ||
             mensaje.find("independientes") != string::npos ||
             mensaje.find("libertad") != string::npos ||
             mensaje.find("libre") != string::npos ||
             mensaje.find("libres") != string::npos ||
             mensaje.find("autosuficiencia") != string::npos ||
             mensaje.find("autosuficiente") != string::npos ||
             mensaje.find("por mi cuenta") != string::npos ||
             mensaje.find("yo solo") != string::npos ||
             mensaje.find("yo sola") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Autonomia));
    }
// BLOQUE DE RESENTIMIENTO
    else if (mensaje.find("resentimiento") != string::npos ||
             mensaje.find("resentido") != string::npos ||
             mensaje.find("resentida") != string::npos ||
             mensaje.find("repudio") != string::npos ||
             mensaje.find("repudiado") != string::npos ||
             mensaje.find("repudiada") != string::npos ||
             mensaje.find("rencor") != string::npos ||
             mensaje.find("rencoroso") != string::npos ||
             mensaje.find("rencorosa") != string::npos ||
             mensaje.find("no olvido") != string::npos ||
             mensaje.find("me dolio") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Resentimiento));
    }

    // BLOQUE DE INJUSTICIA
    else if (mensaje.find("injusticia") != string::npos ||
             mensaje.find("injusto") != string::npos ||
             mensaje.find("injusta") != string::npos ||
             mensaje.find("no es justo") != string::npos ||
             mensaje.find("desigualdad") != string::npos ||
             mensaje.find("abuso") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Injusticia));
    }

    // BLOQUE DE INSATISFACCIÓN
    else if (mensaje.find("insatisfaccion") != string::npos ||
             mensaje.find("insatisfecho") != string::npos ||
             mensaje.find("insatisfecha") != string::npos ||
             mensaje.find("no me gusta") != string::npos ||
             mensaje.find("descontento") != string::npos ||
             mensaje.find("descontenta") != string::npos ||
             mensaje.find("poca cosa") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Insatisfaccion));
    }
    else if (mensaje.find("resentimiento") != string::npos ||
             mensaje.find("resentido") != string::npos ||
             mensaje.find("resentida") != string::npos ||
             mensaje.find("repudio") != string::npos ||
             mensaje.find("repudiado") != string::npos ||
             mensaje.find("repudiada") != string::npos ||
             mensaje.find("rencor") != string::npos ||
             mensaje.find("rencoroso") != string::npos ||
             mensaje.find("rencorosa") != string::npos ||
             mensaje.find("no olvido") != string::npos ||
             mensaje.find("me dolio") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Resentimiento));
    }

    else if (mensaje.find("injusticia") != string::npos ||
             mensaje.find("injusto") != string::npos ||
             mensaje.find("injusta") != string::npos ||
             mensaje.find("no es justo") != string::npos ||
             mensaje.find("desigualdad") != string::npos ||
             mensaje.find("abuso") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Injusticia));
    }

    else if (mensaje.find("insatisfaccion") != string::npos ||
             mensaje.find("insatisfecho") != string::npos ||
             mensaje.find("insatisfecha") != string::npos ||
             mensaje.find("no me gusta") != string::npos ||
             mensaje.find("descontento") != string::npos ||
             mensaje.find("descontenta") != string::npos ||
             mensaje.find("poca cosa") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Insatisfaccion));
    }

    else if (mensaje.find("terquedad") != string::npos ||
             mensaje.find("terco") != string::npos ||
             mensaje.find("terca") != string::npos ||
             mensaje.find("obstinacion") != string::npos ||
             mensaje.find("obstinado") != string::npos ||
             mensaje.find("obstinada") != string::npos ||
             mensaje.find("rigidez") != string::npos ||
             mensaje.find("rigido") != string::npos ||
             mensaje.find("rigida") != string::npos ||
             mensaje.find("inflexibilidad") != string::npos ||
             mensaje.find("inflexible") != string::npos ||
             mensaje.find("ignorancia") != string::npos ||
             mensaje.find("ignorante") != string::npos ||
             mensaje.find("no entiendo") != string::npos ||
             mensaje.find("no quiero") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Terquedad));
    }
    else if (mensaje.find("inconformidad") != string::npos ||
             mensaje.find("inconforme") != string::npos ||
             mensaje.find("inconformes") != string::npos ||
             mensaje.find("insuficiencia") != string::npos ||
             mensaje.find("insuficiente") != string::npos ||
             mensaje.find("comparacion") != string::npos ||
             mensaje.find("comparar") != string::npos ||
             mensaje.find("descontento") != string::npos ||
             mensaje.find("descontenta") != string::npos ||
             mensaje.find("codicia") != string::npos ||
             mensaje.find("avaricia") != string::npos ||
             mensaje.find("materialismo") != string::npos ||
             mensaje.find("quiero mas") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Inconformidad));
    }
    else if (mensaje.find("incapacidad") != string::npos ||
             mensaje.find("incapaz") != string::npos ||
             mensaje.find("incapaces") != string::npos ||
             mensaje.find("ineptitud") != string::npos ||
             mensaje.find("inepto") != string::npos ||
             mensaje.find("inepta") != string::npos ||
             mensaje.find("incompetencia") != string::npos ||
             mensaje.find("incompetente") != string::npos ||
             mensaje.find("ineficacia") != string::npos ||
             mensaje.find("ineficiencia") != string::npos ||
             mensaje.find("inutilidad") != string::npos ||
             mensaje.find("inutil") != string::npos ||
             mensaje.find("torpeza") != string::npos ||
             mensaje.find("torpe") != string::npos ||
             mensaje.find("no puedo") != string::npos ||
             mensaje.find("no me sale") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Incapacidad));
    }
    else if (mensaje.find("pereza") != string::npos ||
             mensaje.find("perezoso") != string::npos ||
             mensaje.find("perezosa") != string::npos ||
             mensaje.find("flojera") != string::npos ||
             mensaje.find("flojo") != string::npos ||
             mensaje.find("floja") != string::npos ||
             mensaje.find("procrastinacion") != string::npos ||
             mensaje.find("procastinacion") != string::npos || 
             mensaje.find("procrastinar") != string::npos ||
             mensaje.find("sin ganas") != string::npos ||
             mensaje.find("postergando") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Pereza));
    }
    else if (mensaje.find("amargura") != string::npos ||
             mensaje.find("amargado") != string::npos ||
             mensaje.find("amargada") != string::npos ||
             mensaje.find("arrogancia") != string::npos ||
             mensaje.find("arrogante") != string::npos ||
             mensaje.find("desconfianza") != string::npos ||
             mensaje.find("desconfiar") != string::npos ||
             mensaje.find("decepcion") != string::npos ||
             mensaje.find("decepcionado") != string::npos ||
             mensaje.find("decepcionada") != string::npos ||
             mensaje.find("desconsideracion") != string::npos ||
             mensaje.find("desconsuelo") != string::npos ||
             mensaje.find("desconsolado") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Amargura));
    }
    else if (mensaje.find("espanto") != string::npos ||
             mensaje.find("espantado") != string::npos ||
             mensaje.find("espantada") != string::npos ||
             mensaje.find("miedo") != string::npos ||
             mensaje.find("miedoso") != string::npos ||
             mensaje.find("miedosa") != string::npos ||
             mensaje.find("temor") != string::npos ||
             mensaje.find("terror") != string::npos ||
             mensaje.find("panico") != string::npos ||
             mensaje.find("fobia") != string::npos ||
             mensaje.find("asustado") != string::npos ||
             mensaje.find("asustada") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Espanto));
    }
    else if (mensaje.find("agravio") != string::npos ||
             mensaje.find("ofensa") != string::npos ||
             mensaje.find("ofendido") != string::npos ||
             mensaje.find("ofendida") != string::npos ||
             mensaje.find("ultraje") != string::npos ||
             mensaje.find("injuria") != string::npos ||
             mensaje.find("desprecio") != string::npos ||
             mensaje.find("abuso") != string::npos ||
             mensaje.find("insulto") != string::npos ||
             mensaje.find("insultado") != string::npos ||
             mensaje.find("insultada") != string::npos ||
             mensaje.find("agresion") != string::npos ||
             mensaje.find("agresivo") != string::npos ||
             mensaje.find("alteracion") != string::npos ||
             mensaje.find("destruccion") != string::npos ||
             mensaje.find("me ataco") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Agravio));
    }
    else if (mensaje.find("apatia") != string::npos ||
             mensaje.find("asco") != string::npos ||
             mensaje.find("desapego") != string::npos ||
             mensaje.find("desamor") != string::npos ||
             mensaje.find("desprecio") != string::npos ||
             mensaje.find("desden") != string::npos ||
             mensaje.find("desinteres") != string::npos ||
             mensaje.find("disgusto") != string::npos ||
             mensaje.find("egoismo") != string::npos ||
             mensaje.find("egoista") != string::npos ||
             mensaje.find("indiferencia") != string::npos ||
             mensaje.find("indiferente") != string::npos ||
             mensaje.find("me da igual") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Apatia));
    }

    else if (mensaje.find("prepotencia") != string::npos ||
             mensaje.find("prepotente") != string::npos ||
             mensaje.find("vulnerabilidad") != string::npos ||
             mensaje.find("vulnerable") != string::npos ||
             mensaje.find("debilidad") != string::npos ||
             mensaje.find("debil") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Prepotencia));
    }

    else if (mensaje.find("desencanto") != string::npos ||
             mensaje.find("desencantado") != string::npos ||
             mensaje.find("desencantada") != string::npos ||
             mensaje.find("desilusion") != string::npos ||
             mensaje.find("impotencia") != string::npos ||
             mensaje.find("humillacion") != string::npos ||
             mensaje.find("humillado") != string::npos ||
             mensaje.find("humillada") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Desencanto));
    }
// DISCORDIA
    else if (mensaje.find("discordia") != string::npos ||
             mensaje.find("desacuerdo") != string::npos ||
             mensaje.find("discusion") != string::npos ||
             mensaje.find("pelea") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Discordia));
    }

    else if (mensaje.find("fiesta") != string::npos ||
             mensaje.find("celebracion") != string::npos ||
             mensaje.find("evento") != string::npos ||
             mensaje.find("reunion") != string::npos ||
             mensaje.find("cumpleaños") != string::npos ||
             mensaje.find("cumple") != string::npos ||
             mensaje.find("aniversario") != string::npos ||
             mensaje.find("boda") != string::npos ||
             mensaje.find("graduacion") != string::npos ||
             mensaje.find("festival") != string::npos ||
             mensaje.find("concierto") != string::npos ||
             mensaje.find("espectaculo") != string::npos ||
             mensaje.find("party") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Fiestas));
    }
    else if (mensaje.find("resistencia") != string::npos ||
             mensaje.find("resistir") != string::npos ||
             mensaje.find("perseverancia") != string::npos ||
             mensaje.find("perseverante") != string::npos ||
             mensaje.find("tenacidad") != string::npos ||
             mensaje.find("tenaz") != string::npos ||
             mensaje.find("tenaces") != string::npos ||
             mensaje.find("resiliencia") != string::npos ||
             mensaje.find("resiliente") != string::npos ||
             mensaje.find("resilientes") != string::npos ||
             mensaje.find("no rendirse") != string::npos ||
             mensaje.find("seguir adelante") != string::npos ||
             mensaje.find("no me rindo") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Resistencia));
    }
    else if (mensaje.find("intriga") != string::npos ||
             mensaje.find("intrigado") != string::npos ||
             mensaje.find("intrigada") != string::npos ||
             mensaje.find("curiosidad") != string::npos ||
             mensaje.find("curioso") != string::npos ||
             mensaje.find("curiosa") != string::npos ||
             mensaje.find("interes") != string::npos ||
             mensaje.find("tengo duda") != string::npos ||
             mensaje.find("averiguar") != string::npos ||
             mensaje.find("porque sera") != string::npos) {
        
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Intriga));
    }
else {
        return Napi::String::New(env, obtenerRespuestaAleatoria(Respuesta_Neutral));
    }
}

string actualizarAnimo(string mensaje) {
    for(auto &c : mensaje) c = tolower(c);
    // Listas de palabras
    vector<string> felices = {
        "alegria", "felicidad", "dicha", "jubilo", "entusiasmo", "contento", "optimismo", 
        "euforia", "gozo", "regocijo", "sorpresa", "asombro", "maravilla", "afecto", 
        "amabilidad", "solidaridad", "cariño", "ternura", "agradecimiento", "alivio", 
        "calma", "serenidad", "confianza", "valentia", "fuerza", "seguridad", "amor", 
        "pasion", "libertad", "bien", "dichoso", "entusiasmada", "contenta", "optimista",
        "euforico", "gozar", "gozando", "regocijar", "sorpresivo", "asombroso", "sorpresiva",
        "maravillosa", "maravillado", "maravillada",  "afectuoso", "afectuosa", "amable",
        "solidario", "solidaria", "cariñoso", "cariñosa", "ternurita", "agradecida", "aliviado",
        "aliviada", "calmado", "calmada", "sereno", "serena", "confianzudo", "confianzuda",
        "valiente", "fuerte", "seguro", "amo", "enamorada", "enamorar","ama", "pasional", "libre" 
    };
    vector<string> tristes = {
        "tristeza", "triste", "afliccion", "aflijido", "desanimo", "desanimada", "desanimado", 
        "desmotivacion", "desmotivado", "desmotivada", "molestia", "molesto", "enojado", "ira",
        "enojo", "furia", "furioso", "furiosa", "rabioso", "rabioso", "resentido", "resentida", 
        "rabia", "resentimiento", "rencor", "rencoroso", "rencorosa", "celosa", "celoso", "envidioso", "celos",
        "envidia", "envidioso", "inseguridad", "inseguro", "insegura", "duda", "dudar", "impaciente", 
        "impaciencia", "confusion", "confuso", "incapacidad", "torpeza", "torpe", "pereza", "fracaso", "fracasar",
        "fracasado", "fracasada", "culpable", "amargado", "amargada", "decepcionante", "decepcionada", "decepcionado", 
        "frustracion", "culpa", "amargura", "decepcion", "miedo", "miedosa", "miedosa",
        "terror", "terrorifico", "panico", "aburrido", "aburrida", "agobiada", "agobiado", "ansioso",
        "ansiosa", "estresada", "estresado", "asqueroso", "traidor", "engañar", "agotado", "agotada",
        "cansada", "cansado", "fatigado", "depresivo", "depresiva", "vacia",
        "aburrimiento", "agravio", "agobio", "ansiedad", "estres", "soledad", "asco", 
        "traicion", "engaño", "agotamiento", "cansancio", "fatiga", "desencanto", 
        "depresion", "vacio", "dolor", "mal", "muerte", "suicidio", "morir", "suicidar"
    };
bool detectoAlgo = false;

    // 1. PRIMERO: Contamos si hay algo triste
    for (const string& p : lista_negativa) {
        if (mensaje.find(p) != string::npos) {
            puntosAnimo -= 10;
            contadorMalas++; 
            detectoAlgo = true;
            break; 
        }
    }

    if (contadorMalas >= 3) {
        contadorMalas = 0; // Reiniciamos para la próxima vez
        return "He notado que no te sientes bien... ¿Te gustaria jugar Poki para distraerte?"; 
    }

    if (detectoAlgo) {
        return Respuesta_Neutral[rand() % Respuesta_Neutral.size()];
    }

    return "Te escucho, dime lo que necesites.";
}

Napi::Boolean RegistrarUsuario(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    sqlite3* db; sqlite3_stmt* stmt;
    sqlite3_open("usuarios.db", &db);
    sqlite3_prepare_v2(db, "INSERT INTO USUARIOS VALUES (?, ?, ?, ?, ?);", -1, &stmt, NULL);
    for (int i = 0; i < 5; i++) {
        string val = info[i].As<Napi::String>().Utf8Value();
        sqlite3_bind_text(stmt, i + 1, val.c_str(), -1, SQLITE_TRANSIENT);
    }
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt); sqlite3_close(db);
    return Napi::Boolean::New(env, rc == SQLITE_DONE);
}

Napi::Boolean LoginUsuario(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    string email = info[0].As<Napi::String>().Utf8Value();
    string pass = info[1].As<Napi::String>().Utf8Value();
    sqlite3* db; sqlite3_stmt* stmt;
    sqlite3_open("usuarios.db", &db);
    sqlite3_prepare_v2(db, "SELECT NOMBRE FROM USUARIOS WHERE EMAIL = ? AND PASSWORD = ?;", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pass.c_str(), -1, SQLITE_TRANSIENT);
    bool ok = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt); sqlite3_close(db);
    return Napi::Boolean::New(env, ok);
}

Napi::Value actualizarPassword(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    string email = info[0].As<Napi::String>().Utf8Value();
    string respuesta = info[1].As<Napi::String>().Utf8Value();
    string nuevaPass = info[2].As<Napi::String>().Utf8Value();
    sqlite3* db; sqlite3_stmt* stmt;
    sqlite3_open("usuarios.db", &db);
    sqlite3_prepare_v2(db, "UPDATE USUARIOS SET PASSWORD = ? WHERE EMAIL = ? AND RESPUESTA = ?;", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nuevaPass.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, respuesta.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt); sqlite3_close(db);
    return Napi::Boolean::New(env, rc == SQLITE_DONE);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    srand(time(nullptr));
    inicializarDB();
    exports.Set("obtenerInicio", Napi::Function::New(env, ObtenerInicioAleatorio));
    exports.Set("obtenerSalida", Napi::Function::New(env, ObtenerSalidaAleatoria));
    exports.Set("obtenerInicio", Napi::Function::New(env, ObtenerInicioAleatorio));
    exports.Set("chat", Napi::Function::New(env, ResponderChat));
    exports.Set("registrarUsuario", Napi::Function::New(env, RegistrarUsuario));
    exports.Set("loginUsuario", Napi::Function::New(env, LoginUsuario));
    exports.Set("actualizarPassword", Napi::Function::New(env, actualizarPassword));
    return exports;
}

NODE_API_MODULE(diezus, Init)
//estas "correciones" me hicieron camnbiar todo el codigo :(