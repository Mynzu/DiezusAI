const express = require('express');
const path = require('path');
const { execSync } = require('child_process');
const fs = require('fs');
const app = express();

app.use(express.json());
app.use(express.static(__dirname));

const USERS_FILE = './usuarios.json';
let usuarios = {};

if (fs.existsSync(USERS_FILE)) {
    usuarios = JSON.parse(fs.readFileSync(USERS_FILE));
}

const guardarUsuarios = () => {
    fs.writeFileSync(USERS_FILE, JSON.stringify(usuarios, null, 2));
};

let alertasSesion = {};

// --- RUTAS DE AUTENTICACIÓN ---
app.post('/api/register', (req, res) => {
    const { nombre, email, pass, pregunta, respuesta } = req.body;
    if (!email || !pass || !nombre) return res.json({ success: false, message: "Faltan campos." });
    if (usuarios[email]) return res.json({ success: false, message: "Ya existe." });
    usuarios[email] = { nombre, pass, pregunta, respuesta };
    guardarUsuarios();
    res.json({ success: true });
});

app.post('/api/login', (req, res) => {
    const { email, pass } = req.body;
    const user = usuarios[email];
    if (user && user.pass === pass) {
        alertasSesion[email] = 0;
        res.json({ success: true, nombre: user.nombre, email: email });
    } else {
        res.json({ success: false, message: "Error de credenciales." });
    }
});

// --- RUTA DEL CHAT SINCRONIZADA CON C++ ---

app.post('/api/chat', (req, res) => {
    const { mensaje, email } = req.body; 
    if (!mensaje) return res.json({ res: "..." });

    try {
        // Escapamos comillas para que el shell no rompa el comando
        const mensajeSeguro = mensaje.replace(/"/g, '\\"');
        
        // Ejecutamos el motor Diezus (asegúrate que el ejecutable se llame DiezusAI)
        const resultadoStr = execSync(`./DiezusAI "${mensajeSeguro}"`).toString();
        const resultado = JSON.parse(resultadoStr);

        // SINCRONIZACIÓN DE VARIABLES:
        // C++ entrega: sev (0-9), res (texto), act (none/trigger_games)
        
        // Lógica de acumulador (Nivel 9 o Nivel 0 detectado por el motor)
        if (resultado.sev === 9 || resultado.sev === 0) {
            if (!alertasSesion[email]) alertasSesion[email] = 0;
            alertasSesion[email]++;

            console.log(`Estado crítico/triste detectado para ${email}. Acumulado: ${alertasSesion[email]}`);

            if (alertasSesion[email] < 3) {
                // Bloqueamos la redirección automática hasta la 3ra vez
                resultado.act = "none";
                resultado.res = `Entiendo que te sientes así (Aviso ${alertasSesion[email]}/3). Aquí estoy para escucharte.`;
            } else {
                // A la tercera, mantenemos act: "trigger_games"
                resultado.res = "He notado esta tendencia varias veces hoy. Como Diezus, insisto: es momento de despejar tu mente con un juego.";
                alertasSesion[email] = 0; // Reiniciamos
            }
        }

        res.json(resultado);
    } catch (e) {
        console.error("Error en ejecución C++:", e);
        res.json({ res: "Error en el núcleo de procesamiento.", sev: 3, act: "none" });
    }
});

app.get('/', (req, res) => { res.sendFile(path.join(__dirname, 'Frontend.html')); });

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => { console.log(`DIEZUS AI operativo en puerto ${PORT}`); });