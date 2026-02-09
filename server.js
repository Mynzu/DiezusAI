const express = require('express');
const path = require('path');
const { execSync } = require('child_process');
const fs = require('fs');
const app = express();

app.use(express.json());
app.use(express.static(__dirname));

const USERS_FILE = './usuarios.json';
let usuarios = fs.existsSync(USERS_FILE) ? JSON.parse(fs.readFileSync(USERS_FILE)) : {};

app.post('/api/register', (req, res) => {
    const { nombre, email, pass, pregunta, respuesta } = req.body;
    if (usuarios[email]) return res.json({ success: false, message: "Ya existe." });
    usuarios[email] = { nombre, pass, pregunta, respuesta };
    fs.writeFileSync(USERS_FILE, JSON.stringify(usuarios, null, 2));
    res.json({ success: true });
});

app.post('/api/login', (req, res) => {
    const { email, pass } = req.body;
    const user = usuarios[email];
    if (user && user.pass === pass) res.json({ success: true, nombre: user.nombre, email: email });
    else res.json({ success: false });
});

app.post('/api/chat', (req, res) => {
    const { mensaje, email } = req.body; 
    if (!mensaje) return res.json({ res: "..." });
    try {
        const mensajeSeguro = mensaje.replace(/"/g, '\\"');
        // El servidor NO toca la lógica, solo ejecuta y devuelve lo que diga Diezus
        const resultadoStr = execSync(`./DiezusAI "${mensajeSeguro}" "${email}"`).toString();
        res.json(JSON.parse(resultadoStr));
    } catch (e) {
        res.json({ res: "Error en el núcleo de Diezus.", sev: 3, act: "none" });
    }
});

app.get('/', (req, res) => { res.sendFile(path.join(__dirname, 'Frontend.html')); });

app.listen(process.env.PORT || 3000, () => console.log("Servidor Online"));