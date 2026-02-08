#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map> 
#include <sstream>
#include <algorithm>
using namespace std;

int main(){

    map<string,int> emociones_valores = {
        // Felicidad
        {"alegria", 1000000},
        {"dicha",1000000},
        {"jubilo",1000000},
        {"entusiasmo",1000000},
        {"contento",1000000},
        {"optimismo",1000000},
        {"euforia",1000000},
        {"felicidad",1000000},
        {"gozo",1000000},
        {"regocijo",1000000},

        // Sorpresa
        {"sorpresa",1001010},

        // Impertubalidad
        {"impertubabilidad",1010010},

        // Añoranza
        {"añoranza",1100010},
        {"esperanza",1100010},
        
        
        {"apego",1100110},

        // Afecto
        {"afecto",1101100},
        {"amabilidad",1101100},
        {"benevolencia",1101100},
        {"solidaridad",1101100},
        {"bondad",1101100},
        {"cariño",1101100},
        {"ternura",1101100},
        {"generosidad",1101100},
        {"tolerancia",1101100},
        {"integridad",1101100},

        // compasion
        {"compasion",1011100},
        {"condescendencia",1011100},
        {"consideracion",1011100},
        {"empatia",1011100},
        
        // admiracion
        {"admiracion",1000001},
        {"aprobacion",1000001},
        {"estima",1000001},
        {"honorabilidad",1000001},

        // agradecimiento
        {"agradecimiento",1000011},

        // alivio
        {"alivio",1001001},
        {"tranquilo",1001001},
        {"calma",1001001},
        {"serenidad",1001001},
        {"armonia",1001001},

        // ambivalencia
        {"ambivalencia",1010001},

        // respeto
        {"respeto",1010101},

        // apoyo
        {"apoyo",1011001},

        // confianza
        {"confianza",1011011},
        {"valentia",1011011},
        {"coraje",1011011},
        {"determinacion",1011011},
        {"decision",1011011},
        {"fortaleza",1011011},
        {"fuerza",1011011},
        
        // Resistencia
        {"resistencia",1010111},
        {"perseverancia",1010111},
        {"tenacidad",1010111},
        {"resiliencia",1010111},

        // aca agregue las de la otra noche!

        // Intriga
        {"intriga",1110011},
        {"curiosidad",1110011},

        // amor
        {"amor",1101111},
        {"atraccion",1101111},

        // autonomia
        {"autonomia",1111011},
        {"independencia",1111011},
                
    };

    vector<pair<string, int>> emociones_tristes = {
        {"tristeza",1000010},
        {"afliccion",1000010},
        {"desanimo",1000010},
        {"desmotivacion",1000010},
        {"desasosiego",1000010},

        {"dependencia", 1111100},

        // Ira
        {"ira",1001010},
        {"enojo",1001010},
        {"furia",1001010},
        {"rabia",1001010},
        {"rebeldia",1001010},
        {"indignacion",1001010},

        // Resentimiento
        {"resentimiento",1001110},
        {"repudio",1001110},
        {"rencor",1001110},

        //injusticia
        {"injusticia",1010010},

        // insatisfaccion
        {"insatisfaccion",1010110},

        //terquedad
        {"terquedad",1001011},
        {"obstinacion",1001011},
        {"rigidez",1001011},
        {"inflexibilidad",1001011},
        {"ignorancia",1001011}, // agregue esta

        // celos
        {"celos",1110010},
        {"envidia",1110010},
        {"recelos",1110010},
        {"sospecha",1110010},

        // inseguridad
        {"inseguridad",1011010},

        // impaciencia
        {"impaciencia",1010000},

        //Inconformidad
        {"insuficiencia",1011000},
        {"inconformidad",1011000},
        {"comparacion",1011000},

        // Confusion
        {"confusion",1000110},
        {"duda",1000110},
        {"incertidumbre",1000110},
        {"desconcierto",1000110},
        {"desorientacion",1000110},
        {"turbacion",1000110},
        {"inquietud",1000110}, // agregue esta

        // incapacidad
        {"incapacidad",1100000},
        {"ineptitud",1100000},
        {"incompetencia",1100000},
        {"ineficacia",1100000},
        {"ineficiencia",1100000},
        {"inutilidad",1100000},
        {"torpeza",1100000},

        // peraza
        {"pereza",1100101},
        {"flojera",1100101},
        {"procastinacion",1100101},

        // fracaso
        {"frustracion",1110000},
        {"fracaso",1110000},
        {"irritacion",1110000},

        // Arrepentimiento
        {"arrepentimiento",1100100},
        {"culpa",1100100},
        {"remordimiento",1100100},

        // Amargura
        {"amargura",1101010},
        {"arrogancia",1101010},
        {"desconfianza",1101010},
        {"resentimiento",1101010},
        {"decepcion",1101010},
        {"desconsideracion",1101010},
        {"desconsuelo",1101010},

        // espanto
        {"espanto",1101000},
        {"miedo",1101000},
        {"terror",1101000},
        {"panico",1101000},
        {"fobia",1101000},

        // aburrimiento
        {"aburrimiento",1000101},
        {"fastidio",1000101},
        {"tedio",1000101},
        {"hastio",1000101},

        // agravio
        {"agravio",1001101},
        {"abuso",1001101},
        {"agresion",1001101},
        {"alteracion",1001101},
        {"destruccion",1001101},

        // abrumado
        {"abrumado",1000111},
        {"agobio",1000111},
        {"angustia",1000111},
        {"ansiedad",1000111},
        {"estres",1000111},
        {"presion",1000111},
        {"sobrecarga",1000111},
        {"tension",1000111},
        {"fatiga",1000111},
        {"agotamiento",1000111},
        {"estres academico", 1000111},

        // abandono
        {"abandono",1001111},
        {"ausencia",1001111},
        {"desamparo",1001111},
        {"desolacion",1001111},
        {"soledad",1001111}, //listo

        // apatia
        {"apatia",1010011},
        {"asco",1010011},
        {"desapego",1010011},
        {"desamor",1010011},
        {"desprecio",1010011},
        {"desden",1010011},
        {"desinteres",1010011},
        {"disgusto",1010011},
        {"egoismo",1010011},
        {"indiferencia",1010011},

        // traicion
        {"traicion",1100001},
        {"engaño",1100001},
        {"infidelidad",1100001},
        {"mentira",1100001},
        {"rechazo",1100001},
        {"perfidia",1100001},

        // Prepotencia
        {"prepotencia",1011111},

        {"vurnerabilidad",1111101},
        {"debilidad",1111101},

        // Cansancio
        {"cansancio",1000100},
        {"abatimiento",1000100},
        {"fatiga",1000100},

        // desencanto
        {"desescanto",1100111},
        {"desilusion",1100111},

        {"impotencia",1111001},
        {"humillacion",1111001},

        // discordia
        {"discordia",1110001},
        {"desacuerdo",1110001},

        // nostalgia
        {"nostalgia",1101011},
        {"melancolia",1101011},

        //  depresion
        {"depresion",1101101},
        {"vacio",1101101},

        // dolor
        {"dolor",1101001},
        {"duelo",1101001},
        {"derrota",1101001}, //listo
        {"desaliento",1101001}, // agregue esta

        {"pesimismo",1100011},
        {"negatividad",1100011},
        {"desesperanza",1100011},

        {"perfeccionismo",1111111}, //listo
        {"obsesion",1111111},
        {"autoexigencia",1111111},
    };


    vector<pair<string, int>> emociones_negativas = {
        {"no",0000000},
        {"nunca",0000000},
        {"ningun",0000000},
        {"ninguna",0000000},
        {"jamas",0000000},
        {"nada",0000000},
        {"tampoco",0000000},
        {"nadie",0000000},
        {"sin",0000000},
        {"ni",0000000},
        {"pero",0000000},
        {"aunque",0000000},
        {"excepto",0000000},
        {"ni siquiera",0000000},
    };

    vector<pair<string, int>> palabras = {
        // Saludos
        {"hola",0000001},
        {"saludos",0000001},
        {"hey",0000001},
        {"buenos dias",0000001},
        {"buenas tardes",0000001},
        {"buenas noches",0000001},
        {"como estas",0000001},
        {"Buenas",0000001},
        {"que tal",0000001},
        {"olaa",0000001},
        {"que hubo",0000001},
        {"holi", 00000001}
        // Despedidas
        {"adios",0000011},
        {"hasta luego",0000011},
        {"nos vemos",0000011},
        {"chao",0000011},
        {"cuidate",0000011},
        {"hasta pronto",0000011},
        {"bye",0000011},
        {"me voy",0000011},
        {"hasta la vista",0000011},
        {"nos hablamos",0000011},
        {"hasta mañana",0000011},
        // Cortesias
        {"gracias",0000111},
        {"por favor",0001111},
        {"de nada",0001111},
        {"disculpa",0011111},
        {"perdon",0011111},
        {"muchas gracias",0011111},
        {"lo siento",0011111},
        {"con gusto",0001111},
        {"un placer",0001111},
        {"es un honor",0001111},
        {"te lo agradezco",0001111},
        // Solicitudes de ayuda
        {"ayuda",0011111},
        {"socorro",0011111},
        {"auxilio",001111},
        {"salva",0011111},
        {"rescata",0011111},
        {"asiste",0011111},
        {"apoya",0011111},
        {"salvame",0011111},
        {"rescatame",0011111},
        {"asisteme",0011111},
        {"protege",0011111},
        {"sobrevive",0011111},
        {"vive",0011111},
        {"lucha",0011111},
        //familia
        {"madre",1111111},
        {"padre",1111111},
        {"hermano",1111111},
        {"hermana",1111111},
        {"hijo",1111111},
        {"hija",1111111},
        {"familia",1111111},
        {"familiar",1111111},
        {"abuelo",1111111},
        {"abuela",1111111},
        {"tio",1111111},
        {"tia",1111111},
        {"primo",1111111},
        {"prima",1111111},
        {"esposo",1111111},
        {"esposa",1111111},
        {"pareja",1111111},
        {"novio",1111111},
        {"novia",1111111},
        {"amor",1111111},

        //situaciones
        {"examen",0001000},
        {"clase",0001000},
        {"escuela",0001000},
        {"universidad",0001000},
        {"maestro", 0001000},
        {"profesor", 0001000},
        {"estudiante", 0001000},
        {"curso",0001000},
        {"leccion",0001000},
        {"tarea",0001000},
        {"estudio",0001000},
        {"investigacion", 0001000},  
        {"practica",0001000},
        {"nota",0001000},
        {"calificacion",0001000},
        {"graduacion",0001000},
        {"trabajo en equipo",0001000},
        {"presentacion",0001000},
        {"proyecto",0001000},
        {"exposicion",0001000},
        {"investigacion",0001000},
        {"bibliografia",0001000},
        {"ensayo",0001000},
        {"plazo",0001000},
        {"entrega",0001000},
        {"investigar",0001000},
        {"aprender",0001000},
        {"estudiar",0001000},
        {"repasar",0001000},
        {"memorizar",0001000},
        {"comprender",0001000},
        {"analizar",0001000},
        {"sintetizar",0001000},
        {"evaluar",0001000},
        {"calificar",0001000},
        {"graduarse",0001000},
        {"trabajo",0001000},
        {"problema",0001000},

        //salud
        {"enfermedad",0001001},
        {"dolor",0001001},
        {"fiebre", 0001001},
        {"tos", 0001001},
        {"resfriado", 0001001},
        {"gripe", 0001001},
        {"nauseas", 0001001},
        {"vomito", 0001001},
        {"mareo", 0001001},
        {"dolor de garganta", 0001001},
        {"congestion nasal", 0001001},
        {"dolor muscular", 0001001},
        {"dolor de cabeza", 0001001},
        {"estres", 0001001},
        {"ansiedad", 0001001},
        {"depresion", 0001001},
        {"insomnio", 0001001},
        {"bienestar general", 0001001},
        {"malestar",0001001},
        {"fatiga",0001001},
        {"estres",0001001},
        {"ansiedad",0001001},
        {"depresion",0001001},
        {"insomnio",0001001},
        {"virus",0001001},
        {"bacteria",0001001},
        {"infeccion",0001001},
        {"lesion",0001001},
        {"cirugia",0001001},
        {"medicamento",0001001},
        {"sintoma",0001001},
        {"diagnostico",0001001},
        {"tratamiento",0001001},
        {"recuperarse",0001001},
        {"recuperacion",0001001},
        {"medico",0001001},
        {"hospital",0001001},
        {"cura",0001001},
        {"tratamiento",0001001},
        {"salud",0001001}, 

        // trabajo
        {"empleo", 0001010},
        {"oficina",0001010},
        {"jefe",0001010},
        {"compañero",0001010},
        {"proyecto",0001010},
        {"tarea",0001010},
        {"reunion",0001010},
        {"presentacion",0001010},
        {"negocio",0001010},
        {"empresa",0001010},
        {"entrevista",0001010},
        {"salario",0001010},
        {"beneficio",0001010},
        {"horario",0001010},
        {"vacaciones",0001010},
        {"ascenso",0001010},
        {"despido",0001010},
        {"contrato",0001010},
        {"cliente",0001010},
        {"proveedor",0001010},
        {"producto",0001010},
        {"servicio",0001010},
        {"marketing",0001010},
        {"ventas",0001010},
        {"finanzas",0001010},
        {"contabilidad",0001010},
        {"administracion",0001010},
        {"liderazgo",0001010},
        {"trabajo en equipo",0001010},
        {"colaboracion",0001010},
        {"crecimiento profesional",0001010},
        {"desarrollo profesional",0001010},
        {"equilibrio trabajo-vida",0001010},

        //pensamientos
        {"idea",0000101},
        {"creatividad",0000101},
        {"inspiracion",0000101},
        {"motivacion",0000101},
        {"concentracion",0000101},
        {"enfoque",0000101},
        {"productividad",0000101},
        {"organizacion",0000101},
        {"sobrellevar",0000101},
        {"sobre pensar",0000101},
        {"analizar",0000101},
        {"reflexionar",0000101},
        {"meditar",0000101},
        {"planear",0000101},
        {"estrategia",0000101},

        //fiestas
        {"fiesta",0000100},
        {"celebracion",0000100},
        {"evento",0000100},
        {"reunion",0000100},
        {"cumpleanos", 0000100},
        {"aniversario", 0000100},
        {"boda",0000100},
        {"graduacion",0000100},
        {"festival", 0000100},
        {"concierto",0000100},
        {"espectaculo",0000100},
    };
}    

//0001011, 0001100, 0001101, 0010000, 0010001, 0010010, 0010011, 0010100, 0010101, 0010110, 0010111, 0011000, 0011001, 0011010, 0011011, 0011100, 0011101010xxxx → toda la serie 0100000–0101111 está libre.011xxxx → toda la serie 0110000–0111111 está libre.1110100, 1110101, 1110110, 1110111, 1111000, 1111010, 1111101, 1111110