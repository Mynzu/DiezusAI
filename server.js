const express = require('express');
const path = require('path');
const { execSync } = require('child_process');
const fs = require('fs');
const app = express();

app.use(express.json());
app.use(express.static(__dirname));

// --- PERSISTENCIA DE USUARIOS ---
const USERS_FILE = './usuarios.json';
let usuarios = {};

// Cargar usuarios al iniciar
if (fs.existsSync(USERS_FILE)) {
    usuarios = JSON.parse(fs.readFileSync(USERS_FILE));
}

const guardarUsuarios = () => {
    fs.writeFileSync(USERS_FILE, JSON.stringify(usuarios, null, 2));
};

// --- RUTAS DE AUTENTICACIÓN ---

app.post('/api/register', (req, res) => {
    const { nombre, email, pass, pregunta, respuesta } = req.body;
    
    if (!email || !pass || !nombre) {
        return res.json({ success: false, message: "Faltan campos críticos." });
    }

    if (usuarios[email]) {
        return res.json({ success: false, message: "El correo ya está registrado." });
    }

    usuarios[email] = { nombre, pass, pregunta, respuesta };
    guardarUsuarios();
    
    console.log(`Usuario registrado: ${email}`);
    res.json({ success: true });
});

app.post('/api/login', (req, res) => {
    const { email, pass } = req.body;
    const user = usuarios[email];

    if (user && user.pass === pass) {
        res.json({ success: true, nombre: user.nombre });
    } else {
        res.json({ success: false, message: "Correo o contraseña incorrectos." });
    }
});

app.post('/api/recover', (req, res) => {
    const { email, pregunta, respuesta, nuevaPass } = req.body;
    const user = usuarios[email];

    if (user && user.pregunta === pregunta && user.respuesta === respuesta) {
        user.pass = nuevaPass;
        guardarUsuarios();
        res.json({ success: true, mensaje: "Contraseña actualizada con éxito." });
    } else {
        res.json({ success: false, mensaje: "Los datos de seguridad no coinciden." });
    }
});

// --- RUTA DEL CHAT (CONEXIÓN CON C++) ---

app.post('/api/chat', (req, res) => {
    const { mensaje } = req.body;
    if (!mensaje) return res.json({ message: "..." });

    try {
        // Escapamos comillas dobles para evitar que rompan el comando de terminal
        const mensajeSeguro = mensaje.replace(/"/g, '\\"');
        
        // Ejecutamos el binario DiezusAI compilado por Docker
        const resultado = execSync(`./DiezusAI "${mensajeSeguro}"`).toString();
        
        // Enviamos el JSON que genera el C++ directamente al frontend
        res.json(JSON.parse(resultado));
    } catch (e) {
        console.error("Error ejecutando el núcleo C++:", e);
        res.json({ 
            message: "Lo siento, mi núcleo está procesando demasiada información ahora.", 
            sentiment: "neutral", 
            action: "none" 
        });
    }
});

// --- RUTA INICIAL ---

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'Frontend.html'));
});

// Puerto dinámico para Render
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`--- DIEZUS AI ACTIVO ---`);
    console.log(`Servidor escuchando en puerto: ${PORT}`);
});