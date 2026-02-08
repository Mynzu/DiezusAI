const express = require('express');
const path = require('path');
const fs = require('fs');
const app = express();

let diezus;
try {
    diezus = require('./build/Release/Diezus');
    console.log(" Diezus conectado exitosamente");
} catch (err) {
    console.error(" Error cargando el core de C++:", err.message);
    process.exit(1);
}

app.use(express.json());
app.use(express.static(__dirname));

// API Login - Forzamos el éxito para que puedas entrar
app.post('/api/login', (req, res) => {
    console.log("Intento de login recibido");
    res.json({ success: true }); 
});

// API para el Chat con límite de longitud
app.post('/api/chat', (req, res) => {
    const { mensaje } = req.body;
    if (!mensaje) return res.json({ respuesta: "Dime algo, amigo." });

    try {
        let respuesta = diezus.chat(mensaje);
        
        // Si por alguna razón el C++ se emociona y escribe de más, 
        // lo recortamos aquí también para asegurar los ~50-80 caracteres.
        if (respuesta.length > 80) {
            respuesta = respuesta.substring(0, 77) + "...";
        }

        res.json({ respuesta });
    } catch (e) {
        console.error("Error en el core:", e);
        res.json({ respuesta: "Lo siento, tuve un error en mi núcleo." });
    }
});

app.get('/api/inicio', (req, res) => res.json({ frase: "Hola, soy Diezus. ¿Cómo te sientes hoy?" }));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'Frontend.html'));
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Servidor en http://localhost:${PORT}`);
});