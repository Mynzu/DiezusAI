// El nombre tiene que ser igual al target_name del binding.gyp
const diezus = require('./build/Release/Ejemplodiezuscompleto');

// Probamos la función que registramos en el C++
console.log("Diezus dice:", diezus.frases_De_Inicio());