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

// Objeto temporal para contar alertas en la sesión actual
// Esto no se guarda en el JSON para que el contador reinicie al refrescar,
// pero podrías moverlo a 'usuarios[email]' si quieres que sea permanente.
let alertasSesion = {};

// --- RUTAS DE AUTENTICACIÓN --- (Sin cambios)
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
        // Inicializamos el contador de alertas para este usuario al loguearse
        alertasSesion[email] = 0;
        res.json({ success: true, nombre: user.nombre, email: email }); // Enviamos email para el front
    } else {
        res.json({ success: false, message: "Error." });
    }
});

// --- RUTA DEL CHAT CON LÓGICA DE 3 ADVERTENCIAS ---

app.post('/api/chat', (req, res) => {
    const { mensaje, email } = req.body; // El front debe enviar el email del usuario activo
    if (!mensaje) return res.json({ message: "..." });

    try {
        const mensajeSeguro = mensaje.replace(/"/g, '\\"');
        const resultadoStr = execSync(`./DiezusAI "${mensajeSeguro}"`).toString();
        const resultado = JSON.parse(resultadoStr);

        // Lógica de acumulador de sentimientos negativos
        if (resultado.sentiment === "critical") {
            if (!alertasSesion[email]) alertasSesion[email] = 0;
            alertasSesion[email]++;

            console.log(`Alerta detectada para ${email}. Total: ${alertasSesion[email]}`);

            // Si aún no llega a 3, bloqueamos la acción de ir a jugar
            if (alertasSesion[email] < 3) {
                resultado.action = "none";
                resultado.message = `Te escucho con atención... Te noto algo decaído por ${alertasSesion[email]}ª vez).`;
            } else {
                // A la tercera vez, mantenemos el 'suggest_break' y reiniciamos contador
                resultado.message = "Ya son varias veces que te noto así hoy. Como tu compañero Diezus, insisto: detente y despeja tu mente con un juego.";
                alertasSesion[email] = 0; 
            }
        }

        res.json(resultado);
    } catch (e) {
        console.error("Error:", e);
        res.json({ message: "Error en el núcleo.", sentiment: "neutral", action: "none" });
    }
});

app.get('/', (req, res) => { res.sendFile(path.join(__dirname, 'Frontend.html')); });

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => { console.log(`DIEZUS AI en puerto ${PORT}`); });